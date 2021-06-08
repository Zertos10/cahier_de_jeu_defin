#ifndef CALCUL_DISTANCE_H
#define CALCUL_DISTANCE_H
#include "trajectoire_entite.h"


class calcul_distance
{
  public:
    calcul_distance(trajectoire_entite trajectoire);

    int calcul();

  private:
    trajectoire_entite traj;

};

#endif // CALCUL_DISTANCE_H
