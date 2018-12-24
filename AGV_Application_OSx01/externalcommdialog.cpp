#include "externalcommdialog.h"
#include "ui_externalcommdialog.h"

externalCommDialog::externalCommDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::externalCommDialog)
{
    ui->setupUi(this);
    ui->addressSpinBox->setPrefix("0x");
    ui->addressSpinBox->setDisplayIntegerBase(16);
    ui->addressSpinBox->setRange(0, 0xFFFF);

    ui->valueSpinBox->setPrefix("0x");
    ui->valueSpinBox->setDisplayIntegerBase(16);
    ui->valueSpinBox->setRange(0, 0xFFFF);
    ui->delaySpinBox->setSuffix("ms");
    order = -1;
}

externalCommDialog::externalCommDialog(EXTERNAL_TYPE type, int orderValue, int address, int value, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::externalCommDialog)
{
    ui->setupUi(this);
    ui->addressSpinBox->setPrefix("0x");
    ui->addressSpinBox->setDisplayIntegerBase(16);
    ui->addressSpinBox->setRange(0, 0xFFFF);

    ui->valueSpinBox->setPrefix("0x");
    ui->valueSpinBox->setDisplayIntegerBase(16);
    ui->valueSpinBox->setRange(0, 0xFFFF);
    ui->delaySpinBox->setSuffix("ms");
    order = orderValue;
    if(type == EXTERNAL_TYPE::DELAYMS){
        ui->delayRadioButton->setChecked(true);
        ui->delaySpinBox->setValue(value);
    }
    else if (type == EXTERNAL_TYPE::EXTERNALCOMM) {
        ui->externalRadioButton->setChecked(true);
        ui->addressSpinBox->setValue(address);
        ui->valueSpinBox->setValue(value);
    }
}

externalCommDialog::~externalCommDialog()
{
    delete ui;
}

void externalCommDialog::on_okBtn_clicked()
{
    if(ui->delayRadioButton->isChecked()){
        emit externalComm(EXTERNAL_TYPE::DELAYMS, order, 0, ui->delaySpinBox->value());
    }
    else if(ui->externalRadioButton->isChecked()){
        emit externalComm(EXTERNAL_TYPE::EXTERNALCOMM, order, ui->addressSpinBox->value(), ui->valueSpinBox->value());
    }
    this->close();
}

void externalCommDialog::on_cancelBtn_clicked()
{
    this->close();
}

void externalCommDialog::on_delayRadioButton_toggled(bool checked)
{
    ui->delaySpinBox->setEnabled(checked);
}

void externalCommDialog::on_externalRadioButton_toggled(bool checked)
{
    ui->addressSpinBox->setEnabled(checked);
    ui->valueSpinBox->setEnabled(checked);
}
