#ifndef LINEAR_SPACE_HPP
#define LINEAR_SPACE_HPP

#include <vector>
#include <tuple>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <QPointF>
typedef long double real;

#define PI 3.14159268

namespace linear_space
{
    struct point
    {
        real x;
        real y;

        point() = default;

        point& operator+=(const point& p);
        point operator+(const point& p) const;
        point& operator-=(const point& p);
        point operator-(const point& p) const;
        point& operator/=(const real& value);
        point operator/(const real& value) const;

        point& operator=(const point& p) = default;
    };

    point toLSpoint(const QPointF& qt_point);
    std::vector<point> toLSpoints(const std::vector<QPointF>& qt_points);
    point sort_by_angle_to_center_of_gravity(std::vector<point>& points);
    #define sacg(p) sort_by_angle_to_center_of_gravity(p)
    point center_of_gravity(const std::vector<point>& points);
    bool comparator_by_angle(const point& p1, const point& p2);
    real cos_to_x_axis(const point& p1);
    #define cxa(p) cos_to_x_axis(p)
    real sin_to_x_axis(const point& p1);
    #define sxa(p) sin_to_x_axis(p)
    real modulus(const point& p1);
    real sin_vector(const point& p1, const point& p2);

    class border2d	// border: const_y * y + const_x * x <= m_const
    {
    private:
        real const_x;
        real const_y;
        real m_const;
        bool leq;
    public:
        border2d() = default;
        border2d(const border2d& _b_2d) = default;
        border2d(std::tuple<point, point> line, const point& area_cond);	// init border from line to side of area_cond

        bool in_border(const point& p) const;	// point inside border
        bool out_border(const point& p) const;	// point outside border - true

        border2d& operator=(const border2d& _b_2d) = default;
        border2d& operator=(border2d&& _b_2d) = default;

        ~border2d() = default;
    };

    class area2d	// area is set of borders
    {
    private:
        std::vector<border2d> borders;

    public:
        area2d() = default;
        area2d(const area2d& a_2d) = default;
        area2d(std::vector<point> points);	// triangle area

        bool in_area(const point& p) const;	// point inside area
        void push_back_border(const border2d& border);

        area2d operator&(const area2d& a_2d) const;	// intersection of 2 areas
        area2d& operator&=(const area2d& a_2d);

        area2d& operator=(const area2d& a_2d) = default;
        area2d& operator=(area2d&& a_2d) = default;

        void clear();

        ~area2d() = default;
    };
}

#endif // LINEAR_SPACE_HPP
