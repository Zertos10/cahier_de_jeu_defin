#include "terrainRugby.h"

terrainRugby::terrainRugby(QWidget *parent):QFrame(parent)
{
    mousePressed = false;
    QPixmap pixmap(":img/terrain.jpg");
    QRect dimension(290,50,pixmap.size().width(),pixmap.size().height());
    setGeometry(dimension);
    this->setObjectName("terrainQFrame");
qDebug() << this->objectName();
    QString style("QFrame#"+objectName()+"{"
       " border: 2px solid green;"
       " border-radius: 4px;"
       " padding: 2px;"
        "background-image: url(:img/terrain.jpg);  }"
         );
   this->setStyleSheet(style);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(showLabelDistance(int)), parent, SLOT(showLabelDistance(int )));
    connect(this,SIGNAL(customContextMenuRequested(QPoint)), SLOT(customMenuRequested(QPoint)));


         //"background-image:url(':/img/terrain.jpg'); background-position: center;" );
    setAcceptDrops(true);
    update();

    this->parent = parent;



}

void terrainRugby::createTrajectory(bool isCreateTrajectory)
{
    this->isCreateTrajectory = isCreateTrajectory;
    qDebug() << this->isCreateTrajectory;
}

void terrainRugby::modifTrajectory(bool isModifyTrajectory)
{
  this->isModifyTrajectory = isModifyTrajectory;
}

void terrainRugby::supprTrajectory(bool isSuppr)
{
 isSupprTrajectory=isSuppr;


}

int terrainRugby::setNombreTrajectoire()
{
  return trajectoire.size();
}

void terrainRugby::startAnimation()
{
  traj = new  AnimationTraj(&listPlayerAnimation);
  traj->startAnimation();
  qDebug() << "enclenché";
}

void terrainRugby::stopAnimation()
{
  traj->stopAnimation();
}

void terrainRugby::changeSpeedAnim(int seconde)
{
  if(!listPlayerAnimation.isEmpty())
  {
      qDebug() << selecteur << ": seconde de décalage avant "<<listPlayerAnimation[selecteur]->getDecalage();
      listPlayerAnimation[selecteur]->setDecalage(seconde*1000);
      qDebug() << selecteur << ": seconde de décalage"<<seconde;
  }

}

cahier_de_jeu_donnee *terrainRugby::export_prepare()
{
  cahier_de_jeu_donnee *import_data = new cahier_de_jeu_donnee;

  cahier_de_jeu_mod cahier_de_jeu_pres ;

  QDateTime datetime = QDateTime::currentDateTime();
  QDate date = datetime.date();
  //Enregistrement du cahier de jeu
  cahier_de_jeu_pres.date = date.toString(Qt::ISODate);
  cahier_de_jeu_pres.terrain = false;


  import_data->cahier_de_jeu = cahier_de_jeu_pres; //
  import_data->joueurs = joueurs; //Enregistrement des joueurs placer
  //Compilation de la partie ballon (sert pour les tests)
  ballon *ball = new ballon;
  trajectoire_entite *trajBallon = new trajectoire_entite(Ballon);
  trajBallon->setDepPoint(QPoint(0,0));
  trajBallon->setArrvPoint(QPoint(100,100));
  for(int i=0;i<50;i++) trajBallon->addPoint(QPoint(i,i),Courir);
  struct trajectoire trajectoireBallon;
  trajectoireBallon.point_intermed = trajBallon->getTrajectoire();
  trajectoireBallon.point_dep = trajBallon->getDepPoint();
  trajectoireBallon.point_arriv = trajBallon->getArrvPoint();
  ball->ballonTraj = trajectoireBallon ;
  ball->pointAppr = QPoint(2,2);

  import_data->ballon = *ball;//enregistrement du ballon

  qDebug()<<"date:" << cahier_de_jeu_pres.date;
    qDebug() << "Exportation :"<< date.toString(Qt::ISODate);




    return import_data;
}

