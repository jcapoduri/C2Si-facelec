/********************************************************************************
** Form generated from reading UI file 'sslclient.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SSLCLIENT_H
#define UI_SSLCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(370, 321);
        vboxLayout = new QVBoxLayout(Form);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        hostNameLabel = new QLabel(Form);
        hostNameLabel->setObjectName(QStringLiteral("hostNameLabel"));

        gridLayout->addWidget(hostNameLabel, 0, 0, 1, 1);

        hostNameEdit = new QLineEdit(Form);
        hostNameEdit->setObjectName(QStringLiteral("hostNameEdit"));

        gridLayout->addWidget(hostNameEdit, 0, 1, 1, 1);

        portBox = new QSpinBox(Form);
        portBox->setObjectName(QStringLiteral("portBox"));
        portBox->setMinimum(1);
        portBox->setMaximum(65535);
        portBox->setValue(443);

        gridLayout->addWidget(portBox, 1, 1, 1, 1);

        portLabel = new QLabel(Form);
        portLabel->setObjectName(QStringLiteral("portLabel"));

        gridLayout->addWidget(portLabel, 1, 0, 1, 1);


        vboxLayout->addLayout(gridLayout);

        connectButton = new QPushButton(Form);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setEnabled(true);
        connectButton->setDefault(true);

        vboxLayout->addWidget(connectButton);

        sessionBox = new QGroupBox(Form);
        sessionBox->setObjectName(QStringLiteral("sessionBox"));
        sessionBox->setEnabled(true);
        vboxLayout1 = new QVBoxLayout(sessionBox);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        cipherText = new QLabel(sessionBox);
        cipherText->setObjectName(QStringLiteral("cipherText"));

        hboxLayout->addWidget(cipherText);

        cipherLabel = new QLabel(sessionBox);
        cipherLabel->setObjectName(QStringLiteral("cipherLabel"));
        cipherLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hboxLayout->addWidget(cipherLabel);


        vboxLayout1->addLayout(hboxLayout);

        sessionOutput = new QTextEdit(sessionBox);
        sessionOutput->setObjectName(QStringLiteral("sessionOutput"));
        sessionOutput->setEnabled(true);
        sessionOutput->setFocusPolicy(Qt::NoFocus);
        sessionOutput->setReadOnly(true);

        vboxLayout1->addWidget(sessionOutput);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        pedirProxFactura = new QPushButton(sessionBox);
        pedirProxFactura->setObjectName(QStringLiteral("pedirProxFactura"));
        pedirProxFactura->setEnabled(false);

        hboxLayout1->addWidget(pedirProxFactura);

        pedirCaeButton = new QPushButton(sessionBox);
        pedirCaeButton->setObjectName(QStringLiteral("pedirCaeButton"));
        pedirCaeButton->setEnabled(false);

        hboxLayout1->addWidget(pedirCaeButton);


        vboxLayout1->addLayout(hboxLayout1);


        vboxLayout->addWidget(sessionBox);


        retranslateUi(Form);
        QObject::connect(hostNameEdit, SIGNAL(returnPressed()), connectButton, SLOT(animateClick()));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Secure Socket Client", 0));
        hostNameLabel->setText(QApplication::translate("Form", "Host:", 0));
        hostNameEdit->setText(QApplication::translate("Form", "wsaahomo.afip.gov.ar", 0));
        portLabel->setText(QApplication::translate("Form", "Puerto:", 0));
        connectButton->setText(QApplication::translate("Form", "Conectar al host", 0));
        sessionBox->setTitle(QApplication::translate("Form", "Active session", 0));
        cipherText->setText(QApplication::translate("Form", "Cryptographic Cipher:", 0));
        cipherLabel->setText(QApplication::translate("Form", "<none>", 0));
        sessionOutput->setHtml(QApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p></body></html>", 0));
        pedirProxFactura->setText(QApplication::translate("Form", "Pedir Proxima Factura", 0));
        pedirCaeButton->setText(QApplication::translate("Form", "Pedir CAE", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SSLCLIENT_H
