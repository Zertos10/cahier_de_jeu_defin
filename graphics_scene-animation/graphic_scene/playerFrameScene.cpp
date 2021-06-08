#include "playerFrameScene.h"

PlayerFrameScene::PlayerFrameScene(struct joueur *joueur,int compt):compt(compt)
{
    qDebug() <<"compteur PlayerFrameScene" <<compt;
     frame = new itemFrameCreation(compt);
    qDebug() << "frame -> token" <<*frame->getRec();
     token = new ItemTokenCreation(frame->getRec(),frame);



}

PlayerFrameScene::PlayerFrameScene(int compt)
{
    qDebug() <<"compteur PlayerFrameScene" <<compt;
     frame = new itemFrameCreation(compt);
    qDebug() << "frame -> token" <<*frame->getRec();
     token = new ItemTokenCreation(frame->getRec());


}

QGraphicsItemGroup* PlayerFrameScene::getPlayerTimeline()
{
    QGraphicsItemGroup *frameGroup = new QGraphicsItemGroup();
    qDebug() << "frameGroup ajout";
    frameGroup->addToGroup(frame);
    frameGroup->addToGroup(token);
    return frameGroup;

}











