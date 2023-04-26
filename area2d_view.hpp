#ifndef AREA2D_VIEW_HPP
#define AREA2D_VIEW_HPP
#include <edge.hpp>
#include <linear_space.hpp>

typedef std::vector<std::vector<viewItem::moveNode *>> dataNodes;

namespace viewItem
{
    class area2d_view: public QObject, public QGraphicsItem
    {
    public:
        area2d_view(const dataNodes& _figures);
        static void setScene(QGraphicsScene *other_scene);
        static QGraphicsScene* getScene();
    signals:
    private:
        static QGraphicsScene *scene;
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    private:
        linear_space::area2d calcArea() const;
        QLinearGradient getGradient() const;
    private:
        dataNodes figures;
    };
}

#endif // AREA2D_VIEW_HPP
