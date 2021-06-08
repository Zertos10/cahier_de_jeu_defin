#ifndef TRAJECTOIRE_ENTITE_H
#define TRAJECTOIRE_ENTITE_H

#include <QWidget>
#include "database.h"
#include <QtMath>

enum EntityType {Player,Ballon};
enum Vitesse {Marche,Trotiner,Courir};

//Instancié quand clique gauche fait la premiére fois
class trajectoire_entite
{
public:
    //constructeur de la classe
    trajectoire_entite(QPoint depPoint,int type = Player);
    trajectoire_entite(int type = Player);

    //Lorsque la souris bouge ajoute un point a la trajectoire
    void addPoint(QPoint pointMove,int speed = Marche);
    //Lors du relachement du click stock la dernière trajectoire
    void endPoint(QPoint arrvPoint);
    void modifPoint(trajectoire_entite modifTrajectoire,int pointExtrimite);

    void lierBallonAJoueur();

    void lierJoueurATrajectoire(joueur* joueurLie);

    void affectPlayer(int joueur , QString equipe);
    //Getter
    QPoint getDepPoint();
    QPoint getArrvPoint();
    QList<Points> getTrajectoire();
    int getTypeEntity();

    //Setter
    void setTypEntity(int type);
    void setDepPoint(QPoint depPoint);
    void setArrvPoint(QPoint arrvPoint);
    void setPoints(int valeur,QPoint nouvPoint);
    void recomptPos();

    void clear();



private:
    QPoint depPoint = QPoint(0,0);
    QPoint arrvPoint;
    QList<Points> trajectoire;
    int typeEntity = Player;
    unsigned int pos = 0;
    int player_number = 0;
    QString equipe = "not define";
    joueur joueurLier;
};

#endif // TRAJECTOIRE_ENTITE_H
