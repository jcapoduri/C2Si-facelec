#ifndef WSAALOGIN_H
#define WSAALOGIN_H

#include <QObject>
#include <QSslSocket>

class wsaaLogin : public QObject
{
    Q_OBJECT
public:
    static QString wsaaUrl;
    static QString wsaaUrlTesting;
    static QString wsaaService;

    explicit wsaaLogin(QSslSocket *conn, bool homologacion = false, QObject *parent = 0);
    ~wsaaLogin();

    bool     isAuthenticated() { return isAuthOk; }
    QString  getToken() { return token; }
    QString  getSign() { return sign; }
    QString  getCuit() { return cuit; }
    QString  getServiceUrl() { return serviceUrl; }

    void    getAuth(QString source, QString x509, QString inker, QString pass);

    QSslSocket *socket;

signals:
    void    login(QString token, QString sign);
    void    logFailed();
protected slots:
    void    readResponse();

protected:
    static QString tokenBegin;
    static QString tokenEnd;
    static QString signBegin;
    static QString signEnd;

    QString makeTRA(QString source, QString x509, QString inker, QString pass);
    QString makeTicket(QString cms);
    bool    getAuthentification();

    QString    token;
    QString    sign;
    QString    cuit;
    QString    serviceUrl;
    bool       testing;

    bool    isAuthOk = false;


};

#endif // WSAALOGIN_H
