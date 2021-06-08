#include "itemtokencreation.h"

ItemTokenCreation::ItemTokenCreation(QRectF *frame, QGraphicsItem *parent):ItemCreationScene(parent),frame(frame)
{

    polygonToken << QPoint(-35+frame->x() ,0+frame->y()) <<QPoint(0+frame->x(),35+frame->y()) <<QPoint(35+frame->x(),0+frame->y())
                 <<QPoint(0+frame->x(),-35+frame->y());
    qDebug() <<"Taille Polygon" <<polygonToken;
   this->setPos(10,0);
    qDebug() << "createToken playerToken";

   this->setFlag(this->ItemIsMovable);
}

QRectF ItemTokenCreation::boundingRect() const
{
    qreal penWidth = 1;

       return QRectF(-20 - penWidth / 2, -20 - penWidth / 2,
                     40 + penWidth, 40 + penWidth);
}


void ItemTokenCreation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    qDebug()<< "creationToken";
    painter->drawPolygon(polygonToken);

}


