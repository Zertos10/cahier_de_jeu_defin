#include "graphic_animation.h"


graphic_animation::graphic_animation(QWidget *parent):QGraphicsView(parent)
{
    qDebug() << parent->geometry();
    setGeometry(10,1040-500,1000,500);
    addPlayersTimeLine();
    showScene();

}

void graphic_animation::createFrame()
{
    qDebug() << "createFrame";
    QRectF *frameRec = new QRectF(0,0,100,100);
    frame = new QGraphicsRectItem(*frameRec);
}




void graphic_animation::addPlayersTimeLine()
{
    for(int compt=0;compt<5;compt++)
    {
        qDebug() << "compteur addPlayerTimeLine"<<compt;
        PlayerFrameScene *player = new PlayerFrameScene(compt);
        qDebug() << "ajout a la scene";
        listPlayerItem.append(player);

    }
}
void graphic_animation::createAbsTemps()
{
    QGraphicsItemGroup* itemTimeLine = new QGraphicsItemGroup();
    for(int tensecondCompt =0;tensecondCompt<50;tensecondCompt++)
    {
        QLine lineTenSecond(QPoint(tensecondCompt*50,0),QPoint(tensecondCompt*50,20));
        itemTimeLine->addToGroup(new QGraphicsLineItem(lineTenSecond));

    }
    itemTimeLine->setPos(0,0);
    scene.addItem(itemTimeLine);

}
void graphic_animation::showScene()
{
    setRenderHint(QPainter::Antialiasing);
    qDebug() <<"showScene()";
    qDebug() << "size :" << listPlayerItem.size();
    for(PlayerFrameScene* item : qAsConst(listPlayerItem))
    {
        scene.addItem(item->getPlayerTimeline());
    }
    scene.setSceneRect(-10,-100,1000,(250*(listPlayerItem.size()))/2);
    setScene(&scene);

    show();

}
