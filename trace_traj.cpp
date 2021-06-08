#include "trace_traj.h"

trace_traj::trace_traj()
{

}

void trace_traj::placeTrajPlayer(QPainter *painter)
{
    painter->drawLine(QLine(QPoint(1,1),QPoint(100,100)));

}

