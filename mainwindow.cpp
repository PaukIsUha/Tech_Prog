#include "mainwindow.h"
#include "Geli.hpp"
#include "move_node.hpp"
#include "GraphicsScene.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QDebug>
#include <QApplication>

void clean_button_clicked()
{
    qDebug() << "CLICK" << geli::Graph::get_graphs_db().size();
    for (auto &graph : geli::Graph::get_graphs_db()) {
        graph->clear();
    }
}


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
    geli::Graph::setScene(scene);

    scene->setSceneRect(0, 0, ui->graphicsView->geometry().width(), ui->graphicsView->geometry().height());

    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCentralWidget(ui->graphicsView);

    scene->setBackgroundBrush(getGradient());
    viewItem::grid *Grid = new viewItem::grid(scene);
    scene->addItem(Grid);

    dataNodes pps;

    // TRIANGLE test
    std::vector<QPointF*> tr0_points = {
        new QPointF(100, 200),
        new QPointF(200, 300),
        new QPointF(300, 300),
//        new QPointF(300, 200),
//        new QPointF(200, 100)
    };
    geli::Graph *tr0 = new geli::Graph(tr0_points);
    scene->addItem(tr0);

    std::vector<QPointF*> tr1_points = {
        new QPointF(150, 500),
        new QPointF(0, 0),
        new QPointF(500, 150)
    };
    geli::Graph *tr1 = new geli::Graph(tr1_points);
    scene->addItem(tr1);

    std::vector<QPointF*> tr2_points = {
        new QPointF(700, 800),
        new QPointF(800, 800),
        new QPointF(700, 900),
//        new QPointF(900, 900)
    };
//    geli::Graph *tr2 = new geli::Graph(tr2_points);
//    scene->addItem(tr2);

    pps.push_back(std::vector<viewItem::moveNode*>());
    for (auto el : tr0->get_nodes()) {
        pps[0].push_back(el);
    }

    pps.push_back(std::vector<viewItem::moveNode*>());
    for (auto el : tr1->get_nodes()) {
        pps[1].push_back(el);
    }

    viewItem::area2d_view *area = new viewItem::area2d_view(pps);
    scene->addItem(area);

    QPushButton *clean_button = new QPushButton("clean");
    clean_button->setStyleSheet(
        "QPushButton {"
            "background-color: #2196F3;"
            "color: #FFFFFF;"
            "border: none;"
            "padding: 8px 16px;"
            "font-size: 16px;"
            "border-radius: 20px;"
        "}"

        "QPushButton:hover {"
            "background-color: #1976D2;"
        "}"

        "QPushButton:pressed {"
            "background-color: #0D47A1;"
        "}"
    );
    QObject::connect(clean_button, &QPushButton::clicked, clean_button_clicked);
    scene->addWidget(clean_button); // Добавление кнопки на сцену

//    Область пересечения:
//    viewItem::area2d_view *intersection = new viewItem::area2d_view(pps);
//    intersection->setScene(scene);
//    scene->addItem(intersection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
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

QRadialGradient MainWindow::getGradient() const
{
    QRadialGradient m_gradient(QPointF(this->width() * 0.75, this->height() * 0.75), this->width() * 0.75);
    m_gradient.setColorAt(0.0, DARK_SIDE_BACKGROUND);
    m_gradient.setColorAt(0.5, MIDDLE_SIDE_BACKGROUND);
    m_gradient.setColorAt(1, LIGHT_SIDE_BACKGROUND);
    return m_gradient;
}

