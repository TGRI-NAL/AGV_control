/********************************************************************************
** Form generated from reading UI file 'dbwidgt.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBWIDGT_H
#define UI_DBWIDGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DbWidgt
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *acTableView;
    QGridLayout *gridLayout;
    QPushButton *editBtn;
    QPushButton *addButton;
    QPushButton *logoutButton;
    QPushButton *deletehButton;
    QPushButton *upBtn;
    QPushButton *downBtn;

    void setupUi(QWidget *DbWidgt)
    {
        if (DbWidgt->objectName().isEmpty())
            DbWidgt->setObjectName(QStringLiteral("DbWidgt"));
        DbWidgt->resize(257, 387);
        DbWidgt->setStyleSheet(QLatin1String("QWidget\n"
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
        verticalLayout = new QVBoxLayout(DbWidgt);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        acTableView = new QTableView(DbWidgt);
        acTableView->setObjectName(QStringLiteral("acTableView"));
        acTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        acTableView->setSelectionBehavior(QAbstractItemView::SelectItems);
        acTableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(acTableView);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        editBtn = new QPushButton(DbWidgt);
        editBtn->setObjectName(QStringLiteral("editBtn"));
        editBtn->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(12);
        editBtn->setFont(font);

        gridLayout->addWidget(editBtn, 0, 4, 1, 1);

        addButton = new QPushButton(DbWidgt);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setMinimumSize(QSize(0, 30));
        addButton->setFont(font);

        gridLayout->addWidget(addButton, 0, 0, 1, 1);

        logoutButton = new QPushButton(DbWidgt);
        logoutButton->setObjectName(QStringLiteral("logoutButton"));
        logoutButton->setMinimumSize(QSize(0, 30));
        logoutButton->setFont(font);

        gridLayout->addWidget(logoutButton, 1, 4, 1, 1);

        deletehButton = new QPushButton(DbWidgt);
        deletehButton->setObjectName(QStringLiteral("deletehButton"));
        deletehButton->setMinimumSize(QSize(0, 30));
        deletehButton->setFont(font);

        gridLayout->addWidget(deletehButton, 0, 1, 1, 1);

        upBtn = new QPushButton(DbWidgt);
        upBtn->setObjectName(QStringLiteral("upBtn"));
        upBtn->setMinimumSize(QSize(0, 30));
        upBtn->setFont(font);

        gridLayout->addWidget(upBtn, 1, 0, 1, 1);

        downBtn = new QPushButton(DbWidgt);
        downBtn->setObjectName(QStringLiteral("downBtn"));
        downBtn->setMinimumSize(QSize(0, 30));
        downBtn->setFont(font);

        gridLayout->addWidget(downBtn, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(DbWidgt);

        QMetaObject::connectSlotsByName(DbWidgt);
    } // setupUi

    void retranslateUi(QWidget *DbWidgt)
    {
        DbWidgt->setWindowTitle(QApplication::translate("DbWidgt", "Form", nullptr));
        editBtn->setText(QApplication::translate("DbWidgt", "Edit", nullptr));
        addButton->setText(QApplication::translate("DbWidgt", "Add", nullptr));
        logoutButton->setText(QApplication::translate("DbWidgt", "Close", nullptr));
        deletehButton->setText(QApplication::translate("DbWidgt", "Delete", nullptr));
        upBtn->setText(QApplication::translate("DbWidgt", "Up", nullptr));
        downBtn->setText(QApplication::translate("DbWidgt", "Down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DbWidgt: public Ui_DbWidgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBWIDGT_H
