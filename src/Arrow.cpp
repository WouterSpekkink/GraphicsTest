#include "../include/Arrow.h"
#include <math.h>

#include <QPen>
#include <QPainter>
#include <QtCore>

const qreal Pi = 3.14;

Arrow::Arrow(EventItem *startItem, EventItem *endItem, int submittedHeight, QGraphicsItem *parent)
  : QGraphicsLineItem(parent) {
  start = startItem;
  end = endItem;
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  color = Qt::black;
  setPen(QPen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  height = submittedHeight;
}

QRectF Arrow::boundingRect() const {
  qreal extra = (pen().width() + height + 20) / 2.0;
  
  return QRectF(start->pos(), QSizeF(end->pos().x() - start->pos().x(),
				     end->pos().y() - start->pos().y()))
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

  // Let us first calculate the distance between our two points.
  qreal xDiff = end->pos().x() - start->pos().x();
  qreal yDiff = end->pos().y() - start->pos().y();

  qreal distance = sqrt(pow(xDiff, 2) + pow(yDiff, 2));

  // Then we draw two new points that are on a horizontal line.
  // This makes it easier to draw a control point perpendicular to the line.
  QPointF tempStart = QPointF(0, 0);
  QPointF tempEnd = QPointF(distance, 0);

  // Calculate midpoint
  qreal mX = (tempStart.x() + tempEnd.x()) / 2;
  qreal mY = (tempStart.y() + tempEnd.y()) / 2;
  QPointF midPoint = QPointF(mX, mY);
  midPoint.setY(midPoint.y() + height);

  // Calculate point between midPoint and end of line.
  qreal mX2 = (midPoint.x() + tempEnd.x()) / 2;
  qreal mY2 = (midPoint.y() + tempEnd.y()) / 2;
  QPointF stopPoint = QPointF(mX2, mY2);

  // Calculate point between last point and end of line.
  qreal mX3 = (stopPoint.x() + tempEnd.x()) / 2;
  qreal mY3 = (stopPoint.y() + tempEnd.y()) / 2;
  QPointF endPoint = QPointF(mX3, mY3);
  
  // Offset height of endPoint.
  // need to find a better solution for this.
  //  if (height == 80) {
  endPoint.setY(endPoint.y() - 2);
  //  } else if (height == 60) {
    endPoint.setY(endPoint.y() - 6);
    //  }

  QLineF newLine = QLineF(tempStart, tempEnd);
  setLine(newLine);

  // But then we still need to rotate and translate the painter such that it draws
  // the line between the correct points. 
  qreal dY = end->pos().y() - start->pos().y();
  qreal dX = end->pos().x() - start->pos().x();
  
  // theta is initially the angle in radians, so we convert it to degrees.
  qreal theta = atan2(dY, dX);
  //  qreal angle = theta;
  theta = qRadiansToDegrees(theta);

  QLineF oLine = QLineF(midPoint, tempEnd);
  if (oLine.length() <= 18) {
    oLine = QLineF(midPoint, tempEnd);
  }
  oLine.setLength(oLine.length() - 18);
  
  double angle = ::acos(oLine.dx() / oLine.length());
  if (oLine.dy() >= 0)
    angle = (Pi * 2) - angle;

  qreal arrowSize = 10;
  
  QPointF arrowP1 = oLine.p2() - QPointF(sin(angle + Pi /3) * arrowSize,
    cos(angle + Pi / 3) * arrowSize);
  QPointF arrowP2 = oLine.p2() - QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
  cos(angle + Pi - Pi / 3) * arrowSize);

  arrowHead.clear();
  arrowHead << oLine.p2() << arrowP1 << arrowP2;

  QPainterPath myPath;
  myPath.moveTo(tempStart);
  myPath.quadTo(midPoint, oLine.p2());
  painter->translate(start->pos() - tempStart);
  painter->rotate(theta);
  painter->drawPolygon(arrowHead);
  painter->strokePath(myPath, QPen(color));
  painter->strokePath(myPath, QPen(color));
  if (isSelected()) {
    painter->setPen(QPen(color, 1, Qt::DashLine));
    QLineF myLine = line();
    myLine.translate(0, 4.0);
    painter->drawLine(myLine);
    myLine.translate(0,-8.0);
    painter->drawLine(myLine);
  }
}
