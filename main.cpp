#include <QtWidgets>
#include "./include/GraphicsView.h"
#include "./include/EventItem.h"
#include "./include/Arrow.h"

#include <math.h>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  /*
    I believe that the graphics scene provides all information on what needs to be drawn.
  */
  QGraphicsScene scene(-100, -100, 600, 400);

  /*  for (int i = 0; i < 10; ++i) {
    EventItem *item = new EventItem;
    int horPos = i * 35;
    item->setPos(horPos, 100);
    item->setOriginalPos(horPos, 100);
    scene.addItem(item);
    }*/

  EventItem *itemOne = new EventItem;
  int horPos = 1 * 35;
  itemOne->setPos(horPos, 100);
  itemOne->setOriginalPos(horPos, 100);
  scene.addItem(itemOne);

  EventItem *itemTwo = new EventItem;
  horPos = 5 * 35;
  itemTwo->setPos(horPos, 100);
  itemTwo->setOriginalPos(horPos, 100);
  scene.addItem(itemTwo);

  QPointF start = itemOne->scenePos();
  QPointF end = itemTwo->scenePos();
  
  Arrow *line = new Arrow(itemOne, itemTwo);

  scene.addItem(line);
  
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
