#include "sslclient.h"
#include <QScrollBar>
#include <QStyle>
#include <QToolButton>
#include <QtNetwork/QSslCipher>
#include <QFile>
#include <QFileDialog>

SslClient::SslClient(QWidget *parent)
    : QWidget(parent), socket(0), padLock(0), executingDialog(false), _justcae(false)
{
    wsaaok = false;
    form = new Ui_Form;
    form->setupUi(this);
    form->hostNameEdit->setSelection(0, form->hostNameEdit->text().size());
    form->sessionOutput->setHtml(tr("&lt;not connected&gt;"));

    connect(form->hostNameEdit, SIGNAL(textChanged(QString)),
            this, SLOT(updateEnabledState()));
    connect(form->connectButton, SIGNAL(clicked()),
            this, SLOT(secureConnect()));
    connect(form->pedirCaeButton, SIGNAL(clicked()),
            this, SLOT(secureConnect()));
    connect(form->pedirProxFactura, SIGNAL(clicked()),
            this, SLOT(secureConnect()));
}

SslClient::SslClient(QString wsaa, QString wsfe, QString inker, QString pass, QString cert, QString x509, QString pedido, QString source, int port, int ptoventa, bool testing, bool prestaserv, QWidget *parent)
    :QWidget(parent), socket(0), padLock(0), executingDialog(false), _justcae(false) {
    wsaaok = false;
    this->wsaa = wsaa;
    this->wsfe = wsfe;
    this->certConexion = cert;
    this->x509 = x509;
    this->sourceEmpresa = source;
    this->pass = pass;
    this->inker = inker;
    this->cuit = source.mid(source.indexOf("CUIT")+5, 11); qDebug() << cuit;
    this->port = port;
    this->pedido = pedido;
    this->testing = testing;
    this->ptoventa.arg("%1").arg(ptoventa);
    this->ptoventa.rightJustified(4, '0');
    this->prestaserv = prestaserv ? "1" : "0";

    form = new Ui_Form;
    form->setupUi(this);
    form->hostNameEdit->setSelection(0, form->hostNameEdit->text().size());
    form->sessionOutput->setHtml(tr("&lt;not connected&gt;"));
    form->hostNameEdit->setText(wsaa);

    connect(form->hostNameEdit, SIGNAL(textChanged(QString)),
            this, SLOT(updateEnabledState()));
    connect(form->connectButton, SIGNAL(clicked()),
            this, SLOT(secureConnect()));
    connect(form->pedirCaeButton, SIGNAL(clicked()),
            this, SLOT(secureConnect()));
    connect(form->pedirProxFactura, SIGNAL(clicked()),
            this, SLOT(secureConnect()));
}

SslClient::~SslClient()
{
    delete form;
}

void SslClient::updateEnabledState()
{
    bool unconnected = !socket || socket->state() == QAbstractSocket::UnconnectedState;

    form->hostNameEdit->setReadOnly(!unconnected);
    form->hostNameEdit->setFocusPolicy(unconnected ? Qt::StrongFocus : Qt::NoFocus);
    if(!form->connectButton->isEnabled()){
        form->hostNameLabel->setEnabled(unconnected);
        form->portBox->setEnabled(unconnected);
        form->portLabel->setEnabled(unconnected);
        form->connectButton->setEnabled(unconnected && !form->hostNameEdit->text().isEmpty());
    };
    bool connected = socket && socket->state() == QAbstractSocket::ConnectedState;
    /*form->sessionBox->setEnabled(connected);*/
    form->sessionOutput->setEnabled(connected);    
    if(this->wsaaok){
        form->connectButton->setEnabled(false);
        form->pedirCaeButton->setEnabled(true);
        form->pedirProxFactura->setEnabled(true);
    };
}

