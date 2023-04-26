
#ifndef GRAPHICSVIEW_CPP
#define GRAPHICSVIEW_CPP

#include "GraphicsScene.h"
#include <QGraphicsView>
#include <QDebug>

void GraphicsScene::ScreenResize(int width, int height)
{
    this->setSceneRect(0, 0, width - 15, height - 40);
    qDebug() << "Width: " << this->width() << ", Height: " << this->height();
    qDebug() << "Width: " << width << ", Height: " << height;
}

#endif // GRAPHICSVIEW_CPP
