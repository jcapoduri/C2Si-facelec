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
    qlonglong docnumber = 0;
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

struct wsfeRecipeTax  {
    int    id = 7;
    double base_imp = 0.0;
    double imp_iva = 0.0;
};

struct wsfeRecipeTrib  {
    int    id = 1;
    double base_imp = 0.0;
    double alicuota = 0.0;
    double import = 0.0;
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
    static QString wsfeXMLCheckRecipeTemplate;
    static QString wsfeGetRecipeInfoOpPath;
    static QString wsfeXMLIVATemplate;
    static QString wsfeXMLIVARecordTemplate;
    static QString wsfeXMLTributoTemplate;
    static QString wsfeXMLTributoRecordTemplate;

    explicit wsfeManager(wsaaLogin *wsaa, bool homologacion = false, QObject *parent = 0);
    ~wsfeManager();

    bool    validateRecipies(QString fileLocation, QString extrasFileLocation, QString tributeFileLocation);
    bool    getLastAuthRecipe(int pto_venta, int comprobante_tipo);
    bool    getRecipeInfo(int typeRecipe, int ptovta, long nbrRecipe);
    bool    getData(QString op);
    QString getServiceUrl() { return serviceUrl; }

signals:
    void    serverResponse(QString response);
    void    serverDataSent(QString data);
public slots:
    void    dataReceived();

protected:
    wsfeRecipe    parseRecipies(QString fileLocation);
    QList<wsfeRecipeTax> parseExtraRecipes(QString fileLocation);
    QList<wsfeRecipeTrib> parseTributeRecipes(QString fileLocation);
    void          doRequset(QString op, QByteArray data);

    QSslSocket *socket;
    wsaaLogin  *wsaa;
    QString    serviceUrl;
    bool       testing;
};

#endif // WSFEMANAGER_H
