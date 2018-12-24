/********************************************************************************
** Form generated from reading UI file 'joystickdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOYSTICKDIALOG_H
#define UI_JOYSTICKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_JoystickDialog
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *leftBtn;
    QPushButton *backwardBtn;
    QPushButton *forwardBtn;
    QPushButton *rightBtn;
    QPushButton *stopBtn;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *modeGb;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *linearRb;
    QRadioButton *jogRb;
    QCheckBox *emergencyStopCb;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *goOriginBtn;
    QPushButton *abortBtn;
    QPushButton *closeBtn;

    void setupUi(QDialog *JoystickDialog)
    {
        if (JoystickDialog->objectName().isEmpty())
            JoystickDialog->setObjectName(QStringLiteral("JoystickDialog"));
        JoystickDialog->resize(837, 429);
        JoystickDialog->setStyleSheet(QLatin1String("QDialog \n"
"{ \n"
"	background:  rgba(32, 80, 96, 100);\n"
"	/*background:  rgba(255, 0, 0, 255);*/\n"
"	color:white;\n"
"	font-size: 12px;\n"
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
"QLabel , QRadioButton, QCheckBox\n"
"{ \n"
"	color: white; \n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"QPushButton:hover, QComboBox:hover{ background-color: #66c011; }\n"
""));
        gridLayout_2 = new QGridLayout(JoystickDialog);
        gridLayout_2->setSpacing(20);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        leftBtn = new QPushButton(JoystickDialog);
        leftBtn->setObjectName(QStringLiteral("leftBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftBtn->sizePolicy().hasHeightForWidth());
        leftBtn->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(50);
        leftBtn->setFont(font);

        gridLayout_2->addWidget(leftBtn, 1, 0, 1, 1);

        backwardBtn = new QPushButton(JoystickDialog);
        backwardBtn->setObjectName(QStringLiteral("backwardBtn"));
        sizePolicy.setHeightForWidth(backwardBtn->sizePolicy().hasHeightForWidth());
        backwardBtn->setSizePolicy(sizePolicy);
        backwardBtn->setFont(font);

        gridLayout_2->addWidget(backwardBtn, 2, 1, 1, 1);

        forwardBtn = new QPushButton(JoystickDialog);
        forwardBtn->setObjectName(QStringLiteral("forwardBtn"));
        sizePolicy.setHeightForWidth(forwardBtn->sizePolicy().hasHeightForWidth());
        forwardBtn->setSizePolicy(sizePolicy);
        forwardBtn->setFont(font);

        gridLayout_2->addWidget(forwardBtn, 0, 1, 1, 1);

        rightBtn = new QPushButton(JoystickDialog);
        rightBtn->setObjectName(QStringLiteral("rightBtn"));
        sizePolicy.setHeightForWidth(rightBtn->sizePolicy().hasHeightForWidth());
        rightBtn->setSizePolicy(sizePolicy);
        rightBtn->setFont(font);

        gridLayout_2->addWidget(rightBtn, 1, 2, 1, 1);

        stopBtn = new QPushButton(JoystickDialog);
        stopBtn->setObjectName(QStringLiteral("stopBtn"));
        sizePolicy.setHeightForWidth(stopBtn->sizePolicy().hasHeightForWidth());
        stopBtn->setSizePolicy(sizePolicy);
        stopBtn->setFont(font);

        gridLayout_2->addWidget(stopBtn, 1, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        modeGb = new QGroupBox(JoystickDialog);
        modeGb->setObjectName(QStringLiteral("modeGb"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(modeGb->sizePolicy().hasHeightForWidth());
        modeGb->setSizePolicy(sizePolicy1);
        modeGb->setMinimumSize(QSize(0, 40));
        horizontalLayout_2 = new QHBoxLayout(modeGb);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        linearRb = new QRadioButton(modeGb);
        linearRb->setObjectName(QStringLiteral("linearRb"));
        QFont font1;
        font1.setPointSize(20);
        linearRb->setFont(font1);

        horizontalLayout_2->addWidget(linearRb);

        jogRb = new QRadioButton(modeGb);
        jogRb->setObjectName(QStringLiteral("jogRb"));
        jogRb->setFont(font1);

        horizontalLayout_2->addWidget(jogRb);


        horizontalLayout_4->addWidget(modeGb);

        emergencyStopCb = new QCheckBox(JoystickDialog);
        emergencyStopCb->setObjectName(QStringLiteral("emergencyStopCb"));
        sizePolicy.setHeightForWidth(emergencyStopCb->sizePolicy().hasHeightForWidth());
        emergencyStopCb->setSizePolicy(sizePolicy);
        emergencyStopCb->setFont(font1);
        emergencyStopCb->setChecked(true);

        horizontalLayout_4->addWidget(emergencyStopCb);


        gridLayout_2->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(JoystickDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        pushButton->setFont(font1);

        horizontalLayout->addWidget(pushButton);

        goOriginBtn = new QPushButton(JoystickDialog);
        goOriginBtn->setObjectName(QStringLiteral("goOriginBtn"));
        sizePolicy.setHeightForWidth(goOriginBtn->sizePolicy().hasHeightForWidth());
        goOriginBtn->setSizePolicy(sizePolicy);
        goOriginBtn->setFont(font1);

        horizontalLayout->addWidget(goOriginBtn);

        abortBtn = new QPushButton(JoystickDialog);
        abortBtn->setObjectName(QStringLiteral("abortBtn"));
        sizePolicy.setHeightForWidth(abortBtn->sizePolicy().hasHeightForWidth());
        abortBtn->setSizePolicy(sizePolicy);
        abortBtn->setFont(font1);

        horizontalLayout->addWidget(abortBtn);

        closeBtn = new QPushButton(JoystickDialog);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        sizePolicy.setHeightForWidth(closeBtn->sizePolicy().hasHeightForWidth());
        closeBtn->setSizePolicy(sizePolicy);
        closeBtn->setFont(font1);

        horizontalLayout->addWidget(closeBtn);


        gridLayout_2->addLayout(horizontalLayout, 3, 1, 1, 2);

        gridLayout_2->setRowStretch(0, 2);
        gridLayout_2->setRowStretch(1, 2);
        gridLayout_2->setRowStretch(2, 2);
        gridLayout_2->setRowStretch(3, 1);

        retranslateUi(JoystickDialog);

        QMetaObject::connectSlotsByName(JoystickDialog);
    } // setupUi

    void retranslateUi(QDialog *JoystickDialog)
    {
        JoystickDialog->setWindowTitle(QApplication::translate("JoystickDialog", "\346\220\226\346\241\277\346\250\241\345\274\217", nullptr));
        leftBtn->setText(QApplication::translate("JoystickDialog", "\345\267\246\350\275\211", nullptr));
        backwardBtn->setText(QApplication::translate("JoystickDialog", "\345\276\214\351\200\200", nullptr));
        forwardBtn->setText(QApplication::translate("JoystickDialog", "\345\211\215\351\200\262", nullptr));
        rightBtn->setText(QApplication::translate("JoystickDialog", "\345\217\263\350\275\211", nullptr));
        stopBtn->setText(QApplication::translate("JoystickDialog", "\345\201\234\346\255\242", nullptr));
        modeGb->setTitle(QString());
        linearRb->setText(QApplication::translate("JoystickDialog", "\347\267\232\346\200\247", nullptr));
        jogRb->setText(QApplication::translate("JoystickDialog", "\345\257\270\345\213\225", nullptr));
        emergencyStopCb->setText(QApplication::translate("JoystickDialog", "\351\201\277\345\201\234\351\226\213\351\227\234", nullptr));
        pushButton->setText(QApplication::translate("JoystickDialog", "\350\250\255\345\256\232\345\216\237\351\273\236", nullptr));
        goOriginBtn->setText(QApplication::translate("JoystickDialog", "\345\233\236\350\265\267\345\247\213\351\273\236", nullptr));
        abortBtn->setText(QApplication::translate("JoystickDialog", "\347\265\202\346\255\242\344\275\234\346\245\255", nullptr));
        closeBtn->setText(QApplication::translate("JoystickDialog", "\351\227\234\351\226\211\350\246\226\347\252\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JoystickDialog: public Ui_JoystickDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOYSTICKDIALOG_H
