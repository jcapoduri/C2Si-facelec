/********************************************************************************
** Form generated from reading UI file 'wsfeform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WSFEFORM_H
#define UI_WSFEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wsfeForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *hostNameEdit;
    QPushButton *connectButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *operationComboBox;
    QComboBox *operationHelperComboBox;
    QPushButton *doButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QFormLayout *formLayout;
    QLabel *puntoVentaLabel;
    QSpinBox *puntoVentaSpinBox;
    QLabel *tipoComprobanteLabel;
    QSpinBox *tipoComprobanteSpinBox;
    QLabel *nroComprobanteLabel;
    QSpinBox *nroComprobanteSpinBox;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QTextBrowser *sessionOutput;

    void setupUi(QWidget *wsfeForm)
    {
        if (wsfeForm->objectName().isEmpty())
            wsfeForm->setObjectName(QString::fromUtf8("wsfeForm"));
        wsfeForm->resize(753, 446);
        verticalLayout_2 = new QVBoxLayout(wsfeForm);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(wsfeForm);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        hostNameEdit = new QLineEdit(wsfeForm);
        hostNameEdit->setObjectName(QString::fromUtf8("hostNameEdit"));

        horizontalLayout_2->addWidget(hostNameEdit);

        connectButton = new QPushButton(wsfeForm);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        horizontalLayout_2->addWidget(connectButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(wsfeForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        operationComboBox = new QComboBox(wsfeForm);
        operationComboBox->addItem(QString());
        operationComboBox->addItem(QString());
        operationComboBox->addItem(QString());
        operationComboBox->addItem(QString());
        operationComboBox->setObjectName(QString::fromUtf8("operationComboBox"));
        operationComboBox->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(operationComboBox->sizePolicy().hasHeightForWidth());
        operationComboBox->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(operationComboBox);

        operationHelperComboBox = new QComboBox(wsfeForm);
        operationHelperComboBox->addItem(QString());
        operationHelperComboBox->addItem(QString());
        operationHelperComboBox->addItem(QString());
        operationHelperComboBox->addItem(QString());
        operationHelperComboBox->addItem(QString());
        operationHelperComboBox->addItem(QString());
        operationHelperComboBox->addItem(QString());
        operationHelperComboBox->addItem(QString());
        operationHelperComboBox->addItem(QString());
        operationHelperComboBox->addItem(QString());
        operationHelperComboBox->setObjectName(QString::fromUtf8("operationHelperComboBox"));

        horizontalLayout_3->addWidget(operationHelperComboBox);

        doButton = new QPushButton(wsfeForm);
        doButton->setObjectName(QString::fromUtf8("doButton"));
        doButton->setEnabled(false);

        horizontalLayout_3->addWidget(doButton);


        verticalLayout_2->addLayout(horizontalLayout_3);

        groupBox = new QGroupBox(wsfeForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(true);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        puntoVentaLabel = new QLabel(groupBox);
        puntoVentaLabel->setObjectName(QString::fromUtf8("puntoVentaLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, puntoVentaLabel);

        puntoVentaSpinBox = new QSpinBox(groupBox);
        puntoVentaSpinBox->setObjectName(QString::fromUtf8("puntoVentaSpinBox"));
        puntoVentaSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        puntoVentaSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

        formLayout->setWidget(0, QFormLayout::FieldRole, puntoVentaSpinBox);

        tipoComprobanteLabel = new QLabel(groupBox);
        tipoComprobanteLabel->setObjectName(QString::fromUtf8("tipoComprobanteLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, tipoComprobanteLabel);

        tipoComprobanteSpinBox = new QSpinBox(groupBox);
        tipoComprobanteSpinBox->setObjectName(QString::fromUtf8("tipoComprobanteSpinBox"));
        tipoComprobanteSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tipoComprobanteSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        tipoComprobanteSpinBox->setMaximum(99999999);

        formLayout->setWidget(1, QFormLayout::FieldRole, tipoComprobanteSpinBox);

        nroComprobanteLabel = new QLabel(groupBox);
        nroComprobanteLabel->setObjectName(QString::fromUtf8("nroComprobanteLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, nroComprobanteLabel);

        nroComprobanteSpinBox = new QSpinBox(groupBox);
        nroComprobanteSpinBox->setObjectName(QString::fromUtf8("nroComprobanteSpinBox"));
        nroComprobanteSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        nroComprobanteSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        nroComprobanteSpinBox->setMaximum(999999);

        formLayout->setWidget(2, QFormLayout::FieldRole, nroComprobanteSpinBox);


        horizontalLayout_4->addLayout(formLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(groupBox);

        sessionOutput = new QTextBrowser(wsfeForm);
        sessionOutput->setObjectName(QString::fromUtf8("sessionOutput"));

        verticalLayout_2->addWidget(sessionOutput);


        retranslateUi(wsfeForm);

        QMetaObject::connectSlotsByName(wsfeForm);
    } // setupUi

    void retranslateUi(QWidget *wsfeForm)
    {
        wsfeForm->setWindowTitle(QCoreApplication::translate("wsfeForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("wsfeForm", "Url a conectar:", nullptr));
        connectButton->setText(QCoreApplication::translate("wsfeForm", "Conectar", nullptr));
        label_2->setText(QCoreApplication::translate("wsfeForm", "Operaci\303\263n:", nullptr));
        operationComboBox->setItemText(0, QCoreApplication::translate("wsfeForm", "Obtener CAE p/Comprobante", nullptr));
        operationComboBox->setItemText(1, QCoreApplication::translate("wsfeForm", "Obtener Info de Comprobante", nullptr));
        operationComboBox->setItemText(2, QCoreApplication::translate("wsfeForm", "Obtener Ult. Comprobante", nullptr));
        operationComboBox->setItemText(3, QCoreApplication::translate("wsfeForm", "Informacion", nullptr));

        operationHelperComboBox->setItemText(0, QCoreApplication::translate("wsfeForm", "FEParamGetTiposCbte", nullptr));
        operationHelperComboBox->setItemText(1, QCoreApplication::translate("wsfeForm", "FEParamGetTiposConcepto", nullptr));
        operationHelperComboBox->setItemText(2, QCoreApplication::translate("wsfeForm", "FEParamGetTiposDoc", nullptr));
        operationHelperComboBox->setItemText(3, QCoreApplication::translate("wsfeForm", "FEParamGetTiposIva", nullptr));
        operationHelperComboBox->setItemText(4, QCoreApplication::translate("wsfeForm", "FEParamGetTiposMonedas", nullptr));
        operationHelperComboBox->setItemText(5, QCoreApplication::translate("wsfeForm", "FEParamGetTiposOpcional", nullptr));
        operationHelperComboBox->setItemText(6, QCoreApplication::translate("wsfeForm", "FEParamGetTiposTributos", nullptr));
        operationHelperComboBox->setItemText(7, QCoreApplication::translate("wsfeForm", "FEParamGetPtosVenta", nullptr));
        operationHelperComboBox->setItemText(8, QCoreApplication::translate("wsfeForm", "FEParamGetCotizacion", nullptr));
        operationHelperComboBox->setItemText(9, QCoreApplication::translate("wsfeForm", "FEDummy", nullptr));

        doButton->setText(QCoreApplication::translate("wsfeForm", "Ejecutar Operaci\303\263n", nullptr));
        groupBox->setTitle(QCoreApplication::translate("wsfeForm", "Operaciones", nullptr));
        puntoVentaLabel->setText(QCoreApplication::translate("wsfeForm", "Punto Venta:", nullptr));
        tipoComprobanteLabel->setText(QCoreApplication::translate("wsfeForm", "Tipo Comprobante:", nullptr));
        nroComprobanteLabel->setText(QCoreApplication::translate("wsfeForm", "Nro. Comprobante:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wsfeForm: public Ui_wsfeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WSFEFORM_H
