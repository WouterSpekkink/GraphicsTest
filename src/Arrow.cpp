#include "../include/Arrow.h"
#include <math.h>

#include <QPen>
#include <QPainter>
#include <QtCore>

const qreal Pi = 3.14;

Arrow::Arrow(EventItem *startItem, EventItem *endItem, QGraphicsItem *parent)
  : QGraphicsLineItem(parent) {
  start = startItem;
  end = endItem;
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  color = Qt::black;
  setPen(QPen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Arrow::boundingRect() const {
  qreal extra = (pen().width() + 40) / 2.0;
  
  return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
				    line().p2().y() - line().p1().y()))
    .normalized()
    .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const {
  QPainterPath path = QGraphicsLineItem::shape();
  path.addPolygon(arrowHead);
  return path;
}

void Arrow::updatePosition() {
  QLineF line(mapFromItem(start, 0, 0), mapFromItem(end, 0, 0));
  setLine(line);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
  if (start->collidesWithItem(end))
    return;

  QPen myPen = pen();
  myPen.setColor(color);
  painter->setPen(myPen);
  painter->setBrush(color);

  QLineF newLine = QLineF();
  
  newLine = QLineF(start->pos(), end->pos());
  newLine.setLength(newLine.length() - 18);
  setLine(newLine);
  
  double angle = ::acos(line().dx() / line().length());
  if (line().dy() >= 0)
    angle = (Pi * 2) - angle;

  qreal yDiff = end->pos().y() - start->pos().y();
  qreal xDiff = end->pos().x() - start->pos().x();

  qreal slope = yDiff/xDiff;
  qreal perpendicular = -1 * (1/slope);
  qDebug() << slope;
  //qDebug() << perpendicular;
  QPointF midPoint = (1-0.5) * QPointF(start->pos()) + 0.5 * QPointF(end->pos());
  if (slope == 0) {
    midPoint.setY(midPoint.y() + 40);
  } else {
    midPoint.setY(midPoint.y() - 60 * slope);
  }
  
  QPainterPath myPath;
  myPath.moveTo(start->pos());
  myPath.quadTo(midPoint, end->pos());
  painter->strokePath(myPath, QPen(Qt::black));
  if (isSelected()) {
    painter->setPen(QPen(color, 1, Qt::DashLine));
    QLineF myLine = line();
    myLine.translate(0, 4.0);
    painter->drawLine(myLine);
    myLine.translate(0,-8.0);
    painter->drawLine(myLine);
  }
}
