#include "mainwindow.h"
#include "Geli.hpp"
#include "GraphicsScene.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QDebug>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR","1");
    ui->setupUi(this);


    scene = new GraphicsScene();   // Инициализируем графическую сцену
    scene->setItemIndexMethod(GraphicsScene::NoIndex); // настраиваем индексацию элементов

    connect(this, &MainWindow::resized, scene, &GraphicsScene::ScreenResize);

    viewItem::moveNode::setScene(scene);
    scene->setSceneRect(0, 0, ui->graphicsView->geometry().width(), ui->graphicsView->geometry().height());

    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCentralWidget(ui->graphicsView);
//    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    scene->setBackgroundBrush(getGradient());
    dataNodes pps;

    // TRIANGLE I
    pps.push_back(std::vector<viewItem::moveNode *>());

    viewItem::moveNode *T1node1 = new viewItem::moveNode();        // Создаём узел (Треугольник 1, точка 1)
    T1node1->setPos(100, 400);
    viewItem::moveNode *T1node2 = new viewItem::moveNode();        // Создаём узел (Треугольник 1, точка 2)
    T1node2->setPos(400, 350);
    viewItem::moveNode *T1node3 = new viewItem::moveNode();        // Создаём узел (Треугольник 1, точка 3)
    T1node3->setPos(250, 200);

    pps[0].push_back(T1node1);
    pps[0].push_back(T1node2);
    pps[0].push_back(T1node3);

    scene->addItem(T1node1);   // Добавляем элемент на графическую сцену
    scene->addItem(T1node2);   // Добавляем элемент на графическую сцену
    scene->addItem(T1node3);   // Добавляем элемент на графическую сцену

    viewItem::edge *T1edge1 = new viewItem::edge(T1node1, T1node2); // Создаём сторону между T1node1 T1node2
    viewItem::edge *T1edge2 = new viewItem::edge(T1node2, T1node3); // Создаём сторону между T1node2 T1node3
    viewItem::edge *T1edge3 = new viewItem::edge(T1node1, T1node3); // Создаём сторону между T1node1 T1node3
    scene->addItem(T1edge1);
    scene->addItem(T1edge2);
    scene->addItem(T1edge3);

    // TRIANGLE II
    pps.push_back(std::vector<viewItem::moveNode *>());

    viewItem::moveNode *T2node1 = new viewItem::moveNode();        // Создаём узел (Треугольник 2, точка 1)
    T2node1->setPos(175, 350);
    viewItem::moveNode *T2node2 = new viewItem::moveNode();        // Создаём узел (Треугольник 2, точка 2)
    T2node2->setPos(500, 400);
    viewItem::moveNode *T2node3 = new viewItem::moveNode();        // Создаём узел (Треугольник 2, точка 3)
    T2node3->setPos(500, 190);

    pps[1].push_back(T2node1);
    pps[1].push_back(T2node2);
    pps[1].push_back(T2node3);

    scene->addItem(T2node1);   // Добавляем элемент на графическую сцену
    scene->addItem(T2node2);   // Добавляем элемент на графическую сцену
    scene->addItem(T2node3);   // Добавляем элемент на графическую сцену

    viewItem::edge *T2edge1 = new viewItem::edge(T2node1, T2node2); // Создаём сторону между T1node1 T1node2
    viewItem::edge *T2edge2 = new viewItem::edge(T2node2, T2node3); // Создаём сторону между T1node2 T1node3
    viewItem::edge *T2edge3 = new viewItem::edge(T2node1, T2node3); // Создаём сторону между T1node1 T1node3
    T2edge1->setColor(EDGE_COLOR_1);
    T2edge2->setColor(EDGE_COLOR_1);
    T2edge3->setColor(EDGE_COLOR_1);
    scene->addItem(T2edge1);
    scene->addItem(T2edge2);
    scene->addItem(T2edge3);

    viewItem::area2d_view *intersection = new viewItem::area2d_view(pps);
    intersection->setScene(scene);
    scene->addItem(intersection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    Q_UNUSED(event);
//    QPainter painter(ui->graphicsView); // Создаём объект отрисовщика
//    // Устанавливаем кисть абриса
////    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));

////    /* Проверяем, какой из радиобаттонов выбран
////     * */
////    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
////    painter.drawEllipse(100, 50, 150, 150);
////    ui->graphicsView->

//    auto _width_ = geometry().width();
//    auto _height_ = geometry().height();


//    QColor start_color(70, 130, 180, 255);
//    QColor end_color(39, 163, 144, 255);
//    QLinearGradient m_gradient(0, 0, _width_, _height_);

//    m_gradient.setColorAt(0.0, start_color);
//    m_gradient.setColorAt(1.0, end_color);
//    painter.fillRect(0, 0, _width_, _height_, m_gradient);

//    move_node::moveNode* node = new move_node::moveNode(this);
//    node->setPos(50, 50);
    //    node->paint(&painter);
    Q_UNUSED(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    emit MainWindow::resized(event->size().width(), event->size().height());
}

void MainWindow::ScreenResize(int width, int height)
{
    qDebug() << "Width: " << width << ", Height: " << height;
}

QLinearGradient MainWindow::getGradient() const
{
    QLinearGradient m_gradient(0, 0, ui->graphicsView->geometry().width(), ui->graphicsView->geometry().height());
    m_gradient.setColorAt(0.0, DARK_SIDE_BACKGROUND);
    m_gradient.setColorAt(1.0, LIGHT_SIDE_BACKGROUND);
    return m_gradient;
}
