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

  EventItem *itemOne = new EventItem(100);
  int horPos = 1 * 35;
  itemOne->setPos(horPos, 100);
  itemOne->setOriginalPos(horPos, 100);
  scene.addItem(itemOne);

  EventItem *itemTwo = new EventItem(300);
  horPos = 5 * 35;
  itemTwo->setPos(horPos, 100);
  itemTwo->setOriginalPos(horPos, 100);
  scene.addItem(itemTwo);

  EventItem *itemThree = new EventItem(30);
  horPos = 30 * 35;
  itemThree->setPos(horPos, 100);
  itemThree->setOriginalPos(horPos, 100);
  scene.addItem(itemThree);

  EventItem *itemFour = new EventItem(100);
  horPos = 1 * 35;
  itemFour->setPos(horPos, 0);
  itemFour->setOriginalPos(horPos, 0);
  scene.addItem(itemFour);

  EventItem *itemFive = new EventItem(300);
  horPos = 5 * 35;
  itemFive->setPos(horPos, 0);
  itemFive->setOriginalPos(horPos, 0);
  scene.addItem(itemFive);

  EventItem *itemSix = new EventItem(30);
  horPos = 30 * 35;
  itemSix->setPos(horPos, 0);
  itemSix->setOriginalPos(horPos, 0);
  scene.addItem(itemSix);

  
  //  Arrow *line = new Arrow(itemOne, itemTwo);
  //Arrow *line2 = new Arrow(itemTwo, itemThree);

  Arrow *line = new Arrow(itemTwo, itemOne);
  Arrow *line2 = new Arrow(itemThree, itemTwo);

  Arrow *line3 = new Arrow(itemFour, itemFive);
  Arrow *line4 = new Arrow(itemFive, itemSix);

  
  scene.addItem(line);
  scene.addItem(line2);

  scene.addItem(line3);
  scene.addItem(line4);
    
  itemOne->setZValue(1);
  itemTwo->setZValue(1);
  itemThree->setZValue(1);
  itemFour->setZValue(1);
  itemFive->setZValue(1);
  itemSix->setZValue(1);

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
