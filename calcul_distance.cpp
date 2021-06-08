#include "calcul_distance.h"
#include <QDebug>


calcul_distance::calcul_distance(trajectoire_entite trajectoire):traj(trajectoire)
{



}

int calcul_distance::calcul()
{
    QList<Points> listeDePoint = traj.getTrajectoire();

  int dist_calc =0;
  int convertion_m;
    for(int i=1 ; i<listeDePoint.size();i++)
    {
     int x= listeDePoint[i-1].pointStock.x();
     int y = listeDePoint[i-1].pointStock.y();

    int x2 = listeDePoint[i].pointStock.x();
    int y2 = listeDePoint[i].pointStock.y();
    int calcul = sqrt(pow((x2-x),2)+(pow((y2-y),2)));
    dist_calc += calcul;
    convertion_m = dist_calc / 6;

//  qDebug() << "i: " << i << ", distance : " << dist_calc ;
  //qDebug() << "distance en mètre" << convertion_m;


  }

  return convertion_m;

}

