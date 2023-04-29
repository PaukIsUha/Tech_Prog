#ifndef MOVE_NODE_HPP
#define MOVE_NODE_HPP

#include <QGraphicsItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <ui_mainwindow.h>
#include <mainwindow.h>
#include <QGraphicsScene>
#include <QCoreApplication>
#include <QDebug>
#include <QtGui>
#define POINT_SIZE 20

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;
namespace geli {
    class Graph;
}

#define OUT_CONTRE_NODE QColor(175, 0, 0, 255)
#define OUT_LINE_NODE QColor(125, 0, 0, 255)
#define INSIDE_CONTRE_NODE QColor(100, 0, 0, 255)
#define INSIDE_LINE_NODE QColor(75, 0, 0, 255)

namespace viewItem
{
    class moveNode : public QObject, public QGraphicsItem
    {
    public:
        moveNode();
        moveNode(const moveNode& new_node);
        moveNode(const QPoint& point);
        moveNode(qreal x, qreal y);
        static void setScene(QGraphicsScene *other_scene);
        static QGraphicsScene* getScene();

        ~moveNode() = default;
    signals:
    private:
        static QGraphicsScene *scene;
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        friend class geli::Graph;
    };

    std::vector<QPointF> vector_pos(const std::vector<moveNode*>& m_nodes);
}

#endif // MOVE_NODE_HPP
