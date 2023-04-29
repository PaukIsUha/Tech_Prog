
#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <graphicFigures/geli/poly_line.hpp>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    bool getDevStatus();
    void setDevStatus(bool status);

public slots:
    void ScreenResize(int width, int height);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool developing_status = false;
};


#endif // GRAPHICSSCENE_H