void terrainRugby::placement_import(cahier_de_jeu_donnee donnee)
{
  //Efface les donnée du précedent cahier de jeu.
    trajectoire.clear();
    for(QLabel* labelPlayer:listLabelPlayers) labelPlayer->hide();
    listLabelPlayers.clear();
    listPlayerAnimation.clear();
    joueursImporter = donnee.joueurs;
    for(int i=0;i<donnee.joueurs.size();i++)
    {
      //Ajoute les trajectoire
        trajectoire_entite players_traj;
        players_traj.setDepPoint(donnee.joueurs.value(i).trajectoire.point_dep);
        players_traj.setArrvPoint(donnee.joueurs.value(i).trajectoire.point_arriv);
        qDebug() <<"Point arrivée"<<players_traj.getArrvPoint();
        //Ajoute les points des trajectoire
     for(Points point : donnee.joueurs.value(i).trajectoire.point_intermed)
     {
       players_traj.addPoint(point.pointStock,point.speedPoint);
     }
     trajectoire << players_traj;
     addLabelPlayer(donnee.joueurs.value(i));
    }
}

QVector<QVector<int> > terrainRugby::joueurImporter()
{
  qDebug() << "trieParEquipe" ;
QVector<QString> *trieEquipe = new QVector<QString>;
QVector<int> *trieNumJoueur = new QVector<int>;
//Détermine le nombre d'équipe importer
for(const joueur &joueur :qAsConst(joueursImporter))
{
    qDebug() <<"Contient l'équipe du joueur :"<< trieEquipe->contains(joueur.nom_equipe);
   if(!(trieEquipe->contains(joueur.nom_equipe)))
  {
    trieEquipe->push_back(joueur.nom_equipe);
    teamsName = *trieEquipe;

  }


}
//Fait le trie entre les joueurs appartenant a une équipe ou une autre
QVector<QVector<int>> tableauNumJoueur;
for(const joueur &joueur : qAsConst(joueursImporter))
{
    if(joueur.nom_equipe == trieEquipe->value(0))
    {
        trieNumJoueur->push_back(joueur.numero_joueur);
    }
}
tableauNumJoueur.push_back(*trieNumJoueur);
trieNumJoueur->clear();
//Fait le trie entre les joueurs appartenant a une équipe ou une autre
for(const joueur &joueur : qAsConst(joueursImporter))
{
    if(joueur.nom_equipe == trieEquipe->value(1))
    {
        trieNumJoueur->push_back(joueur.numero_joueur);
    }
}
tableauNumJoueur.push_back(*trieNumJoueur);
return tableauNumJoueur;
}

QVector<QString> terrainRugby::getTeamName()
{
  return teamsName;
}

void terrainRugby::paintEvent(QPaintEvent *)
{


    //Trajectoire en cours de création

   if(addPlayer->getTrajectoire().empty() != true && isDrawing)
    {
      QPainter *actualDraw = new QPainter(this);
     TraceTraj::tempTraj(actualDraw,*addPlayer);
    delete actualDraw;
  }

  //Trajectoire stocker
  if(!(trajectoire.empty()))
   {
  QPainter *oldDraw = new QPainter(this);
  if(!(trajectoire.isEmpty()))
  {
      TraceTraj::tracerTraj(oldDraw,trajectoire);

  }
  delete oldDraw;

  }


  //Point de modification de la trajectoire
  if(isModifyTrajectory)
  {
    QPainter modif(this);
    modif.setPen(QPen(Qt::blue,10));
      for(int i=1;i< pointModif.size();i++)
       {
      modif.drawPoint(*new QPoint(trajectoire[selecteur].getTrajectoire().value(pointModif[i]).pointStock.rx(),trajectoire[selecteur].getTrajectoire().value(pointModif[i]).pointStock.ry()));

      }
  }
}

