#ifndef TERRAINCASE_H
#define TERRAINCASE_H

#include <QtWidgets>
#include <QPainter>
#include "trajectoire_entite.h"
#include "lib/Bezier.hpp"
#include "mainwindows/tracetraj.h"
#include "mainwindows/tablesteam.h"
#include "graphics_scene-animation/animation/animationTraj.h"

#include "calcul_distance.h"
#include <math.h>
class terrainRugby :public QFrame
{
    Q_OBJECT
  enum Extremite{PointDep,PointArriv};

public:
  //Constructeur de la classe
    terrainRugby(QWidget* parent);
    //Création d'une trajectoire ou modification d'une trajectoire
    void createTrajectory(bool isCreateTrajectory);
    void modifTrajectory(bool isModifyTrajectory);
    void supprTrajectory(bool isSuppr);
    //Retourne le nombre de trajectoire
    int setNombreTrajectoire();


    //Methode pour l'animation
    void startAnimation();
    void stopAnimation();
    void changeSpeedAnim(int seconde);

    //Préparation a l'exportation du cahier de jeu et mise en place du cahier de jeu importé
    cahier_de_jeu_donnee* export_prepare();
    void placement_import(cahier_de_jeu_donnee);
    QVector<QVector<int>> joueurImporter();
    QVector<QString> getTeamName();

signals:
   void showLabelDistance(int);
private slots:
   void customMenuRequested(QPoint pos);
   void lierBallonATraj();


private:
    void paintEvent(QPaintEvent*) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;


    bool isInTraj(QPoint positionEvent, QPoint positionTraj) const;
    //Detecte la possibilité de créer ou modifier une trajectoire


    bool isCreateTrajectory = false;
    bool isModifyTrajectory = false;
    bool placeBallonDansTraj = false;
    bool isSupprTrajectory =false;

    void addLabelPlayer(joueur joueurLabel);
//Actualise l'affichage des labels
    void showListsLabel();

    QWidget *parent ;
    //Faire allonger la trajectoire
    Extremite extremiteTraj;

    trajectoire_entite *addPlayer = new trajectoire_entite ;
    trajectoire_entite *modifExistTrajectoire = new trajectoire_entite;

    QList<trajectoire_entite> trajectoire ;


    int selecteur =0;
    bool enregistPos = true;
    bool isDrawing= false,isModif=false , isMoving = false ;

    QList<QPoint> *pointProvisoire = new QList<QPoint>;
    int vitesse_course = Marche;
    bool mousePressed;

    QPoint pointTempTrajectoire ;
    QList<int> pointModif;
    int pointModifSelect =0;

    QVector<QString> teamsName;
    QVector<QLabel*> listLabelPlayers;
    QList<joueur> joueurs;
    QList<joueur> joueursImporter;

    AnimationTraj *traj = new AnimationTraj();
    trajectoire_entite trajectoireTriggeredBallon;
    QVector<CreateAnimation*> listPlayerAnimation;




};

#endif // TERRAINCASE_H
