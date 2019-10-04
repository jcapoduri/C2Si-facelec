#include "wsfemanager.h"
#include <QFile>

QString wsfeManager::wsfeUrl = "servicios1.afip.gov.ar";
QString wsfeManager::wsfeUrlTesting = "wswhomo.afip.gov.ar";
QString wsfeManager::wsfeBasePath = "/wsfev1/service.asmx?op=";
QString wsfeManager::wsfeGetCAEOpPath = "FECAESolicitar";
QString wsfeManager::wsfeGetLastAuthOpPath = "FECompUltimoAutorizado";
QString wsfeManager::wsfeGetInfoOpPath = "FEParamGetTiposCbte";
QString wsfeManager::wsfeGetRecipeInfoOpPath = "FECompConsultar";

QString wsfeManager::wsfeGetTributosOpPath = "FEParamGetTiposTributos";
QString wsfeManager::wsfeGetIvaOpPath = "FEParamGetTiposIva";

QString wsfeManager::wsfeXMLRecipeTemplate = ""
                                             "<soap:Envelope xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:ar=\"http://ar.gov.afip.dif.FEV1/\">\n"
                                             "   <soap:Header/>\n"
                                             "   <soap:Body>\n"
                                             "      <ar:FECAESolicitar>\n"
                                             "         <ar:Auth>\n"
                                             "            <ar:Token>%1</ar:Token>\n"
                                             "            <ar:Sign>%2</ar:Sign>\n"
                                             "            <ar:Cuit>%3</ar:Cuit>\n"
                                             "         </ar:Auth>\n"
                                             "         <ar:FeCAEReq>\n"
                                             "            <ar:FeCabReq>\n"
                                             "               <ar:CantReg>%4</ar:CantReg>\n"
                                             "               <ar:PtoVta>%5</ar:PtoVta>\n"
                                             "               <ar:CbteTipo>%6</ar:CbteTipo>\n"
                                             "            </ar:FeCabReq>\n"
                                             "            <ar:FeDetReq>\n"
                                             "               <ar:FECAEDetRequest>\n"
                                             "                  <ar:Concepto>%7</ar:Concepto>\n"
                                             "                  <ar:DocTipo>%8</ar:DocTipo>\n"
                                             "                  <ar:DocNro>%9</ar:DocNro>\n"
                                             "                  <ar:CbteDesde>%10</ar:CbteDesde>\n"
                                             "                  <ar:CbteHasta>%11</ar:CbteHasta>\n"
                                             "                  <ar:CbteFch>%12</ar:CbteFch>\n"
                                             "                  <ar:ImpTotal>%13</ar:ImpTotal>\n"
                                             "                  <ar:ImpTotConc>%14</ar:ImpTotConc>\n"
                                             "                  <ar:ImpNeto>%15</ar:ImpNeto>\n"
                                             "                  <ar:ImpOpEx>%16</ar:ImpOpEx>\n"
                                             "                  <ar:ImpTrib>%17</ar:ImpTrib>\n"
                                             "                  <ar:ImpIVA>%18</ar:ImpIVA>\n"
                                             "                  <ar:FchServDesde>%19</ar:FchServDesde>\n"
                                             "                  <ar:FchServHasta>%20</ar:FchServHasta>\n"
                                             "                  <ar:FchVtoPago>%21</ar:FchVtoPago>\n"
                                             "                  <ar:MonId>%22</ar:MonId>\n"
                                             "                  <ar:MonCotiz>%23</ar:MonCotiz>\n"
                                             "                  %24"
                                             "               </ar:FECAEDetRequest>\n"
                                             "            </ar:FeDetReq>\n"
                                             "         </ar:FeCAEReq>\n"
                                             "      </ar:FECAESolicitar>\n"
                                             "   </soap:Body>\n"
                                             "</soap:Envelope>";

QString wsfeManager::wsfeXMLIVATemplate = ""
                                           "<ar:Iva>"
                                           "   %1"
                                           "</ar:Iva>";

