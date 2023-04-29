#include <mainwindow.h>
#include <ui_mainwindow.h>

void MainWindow::add_new_graph(GraphicsScene *scene) {
    geli::PolyLine *triangle = new geli::PolyLine(scene);
    triangle->add_node(new viewItem::moveNode(400, 400));
    triangle->add_node(new viewItem::moveNode(300, 50));
    triangle->add_node(new viewItem::moveNode(50, 400));
    triangle->close_line();
    intersect_area->push_back_graph(triangle);
}

void MainWindow::clean_button_clicked()
{
    std::vector<geli::Graph*> graphs;
    for (auto item : this->scene->items()) {
        if (dynamic_cast<geli::Graph*>(item)) {
            graphs.push_back(dynamic_cast<geli::Graph*>(item));
        }
    }
    for (auto graph : graphs) {
        this->scene->removeItem(graph);
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

    intersect_area = new viewItem::area2d_view;
    intersect_area->setScene(scene);
    scene->addItem(intersect_area);

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
    QObject::connect(clean_button, &QPushButton::clicked, this, &MainWindow::clean_button_clicked);
    clean_button->move(0, 50);
    scene->addWidget(clean_button); // Добавление кнопки на сцену

    QPushButton *add_graph = new QPushButton("new graph");
    add_graph->setStyleSheet(
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
    QObject::connect(add_graph, &QPushButton::clicked, this, [=](){
        add_new_graph(scene);
    });
    scene->addWidget(add_graph);
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

QRadialGradient MainWindow::getGradient() const
{
    QRadialGradient m_gradient(QPointF(this->width() * 0.75, this->height() * 0.75), this->width() * 0.75);
    m_gradient.setColorAt(0.0, DARK_SIDE_BACKGROUND);
    m_gradient.setColorAt(0.5, MIDDLE_SIDE_BACKGROUND);
    m_gradient.setColorAt(1, LIGHT_SIDE_BACKGROUND);
    return m_gradient;
}

void MainWindow::setScene(GraphicsScene *other_scene) {
    this->scene = other_scene;
}

QGraphicsScene* MainWindow::getScene() {
    return this->scene;
}
