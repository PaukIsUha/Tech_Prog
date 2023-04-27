
#ifndef GELI_CPP
#define GELI_CPP
#include "Geli.hpp"
#include "move_node.hpp"
#include "edge.hpp"
#include <QDebug>

QGraphicsScene* geli::Graph::scene = nullptr;
std::vector<geli::Graph*> geli::Graph::graphs_db;

namespace geli {
    Graph::Graph() {
        graphs_db.push_back(this);
    }

    Graph::Graph(const std::vector<QPointF*> &input) : Graph() {
        for (auto el : input) {
            viewItem::moveNode *node = new viewItem::moveNode();        // Создаём узел (Треугольник 2, точка 1)
            node->setPos(*el);
            this->nodes.push_back(node);
        }

        if (this->nodes.size() > 1) {
            viewItem::edge *ed = new viewItem::edge(this->nodes[0],
                                                    this->nodes[this->nodes.size() - 1]);
            this->edges.push_back(ed);
            for (int i = 0; i < this->nodes.size() - 1; ++i) {
                ed = new viewItem::edge(this->nodes[i], this->nodes[i + 1]);
                this->edges.push_back(ed);
            }
        }
        validation_check();
        qDebug() << this->validity;
    }

    void Graph::append_node(viewItem::moveNode* new_node) {
        this->nodes.push_back(new_node);
    }

    void Graph::delete_last() {
        this->nodes.pop_back();
    }

    size_t Graph::get_size() const {
        return this->nodes.size();
    }

    void Graph::clear() {
        for (auto edge : this->edges) {
            delete edge;
        }
        for (auto node : this->nodes) {
            delete node;
        }
        this->nodes.clear();
        this->edges.clear();
    }

    void Graph::add_subobjects_to_scene() {
        for (size_t i = 0; i < this->nodes.size(); ++i) {
            scene->addItem(this->nodes[i]);
        }

        for (size_t i = 0; i < this->edges.size(); ++i) {
            scene->addItem(this->edges[i]);
        }
    }

    Graph::~Graph() {
        for (auto &el : this->nodes) {
            delete el;
        }
    }

    QGraphicsScene* Graph::getScene() {
        return scene;
    }

    void Graph::setScene(QGraphicsScene *other_scene) {
        scene = other_scene;
    }

    const std::vector<viewItem::moveNode*>& Graph::get_nodes() {
        return this->nodes;
    }

    const std::vector<viewItem::edge*>& Graph::get_edges() {
        return this->edges;
    }

    void Graph::validation_check() {
        for (auto &ed1 : this->edges) {
            for (auto &ed2 : this->edges) {
                if (ed1->intersects(ed2)) {
                    this->validity = false;
                    this->setColor(Qt::red);
                    return;
                }
            }
        }
        this->validity = true;
        this->setColor(Qt::green);
    }

    std::vector<Graph*> geli::Graph::get_graphs_db() {
        return graphs_db;
    }

    void Graph::setColor(const QColor& _color) {
        for (auto &edge : this->edges) {
            edge->setColor(_color);
        }
    }
}

#endif // GELI_CPP
