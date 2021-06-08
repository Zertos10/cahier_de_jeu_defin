#ifndef ITEMFRAMECREATION_H
#define ITEMFRAMECREATION_H

#include "itemcreationscene.h"
#include <QPainter>
#include <qdebug.h>

class itemFrameCreation: public ItemCreationScene
{
public:
    itemFrameCreation(int compt,QGraphicsItem *parent = nullptr);

    QRectF* getRec();
protected:

 QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    QRectF* frameRec = new QRectF();
    int compt;

};

#endif // ITEMFRAMECREATION_H