void terrainRugby::mousePressEvent(QMouseEvent *event)
{



    if(!trajectoire.empty())
    {

    for( int i =0;i<trajectoire.size();i++)
    {

    if(isInTraj(event->pos(),trajectoire.value(i).getDepPoint()))
    {

        qDebug() << "point de la figure n° "<< i <<",sélectionner a";
       selecteur = i;
       qDebug() <<i;
       break;
    }
    if(isInTraj(event->pos(),trajectoire.value(i).getArrvPoint()))
    {
      qDebug() << "point de la figure n° "<< i <<",sélectionner point b";
      selecteur = i;
      break;
    }


    }
  }
   qDebug() << "Nombre de figure : "<< trajectoire.size();

   //Clique gauche effectuer

   if (event->button() == Qt::LeftButton)
   {

       qDebug() <<"Etat de placeBallonDansTraj :" <<placeBallonDansTraj;
       if(placeBallonDansTraj && !trajectoire.isEmpty() && isCreateTrajectory)
       {
           Points n0 = trajectoireTriggeredBallon.getTrajectoire().first();


           for(int comptPoint=1 ;comptPoint<trajectoireTriggeredBallon.getTrajectoire().size();comptPoint++)
           {
               Points n1 = trajectoireTriggeredBallon.getTrajectoire().value(comptPoint);
               qDebug() << "Point de n-1: "<<comptPoint-1 <<n0.pointStock;
                qDebug() << "Point de n: "<<comptPoint <<n1.pointStock;
               int xN0 =  n0.pointStock.x();
               int yN0 =  n0.pointStock.y();
               int xN1 =  n1.pointStock.x();
               int yN1 =  n1.pointStock.y();
                float epsilon = 0.05;
                qDebug() <<abs(float(xN1-xN0)/(yN1-yN0)-float(event->pos().x()-xN0)/(event->pos().y()-yN0));

               if (abs(float(xN1-xN0)/(yN1-yN0)-float(event->pos().x()-xN0)/(event->pos().y()-yN0))<epsilon)
               {
                 // M est sur la droite formée par A-B

                  qDebug()<<"appartient";
                  for (int deletePoint=n1.posPoint;deletePoint<trajectoireTriggeredBallon.getTrajectoire().size();deletePoint++) {
                   trajectoireTriggeredBallon.getTrajectoire().removeAt(deletePoint);
                  }
                  trajectoireTriggeredBallon.setArrvPoint(n1.pointStock);


                  break;

               } else {
                 // M est en dehors de la droite donc en dehors du segment
               }
               n0 = n1;
           }

       }

       //modifier la trajectoire selectionner
       qDebug()<<"Trajectoire vide ? =" << trajectoire.isEmpty();
       if(!(placeBallonDansTraj) && isModifyTrajectory && !(trajectoire.isEmpty()))
     {

        // int size_select =mesLignes[selecteur].ptint.size();
        trajectoire_entite selectEntity = trajectoire[selecteur];
          int size_select = selectEntity.getTrajectoire().size();
          qDebug() << "Max nombre point " << size_select;

         pointModif.clear();

         for(Points pointSelect : selectEntity.getTrajectoire())
         {
             if(pointSelect.pointModif)
             {
                 if(isInTraj(event->pos(),pointSelect.pointStock))
                 {
                     if(!(pointSelect.pointStock == selectEntity.getTrajectoire().last().pointStock))
                     {
                       qDebug() << "Résultat de result_size" << pointSelect.posPoint;
                       isModif = true;
                         pointModifSelect = pointSelect.posPoint;
                         pointProvisoire = new QList<QPoint>;
                     }
                 }
                 pointModif.append(pointSelect.posPoint);
             }
         }
         //Sélectionne le dernier point de la trajectoire
         pointModif.append(selectEntity.getTrajectoire().last().posPoint);

         //trie des résultat par  ordre croissant
         for(int i=0;i<pointModif.size();i++)
         {

            int x = pointModif[i];
            int j = i;
            while(j>0 && pointModif[j-1] >x)
            {
              pointModif[j] = pointModif[j-1];
              j = j-1;
            }

              pointModif[j] = x;
         }
         qDebug()<<"Contenu de pointModif :" << pointModif;

         update();
     }

     else
     {
         //Création de la trajectoire joueur comme ballon
         if(vitesse_course >=Marche)
                 {
                if(!addPlayer->getTrajectoire().empty())
                {
                addPlayer->clear();
                qDebug() << "Taille : "<< addPlayer->getTrajectoire().size();
                 }
                if(isCreateTrajectory != true ) //Si l'outils est activer
                {

                  qDebug() << "x="<< pointTempTrajectoire.x() <<"\n y=" << pointTempTrajectoire.y();
                  addPlayer->addPoint(pointTempTrajectoire);
                }
                else
                {

                   addPlayer->addPoint(event->pos());
                   addPlayer->setDepPoint(event->pos());
                }
                  qDebug() << "Ajout point de départ : " << event->pos() << "\naddPlayer :"<<addPlayer->getDepPoint();
                  isDrawing = true;
                  mousePressed = true;
                update();
              }

     }
       if(isSupprTrajectory) trajectoire.removeAt(selecteur);

    }
}

