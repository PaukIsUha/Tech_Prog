#include <viewItems/move_node.hpp>

QGraphicsScene* viewItem::moveNode::scene = nullptr;

void viewItem::moveNode::setScene(QGraphicsScene *other_scene) {
    scene = other_scene;
}

QGraphicsScene* viewItem::moveNode::getScene() {
    return scene;
}

viewItem::moveNode::moveNode(const moveNode& new_node) : viewItem::moveNode::moveNode() {
    this->scene = new_node.scene;
}

viewItem::moveNode::moveNode()
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    //position = new QPointF();
}

QRectF viewItem::moveNode::boundingRect() const
{
    return QRectF(-POINT_SIZE / 2, -POINT_SIZE / 2, POINT_SIZE, POINT_SIZE);
}

void viewItem::moveNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(OUT_CONTRE_NODE);
    painter->setBrush(OUT_LINE_NODE);
    painter->drawEllipse(-POINT_SIZE / 2, -POINT_SIZE / 2, POINT_SIZE, POINT_SIZE);
    painter->setPen(INSIDE_CONTRE_NODE);
    painter->setBrush(INSIDE_LINE_NODE);
    painter->drawEllipse(-POINT_SIZE / 2.5, -POINT_SIZE / 2.5, POINT_SIZE * 2 / 2.5, POINT_SIZE * 2 / 2.5);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void viewItem::moveNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->scene->update();
    QPointF cur_pnt = mapToScene(event->pos());
    if(cur_pnt.rx() < 0.0) {
        cur_pnt.setX(0);
    }
    if (cur_pnt.ry() < 3.0) {
        cur_pnt.setY(3);
    }
    if(cur_pnt.rx() > this->scene->width() - 0.0) {
        cur_pnt.setX(this->scene->width() - 0.0);
    }
    if (cur_pnt.ry() > this->scene->height() - 3.0) {
        cur_pnt.setY(this->scene->height() - 3.0);
    }
    this->setPos(cur_pnt);
}

void viewItem::moveNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void viewItem::moveNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */

    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

std::vector<QPointF> viewItem::vector_pos(const std::vector<moveNode*>& m_nodes)
{
    std::vector<QPointF> qt_points(m_nodes.size());
    for (size_t i = 0; i < m_nodes.size(); ++i)
        qt_points[i] = m_nodes[i]->pos();
    return qt_points;
}
