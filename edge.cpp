#include "edge.hpp"

viewItem::edge::edge(viewItem::moveNode* _start_node, viewItem::moveNode* _finish_node)
    : start_node(_start_node),
      finish_node(_finish_node)
{
    setZValue(-2);
    color = Qt::white;
}


QRectF viewItem::edge::boundingRect() const
{
    return QRectF(0, 0, 600, 800);
}

void viewItem::edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!start_node || !finish_node)
            return;

    QLineF line(start_node->pos(), finish_node->pos());
    if (qFuzzyCompare(line.length(), qreal(0.)))
            return;

    prepareGeometryChange();
// Draw the line itself
    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void viewItem::edge::setColor(const QColor& _color)
{
    color = _color;
}
