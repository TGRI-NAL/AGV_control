/********************************************************************************
** Form generated from reading UI file 'editdbdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDBDIALOG_H
#define UI_EDITDBDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditDbDialog
{
public:
    QFormLayout *formLayout_2;
    QLabel *numberLabel;
    QLabel *identifierLabel;
    QLineEdit *numberLineEdit;
    QLineEdit *idLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelBtn;
    QPushButton *okBtn;

    void setupUi(QDialog *EditDbDialog)
    {
        if (EditDbDialog->objectName().isEmpty())
            EditDbDialog->setObjectName(QStringLiteral("EditDbDialog"));
        EditDbDialog->resize(205, 122);
        EditDbDialog->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"	background:  rgba(32, 80, 96, 100);\n"
"	color: white;\n"
"}\n"
"\n"
"QLabel, QCheckBox\n"
"{ \n"
"	color: white; \n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"\n"
"QPushButton, QComboBox\n"
"{\n"
"	color: white;\n"
"	background-color: #27a9e3;\n"
"	border-width: 0px;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"QPushButton:hover, QComboBox:hover, QPushButton:checked{ background-color: #66c011; }\n"
"\n"
"QTableView\n"
"{\n"
"	background:  rgba(32, 80, 96, 100);\n"
"	color: white;\n"
"}\n"
"\n"
"QHeaderView::section { color:black }"));
        formLayout_2 = new QFormLayout(EditDbDialog);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        numberLabel = new QLabel(EditDbDialog);
        numberLabel->setObjectName(QStringLiteral("numberLabel"));
        numberLabel->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(12);
        numberLabel->setFont(font);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, numberLabel);

        identifierLabel = new QLabel(EditDbDialog);
        identifierLabel->setObjectName(QStringLiteral("identifierLabel"));
        identifierLabel->setMinimumSize(QSize(0, 30));
        identifierLabel->setFont(font);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, identifierLabel);

        numberLineEdit = new QLineEdit(EditDbDialog);
        numberLineEdit->setObjectName(QStringLiteral("numberLineEdit"));
        numberLineEdit->setMinimumSize(QSize(0, 30));
        numberLineEdit->setFont(font);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, numberLineEdit);

        idLineEdit = new QLineEdit(EditDbDialog);
        idLineEdit->setObjectName(QStringLiteral("idLineEdit"));
        idLineEdit->setMinimumSize(QSize(0, 30));
        idLineEdit->setFont(font);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, idLineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cancelBtn = new QPushButton(EditDbDialog);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(0, 30));
        cancelBtn->setFont(font);

        horizontalLayout->addWidget(cancelBtn);

        okBtn = new QPushButton(EditDbDialog);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setMinimumSize(QSize(0, 30));
        okBtn->setFont(font);

        horizontalLayout->addWidget(okBtn);


        formLayout_2->setLayout(2, QFormLayout::FieldRole, horizontalLayout);


        retranslateUi(EditDbDialog);

        QMetaObject::connectSlotsByName(EditDbDialog);
    } // setupUi

    void retranslateUi(QDialog *EditDbDialog)
    {
        EditDbDialog->setWindowTitle(QApplication::translate("EditDbDialog", "Dialog", nullptr));
        numberLabel->setText(QApplication::translate("EditDbDialog", "No.", nullptr));
        identifierLabel->setText(QApplication::translate("EditDbDialog", "ID", nullptr));
        cancelBtn->setText(QApplication::translate("EditDbDialog", "Cancel", nullptr));
        okBtn->setText(QApplication::translate("EditDbDialog", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditDbDialog: public Ui_EditDbDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDBDIALOG_H