void terrainRugby::mouseMoveEvent(QMouseEvent *event)
{

  //Si la souris bouge et que le tracé est active
    /*
     * Souris en forme de croix
     * Coord enregistrer dans trace_j sans joueur définis
     *
    */
    if(!isMoving)
          {
            if ((event->buttons() & Qt::LeftButton) && isDrawing)
            {

              if(enregistPos == true)
              {
                addPlayer->addPoint(event->pos());
                enregistPos= false;
              }
              else
              {
                enregistPos = true;
              }




              qDebug() << "Ajout point intermediaire : "<< event->pos()  << "\naddPlayer last : "<< addPlayer->getTrajectoire().last().pointStock;
            }
            update();

          }


      //Permet de mofifier la trajectoire selectionner
    if(isModifyTrajectory && isModif)

          {

         //Etire la longueur de la trajectoire
      if(unsigned(pointModifSelect) != trajectoire[selecteur].getTrajectoire().first().posPoint && unsigned(pointModifSelect) != trajectoire[selecteur].getTrajectoire().last().posPoint)
       {
          //Modification d'une portion de la trajectoire

            trajectoire[selecteur].setPoints(pointModifSelect,event->pos());
                int limitePoint = pointModif.indexOf(pointModifSelect);

              int intLimitePoint = pointModif[limitePoint] ;
              int intLimiteplus = pointModif[limitePoint+1];
              int intLimitemoins = pointModif[limitePoint-1];
              qDebug() << "limite point" << limitePoint;
              qDebug() << pointModif[limitePoint-1];
              qDebug() << pointModif[limitePoint];
              qDebug() << pointModif[limitePoint+1];

             QPoint P3 = trajectoire[selecteur].getTrajectoire()[intLimiteplus].pointStock;
             QPoint P1 = trajectoire[selecteur].getTrajectoire()[intLimitePoint].pointStock;
             QPoint P2 = trajectoire[selecteur].getTrajectoire()[intLimitePoint].pointStock;
             QPoint P0 = trajectoire[selecteur].getTrajectoire()[intLimitemoins].pointStock;


              QList<QPoint> points;
              points.append(P0);
              points.append(P1);
              points.append(P2);
              points.append(P3);

              if(!(P1.isNull() || P2.isNull() || P3.isNull() || P0.isNull()) && !(pointModif.first() == limitePoint ||pointModif.last() == limitePoint ) )
              {

                Bezier bezier;
                bezier.addControlPoint(P0.x(),P0.y());
                bezier.addControlPoint(P1.x(),P1.y());
                bezier.addControlPoint(P3.x(),P3.y());
                qDebug() <<"Courbe valide :"<< bezier.isValid();

                 std::vector<BezierPoint> cp = bezier.curvePoints();
                 pointProvisoire->clear();
               for(unsigned int i=0;i<cp.size();i++)
                 {
                   qDebug() << "i = "<< i << "cp ="<<cp[i].x() << "y="<<cp[i].y();
                   pointProvisoire->append(QPoint(cp[i].x(),cp[i].y()));
                 }

               int  j=0;
               QList<QPoint> pointSupprimable ;
               for(int k =intLimitemoins+1;k<intLimiteplus;k++)
               {
                pointSupprimable.append(trajectoire[selecteur].getTrajectoire()[k].pointStock);
                trajectoire[selecteur].setPoints(k,QPoint());
               }
               int i;
               for( i=intLimitemoins;i<intLimiteplus;i++)
               {
                 qDebug() << "j=" <<j<<" et pointProvisoire:"<<pointProvisoire->size();
                 if(j<cp.size())
                 {
                   trajectoire[selecteur].setPoints(i,pointProvisoire->value(j));
                 }
                 else
                 {
                   break;
                 }

                 j++;
               }
              }
      }
      update();
    }



}

