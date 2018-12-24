/********************************************************************************
** Form generated from reading UI file 'failedreasondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAILEDREASONDIALOG_H
#define UI_FAILEDREASONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FailedReasonDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QHBoxLayout *horizontalLayout;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *FailedReasonDialog)
    {
        if (FailedReasonDialog->objectName().isEmpty())
            FailedReasonDialog->setObjectName(QStringLiteral("FailedReasonDialog"));
        FailedReasonDialog->resize(203, 322);
        FailedReasonDialog->setStyleSheet(QLatin1String("QDialog, QRadioButton , QLabel, QCheckBox\n"
"{ \n"
"	background:  rgba(32, 80, 96, 100);\n"
"	color:white;\n"
"}\n"
"\n"
"QPushButton, QComboBox\n"
"{\n"
"	color: white;\n"
"	background-color: #27a9e3;\n"
"	border-width: 0px;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"QPushButton:hover, QComboBox:hover{ background-color: #66c011; }\n"
"QPushButton:disabled { background-color:rgb(114,200,237); }"));
        verticalLayout_2 = new QVBoxLayout(FailedReasonDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(FailedReasonDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        radioButton_1 = new QRadioButton(groupBox);
        radioButton_1->setObjectName(QStringLiteral("radioButton_1"));
        radioButton_1->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(12);
        radioButton_1->setFont(font);
        radioButton_1->setChecked(true);

        verticalLayout_3->addWidget(radioButton_1);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setMinimumSize(QSize(0, 30));
        radioButton_2->setFont(font);

        verticalLayout_3->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setMinimumSize(QSize(0, 30));
        radioButton_3->setFont(font);

        verticalLayout_3->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setMinimumSize(QSize(0, 30));
        radioButton_4->setFont(font);

        verticalLayout_3->addWidget(radioButton_4);

        radioButton_5 = new QRadioButton(groupBox);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setMinimumSize(QSize(0, 30));
        radioButton_5->setFont(font);

        verticalLayout_3->addWidget(radioButton_5);

        radioButton_6 = new QRadioButton(groupBox);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setMinimumSize(QSize(0, 30));
        radioButton_6->setFont(font);

        verticalLayout_3->addWidget(radioButton_6);

        radioButton_7 = new QRadioButton(groupBox);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setMinimumSize(QSize(0, 30));
        radioButton_7->setFont(font);

        verticalLayout_3->addWidget(radioButton_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        okBtn = new QPushButton(groupBox);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setMinimumSize(QSize(0, 30));
        okBtn->setFont(font);

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(groupBox);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(0, 30));
        cancelBtn->setFont(font);

        horizontalLayout->addWidget(cancelBtn);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(groupBox);


        retranslateUi(FailedReasonDialog);

        QMetaObject::connectSlotsByName(FailedReasonDialog);
    } // setupUi

    void retranslateUi(QDialog *FailedReasonDialog)
    {
        FailedReasonDialog->setWindowTitle(QApplication::translate("FailedReasonDialog", "Dialog", nullptr));
        groupBox->setTitle(QString());
        radioButton_1->setText(QApplication::translate("FailedReasonDialog", "\351\200\232\351\201\223\351\232\234\347\244\231\347\211\251", nullptr));
        radioButton_2->setText(QApplication::translate("FailedReasonDialog", "\346\241\214\346\244\205\347\225\260\345\213\225", nullptr));
        radioButton_3->setText(QApplication::translate("FailedReasonDialog", "\350\277\267\350\210\252", nullptr));
        radioButton_4->setText(QApplication::translate("FailedReasonDialog", "\346\211\213\350\207\202\345\213\225\344\275\234\347\225\260\345\270\270", nullptr));
        radioButton_5->setText(QApplication::translate("FailedReasonDialog", "\351\244\220\351\273\236\351\214\257\350\252\244", nullptr));
        radioButton_6->setText(QApplication::translate("FailedReasonDialog", "\345\205\266\344\273\226", nullptr));
        radioButton_7->setText(QApplication::translate("FailedReasonDialog", "\345\267\245\347\250\213\344\272\272\345\223\241\346\270\254\350\251\246\344\270\255", nullptr));
        okBtn->setText(QApplication::translate("FailedReasonDialog", "Ok", nullptr));
        cancelBtn->setText(QApplication::translate("FailedReasonDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FailedReasonDialog: public Ui_FailedReasonDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAILEDREASONDIALOG_H
