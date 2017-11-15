#include <QtWidgets>
#include "./include/GraphicsView.h"
#include "./include/EventItem.h"

#include <math.h>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  /*
    I believe that the graphics scene provides all information on what needs to be drawn.
  */
  QGraphicsScene scene(-100, -100, 600, 400);

  for (int i = 0; i < 10; ++i) {
    EventItem *item = new EventItem;
    int horPos = i * 35;
    item->setPos(horPos, 100);
    item->setOriginalPos(horPos, 100);
    scene.addItem(item);
  }
  
  /* 
     So the graphics view seems to be an object that provides a viewport.
  */
  GraphicsView view(&scene);
  view.setBackgroundBrush(QColor(230, 200, 167)); // Sets the background colour.
  view.setRenderHint(QPainter::Antialiasing);
  view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  view.setWindowTitle("Graphics Test");
  view.show();

  return app.exec();
}
