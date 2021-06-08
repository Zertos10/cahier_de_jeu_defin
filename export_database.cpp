#include "export_database.h"
#include "ui_export_database.h"

/*export_database::export_database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::export_database)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->port->setInputMask("0000");
}*/

export_database::export_database(cahier_de_jeu_donnee* donnee, QWidget *parent):
  QDialog(parent),
  ui(new Ui::export_database)
{
  ui->setupUi(this);
  ui->password->setEchoMode(QLineEdit::Password);
  ui->port->setInputMask("0000");
  data_export = donnee;
}


export_database::~export_database()
{
    delete ui;
}

void export_database::isConnexionValid()
{
    addRequest = SqlRequest(dbname,adresse_IP,username,password,port);
    if(addRequest.requestConnexion())
    {
        if(addRequest.hasExist(ui->name_cahier_de_jeu->text()))
        {
            QMessageBox *updateMessage = new QMessageBox();
            updateMessage->setWindowTitle("Cahier de jeu existant");
            updateMessage->setText("Un cahier de jeu du même nom est déja enregistrée voulez-vous la mettre à jour ?");
            updateMessage->setIcon(QMessageBox::Information);
            QAbstractButton *miseAjoursButton =  updateMessage->addButton(QString("Mettre à jour"),QMessageBox::AcceptRole);
            QAbstractButton *ajoutButton =  updateMessage->addButton(QString("Ajouter à la base de donnée"),QMessageBox::RejectRole);

            //updateMessage->show();
            updateMessage->exec();

            if(updateMessage->clickedButton() == miseAjoursButton)
               {

                   qDebug() << "Mettre a jours la base de donnée !";

               }
               else if(updateMessage->clickedButton() == ajoutButton)
               {

                    submitCahier_de_jeu();
                    trieParEquipe();
                    data_export->cahier_de_jeu.nom= data_export->cahier_de_jeu.nom+"(1)";
                    QString erreurString =addRequest.insertCahier_de_jeu(*data_export);
                    qDebug()<<erreurString;
                    showError(erreurString);

                   qDebug() << "Rajouter le cahier de jeu";
               }


        }
        else
        {
            submitCahier_de_jeu();
            qDebug()<<"Nom equipe :"<< data_export->joueurs.value(0).nom_equipe;

            trieParEquipe();
            qDebug()<<"Nom equipe:"<< data_export->joueurs.value(0).nom_equipe;

            QString erreurString =addRequest.insertCahier_de_jeu(*data_export);
            showError(erreurString);

        }


    }
    else
    {
        QMessageBox message;
        message.setWindowTitle("Base de donnée erreur ");
        message.setIcon(QMessageBox::Warning);
        message.setText("Erreur : Impossible de se connecter a la base de donnée !");
        message.exec();
    }
}

bool export_database::submitCahier_de_jeu()
{
    data_export->cahier_de_jeu.nom = ui->name_cahier_de_jeu->text();
    qDebug() << "terrain du cahier de jeu :" << data_export->cahier_de_jeu.terrain;

    qDebug() << "nom du cahier de jeu :" << data_export->cahier_de_jeu.nom;

    return true;
}

int export_database::updateCahier_de_jeu()
{

}

void export_database::showError(QString erreurString)
{
  if(erreurString.split(':').value(0) == "-1")
  {
    QMessageBox *validExport = new QMessageBox();
    validExport->setWindowTitle("Cahier de jeu");
    validExport->setText("Le cahier de jeu a été exporté avec succès.");
    validExport->setIcon(QMessageBox::Information);
    QAbstractButton *quitButton = validExport->addButton(QString("Quitter"),QMessageBox::AcceptRole);
    validExport->exec();
    if(validExport->clickedButton() == quitButton)
    {
      validExport->close();
      this->close();
    }
  }
  else
  {
    QMessageBox *errorExport = new QMessageBox();
    errorExport->setWindowTitle("Cahier de jeu");
    errorExport->setText("Une erreur c'est produite lors de l'exportation \nErreur : "+erreurString);
    errorExport->setIcon(QMessageBox::Warning);

  }
}

void export_database::on_Connextion_clicked()
{
     username = ui->username->text();
     password = ui->password->text();
     port = ui->port->text();
     adresse_IP = ui->ip->text();
   QVector<short> *editIsEmpty = new QVector<short>;
   *editIsEmpty = isEditEmpty(username,password,adresse_IP,port);
   //Si les entrée sont vide alors affiche en rouge a l'emplacement
   if(!(editIsEmpty->isEmpty()))
   {
     for(int i=0;i<editIsEmpty->size();i++)
     {
       switch (editIsEmpty->value(i))
       {
        case 0:
         ui->ip->setStyleSheet(getStyleError());
         break;
        case 1:
         ui->username->setStyleSheet(getStyleError());
         break;
       case 2:
        ui->password->setStyleSheet(getStyleError());
        break;
       case 3:
        ui->port->setStyleSheet(getStyleError());
        break;
       }
     }
     return;
   }
   else delete editIsEmpty;

   if(!isIpValid(ipDecomp(adresse_IP)))
   {
     ui->ip->setStyleSheet(getStyleError());
     return;
   }
   qDebug() << isIpValid(ipDecomp(adresse_IP));
  isConnexionValid();

}

void export_database::trieParEquipe()
{
    qDebug() << "trieParEquipe" ;
  QVector<QString> *trieEquipe = new QVector<QString>;
  QList<joueur> *trieJoueur = new QList<joueur>;
  for(const joueur &joueur :qAsConst(data_export->joueurs))
  {
      qDebug() <<"Contient l'équipe du joueur :"<< trieEquipe->contains(joueur.nom_equipe);
     if(!(trieEquipe->contains(joueur.nom_equipe)))
    {
      trieEquipe->push_back(joueur.nom_equipe);
      qDebug() << trieEquipe->last();

    }


  }
  //Fait le trie entre les joueurs appartenant a une équipe ou une autre
  for(const joueur &joueur : qAsConst(data_export->joueurs))
  {
      if(joueur.nom_equipe == trieEquipe->value(0))
      {
          trieJoueur->push_back(joueur);
      }
  }
  //Fait le trie entre les joueurs appartenant a une équipe ou une autre
  for(const joueur &joueur : qAsConst(data_export->joueurs))
  {
      if(joueur.nom_equipe == trieEquipe->value(1))
      {
          trieJoueur->push_back(joueur);
      }
  }
  delete trieEquipe;
  data_export->joueurs = *trieJoueur;

  }