QString wsfeManager::wsfeXMLIVARecordTemplate = ""
                                                 "<ar:AlicIva>"
                                                 "<ar:Id>%1</ar:Id>"
                                                 "<ar:BaseImp>%2</ar:BaseImp>"
                                                 "<ar:Importe>%3</ar:Importe>"
                                                 "</ar:AlicIva>";
QString wsfeManager::wsfeXMLTributoTemplate = ""
                                           "<ar:Tributos>"
                                           "   %1"
                                           "</ar:Tributos>";

QString wsfeManager::wsfeXMLTributoRecordTemplate = ""
                                                 "<ar:Tributo>"
                                                 "<ar:Id>%1</ar:Id>"
                                                 "<ar:BaseImp>%2</ar:BaseImp>"
                                                 "<ar:Alic>%3</ar:Alic>"
                                                 "<ar:Importe>%4</ar:Importe>"
                                                 "</ar:Tributo>";
QString wsfeManager::wsfeXMLOptionalTemplate = ""
                                               "<ar:Opcionales>"
                                               "   %1"
                                               "</ar:Opcionales>";

QString wsfeManager::wsfeXMLOptionalRecordTemplate = ""
                                                     "<ar:Opcional>"
                                                     "<ar:Id>%1</ar:Id>"
                                                     "<ar:Valor>%2</ar:Valor>"
                                                     "</ar:Opcional>";

QString wsfeManager::wsfeXMLLastAuthRecipeTemplate = ""
                                                     "<soap:Envelope xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:ar=\"http://ar.gov.afip.dif.FEV1/\">\n"
                                                     "   <soap:Header/>\n"
                                                     "   <soap:Body>\n"
                                                     "      <ar:FECompUltimoAutorizado>\n"
                                                     "         <ar:Auth>\n"
                                                     "            <ar:Token>%1</ar:Token>\n"
                                                     "            <ar:Sign>%2</ar:Sign>\n"
                                                     "            <ar:Cuit>%3</ar:Cuit>\n"
                                                     "         </ar:Auth>\n"
                                                     "         <ar:PtoVta>%4</ar:PtoVta>\n"
                                                     "         <ar:CbteTipo>%5</ar:CbteTipo>\n"
                                                     "      </ar:FECompUltimoAutorizado>\n"
                                                     "   </soap:Body>\n"
                                                     "</soap:Envelope>";

QString wsfeManager::wsfeXMLCheckRecipeTemplate = ""
                                                     "<soap:Envelope xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:ar=\"http://ar.gov.afip.dif.FEV1/\">\n"
                                                     "   <soap:Header/>\n"
                                                     "   <soap:Body>\n"
                                                     "      <ar:FECompConsultar>\n"
                                                     "         <ar:Auth>\n"
                                                     "            <ar:Token>%1</ar:Token>\n"
                                                     "            <ar:Sign>%2</ar:Sign>\n"
                                                     "            <ar:Cuit>%3</ar:Cuit>\n"
                                                     "         </ar:Auth>\n"
                                                     "         <ar:FeCompConsReq>\n"
                                                     "           <ar:CbteTipo>%4</ar:CbteTipo>\n"
                                                     "           <ar:CbteNro>%6</ar:CbteNro>\n"
                                                     "           <ar:PtoVta>%5</ar:PtoVta>\n"
                                                     "         </ar:FeCompConsReq>\n"
                                                     "      </ar:FECompConsultar>\n"
                                                     "   </soap:Body>\n"
                                                     "</soap:Envelope>";

QString wsfeManager::wsfeXMLInfoOpTemplate = ""
                                                     "<soap:Envelope xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:ar=\"http://ar.gov.afip.dif.FEV1/\">\n"
                                                     "   <soap:Header/>\n"
                                                     "   <soap:Body>\n"
                                                     "      <ar:%1>\n"
                                                     "         <ar:Auth>\n"
                                                     "            <ar:Token>%2</ar:Token>\n"
                                                     "            <ar:Sign>%3</ar:Sign>\n"
                                                     "            <ar:Cuit>%4</ar:Cuit>\n"
                                                     "         </ar:Auth>\n"
                                                     "      </ar:%1>\n"
                                                     "   </soap:Body>\n"
                                                     "</soap:Envelope>";
