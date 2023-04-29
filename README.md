# Tech_Prog
## frame Graph 
Основная фигура(в частности треугольник), состоящая из наборов: edge, move_node
## frame PolyLine 
Надстройка над Graph, обеспечивающая более удобный UI
## frame linear_space
Добавляет различные вычислительные инструменты для работы с линейными пространствами: </br>
 - struct point - точка </br>
 - class border2d - полуплоскость относительно какой-либо прямой </br>
 - class area2d - полуплоскость являющаяся пересечением border2d
## frame move_node
Двигаемая точка на дисплее
## frame edge
Линия на дисплее определяемая двумя move_node
## frame area2d_view
Область пересечения нескольких фигур(area2d)
## frame mainwindow
Виджет экрана унаследованый от QWindow.
## qmake nodes_project.pro
just QMake)))
