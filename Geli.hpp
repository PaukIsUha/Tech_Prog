
#ifndef GELI_H
#define GELI_H
#include "move_node.hpp"
#include <vector>

namespace GELI {
    class Graph {
        std::vector<viewItem::moveNode> nodes;
    public:
        Graph(const std::vector<viewItem::moveNode> &input);

        void add_node(const viewItem::moveNode& new_node);

        void delete_last();

        size_t get_size() const;

        void clear();

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    };
}

#endif // GELI_H
