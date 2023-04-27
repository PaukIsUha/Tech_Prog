
#ifndef GRAPHICSVIEW_CPP
#define GRAPHICSVIEW_CPP

#include <graphicFigures/GraphicsScene.h>

void GraphicsScene::ScreenResize(int width, int height)
{
    this->setSceneRect(0, 0, width - 15, height - 40);
    qDebug() << "Width: " << this->width() << ", Height: " << this->height();
    qDebug() << "Width: " << width << ", Height: " << height;
}

void GraphicsScene::addItem(QGraphicsItem* gr_obj) {
    QGraphicsScene::addItem(gr_obj);
}

void GraphicsScene::addItem(geli::Graph* gr_obj) {
    gr_obj->add_subobjects_to_scene();
}

#endif // GRAPHICSVIEW_CPP
