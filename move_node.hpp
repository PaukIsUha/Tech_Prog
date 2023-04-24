#ifndef MOVE_NODE_HPP
#define MOVE_NODE_HPP

#include <QGraphicsItem>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

namespace move_node
{
    class moveNode : public QObject, public QGraphicsItem
    {
    public:
        moveNode(QPointF* rect = nullptr, QWidget *_widget = nullptr);
    signals:
    private:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


        QWidget *__widget__;
        QPointF *position;
    };
}

#endif // MOVE_NODE_HPP
