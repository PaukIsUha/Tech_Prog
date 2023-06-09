
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
    public:
        Graph(const std::vector<QPointF*> &input);
        const std::vector<viewItem::moveNode*>& get_nodes();
        const std::vector<viewItem::edge*>& get_edges();
        size_t size() const;
        void clear();
        static void setScene(QGraphicsScene *other_scene);
        static QGraphicsScene* getScene();
        void validation_check();
        void setColor(const QColor& _color);
        bool is_valid() const;

        ~Graph();
    protected:
        Graph() = default;
        std::vector<viewItem::moveNode*> nodes;
        std::vector<viewItem::edge*> edges;
        bool validity;

        static QGraphicsScene *scene;
    protected:
        QRectF boundingRect() const;
        bool valid_intersection() const;
        bool valid_convexity() const;

    private:
        void add_subobjects_to_scene();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    private:
        bool already_on_scene = false;
    };
}

#endif // GRAPH_H
