#include <mainwindow.h>
#include <ui_mainwindow.h>

void MainWindow::clean_button_clicked()
{
    intersect_area->clear();
    for (auto item : this->scene->items()) {
        geli::Graph* graph = dynamic_cast<geli::Graph*>(item);
        if (graph) {
            graph->deleteLater();
        }
    }
}

void MainWindow::add_button_clicked()
{
    size_t n = __count_angle__->value();
    double step = 2 * PI / n;
    geli::PolyLine *figure = new geli::PolyLine(scene);
    for (size_t i = 0; i < n; ++i)
    {
        size_t X_coord = R_FIGURE * cos(i * step);
        size_t Y_coord = R_FIGURE * sin(i * step);
        figure->add_node(new viewItem::moveNode(X_coord + COG_X + slizer, Y_coord + COG_Y + slizer));
    }
    figure->close_line();
    intersect_area->push_back_graph(figure);
    slizer += 10;
    slizer %= 200;
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
    setDSSB(clean_button);
    QObject::connect(clean_button, &QPushButton::clicked, this, &MainWindow::clean_button_clicked);
    clean_button->move(0, 50);
    scene->addWidget(clean_button); // Добавление кнопки на сцену

    __count_angle__ = new QSpinBox;
    __count_angle__->setGeometry(0, 4, 40, 40);
    __count_angle__->setMinimum(3);
    __count_angle__->setMaximum(55);
    scene->addWidget(__count_angle__);

    QPushButton *add_graph0 = new QPushButton("Add figure");
    setDSSB(add_graph0);
    QObject::connect(add_graph0, &QPushButton::clicked, this, &MainWindow::add_button_clicked);
    add_graph0->move(40, 5);
    scene->addWidget(add_graph0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete intersect_area;
    delete scene;
    delete __count_angle__;
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

void setDefaultStyleSheetButton(QPushButton* button)
{
    button->setStyleSheet(
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
}
