Описание 
========================
## <charts_limits>
описание структуры пределов графиков, long long int [x/y]_[down/up]_limit
## <linear_space>
описание инструментов для линейного пространства
### структура point имеет координаты, также умеет скалярно складывать и вычитать точки (+, -)
### sacg - функция соритрурющая vector<point> по углу к центру масс
### класс border2d олицитворяет полуплоскость относительно прямой border: const_y * y + const_x * x <= m_const
bool in_border(point) лежит ли точка в полуплоскости
bool out_border(point) лежит ли точка вне полуплоскости
### класс area2d множество борьеров, которое ограничивает конкретную область, также 
bool in_area(point) лежит ли точка в множестве,
area2d operator&(const area2d& a_2d) const; пересечение двух областей(area2d)
## <themewidget>
qt backend приложения
ThemeWidget : QWidget
QChart *createLineChart() const; возвращает qt chart (двух треугольников и их пересечения)
pointTable setTrianglesPoints() const; возвращает двумерный массив точек (2 труегольника)
void setLimits(const pointTable& all_points, limits& _limits) const; поиск границ графика, в зависимости от входных точек
### themewidget.ui
qt frontend приложения
