#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

class GraphicsView : public QGraphicsView {
public:
  GraphicsView(QGraphicsScene *scene) : QGraphicsView(scene) {}

protected:
  void resizeEvent(QResizeEvent *) override {}

};


#endif
