#include "client.h"
#include <QScrollBar>
#include <QStyle>
#include <QToolButton>
#include <QtNetwork/QSslCipher>
#include <QFile>
#include <QFileDialog>
#include <QSettings>

client::client(QString settingFile, bool justcae, QWidget *parent)
    :QWidget(parent), socket(0), padLock(0), executingDialog(false), _justcae(justcae) {

    QSettings settings(settingFile, QSettings::IniFormat);
    settings.setValue("Version", 0.1);
    settings.beginGroup("global");
    certConexion = settings.value("cert", "").toString();
    testing = settings.value("testing").toBool();
    source = settings.value("source", "").toString();
    x509 = settings.value("x509", "").toString();
    pedido = settings.value("pedido", "").toString();
    pedido_iva = settings.value("pedido_iva", "").toString();
    pass = settings.value("pass", "").toString();
    inker = settings.value("inker", "").toString();
    port = settings.value("port", 443).toInt();
    _justcae = settings.value("justcae", false).toBool() || justcae;
    prestaserv = settings.value("prestaserv", false).toBool() ? "1" : "0";
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

    wsaa = new wsaaLogin(socket, testing, this);
    wsfe = new wsfeManager(wsaa, testing, this);

    connect(wsaa, SIGNAL(login(QString,QString)), this, SLOT(logedIn()));
    connect(wsfe, SIGNAL(serverResponse(QString)), this, SLOT(logSessionData(QString)));
    connect(wsfe, SIGNAL(serverDataSent(QString)), this, SLOT(appendString(QString)));

    form = new Ui_wsfeForm;
    form->setupUi(this);
    this->setWindowTitle("Facturación Eelctronica v1");
    form->hostNameEdit->setSelection(0, form->hostNameEdit->text().size());
    form->sessionOutput->setHtml(tr("&lt;not connected&gt;"));
    form->hostNameEdit->setText(wsaa->getServiceUrl());

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

void client::logedIn()
{
    form->connectButton->setEnabled(false);
    form->doButton->setEnabled(true);
    if(_justcae) validateRecipe();
}

void client::doOperation()
{
    QString op = form->operationComboBox->currentText();

    if (op == "Obtener Ult. Comprobante") getLastApproveRecipe();
    if (op == "Obtener Info de Comprobante") getRecipeInfo();
    if (op == "Obtener CAE p/Comprobante") validateRecipe();
    if (op == "Obtener tipos de IVAs") wsfe->getData(wsfeManager::wsfeGetIvaOpPath);
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
    if (_justcae) qApp->quit();
}

void client::getLastApproveRecipe() {
    int pto_venta = form->puntoVentaSpinBox->value(),
        tipo_comp = form->tipoComprobanteSpinBox->value();


    wsfe->getLastAuthRecipe(pto_venta, tipo_comp);
}

void client::validateRecipe()
{
    wsfe->validateRecipies(pedido, pedido_iva);
}


void client::appendString(const QString &line)
{
    QTextCursor cursor(form->sessionOutput->textCursor());
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(line);
    form->sessionOutput->verticalScrollBar()->setValue(form->sessionOutput->verticalScrollBar()->maximum());
}