void SslClient::secureConnect()
{    
    if (!socket) {
        QString file = this->certConexion;

        QFile certFile(file);
        if(!certFile.open(QIODevice::ReadOnly)){
            file = QFileDialog::getOpenFileName(this,tr("Open certificate"), "", tr("Cert Files (*.crt)"));
            QFile certFile(file);
            certFile.open(QIODevice::ReadOnly);
        };
        qDebug() << "before cert";
        appendString("before cert");
        QSslCertificate cert(&certFile, QSsl::Pem);
        qDebug() << "after cert";
        appendString("after cert");

        socket = new QSslSocket(this);

        appendString("before add cert");
        qDebug() << "before add cert";
        socket->addCaCertificate(cert);
        qDebug() << "after add cert";
        appendString("after add cert");

        connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
        connect(socket, SIGNAL(encrypted()),
                this, SLOT(socketEncrypted()));
        connect(socket, SIGNAL(sslErrors(QList<QSslError>)),
                this, SLOT(sslErrors(QList<QSslError>)));
        if(!wsaaok){
            connect(socket, SIGNAL(readyRead()),this, SLOT(socketReadyRead()));
        }else{
            connect(socket, SIGNAL(readyRead()),this, SLOT(socketFacReadyRead()));
            form->hostNameEdit->setText(this->wsfe);
        };
    }
    socket->connectToHostEncrypted(form->hostNameEdit->text(), form->portBox->value());
    updateEnabledState();
     if(!wsaaok){
        sendData();
     }else{
        sendFacData();
        //sendLastFac();
     };

}

void SslClient::socketStateChanged(QAbstractSocket::SocketState state)
{
    if (executingDialog)
        return;

    updateEnabledState();
    qDebug() << "Estado: " << state;
    if (state == QAbstractSocket::UnconnectedState) {
        form->hostNameEdit->setPalette(QPalette());
        form->hostNameEdit->setFocus();
        form->cipherLabel->setText(tr("<none>"));
        if (padLock)
            padLock->hide();
        socket->deleteLater();
        socket = 0;
    }
}

void SslClient::socketEncrypted()
{
    if (!socket)
        return;                 // might have disconnected already

    form->sessionOutput->clear();
    /*form->sessionInput->setFocus();*/

    QPalette palette;
    palette.setColor(QPalette::Base, QColor(255, 255, 192));
    form->hostNameEdit->setPalette(palette);

    QSslCipher ciph = socket->sessionCipher();
    QString cipher = QString("%1, %2 (%3/%4)").arg(ciph.authenticationMethod())
                     .arg(ciph.name()).arg(ciph.usedBits()).arg(ciph.supportedBits());;
    form->cipherLabel->setText(cipher);

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

        connect(padLock, SIGNAL(clicked()),
                this, SLOT(displayCertificateInfo()));
    } else {
        padLock->show();
    }
}

void SslClient::socketReadyRead()
{
    QString tokenBegin = QString("&lt;token&gt;");
    QString tokenEnd = QString("&lt;/token&gt;");
    QString signBegin = QString("&lt;sign&gt;");
    QString signEnd = QString("&lt;/sign&gt;");
    //QString token, sign;

    QString data = QString::fromUtf8(socket->readAll());

    int tokenStart = data.indexOf(tokenBegin) + tokenBegin.length();
    if(tokenStart != (tokenBegin.length() - 1)){
        wsaaok = true;
        //int tokenStart = data.indexOf(tokenBegin) + tokenBegin.length();
        int tokenFinish = data.indexOf(tokenEnd) - tokenStart;
        int signStart = data.indexOf(signBegin) + signBegin.length();
        int signFinish = data.indexOf(signEnd) - signStart;

        token = data.mid(tokenStart, tokenFinish);
        sign = data.mid(signStart, signFinish);

        qDebug() << "tokenStart: " << tokenStart;
        qDebug() << "tokenFinish: " << tokenFinish;
        qDebug() << "signStart: " << signStart;
        qDebug() << "signFinish: " << signFinish;
        qDebug() << "data: " << data;
        qDebug() << "token: " << token;
        qDebug() << "sign: " << sign;
        emit this->wsaalogon(true);
    }else{
        emit this->wsaalogon(false);
    };
    appendString(data);
}

