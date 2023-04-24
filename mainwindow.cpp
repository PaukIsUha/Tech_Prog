#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов

    auto _width_ = geometry().width();
    auto _height_ = geometry().height();

//    scene->setSceneRect(0, 0, ui->graphicsView->geometry().width(), ui->graphicsView->geometry().height());
    scene->setSceneRect(0, 0, _width_, _height_); // Устанавливаем размер сцены
    QRect rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    //ui->graphicsView->resize(_width_, _height_);  // Устанавливаем размер graphicsView
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    QColor start_color(70, 130, 180, 255);
    QColor end_color(39, 163, 144, 255);
    QLinearGradient m_gradient(0, 0, ui->graphicsView->geometry().width(), ui->graphicsView->geometry().height());

    m_gradient.setColorAt(0.0, start_color);
    m_gradient.setColorAt(1.0, end_color);

    scene->setBackgroundBrush(m_gradient);

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
    QColor clr_T2_edges(205, 92, 92, 255);
    T2edge1->setColor(clr_T2_edges);
    T2edge2->setColor(clr_T2_edges);
    T2edge3->setColor(clr_T2_edges);
    scene->addItem(T2edge1);
    scene->addItem(T2edge2);
    scene->addItem(T2edge3);

    viewItem::area2d_view *intersection = new viewItem::area2d_view(pps, width(), height());
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
}
