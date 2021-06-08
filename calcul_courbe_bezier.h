#ifndef CALCUL_COURBE_BEZIER_H
#define CALCUL_COURBE_BEZIER_H
#include <math.h>
#include <QWidget>
#include <QDebug>
class calcul_courbe_Bezier
{
public:
  calcul_courbe_Bezier();
  QPoint combinaisonLinaire(QPoint A,QPoint B,float u, float v);
  QPoint interpolationLinaire(QPoint A,QPoint B,double t);
  QPoint VecteurUnitaire(QPoint P1,QPoint P2);
  bool test_alignement_4pts(QList<QPoint> points,double epsilon);
  QList<QList<QPoint>> division_courbe_bezier(QList<QPoint> pointsControl);
  void courbe_bezier_recursif(QList<QPoint> pointsControl,double epsilon,QList<QPoint> pile_point_courbe);
  QList<QPoint> coube_bezier_init(QList<QPoint> pointsControl,double epsilon);

};

#endif // CALCUL_COURBE_BEZIER_H
