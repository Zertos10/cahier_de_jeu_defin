#ifndef GRAPHIC_ANIMATION_H
#define GRAPHIC_ANIMATION_H

#include <QtWidgets>
#include "playerFrameScene.h"
#include <qdebug.h>

class graphic_animation : public QGraphicsView
{

public:
    explicit graphic_animation(QWidget *parent = nullptr);
    void createFrame();


    void addPlayersTimeLine();

    void showScene();
protected:
    void createAbsTemps();


private:
   QGraphicsRectItem *frame;
   QGraphicsScene scene ;
   QVector<PlayerFrameScene*> listPlayerItem;

};

#endif // GRAPHIC_ANIMATION_H
