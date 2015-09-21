#ifndef WSFEMANAGER_H
#define WSFEMANAGER_H

#include <QObject>
#include <QSslSocket>
#include "wsaalogin.h"

struct wsfeRecipe {
    int  pto_venta = 0;
    int  cbte_type = 0;
    int  concepto = 0;
    int  doctype = 0;
    long docnumber = 0;
    long compdesde = 0;
    long comphasta = 0;
    QString compfecha = "";
    double imp_total = 0;
    double imp_totalConc = 0;
    double imp_neto = 0;
    double imp_opEx = 0;
    double imp_trib = 0;
    double imp_iva = 0;
    QString fechaServDesde = "";
    QString fechaServHasta = "";
    QString fechaVtoPago = "";
    QString mon_id = "";
    double mon_cotiz = 0;
    double imp_no_resp;
    double percep_nac;
    double percep_prov;
    double percep_muni;
    double percep_otros;
};

class wsfeManager : public QObject
{
    Q_OBJECT
public:
    static QString wsfeUrl;
    static QString wsfeUrlTesting;
    static QString wsfeGetCAEOpPath;
    static QString wsfeGetInfoOpPath;
    static QString wsfeXMLRecipeTemplate;
    static QString wsfeGetLastAuthOpPath;
    static QString wsfeXMLLastAuthRecipeTemplate;
    static QString wsfeBasePath;
    static QString wsfeGetTributosOpPath;
    static QString wsfeXMLInfoOpTemplate;
    static QString wsfeGetIvaOpPath;

    explicit wsfeManager(wsaaLogin *wsaa, bool homologacion = false, QObject *parent = 0);
    ~wsfeManager();

    bool    validateRecipies(QString cuit, QString fileLocation);
    bool    getLastAuthRecipe(QString cuit, QString fileLocation);
    bool    getData(QString op, QString cuit);
    QString getServiceUrl() { return serviceUrl; }

signals:

public slots:
    void    dataReceived();

protected:
    wsfeRecipe    parseRecipies(QString fileLocation);
    void          doRequset(QString op, QByteArray data);

    QSslSocket *socket;
    wsaaLogin  *wsaa;
    QString    serviceUrl;
    bool       testing;
};

#endif // WSFEMANAGER_H
