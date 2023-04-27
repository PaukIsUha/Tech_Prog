#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <area2d_view.hpp>
#include "GraphicsScene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define DARK_SIDE_BACKGROUND QColor(70, 130, 180, 255)
#define LIGHT_SIDE_BACKGROUND QColor(39, 163, 144, 255)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
signals:
    void resized(int width, int height);

public slots:
    void ScreenResize(int width, int height);

private slots:

private:
    QLinearGradient getGradient() const;
    Ui::MainWindow *ui;
    GraphicsScene *scene;
};
#endif // MAINWINDOW_H
