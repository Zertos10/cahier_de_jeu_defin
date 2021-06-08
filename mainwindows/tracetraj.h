#ifndef TRACETRAJ_H
#define TRACETRAJ_H

#include <QWidget>
#include "trajectoire_entite.h"
#include <QPainter>
#include <QList>



class TraceTraj
{
public:
    TraceTraj();
    static void tempTraj(QPainter *painter,trajectoire_entite trajTemp);
    static void tracerTraj(QPainter *painter,QList<trajectoire_entite> listTraj,int colors= Marche);
    static QPen colorTraj(int colors);
    static QPen colorTraj(QString colors = "#000000");
    static void paintPoints(QPainter *painterPoint,QPoint dep, QPoint arrv);
    static void tracePasseTemp(QPainter *painterPasseTemp,trajectoire_entite trajPasse);



private:


};

#endif // TRACETRAJ_H
