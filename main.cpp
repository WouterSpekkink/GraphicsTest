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
  itemOne->setPos(horPos, 0);
  itemOne->setOriginalPos(horPos, 100);
  scene.addItem(itemOne);

  EventItem *itemTwo = new EventItem(30);
  horPos = 15 * 35;
  itemTwo->setPos(horPos, 200);
  itemTwo->setOriginalPos(horPos, 100);
  scene.addItem(itemTwo);

  EventItem *itemThree = new EventItem(30);
  horPos = 15 * 35;
  itemThree->setPos(horPos, 400);
  itemThree->setOriginalPos(horPos, 100);
  scene.addItem(itemThree);

  EventItem *itemFour = new EventItem(30);
  horPos = 10 * 35;
  itemFour->setPos(horPos, 200);
  itemFour->setOriginalPos(horPos, 100);
  scene.addItem(itemFour);

  Arrow *line = new Arrow(itemOne, itemTwo, 80);
  Arrow *line2 = new Arrow(itemFour, itemThree, 0);
  Arrow *line3 = new Arrow(itemFour, itemThree, 80);
  line3->setColor(Qt::darkRed);
  Arrow *line4 = new Arrow(itemFour, itemThree, 160);
  line4->setColor(Qt::darkBlue);
  Arrow *line5 = new Arrow(itemFour, itemThree, 240);
  line5->setColor(Qt::darkGreen);
  
  
  scene.addItem(line);
  scene.addItem(line2);
  scene.addItem(line3);
  scene.addItem(line4);
  scene.addItem(line5);
  
  itemOne->setZValue(1);
  itemTwo->setZValue(1);
  itemThree->setZValue(1);
  itemFour->setZValue(1);

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
