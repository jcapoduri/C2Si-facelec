/********************************************************************************
** Form generated from reading UI file 'wsfeform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WSFEFORM_H
#define UI_WSFEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            wsfeForm->setObjectName(QStringLiteral("wsfeForm"));
        wsfeForm->resize(753, 446);
        verticalLayout_2 = new QVBoxLayout(wsfeForm);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(wsfeForm);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        hostNameEdit = new QLineEdit(wsfeForm);
        hostNameEdit->setObjectName(QStringLiteral("hostNameEdit"));

        horizontalLayout_2->addWidget(hostNameEdit);

        connectButton = new QPushButton(wsfeForm);
        connectButton->setObjectName(QStringLiteral("connectButton"));

        horizontalLayout_2->addWidget(connectButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(wsfeForm);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        operationComboBox = new QComboBox(wsfeForm);
        operationComboBox->setObjectName(QStringLiteral("operationComboBox"));
        operationComboBox->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(operationComboBox->sizePolicy().hasHeightForWidth());
        operationComboBox->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(operationComboBox);

        operationHelperComboBox = new QComboBox(wsfeForm);
        operationHelperComboBox->setObjectName(QStringLiteral("operationHelperComboBox"));

        horizontalLayout_3->addWidget(operationHelperComboBox);

        doButton = new QPushButton(wsfeForm);
        doButton->setObjectName(QStringLiteral("doButton"));
        doButton->setEnabled(false);

        horizontalLayout_3->addWidget(doButton);


        verticalLayout_2->addLayout(horizontalLayout_3);

        groupBox = new QGroupBox(wsfeForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(true);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        puntoVentaLabel = new QLabel(groupBox);
        puntoVentaLabel->setObjectName(QStringLiteral("puntoVentaLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, puntoVentaLabel);

        puntoVentaSpinBox = new QSpinBox(groupBox);
        puntoVentaSpinBox->setObjectName(QStringLiteral("puntoVentaSpinBox"));
        puntoVentaSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        puntoVentaSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

        formLayout->setWidget(0, QFormLayout::FieldRole, puntoVentaSpinBox);

        tipoComprobanteLabel = new QLabel(groupBox);
        tipoComprobanteLabel->setObjectName(QStringLiteral("tipoComprobanteLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, tipoComprobanteLabel);

        tipoComprobanteSpinBox = new QSpinBox(groupBox);
        tipoComprobanteSpinBox->setObjectName(QStringLiteral("tipoComprobanteSpinBox"));
        tipoComprobanteSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tipoComprobanteSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        tipoComprobanteSpinBox->setMaximum(99999999);

        formLayout->setWidget(1, QFormLayout::FieldRole, tipoComprobanteSpinBox);

        nroComprobanteLabel = new QLabel(groupBox);
        nroComprobanteLabel->setObjectName(QStringLiteral("nroComprobanteLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, nroComprobanteLabel);

        nroComprobanteSpinBox = new QSpinBox(groupBox);
        nroComprobanteSpinBox->setObjectName(QStringLiteral("nroComprobanteSpinBox"));
        nroComprobanteSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        nroComprobanteSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        nroComprobanteSpinBox->setMaximum(999999);

        formLayout->setWidget(2, QFormLayout::FieldRole, nroComprobanteSpinBox);


        horizontalLayout_4->addLayout(formLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(groupBox);

        sessionOutput = new QTextBrowser(wsfeForm);
        sessionOutput->setObjectName(QStringLiteral("sessionOutput"));

        verticalLayout_2->addWidget(sessionOutput);


        retranslateUi(wsfeForm);

        QMetaObject::connectSlotsByName(wsfeForm);
    } // setupUi

    void retranslateUi(QWidget *wsfeForm)
    {
        wsfeForm->setWindowTitle(QApplication::translate("wsfeForm", "Form", 0));
        label->setText(QApplication::translate("wsfeForm", "Url a conectar:", 0));
        connectButton->setText(QApplication::translate("wsfeForm", "Conectar", 0));
        label_2->setText(QApplication::translate("wsfeForm", "Operaci\303\263n:", 0));
        operationComboBox->clear();
        operationComboBox->insertItems(0, QStringList()
         << QApplication::translate("wsfeForm", "Obtener CAE p/Comprobante", 0)
         << QApplication::translate("wsfeForm", "Obtener Info de Comprobante", 0)
         << QApplication::translate("wsfeForm", "Obtener Ult. Comprobante", 0)
         << QApplication::translate("wsfeForm", "Informacion", 0)
        );
        operationHelperComboBox->clear();
        operationHelperComboBox->insertItems(0, QStringList()
         << QApplication::translate("wsfeForm", "FEParamGetTiposCbte", 0)
         << QApplication::translate("wsfeForm", "FEParamGetTiposConcepto", 0)
         << QApplication::translate("wsfeForm", "FEParamGetTiposDoc", 0)
         << QApplication::translate("wsfeForm", "FEParamGetTiposIva", 0)
         << QApplication::translate("wsfeForm", "FEParamGetTiposMonedas", 0)
         << QApplication::translate("wsfeForm", "FEParamGetTiposOpcional", 0)
         << QApplication::translate("wsfeForm", "FEParamGetTiposTributos", 0)
         << QApplication::translate("wsfeForm", "FEParamGetPtosVenta", 0)
         << QApplication::translate("wsfeForm", "FEParamGetCotizacion", 0)
         << QApplication::translate("wsfeForm", "FEDummy", 0)
        );
        doButton->setText(QApplication::translate("wsfeForm", "Ejecutar Operaci\303\263n", 0));
        groupBox->setTitle(QApplication::translate("wsfeForm", "Operaciones", 0));
        puntoVentaLabel->setText(QApplication::translate("wsfeForm", "Punto Venta:", 0));
        tipoComprobanteLabel->setText(QApplication::translate("wsfeForm", "Tipo Comprobante:", 0));
        nroComprobanteLabel->setText(QApplication::translate("wsfeForm", "Nro. Comprobante:", 0));
    } // retranslateUi

};

namespace Ui {
    class wsfeForm: public Ui_wsfeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WSFEFORM_H
