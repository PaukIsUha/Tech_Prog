
#ifndef GELI_CPP
#define GELI_CPP
#include <graphicFigures/Geli.hpp>
#include <viewItems/move_node.hpp>
#include <viewItems/edge.hpp>
#include <QDebug>

QGraphicsScene* geli::Graph::scene = nullptr;

namespace geli {
    Graph::Graph(const std::vector<QPointF*> &input) : Graph() {
        for (auto el : input) {
            viewItem::moveNode *node = new viewItem::moveNode();
            node->setPos(*el);
            this->nodes.push_back(node);
        }

        if (this->nodes.size() > 1) {
            viewItem::edge *ed = new viewItem::edge(this->nodes[0],
                                                    this->nodes[this->nodes.size() - 1]);
            this->edges.push_back(ed);
            for (size_t i = 0; i < this->nodes.size() - 1; ++i) {
                ed = new viewItem::edge(this->nodes[i], this->nodes[i + 1]);
                this->edges.push_back(ed);
            }
        }
        validation_check();
        qDebug() << this->validity;
    }

    void Graph::push_back_node(viewItem::moveNode* new_node) {
        this->nodes.push_back(new_node);
    }

    void Graph::pop_back_node() {
        this->nodes.pop_back();
    }

    size_t Graph::size() const {
        return this->nodes.size();
    }

    void Graph::clear() {
        for (auto edge : this->edges) {
            scene->removeItem(edge);
            delete edge;
        }
        for (auto node : this->nodes) {
            scene->removeItem(node);
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
        if (!valid_intersection() || !valid_convexity())
        {
            this->validity = false;
            this->setColor(Qt::red);
        }
        else
        {
            this->validity = true;
            this->setColor(Qt::green);
        }
    }

    void Graph::setColor(const QColor& _color) {
        for (auto &edge : this->edges) {
            edge->setColor(_color);
        }
    }

    bool Graph::is_valid() const
    {
        return validity;
    }

    bool Graph::valid_intersection() const
    {
        for (auto &ed1 : this->edges) {
            for (auto &ed2 : this->edges) {
                if (ed1->intersects(ed2)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Graph::valid_convexity() const
    {
        // some check convexity
        return true;
    }

    QRectF Graph::boundingRect() const
    {
        return QRectF(0, 0, 0, 0);
    }

    void Graph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        Q_UNUSED(painter);
        validation_check();
        if (!Graph::already_on_scene) {
            Graph::add_subobjects_to_scene();
            Graph::already_on_scene = true;
        }
    }

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
        Q_UNUSED(option);
        Q_UNUSED(widget);
        Q_UNUSED(painter);
        if (this->is_closed) {
            this->validation_check();
        }
    }
}

#endif // GELI_CPP
