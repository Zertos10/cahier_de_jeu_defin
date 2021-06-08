#include "tracetraj.h"

TraceTraj::TraceTraj()
{

}

void TraceTraj::tempTraj(QPainter *painter, trajectoire_entite trajTemp)
{
    qDebug() << "test";
    QPoint *ligneTrace  = new QPoint[trajTemp.getTrajectoire().size()];
    for(int i =0;i<trajTemp.getTrajectoire().size();i++)
    {

        ligneTrace[i] = trajTemp.getTrajectoire().value(i).pointStock;
    }
    painter->setPen(Qt::red);
    painter->drawPolyline(ligneTrace,trajTemp.getTrajectoire().size());
    delete[] ligneTrace;
}

void TraceTraj::tracerTraj(QPainter *painter, QList<trajectoire_entite> listTraj, int colors)
{

    for(trajectoire_entite traj : listTraj)
    {
        QPoint *pointTrac = new QPoint[traj.getTrajectoire().size()];
        for(int i=0;i<traj.getTrajectoire().size();i++)
        {
            pointTrac[i] = traj.getTrajectoire().value(i).pointStock;



        }
        painter->setPen(colorTraj(colors));
        painter->drawPolyline(pointTrac,traj.getTrajectoire().size());
        paintPoints(painter,traj.getDepPoint(),traj.getArrvPoint());

    }
    painter->end();
}

QPen TraceTraj::colorTraj(int colors)
{
    QPen colorPen;
    if(colors == Vitesse::Marche)
    {
        colorPen.setColor(Qt::green);
    }
    else if(colors == Vitesse::Trotiner)
    {
        colorPen.setColor(*new QColor(255,119,0,1));

    }
    else if(colors == Vitesse::Courir)
    {
        colorPen.setColor(Qt::red);
    }
    return colorPen;
}

QPen TraceTraj::colorTraj(QString colors)
{
    QColor rgb(colors);
    QPen colorPen(rgb);
    return colorPen;
}
void TraceTraj::paintPoints(QPainter *painterPoint, QPoint dep, QPoint arrv)
{
    painterPoint->setPen(QPen(Qt::red,15));
    painterPoint->drawPoint(dep);
    painterPoint->drawPoint(arrv);
}

void TraceTraj::tracePasseTemp(QPainter *painterPasseTemp, trajectoire_entite trajPasse)
{
    if(trajPasse.getTypeEntity() == Ballon)
    {
        painterPasseTemp->setPen(colorTraj("#A9A9A9"));
        QLineF lignePasse(trajPasse.getDepPoint(),trajPasse.getArrvPoint());
        painterPasseTemp->drawLine(lignePasse);

    }
}


