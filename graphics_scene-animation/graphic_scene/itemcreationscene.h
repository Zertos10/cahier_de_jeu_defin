#ifndef ITEMCREATIONSCENE_H
#define ITEMCREATIONSCENE_H

#include <QGraphicsObject>
#include <QPainter>
#include <qdebug.h>

enum Type{Frame,Token,Line};

class ItemCreationScene : public QGraphicsObject
{
    Q_OBJECT
public:
    ItemCreationScene(QGraphicsItem *parent = Q_NULLPTR);


protected:


     QBrush getColor();
     void setColorItem(QString color);


   QGraphicsScene *scene;
   const int geometry = 250;
   int compt = 0;
   QBrush brush;



};

#endif // ITEMCREATIONSCENE_H
