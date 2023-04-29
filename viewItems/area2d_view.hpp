#ifndef AREA2D_VIEW_HPP
#define AREA2D_VIEW_HPP

#include <graphicFigures/Geli.hpp>
#include <linSpace/linear_space.hpp>
#include <viewItems/edge.hpp>


namespace viewItem
{
    class area2d_view: public QObject, public QGraphicsItem
    {
    public:
        area2d_view(const std::vector<geli::Graph *>& _figures = std::vector<geli::Graph *>());
        static void setScene(QGraphicsScene *other_scene);
        static QGraphicsScene* getScene();
        void push_back_graph(geli::Graph* graph);

        ~area2d_view() = default;
    signals:
    private:
        static QGraphicsScene *scene;
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    private:
        linear_space::area2d calcArea() const;
        QLinearGradient getGradient() const;
    private:
        std::vector<geli::Graph *> figures;
    };
}

#endif // AREA2D_VIEW_HPP
