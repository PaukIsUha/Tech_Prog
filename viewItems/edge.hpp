#ifndef EDGE_HPP
#define EDGE_HPP

#include <viewItems/move_node.hpp>
#include <QDebug>

#define EDGE_COLOR_1 QColor(250, 150, 150, 255)

namespace viewItem
{
    class edge : public QObject, public QGraphicsItem
    {
    public:
        void link(viewItem::moveNode* _start_node, viewItem::moveNode* _finish_node);
        edge(viewItem::moveNode* _start_node, viewItem::moveNode* _finish_node);
        void setColor(const QColor& _color);
        bool intersects(const viewItem::edge* other_edge);
        ~edge() = default;
    
    signals:
    private:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    private:
        viewItem::moveNode* start_node;
        viewItem::moveNode* finish_node;
        QColor color;
    };
}

#endif // EDGE_HPP
