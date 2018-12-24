#ifndef NAVIMARKERITEM_H
#define NAVIMARKERITEM_H

#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QGraphicsSceneHoverEvent>
#include <QtMath>
#include <QDebug>

enum EDIT_TYPE {Nop = 10, Position, Direction};
enum EDIT_STATUS {Idle = 20, OnEdit};

class NaviMarkerItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    NaviMarkerItem(int);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    EDIT_TYPE editType;
    int order;
    float theta;
    bool isFocus;
    bool isEditable;
    bool isOneGoalSelected;

signals:
    void updateMarkerValue(int num, QPointF pos, float thetaValue);
    void updateMarkerEditStatus(EDIT_STATUS);

public slots:
    void updateNaviMarkerEditable(bool);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // NAVIMARKERITEM_H
