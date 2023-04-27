
#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsView>
#include <graphicFigures/Geli.hpp>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class GraphicsScene; }  // Не пон что это, но у тебя было также ¯\_(ツ)_/¯
QT_END_NAMESPACE

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    void addItem(QGraphicsItem* gr_obj);

    void addItem(geli::Graph* gr_obj);

public slots:
    void ScreenResize(int width, int height);
};

//public:


#endif // GRAPHICSSCENE_H
