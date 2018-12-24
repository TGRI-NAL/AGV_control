/********************************************************************************
** Form generated from reading UI file 'dynparamdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DYNPARAMDIALOG_H
#define UI_DYNPARAMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_dynparamDialog
{
public:
    QGridLayout *dynparamGridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *closeBtn;
    QPushButton *writeBtn;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;

    void setupUi(QDialog *dynparamDialog)
    {
        if (dynparamDialog->objectName().isEmpty())
            dynparamDialog->setObjectName(QStringLiteral("dynparamDialog"));
        dynparamDialog->resize(360, 240);
        dynparamDialog->setStyleSheet(QLatin1String("QDialog\n"
"{ \n"
"	background:  rgba(32, 80, 96, 100);\n"
"	color:white;\n"
"	font-size: 12px;\n"
"}\n"
"\n"
"QLabel \n"
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
"QPushButton:hover, QComboBox:hover, QPushButton:checked{ background-color: #66c011; }\n"
"\n"
""));
        dynparamGridLayout = new QGridLayout(dynparamDialog);
        dynparamGridLayout->setObjectName(QStringLiteral("dynparamGridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        closeBtn = new QPushButton(dynparamDialog);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(closeBtn);

        writeBtn = new QPushButton(dynparamDialog);
        writeBtn->setObjectName(QStringLiteral("writeBtn"));
        writeBtn->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(writeBtn);


        dynparamGridLayout->addLayout(horizontalLayout, 2, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        dynparamGridLayout->addItem(verticalSpacer, 1, 1, 1, 2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        dynparamGridLayout->addLayout(gridLayout, 0, 1, 1, 2);


        retranslateUi(dynparamDialog);

        QMetaObject::connectSlotsByName(dynparamDialog);
    } // setupUi

    void retranslateUi(QDialog *dynparamDialog)
    {
        dynparamDialog->setWindowTitle(QApplication::translate("dynparamDialog", "Dynamic Parameter Configuration", nullptr));
        closeBtn->setText(QApplication::translate("dynparamDialog", "Close", nullptr));
        writeBtn->setText(QApplication::translate("dynparamDialog", "Write", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dynparamDialog: public Ui_dynparamDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DYNPARAMDIALOG_H
