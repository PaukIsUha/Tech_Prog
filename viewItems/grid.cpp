#ifndef GRID_CPP
#define GRID_CPP

#include <viewItems/grid.hpp>

viewItem::grid::grid(QGraphicsScene *_scene, QColor _color)
    : color(_color) ,
      scene(_scene)
{
    setZValue(-5);
}


QRectF viewItem::grid::boundingRect() const
{
    return QRectF(0, 0, 600, 800);
}

void viewItem::grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    prepareGeometryChange();

    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    // vertical
    size_t v = scene->width() / GRID_FREQUENCY;
    for (size_t i = 0; i < scene->width(); i += v)
    {
        QLineF line(QPointF(i, 0), QPointF(i, scene->height()));
        painter->drawLine(line);
    }
    // horizontal
    v = scene->height() / GRID_FREQUENCY;
    for (size_t j = 0; j < scene->height(); j += v)
    {
        QLineF line(QPointF(0, j), QPointF(scene->width(), j));
        painter->drawLine(line);
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void viewItem::grid::setColor(const QColor& _color)
{
    color = _color;
}

#endif
