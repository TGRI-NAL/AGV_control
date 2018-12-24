#ifndef GOALEDITDIALOG_H
#define GOALEDITDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QQuaternion>
#include <QtMath>
#include <QGraphicsPixmapItem>

namespace Ui {
class goalEditDialog;
}

class goalEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit goalEditDialog(int, QPointF, QQuaternion, float, float, float, QString, QWidget *parent = 0);
    void setMapInfo(float, float, float, float, float);
    ~goalEditDialog();

signals:
    void updateGoalValue(int order, QPointF pos, float thetaValue, float disTolerance, float angleTolerance, float reachTolerance, QString remark);
    void cloneGoal(int, QPointF pos, float thetaValue, float disTolerance, float angleTolerance, float reachTolerance, QString remark);

private slots:
    void on_okBtn_clicked();
    void on_cancelBtn_clicked();
    void on_coordinateMapBtn_clicked();
    void on_cloneEndBtn_clicked();
    void on_cloneBelowBtn_clicked();

private:
    Ui::goalEditDialog *ui;
    int goalOrder;
    QString goalRemark;
};

#endif // GOALEDITDIALOG_H