QList<int> wsfeManager::fceDocuments = QList<int>({201,203,207, 211, 213});
int wsfeManager::fechaVtoPagoCustomId = 9999;


wsfeManager::wsfeManager(wsaaLogin *wsaa, bool homologacion, QObject *parent) : QObject(parent)
{
    this->wsaa = wsaa;
    socket = wsaa->socket;
    testing = homologacion;

    serviceUrl = homologacion ? wsfeManager::wsfeUrlTesting : wsfeManager::wsfeUrl;
}

wsfeManager::~wsfeManager()
{

}

bool wsfeManager::validateRecipies(QString fileLocation, QString extrasFileLocation, QString tributeFileLocation, QString optionalFileLocation) {
    QString data, extra = "";
    wsfeRecipe recipe;
    QList <wsfeRecipeTax> ivaRecords;
    QList <wsfeRecipeTrib> tributeRecords;
    QList <wsfeOptionals> optionalRecords;

    recipe = parseRecipies(fileLocation);
    ivaRecords = parseExtraRecipes(extrasFileLocation);
    tributeRecords = parseTributeRecipes(tributeFileLocation);
    if (!optionalFileLocation.isEmpty()) {
        optionalRecords = parseOptionalsRecipes(optionalFileLocation);
        wsfeOptionals opts;
        foreach (opts, optionalRecords) {
            if (opts.id == wsfeManager::fechaVtoPagoCustomId) { //special value, this means fecha vencimiento
                recipe.fechaVtoPago = opts.details;
                break;
            }
        }
    }

    data = wsfeManager::wsfeXMLRecipeTemplate;
    data = data.arg(wsaa->getToken()).arg(wsaa->getSign()).arg(wsaa->getCuit());
    data = data.arg(1).arg(recipe.pto_venta).arg(recipe.cbte_type);

    data = data.arg(recipe.concepto);
    data = data.arg(recipe.doctype);
    data = data.arg(recipe.docnumber);
    data = data.arg(recipe.compdesde);
    data = data.arg(recipe.comphasta);
    data = data.arg(recipe.compfecha);
    data = data.arg(QString::number(recipe.imp_total, 'f', 2));
    data = data.arg(QString::number(recipe.imp_totalConc, 'f', 2));
    data = data.arg(QString::number(recipe.imp_neto, 'f', 2));
    data = data.arg(QString::number(recipe.imp_opEx, 'f', 2));
    data = data.arg(QString::number(recipe.imp_trib, 'f', 2));
    data = data.arg(QString::number(recipe.imp_iva, 'f', 2));
    data = data.arg("");
    data = data.arg("");
    data = data.arg(recipe.fechaVtoPago);
    data = data.arg(recipe.mon_id);
    data = data.arg(recipe.mon_cotiz);

    if (!ivaRecords.isEmpty()) {
        wsfeRecipeTax iva;
        wsfeRecipeTrib trib;
        QString ivaData  = "";
        QString tribData = "";
        foreach (iva, ivaRecords) {
            QString buffer = wsfeManager::wsfeXMLIVARecordTemplate;
            buffer = buffer.arg(iva.id);
            buffer = buffer.arg(QString::number(iva.base_imp, 'f', 2));
            buffer = buffer.arg(QString::number(iva.imp_iva, 'f', 2));
            ivaData.append(buffer);
        }

        foreach (trib, tributeRecords) {
            QString buffer = wsfeManager::wsfeXMLTributoRecordTemplate;
            buffer = buffer.arg(iva.id);
            buffer = buffer.arg(QString::number(trib.base_imp, 'f', 2));
            buffer = buffer.arg(QString::number(trib.alicuota, 'f', 2));
            buffer = buffer.arg(QString::number(trib.import, 'f', 2));
            tribData.append(buffer);
        }

        ivaData = !ivaData.isEmpty() ? wsfeManager::wsfeXMLIVATemplate.arg(ivaData) : "";
        tribData = !tribData.isEmpty() ? wsfeManager::wsfeXMLTributoTemplate.arg(tribData) : "";
        extra = ivaData + tribData;
    }

    if (fceDocuments.toSet().contains(recipe.cbte_type) && !optionalRecords.isEmpty()) {
        wsfeOptionals opts;
        QString optionalsData = "";
        foreach (opts, optionalRecords) {
            if (opts.id == wsfeManager::fechaVtoPagoCustomId) { //special value, this means fecha vencimiento
                continue;
            }
            QString buffer = wsfeManager::wsfeXMLOptionalRecordTemplate;
            buffer = buffer.arg(opts.id);
            buffer = buffer.arg(opts.details);
            optionalsData.append(buffer);
        }

        optionalsData = !optionalsData.isEmpty() ? wsfeManager::wsfeXMLOptionalTemplate.arg(optionalsData) : "";
        extra += optionalsData;
    }

    data = data.arg(extra);

    emit serverDataSent(data);

    doRequset(wsfeManager::wsfeGetCAEOpPath, data.toLatin1());
}