void terrainRugby::mouseReleaseEvent(QMouseEvent *event)
{
  isMoving = false;
      if(isModifyTrajectory)
      {
       /* if(extremiteTraj>=PointDep)
        {
          qDebug() << "Extrimite traj: " <<extremiteTraj;
          trajectoire[selecteur].modifPoint(*modifExistTrajectoire,extremiteTraj);
          modifExistTrajectoire->clear();
          update();
        }*/

        isModif = false;
        delete pointProvisoire;

      }
      if (event->button() == Qt::LeftButton && isDrawing )
        {

              //Stockage de addTrajectoire dans la liste de trajectoire
                addPlayer->endPoint(event->pos());
                if(!isCreateTrajectory)
                {
                  if(trajectoire.isEmpty()) trajectoire.append(*addPlayer);
                  qDebug() << "x="<< pointTempTrajectoire.x() <<"\n y=" << pointTempTrajectoire.y();
                  //trajectoire.last().setArrvPoint(event->pos());
                }
                else
                {
                   trajectoire.append(*addPlayer);

                }
                isDrawing = false;
                mousePressed = false;


        }
              update();
              calcul_distance *calculJoueur = new calcul_distance(*addPlayer);

              int calcul =calculJoueur->calcul();
              if(calcul != NULL) emit showLabelDistance(calcul);



}
void terrainRugby::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "dropDetect";

        event->acceptProposedAction();



}
//Ajoute un label
void terrainRugby::dropEvent(QDropEvent *event)
{
    qDebug() <<"dropAction detect";
    for(trajectoire_entite traj_seul : qAsConst(trajectoire))
    {
        if (event->mimeData()->hasFormat(TablesTeam::TablePlayerMimeType()) && (isInTraj(event->pos(),traj_seul.getDepPoint())))
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();

            qDebug() <<"bon format";
            QByteArray playerData = event->mimeData()->data(TablesTeam::TablePlayerMimeType());
            QDataStream dataStream(&playerData, QIODevice::ReadOnly);
            QPixmap pixmap;
            QString nom_equipe;
            int joueur_nombre;

            dataStream >> pixmap >> nom_equipe >> joueur_nombre;

            QLabel *playerDrops = new QLabel(this);

            playerDrops->setText(event->mimeData()->text()+"\n"+QString::number(event->pos().x())+":"+QString::number(event->pos().y()));
            playerDrops->setGeometry(event->pos().x(),event->pos().y(),pixmap.size().width(),pixmap.size().height());
            playerDrops->setPixmap(pixmap);
            playerDrops->show();
            struct trajectoire traj ;
            joueur joueur ;
            traj.point_arriv = traj_seul.getArrvPoint();
            traj.point_dep = traj_seul.getDepPoint();
            traj.point_intermed = traj_seul.getTrajectoire();

            joueur.point_appr= event->pos();
            joueur.trajectoire = traj;
            joueur.numero_joueur = joueur_nombre;
            joueur.nom_equipe = nom_equipe;
            qDebug()<<"Nom equipe"<< joueur.nom_equipe;
            joueurs.append(joueur);
            listLabelPlayers.append(playerDrops);
            CreateAnimation *playerAnimation = new CreateAnimation(playerDrops);
            playerAnimation->keyAnim(joueur);
            playerAnimation->setDecalage(2);
            listPlayerAnimation.append(playerAnimation);
        }
        else
         {
            qDebug() << "pas bon";
        }
    }



}
bool terrainRugby::isInTraj(QPoint positionEvent, QPoint positionTraj) const
{
    if((positionTraj.rx()+20 >= positionEvent.rx() && positionTraj.ry()+20 >= positionEvent.ry()))
    {

        if((positionTraj.rx()-20 <= positionEvent.rx() && positionTraj.ry()-20 <= positionEvent.ry()))
         {
            return true;
        }
        else return false;

    }
    else return false;


}

