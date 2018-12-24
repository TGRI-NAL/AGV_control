#include "goaleditdialog.h"
#include "ui_goaleditdialog.h"

goalEditDialog::goalEditDialog(int order, QPointF pos, QQuaternion quat, float disTolerance, float angleTolerance, float reachTolerance, QString remark, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goalEditDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());

    goalOrder = order;
    goalRemark = remark;
    ui->xDoubleSpinBox->setValue(pos.y());
    ui->yDoubleSpinBox->setValue(pos.x());
    ui->orientationDoubleSpinBox->setValue(quat.toEulerAngles().z());
    ui->disToleranceDSB->setValue(disTolerance);
    ui->angleToleranceDSB->setValue(angleTolerance);
    ui->reachToleranceDSB->setValue(reachTolerance);
    ui->remarkLineEdit->setText(remark);

    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap(":/xy_description.png"));
    double ratio = (double) (241.0-10)/pixmapItem->pixmap().height();
    pixmapItem->setScale(ratio);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addItem(pixmapItem);
    ui->xyGraphicsView->setScene(scene);

    ui->xyGraphicsView->hide();
    this->setFixedWidth(340);
}

void goalEditDialog::setMapInfo(float resolution, float width, float height, float width_ori, float height_ori)
{
    ui->xDoubleSpinBox->setMaximum(height * resolution + height_ori);
    ui->xDoubleSpinBox->setMinimum(height_ori);

    ui->yDoubleSpinBox->setMaximum(width * resolution + width_ori);
    ui->yDoubleSpinBox->setMinimum(width_ori);
}

goalEditDialog::~goalEditDialog()
{
    delete ui;
}

void goalEditDialog::on_okBtn_clicked()
{
    QPointF pos(ui->yDoubleSpinBox->value(), ui->xDoubleSpinBox->value());
    emit updateGoalValue(goalOrder, pos, qDegreesToRadians(ui->orientationDoubleSpinBox->value()),
                         ui->disToleranceDSB->value(), ui->angleToleranceDSB->value(), ui->reachToleranceDSB->value(), ui->remarkLineEdit->text());

    close();
}

void goalEditDialog::on_cancelBtn_clicked()
{
    close();
}

void goalEditDialog::on_coordinateMapBtn_clicked()
{
    if(ui->xyGraphicsView->isHidden())
    {
        ui->xyGraphicsView->show();
        this->setFixedWidth(570);
    }
    else
    {
        ui->xyGraphicsView->hide();
        this->setFixedWidth(340);
    }
}

void goalEditDialog::on_cloneEndBtn_clicked()
{
    QPointF pos(ui->yDoubleSpinBox->value(), ui->xDoubleSpinBox->value());
    emit cloneGoal(-1, pos, qDegreesToRadians(ui->orientationDoubleSpinBox->value()),
                   ui->disToleranceDSB->value(), ui->angleToleranceDSB->value(), ui->reachToleranceDSB->value(), ui->remarkLineEdit->text());
    close();
}

void goalEditDialog::on_cloneBelowBtn_clicked()
{
    QPointF pos(ui->yDoubleSpinBox->value(), ui->xDoubleSpinBox->value());
    emit cloneGoal(goalOrder, pos, qDegreesToRadians(ui->orientationDoubleSpinBox->value()),
                   ui->disToleranceDSB->value(), ui->angleToleranceDSB->value(), ui->reachToleranceDSB->value(), ui->remarkLineEdit->text());
    close();
}
