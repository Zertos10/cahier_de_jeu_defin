#ifndef BALLON_H
#define BALLON_H

#include <QPainter>
#include <QtMath>
#include <QPainterPath>
#include <QColor>
#include "trajectoire_entite.h"

class Ballon
{
public:
    Ballon(trajectoire_entite trajectoire);
    int calcul();

    int getDistance();
    int getVitesse();

  private:
    trajectoire_entite traj;
    int timer = 3;
    int convertion_m_ballon = 0;
    int vitesse_m_ballon = 0;
    QColor color;
};

#endif // BALLON_H
