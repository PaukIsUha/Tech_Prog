#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <viewItems/grid.hpp>
//#include <graphicFigures/Geli.hpp>
//#include <viewItems/move_node.hpp>
#include <graphicFigures/GraphicsScene.h>
#include <QtGui>
#include <QDebug>
#include <QApplication>
#include <viewItems/area2d_view.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace viewItem
{
    class area2d_view;
}

#define DARK_SIDE_BACKGROUND QColor(78, 78, 78, 255)
#define MIDDLE_SIDE_BACKGROUND QColor(68, 68, 68, 255)
#define LIGHT_SIDE_BACKGROUND QColor(58, 58, 58, 255)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void add_new_graph(GraphicsScene *scene);
    void setScene(GraphicsScene *other_scene);
    QGraphicsScene* getScene();
    ~MainWindow();
    
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
signals:
    void resized(int width, int height);

private slots:

private:
    void clean_button_clicked();
    QRadialGradient getGradient() const;

    Ui::MainWindow *ui;
    GraphicsScene *scene;
    viewItem::area2d_view *intersect_area;
};

void setDefaultStyleSheetButton(QPushButton* button);
#define setDSSB(button) setDefaultStyleSheetButton(button)

#endif // MAINWINDOW_H
