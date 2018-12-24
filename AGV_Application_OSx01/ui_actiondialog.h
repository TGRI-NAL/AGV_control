/********************************************************************************
** Form generated from reading UI file 'actiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIONDIALOG_H
#define UI_ACTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ActionDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *laserDistanceSpinBox;
    QLabel *label_4;
    QDoubleSpinBox *laserDegreeMinSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *laserDegreeMaxSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_13;
    QComboBox *globalCombinMethodCB;
    QLabel *label_12;
    QComboBox *localCombinMethodCB;
    QRadioButton *armRadioBtn;
    QLabel *label_8;
    QLabel *label_2;
    QRadioButton *audioRadioBtn;
    QRadioButton *searchTagRadioBtn;
    QRadioButton *ledRadioBtn;
    QRadioButton *delayRadioBtn;
    QLabel *label_10;
    QRadioButton *dynparamRadioBtn;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QLabel *gLabel;
    QScrollBar *glWeightScrollBar;
    QLabel *lLabel;
    QSpinBox *glSpinBox;
    QGridLayout *gridLayout;
    QPushButton *cancelBtn;
    QPushButton *add2EndBtn;
    QPushButton *add2BelowBtn;
    QSpinBox *delaySpinBox;
    QLabel *label;
    QRadioButton *imgDetcRadioButton;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *allCB;
    QCheckBox *personCB;
    QCheckBox *chairCB;
    QCheckBox *tableCB;
    QCheckBox *otherCB;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *ginflationSpinBox;
    QLabel *label_7;
    QDoubleSpinBox *linflationSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QComboBox *gFootprintCB;
    QLabel *label_14;
    QComboBox *lFootprintCB;
    QComboBox *searchTagComboBox;
    QComboBox *ledComboBox;
    QComboBox *audioComboBox;

    void setupUi(QDialog *ActionDialog)
    {
        if (ActionDialog->objectName().isEmpty())
            ActionDialog->setObjectName(QStringLiteral("ActionDialog"));
        ActionDialog->resize(612, 503);
        ActionDialog->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(12);
        ActionDialog->setFont(font);
        ActionDialog->setStyleSheet(QLatin1String("QDialog, QRadioButton , QLabel, QCheckBox\n"
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
        ActionDialog->setModal(true);
        verticalLayout_2 = new QVBoxLayout(ActionDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(ActionDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        laserDistanceSpinBox = new QDoubleSpinBox(groupBox);
        laserDistanceSpinBox->setObjectName(QStringLiteral("laserDistanceSpinBox"));
        laserDistanceSpinBox->setEnabled(false);
        laserDistanceSpinBox->setMinimumSize(QSize(0, 30));
        laserDistanceSpinBox->setFont(font);
        laserDistanceSpinBox->setMinimum(0.01);
        laserDistanceSpinBox->setMaximum(10);
        laserDistanceSpinBox->setSingleStep(0.1);
        laserDistanceSpinBox->setValue(0.3);

        horizontalLayout_4->addWidget(laserDistanceSpinBox);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(0, 30));
        label_4->setFont(font);

        horizontalLayout_4->addWidget(label_4);

        laserDegreeMinSpinBox = new QDoubleSpinBox(groupBox);
        laserDegreeMinSpinBox->setObjectName(QStringLiteral("laserDegreeMinSpinBox"));
        laserDegreeMinSpinBox->setEnabled(false);
        laserDegreeMinSpinBox->setMinimumSize(QSize(0, 30));
        laserDegreeMinSpinBox->setFont(font);
        laserDegreeMinSpinBox->setMinimum(-135);
        laserDegreeMinSpinBox->setMaximum(0);
        laserDegreeMinSpinBox->setSingleStep(5);
        laserDegreeMinSpinBox->setValue(-90);

        horizontalLayout_4->addWidget(laserDegreeMinSpinBox);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 30));
        label_3->setFont(font);

        horizontalLayout_4->addWidget(label_3);

        laserDegreeMaxSpinBox = new QDoubleSpinBox(groupBox);
        laserDegreeMaxSpinBox->setObjectName(QStringLiteral("laserDegreeMaxSpinBox"));
        laserDegreeMaxSpinBox->setEnabled(false);
        laserDegreeMaxSpinBox->setMinimumSize(QSize(0, 30));
        laserDegreeMaxSpinBox->setFont(font);
        laserDegreeMaxSpinBox->setMaximum(135);
        laserDegreeMaxSpinBox->setSingleStep(5);
        laserDegreeMaxSpinBox->setValue(90);

        horizontalLayout_4->addWidget(laserDegreeMaxSpinBox);


        gridLayout_2->addLayout(horizontalLayout_4, 7, 2, 1, 3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(0, 30));
        label_13->setFont(font);

        horizontalLayout_3->addWidget(label_13);

        globalCombinMethodCB = new QComboBox(groupBox);
        globalCombinMethodCB->addItem(QString());
        globalCombinMethodCB->addItem(QString());
        globalCombinMethodCB->setObjectName(QStringLiteral("globalCombinMethodCB"));
        globalCombinMethodCB->setEnabled(false);
        globalCombinMethodCB->setMinimumSize(QSize(0, 30));
        globalCombinMethodCB->setFont(font);

        horizontalLayout_3->addWidget(globalCombinMethodCB);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(0, 30));
        label_12->setFont(font);

        horizontalLayout_3->addWidget(label_12);

        localCombinMethodCB = new QComboBox(groupBox);
        localCombinMethodCB->addItem(QString());
        localCombinMethodCB->addItem(QString());
        localCombinMethodCB->setObjectName(QStringLiteral("localCombinMethodCB"));
        localCombinMethodCB->setEnabled(false);
        localCombinMethodCB->setMinimumSize(QSize(0, 30));
        localCombinMethodCB->setFont(font);

        horizontalLayout_3->addWidget(localCombinMethodCB);


        gridLayout_2->addLayout(horizontalLayout_3, 11, 2, 1, 3);

        armRadioBtn = new QRadioButton(groupBox);
        armRadioBtn->setObjectName(QStringLiteral("armRadioBtn"));
        armRadioBtn->setMinimumSize(QSize(0, 30));
        armRadioBtn->setFont(font);
        armRadioBtn->setChecked(false);

        gridLayout_2->addWidget(armRadioBtn, 1, 0, 1, 5);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(0, 30));
        label_8->setFont(font);

        gridLayout_2->addWidget(label_8, 9, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 30));
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 7, 1, 1, 1);

        audioRadioBtn = new QRadioButton(groupBox);
        audioRadioBtn->setObjectName(QStringLiteral("audioRadioBtn"));
        audioRadioBtn->setMinimumSize(QSize(0, 30));
        audioRadioBtn->setFont(font);

        gridLayout_2->addWidget(audioRadioBtn, 2, 0, 1, 1);

        searchTagRadioBtn = new QRadioButton(groupBox);
        searchTagRadioBtn->setObjectName(QStringLiteral("searchTagRadioBtn"));
        searchTagRadioBtn->setEnabled(false);
        searchTagRadioBtn->setMinimumSize(QSize(0, 30));
        searchTagRadioBtn->setFont(font);

        gridLayout_2->addWidget(searchTagRadioBtn, 4, 0, 1, 1);

        ledRadioBtn = new QRadioButton(groupBox);
        ledRadioBtn->setObjectName(QStringLiteral("ledRadioBtn"));
        ledRadioBtn->setMinimumSize(QSize(0, 30));
        ledRadioBtn->setFont(font);

        gridLayout_2->addWidget(ledRadioBtn, 3, 0, 1, 1);

        delayRadioBtn = new QRadioButton(groupBox);
        delayRadioBtn->setObjectName(QStringLiteral("delayRadioBtn"));
        delayRadioBtn->setMinimumSize(QSize(0, 30));
        delayRadioBtn->setFont(font);
        delayRadioBtn->setChecked(true);

        gridLayout_2->addWidget(delayRadioBtn, 0, 0, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(0, 30));
        label_10->setFont(font);

        gridLayout_2->addWidget(label_10, 10, 1, 1, 1);

        dynparamRadioBtn = new QRadioButton(groupBox);
        dynparamRadioBtn->setObjectName(QStringLiteral("dynparamRadioBtn"));
        dynparamRadioBtn->setMinimumSize(QSize(0, 30));
        dynparamRadioBtn->setFont(font);

        gridLayout_2->addWidget(dynparamRadioBtn, 7, 0, 3, 1);

        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 6, 0, 1, 5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gLabel = new QLabel(groupBox);
        gLabel->setObjectName(QStringLiteral("gLabel"));
        sizePolicy.setHeightForWidth(gLabel->sizePolicy().hasHeightForWidth());
        gLabel->setSizePolicy(sizePolicy);
        gLabel->setMinimumSize(QSize(25, 30));
        gLabel->setFont(font);
        gLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(gLabel);

        glWeightScrollBar = new QScrollBar(groupBox);
        glWeightScrollBar->setObjectName(QStringLiteral("glWeightScrollBar"));
        glWeightScrollBar->setEnabled(false);
        glWeightScrollBar->setMinimumSize(QSize(0, 30));
        glWeightScrollBar->setFont(font);
        glWeightScrollBar->setMaximum(100);
        glWeightScrollBar->setValue(50);
        glWeightScrollBar->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(glWeightScrollBar);

        lLabel = new QLabel(groupBox);
        lLabel->setObjectName(QStringLiteral("lLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lLabel->sizePolicy().hasHeightForWidth());
        lLabel->setSizePolicy(sizePolicy1);
        lLabel->setMinimumSize(QSize(25, 30));
        lLabel->setFont(font);
        lLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lLabel);

        glSpinBox = new QSpinBox(groupBox);
        glSpinBox->setObjectName(QStringLiteral("glSpinBox"));
        glSpinBox->setEnabled(false);
        glSpinBox->setMinimumSize(QSize(0, 30));
        glSpinBox->setFont(font);
        glSpinBox->setMaximum(100);
        glSpinBox->setValue(50);

        horizontalLayout->addWidget(glSpinBox);

        horizontalLayout->setStretch(1, 2);

        gridLayout_2->addLayout(horizontalLayout, 10, 2, 1, 3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cancelBtn = new QPushButton(groupBox);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(0, 40));
        cancelBtn->setFont(font);

        gridLayout->addWidget(cancelBtn, 0, 2, 1, 1);

        add2EndBtn = new QPushButton(groupBox);
        add2EndBtn->setObjectName(QStringLiteral("add2EndBtn"));
        add2EndBtn->setMinimumSize(QSize(0, 40));
        add2EndBtn->setFont(font);

        gridLayout->addWidget(add2EndBtn, 0, 0, 1, 1);

        add2BelowBtn = new QPushButton(groupBox);
        add2BelowBtn->setObjectName(QStringLiteral("add2BelowBtn"));
        add2BelowBtn->setMinimumSize(QSize(0, 40));
        add2BelowBtn->setFont(font);

        gridLayout->addWidget(add2BelowBtn, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 12, 0, 1, 5);

        delaySpinBox = new QSpinBox(groupBox);
        delaySpinBox->setObjectName(QStringLiteral("delaySpinBox"));
        delaySpinBox->setMinimumSize(QSize(0, 30));
        delaySpinBox->setFont(font);
        delaySpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        delaySpinBox->setMinimum(0);
        delaySpinBox->setMaximum(60000);
        delaySpinBox->setValue(1000);

        gridLayout_2->addWidget(delaySpinBox, 0, 1, 1, 3);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 4, 1, 1);

        imgDetcRadioButton = new QRadioButton(groupBox);
        imgDetcRadioButton->setObjectName(QStringLiteral("imgDetcRadioButton"));
        imgDetcRadioButton->setMinimumSize(QSize(0, 30));
        imgDetcRadioButton->setFont(font);

        gridLayout_2->addWidget(imgDetcRadioButton, 5, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(0, 30));
        label_6->setFont(font);

        gridLayout_2->addWidget(label_6, 8, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        allCB = new QCheckBox(groupBox);
        allCB->setObjectName(QStringLiteral("allCB"));
        allCB->setEnabled(false);
        allCB->setMinimumSize(QSize(0, 30));
        allCB->setFont(font);

        horizontalLayout_2->addWidget(allCB);

        personCB = new QCheckBox(groupBox);
        personCB->setObjectName(QStringLiteral("personCB"));
        personCB->setEnabled(false);
        personCB->setMinimumSize(QSize(0, 30));
        personCB->setFont(font);

        horizontalLayout_2->addWidget(personCB);

        chairCB = new QCheckBox(groupBox);
        chairCB->setObjectName(QStringLiteral("chairCB"));
        chairCB->setEnabled(false);
        chairCB->setMinimumSize(QSize(0, 30));
        chairCB->setFont(font);

        horizontalLayout_2->addWidget(chairCB);

        tableCB = new QCheckBox(groupBox);
        tableCB->setObjectName(QStringLiteral("tableCB"));
        tableCB->setEnabled(false);
        tableCB->setMinimumSize(QSize(0, 30));
        tableCB->setFont(font);

        horizontalLayout_2->addWidget(tableCB);

        otherCB = new QCheckBox(groupBox);
        otherCB->setObjectName(QStringLiteral("otherCB"));
        otherCB->setEnabled(false);
        otherCB->setMinimumSize(QSize(0, 30));
        otherCB->setFont(font);

        horizontalLayout_2->addWidget(otherCB);


        gridLayout_2->addLayout(horizontalLayout_2, 5, 1, 1, 4);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(0, 30));
        label_11->setFont(font);

        gridLayout_2->addWidget(label_11, 11, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(0, 30));
        label_5->setFont(font);

        horizontalLayout_5->addWidget(label_5);

        ginflationSpinBox = new QDoubleSpinBox(groupBox);
        ginflationSpinBox->setObjectName(QStringLiteral("ginflationSpinBox"));
        ginflationSpinBox->setEnabled(false);
        ginflationSpinBox->setMinimumSize(QSize(0, 30));
        ginflationSpinBox->setFont(font);
        ginflationSpinBox->setMinimum(0.01);
        ginflationSpinBox->setMaximum(1);
        ginflationSpinBox->setSingleStep(0.01);
        ginflationSpinBox->setValue(0.1);

        horizontalLayout_5->addWidget(ginflationSpinBox);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(0, 30));
        label_7->setFont(font);

        horizontalLayout_5->addWidget(label_7);

        linflationSpinBox = new QDoubleSpinBox(groupBox);
        linflationSpinBox->setObjectName(QStringLiteral("linflationSpinBox"));
        linflationSpinBox->setEnabled(false);
        linflationSpinBox->setMinimumSize(QSize(0, 30));
        linflationSpinBox->setFont(font);
        linflationSpinBox->setMinimum(0.01);
        linflationSpinBox->setMaximum(1);
        linflationSpinBox->setSingleStep(0.01);
        linflationSpinBox->setValue(0.1);

        horizontalLayout_5->addWidget(linflationSpinBox);


        gridLayout_2->addLayout(horizontalLayout_5, 8, 2, 1, 3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setMinimumSize(QSize(0, 30));
        label_9->setFont(font);

        horizontalLayout_6->addWidget(label_9);

        gFootprintCB = new QComboBox(groupBox);
        gFootprintCB->addItem(QString());
        gFootprintCB->addItem(QString());
        gFootprintCB->addItem(QString());
        gFootprintCB->setObjectName(QStringLiteral("gFootprintCB"));
        gFootprintCB->setEnabled(false);
        gFootprintCB->setMinimumSize(QSize(0, 30));
        gFootprintCB->setFont(font);

        horizontalLayout_6->addWidget(gFootprintCB);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        label_14->setMinimumSize(QSize(0, 30));
        label_14->setFont(font);

        horizontalLayout_6->addWidget(label_14);

        lFootprintCB = new QComboBox(groupBox);
        lFootprintCB->addItem(QString());
        lFootprintCB->addItem(QString());
        lFootprintCB->addItem(QString());
        lFootprintCB->setObjectName(QStringLiteral("lFootprintCB"));
        lFootprintCB->setEnabled(false);
        lFootprintCB->setMinimumSize(QSize(0, 30));
        lFootprintCB->setFont(font);

        horizontalLayout_6->addWidget(lFootprintCB);


        gridLayout_2->addLayout(horizontalLayout_6, 9, 2, 1, 3);

        searchTagComboBox = new QComboBox(groupBox);
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->addItem(QString());
        searchTagComboBox->setObjectName(QStringLiteral("searchTagComboBox"));
        searchTagComboBox->setEnabled(false);
        searchTagComboBox->setMinimumSize(QSize(0, 30));
        searchTagComboBox->setFont(font);

        gridLayout_2->addWidget(searchTagComboBox, 4, 1, 1, 4);

        ledComboBox = new QComboBox(groupBox);
        ledComboBox->addItem(QString());
        ledComboBox->addItem(QString());
        ledComboBox->addItem(QString());
        ledComboBox->addItem(QString());
        ledComboBox->addItem(QString());
        ledComboBox->addItem(QString());
        ledComboBox->setObjectName(QStringLiteral("ledComboBox"));
        ledComboBox->setMinimumSize(QSize(0, 30));
        ledComboBox->setFont(font);

        gridLayout_2->addWidget(ledComboBox, 3, 1, 1, 4);

        audioComboBox = new QComboBox(groupBox);
        audioComboBox->addItem(QString());
        audioComboBox->addItem(QString());
        audioComboBox->addItem(QString());
        audioComboBox->addItem(QString());
        audioComboBox->addItem(QString());
        audioComboBox->addItem(QString());
        audioComboBox->addItem(QString());
        audioComboBox->setObjectName(QStringLiteral("audioComboBox"));
        audioComboBox->setMinimumSize(QSize(0, 30));
        audioComboBox->setFont(font);

        gridLayout_2->addWidget(audioComboBox, 2, 1, 1, 4);

        gridLayout_2->setColumnStretch(0, 2);

        verticalLayout_2->addWidget(groupBox);


        retranslateUi(ActionDialog);

        QMetaObject::connectSlotsByName(ActionDialog);
    } // setupUi

    void retranslateUi(QDialog *ActionDialog)
    {
        ActionDialog->setWindowTitle(QApplication::translate("ActionDialog", "Action List", nullptr));
        groupBox->setTitle(QString());
        label_4->setText(QApplication::translate("ActionDialog", "m", nullptr));
        label_3->setText(QApplication::translate("ActionDialog", "~", nullptr));
        label_13->setText(QApplication::translate("ActionDialog", "Global", nullptr));
        globalCombinMethodCB->setItemText(0, QApplication::translate("ActionDialog", "Maximum", nullptr));
        globalCombinMethodCB->setItemText(1, QApplication::translate("ActionDialog", "Nothing", nullptr));

        label_12->setText(QApplication::translate("ActionDialog", "Local", nullptr));
        localCombinMethodCB->setItemText(0, QApplication::translate("ActionDialog", "Maximum", nullptr));
        localCombinMethodCB->setItemText(1, QApplication::translate("ActionDialog", "Nothing", nullptr));

        armRadioBtn->setText(QApplication::translate("ActionDialog", "Arm Action", nullptr));
        label_8->setText(QApplication::translate("ActionDialog", "Footprint", nullptr));
        label_2->setText(QApplication::translate("ActionDialog", "Laser Detection", nullptr));
        audioRadioBtn->setText(QApplication::translate("ActionDialog", "Audio", nullptr));
        searchTagRadioBtn->setText(QApplication::translate("ActionDialog", "Search Tag", nullptr));
        ledRadioBtn->setText(QApplication::translate("ActionDialog", "LED", nullptr));
        delayRadioBtn->setText(QApplication::translate("ActionDialog", "Delay", nullptr));
        label_10->setText(QApplication::translate("ActionDialog", "Global-Local Weighting ", nullptr));
        dynparamRadioBtn->setText(QApplication::translate("ActionDialog", "Dynamic\n"
"Parameter", nullptr));
        gLabel->setText(QApplication::translate("ActionDialog", "32.5", nullptr));
        lLabel->setText(QApplication::translate("ActionDialog", "32.5", nullptr));
        cancelBtn->setText(QApplication::translate("ActionDialog", "Cancle", nullptr));
        add2EndBtn->setText(QApplication::translate("ActionDialog", "Add to End", nullptr));
        add2BelowBtn->setText(QApplication::translate("ActionDialog", "Add to Below", nullptr));
#ifndef QT_NO_TOOLTIP
        delaySpinBox->setToolTip(QApplication::translate("ActionDialog", "(0~60000ms)", nullptr));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("ActionDialog", "ms", nullptr));
        imgDetcRadioButton->setText(QApplication::translate("ActionDialog", "Image Detection", nullptr));
        label_6->setText(QApplication::translate("ActionDialog", "Inflation", nullptr));
        allCB->setText(QApplication::translate("ActionDialog", "All", nullptr));
        personCB->setText(QApplication::translate("ActionDialog", "Person", nullptr));
        chairCB->setText(QApplication::translate("ActionDialog", "Chair", nullptr));
        tableCB->setText(QApplication::translate("ActionDialog", "Table", nullptr));
        otherCB->setText(QApplication::translate("ActionDialog", "Other", nullptr));
        label_11->setText(QApplication::translate("ActionDialog", "Method of combining layers", nullptr));
        label_5->setText(QApplication::translate("ActionDialog", "Global", nullptr));
        label_7->setText(QApplication::translate("ActionDialog", "Local", nullptr));
        label_9->setText(QApplication::translate("ActionDialog", "Global", nullptr));
        gFootprintCB->setItemText(0, QApplication::translate("ActionDialog", "Normal", nullptr));
        gFootprintCB->setItemText(1, QApplication::translate("ActionDialog", "Small", nullptr));
        gFootprintCB->setItemText(2, QApplication::translate("ActionDialog", "Big", nullptr));

        label_14->setText(QApplication::translate("ActionDialog", "Local", nullptr));
        lFootprintCB->setItemText(0, QApplication::translate("ActionDialog", "Normal", nullptr));
        lFootprintCB->setItemText(1, QApplication::translate("ActionDialog", "Small", nullptr));
        lFootprintCB->setItemText(2, QApplication::translate("ActionDialog", "Big", nullptr));

        searchTagComboBox->setItemText(0, QApplication::translate("ActionDialog", "0", nullptr));
        searchTagComboBox->setItemText(1, QApplication::translate("ActionDialog", "1", nullptr));
        searchTagComboBox->setItemText(2, QApplication::translate("ActionDialog", "2", nullptr));
        searchTagComboBox->setItemText(3, QApplication::translate("ActionDialog", "3", nullptr));
        searchTagComboBox->setItemText(4, QApplication::translate("ActionDialog", "4", nullptr));
        searchTagComboBox->setItemText(5, QApplication::translate("ActionDialog", "5", nullptr));
        searchTagComboBox->setItemText(6, QApplication::translate("ActionDialog", "6", nullptr));
        searchTagComboBox->setItemText(7, QApplication::translate("ActionDialog", "7", nullptr));
        searchTagComboBox->setItemText(8, QApplication::translate("ActionDialog", "8", nullptr));
        searchTagComboBox->setItemText(9, QApplication::translate("ActionDialog", "9", nullptr));
        searchTagComboBox->setItemText(10, QApplication::translate("ActionDialog", "10", nullptr));
        searchTagComboBox->setItemText(11, QApplication::translate("ActionDialog", "11", nullptr));
        searchTagComboBox->setItemText(12, QApplication::translate("ActionDialog", "12", nullptr));
        searchTagComboBox->setItemText(13, QApplication::translate("ActionDialog", "13", nullptr));
        searchTagComboBox->setItemText(14, QApplication::translate("ActionDialog", "14", nullptr));
        searchTagComboBox->setItemText(15, QApplication::translate("ActionDialog", "15", nullptr));
        searchTagComboBox->setItemText(16, QApplication::translate("ActionDialog", "16", nullptr));
        searchTagComboBox->setItemText(17, QApplication::translate("ActionDialog", "17", nullptr));

        ledComboBox->setItemText(0, QApplication::translate("ActionDialog", "Hello", nullptr));
        ledComboBox->setItemText(1, QApplication::translate("ActionDialog", "Delivery", nullptr));
        ledComboBox->setItemText(2, QApplication::translate("ActionDialog", "Please take meal", nullptr));
        ledComboBox->setItemText(3, QApplication::translate("ActionDialog", "Thanks", nullptr));
        ledComboBox->setItemText(4, QApplication::translate("ActionDialog", "Love heart (test)", nullptr));
        ledComboBox->setItemText(5, QApplication::translate("ActionDialog", "Empty (Default)", nullptr));

        audioComboBox->setItemText(0, QApplication::translate("ActionDialog", "Meals ready", nullptr));
        audioComboBox->setItemText(1, QApplication::translate("ActionDialog", "Card return", nullptr));
        audioComboBox->setItemText(2, QApplication::translate("ActionDialog", "Be careful with hot meals", nullptr));
        audioComboBox->setItemText(3, QApplication::translate("ActionDialog", "Be careful with robot", nullptr));
        audioComboBox->setItemText(4, QApplication::translate("ActionDialog", "Background music ON", nullptr));
        audioComboBox->setItemText(5, QApplication::translate("ActionDialog", "Background music OFF", nullptr));
        audioComboBox->setItemText(6, QApplication::translate("ActionDialog", "Happy Birthday", nullptr));

    } // retranslateUi

};

namespace Ui {
    class ActionDialog: public Ui_ActionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIONDIALOG_H
