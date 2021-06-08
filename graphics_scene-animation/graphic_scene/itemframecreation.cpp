#include "itemcreationscene.h"
#include "itemframecreation.h"

itemFrameCreation::itemFrameCreation(int compt, QGraphicsItem* parent):ItemCreationScene(parent),compt(compt)
{
    qDebug() <<"compteur Frame:" <<compt;
     frameRec =new QRectF(0,-100+(geometry*compt),1000,250);;
    setColorItem("CC0000");
    this->setPos(0,0);
    qDebug() << "frame create";
}

QRectF *itemFrameCreation::getRec() {return frameRec;}
QRectF itemFrameCreation::boundingRect() const
{
    qreal penWidth = 1;

       return QRectF(-frameRec->x() - penWidth / 2, -frameRec->y() - penWidth / 2,
                     frameRec->width() + penWidth,frameRec->height() + penWidth);
}



void itemFrameCreation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug()<< "creation de frame";
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->setPen(Qt::red);
    painter->drawRect(*frameRec);

}

