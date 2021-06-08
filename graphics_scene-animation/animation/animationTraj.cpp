#include "animationTraj.h"



AnimationTraj::AnimationTraj(QVector<CreateAnimation*> *listPlayer):listPlayer(listPlayer)
{

    timer = new QTimer(this);
    size = this->listPlayer->count();
    qDebug() <<"taille stocker" << size;
    connect(timer, SIGNAL(timeout()),
             this, SLOT(createAnimation()));
    qDebug() <<"Classe instancié";

}

AnimationTraj::AnimationTraj()
{

}

void AnimationTraj::createAnimation()
{
    qDebug() << "Activation";
    if(compteur< listPlayer->size())
    {

        qDebug() << "lancement de l'animation" << compteur;
        listPlayer->value(compteur)->start();

        timer->start(50+listPlayer->value(compteur)->getDecalage());

        compteur++;
    }
    else
    {
        stopAnimation();
    }




}



void AnimationTraj::breakAnimation(int ms)
{


}



double AnimationTraj::count()
{
    return timer->remainingTime();
}

void AnimationTraj::setListFramePlayerAnimation(QVector<CreateAnimation*> *listPlayer )
{
    this->listPlayer = listPlayer;
}

void AnimationTraj::startAnimation()
{

    timer->start(50+listPlayer->value(compteur)->getDecalage());
    qDebug() << timer->isActive();


}


void AnimationTraj::stopAnimation()
{
    timer->stop();
    delete this;

}

void AnimationTraj::depTimeLineChanged()
{

}
