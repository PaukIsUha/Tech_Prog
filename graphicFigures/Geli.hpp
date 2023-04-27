
#ifndef GELI_H
#define GELI_H
#include <QObject>
#include <QGraphicsItem>
#include <vector>

namespace viewItem {
    class moveNode;
}

namespace viewItem {
    class edge;
}


namespace geli {
    class Graph {
        std::vector<viewItem::moveNode*> nodes;
        std::vector<viewItem::edge*> edges;

        static QGraphicsScene *scene;
        static std::vector<Graph*> graphs_db;

        bool validity;
    public:
        Graph();
        Graph(const std::vector<QPointF*> &input);
        const std::vector<viewItem::moveNode*>& get_nodes();
        const std::vector<viewItem::edge*>& get_edges();
        void push_back_node(viewItem::moveNode* new_node);
        void pop_back_node();
        size_t size() const;
        void clear();
        void add_subobjects_to_scene();
        static std::vector<Graph*> get_graphs_db();
        static void setScene(QGraphicsScene *other_scene);
        static QGraphicsScene* getScene();
        void validation_check();
        void setColor(const QColor& _color);
        bool is_valid() const;

        ~Graph();

    private:

    };
}

#endif // GELI_H
