#include "../include/GraphicsView.h"

GraphicsView::GraphicsView(QGraphicsScene *scene) : QGraphicsView(scene) {
}

void GraphicsView::resizeEvent(QResizeEvent *) {};

void GraphicsView::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton) {
    pan = true;
    panStartX = event->x();
    panStartY = event->y();
    setCursor(Qt::ClosedHandCursor);
    event->accept();
    return;
  } else {
    QGraphicsView::mousePressEvent(event);
  }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton) {
    pan = false;
    setCursor(Qt::ArrowCursor);
    event->accept();
    return;
  } else {
    QGraphicsView::mouseReleaseEvent(event);
  }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
  if (pan) {
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - panStartX));
    verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - panStartY));
    panStartX = event->x();
    panStartY = event->y();
    event->accept();
    return;
  } else {
    QGraphicsView::mouseMoveEvent(event);
  }
}

void GraphicsView::wheelEvent(QWheelEvent* event) {
  if (event->modifiers() & Qt::ControlModifier) {
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.15;
    if (event->delta() > 0) {
      this->scale(scaleFactor, scaleFactor);
    } else {
      this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
  } else if (event->modifiers() & Qt::ShiftModifier) {
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() - event->delta());
  } else {
    QGraphicsView::wheelEvent(event);
  }
}
