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
    class moveNode : public QGraphicsItem
    {
    public:
        moveNode(QGraphicsWidget *graphWidget);

        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    private:
        QPointF newPos;
        QGraphicsWidget *graph;
    };
}

#endif // MOVE_NODE_HPP
