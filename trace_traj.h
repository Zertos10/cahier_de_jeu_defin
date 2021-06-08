#ifndef TRACE_TRAJ_H
#define TRACE_TRAJ_H

#include <QWidget>
#include "mainwindow.h"


class trace_traj
{
public:
    trace_traj();


    //Fait le tracer pour la trajectoire des joueurs

    void placeTrajPlayer(QPainter *painter);
    //Fait le tracer pour le ballon de rugby
    //Partie de Noah
    void placeBall();





private:
    QList<Points> points;


};

#endif // TRACE_TRAJ_H
