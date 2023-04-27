#include "edge.hpp"
#include <QDebug>

#define DELTA 0.3

viewItem::edge::edge(viewItem::moveNode* _start_node, viewItem::moveNode* _finish_node)
    : start_node(_start_node),
      finish_node(_finish_node)
{
    setZValue(-2);
    color = Qt::white;
}


QRectF viewItem::edge::boundingRect() const
{
    return QRectF(this->start_node->pos().x(),
                  this->start_node->pos().y(),
                  this->finish_node->pos().x(),
                  this->finish_node->pos().y());
}

void viewItem::edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!start_node || !finish_node)
            return;

    QLineF line(start_node->pos(), finish_node->pos());
    if (qFuzzyCompare(line.length(), qreal(0.))) {
        return;
    }

    prepareGeometryChange();
    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void viewItem::edge::setColor(const QColor& _color)
{
    color = _color;
}

void viewItem::edge::link(viewItem::moveNode* _start_node, viewItem::moveNode* _finish_node) {
    this->start_node  = _start_node;
    this->finish_node = _finish_node;
}

bool viewItem::edge::intersects(const viewItem::edge* other_edge) {
    qreal x1 = this->start_node->pos().x();
    qreal x2 = this->finish_node->pos().x();
    qreal y1 = this->start_node->pos().y();
    qreal y2 = this->finish_node->pos().y();

    qreal _x1 = other_edge->start_node->pos().x();
    qreal _x2 = other_edge->finish_node->pos().x();
    qreal _y1 = other_edge->start_node->pos().y();
    qreal _y2 = other_edge->finish_node->pos().y();

    if (x1 - x2 == 0 && _x1 - _x2 == 0) {
        return false;
    } else if (x1 - x2 == 0) {
        qreal _k = (_y2 - _y1) / (_x2 - _x1);
        qreal x0 = x1;
        qreal y0 = _k * x0 + _x1;
        if (((y1 + DELTA < y0 && y0 < y2 - DELTA) || (y2 + DELTA < y0 && y0 < y1 - DELTA)) &&
            ((_x1 + DELTA < x0 && x0 < _x2 - DELTA) || (_x2 + DELTA < x0 && x0 < _x1 - DELTA)) &&
            ((_y1 + DELTA < y0 && y0 < _y2 - DELTA) || (_y2 + DELTA < y0 && y0 < _y1 - DELTA))) {
            return true;
        } else {
            return false;
        }
    } else if (_x1 - _x2 == 0) {
        qreal k = (y2 - y1) / (x2 - x1);
        qreal x0 = _x1;
        qreal y0 = k * x0 + x1;
        if (((x1 + DELTA < x0 && x0 < x2 - DELTA) || (x2 + DELTA < x0 && x0 < x1 - DELTA)) &&
            ((y1 + DELTA < y0 && y0 < y2 - DELTA) || (y2 + DELTA < y0 && y0 < y1 - DELTA)) &&
            ((_y1 + DELTA < y0 && y0 < _y2 - DELTA) || (_y2 + DELTA < y0 && y0 < _y1 - DELTA))) {
            return true;
        } else {
            return false;
        }
    } else {
        qreal k = (y2 - y1) / (x2 - x1);
        qreal _k = (_y2 - _y1) / (_x2 - _x1);
        if (_k == k) {
            return false;
        } else {
            qreal x0 = (k * x1 - _k * _x1 + _y1 - y1) / (k - _k);
            qreal y0 = k * (x0 - x1) + y1;

            if (((x1 + DELTA < x0 && x0 < x2 - DELTA) || (x2 + DELTA < x0 && x0 < x1 - DELTA)) &&
                ((y1 + DELTA < y0 && y0 < y2 - DELTA) || (y2 + DELTA < y0 && y0 < y1 - DELTA)) &&
                ((_x1 + DELTA < x0 && x0 < _x2 - DELTA) || (_x2 + DELTA < x0 && x0 < _x1 - DELTA)) &&
                ((_y1 + DELTA < y0 && y0 < _y2 - DELTA) || (_y2 + DELTA < y0 && y0 < _y1 - DELTA))) {
                return true;
            } else {
                return false;
            }
        }
    }
}
