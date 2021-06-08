#include "ballon.h"
#include "trajectoire_entite.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QDebug>


Ballon::Ballon(trajectoire_entite trajectoire):traj(trajectoire)
{

}

int Ballon::calcul()
{
  QList<Points> listeDePoint = traj.getTrajectoire();

int dist_calc_ballon =0;

  for(int i=1 ; i<listeDePoint.size();i++)
  {
   int x= listeDePoint[i-1].pointStock.x();
   int y = listeDePoint[i-1].pointStock.y();

  int x2 = listeDePoint[i].pointStock.x();
  int y2 = listeDePoint[i].pointStock.y();
  int calcul = sqrt(pow((x2-x),2)+(pow((y2-y),2)));
  dist_calc_ballon += calcul;
  convertion_m_ballon = dist_calc_ballon / 6;

  vitesse_m_ballon = convertion_m_ballon / timer;

  qDebug() << "i: " << i << ", distance : " << dist_calc_ballon ;
  qDebug() << "distance en mètre" << convertion_m_ballon;
  qDebug() << "vitesse en mètres par secondes :" << vitesse_m_ballon;




  }

    return convertion_m_ballon;



}

int Ballon::getDistance()
{
    return convertion_m_ballon;
}


int Ballon::getVitesse()
{
    return vitesse_m_ballon;
}
