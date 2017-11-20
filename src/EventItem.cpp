#include <QtWidgets>
#include "../include/EventItem.h"
#include "../include/Arrow.h"

/*
  In this case we assign a random colour. I will want to change that
  in real applications.
*/

EventItem::EventItem(int subWidth) : color(255, 255, 255) {
  width = subWidth;

  setToolTip("This could be an event");
  setCursor(Qt::OpenHandCursor);
  setAcceptedMouseButtons(Qt::LeftButton);
  //  setFlag(QGraphicsItem::ItemIsSelectable);
  //  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges);
  originalPos = QPointF(0, 0);
  previousPos = originalPos;
}

/*
  I assume that this is for collision or
  selection purposes?
*/

QRectF EventItem::boundingRect() const {
  return QRectF(-15.5, -15.5, width + 4, 34);
}

void EventItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  painter->setPen(Qt::NoPen);
  painter->setPen(QPen(Qt::black, 1));
  painter->setBrush(QBrush(color));
  painter->drawEllipse(-15, -15, width, 30);
}

// Only to set the cursor to a different graphic.
void EventItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  previousPos = event->scenePos();
  setCursor(Qt::ClosedHandCursor);
}

void EventItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  QPointF newPos = event->scenePos();
  qreal x = newPos.x();
  qreal y = newPos.y();
  bool trespass = false;

  for (int i = 0; i < scene()->items().count(); i++) {
    QGraphicsItem *item = scene()->items()[i];
    EventItem *currentItem = qgraphicsitem_cast<EventItem*>(item);
    Arrow *no = qgraphicsitem_cast<Arrow*>(item);
    if (currentItem && !(no) && item != this) {
      int dist = qSqrt(qPow(currentItem->pos().x()-x,2)+qPow(currentItem->pos().y()-y,2));
      if (dist <= 40) {
	trespass = true;
      } else {
	previousPos = this->scenePos();
      }
    }
  }
  if (trespass) {
    this->setPos(previousPos);
  } else {
    this->setPos(newPos);
  }
  setCursor(Qt::OpenHandCursor);
}

void EventItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)  {
  QPointF newPos = event->scenePos();
  qreal x = newPos.x();
  qreal y = newPos.y();

  bool trespass = false;
   for (int i = 0; i < scene()->items().count(); i++) {
    QGraphicsItem *item = scene()->items()[i];
    EventItem *currentItem = qgraphicsitem_cast<EventItem*>(item);
    Arrow *no = qgraphicsitem_cast<Arrow*>(item);
    if (currentItem && !(no) && item != this) {
      int dist = qSqrt(qPow(currentItem->pos().x()-x,2)+qPow(currentItem->pos().y()-y,2));
      if (dist <= 40) {
	trespass = true;
      } else {
	previousPos = this->scenePos();
      }
    }
  }
  if (trespass) {
    this->setPos(previousPos);
  } else {
    this->setPos(newPos);
  }
  setCursor(Qt::OpenHandCursor);
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}

void EventItem::setOriginalPos(qreal x, qreal y) {
  originalPos = QPointF(x, y);
}

int EventItem::getCorrection() {
  return width - 29;
}


