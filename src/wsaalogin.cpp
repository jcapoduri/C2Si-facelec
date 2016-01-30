#include "wsaalogin.h"
#include <QXmlStreamWriter>
#include <QFile>
#include <QProcess>
#include <QDebug>

QString wsaaLogin::wsaaUrl = "wsaa.afip.gov.ar";
QString wsaaLogin::wsaaUrlTesting = "wsaahomo.afip.gov.ar";
QString wsaaLogin::wsaaService = "/ws/services/LoginCms";
QString wsaaLogin::tokenBegin = QString("&lt;token&gt;");
QString wsaaLogin::tokenEnd = QString("&lt;/token&gt;");
QString wsaaLogin::signBegin = QString("&lt;sign&gt;");
QString wsaaLogin::signEnd = QString("&lt;/sign&gt;");

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
    socket->waitForConnected(-1);

    cuit = source.mid(source.indexOf("CUIT")+5, 11);

    tra = makeTRA(source, x509, inker, pass);
    if (tra.isEmpty()) return;
    ticket = makeTicket(tra);
    //qDebug() << ticket.toUtf8();
    socket->write(ticket.toUtf8() + "\n");
}

void wsaaLogin::readResponse()
{
    QString data = QString::fromUtf8(socket->readAll());
    qDebug() << data;

    int tokenStart = data.indexOf(tokenBegin) + tokenBegin.length();
    if(tokenStart != (tokenBegin.length() - 1)){
        int tokenFinish = data.indexOf(tokenEnd) - tokenStart;
        int signStart = data.indexOf(signBegin) + signBegin.length();
        int signFinish = data.indexOf(signEnd) - signStart;

        token = data.mid(tokenStart, tokenFinish);
        sign = data.mid(signStart, signFinish);

        emit this->login(token, sign);
        disconnect(socket, SIGNAL(readyRead()), this, SLOT(readResponse()));
    }else{
        emit this->logFailed();
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
        return QString("");
    };

    TRAfile.write(TRA.toLatin1());
    TRAfile.close();

    QProcess openssl;
    openssl.execute("openssl smime -sign -signer " + x509 + " -inkey " + inker + " -out ticket.xml.cms -in ticket.xml -outform PEM -nodetach -passin pass:" + pass);
    if(openssl.exitStatus() != QProcess::NormalExit){
        return QString("");
    };

    QFile TRAcms(QString("ticket.xml.cms"));
    if (!TRAcms.open(QIODevice::ReadOnly | QIODevice::Text)){
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
    ticket =   "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:wsaa=\"http://wsaa.view.sua.dvadac.desein.afip.gov\">\n"
                  "<soapenv:Header/>\n"
                  "<soapenv:Body>\n"
                  "   <wsaa:loginCms>\n"
                  "    <wsaa:in0>\n";

    ticket += cms;
    ticket +=  "</wsaa:in0>\n"
                   "</wsaa:loginCms>\n"
                   "</soapenv:Body>\n"
                   "</soapenv:Envelope>\n";

    header = "POST " + wsaaLogin::wsaaService +  " HTTP/1.1\n" //"POST https://wsaahomo.afip.gov.ar/ws/services/LoginCms HTTP/1.1\n"
                "Content-Type: text/xml;charset=UTF-8\n"
                "SOAPAction: \"\"\n"
                "User-Agent: Jakarta Commons-HttpClient/3.1\n"
                "Host: " + serviceUrl + "\n"
                "Content-Length: ";
    header += QString::number(ticket.length());
    header += "\n\n";
    ticket = header + ticket;
    return ticket;
}

