#ifndef MOVE_NODE_HPP
#define MOVE_NODE_HPP

#include <QGraphicsItem>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#define POINT_SIZE 20

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

namespace viewItem
{
    class moveNode : public QObject, public QGraphicsItem
    {
    public:
        moveNode();
    signals:
    private:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    };
}

#endif // MOVE_NODE_HPP