bool wsfeManager::getLastAuthRecipe(int pto_venta, int comprobante_tipo)
{
    QString data;

    data = wsfeManager::wsfeXMLLastAuthRecipeTemplate;
    data = data.arg(wsaa->getToken()).arg(wsaa->getSign()).arg(wsaa->getCuit());
    data = data.arg(pto_venta).arg(comprobante_tipo);

    emit serverDataSent(data);

    doRequset(wsfeManager::wsfeGetLastAuthOpPath, data.toLatin1());
}

bool wsfeManager::getRecipeInfo(int typeRecipe, int ptovta, long nbrRecipe)
{
    QString data;

    data = wsfeManager::wsfeXMLCheckRecipeTemplate;
    data = data.arg(wsaa->getToken()).arg(wsaa->getSign()).arg(wsaa->getCuit());
    data = data.arg(typeRecipe)
               .arg(ptovta)
               .arg(nbrRecipe);

    emit serverDataSent(data);

    doRequset(wsfeManager::wsfeGetRecipeInfoOpPath, data.toLatin1());
}

bool wsfeManager::getData(QString op)
{
    QString data = wsfeManager::wsfeXMLInfoOpTemplate;

    data = data.arg(op);
    data = data.arg(wsaa->getToken()).arg(wsaa->getSign()).arg(wsaa->getCuit());

    doRequset(op, data.toLatin1());
}

void wsfeManager::dataReceived()
{
    QString data = QString::fromUtf8(socket->readAll());
    qDebug() << data;
    emit serverResponse(data);
}

