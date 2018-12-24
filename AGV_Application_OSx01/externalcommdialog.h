#ifndef EXTERNALCOMMDIALOG_H
#define EXTERNALCOMMDIALOG_H

#include <QDialog>
#include <QDebug>

enum EXTERNAL_TYPE {DELAYMS = 200, EXTERNALCOMM};

namespace Ui {
class externalCommDialog;
}

class externalCommDialog : public QDialog
{
    Q_OBJECT

public:
    explicit externalCommDialog(QWidget *parent = nullptr);
    externalCommDialog(EXTERNAL_TYPE, int, int, int, QWidget *parent = nullptr);
    ~externalCommDialog();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void on_delayRadioButton_toggled(bool checked);

    void on_externalRadioButton_toggled(bool checked);

private:
    Ui::externalCommDialog *ui;
    int order;
signals:
    void externalComm(EXTERNAL_TYPE, int, int, int);
};

#endif // EXTERNALCOMMDIALOG_H
