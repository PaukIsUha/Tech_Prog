
#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class GraphicsScene; }  // Не пон что это, но у тебя было также ¯\_(ツ)_/¯
QT_END_NAMESPACE

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public slots:
    void ScreenResize(int width, int height);
};

#endif // GRAPHICSSCENE_H
