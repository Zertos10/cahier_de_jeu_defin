#ifndef PLAYERFRAMESCENE_H
#define PLAYERFRAMESCENE_H


#include "trajectoire_entite.h"
#include "itemframecreation.h"
#include "itemtokencreation.h"
#include "itemlinetempcreation.h"

#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
class PlayerFrameScene
{
public:
    PlayerFrameScene(joueur *joueur,int compt);
    PlayerFrameScene(int compt);
   QGraphicsItemGroup *getPlayerTimeline();



protected:





private:
    joueur joueur;
    itemFrameCreation *frame;
    ItemTokenCreation *token;
    int compt;



};

#endif // PLAYERFRAMESCENE_H
