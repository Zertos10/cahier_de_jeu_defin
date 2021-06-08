#ifndef ITEMLINETEMPCREATION_H
#define ITEMLINETEMPCREATION_H

#include "itemcreationscene.h"
#include <QPainter>
#include <qdebug.h>

class ItemLineTempCreation: public ItemCreationScene
{
public:
    ItemLineTempCreation();
    void createLine();


private:
    QVector<QGraphicsLineItem> linesTempo;
};

#endif // ITEMLINETEMPCREATION_H