void SslClient::socketFacReadyRead()
{
    QString data = QString::fromUtf8(socket->readAll());
    QString caeBeginToken = "<cae>";
    QString caeEndToken = "</cae>";
    QString fecvenBeginToken = "fecha_vto>";
    QString fecvenEndToken = "</fecha_vto>";
    QString pererrBeginToken = "<percode>";
    QString pererrEndToken = "</percode>";

    int caeStart = data.indexOf(caeBeginToken) + caeBeginToken.length();
    int caeLength = data.indexOf(caeEndToken) - caeStart;
    int fecvenStart = data.indexOf(fecvenBeginToken) + fecvenBeginToken.length();
    int fecvenLength = data.indexOf(fecvenEndToken) - fecvenStart;
    int errorStart = data.indexOf(pererrBeginToken) + pererrBeginToken.length();
    int errorLength = data.indexOf(pererrEndToken) - errorStart;

    QFile file("cae.txt");
    file.open(QIODevice::WriteOnly);
    file.write(data.mid(caeStart, caeLength).toLatin1());
    file.write(data.mid(fecvenStart, fecvenLength).toLatin1());
    file.write(data.mid(errorStart, errorLength).toLatin1());

    QFile fileRes("wsferesponse.txt");
    fileRes.open(QIODevice::WriteOnly);
    fileRes.write(data.toLatin1());

    qDebug() << data;
    appendString(data);
    if (_justcae) {
        this->close();
    } else {
        this->show();
    };

}

void SslClient::sendData()
{
    /*QString input = form->sessionInput->text();
    appendString(input + "\n");
    socket->write(input.toUtf8() + "\n");
    form->sessionInput->clear();*/

    /* Creo el ticket */
    QString cms = makeTRA();
    if(cms != ""){
        QString input = makeTicket(cms);
        //QMessageBox::warning(this, QString("test"), QString("%1").arg(input.length()), QMessageBox::Yes);
        appendString(input + "\n");
        socket->write(input.toUtf8() + "\n");
        /*form->sessionInput->clear();*/
    };
}

void SslClient::sendFacData()
{
    QString data;

    /*data = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
    "<soap:Envelope xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:ar=\"http://ar.gov.afip.dif.facturaelectronica/\">\n"
    "<soap:Body>\n"
    "<FERecuperaLastCMPRequest xmlns=\"http://ar.gov.afip.dif.facturaelectronica/\">\n"
    "<argAuth>\n"
    "        <Token>"+token+"</Token>\n"
    "        <Sign>"+sign+"</Sign>\n"
    "        <cuit>30664156489</cuit>\n"
    "</argAuth>\n"
    "<argTCMP>\n"
    "<PtoVta>0002</PtoVta>\n"
    "<TipoCbte>01</TipoCbte>\n"
    "</argTCMP>\n"
    "</FERecuperaLastCMPRequest>\n"
    "</soap:Body>\n"
    "</soap:Envelope>";*/

    data = ""
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">\n"
    "  <soap:Body>\n"
    "    <FEAutRequest xmlns=\"http://ar.gov.afip.dif.facturaelectronica/\">\n"
    "      <argAuth>\n"
    "        <Token>"+token+"</Token>\n"
    "        <Sign>"+sign+"</Sign>\n"
    "        <cuit>"+this->cuit+"</cuit>\n"
    "      </argAuth>\n"
    "      <Fer>\n"
    "        <Fecr>\n"
    "          <id>123456</id>\n"
    "          <cantidadreg>1</cantidadreg>\n"
    "          <presta_serv>0</presta_serv>\n"
    "        </Fecr>\n"
    "        <Fedr>\n"
    "          <FEDetalleRequest>\n";
    data += parseFactura(this->pedido);
    data += "          </FEDetalleRequest>\n"
                "        </Fedr>\n"
                "      </Fer>\n"
                "    </FEAutRequest>\n"
                "  </soap:Body>\n"
                "</soap:Envelope>";

    data =
    //"POST /wsfe/service.asmx HTTP/1.1\n"
    //"Host: servicios1.afip.gov.ar\n"
    "POST /wsfe/service.asmx?op=FEAutRequest HTTP/1.1\n"
    //"POST /wsfe/service.asmx?op= HTTP/1.1\n"
    //"SOAPAction: \"http://ar.gov.afip.dif.facturaelectronica/FERecuperaLastCMPRequest\"\n"
    //"Host: wswhomo.afip.gov.ar\n"
    "Host: "+this->wsfe+"\n"
    "Content-Type: text/xml; charset=utf-8\n"
    "Content-Length: "+QString("%1").arg(data.length())+"\n\n" + data;

    //"SOAPAction: \"http://ar.gov.afip.dif.facturaelectronica/FEAutRequest\"\n"
    appendString(data + "\n");
    qDebug() << data;
    socket->write(data.toUtf8() + "\n");
    /*form->sessionInput->clear();*/
}

