#ifndef ANIMATIONTRAJ_H
#define ANIMATIONTRAJ_H

#include <QWidget>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include "graphics_scene-animation/animation/confAnimation.h"
#include <QDebug>
#include <QAnimationGroup>
class AnimationTraj : public QObject
{
    Q_OBJECT
public:
    AnimationTraj(QVector<CreateAnimation*> *listPlayer);
    AnimationTraj();

    //Trajet de l'animation
    void breakAnimation(int ms);
    void stopAnimation();
    double count();

    void setListFramePlayerAnimation(QVector<CreateAnimation*> *listPlayer);
    void startAnimation();

public slots:
    void depTimeLineChanged();
    void createAnimation();



private:
    QTimer *timer ;
    QVector<CreateAnimation*>* listPlayer;
    int size = 0;
    int compteur = 0;




};

#endif // ANIMATIONTRAJ_H
