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
  QGraphicsScene scene(0);

  EventItem *itemOne = new EventItem(30);
  int horPos = 1 * 35;
  itemOne->setPos(horPos, 200);
  itemOne->setOriginalPos(horPos, 100);
  scene.addItem(itemOne);

<<<<<<< HEAD
  EventItem *itemTwo = new EventItem(30);
  horPos = 10 * 35;
  itemTwo->setPos(horPos, 100);
=======
  EventItem *itemTwo = new EventItem(300);
  horPos = 5 * 35;
  itemTwo->setPos(horPos, 200);
>>>>>>> ab7fa3c3eccd5be947b04d773e6d69aed8e50531
  itemTwo->setOriginalPos(horPos, 100);
  scene.addItem(itemTwo);

  EventItem *itemThree = new EventItem(30);
  horPos = 30 * 35;
  itemThree->setPos(horPos, 200);
  itemThree->setOriginalPos(horPos, 100);
  scene.addItem(itemThree);

  EventItem *itemFour = new EventItem(30);
  horPos = 1 * 35;
  itemFour->setPos(horPos, 400);
  itemFour->setOriginalPos(horPos, 0);
  scene.addItem(itemFour);

<<<<<<< HEAD
  EventItem *itemFive = new EventItem(30);
  horPos = 10 * 35;
  itemFive->setPos(horPos, 0);
=======
  EventItem *itemFive = new EventItem(300);
  horPos = 5 * 35;
  itemFive->setPos(horPos, 400);
>>>>>>> ab7fa3c3eccd5be947b04d773e6d69aed8e50531
  itemFive->setOriginalPos(horPos, 0);
  scene.addItem(itemFive);

  EventItem *itemSix = new EventItem(30);
  horPos = 30 * 35;
  itemSix->setPos(horPos, 400);
  itemSix->setOriginalPos(horPos, 0);
  scene.addItem(itemSix);

  EventItem *itemSeven = new EventItem(30);
  horPos = 5 * 35;
  itemSeven->setPos(horPos, 100);
  itemSeven->setOriginalPos(horPos, 0);
  scene.addItem(itemSeven);
  
  
  //  Arrow *line = new Arrow(itemOne, itemTwo);
  //Arrow *line2 = new Arrow(itemTwo, itemThree);

  Arrow *line = new Arrow(itemTwo, itemOne);
  Arrow *line2 = new Arrow(itemThree, itemTwo);

  Arrow *line3 = new Arrow(itemFour, itemFive);
  Arrow *line4 = new Arrow(itemFive, itemSix);

  Arrow *line5 = new Arrow(itemSeven, itemOne);
  
  scene.addItem(line);
  scene.addItem(line2);

  scene.addItem(line3);
  scene.addItem(line4);

  scene.addItem(line5);
  
  itemOne->setZValue(1);
  itemTwo->setZValue(1);
  itemThree->setZValue(1);
  itemFour->setZValue(1);
  itemFive->setZValue(1);
  itemSix->setZValue(1);

  itemSeven->setZValue(1);
  QRectF currentRect = scene.itemsBoundingRect();
  currentRect.setX(currentRect.x() - 50);
  currentRect.setY(currentRect.y() - 50);
  currentRect.setWidth(currentRect.width() + 100);
  currentRect.setHeight(currentRect.height() + 100);
  scene.setSceneRect(currentRect);
  
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
