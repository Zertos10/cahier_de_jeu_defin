#ifndef ITEMTOKENCREATION_H
#define ITEMTOKENCREATION_H

#include "itemcreationscene.h"
#include <QPainter>
#include <qdebug.h>

class ItemTokenCreation: public ItemCreationScene
{
public:
    ItemTokenCreation(QRectF* frame,QGraphicsItem *parent = nullptr);
    void createToken();
    QGraphicsItem* getToken();

protected:

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QRectF *frame;
    QPolygonF polygonToken;

};

#endif // ITEMTOKENCREATION_H
