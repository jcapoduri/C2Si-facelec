#include "client.h"
#include <QScrollBar>
#include <QStyle>
#include <QToolButton>
#include <QtNetwork/QSslCipher>
#include <QFile>
#include <QFileDialog>
#include <QSettings>
#include <QTimer>

client::client(QString settingFile, bool justcae, QWidget *parent)
    :QWidget(parent), socket(0), padLock(0), executingDialog(false), _justcae(justcae), closeTimer(this) {

    QSettings settings(settingFile, QSettings::IniFormat);
    settings.setValue("Version", 0.1);
    settings.beginGroup("global");
    certConexion = settings.value("cert", "").toString();
    testing = settings.value("testing").toBool();
    source = settings.value("source", "").toString();
    x509 = settings.value("x509", "").toString();
    pedido = settings.value("pedido", "").toString();
    pedido_iva = settings.value("pedido_iva", "").toString();
    pedido_tributo = settings.value("pedido_tributo", "").toString();
    pass = settings.value("pass", "").toString();
    inker = settings.value("inker", "").toString();
    port = settings.value("port", 443).toInt();
    _justcae = settings.value("justcae", false).toBool() || justcae;
    prestaserv = settings.value("prestaserv", false).toBool() ? "1" : "0";
    secondsToClose = settings.value("secondsToClose", QVariant(30)).toInt();
    ptoventa = settings.value("ptoventa", 1).toString().rightJustified(4, '0');
    settings.endGroup();

    wsaaok = false;
    cuit = source.mid(source.indexOf("CUIT")+5, 11);

    QFile certFile(certConexion);
    if(!certFile.open(QIODevice::ReadOnly)){
        certConexion = QFileDialog::getOpenFileName(this,tr("Open certificate"), "", tr("Cert Files (*.crt)"));
        QFile certFile(certConexion);
        certFile.open(QIODevice::ReadOnly);
    };
    QSslCertificate cert(&certFile, QSsl::Pem);

    socket = new QSslSocket(this);

    socket->addCaCertificate(cert);

    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(encrypted()),
            this, SLOT(socketEncrypted()));
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(sslErrors(QList<QSslError>)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socketErrors(QAbstractSocket::SocketError)));
    connect(&closeTimer, SIGNAL(timeout()), qApp, SLOT(quit()));

    wsaa = new wsaaLogin(socket, testing, this);
    wsfe = new wsfeManager(wsaa, testing, this);

    connect(wsaa, SIGNAL(login(QString,QString)), this, SLOT(logedIn()));
    connect(wsaa, SIGNAL(logFailed()), this, SLOT(cleanCae()));
    connect(wsfe, SIGNAL(serverResponse(QString)), this, SLOT(logSessionData(QString)));
    connect(wsfe, SIGNAL(serverDataSent(QString)), this, SLOT(appendString(QString)));

    form = new Ui_wsfeForm;
    form->setupUi(this);
    form->operationHelperComboBox->setVisible(false);
    this->setWindowTitle("Facturación Eelctronica v1");
    form->hostNameEdit->setSelection(0, form->hostNameEdit->text().size());
    form->sessionOutput->setHtml(tr("&lt;not connected&gt;"));
    form->hostNameEdit->setText(wsaa->getServiceUrl());

    connect(form->operationComboBox, SIGNAL(currentTextChanged(QString)),
            this, SLOT(operationChanged(QString)));
    connect(form->hostNameEdit, SIGNAL(textChanged(QString)),
            this, SLOT(updateEnabledState()));
    connect(form->connectButton, SIGNAL(clicked()),
            this, SLOT(secureConnect()));
    connect(form->doButton, SIGNAL(clicked()),
            this, SLOT(doOperation()));

    if (_justcae) secureConnect();
}

client::~client()
{
    delete form;
}

void client::updateEnabledState()
{
    bool unconnected = !socket || socket->state() == QAbstractSocket::UnconnectedState;

    form->hostNameEdit->setReadOnly(!unconnected);
    form->hostNameEdit->setFocusPolicy(unconnected ? Qt::StrongFocus : Qt::NoFocus);
    if(!form->connectButton->isEnabled()){
        form->connectButton->setEnabled(unconnected && !form->hostNameEdit->text().isEmpty());
    };
    bool connected = socket && socket->state() == QAbstractSocket::ConnectedState;
    form->sessionOutput->setEnabled(connected);    
    if(this->wsaaok){
        form->connectButton->setEnabled(false);
        form->doButton->setEnabled(true);
    };
}

