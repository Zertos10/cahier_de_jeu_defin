#include "trajectoire_entite.h"


trajectoire_entite::trajectoire_entite(QPoint depPoint, int type)
{
    this->depPoint = depPoint;
    this->typeEntity = type;
    //objList.push_back(this);


}

trajectoire_entite::trajectoire_entite(int type)
{
    this->typeEntity = type;
    //objList.push_back(this);
}

void trajectoire_entite::addPoint(QPoint pointMove, int speed)
{
    qDebug() << "Ajout du point" << pos << "de coordonnée" << pointMove;


    Points *point = new Points;
    point->pointStock = pointMove;
    point->posPoint = pos;
    point->speedPoint = speed;

    if(pos%10 == 0) point->pointModif = true;

    pos++;
    trajectoire.append(*point);


}

void trajectoire_entite::endPoint(QPoint arrvPoint)
{
    this->arrvPoint = arrvPoint;


}



void trajectoire_entite::modifPoint(trajectoire_entite modifTrajectoire, int pointExtrimite)
{
  if(pointExtrimite== 0)
  {
    qDebug() <<"modifPoint DepPoint: "<< modifTrajectoire.getDepPoint();
    qDebug() <<"modifPoint ArrvPoint: "<< modifTrajectoire.getArrvPoint();

    for(Points pushFrontPoint: modifTrajectoire.getTrajectoire())
    {
      trajectoire.push_front(pushFrontPoint);
    }
    depPoint = modifTrajectoire.getArrvPoint();
    recomptPos();
  }
  else if(pointExtrimite == 1)
  {
    for(Points pushBackPoint: modifTrajectoire.getTrajectoire())
    {
      trajectoire.push_back(pushBackPoint);
    }
    arrvPoint = modifTrajectoire.getArrvPoint();
    recomptPos();
  }

}

void trajectoire_entite::lierBallonAJoueur()
{
if(typeEntity == Ballon)
{

}
}

void trajectoire_entite::lierJoueurATrajectoire(joueur *joueurLie)
{
    if(typeEntity == Player)
    {
        this->joueurLier = *joueurLie;

    }
}

void trajectoire_entite::affectPlayer(int joueur, QString equipe)
{
    if(typeEntity == Player)
    {
        player_number = joueur;
        this->equipe = equipe;
    }
}


//Getter
QPoint trajectoire_entite::getDepPoint()
{
    return depPoint;
}

QPoint trajectoire_entite::getArrvPoint()
{
    return arrvPoint;
}

QList<Points> trajectoire_entite::getTrajectoire()
{
    return trajectoire;
}

int trajectoire_entite::getTypeEntity()
{
    return typeEntity;
}
//Setter
void trajectoire_entite::setTypEntity(int type)
{
    typeEntity = type;
}

void trajectoire_entite::setDepPoint(QPoint depPoint)
{
  qDebug() << depPoint;
    this->depPoint = depPoint;
}

void trajectoire_entite::setArrvPoint(QPoint arrvPoint)
{
  this->arrvPoint = arrvPoint;
}

void trajectoire_entite::setPoints(int valeur, QPoint nouvPoint)
{
  trajectoire[valeur].pointStock = nouvPoint;
}
void trajectoire_entite::recomptPos()
{
  for(int pos=0;pos<trajectoire.size();pos++)
  {
    trajectoire[pos].posPoint = pos;
    qDebug() <<"pos traj : "<<trajectoire[pos].posPoint;
  }
}

void trajectoire_entite::clear()
{
    trajectoire.clear();
    pos = 0;
}


/*QVector<trajectoire_entite *> trajectoire_entite::getAllObject()
{
    return objList;
}*/
