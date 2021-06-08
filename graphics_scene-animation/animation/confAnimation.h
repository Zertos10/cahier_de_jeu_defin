#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include <QWidget>
#include "trajectoire_entite.h"
#include <QPropertyAnimation>
class CreateAnimation: public QPropertyAnimation
{
public:
    CreateAnimation(QWidget *Label,int secondeDecalage=0);
    CreateAnimation(joueur joueur,int secondeDecalage=0);
    CreateAnimation(QWidget *Label, joueur joueur, int secondeDecalage=0);
    void keyAnim(joueur joueur);
    void keyAnim(trajectoire_entite entite);
    void LabelMove();
    void calculDuree();


    void setDecalage(int secondeDecalage);
    int getDecalage();
private:
    int secondeDecalage = 0;
    QWidget *Label;

};


#endif // PLAYERANIMATION_H
