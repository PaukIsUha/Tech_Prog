#ifndef POLY_LINE_CPP
#define POLY_LINE_CPP

#include <graphicFigures/geli/poly_line.hpp>


namespace geli {
    PolyLine::PolyLine(QGraphicsScene *scene) {
        this->scene = scene;
    }

    void PolyLine::add_node(viewItem::moveNode* new_node) {
        if (this->nodes.size()) {
            viewItem::edge *new_edge = new viewItem::edge(this->nodes.back(), new_node);
            this->edges.push_back(new_edge);
            this->scene->addItem(new_edge);
        } else {
            this->scene->addItem(this);
        }
        this->nodes.push_back(new_node);
        this->scene->addItem(new_node);
    }

    void PolyLine::close_line() {
        is_closed = true;
        if (this->nodes.size() >= 2) {
            viewItem::edge *new_edge = new viewItem::edge(this->nodes.back(), this->nodes[0]);
            this->edges.push_back(new_edge);
            this->scene->addItem(new_edge);
        }
    }

    void PolyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        prepareGeometryChange();
        Q_UNUSED(option);
        Q_UNUSED(widget);
        Q_UNUSED(painter);
        if (this->is_closed) {
            this->validation_check();
        }
    }
}

#endif
