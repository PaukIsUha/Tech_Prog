#include <linSpace/linear_space.hpp>

linear_space::area2d::area2d(std::vector<point> points)
{
    point cof = sacg(points);
    for (size_t i = 1; i < points.size(); ++i)
    {
        borders.push_back(border2d(std::make_tuple(points[i], points[i - 1]), cof));
    }
    borders.push_back(border2d(std::make_tuple(points.front(), points.back()), cof));
}

void linear_space::area2d::push_back_border(const border2d& border)
{
    borders.push_back(border);
}

linear_space::border2d::border2d(std::tuple<point, point> line, const point& area_cond)
{
    point p1 = std::get<0>(line);
    point p2 = std::get<1>(line);

    if (p1.x == p2.x)
    {
        const_y = 0;
        const_x = 1;
        m_const = p1.x;
    }
    else
    {
        const_y = 1;
        const_x = (p2.y - p1.y) / (p1.x - p2.x);
        m_const = const_y * p1.y + const_x * p1.x;
    }

    if (const_y * area_cond.y + const_x * area_cond.x < m_const)
        leq = true;
    else if (const_y* area_cond.y + const_x * area_cond.x > m_const)
        leq = false;
    else
        throw std::logic_error("Error linear function");
}

linear_space::area2d linear_space::area2d::operator&(const area2d& a_2d) const
{
    area2d new_area = *this;
    new_area &= a_2d;
    return new_area;
}

linear_space::area2d& linear_space::area2d::operator&=(const area2d& a_2d)
{
    for (const auto& border : a_2d.borders)
        borders.push_back(border);
    return *this;
}

bool linear_space::border2d::in_border(const point& p) const
{
    if (leq)
        return const_x * p.x + const_y * p.y <= m_const;
    else
        return const_x * p.x + const_y * p.y >= m_const;
}

bool linear_space::border2d::out_border(const point& p) const
{
    return !in_border(p);
}

bool linear_space::area2d::in_area(const point& p) const
{
    if (borders.empty())
        return false;
    for (const auto& border : borders)
        if (border.out_border(p))
            return false;
    return true;
}

linear_space::point& linear_space::point::operator+=(const point& p)
{
    x += p.x;
    y += p.y;
    return *this;
}

linear_space::point linear_space::point::operator+(const point& p) const
{
    point summary = *this;
    summary += p;
    return summary;
}

linear_space::point& linear_space::point::operator-=(const point& p)
{
    x -= p.x;
    y -= p.y;
    return *this;
}

linear_space::point linear_space::point::operator-(const point& p) const
{
    point summary = *this;
    summary -= p;
    return summary;
}

linear_space::point linear_space::sort_by_angle_to_center_of_gravity(std::vector<point>& points)
{
    point cof = center_of_gravity(points);
    for (auto& _point : points)
        _point -= cof;
    std::sort(points.begin(), points.end(), comparator_by_angle);
    for (auto& _point : points)
        _point += cof;
    return cof;
}

bool linear_space::comparator_by_angle(const point& p1, const point& p2)
{
    real _cos1 = cxa(p1);
    real _sin1 = sxa(p1);
    real _cos2 = cxa(p2);
    real _sin2 = sxa(p2);

    int quartal1 = 0;
    int quartal2 = 0;

    if (_cos1 >= 0)
        if (_sin1 >= 0)
            quartal1 = 1;
        else
            quartal1 = 2;
    else
        if (_sin1 < 0)
            quartal1 = 3;
        else
            quartal1 = 4;

    if (_cos2 >= 0)
        if (_sin2 >= 0)
            quartal2 = 1;
        else
            quartal2 = 2;
    else
        if (_sin2 < 0)
            quartal2 = 3;
        else
            quartal2 = 4;

    if (quartal1 != quartal2)
        return quartal1 < quartal2;
    if (_sin1 >= 0)
        return _cos1 < _cos2;
    else
        return _cos1 >= _cos2;
}

real linear_space::cos_to_x_axis(const point& p1)
{
    return p1.x / modulus(p1);
}

real linear_space::sin_to_x_axis(const point& p1)
{
    return p1.y / modulus(p1);
}

real linear_space::modulus(const point& p1)
{
    return std::sqrt(p1.x * p1.x + p1.y * p1.y);
}

linear_space::point linear_space::center_of_gravity(const std::vector<point>& points)
{
    point cof = { 0, 0 };
    for (const auto& _point : points)
        cof += _point;
    cof /= points.size();
    return cof;
}

linear_space::point& linear_space::point::operator/=(const real& value)
{
    x /= value;
    y /= value;
    return *this;
}

linear_space::point linear_space::point::operator/(const real& value) const
{
    point copy = *this;
    copy /= value;
    return copy;
}

linear_space::point linear_space::toLSpoint(const QPointF& qt_point)
{
    point p;
    p.x = qt_point.x();
    p.y = qt_point.y();
    return p;
}

void linear_space::area2d::clear()
{
    borders.clear();
}