void terrainRugby::addLabelPlayer(joueur joueurLabel)
{
  QLabel *playerLabel = new QLabel(this);
  QString pixmapPath(":img/"+QString::number(joueurLabel.numero_joueur+1)+".png");
  qDebug() << "pixmapPath :"<<pixmapPath;

  playerLabel->setGeometry(joueurLabel.point_appr.x(),joueurLabel.point_appr.y(),71,71);
  QPixmap pixPlayer;
  if(pixPlayer.load(pixmapPath,"PNG"))
  {
    qDebug() << "debug";
  }
  playerLabel->setPixmap(pixPlayer);
  playerLabel->setText(joueurLabel.nom_equipe+"/"+joueurLabel.numero_joueur);
  listLabelPlayers.push_back(playerLabel);
  CreateAnimation *playerAnimation = new CreateAnimation(playerLabel);
  playerAnimation->keyAnim(joueurLabel);
  playerAnimation->setDecalage(2);
  listPlayerAnimation.append(playerAnimation);
  showListsLabel();
}

void terrainRugby::showListsLabel()
{
  for(QLabel* labelPlayer : qAsConst(listLabelPlayers))
  {
    labelPlayer->show();
  }
}

void terrainRugby::customMenuRequested(QPoint pos){


    QMenu *menu=new QMenu(this);
    for(trajectoire_entite trajectoire_tracer : qAsConst(trajectoire))
    {
        if(isInTraj(pos,trajectoire_tracer.getDepPoint()))
        {

            trajectoireTriggeredBallon = trajectoire_tracer;
            QAction *lierBallon = menu->addAction("Lier un ballon à la trajectoire");
            menu->popup(pos);
            connect(lierBallon,SIGNAL(triggered()),this,SLOT(lierBallonATraj()));
        }


    }
}

void terrainRugby::lierBallonATraj()
{
    placeBallonDansTraj = true;
    isCreateTrajectory = true;
    QLabel* labelBallon = new QLabel(this);
      QPixmap pixmapBallon(":/img/ballon.png","PNG");
      QPixmap newImageBallon =pixmapBallon.scaled(QSize(71,71),Qt::KeepAspectRatio);

    labelBallon->setPixmap(newImageBallon);
    labelBallon->setGeometry(trajectoireTriggeredBallon.getDepPoint().x(),trajectoireTriggeredBallon.getDepPoint().y()+20,71,71);
    labelBallon->raise();
    listLabelPlayers.append(labelBallon);

    CreateAnimation *animationBallon = new CreateAnimation(labelBallon);
    animationBallon->keyAnim(trajectoireTriggeredBallon);
    animationBallon->setDecalage(0);
    listPlayerAnimation.append(animationBallon);
    showListsLabel();


}


