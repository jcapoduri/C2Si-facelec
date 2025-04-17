#include "wsaalogin.h"
#include <QXmlStreamWriter>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QRegularExpression>

QString wsaaLogin::wsaaUrl = "wsaa.afip.gov.ar";
QString wsaaLogin::wsaaUrlTesting = "wsaahomo.afip.gov.ar";
QString wsaaLogin::wsaaService = "/ws/services/LoginCms";
QString wsaaLogin::tokenBegin = QString("&lt;token&gt;");
QString wsaaLogin::tokenEnd = QString("&lt;/token&gt;");
QString wsaaLogin::signBegin = QString("&lt;sign&gt;");
QString wsaaLogin::signEnd = QString("&lt;/sign&gt;");
QString wsaaLogin::errorBegin = QString("<faultstring>");
QString wsaaLogin::errorEnd = QString("</faultstring>");

wsaaLogin::wsaaLogin(QSslSocket *conn, bool homologacion, QObject *parent) : QObject(parent)
{
    this->socket = conn;
    this->testing = homologacion;

    this->serviceUrl = this->testing ? wsaaLogin::wsaaUrlTesting : wsaaLogin::wsaaUrl;
}

wsaaLogin::~wsaaLogin()
{

}

void wsaaLogin::getAuth(QString source, QString x509, QString inker, QString pass)
{
    QString tra, ticket;
    if (socket->isOpen()) socket->close();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readResponse()));

    socket->connectToHostEncrypted(serviceUrl, 443);
    socket->setPeerVerifyName(serviceUrl);
    socket->waitForConnected(-1);
    qDebug() << "se conecto";
    if (source.contains("faultcode")) {
        tra = readCMS();
    } else {
        cuit = source.mid(source.indexOf("CUIT")+5, 11);
        tra = makeTRA(source, x509, inker, pass);
    };

    if (tra.isEmpty()) {
        qDebug() << "paso algo";
    };
    ticket = makeTicket(tra);

    qDebug() << ticket.toUtf8();
    socket->write(ticket.toUtf8());
}

void wsaaLogin::readResponse()
{
    QString data = QString::fromUtf8(socket->readAll());
    qDebug() << data;
    if (!data.contains("<?xml")) {
        return; //i don't care for initial headers
    }

    disconnect(socket, SIGNAL(readyRead()), this, SLOT(readResponse()));
    emit this->logMsg("response");
    emit this->logMsg(data);

    int tokenStart = data.indexOf(tokenBegin) + tokenBegin.length();
    if(tokenStart != (tokenBegin.length() - 1)){
        int tokenFinish = data.indexOf(tokenEnd) - tokenStart;
        int signStart = data.indexOf(signBegin) + signBegin.length();
        int signFinish = data.indexOf(signEnd) - signStart;

        token = data.mid(tokenStart, tokenFinish);
        sign = data.mid(signStart, signFinish);

        emit this->login(token, sign);
    }else{
        int errorStart = data.indexOf(errorBegin) + errorBegin.length();
        int errorFinish = data.indexOf(errorEnd) - errorStart;
        qDebug() << errorStart << errorFinish << data.mid(errorStart, errorFinish);
        emit logFailed(data.mid(errorStart, errorFinish));
    };
}

