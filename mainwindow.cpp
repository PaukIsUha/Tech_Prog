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

    //scene->setSceneRect(0, 0, ui->graphicsView->geometry().width() - 100, ui->graphicsView->geometry().height() - 100);
    QRect rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    //ui->graphicsView->resize(_width_, _height_);  // Устанавливаем размер graphicsView
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(0, 0, _width_, _height_); // Устанавливаем размер сцены

    QColor start_color(70, 130, 180, 255);
    QColor end_color(39, 163, 144, 255);
    QLinearGradient m_gradient(0, 0, ui->graphicsView->geometry().width(), ui->graphicsView->geometry().height());

    m_gradient.setColorAt(0.0, start_color);
    m_gradient.setColorAt(1.0, end_color);

    scene->setBackgroundBrush(m_gradient);

    move_node::moveNode *item = new move_node::moveNode();        // Создаём графический элемента
    item->setPos(100, 200);
    scene->addItem(item);   // Добавляем элемент на графическую сцену

    //repaint();
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