wsfeRecipe wsfeManager::parseRecipies(QString fileLocation)
{
    wsfeRecipe recipe;

    QFile arch(fileLocation);
    if (!arch.open(QIODevice::ReadOnly | QIODevice::Text)){
        return recipe;
    }

    char buf[1024];
    arch.readLine(buf, sizeof(buf));
    QString buffer(buf);

    recipe.cbte_type = buffer.mid(9, 3).toInt();
    recipe.pto_venta = buffer.mid(12, 4).toInt();
    recipe.concepto = 1;
    recipe.doctype = buffer.mid(35, 2).toInt();
    recipe.docnumber = buffer.mid(37, 11).toLongLong();
    recipe.compdesde = buffer.mid(16, 8).toLong();
    recipe.comphasta = buffer.mid(24, 8).toLong();
    recipe.compfecha = buffer.mid(1, 8);
    recipe.imp_total = buffer.mid(78, 15).toDouble() / 100;
    recipe.imp_totalConc = buffer.mid(93, 15).toDouble() / 100;
    recipe.imp_neto = buffer.mid(108, 15).toDouble() / 100;
    recipe.imp_opEx = buffer.mid(153, 15).toDouble() / 100;
    recipe.imp_iva = buffer.mid(123, 15).toDouble() / 100;
    recipe.imp_no_resp = buffer.mid(138, 15).toDouble() / 100;
    recipe.percep_nac = buffer.mid(168, 15).toDouble() / 100;
    recipe.percep_prov = buffer.mid(183, 15).toDouble() / 100;
    recipe.percep_muni = buffer.mid(198, 15).toDouble() / 100;
    recipe.percep_otros = buffer.mid(213, 15).toDouble() / 100;
    recipe.imp_trib = recipe.imp_no_resp + recipe.percep_nac + recipe.percep_prov + recipe.percep_muni + recipe.percep_otros;
    recipe.mon_id = "PES";
    recipe.mon_cotiz = 1;
    /*
    imp no responsable 138, 15
    imp percep nacional 168,15
    imp percep ing brutos prov 183, 15
    imp percep municipales 198, 15
    imp otras percepciones 213, 15
    */

    return recipe;
}

QList<wsfeRecipeTax> wsfeManager::parseExtraRecipes(QString fileLocation)
{
    QList<wsfeRecipeTax> result;

    QFile arch(fileLocation);
    if (!arch.open(QIODevice::ReadOnly | QIODevice::Text)){
        return result;
    };

    while (!arch.atEnd()) {
        QByteArray buffer = arch.readLine();
        wsfeRecipeTax tax;
        tax.id = buffer.mid(43, 5).toInt();
        tax.base_imp = buffer.mid(28, 15).toDouble() / 100;
        tax.imp_iva = buffer.mid(48, 15).toDouble() / 100;
        result.append(tax);
    }

    return result;
}


QList<wsfeRecipeTrib> wsfeManager::parseTributeRecipes(QString fileLocation)
{
    QList<wsfeRecipeTrib> result;

    QFile arch(fileLocation);
    if (!arch.open(QIODevice::ReadOnly | QIODevice::Text)){
        return result;
    };

    while (!arch.atEnd()) {
        QByteArray buffer = arch.readLine();
        wsfeRecipeTrib tax;
        tax.id = buffer.mid(0, 2).toInt();
        tax.base_imp = buffer.mid(30, 15).toDouble() / 100;
        tax.alicuota = buffer.mid(45, 5).toDouble() / 100;
        tax.import = buffer.mid(50, 15).toDouble() / 100;
        qDebug() << tax.id << tax.base_imp << tax.alicuota << tax.import;
        result.append(tax);
    }

    return result;
}

QList<wsfeOptionals> wsfeManager::parseOptionalsRecipes(QString fileLocation, bool isFCE)
{
    QList<wsfeOptionals> result;

    QFile arch(fileLocation);
    if (!arch.open(QIODevice::ReadOnly | QIODevice::Text)){
        return result;
    }

    while (!arch.atEnd()) {
        QByteArray buffer = arch.readLine();
        if (buffer.isEmpty()) continue;
        wsfeOptionals optional;
        optional.id = buffer.mid(0, 4).toInt();
        optional.details = buffer.mid(4, 255).trimmed();
        qDebug() << optional.id << optional.details;
        result.append(optional);
    }

    return result;
}

void wsfeManager::doRequset(QString op, QByteArray data)
{
    QString header;

    if (socket->isOpen()) socket->close();

    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    qDebug() << serviceUrl;
    socket->connectToHostEncrypted(serviceUrl, 443);
    socket->waitForConnected(-1);

    header =
    "POST " + wsfeManager::wsfeBasePath + op + " HTTP/1.1\n"
    "Host: " + serviceUrl + "\n"
    "Content-Type: text/xml; charset=utf-8\n"
    "Content-Length: " + QString::number(data.length()) + "\n\n";

    data.prepend(header.toLatin1());
    qDebug() << data;
    socket->write(data + "\n");
}

