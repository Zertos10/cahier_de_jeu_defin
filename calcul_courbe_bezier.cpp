#include "calcul_courbe_bezier.h"

calcul_courbe_Bezier::calcul_courbe_Bezier()
{

}
QPoint calcul_courbe_Bezier::combinaisonLinaire(QPoint A, QPoint B, float u, float v)
{
  qDebug() <<"Valeur de retour de la méthode combinaisonLinaire  :  x=" << A.x()*u+B.x()*v << "\n y="<< A.y()*u+B.y()*v;
  return QPoint(A.x()*u+B.x()*v,A.y()*u+B.y()*v);
}



QPoint calcul_courbe_Bezier::interpolationLinaire(QPoint A, QPoint B, double t)
{
  qDebug() <<"Valeur de retour de la méthode interpolationLinaire  : " << 1-t;

  return combinaisonLinaire(A,B,t,1-t);
}

QPoint calcul_courbe_Bezier::VecteurUnitaire(QPoint P1, QPoint P2)
{
  int Ux = P2.x() - P1.x();
  int Uy = P2.y() - P1.y();
  float norme = sqrt(Ux*Ux+Uy*Uy);
   QPoint pointCalcul ;

  if(norme != 0)
  {
   float x =Ux/norme*100;
   float y = Uy/norme*100;
   qDebug() << "Valeur de Ux" << x << "\n Valeur de Uy" << y;
   pointCalcul.setX(x);
   pointCalcul.setY(y);
   qDebug() << "Valeur de retour de la méthode VecteurUnitaire : " << pointCalcul <<"(true)";
   return pointCalcul;
  }
  else
  {
    return pointCalcul;
  }



}



bool calcul_courbe_Bezier::test_alignement_4pts(QList<QPoint> points, double epsilon)
{
  QPoint U1,U2,U3;
  float x =0;

    U1 = VecteurUnitaire(points[0],points[1]);
    U2 = VecteurUnitaire(points[1],points[2]);
    U3 = VecteurUnitaire(points[2],points[3]);
  if(!U2.isNull())
  {
    x= 2.0-(U1.x()*U2.x()+U1.y()*U2.y()+U2.x()*U3.x()+U2.y()*U3.y());
  }
  else
  {
    x= 1.0-(U1.x()*U3.x()+U1.y()*U3.y());
  }
  qDebug() << "x="<< x;


 qDebug() <<"Valeur de retour de la fonction test_alignement : " << abs(x) ;

  if(abs(x) <epsilon) return true;
  else return false;

}

QList<QList<QPoint>> calcul_courbe_Bezier::division_courbe_bezier(QList<QPoint> pointsControl)
{
  qDebug() <<"Valeur d'entrée de la méthode division_courbe_bezier : " <<pointsControl;
  QPoint P01 = interpolationLinaire(pointsControl[0],pointsControl[1],0.5);
  QPoint P12 = interpolationLinaire(pointsControl[1],pointsControl[2],0.5);
  QPoint P23 = interpolationLinaire(pointsControl[2],pointsControl[3],0.5);
  QPoint P01_12 = interpolationLinaire(P01,P12,0.5);
  QPoint P12_23 = interpolationLinaire(P12,P23,0.5);
  QPoint Q = interpolationLinaire(P01_12,P12_23,0.5);
  QList<QList<QPoint>> PointReturn;
  QList<QPoint> points1,points2;
  points1.append(pointsControl[0]);
  points1.append(P01);
  points1.append(P01_12);
  points1.append(Q);
  PointReturn.append(points1);
  points2.append(Q);
  points2.append(P12_23);
  points2.append(P23);
  points2.append(pointsControl[3]);
  PointReturn.append(points2);
  qDebug() <<"Valeur de retour de la méthode division_courbe_bezier : " <<PointReturn;
  return PointReturn;
}

void calcul_courbe_Bezier::courbe_bezier_recursif(QList<QPoint> pointsControl, double epsilon, QList<QPoint> pile_point_courbe)
{
  qDebug() <<"Valeur de retour de la méthode courbe_bezier_recursif : " << test_alignement_4pts(pointsControl,epsilon);

  if(test_alignement_4pts(pointsControl,epsilon))
  {

    pile_point_courbe.append(pointsControl[0]);
    qDebug() << "Ajout du pointsControl" << pile_point_courbe;
  }
  else
  {
    QList<QList<QPoint>> points = division_courbe_bezier(pointsControl);
    courbe_bezier_recursif(points[0],epsilon,pile_point_courbe);
    courbe_bezier_recursif(points[1],epsilon,pile_point_courbe);
  }
}

QList<QPoint> calcul_courbe_Bezier::coube_bezier_init(QList<QPoint> pointsControl, double epsilon)
{
  //qDebug()<< "Valeur d'entrer : pointControl ="<<pointsControl << "epsilon = "<< epsilon;
  QList<QPoint> pile_point_courbe ;
  courbe_bezier_recursif(pointsControl,epsilon,pile_point_courbe);
  pile_point_courbe.append(pointsControl);
  qDebug() <<"Valeur de retour de la méthode coube_bezier_init : " <<pile_point_courbe;
  return pile_point_courbe;

}
