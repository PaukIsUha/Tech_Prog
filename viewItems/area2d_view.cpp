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
    //dataPoints.resize(figures.size());
    linear_space::area2d interscetion;
    for (size_t i = 0; i < figures.size(); ++i)
    {
        if (!figures[i]->is_valid())
        {
            continue;
        }
        dataPoints.push_back(std::vector<linear_space::point>());
        size_t last_ind = dataPoints.size() - 1;
        auto nodes_figures = figures[i]->get_nodes();
        dataPoints[last_ind].resize(nodes_figures.size());
        for (size_t j = 0; j < dataPoints[last_ind].size(); ++j)
        {
            dataPoints[last_ind][j] = linear_space::toLSpoint(nodes_figures[j]->pos());
        }
    }
    try
    {
        for (const auto& stack_points: dataPoints)
        {
            interscetion &= linear_space::area2d(stack_points);
        }
    }
    catch (std::logic_error)
    {
        interscetion.clear();
    }

    return interscetion;
}

QLinearGradient viewItem::area2d_view::getGradient() const
{
    QLinearGradient m_gradient(0, 0, this->scene->width(), this->scene->height());
    m_gradient.setColorAt(0.0, OUT_CONTRE_NODE);
    m_gradient.setColorAt(1.0, INSIDE_LINE_NODE);
    return m_gradient;
}
