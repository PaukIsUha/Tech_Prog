#include "move_node.hpp"

move_node::moveNode::moveNode(QPointF* rect, QWidget *_widget)
    : __widget__(_widget),
      position(rect)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    //position = new QPointF();
}

QRectF move_node::moveNode::boundingRect() const
{
    return QRectF(this->pos().x(), this->pos().y(), 10, 10);
}

void move_node::moveNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::lightGray);
    QLinearGradient m_gradient(100,
                               200,
                               10, 10);
    m_gradient.setColorAt(0.0, Qt::red);
    m_gradient.setColorAt(1.0, Qt::blue);
    painter->setBrush(m_gradient);
    painter->drawEllipse(100, 200, 10, 10);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void move_node::moveNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    //this->position = QRectF(event->pos(), position.size());
    this->setPos(mapToScene(event->pos()));
}

void move_node::moveNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void move_node::moveNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