void SslClient::sendLastFac(){
    QString data;
    data = ""
           "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
           "<soap:Envelope xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:ar=\"http://ar.gov.afip.dif.facturaelectronica/\">\n"
           "  <soap:Body>\n"
           "    <ar:FERecuperaLastCMPRequest>\n"
           "      <ar:argAuth>\n"
           "        <ar:Token>"+token+"</ar:Token>\n"
           "        <ar:Sign>"+sign+"</ar:Sign>\n"
           "        <ar:cuit>"+this->cuit+"</ar:cuit>\n"
           "      </ar:argAuth>\n"
           "      <ar:argTCMP>\n"
           "        <ar:PtoVta>1</ar:PtoVta>\n"
           "        <ar:TipoCbte>1</ar:TipoCbte>\n"
           "      </ar:argTCMP>\n"
           "    </ar:FERecuperaLastCMPRequest>\n"
           "  </soap:Body>\n"
           "</soap:Envelope>";

    data =
    "POST /wsfe/service.asmx?op=FERecuperaLastCMPRequest HTTP/1.1\n"
    "Host: "+this->wsfe+"\n"
    "Content-Type: text/xml; charset=utf-8\n"
    "Content-Length: "+QString("%1").arg(data.length())+"\n\n" + data;

    appendString(data + "\n");
    socket->write(data.toUtf8() + "\n");
    qDebug() << data;
}

