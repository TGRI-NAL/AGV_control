/********************************************************************************
** Form generated from reading UI file 'deliverypointeditdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELIVERYPOINTEDITDIALOG_H
#define UI_DELIVERYPOINTEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_deliveryPointEditDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QDoubleSpinBox *xDoubleSpinBox;
    QGraphicsView *xyGraphicsView;
    QLabel *label_3;
    QDoubleSpinBox *yDoubleSpinBox;
    QLabel *label;
    QDoubleSpinBox *arrivedAngleDSB;
    QLabel *label_4;
    QDoubleSpinBox *deliveryAngleDSB;
    QLabel *label_5;
    QPushButton *coordinateMapBtn;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QDoubleSpinBox *departAngleDSB;

    void setupUi(QDialog *deliveryPointEditDialog)
    {
        if (deliveryPointEditDialog->objectName().isEmpty())
            deliveryPointEditDialog->setObjectName(QStringLiteral("deliveryPointEditDialog"));
        deliveryPointEditDialog->resize(400, 283);
        deliveryPointEditDialog->setStyleSheet(QLatin1String("QDialog, QRadioButton , QLabel\n"
"{ \n"
"	background:  rgba(32, 80, 96, 100);\n"
"	color:white;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	color: white;\n"
"	background-color: #27a9e3;\n"
"	border-width: 0px;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"QPushButton:hover, QComboBox:hover{ background-color: #66c011; }"));
        gridLayout = new QGridLayout(deliveryPointEditDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        label_2 = new QLabel(deliveryPointEditDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(12);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        xDoubleSpinBox = new QDoubleSpinBox(deliveryPointEditDialog);
        xDoubleSpinBox->setObjectName(QStringLiteral("xDoubleSpinBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(xDoubleSpinBox->sizePolicy().hasHeightForWidth());
        xDoubleSpinBox->setSizePolicy(sizePolicy);
        xDoubleSpinBox->setMinimumSize(QSize(0, 30));
        xDoubleSpinBox->setFont(font);
        xDoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        xDoubleSpinBox->setMinimum(-50);
        xDoubleSpinBox->setMaximum(50);
        xDoubleSpinBox->setSingleStep(0.1);

        gridLayout->addWidget(xDoubleSpinBox, 0, 1, 1, 1);

        xyGraphicsView = new QGraphicsView(deliveryPointEditDialog);
        xyGraphicsView->setObjectName(QStringLiteral("xyGraphicsView"));

        gridLayout->addWidget(xyGraphicsView, 0, 2, 7, 1);

        label_3 = new QLabel(deliveryPointEditDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(0, 30));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        yDoubleSpinBox = new QDoubleSpinBox(deliveryPointEditDialog);
        yDoubleSpinBox->setObjectName(QStringLiteral("yDoubleSpinBox"));
        sizePolicy.setHeightForWidth(yDoubleSpinBox->sizePolicy().hasHeightForWidth());
        yDoubleSpinBox->setSizePolicy(sizePolicy);
        yDoubleSpinBox->setMinimumSize(QSize(0, 30));
        yDoubleSpinBox->setFont(font);
        yDoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        yDoubleSpinBox->setMinimum(-50);
        yDoubleSpinBox->setMaximum(50);
        yDoubleSpinBox->setSingleStep(0.1);

        gridLayout->addWidget(yDoubleSpinBox, 1, 1, 1, 1);

        label = new QLabel(deliveryPointEditDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 30));
        label->setFont(font);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        arrivedAngleDSB = new QDoubleSpinBox(deliveryPointEditDialog);
        arrivedAngleDSB->setObjectName(QStringLiteral("arrivedAngleDSB"));
        sizePolicy.setHeightForWidth(arrivedAngleDSB->sizePolicy().hasHeightForWidth());
        arrivedAngleDSB->setSizePolicy(sizePolicy);
        arrivedAngleDSB->setMinimumSize(QSize(0, 30));
        arrivedAngleDSB->setFont(font);
        arrivedAngleDSB->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        arrivedAngleDSB->setMinimum(-180);
        arrivedAngleDSB->setMaximum(180);
        arrivedAngleDSB->setSingleStep(0.1);

        gridLayout->addWidget(arrivedAngleDSB, 2, 1, 1, 1);

        label_4 = new QLabel(deliveryPointEditDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(0, 30));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        deliveryAngleDSB = new QDoubleSpinBox(deliveryPointEditDialog);
        deliveryAngleDSB->setObjectName(QStringLiteral("deliveryAngleDSB"));
        sizePolicy.setHeightForWidth(deliveryAngleDSB->sizePolicy().hasHeightForWidth());
        deliveryAngleDSB->setSizePolicy(sizePolicy);
        deliveryAngleDSB->setMinimumSize(QSize(0, 30));
        deliveryAngleDSB->setFont(font);
        deliveryAngleDSB->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        deliveryAngleDSB->setMinimum(-180);
        deliveryAngleDSB->setMaximum(180);
        deliveryAngleDSB->setSingleStep(0.1);

        gridLayout->addWidget(deliveryAngleDSB, 3, 1, 1, 1);

        label_5 = new QLabel(deliveryPointEditDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(0, 30));
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        coordinateMapBtn = new QPushButton(deliveryPointEditDialog);
        coordinateMapBtn->setObjectName(QStringLiteral("coordinateMapBtn"));
        coordinateMapBtn->setMinimumSize(QSize(0, 30));
        coordinateMapBtn->setFont(font);

        gridLayout->addWidget(coordinateMapBtn, 5, 1, 1, 1);

        okBtn = new QPushButton(deliveryPointEditDialog);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setMinimumSize(QSize(0, 30));
        okBtn->setFont(font);

        gridLayout->addWidget(okBtn, 6, 0, 1, 1);

        cancelBtn = new QPushButton(deliveryPointEditDialog);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(0, 30));
        cancelBtn->setFont(font);

        gridLayout->addWidget(cancelBtn, 6, 1, 1, 1);

        departAngleDSB = new QDoubleSpinBox(deliveryPointEditDialog);
        departAngleDSB->setObjectName(QStringLiteral("departAngleDSB"));
        sizePolicy.setHeightForWidth(departAngleDSB->sizePolicy().hasHeightForWidth());
        departAngleDSB->setSizePolicy(sizePolicy);
        departAngleDSB->setMinimumSize(QSize(0, 30));
        departAngleDSB->setFont(font);
        departAngleDSB->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        departAngleDSB->setMinimum(-180);
        departAngleDSB->setMaximum(180);
        departAngleDSB->setSingleStep(0.1);

        gridLayout->addWidget(departAngleDSB, 4, 1, 1, 1);


        retranslateUi(deliveryPointEditDialog);

        QMetaObject::connectSlotsByName(deliveryPointEditDialog);
    } // setupUi

    void retranslateUi(QDialog *deliveryPointEditDialog)
    {
        deliveryPointEditDialog->setWindowTitle(QApplication::translate("deliveryPointEditDialog", "Dialog", nullptr));
        label_2->setText(QApplication::translate("deliveryPointEditDialog", "Position X", nullptr));
        label_3->setText(QApplication::translate("deliveryPointEditDialog", "Position Y", nullptr));
        label->setText(QApplication::translate("deliveryPointEditDialog", "Arrived Angle", nullptr));
        label_4->setText(QApplication::translate("deliveryPointEditDialog", "Delivery Angle", nullptr));
        label_5->setText(QApplication::translate("deliveryPointEditDialog", "Depart Angle", nullptr));
        coordinateMapBtn->setText(QApplication::translate("deliveryPointEditDialog", "Coordinate map", nullptr));
        okBtn->setText(QApplication::translate("deliveryPointEditDialog", "Confirm", nullptr));
        cancelBtn->setText(QApplication::translate("deliveryPointEditDialog", "Cancle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class deliveryPointEditDialog: public Ui_deliveryPointEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELIVERYPOINTEDITDIALOG_H
