
#ifndef GRAPH_H
#define GRAPH_H
#include <QObject>
#include <QGraphicsItem>
#include <vector>
#include <linSpace/linear_space.hpp>
#include <viewItems/edge.hpp>
#include <viewItems/move_node.hpp>
#include <QGraphicsScene>

namespace geli {
    class Graph : public QObject, public QGraphicsItem {
    protected:
        std::vector<viewItem::moveNode*> nodes;
        std::vector<viewItem::edge*> edges;

        static QGraphicsScene *scene;

        bool validity;
        QRectF boundingRect() const;
        bool valid_intersection() const;
        bool valid_convexity() const;
    public:
        Graph() = default;
        Graph(const std::vector<QPointF*> &input);
        const std::vector<viewItem::moveNode*>& get_nodes();
        const std::vector<viewItem::edge*>& get_edges();
        void push_back_node(viewItem::moveNode* new_node);
        void pop_back_node();
        size_t size() const;
        void clear();
        static void setScene(QGraphicsScene *other_scene);
        static QGraphicsScene* getScene();
        void validation_check();
        void setColor(const QColor& _color);
        bool is_valid() const;

        ~Graph();
    private:

        void add_subobjects_to_scene();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        bool already_on_scene = false;
    };
}

#endif // GRAPH_H
