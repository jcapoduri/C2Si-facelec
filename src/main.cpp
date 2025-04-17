#include <QApplication>
#include <QSettings>

#include "client.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[])
{
    QString source;
    QString wsaa ;
    QString wsfe;
    QString certConexion, pedido, inker, pass;
    QString x509, help = "";
    bool justcae;
    bool testing;


    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setValue("Version", 0.1);
    settings.beginGroup("global");
    certConexion = settings.value("cert", "").toString();
    testing = settings.value("testing").toBool();
    if (testing){
        wsaa = "wsaahomo.afip.gov.ar";
        wsfe = "wswhomo.afip.gov.ar";
    }else{
        wsaa = settings.value("wsaa", QString("wsaa.afip.gov.ar")).toString();
        wsfe = settings.value("wsfe", QString("servicios1.afip.gov.ar")).toString();
    };
    source = settings.value("source", "").toString();
    x509 = settings.value("x509", "").toString();
    pedido = settings.value("pedido", "").toString();
    pass = settings.value("pass", "").toString();
    inker = settings.value("inker", "").toString();
    justcae = settings.value("justcae", false).toBool();
    settings.endGroup();

    for(int i = 0; i < argc; i++){
        QString tmp(argv[i]);
        if(tmp.contains("source")) source = tmp.mid(tmp.indexOf("=") + 1);
        if(tmp.contains("testing")){
            wsaa = "wsaahomo.afip.gov.ar";
            wsfe = "wswhomo.afip.gov.ar";
            testing = true;
        };
        if(tmp.contains("cert")) certConexion = tmp.mid(tmp.indexOf("=") + 1);
        if(tmp.contains("x509")) x509 = tmp.mid(tmp.indexOf("=") + 1);
        if(tmp.contains("pedido")) pedido = tmp.mid(tmp.indexOf("=") + 1);
        if(tmp.contains("pass")) pass = tmp.mid(tmp.indexOf("=") + 1);
        if(tmp.contains("inker")) inker = tmp.mid(tmp.indexOf("=") + 1);
        if(tmp.contains("justcae")) justcae = true;
        if(tmp.contains("help")) help ="Pedido de facturacion electronica, puede usarse interfaz grafica o por linea de comando\n"
                                                "\n"
                                                "Argumentos:\n"
                                                 "      -cert=<nombre_archivo>: certificado de coneccion ssl\n"
                                                 "      -x509=<nombre_archivo>: certificado x509 dado por el afip para conectarse con la empresa\n"
                                                 "      -testing: si se usa esta opcion se usara los sitios de testing de la afip env ez del entorno de produccion\n"
                                                 "      -source=<\"string\">: string que contiene los datos de la empresa, dichos datos deben ser los que fueron entregados para hacer el csr para pedir el x509v3\n"
                                                 "      -pedido=<nombre_archivo>: nombre del archivo con la factura a autorizar, el formato es el mismo que el usado para importar archivos en el rece\n"
                                                 "      -inker=<nombre_archivo>: archivo que contiene la clave primada con la que se firmo el certificado csr al enviarlo a la afip\n"
                                                 "      -pass=<\"string\">: clave de la firma digital\n"
                                                 "      -port=<entero>: numero de puerto de conexion, si no se especifica, se toma por defecto 443\n"
                                                 "      -ptoventa=<entero>: punto de venta de la factura, de no especificarse se tomara el valor 1\n"
                                                 "      -justcae: no muestra interfaz grafica, pide cae automaticamente con los parametros pasado\n"
                                                 "      -prestaserv: indica si el pedido es pedido de servicio\n";

    };

    if(!help.isEmpty()){                 //si se pidio la ayudo la muestro y salgo
         QByteArray ayuda(help.toLatin1());
         char *data = ayuda.data();
         puts (data);
         return 0;
    };

    QApplication a(argc, argv);
    a.setOrganizationName("C2SI");
    a.setApplicationName("feClient");
    client widget("config.ini", justcae);
    if (!justcae) widget.show();
    return a.exec();
}
