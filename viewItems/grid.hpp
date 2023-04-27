#ifndef GRID_HPP
#define GRID_HPP

#include <move_node.hpp>

#define GRID_DEFAULT_COLOR QColor(128, 128, 128, 255)
#define GRID_FREQUENCY 10

namespace viewItem
{
    class grid : public QObject, public QGraphicsItem
    {
    public:
        grid(QGraphicsScene *_scene, QColor _color = GRID_DEFAULT_COLOR);
        void setColor(const QColor& _color);

        ~grid() = default;
    signals:
    private:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    private:
        QColor color;
        QGraphicsScene *scene;
    };
}

#endif // GRID_HPP
