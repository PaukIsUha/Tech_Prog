#include "area2d_view.hpp"


QGraphicsScene* viewItem::area2d_view::scene = nullptr;

void viewItem::area2d_view::setScene(QGraphicsScene *other_scene) {
    scene = other_scene;
}

QGraphicsScene* viewItem::area2d_view::getScene() {
    return scene;
}

viewItem::area2d_view::area2d_view(const dataNodes& _figures)
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
    if (figures.size() != 2)
        throw std::out_of_range("Not propably variant");
    if (figures[0].size() != 3)
        throw std::out_of_range("Not propably variant");
    if (figures[1].size() != 3)
        throw std::out_of_range("Not propably variant");
    std::vector<std::vector<linear_space::point>> dataPoints;
    dataPoints.resize(figures.size());
    for (size_t i = 0; i < dataPoints.size(); ++i)
    {
        dataPoints[i].resize(figures[i].size());
        for (size_t j = 0; j < dataPoints[i].size(); ++j)
        {
            dataPoints[i][j] = linear_space::toLSpoint(figures[i][j]->pos());
        }
    }
    linear_space::area2d interscetion;
    try
    {
        for (auto stack_points: dataPoints)
        {
            interscetion &= linear_space::area2d(stack_points);
        }
//        linear_space::area2d area1(std::make_tuple(dataPoints[0][0], dataPoints[0][1], dataPoints[0][2]));
//        linear_space::area2d area2(std::make_tuple(dataPoints[1][0], dataPoints[1][1], dataPoints[1][2]));
//        interscetion = area1 & area2;
    }  catch (std::logic_error)
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
