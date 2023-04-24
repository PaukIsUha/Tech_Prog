#include "move_node.hpp"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>

enum {
    POINT_SIZE = 20,
};

move_node::moveNode::moveNode(QPointF* rect, QWidget *_widget)
    : __widget__(_widget),
      position(rect)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    //position = new QPointF();
}

QRectF move_node::moveNode::boundingRect() const
{
    return QRectF(-POINT_SIZE / 2, -POINT_SIZE / 2, POINT_SIZE, POINT_SIZE);
}

void move_node::moveNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::lightGray);
    QLinearGradient m_gradient(-POINT_SIZE / 2, -POINT_SIZE / 2, POINT_SIZE, POINT_SIZE);
    m_gradient.setColorAt(0.0, Qt::red);
    m_gradient.setColorAt(1.0, Qt::blue);
    painter->setBrush(m_gradient);
    painter->drawEllipse(-POINT_SIZE / 2, -POINT_SIZE / 2, POINT_SIZE, POINT_SIZE);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void move_node::moveNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
//    this->position = QRectF(event->pos(), position.size());

    this->setPos(mapToScene(event->pos()));
}

void move_node::moveNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setScale(2);
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void move_node::moveNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setScale(1);
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
