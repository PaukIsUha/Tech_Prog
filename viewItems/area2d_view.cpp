#ifndef AREA2D_VIEW_CPP
#define AREA2D_VIEW_CPP


#include <viewItems/area2d_view.hpp>


QGraphicsScene* viewItem::area2d_view::scene = nullptr;

void viewItem::area2d_view::setScene(QGraphicsScene *other_scene) {
    scene = other_scene;
}

QGraphicsScene* viewItem::area2d_view::getScene() {
    return scene;
}

viewItem::area2d_view::area2d_view(const std::vector<geli::Graph *>& _figures)
    : figures(_figures)
{
    setZValue(-3);
}

QRectF viewItem::area2d_view::boundingRect() const
{
    return QRectF(0, 0, this->scene->width(), this->scene->height());
}

void viewItem::area2d_view::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    prepareGeometryChange();
// Draw the line itself
    painter->setPen(QPen(getGradient(), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    auto _area = calcArea();
    for (size_t X = 0; X < this->scene->width(); X += 2)
    {
        for (size_t Y = 0; Y < this->scene->height(); Y += 2)
        {
            linear_space::point p = {real(X), real(Y)};
            if (_area.in_area(p))
            {
                painter->drawRect(X, Y, 1, 1);
            }
        }
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

linear_space::area2d viewItem::area2d_view::calcArea() const
{
    std::vector<std::vector<linear_space::point>> dataPoints;
    linear_space::area2d intersection;
    for (const auto& figure: figures)
    {
        if (!figure->is_valid())
        {
            continue;
        }
        auto data_points = linear_space::toLSpoints(viewItem::vector_pos(figure->get_nodes()));
        linear_space::point cof = linear_space::center_of_gravity(data_points);
        for (const auto& side : figure->get_edges())
        {
            linear_space::point _first_ = linear_space::toLSpoint(side->first());
            linear_space::point _second_ = linear_space::toLSpoint(side->second());
            try
            {
                linear_space::border2d border(std::make_tuple(_first_, _second_), cof);
                intersection.push_back_border(border);
            }
            catch (std::logic_error)
            {
                continue;
            }
        }
    }

    return intersection;
}

QLinearGradient viewItem::area2d_view::getGradient() const
{
    QLinearGradient m_gradient(0, 0, this->scene->width(), this->scene->height());
    m_gradient.setColorAt(0.0, OUT_CONTRE_NODE);
    m_gradient.setColorAt(1.0, INSIDE_LINE_NODE);
    return m_gradient;
}

void viewItem::area2d_view::push_back_graph(geli::Graph* graph)
{
    figures.push_back(graph);
}

#endif
