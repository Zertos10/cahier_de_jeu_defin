#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{



  ui->setupUi(this);

  QAction *actionImport = ui->actionImport;
  QAction *actionExport = ui->actionExporte;
  connect(actionImport, SIGNAL(triggered()), this, SLOT(on_import_triggered()));
  connect(actionExport, SIGNAL(triggered()), this, SLOT(on_export_triggered()));
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  ui->distanceTrajectoire->hide();
  setFixedSize(geometry().width(),geometry().height());

  //connect(ui->centralwidget,SIGNAL(customContextMenuRequested(QPoint&)),this,SLOT(ouvrirMenuCont(QPoint&)));
  team = new TablesTeam(this);

  //animationAff = new graphic_animation(this);

   team->activateWindow();
   team->raise();
   ui->scrollArea->activateWindow();
   ui->scrollArea->raise();
  createToolsBar();
  setAcceptDrops(true);
  terrain1 = new terrainRugby(this);

  terrain1->show();

  /* centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
  setMouseTracking(true);*/

}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::animationStart()
{
  qDebug() << animation->currentTime();
  if(animation->currentTime() == animation->duration()) timer->stop();


}






void MainWindow::placement_import(cahier_de_jeu_donnee donnee)
{
  terrain1->placement_import(donnee);
  qDebug() << "team :";
  team->importTable(terrain1->joueurImporter());
  team->setTeamName(terrain1->getTeamName());

}


void MainWindow::on_start_clicked()
{

if(terrain1->setNombreTrajectoire() != 0)
{
  qDebug() << "startAnimation";

    terrain1->startAnimation();
}

}

void MainWindow::on_create_Trajectory_clicked()
{

  if(isCreateTrajectory == false)
  {

    ui->create_Trajectory->setText("Désactiver !");
    ui->modify_trajectory->setText("Modifier trajectoire !");


    isCreateTrajectory = true;
    isModifyTrajectory = false;

    qDebug() << "Mode création activé !";
  }
  else
  {
    isCreateTrajectory = false;
    ui->create_Trajectory->setText("Crée une trajectoire !");

    qDebug() << "Mode création désactivé  !";

  }
  terrain1->createTrajectory(isCreateTrajectory);
  terrain1->modifTrajectory(isModifyTrajectory);


}

void MainWindow::on_modify_trajectory_clicked()
{
    if(isModifyTrajectory == false)
    {
      isModifyTrajectory = true;
      isCreateTrajectory = false;
      ui->modify_trajectory->setText("Désactiver !");
      ui->create_Trajectory->setText("Crée une trajectoire");


    }
    else
    {
      isModifyTrajectory = false;
      ui->modify_trajectory->setText("Modifier trajectoire !");



    }
    terrain1->createTrajectory(isCreateTrajectory);
    terrain1->modifTrajectory(isModifyTrajectory);



}




void MainWindow::on_Vitesserouge_clicked()
{
ui->Vitesserouge->setDisabled(true);
ui->Vitesse_orange->setDisabled(false);
ui->vitesse_vert->setDisabled(false);
}

void MainWindow::on_Vitesse_orange_clicked()
{
  ui->Vitesse_orange->setDisabled(true);
  ui->Vitesserouge->setDisabled(false);
  ui->vitesse_vert->setDisabled(false);

}

void MainWindow::on_vitesse_vert_clicked()
{
  ui->Vitesserouge->setDisabled(false);
  ui->Vitesse_orange->setDisabled(false);
  ui->vitesse_vert->setDisabled(true);

}



void MainWindow::on_import_triggered()
{
    import_database dataBase;
    dataBase.exec();
    if(dataBase.getErrorMessage() == ErrorMessage::PasErreur)
    {
         placement_import(dataBase.getValues());

    }
    else
    {

    }

    qDebug() << "suite";



}

void MainWindow::on_export_triggered()
{

    export_database export_data(terrain1->export_prepare());
    if(export_data.exec())
    {
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "dropDetect";

        event->acceptProposedAction();



}

void MainWindow::showLabelDistance(int calcul)
{
    qDebug() << "slot fonctionne :"<< calcul;
     ui->distanceTrajectoire->setText("Distance calculer pour la trajectoire tracé :" + QString::number(calcul) +"m.");

     ui->distanceTrajectoire->show();
}







void MainWindow::resizeEvent(QResizeEvent *)
{
  qDebug() << "taille "<< geometry();
  //terrainScene->setGeometryView(this->geometry());

}
void MainWindow::on_stop_anim_clicked()
{
    terrain1->stopAnimation();
}


void MainWindow::on_spin_depChang_valueChanged(double seconde)
{
  terrain1->changeSpeedAnim(seconde);
}

void MainWindow::createTrajectoire()
{
    if(isCreateTrajectory)
    {
        isCreateTrajectory= false;
        ui->create_Trajectory->setText("Crée une trajectoire");
    }
    else
    {
        isCreateTrajectory = true;
        ui->create_Trajectory->setText("Désactiver");


    }
    terrain1->createTrajectory(isCreateTrajectory);


}

void MainWindow::supprTrajectoire()
{
 if(isSupprTrajectory)
 {
   isSupprTrajectory= false;
 }
 else
 {
   isSupprTrajectory = true;
 }
 terrain1->supprTrajectory(isSupprTrajectory);
}


void MainWindow::createToolsBar()
{
  const QIcon creatPlayerTrajectoireIcon = QIcon(":/img/crayon_selection.png");
  QAction *createPlayerTrajectoire = new QAction(creatPlayerTrajectoireIcon,tr("&Créer une trajectoire pour les joueurs"),this);
  createPlayerTrajectoire->setStatusTip(tr("Créer une trajectoire pour les joueurs"));
  connect(createPlayerTrajectoire,SIGNAL(triggered()),this,SLOT(createTrajectoire()));
  ui->toolBar->addAction(createPlayerTrajectoire);


  const QIcon  createBallTrajectoireIcon = QIcon(":/img/crayon_selection_ballon.png");
  QAction *createBallTrajectoire = new QAction(createBallTrajectoireIcon,tr("&Créer une trajectoire pour le ballon"),this);
  createBallTrajectoire->setStatusTip(tr("Créer une trajectoire pour le ballon"));
  connect(createBallTrajectoire,SIGNAL(triggered()),this,SLOT(createTrajectoire()));
  ui->toolBar->addAction(createBallTrajectoire);

  const QIcon  supprTrajectoireIcon = QIcon(":/img/suppr_traj.png");
  QAction *supprTrajectoire = new QAction(supprTrajectoireIcon,tr("&Supprimer une trajectoire existante"),this);
  supprTrajectoire->setStatusTip(tr("Supprimer une trajectoire existante"));
  connect(supprTrajectoire,SIGNAL(triggered()),this,SLOT(supprTrajectoire()));
  ui->toolBar->addAction(supprTrajectoire);

}

