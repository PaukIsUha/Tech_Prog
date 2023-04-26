
#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsView>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public slots:
    void ScreenResize(int width, int height);
};

#endif // GRAPHICSSCENE_H
