#include "confAnimation.h"

CreateAnimation::CreateAnimation(QWidget *Label, int secondeDecalage):QPropertyAnimation(Label,"geometry"),secondeDecalage(secondeDecalage),Label(Label)
{

}

CreateAnimation::CreateAnimation(joueur joueur, int secondeDecalage):secondeDecalage(secondeDecalage)
{
    keyAnim(joueur);
}

CreateAnimation::CreateAnimation(QWidget* Label, joueur joueur, int secondeDecalage):QPropertyAnimation(Label,"geometry"),secondeDecalage(secondeDecalage),Label(Label)

{
    keyAnim(joueur);

}

void CreateAnimation::keyAnim(joueur joueur)
{
    setTargetObject(Label);
    setDuration(3000);

    QPointF pointDepart = joueur.trajectoire.point_dep;
    QPointF pointArriv = joueur.trajectoire.point_arriv;

    setStartValue(QRect(pointDepart.x(),pointDepart.y(),Label->geometry().width(),Label->geometry().width()));
    double qTimeLine =0;
    for(Points pointTrajec : qAsConst(joueur.trajectoire.point_intermed))
    {
        qTimeLine = float(pointTrajec.posPoint)/joueur.trajectoire.point_intermed.size();

        setKeyValueAt(qTimeLine,QRect(pointTrajec.pointStock.x(),pointTrajec.pointStock.y(),Label->geometry().width(),Label->geometry().width()));



    }
     setEndValue(QRect(pointArriv.x(),pointArriv.y(),Label->geometry().width(),Label->geometry().width()));

}

void CreateAnimation::keyAnim(trajectoire_entite entite)
{

    setTargetObject(Label);
    setDuration(3000);

    QPointF pointDepart = entite.getDepPoint();
    QPointF pointArriv = entite.getArrvPoint();

    if(entite.getTypeEntity() == Ballon)
    setStartValue(QRect(pointDepart.x(),pointDepart.y()+20,Label->geometry().width(),Label->geometry().height()));
    else
     setStartValue(QRect(pointDepart.x(),pointDepart.y(),Label->geometry().width(),Label->geometry().height()));

    double qTimeLine =0;
    for(Points pointTrajec : entite.getTrajectoire())
    {
        qTimeLine = float(pointTrajec.posPoint)/entite.getTrajectoire().size();
        if(entite.getTypeEntity()==Ballon)
        setKeyValueAt(qTimeLine,QRect(pointTrajec.pointStock.x(),pointTrajec.pointStock.y()+20,Label->geometry().width(),Label->geometry().height()));


        else
        setKeyValueAt(qTimeLine,QRect(pointTrajec.pointStock.x(),pointTrajec.pointStock.y(),Label->geometry().width(),Label->geometry().height()));



    }
     setEndValue(QRect(pointArriv.x(),pointArriv.y(),Label->geometry().width(),Label->geometry().width()));
}

void CreateAnimation::calculDuree()
{

}


void CreateAnimation::setDecalage(int secondeDecalage)
{
    this->secondeDecalage = secondeDecalage;
}

int CreateAnimation::getDecalage()
{
    return secondeDecalage;
}
