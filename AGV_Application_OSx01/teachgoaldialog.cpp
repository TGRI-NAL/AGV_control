#include "teachgoaldialog.h"
#include "ui_teachgoaldialog.h"

TeachGoalDialog::TeachGoalDialog(int value, TELEOP_TYPE type, bool isActionSelected, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeachGoalDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->verticalSlider->setValue(value);
    setTabFocusOrder();
    ui->add2EndBtn->setFocus();
    teleopMode = type;
    if(teleopMode == TELEOP_TYPE::JOG)
        ui->jogRadioBtn->setChecked(true);
    else if(teleopMode == TELEOP_TYPE::LINEAR)
        ui->linearRadioBtn->setChecked(true);

    ui->erCheckBox->setChecked(true);

    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap(":/xy_description.png"));
    double ratio = (double) (140.0-10)/pixmapItem->pixmap().height();
    pixmapItem->setScale(ratio);

    if(isActionSelected)
        ui->add2BelowBtn->setEnabled(true);
    else
        ui->add2BelowBtn->setEnabled(false);
}

TeachGoalDialog::~TeachGoalDialog()
{
    emit setTeleopMode(teleopMode);
    emit setKeyPriorityFlag(true);
    delete ui;
}

void TeachGoalDialog::setTabFocusOrder()
{
    setTabOrder(ui->add2EndBtn, ui->cancelBtn);
    setTabOrder(ui->cancelBtn, ui->forwardBtn);
    setTabOrder(ui->forwardBtn, ui->backwardBtn);
    setTabOrder(ui->backwardBtn, ui->leftBtn);
    setTabOrder(ui->leftBtn, ui->rightBtn);
    setTabOrder(ui->rightBtn, ui->verticalSlider);
    setTabOrder(ui->verticalSlider, ui->add2EndBtn);
}

void TeachGoalDialog::setJoystickLevel(int level)
{
    if(level == 0){
        ui->add2EndBtn->setEnabled(false);
        ui->add2BelowBtn->setEnabled(false);
        ui->goOriginBtn->setEnabled(false);
        ui->abortBtn->setEnabled(false);
        ui->xyLabel->setEnabled(false);
        ui->xyLineEdit->setEnabled(false);
        ui->degreeLabel->setEnabled(false);
        ui->degreeLineEdit->setEnabled(false);
        ui->poseUpdateBtn->setEnabled(false);
        ui->erCheckBox->setEnabled(false);
        this->setWindowTitle("Joystick");
    }
    else if(level == 1){
        ui->add2EndBtn->setEnabled(false);
        ui->add2BelowBtn->setEnabled(false);
        ui->add2EndBtn->setVisible(false);
        ui->add2BelowBtn->setVisible(false);
        this->setWindowTitle("Joystick");
    }
}

void TeachGoalDialog::on_add2EndBtn_clicked()
{
    emit addTeachGoal(m_pos, m_quat, true);
    this->close();
}

void TeachGoalDialog::on_add2BelowBtn_clicked()
{
    emit addTeachGoal(m_pos, m_quat, false);
    this->close();
}

void TeachGoalDialog::on_cancelBtn_clicked()
{
    this->close();
}

void TeachGoalDialog::on_verticalSlider_valueChanged(int value)
{
    emit updateVelPercentage(value);
}

void TeachGoalDialog::on_forwardBtn_pressed()
{
    emit updateVel(VEL_TYPE::Forward);
}

void TeachGoalDialog::on_backwardBtn_pressed()
{
    emit updateVel(VEL_TYPE::Backward);
}

void TeachGoalDialog::on_leftBtn_pressed()
{
    emit updateVel(VEL_TYPE::Left);
}

void TeachGoalDialog::on_rightBtn_pressed()
{
    emit updateVel(VEL_TYPE::Right);
}

void TeachGoalDialog::on_forwardBtn_released()
{
    if(teleopMode == TELEOP_TYPE::JOG)
        emit updateVel(VEL_TYPE::Stop);
}

void TeachGoalDialog::on_backwardBtn_released()
{
    if(teleopMode == TELEOP_TYPE::JOG)
        emit updateVel(VEL_TYPE::Stop);
}

void TeachGoalDialog::on_leftBtn_released()
{
    if(teleopMode == TELEOP_TYPE::JOG)
        emit updateVel(VEL_TYPE::Stop);
}

void TeachGoalDialog::on_rightBtn_released()
{
    if(teleopMode == TELEOP_TYPE::JOG)
        emit updateVel(VEL_TYPE::Stop);
}

void TeachGoalDialog::updateAmclPoseValue(QPointF pos, QQuaternion quat)
{
    m_pos = pos;
    m_quat = quat;
    float angle = quat.toEulerAngles().z();
    if(angle < -180.0)
        angle += 360.0;
    else if(angle > 180.0)
        angle -= 360.0;
    ui->xyLineEdit->setText(QString("(%1,%2)").arg(pos.y(), 0, 'f', 2).arg(pos.x(), 0, 'f', 2));
    ui->degreeLineEdit->setText(QString("%1").arg(angle, 0, 'f', 2));
}

void TeachGoalDialog::on_goOriginBtn_clicked()
{
    ui->erCheckBox->setChecked(true);
    emit goOrigin();
}

void TeachGoalDialog::on_poseUpdateBtn_clicked()
{
    emit poseUpdate();
}

void TeachGoalDialog::on_jogRadioBtn_toggled(bool checked)
{
    if(checked)
        teleopMode = TELEOP_TYPE::JOG;
    else
        teleopMode = TELEOP_TYPE::LINEAR;
    emit updateVel(VEL_TYPE::Stop);
    emit setTeleopMode(teleopMode);
}

void TeachGoalDialog::on_stopBtn_clicked()
{
    emit updateVel(VEL_TYPE::Stop);
}

void TeachGoalDialog::on_abortBtn_clicked()
{
    emit abortMovebase();
}

void TeachGoalDialog::on_erCheckBox_stateChanged(int arg1)
{
    emit setKeyPriorityFlag(arg1);
}