QString SslClient::makeTRA(){
    QString TRA;
    TRA = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
        "<loginTicketRequest version=\"1.0\">\n"
          "<header>\n"
          //"<source>C = AR, O = Rex agencia de publicidad sociedad colectiva, SERIALNUMBER = CUIT 30664156489, CN = Ciamberlani Guillermo</source>\n"
          "<source>"+this->sourceEmpresa+"</source>\n"
            "<destination>CN=wsaa"+(this->testing ? "homo" : "")+", O=AFIP, C=AR, SERIALNUMBER=CUIT 33693450239</destination>\n"
            "<uniqueId>123456</uniqueId>\n"
            "<generationTime>"+QDateTime::currentDateTime().addSecs(-300).toString(Qt::ISODate)+"-03:00</generationTime>\n"
            "<expirationTime>"+QDateTime::currentDateTime().addSecs(300).toString(Qt::ISODate)+"-03:00</expirationTime>\n"
          "</header>\n"
          "<service>wsfe</service>\n"
        "</loginTicketRequest>";

    //TRA.arg(QDateTime::currentDateTime().addSecs(-3600).toString(Qt::ISODate));
    //TRA.arg(QDateTime::currentDateTime().addSecs(3600*3).toString(Qt::ISODate));

    QFile TRAfile(QString("ticket.xml"));
    if (!TRAfile.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, QString("Error"), QString("no puede generarse TRA, cierre cualquier programa que pudiera estar utilizandolo"), QMessageBox::Yes);
        return QString("");
    };

    TRAfile.write(TRA.toLatin1());
    TRAfile.close();
    //qDebug() << TRA;

    QProcess openssl;
    //QMessageBox::warning(this, QString("uepa"), QString("openssl smime -sign -signer "+this->x509+" -inkey "+this->inker+" -out ticket.xml.cms -in ticket.xml -outform PEM -nodetach -passin pass:"+this->pass), QMessageBox::Yes);
    openssl.execute("openssl smime -sign -signer "+this->x509+" -inkey "+this->inker+" -out ticket.xml.cms -in ticket.xml -outform PEM -nodetach -passin pass:"+this->pass);
    appendString("openssl smime -sign -signer "+this->x509+" -inkey "+this->inker+" -out ticket.xml.cms -in ticket.xml -outform PEM -nodetach -passin pass:"+this->pass);
    qDebug() << "openssl smime -sign -signer "+this->x509+" -inkey "+this->inker+" -out ticket.xml.cms -in ticket.xml -outform PEM -nodetach -passin pass:"+this->pass;
    if(openssl.exitStatus() != QProcess::NormalExit){
        QMessageBox::warning(this, QString("Error"), QString("error al firmar el ticket con openssl"), QMessageBox::Yes);
        return QString("");
    };

    QFile TRAcms(QString("ticket.xml.cms"));
    if (!TRAcms.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, QString("Error"), QString("no puede leerse el ticket firmado, cierre cualquier programa que pudiera estar utilizandolo"), QMessageBox::Yes);
        return QString("");
    };

    QString cms;
    char buf[1024];
    qint64 lineLength = TRAcms.readLine(buf, sizeof(buf));
    while(!TRAcms.atEnd()){
        qint64 lineLength = TRAcms.readLine(buf, sizeof(buf));
        if(lineLength != -1){ //si no dio error
            QString toAdd(buf);
            if(!toAdd.contains("-----END PKCS7-----")) cms.append(toAdd);
        }
    };
    cms = cms.trimmed();
    //qDebug() << cms;
    return cms;
}

QString SslClient::makeTicket(QString firma){
    QString Ticket, cabezera;
    //"Content-Length: 3178\n"
    /*Ticket = "<soapenv:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:ser=\"http://services.authws.sua.dvadac.desein.afip.gov\">\n"
                "   <soapenv:Header/>\n"
                "   <soapenv:Body>\n"
                "      <ser:loginCms soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\n"
                "         <request xsi:type=\"xsd:string\">\n";*/
    Ticket =   "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:wsaa=\"http://wsaa.view.sua.dvadac.desein.afip.gov\">\n"
                  "<soapenv:Header/>\n"
                  "<soapenv:Body>\n"
                  "   <wsaa:loginCms>\n"
                  "    <wsaa:in0>\n";

    Ticket += firma;
    Ticket +=  "</wsaa:in0>\n"
                   "</wsaa:loginCms>\n"
                   "</soapenv:Body>\n"
                   "</soapenv:Envelope>\n";
    /*Ticket += "</request>\n"
                "      </ser:loginCms>\n"
                "   </soapenv:Body>\n"
                "</soapenv:Envelope>\n";*/

    cabezera = "POST /ws/services/LoginCms HTTP/1.1\n" //"POST https://wsaahomo.afip.gov.ar/ws/services/LoginCms HTTP/1.1\n"
                "Content-Type: text/xml;charset=UTF-8\n"
                "SOAPAction: \"\"\n"
                "User-Agent: Jakarta Commons-HttpClient/3.1\n"
                "Host: "+this->wsaa+"\n"
                "Content-Length: ";
    cabezera += QString("%1").arg(Ticket.length());
    cabezera += "\n"
                "\n";
    Ticket = cabezera + Ticket;
    //qDebug() << Ticket;
    return Ticket;
}

