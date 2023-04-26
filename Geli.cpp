
#ifndef GELI_CPP
#define GELI_CPP
#include "Geli.hpp"


namespace GELI {
    Graph::Graph(const std::vector<viewItem::moveNode> &input) {
        for (auto &el : input) {
            this->nodes.push_back(el);
        }
    }

    void Graph::add_node(const viewItem::moveNode& new_node) {
        this->nodes.push_back(new_node);
    }

    void Graph::delete_last() {
        this->nodes.pop_back();
    }

    size_t Graph::get_size() const {
        return this->nodes.size();
    }

    void Graph::clear() {
        this->nodes.clear();
    }

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

//    }
}

#endif // GELI_CPP