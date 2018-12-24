#ifndef ListDialog_H
#define ListDialog_H

#include <QDialog>
#include <QDebug>
#include <QListWidgetItem>
#include <QMessageBox>

enum LIST_TYPE{LISTMAP, LISTSCRIPT};

namespace Ui {
class listDialog;
}

class ListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListDialog(QWidget *parent = 0);
    ~ListDialog();

    void clearList();
    void setList(QStringList);

public slots:
    void setListType(LIST_TYPE listType);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_loadBtn_clicked();
    void on_cancelBtn_clicked();
    void on_listWidget_itemSelectionChanged();
    void on_deleteBtn_clicked();

signals:
    void loadMap(QString);
    void loadScript(QString);
    void deleteMap(QString);
    void deleteScript(QString);

private:
    Ui::listDialog *ui;
    LIST_TYPE m_listType;
};

#endif // ListDialog_H
