#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QtGui>
#include <QDebug>
#include <QApplication>
#include <QPushButton>
#include <QSpinBox>
#include <viewItems/grid.hpp>
#include <graphicFigures/geli/poly_line.hpp>
#include <graphicFigures/GraphicsScene.h>
#include <viewItems/area2d_view.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define DARK_SIDE_BACKGROUND QColor(78, 78, 78, 255)
#define MIDDLE_SIDE_BACKGROUND QColor(68, 68, 68, 255)
#define LIGHT_SIDE_BACKGROUND QColor(58, 58, 58, 255)
#define COG_X 250
#define COG_Y 283
#define R_FIGURE 150

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
    void add_button_clicked();
    QRadialGradient getGradient() const;

    size_t slizer = 0;
    Ui::MainWindow *ui;
    GraphicsScene *scene;
    viewItem::area2d_view *intersect_area;
    QSpinBox *__count_angle__;

};

void setDefaultStyleSheetButton(QPushButton* button);
#define setDSSB(button) setDefaultStyleSheetButton(button)

#endif // MAINWINDOW_H
