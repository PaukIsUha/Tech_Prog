
#ifndef GRAPHICSVIEW_CPP
#define GRAPHICSVIEW_CPP

#include <graphicFigures/GraphicsScene.h>

void GraphicsScene::ScreenResize(int width, int height)
{
    this->setSceneRect(0, 0, width - 15, height - 40);
}

bool GraphicsScene::getDevStatus() {
    return this->developing_status;
}

void GraphicsScene::setDevStatus(bool status) {
    this->developing_status = status;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);
}

#endif // GRAPHICSVIEW_CPP
