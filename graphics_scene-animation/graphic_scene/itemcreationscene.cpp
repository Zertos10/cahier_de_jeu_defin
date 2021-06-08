#include "itemcreationscene.h"


ItemCreationScene::ItemCreationScene(QGraphicsItem *parent):QGraphicsObject(parent)
{

}




void ItemCreationScene::setColorItem(QString color)
{
 QBrush *colorPen = new QBrush();
 colorPen->setColor(*new QColor(color));

}







