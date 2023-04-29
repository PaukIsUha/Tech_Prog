#ifndef POLY_LINE_H
#define POLY_LINE_H
#include <graphicFigures/geli/graph.hpp>

namespace geli {
    class PolyLine : public Graph {
    private:
        bool is_closed = false;
        QGraphicsScene *scene;

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    public:
        PolyLine(QGraphicsScene *scene);
        void add_node(viewItem::moveNode* node);
        void close_line();
    };
}

#endif // POLY_LINE_H
