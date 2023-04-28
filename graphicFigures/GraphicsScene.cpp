
#ifndef GRAPHICSVIEW_CPP
#define GRAPHICSVIEW_CPP

#include <graphicFigures/GraphicsScene.h>

void GraphicsScene::ScreenResize(int width, int height)
{
    this->setSceneRect(0, 0, width - 15, height - 40);
    qDebug() << "Width: " << this->width() << ", Height: " << this->height();
    qDebug() << "Width: " << width << ", Height: " << height;
}

bool GraphicsScene::getDevStatus() {
    return this->developing_status;
}

void GraphicsScene::setDevStatus(bool status) {
    this->developing_status = status;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (this->getDevStatus()) {
        if (event->button() == Qt::LeftButton) {
            qDebug() << "developing";
        } else if (event->button() == Qt::RightButton) {
            qDebug() << "Done";
            this->setDevStatus(false);
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}

#endif // GRAPHICSVIEW_CPP
