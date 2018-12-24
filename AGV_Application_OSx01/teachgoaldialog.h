#ifndef TEACHGOALDIALOG_H
#define TEACHGOALDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QQuaternion>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QtMath>

enum VEL_TYPE {Forward, Backward, Right, Left, Stop};
enum TELEOP_TYPE {JOG, LINEAR};

namespace Ui {
class TeachGoalDialog;
}

class TeachGoalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeachGoalDialog(int value, TELEOP_TYPE type, bool, QWidget *parent = 0);
    ~TeachGoalDialog();
    void setTabFocusOrder();
    void setJoystickLevel(int);

private slots:
    void on_cancelBtn_clicked();
    void on_verticalSlider_valueChanged(int value);
    void on_forwardBtn_pressed();
    void on_backwardBtn_pressed();
    void on_leftBtn_pressed();
    void on_rightBtn_pressed();
    void on_forwardBtn_released();
    void on_backwardBtn_released();
    void on_leftBtn_released();
    void on_rightBtn_released();
    void on_goOriginBtn_clicked();
    void on_poseUpdateBtn_clicked();
    void on_jogRadioBtn_toggled(bool checked);
    void on_stopBtn_clicked();
    void on_abortBtn_clicked();
    void on_erCheckBox_stateChanged(int arg1);
    void on_add2BelowBtn_clicked();
    void on_add2EndBtn_clicked();

public slots:
    void updateAmclPoseValue(QPointF, QQuaternion);

private:
    Ui::TeachGoalDialog *ui;
    QPointF m_pos;
    QQuaternion m_quat;
    TELEOP_TYPE teleopMode;

signals:
    void updateVel(VEL_TYPE);
    void updateVelPercentage(int);
    void addTeachGoal(QPointF, QQuaternion, bool);
    void goOrigin();
    void poseUpdate();
    void abortMovebase();
    void setTeleopMode(TELEOP_TYPE);
    void setKeyPriorityFlag(bool);
};

#endif // TEACHGOALDIALOG_H
