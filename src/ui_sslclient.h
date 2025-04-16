/********************************************************************************
** Form generated from reading UI file 'sslclient.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SSLCLIENT_H
#define UI_SSLCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *vboxLayout;
    QGridLayout *gridLayout;
    QLabel *hostNameLabel;
    QLineEdit *hostNameEdit;
    QSpinBox *portBox;
    QLabel *portLabel;
    QPushButton *connectButton;
    QGroupBox *sessionBox;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *cipherText;
    QLabel *cipherLabel;
    QTextEdit *sessionOutput;
    QHBoxLayout *hboxLayout1;
    QPushButton *pedirProxFactura;
    QPushButton *pedirCaeButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(370, 321);
        vboxLayout = new QVBoxLayout(Form);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hostNameLabel = new QLabel(Form);
        hostNameLabel->setObjectName(QString::fromUtf8("hostNameLabel"));

        gridLayout->addWidget(hostNameLabel, 0, 0, 1, 1);

        hostNameEdit = new QLineEdit(Form);
        hostNameEdit->setObjectName(QString::fromUtf8("hostNameEdit"));

        gridLayout->addWidget(hostNameEdit, 0, 1, 1, 1);

        portBox = new QSpinBox(Form);
        portBox->setObjectName(QString::fromUtf8("portBox"));
        portBox->setMinimum(1);
        portBox->setMaximum(65535);
        portBox->setValue(443);

        gridLayout->addWidget(portBox, 1, 1, 1, 1);

        portLabel = new QLabel(Form);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));

        gridLayout->addWidget(portLabel, 1, 0, 1, 1);


        vboxLayout->addLayout(gridLayout);

        connectButton = new QPushButton(Form);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setEnabled(true);

        vboxLayout->addWidget(connectButton);

        sessionBox = new QGroupBox(Form);
        sessionBox->setObjectName(QString::fromUtf8("sessionBox"));
        sessionBox->setEnabled(true);
        vboxLayout1 = new QVBoxLayout(sessionBox);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        cipherText = new QLabel(sessionBox);
        cipherText->setObjectName(QString::fromUtf8("cipherText"));

        hboxLayout->addWidget(cipherText);

        cipherLabel = new QLabel(sessionBox);
        cipherLabel->setObjectName(QString::fromUtf8("cipherLabel"));
        cipherLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hboxLayout->addWidget(cipherLabel);


        vboxLayout1->addLayout(hboxLayout);

        sessionOutput = new QTextEdit(sessionBox);
        sessionOutput->setObjectName(QString::fromUtf8("sessionOutput"));
        sessionOutput->setEnabled(true);
        sessionOutput->setFocusPolicy(Qt::NoFocus);
        sessionOutput->setReadOnly(true);

        vboxLayout1->addWidget(sessionOutput);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        pedirProxFactura = new QPushButton(sessionBox);
        pedirProxFactura->setObjectName(QString::fromUtf8("pedirProxFactura"));
        pedirProxFactura->setEnabled(false);

        hboxLayout1->addWidget(pedirProxFactura);

        pedirCaeButton = new QPushButton(sessionBox);
        pedirCaeButton->setObjectName(QString::fromUtf8("pedirCaeButton"));
        pedirCaeButton->setEnabled(false);

        hboxLayout1->addWidget(pedirCaeButton);


        vboxLayout1->addLayout(hboxLayout1);


        vboxLayout->addWidget(sessionBox);


        retranslateUi(Form);
        QObject::connect(hostNameEdit, SIGNAL(returnPressed()), connectButton, SLOT(animateClick()));

        connectButton->setDefault(true);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Secure Socket Client", nullptr));
        hostNameLabel->setText(QCoreApplication::translate("Form", "Host:", nullptr));
        hostNameEdit->setText(QCoreApplication::translate("Form", "wsaahomo.afip.gov.ar", nullptr));
        portLabel->setText(QCoreApplication::translate("Form", "Puerto:", nullptr));
        connectButton->setText(QCoreApplication::translate("Form", "Conectar al host", nullptr));
        sessionBox->setTitle(QCoreApplication::translate("Form", "Active session", nullptr));
        cipherText->setText(QCoreApplication::translate("Form", "Cryptographic Cipher:", nullptr));
        cipherLabel->setText(QCoreApplication::translate("Form", "<none>", nullptr));
        sessionOutput->setHtml(QCoreApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p></body></html>", nullptr));
        pedirProxFactura->setText(QCoreApplication::translate("Form", "Pedir Proxima Factura", nullptr));
        pedirCaeButton->setText(QCoreApplication::translate("Form", "Pedir CAE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SSLCLIENT_H