void client::secureConnect()
{    
    wsaa->getAuth(source, x509, inker, pass);
    if (secondsToClose > 0) closeTimer.start(secondsToClose * 1000);
}

void client::socketStateChanged(QAbstractSocket::SocketState state)
{
    if (executingDialog)
        return;

    updateEnabledState();
    qDebug() << "Estado: " << state;
}

void client::socketEncrypted()
{
    if (!socket)
        return;                 // might have disconnected already

    //form->sessionOutput->clear();

    QPalette palette;
    palette.setColor(QPalette::Base, QColor(255, 255, 192));
    form->hostNameEdit->setPalette(palette);

    if (!padLock) {
        padLock = new QToolButton;
        padLock->setIcon(QIcon(":/encrypted.png"));
        padLock->setCursor(Qt::ArrowCursor);
        padLock->setToolTip(tr("Display encryption details."));

        int extent = form->hostNameEdit->height() - 2;
        padLock->resize(extent, extent);
        padLock->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);

        QHBoxLayout *layout = new QHBoxLayout(form->hostNameEdit);
        layout->setMargin(form->hostNameEdit->style()->pixelMetric(QStyle::PM_DefaultFrameWidth));
        layout->setSpacing(0);
        layout->addStretch();
        layout->addWidget(padLock);

        form->hostNameEdit->setLayout(layout);
    } else {
        padLock->show();
    }
}

void client::sslErrors(const QList<QSslError> &errors)
{
    qDebug() << "hubo errores de ssl";
    QSslError err;
    for(int i = 0; i < errors.length(); i++){
        qDebug() << errors.at(i);
    };
}

void client::socketErrors(const QAbstractSocket::SocketError error)
{
    qDebug() << error;
    QString errorString;
    switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
      errorString = "La conexion fue refutada desde el servidor o se termino el tiempo de respuesta";
      break;
    case QAbstractSocket::RemoteHostClosedError:
      errorString = "El servidor cerro la conexion actual";
      break;
    case QAbstractSocket::HostNotFoundError:
      errorString = "No se encuentra el servidor destino";
      break;
    case QAbstractSocket::SocketAccessError:
      errorString = "No tiene suficientes privilegios para hacer la siguiente operacion";
      break;
    case QAbstractSocket::SocketResourceError:
      errorString = "El servidor no puede atender el pedido actual";
      break;
    case QAbstractSocket::SocketTimeoutError:
      errorString = "La operaciòn se quedo sin tiempo de espera";
      break;
    case QAbstractSocket::DatagramTooLargeError:
      errorString = "Datagrama demasiado largo";
      break;
    case QAbstractSocket::NetworkError:
      errorString = "Error en la red (cable/wifi desactivado)";
      break;
    case QAbstractSocket::AddressInUseError:
      errorString = "Error en la direcciòn destino";
      break;
    case QAbstractSocket::SocketAddressNotAvailableError:
      errorString = "La direcciòn del servidor destino no pudo ser resuelta";
      break;
    case QAbstractSocket::UnsupportedSocketOperationError:
      errorString = "El pedido al servidor destino no pudo ser resuelto";
      break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
      errorString = "Error en la autentificaciòn al servidor proxy";
      break;
    case QAbstractSocket::SslHandshakeFailedError:
      errorString = "Error al intercambiar información de SSL";
      break;
    case QAbstractSocket::UnfinishedSocketOperationError:
      errorString = "No se pudo cerrar correctamente la ultima operación";
      break;
    case QAbstractSocket::ProxyConnectionRefusedError:
      errorString = "El servidor proxy actual desconecto la conexion actual";
      break;
    case QAbstractSocket::ProxyConnectionClosedError:
      errorString = "El servidor proxy actual cerro la conexion actual";
      break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
      errorString = "El servidor proxy actual desconecto la conexion actual por timeout";
      break;
    case QAbstractSocket::ProxyNotFoundError:
      errorString = "Servidor proxy no encontrado";
      break;
    case QAbstractSocket::ProxyProtocolError:
      errorString = "Servidor proxy invalido";
      break;
    case QAbstractSocket::OperationError:
      errorString = "Error en la operación actual";
      break;
    case QAbstractSocket::SslInternalError:
      errorString = "Error interno de SSL";
      break;
    case QAbstractSocket::SslInvalidUserDataError:
      errorString = "Error de datos de usuario invalido para SSL";
      break;
    case QAbstractSocket::TemporaryError:
      errorString = "Error temporal, pruebe mas tarde";
      break;
    default:
      errorString = "Error desconocido";
      break;
    }
    appendString(errorString);
}