QString wsaaLogin::makeTRA(QString source, QString x509, QString inker, QString pass)
{
    QString TRA;
    TRA = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
        "<loginTicketRequest version=\"1.0\">\n"
          "<header>\n"
          "<source>"+source+"</source>\n"
            "<destination>CN=wsaa"+(testing ? "homo" : "")+", O=AFIP, C=AR, SERIALNUMBER=CUIT 33693450239</destination>\n"
            "<uniqueId>"+QString("%1").arg(QDateTime::currentMSecsSinceEpoch()).left(10)+"</uniqueId>\n"
            "<generationTime>"+QDateTime::currentDateTime().addSecs(-60).toString(Qt::ISODate)+"-03:00</generationTime>\n"
            "<expirationTime>"+QDateTime::currentDateTime().addSecs(60).toString(Qt::ISODate)+"-03:00</expirationTime>\n"
          "</header>\n"
          "<service>wsfe</service>\n"
        "</loginTicketRequest>";

    QFile TRAfile(QString("ticket.xml"));
    if (!TRAfile.open(QIODevice::WriteOnly | QIODevice::Text)){
        //QMessageBox::warning(this, QString("Error"), QString("no puede generarse TRA, cierre cualquier programa que pudiera estar utilizandolo"), QMessageBox::Yes);
        qDebug() << "1";
        return QString("");
    };

    TRAfile.write(TRA.toLatin1());
    TRAfile.close();

    /*QProcess openssl;
    qDebug() << "openssl smime -sign -signer " + x509 + " -inkey " + inker + " -out ticket.xml.cms -in ticket.xml -outform PEM -nodetach -passin pass:" + pass;
    openssl.execute("openssl smime -sign -signer " + x509 + " -inkey " + inker + " -in ticket.xml -outform PEM -nodetach -passin pass:" + pass);
    if(openssl.exitStatus() != QProcess::NormalExit){
        qDebug() << "2";
        return QString("");
    };

    QString out = QString::fromStdString(openssl.readAllStandardOutput().toStdString());
    qDebug() << out;*/
    QProcess openssl;

    QStringList args{
        "smime", "-sign",
        "-signer",  x509,
        "-inkey",   inker,
        "-in",      "ticket.xml",
        "-outform", "PEM",
        "-nodetach",
        "-passin",  "pass:" + pass
    };

    openssl.setProgram("openssl");
    openssl.setArguments(args);
    openssl.setProcessChannelMode(QProcess::MergedChannels);   // stdout + stderr
    openssl.start();

    if (!openssl.waitForFinished())
        qFatal("OpenSSL no terminó correctamente");

    QByteArray out = openssl.readAllStandardOutput();
    QRegularExpression re("-{5,5}(BEGIN|END) PKCS7-{5,5}\\s*");

    QString cms = QString(out).replace(re, "");
    qDebug() << cms;
    return cms.trimmed();
 }

QString wsaaLogin::readCMS() {
    QFile TRAcms(QString("ticket.xml.cms"));
    if (!TRAcms.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "3";
        return QString("");
    };

    QString cms;
    char buf[1024];
    TRAcms.readLine(buf, sizeof(buf));
    while(!TRAcms.atEnd()){
        qint64 lineLength = TRAcms.readLine(buf, sizeof(buf));
        if(lineLength != -1){ //si no dio error
            QString toAdd(buf);
            if(!toAdd.contains("-----END PKCS7-----")) cms.append(toAdd);
        }
    };
    cms = cms.trimmed();
    return cms;
}

QString wsaaLogin::makeTicket(QString cms)
{
    QString ticket, header;
    ticket =   "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:wsaa=\"http://wsaa.view.sua.dvadac.desein.afip.gov\">\r\n"
                  "<soapenv:Header/>\r\n"
                  "<soapenv:Body>\r\n"
                  "   <wsaa:loginCms>\r\n"
                  "    <wsaa:in0>";

    ticket += cms;
    ticket +=  "</wsaa:in0>\r\n"
                   "</wsaa:loginCms>\r\n"
                   "</soapenv:Body>\r\n"
                   "</soapenv:Envelope>";

    header = "POST " +  wsaaLogin::wsaaService +  " HTTP/1.1\r\n" //"POST https://wsaahomo.afip.gov.ar/ws/services/LoginCms HTTP/1.1\n"
                "Content-Type: text/xml;charset=UTF-8\r\n"
                "Accept-Encoding: gzip,deflate\r\n"
                "SOAPAction: \"\"\r\n"
                "Connection: Keep-Alive\r\n"
                "User-Agent: Apache-HttpClient/4.5.5 (Java/17.0.12)\r\n"
                "Host: " + serviceUrl + "\r\n"
                "Content-Length: ";
    QByteArray body(ticket.toUtf8());
    header += QString::number(body.length());
    header += "\r\n\r\n";
    ticket = header + ticket;
    emit this->logMsg(ticket);
    return ticket;
}

