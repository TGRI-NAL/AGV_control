/********************************************************************************
** Form generated from reading UI file 'ultrasonicdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ULTRASONICDIALOG_H
#define UI_ULTRASONICDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ultrasonicDialog
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_1;
    QSlider *horizontalSlider_1;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *spinBox_1;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelBtn;
    QPushButton *okBtn;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QSlider *horizontalSlider_4;
    QSlider *horizontalSlider_5;
    QSlider *horizontalSlider_6;

    void setupUi(QDialog *ultrasonicDialog)
    {
        if (ultrasonicDialog->objectName().isEmpty())
            ultrasonicDialog->setObjectName(QStringLiteral("ultrasonicDialog"));
        ultrasonicDialog->resize(264, 266);
        ultrasonicDialog->setStyleSheet(QLatin1String("QDialog \n"
"{ \n"
"	background:  rgba(32, 80, 96, 100);\n"
"	color:white;\n"
"	font-size: 12px;\n"
"}\n"
"\n"
"QLabel , QRadioButton\n"
"{ \n"
"	color: white; \n"
"	border-radius: 3px;\n"
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
"QPushButton:hover{ background-color: #66c011; }\n"
"\n"
"QPushButton:disabled { background-color:rgb(114,200,237); }\n"
""));
        gridLayout_2 = new QGridLayout(ultrasonicDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(ultrasonicDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(ultrasonicDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label_1 = new QLabel(ultrasonicDialog);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_1, 0, 0, 1, 1);

        horizontalSlider_1 = new QSlider(ultrasonicDialog);
        horizontalSlider_1->setObjectName(QStringLiteral("horizontalSlider_1"));
        horizontalSlider_1->setMinimumSize(QSize(0, 30));
        horizontalSlider_1->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider_1, 0, 2, 1, 1);

        label_4 = new QLabel(ultrasonicDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        label_5 = new QLabel(ultrasonicDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        label_6 = new QLabel(ultrasonicDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_6, 5, 0, 1, 1);

        spinBox_1 = new QSpinBox(ultrasonicDialog);
        spinBox_1->setObjectName(QStringLiteral("spinBox_1"));
        spinBox_1->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(spinBox_1, 0, 1, 1, 1);

        spinBox_2 = new QSpinBox(ultrasonicDialog);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(spinBox_2, 1, 1, 1, 1);

        spinBox_3 = new QSpinBox(ultrasonicDialog);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(spinBox_3, 2, 1, 1, 1);

        spinBox_4 = new QSpinBox(ultrasonicDialog);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(spinBox_4, 3, 1, 1, 1);

        spinBox_5 = new QSpinBox(ultrasonicDialog);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(spinBox_5, 4, 1, 1, 1);

        spinBox_6 = new QSpinBox(ultrasonicDialog);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(spinBox_6, 5, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cancelBtn = new QPushButton(ultrasonicDialog);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(cancelBtn);

        okBtn = new QPushButton(ultrasonicDialog);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(okBtn);


        gridLayout_2->addLayout(horizontalLayout, 6, 0, 1, 3);

        horizontalSlider_2 = new QSlider(ultrasonicDialog);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setMinimumSize(QSize(0, 30));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider_2, 1, 2, 1, 1);

        horizontalSlider_3 = new QSlider(ultrasonicDialog);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setMinimumSize(QSize(0, 30));
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider_3, 2, 2, 1, 1);

        horizontalSlider_4 = new QSlider(ultrasonicDialog);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setMinimumSize(QSize(0, 30));
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider_4, 3, 2, 1, 1);

        horizontalSlider_5 = new QSlider(ultrasonicDialog);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setMinimumSize(QSize(0, 30));
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider_5, 4, 2, 1, 1);

        horizontalSlider_6 = new QSlider(ultrasonicDialog);
        horizontalSlider_6->setObjectName(QStringLiteral("horizontalSlider_6"));
        horizontalSlider_6->setMinimumSize(QSize(0, 30));
        horizontalSlider_6->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider_6, 5, 2, 1, 1);


        retranslateUi(ultrasonicDialog);

        QMetaObject::connectSlotsByName(ultrasonicDialog);
    } // setupUi

    void retranslateUi(QDialog *ultrasonicDialog)
    {
        ultrasonicDialog->setWindowTitle(QApplication::translate("ultrasonicDialog", "Ultrasonic", nullptr));
        label_3->setText(QApplication::translate("ultrasonicDialog", "No. 3", nullptr));
        label_2->setText(QApplication::translate("ultrasonicDialog", "No. 2", nullptr));
        label_1->setText(QApplication::translate("ultrasonicDialog", "No. 1", nullptr));
        label_4->setText(QApplication::translate("ultrasonicDialog", "No. 4", nullptr));
        label_5->setText(QApplication::translate("ultrasonicDialog", "No. 5", nullptr));
        label_6->setText(QApplication::translate("ultrasonicDialog", "No. 6", nullptr));
        cancelBtn->setText(QApplication::translate("ultrasonicDialog", "Cancel", nullptr));
        okBtn->setText(QApplication::translate("ultrasonicDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ultrasonicDialog: public Ui_ultrasonicDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ULTRASONICDIALOG_H
