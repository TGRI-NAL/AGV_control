#include "navimarkeritem.h"

NaviMarkerItem::NaviMarkerItem(int num) :
    editType(EDIT_TYPE::Nop),
    theta(0),
    isFocus(false),
    isEditable(true),
    isOneGoalSelected(false)
{
    order = num;
    this->setAcceptHoverEvents(true);
}

QRectF NaviMarkerItem::boundingRect() const
{
    return QRectF(-5, -5, 10, 10);
}

void NaviMarkerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(isOneGoalSelected)
        if(isFocus)
            painter->setPen(QPen(Qt::green, 1));
        else
            return;
    else
        painter->setPen(QPen(Qt::blue, 1));


    painter->drawEllipse(-5, -5, 10, 10);
    QFont font = painter->font() ;
    font.setPointSize(5);
    painter->setFont(font);
    painter->drawText(-3, -3, 6, 6, Qt::AlignCenter, QString("%1").arg(order));

    painter->setPen(QPen(Qt::red, 3));
    float displayTheta;
    if(theta < 0 && theta > -M_PI_2)
        displayTheta = qAtan(1.0/qTan(theta)) + M_PI;
    else if(theta <= -M_PI_2 && theta >= -M_PI)
        displayTheta = qAtan(1.0/qTan(theta)) - M_PI;
    else if(fabs(theta - M_PI) < 0.001)
        displayTheta = qAtan(1.0/qTan(theta)) - M_PI;
    else
        displayTheta = qAtan(1.0/qTan(theta));
    qreal x_pro = 6*qCos(displayTheta);
    qreal y_pro = 6*qSin(displayTheta);
    painter->drawPoint(x_pro, y_pro);

}

void NaviMarkerItem::updateNaviMarkerEditable(bool flag)
{
    isEditable = flag;
}

void NaviMarkerItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isEditable)
        return;

    if(event->button() == Qt::LeftButton && scene()->sceneRect().contains(event->scenePos())){
        editType = EDIT_TYPE::Position;
        isFocus = true;
    }
    else if(event->button() == Qt::RightButton){
        editType = EDIT_TYPE::Direction;
        isFocus = true;
    }
    else
        editType = EDIT_TYPE::Nop;
}

void NaviMarkerItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isEditable)
        return;
    if(editType == EDIT_TYPE::Position && scene()->sceneRect().contains(event->scenePos())){
        this->setPos(event->scenePos());
    }
    else if(editType == EDIT_TYPE::Direction){
        theta = qAtan2(event->scenePos().toPoint().x() - this->scenePos().x(),
                       event->scenePos().toPoint().y() - this->scenePos().y());
        this->update();
    }
    else
        Q_UNUSED(event);
}

void NaviMarkerItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isEditable)
        return;
    Q_UNUSED(event);
    editType = EDIT_TYPE::Nop;
    emit updateMarkerValue(order, this->scenePos(), theta);
    this->update();
}

void NaviMarkerItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(!isEditable)
        return;
    Q_UNUSED(event);
    emit updateMarkerEditStatus(EDIT_STATUS::OnEdit);
}

void NaviMarkerItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(!isEditable)
        return;
    Q_UNUSED(event);
    emit updateMarkerEditStatus(EDIT_STATUS::Idle);
}