void client::logedIn()
{
    form->connectButton->setEnabled(false);
    form->doButton->setEnabled(true);
    if (secondsToClose > 0) closeTimer.stop();
    if(_justcae) validateRecipe();
}

void client::operationChanged(QString value)
{
    qDebug() << value;
    form->operationHelperComboBox->setVisible(value == "Informacion");
}

void client::doOperation()
{
    QString op = form->operationComboBox->currentText();

    if (op == "Obtener Ult. Comprobante") getLastApproveRecipe();
    if (op == "Obtener Info de Comprobante") getRecipeInfo();
    if (op == "Obtener CAE p/Comprobante") validateRecipe();
    if (op == "Informacion") wsfe->getData(form->operationHelperComboBox->currentText());
}

void client::getRecipeInfo() {
    int pto_venta = form->puntoVentaSpinBox->value(),
        tipo_comp = form->tipoComprobanteSpinBox->value(),
        nro_comp = form->nroComprobanteSpinBox->value();

    wsfe->getRecipeInfo(tipo_comp, pto_venta, nro_comp);
}

void client::logSessionData(QString data)
{
    if (data.isEmpty()) return;
    form->sessionOutput->append(data);
    qDebug() << data;
    QString op = form->operationComboBox->currentText();

    if (op == "Obtener CAE p/Comprobante") {
        QString caeBeginToken = "<CAE>";
        QString caeEndToken = "</CAE>";
        QString fecvenBeginToken = "CAEFchVto>";
        QString fecvenEndToken = "</CAEFchVto>";
        QString pererrBeginToken = "<Errors>";
        QString pererrEndToken = "</Errors>";

        int caeStart = data.indexOf(caeBeginToken) + caeBeginToken.length();
        int caeLength = data.indexOf(caeEndToken) - caeStart;
        int fecvenStart = data.indexOf(fecvenBeginToken) + fecvenBeginToken.length();
        int fecvenLength = data.indexOf(fecvenEndToken) - fecvenStart;
        int errorStart = data.indexOf(pererrBeginToken) + pererrBeginToken.length();
        int errorLength = data.indexOf(pererrEndToken) - errorStart;

        QFile file("cae.txt");
        file.open(QIODevice::WriteOnly);
        if (caeLength > 0) {
            file.write(data.mid(caeStart, caeLength).toLatin1());
        } else {
            file.write("00000000");
        };
        if (fecvenLength > 0) {
            file.write(data.mid(fecvenStart, fecvenLength).toLatin1());
        } else {
            file.write("00000000");
        };
        if (errorLength > 0) file.write(data.mid(errorStart, errorLength).toLatin1());
        file.close();
    }

    QFile fileRes(QString("wsferesponse.txt"));
    fileRes.open(QIODevice::Append);
    fileRes.write(data.toLatin1());
    fileRes.close();
    if (secondsToClose > 0) closeTimer.start(secondsToClose * 1000);
    if (_justcae) qApp->quit();    
}

void client::getLastApproveRecipe() {
    int pto_venta = form->puntoVentaSpinBox->value(),
        tipo_comp = form->tipoComprobanteSpinBox->value();


    wsfe->getLastAuthRecipe(pto_venta, tipo_comp);
}

void client::cleanCae() {
    QFile file("cae.txt");
    file.open(QIODevice::WriteOnly);
    file.write("00000000");
    file.close();
}

void client::validateRecipe()
{
    wsfe->validateRecipies(pedido, pedido_iva, pedido_tributo);
}


void client::appendString(const QString &line)
{
    QTextCursor cursor(form->sessionOutput->textCursor());
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(line);
    form->sessionOutput->verticalScrollBar()->setValue(form->sessionOutput->verticalScrollBar()->maximum());
}
