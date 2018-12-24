#include "ListDialog.h"
#include "ui_listdialog.h"

ListDialog::ListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listDialog)
{
    ui->setupUi(this);
    ui->loadBtn->setEnabled(false);
    ui->deleteBtn->setEnabled(false);
}

ListDialog::~ListDialog()
{
    delete ui;
}

void ListDialog::clearList()
{
    ui->listWidget->clear();
    ui->loadBtn->setEnabled(false);
}

void ListDialog::setList(QStringList strList)
{
    for(int i=0; i<strList.count(); i++){
        QString nameStr = strList.at(i);
        ui->listWidget->addItem(nameStr.split(".").first());
    }
}

void ListDialog::setListType(LIST_TYPE listType)
{
    m_listType = listType;
    if(m_listType == LIST_TYPE::LISTMAP)
        this->setWindowTitle("Map List");
    else if(m_listType == LIST_TYPE::LISTSCRIPT)
        this->setWindowTitle("Script List");
}

void ListDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(ui->listWidget->currentRow() == -1)
        return;
    if(m_listType == LIST_TYPE::LISTMAP)
        emit loadMap(ui->listWidget->currentItem()->text());
    else if(m_listType == LIST_TYPE::LISTSCRIPT)
        emit loadScript(ui->listWidget->currentItem()->text());
    this->close();
}

void ListDialog::on_loadBtn_clicked()
{
    if(ui->listWidget->currentRow() == -1)
        return;
    if(m_listType == LIST_TYPE::LISTMAP)
        emit loadMap(ui->listWidget->currentItem()->text());
    else if(m_listType == LIST_TYPE::LISTSCRIPT)
        emit loadScript(ui->listWidget->currentItem()->text());
    this->close();
}

void ListDialog::on_cancelBtn_clicked()
{
    this->close();
}

void ListDialog::on_listWidget_itemSelectionChanged()
{
    if(ui->listWidget->currentRow() != -1){
        ui->loadBtn->setEnabled(true);
        ui->deleteBtn->setEnabled(true);
    }
    else{
        ui->loadBtn->setEnabled(false);
        ui->deleteBtn->setEnabled(false);
    }
}

void ListDialog::on_deleteBtn_clicked()
{
    if(ui->listWidget->currentRow() == -1)
        return;

    QMessageBox *mb = new QMessageBox;
    mb->setIcon(QMessageBox::Question);
    mb->setText("Warning");
    mb->setInformativeText("The delete action is unrecoverable, are you sure to execute it?");
    mb->setStandardButtons(QMessageBox::Apply|QMessageBox::Cancel);
    mb->setDefaultButton(QMessageBox::Cancel);
    int ret = mb->exec();
    mb->deleteLater();
    switch(ret){
    case QMessageBox::Apply:
        if(m_listType == LIST_TYPE::LISTMAP)
            emit deleteMap(ui->listWidget->currentItem()->text());
        else if(m_listType == LIST_TYPE::LISTSCRIPT)
            emit deleteScript(ui->listWidget->currentItem()->text());
        delete ui->listWidget->takeItem(ui->listWidget->row(ui->listWidget->currentItem()));
        ui->listWidget->setCurrentRow(-1);
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
}
