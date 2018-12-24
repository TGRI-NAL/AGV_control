/********************************************************************************
** Form generated from reading UI file 'mapeditwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEDITWIDGET_H
#define UI_MAPEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *scrollAreaLayout;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *widthLineEdit;
    QSlider *widthSlider;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *occupancyBtn;
    QPushButton *unoccupancyBtn;
    QPushButton *unknownBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *undoBtn;
    QPushButton *redoBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *zoomOutBtn;
    QPushButton *zoomInBtn;
    QPushButton *saveBtn;

    void setupUi(QWidget *MapEditWidget)
    {
        if (MapEditWidget->objectName().isEmpty())
            MapEditWidget->setObjectName(QStringLiteral("MapEditWidget"));
        MapEditWidget->resize(800, 600);
        MapEditWidget->setStyleSheet(QLatin1String("QWidget\n"
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
"QPushButton:hover, QComboBox:hover{ background-color: #66c011; }"));
        horizontalLayout_2 = new QHBoxLayout(MapEditWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(MapEditWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 778, 540));
        scrollAreaLayout = new QHBoxLayout(scrollAreaWidgetContents);
        scrollAreaLayout->setObjectName(QStringLiteral("scrollAreaLayout"));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        widthLineEdit = new QLineEdit(MapEditWidget);
        widthLineEdit->setObjectName(QStringLiteral("widthLineEdit"));
        widthLineEdit->setBaseSize(QSize(0, 30));
        QFont font;
        widthLineEdit->setFont(font);
        widthLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        widthLineEdit->setReadOnly(true);

        horizontalLayout_9->addWidget(widthLineEdit);

        widthSlider = new QSlider(MapEditWidget);
        widthSlider->setObjectName(QStringLiteral("widthSlider"));
        widthSlider->setMinimum(1);
        widthSlider->setMaximum(10);
        widthSlider->setPageStep(1);
        widthSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(widthSlider);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        occupancyBtn = new QPushButton(MapEditWidget);
        occupancyBtn->setObjectName(QStringLiteral("occupancyBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(occupancyBtn->sizePolicy().hasHeightForWidth());
        occupancyBtn->setSizePolicy(sizePolicy);
        occupancyBtn->setMinimumSize(QSize(0, 30));
        occupancyBtn->setBaseSize(QSize(0, 30));
        occupancyBtn->setFont(font);
        occupancyBtn->setCheckable(true);

        horizontalLayout_9->addWidget(occupancyBtn);

        unoccupancyBtn = new QPushButton(MapEditWidget);
        unoccupancyBtn->setObjectName(QStringLiteral("unoccupancyBtn"));
        sizePolicy.setHeightForWidth(unoccupancyBtn->sizePolicy().hasHeightForWidth());
        unoccupancyBtn->setSizePolicy(sizePolicy);
        unoccupancyBtn->setMinimumSize(QSize(0, 30));
        unoccupancyBtn->setBaseSize(QSize(0, 30));
        unoccupancyBtn->setFont(font);
        unoccupancyBtn->setCheckable(true);

        horizontalLayout_9->addWidget(unoccupancyBtn);

        unknownBtn = new QPushButton(MapEditWidget);
        unknownBtn->setObjectName(QStringLiteral("unknownBtn"));
        sizePolicy.setHeightForWidth(unknownBtn->sizePolicy().hasHeightForWidth());
        unknownBtn->setSizePolicy(sizePolicy);
        unknownBtn->setMinimumSize(QSize(0, 30));
        unknownBtn->setBaseSize(QSize(0, 30));
        unknownBtn->setFont(font);
        unknownBtn->setCheckable(true);

        horizontalLayout_9->addWidget(unknownBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        undoBtn = new QPushButton(MapEditWidget);
        undoBtn->setObjectName(QStringLiteral("undoBtn"));
        sizePolicy.setHeightForWidth(undoBtn->sizePolicy().hasHeightForWidth());
        undoBtn->setSizePolicy(sizePolicy);
        undoBtn->setMinimumSize(QSize(0, 30));
        undoBtn->setBaseSize(QSize(0, 30));
        undoBtn->setFont(font);

        horizontalLayout_9->addWidget(undoBtn);

        redoBtn = new QPushButton(MapEditWidget);
        redoBtn->setObjectName(QStringLiteral("redoBtn"));
        sizePolicy.setHeightForWidth(redoBtn->sizePolicy().hasHeightForWidth());
        redoBtn->setSizePolicy(sizePolicy);
        redoBtn->setMinimumSize(QSize(0, 30));
        redoBtn->setBaseSize(QSize(0, 30));
        redoBtn->setFont(font);

        horizontalLayout_9->addWidget(redoBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        zoomOutBtn = new QPushButton(MapEditWidget);
        zoomOutBtn->setObjectName(QStringLiteral("zoomOutBtn"));
        sizePolicy.setHeightForWidth(zoomOutBtn->sizePolicy().hasHeightForWidth());
        zoomOutBtn->setSizePolicy(sizePolicy);
        zoomOutBtn->setMinimumSize(QSize(0, 30));
        zoomOutBtn->setBaseSize(QSize(0, 30));
        zoomOutBtn->setFont(font);

        horizontalLayout_9->addWidget(zoomOutBtn);

        zoomInBtn = new QPushButton(MapEditWidget);
        zoomInBtn->setObjectName(QStringLiteral("zoomInBtn"));
        sizePolicy.setHeightForWidth(zoomInBtn->sizePolicy().hasHeightForWidth());
        zoomInBtn->setSizePolicy(sizePolicy);
        zoomInBtn->setMinimumSize(QSize(0, 30));
        zoomInBtn->setBaseSize(QSize(0, 30));
        zoomInBtn->setFont(font);

        horizontalLayout_9->addWidget(zoomInBtn);

        saveBtn = new QPushButton(MapEditWidget);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));
        sizePolicy.setHeightForWidth(saveBtn->sizePolicy().hasHeightForWidth());
        saveBtn->setSizePolicy(sizePolicy);
        saveBtn->setMinimumSize(QSize(0, 30));
        saveBtn->setBaseSize(QSize(0, 30));
        saveBtn->setFont(font);

        horizontalLayout_9->addWidget(saveBtn);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 3);
        horizontalLayout_9->setStretch(3, 2);
        horizontalLayout_9->setStretch(4, 2);
        horizontalLayout_9->setStretch(5, 2);
        horizontalLayout_9->setStretch(7, 2);
        horizontalLayout_9->setStretch(8, 2);
        horizontalLayout_9->setStretch(10, 2);
        horizontalLayout_9->setStretch(11, 2);
        horizontalLayout_9->setStretch(12, 2);

        verticalLayout->addLayout(horizontalLayout_9);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 4);

        retranslateUi(MapEditWidget);

        QMetaObject::connectSlotsByName(MapEditWidget);
    } // setupUi

    void retranslateUi(QWidget *MapEditWidget)
    {
        MapEditWidget->setWindowTitle(QApplication::translate("MapEditWidget", "Form", nullptr));
        widthLineEdit->setText(QApplication::translate("MapEditWidget", "1", nullptr));
        occupancyBtn->setText(QApplication::translate("MapEditWidget", "Occupancy", nullptr));
        unoccupancyBtn->setText(QApplication::translate("MapEditWidget", "Unoccupancy", nullptr));
        unknownBtn->setText(QApplication::translate("MapEditWidget", "Unknown", nullptr));
        undoBtn->setText(QApplication::translate("MapEditWidget", "Undo", nullptr));
        redoBtn->setText(QApplication::translate("MapEditWidget", "Redo", nullptr));
        zoomOutBtn->setText(QApplication::translate("MapEditWidget", "Zoom Out", nullptr));
        zoomInBtn->setText(QApplication::translate("MapEditWidget", "Zoom In", nullptr));
        saveBtn->setText(QApplication::translate("MapEditWidget", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapEditWidget: public Ui_MapEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITWIDGET_H
