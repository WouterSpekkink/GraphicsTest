#include <QtWidgets>
#include "../include/EventItem.h"

/*
  In this case we assign a random colour. I will want to change that
  in real applications.
*/

EventItem::EventItem() : color(qrand() % 256, qrand() % 256, qrand() % 256) {
  setToolTip("This could be an event");
  setCursor(Qt::OpenHandCursor);
  setAcceptedMouseButtons(Qt::LeftButton);
  //  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges);
  originalPos = QPointF(0, 0);
}

/*
  I assume that this is for collision or
  selection purposes?
*/

QRectF EventItem::boundingRect() const {
  return QRectF(-15.5, -15.5, 34, 34);
}

void EventItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::darkGray);
  painter->drawEllipse(-12, -12, 30, 30);
  painter->setPen(QPen(Qt::black, 1));
  painter->setBrush(QBrush(color));
  painter->drawEllipse(-15, -15, 30, 30);
}

// Only to set the cursor to a different graphic.
void EventItem::mousePressEvent(QGraphicsSceneMouseEvent *) {
    setCursor(Qt::ClosedHandCursor);
}

void EventItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsItem::mouseMoveEvent(event);
  setCursor(Qt::OpenHandCursor);
}

void EventItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)  {
  qreal oldX = originalPos.x();
  QPointF newPos = event->scenePos();
  newPos.setX(oldX);
  this->setPos(newPos);
  update();
  //  QGraphicsItem::itemChange(ItemPositionChange, newPos);
  //this->itemChange(ItemPositionChange, value.toPointF().
  QGraphicsItem::mouseReleaseEvent(event);
}

void EventItem::setOriginalPos(qreal x, qreal y) {
  originalPos = QPointF(x, y);
}
