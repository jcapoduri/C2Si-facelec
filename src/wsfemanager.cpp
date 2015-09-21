#include "wsfemanager.h"
#include <QFile>

QString wsfeManager::wsfeUrl = "servicios1.afip.gov.ar";
QString wsfeManager::wsfeUrlTesting = "wswhomo.afip.gov.ar";
QString wsfeManager::wsfeBasePath = "/wsfev1/service.asmx?op=";
QString wsfeManager::wsfeGetCAEOpPath = "FECAESolicitar";
QString wsfeManager::wsfeGetLastAuthOpPath = "FECompUltimoAutorizado";
QString wsfeManager::wsfeGetInfoOpPath = "FEParamGetTiposTributos";

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

/*bool wsfeManager::validateRecipies(QString cuit, QString fileLocation)
{
    if (socket->isOpen()) socket->close();

    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    qDebug() << serviceUrl;
    socket->connectToHostEncrypted(serviceUrl, 443);
    socket->waitForConnected(-1);
    QString data;
    wsfeRecipe recipe;

    data = ""
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<soap:Envelope xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:ar=\"http://ar.gov.afip.dif.FEV1/\">\n"
    "  <soap:Header/>\n"
    "  <soap:Body>\n"
    "    <ar:FEParamGetTiposTributos>\n"
    "      <ar:Auth>\n"
    "        <ar:Token>" + wsaa->getToken() + "</ar:Token>\n"
    "        <ar:Sign>" + wsaa->getSign() + "</ar:Sign>\n"
    "        <ar:Cuit>" + cuit + "</ar:Cuit>\n"
    "      </ar:Auth>\n";
    data += ""
    "    </ar:FEParamGetTiposTributos>\n"
    "  </soap:Body>\n"
    "</soap:Envelope>";

    data =
    "POST " + wsfeManager::wsfeGetInfoOpPath + " HTTP/1.1\n"
    "Host: "+serviceUrl+"\n"
    "Content-Type: text/xml;charset=UTF-8\n"
    "User-Agent: Jakarta Commons-HttpClient/3.1\n"
    "Content-Length: "+QString("%1").arg(data.length())+"\n\n" + data;

    qDebug() << data;
    socket->write(data.toUtf8() + "\n");


    return false;*/
bool wsfeManager::validateRecipies(QString cuit, QString fileLocation) {
    QString data;
    wsfeRecipe recipe;

    recipe = parseRecipies(fileLocation);

    data = wsfeManager::wsfeXMLRecipeTemplate;
    data = data.arg(wsaa->getToken()).arg(wsaa->getSign()).arg(cuit);
    data = data.arg(1).arg(recipe.pto_venta).arg(recipe.cbte_type);

    data = data.arg(recipe.concepto);
    data = data.arg(recipe.doctype);
    data = data.arg(recipe.docnumber);
    data = data.arg(recipe.compdesde);
    data = data.arg(recipe.comphasta);
    data = data.arg(recipe.compfecha);
    data = data.arg(recipe.imp_total);
    data = data.arg(recipe.imp_totalConc);
    data = data.arg(recipe.imp_neto);
    data = data.arg(recipe.imp_opEx);
    data = data.arg(recipe.imp_trib);
    data = data.arg(recipe.imp_iva);
    data = data.arg("");
    data = data.arg("");
    data = data.arg("");
    data = data.arg(recipe.mon_id);
    data = data.arg(recipe.mon_cotiz);

    doRequset(wsfeManager::wsfeGetCAEOpPath, data.toLatin1());
}

bool wsfeManager::getLastAuthRecipe(QString cuit, QString fileLocation)
{
    QString data;
    wsfeRecipe recipe;

    recipe = parseRecipies(fileLocation);

    data = wsfeManager::wsfeXMLLastAuthRecipeTemplate;
    data = data.arg(wsaa->getToken()).arg(wsaa->getSign()).arg(cuit);
    data = data.arg(recipe.pto_venta).arg(recipe.cbte_type);

    doRequset(wsfeManager::wsfeGetLastAuthOpPath, data.toLatin1());
}

bool wsfeManager::getData(QString op, QString cuit)
{
    QString data = wsfeManager::wsfeXMLInfoOpTemplate;

    data = data.arg(op);
    data = data.arg(wsaa->getToken()).arg(wsaa->getSign()).arg(cuit);

    doRequset(op, data.toLatin1());
}

void wsfeManager::dataReceived()
{
    QString data = QString::fromUtf8(socket->readAll());
    qDebug() << data;
}

wsfeRecipe wsfeManager::parseRecipies(QString fileLocation)
{
    wsfeRecipe recipe;

    QFile arch(fileLocation);
    if (!arch.open(QIODevice::ReadOnly | QIODevice::Text)){
        return recipe;
    };

    char buf[1024];
    arch.readLine(buf, sizeof(buf));
    QString buffer(buf);

    recipe.cbte_type = buffer.mid(9, 2).toInt();
    recipe.pto_venta = buffer.mid(12, 4).toInt();
    recipe.concepto = 1;
    recipe.doctype = buffer.mid(35, 2).toInt();
    recipe.docnumber = buffer.mid(37, 11).toLong();
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
    recipe.percep_otros = buffer.mid(313, 15).toDouble() / 100;
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

