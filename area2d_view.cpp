#include "area2d_view.hpp"

viewItem::area2d_view::area2d_view(const dataNodes& _figures, size_t width, size_t height)
    : figures(_figures),
      __width__(width),
      __height__(height)
{
    setZValue(-3);
}

QRectF viewItem::area2d_view::boundingRect() const
{
    return QRectF(0, 0, 600, 800);
}

void viewItem::area2d_view::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    prepareGeometryChange();
// Draw the line itself
    QLinearGradient m_gradient(0, 0, 600, 800);
    m_gradient.setColorAt(0.0, Qt::black);
    m_gradient.setColorAt(1.0, Qt::white);
    painter->setPen(QPen(m_gradient, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    auto _area = calcArea();
    for (size_t X = 0; X < __width__; ++X)
    {
        for (size_t Y = 0; Y < __height__; ++Y)
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
    linear_space::area2d area1(std::make_tuple(dataPoints[0][0], dataPoints[0][1], dataPoints[0][2]));
    linear_space::area2d area2(std::make_tuple(dataPoints[1][0], dataPoints[1][1], dataPoints[1][2]));

    return area1 & area2;
}
