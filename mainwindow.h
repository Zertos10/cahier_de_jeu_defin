#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtWidgets>
#include <QCursor>
#include <QPainter>
#include <math.h>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "import_database.h"
#include "export_database.h"
#include <QDateTime>
#include <QDate>
#include "trajectoire_entite.h"
#include "save_file.h"

#include "import_database.h"
#include "export_database.h"

#include "mainwindows/tracetraj.h"
#include "mainwindows/tablesteam.h"
#include "mainwindows/terrainRugby.h"


#include "graphics_scene-animation/animation/confAnimation.h"
#include "graphics_scene-animation/animation/animationTraj.h"



using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();


  //Recupere et place les points dans le mainWindows
  void placement_import(cahier_de_jeu_donnee donnee);


  //Drag and drop event methode

  void dragEnterEvent(QDragEnterEvent *event) override;

  bool getStateCreateTrajectory();
public slots:
   void showLabelDistance(int calcul);

private slots:
  //Lance l'animation (sera modifié ultérieurement)
  void animationStart();

 //Trace les trajectoires
  void on_start_clicked();
  //Lance la trajectoire d'un joueur
  void on_create_Trajectory_clicked();
  //Active la modification des trajectoire
  void on_modify_trajectory_clicked();
  //Pour la sélection de la vitesse de déclenchement
  void on_Vitesserouge_clicked();
  void on_Vitesse_orange_clicked();
  void on_vitesse_vert_clicked();
  //Ouvre un menu contextuelle
  //slot permettant l'ouverture de la boîte de dialogue d'importe
  void on_import_triggered();
 //slot permettant l'ouverture de la boîte de dialogue d'exporte
  void on_export_triggered();
  void on_stop_anim_clicked();
  void on_spin_depChang_valueChanged(double seconde);

  void createTrajectoire();
  void supprTrajectoire();

private:

  void createToolsBar();
  void resizeEvent(QResizeEvent*) override;
  Ui::MainWindow *ui;

  TablesTeam *team;
  QTimer *timer;
  bool isCreateTrajectory = false;
  bool isModifyTrajectory = false;
  bool isSupprTrajectory = false;


  QPropertyAnimation *animation =new QPropertyAnimation();
  AnimationTraj *traj = new AnimationTraj();
  //Importation
  QString nom_cahier_de_jeu;
  bool taille_terrain = true;
   terrainRugby *terrain1;

  QVector<CreateAnimation*> listPlayerAnimation;




};
#endif // MAINWINDOW_H