void SslClient::sslErrors(const QList<QSslError> &errors)
{
    qDebug() << "hubo errores de ssl";
    QSslError err;
    for(int i = 0; i < errors.length(); i++){
        qDebug() << errors.at(i);
    };
    /*QDialog errorDialog(this);
    Ui_SslErrors ui;
    ui.setupUi(&errorDialog);
    connect(ui.certificateChainButton, SIGNAL(clicked()),
            this, SLOT(displayCertificateInfo()));

    foreach (const QSslError &error, errors)
        ui.sslErrorList->addItem(error.errorString());

    executingDialog = true;
    if (errorDialog.exec() == QDialog::Accepted)
        socket->ignoreSslErrors();
    executingDialog = false;

    // did the socket state change?
    if (socket->state() != QAbstractSocket::ConnectedState)
        socketStateChanged(socket->state());*/
}

void SslClient::displayCertificateInfo()
{
    /*CertificateInfo *info = new CertificateInfo(this);
    info->setCertificateChain(socket->peerCertificateChain());
    info->exec();
    info->deleteLater();*/
}

void SslClient::connectWsfe(bool wsaa){
    if(wsaa){
        this->socket->waitForDisconnected();
        this->secureConnect();
    };
}

void SslClient::appendString(const QString &line)
{
    QTextCursor cursor(form->sessionOutput->textCursor());
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(line);
    form->sessionOutput->verticalScrollBar()->setValue(form->sessionOutput->verticalScrollBar()->maximum());
}

QString SslClient::parseFactura(QString fileLocation)
{
    QString Resp;
    QFile arch(fileLocation);
    if (!arch.open(QIODevice::ReadOnly | QIODevice::Text)){
        //QMessageBox::warning(this, QString("Error"), QString("no puede generarse TRA, cierre cualquier programa que pudiera estar utilizandolo"), QMessageBox::Yes);
        return QString("");
    };

    //QString cms;
    char buf[1024];
    qint64 lineLength = arch.readLine(buf, sizeof(buf));
    QString buffer(buf);
    Resp = "";
    Resp += "             <tipo_doc>"+buffer.mid(35, 2)+"</tipo_doc>\n";
    Resp += "             <nro_doc>"+buffer.mid(37, 11)+"</nro_doc>\n";
    Resp += "             <tipo_cbte>"+buffer.mid(9, 2)+"</tipo_cbte>\n";
    Resp += "             <punto_vta>"+buffer.mid(12, 4)+"</punto_vta>\n";
    Resp += "             <cbt_desde>"+buffer.mid(16, 8)+"</cbt_desde>\n";
    Resp += "             <cbt_hasta>"+buffer.mid(16, 8)+"</cbt_hasta>\n";
    //Resp += "             <cbt_desde>00000001</cbt_desde>\n";
    //Resp += "             <cbt_hasta>00000001</cbt_hasta>\n";
    Resp += "             <imp_total>"+buffer.mid(78, 15)+"</imp_total>\n";
    Resp += "             <imp_tot_conc>"+buffer.mid(93, 15)+"</imp_tot_conc>\n";
    Resp += "             <imp_neto>"+buffer.mid(108, 15)+"</imp_neto>\n";
    Resp += "             <impto_liq>"+buffer.mid(123, 15)+"</impto_liq>\n";
    Resp += "             <impto_liq_rni>"+buffer.mid(138, 15)+"</impto_liq_rni>\n";
    Resp += "             <imp_op_ex>"+buffer.mid(153, 15)+"</imp_op_ex>\n";
    Resp += "             <fecha_cbte>"+buffer.mid(1, 8)+"</fecha_cbte>\n";
    Resp += "             <fecha_serv_desde>"+buffer.mid(1, 8)+"</fecha_serv_desde>\n";
    Resp += "             <fecha_serv_hasta>"+buffer.mid(1, 8)+"</fecha_serv_hasta>\n";
    //Resp += "             <fecha_venc_pago>00000000</fecha_venc_pago>\n";
    //cms = cms.trimmed();
    return Resp;
}

void SslClient::justcae(){
    connect(this, SIGNAL(wsaalogon(bool)), this, SLOT(connectWsfe(bool)));
    _justcae = true;
    this->secureConnect();
}
