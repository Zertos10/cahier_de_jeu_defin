#include "import_database.h"
#include "ui_import_database.h"

import_database::import_database(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::import_database)
{
  ui->setupUi(this);

  ui->mot_de_passe->setEchoMode(QLineEdit::Password);
  //ui->adresse_ip->setInputMask("000.000.000.000");
  ui->port->setInputMask("0000");




}


import_database::~import_database()
{
    delete ui;
}

void import_database::displayCahier_de_jeu()
{
    //Appel de la classe SqlRequest pour effectuer la requête de connexion vers le serveur de base de donnée
    selectRequest = SQLRequest_import(*new SqlRequest(dbname,adresseIP,username,password,port));

    if(selectRequest.requestConnexion())
    {

        QList<cahier_de_jeu_mod> cahier_de_jeu = selectRequest.selectTable_Cahier_de_jeu();

        //Affichage des cahiers de jeu disponible
        if(!cahier_de_jeu.isEmpty())
        {
            int size_cahier_de_jeu_list = cahier_de_jeu.size();

            QTableWidget *tableWidget = new QTableWidget(this);
            tableWidget->setRowCount(size_cahier_de_jeu_list);
            tableWidget->setColumnCount(6);
            //Déclaration du mapper , qu'on connecte au slot
            QSignalMapper *signalButtonSelect = new QSignalMapper(this);
            QObject::connect(signalButtonSelect, SIGNAL(mapped(QString)), this, SLOT(import_cahier_de_jeu(QString)));
            QSignalMapper *signalButtonSuppr = new QSignalMapper(this);
            QObject::connect(signalButtonSuppr, SIGNAL(mapped(QString)), this, SLOT(suppr_cahier_de_jeu(QString)));

            QFont font("Times", 10);
              QFont fontButton("Times", 10);

            for(int i=0;i<size_cahier_de_jeu_list;i++)
            {
                for(int j=0;j<4;j++)
                {



                    if(j==0)
                    {
                        QTableWidgetItem *id_number = new QTableWidgetItem(QString::number(cahier_de_jeu.value(i).id));
                        id_number->setFont(font);
                        //id_number->setTextAlignment(Qt::AlignCenter);
                        tableWidget->setItem(i,j,id_number);
                    }
                    else if(j==1)
                    {
                         QTableWidgetItem *name_cahier = new QTableWidgetItem(cahier_de_jeu.value(i).nom);
                         name_cahier->setFont(font);
                          tableWidget->setItem(i,j,name_cahier);
                    }
                    else if(j==2)
                    {
                         QTableWidgetItem *type_terrain = new QTableWidgetItem();
                         type_terrain->setFont(font);
                        if(cahier_de_jeu.value(i).terrain)
                        {
                            type_terrain->setText("Terrain complet");
                             tableWidget->setItem(i,j,type_terrain);
                        }
                        else
                        {
                            type_terrain->setText("1/2 terrain");
                             tableWidget->setItem(i,j,type_terrain);


                        }
                    }
                    else if(j==3)
                    {
                        QTableWidgetItem *date_cahier = new QTableWidgetItem(cahier_de_jeu.value(i).date);
                        date_cahier->setFont(fontButton);
                        tableWidget->setItem(i,j,date_cahier);
                    }

                }
                //Mappage, puis connexion du signal au mapper

               QPushButton *import_button = new QPushButton("Importer le cahier de jeu");
               import_button->setFont(font);
               tableWidget->setCellWidget(i,4,import_button);

               signalButtonSelect->setMapping(import_button,QString::number(cahier_de_jeu.value(i).id));
               QObject::connect(import_button, SIGNAL(clicked()), signalButtonSelect, SLOT(map()));

               QPushButton *suppr_button = new QPushButton("Supprimer le cahier de jeu");
               suppr_button->setFont(font);
               tableWidget->setCellWidget(i,5,suppr_button);

               signalButtonSuppr->setMapping(suppr_button,QString::number(cahier_de_jeu.value(i).id));
               QObject::connect(suppr_button, SIGNAL(clicked()), signalButtonSuppr, SLOT(map()));
            }

            //Redimisonne le tableau en fonction du nombre de lignes
            tableWidget->resizeColumnsToContents();
            tableWidget->resizeRowsToContents();
            tableWidget->setGeometry(ui->mot_de_passe->x()-180,ui->mot_de_passe->y()+100,0,0);
            tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


            tableWidget->resizeColumnsToContents();
            int width =0, height=0;
            width = tableWidget->horizontalHeader()->length() +
                    tableWidget->verticalHeader()->width();
            height= tableWidget->verticalHeader()->length() +
                    tableWidget->horizontalHeader()->height();
            //Si limite atteint affichage des scroolbar
            if(height > 1000)
            {
                tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
                tableWidget->setFixedSize(1000,height);
            }
            else
            {
                 tableWidget->setFixedSize(width,height);
            }
            tableWidg = tableWidget;
            //Affichage du tableaux
            tableWidg->show();



        }
        else
        {
           errorMessage(ErrorEmptyCahier_de_jeu);
        }

    }
    else
    {
        errorMessage(ErrorConnexion);

    }
}
//Affiche les different message d'erreur
void import_database::errorMessage(ErrorMessage errorCode, QString errorDet)
{
    this->errorCode = errorCode;
    if(errorCode == ErrorConnexion)
   {
        QMessageBox message;
        message.setWindowTitle("Base de donnée erreur ");
        message.setIcon(QMessageBox::Warning);
        message.setText("Erreur : Impossible de se connecter a la base de donnée !");
        message.exec();


    }
    else if(errorCode == ErrorEmptyCahier_de_jeu)
    {
        QMessageBox message_empty;
        message_empty.setText("Erreur : Il n'a pas de cahier de jeu disponible !");
        message_empty.exec();
    }
    else if(errorCode == ErrorImport && !errorDet.isNull())
    {
        QMessageBox message_importError;
        message_importError.setIcon(QMessageBox::Warning);
        message_importError.setWindowTitle("Erreur d'importation");
        message_importError.setText("Erreur : Une erreurs c'est produite lors de l'importation du cahier de jeu!\nVeuillez contacter l'administrateur pour en savoir plus.");
        message_importError.setDetailedText(errorDet);
        message_importError.exec();
    }
}

ErrorMessage import_database::getErrorMessage()
{
    return errorCode;
}



//Lors de l'appuie du bouton de connexion
void import_database::on_connection_clicked()
{
  //Decoupage de la chaine
taille =0;
//Vérification des donnée saisie
  adresseIP = ui->adresse_ip->text();

 qDebug() << "adresseIp_Dec" << ipDecomp(adresseIP);
 QStringList adresseIP_Dec = ipDecomp(adresseIP);

  username = ui->nom_utilisateur->text();
  password = ui->mot_de_passe->text();
  port = ui->port->text();
 QVector<short> *editIsEmpty = new QVector<short>;
 *editIsEmpty = isEditEmpty(username,password,adresseIP,port);
 if(!(editIsEmpty->isEmpty()))
 {
   for(int i=0;i<editIsEmpty->size();i++)
   {
     switch (editIsEmpty->value(i))
     {
      case 0:
       ui->adresse_ip->setStyleSheet(getStyleError());
       break;
      case 1:
       ui->nom_utilisateur->setStyleSheet(getStyleError());
       break;
     case 2:
      ui->mot_de_passe->setStyleSheet(getStyleError());
      break;
     case 3:
      ui->port->setStyleSheet(getStyleError());
      break;
     }
   }
   return;
 }
 else delete editIsEmpty;

//Met en rouge les zone qui comprend une erreur
 if(!isIpValid(adresseIP_Dec))
 {
   ui->adresse_ip->setStyleSheet(getStyleError());
 }
 qDebug() <<ui->adresse_ip->text()  ;
 displayCahier_de_jeu();




}

void import_database::suppr_cahier_de_jeu(QString id_number)
{
  selectRequest.removeCahier_de_jeu(id_number.toInt());


}



//Execute la methode d'importation
void import_database::import_cahier_de_jeu(QString id_number)
{
    qDebug() << "Activer : " <<id_number;
    cahier_de_jeu_donnee  donnee = selectRequest.importCahier_de_jeu(id_number.toInt());
    if(donnee.detErreur == "Aucune erreur lors de l'importation")
    {
        qDebug()<<"importation effectuer";
        import_donnee = donnee;
        errorMessage(PasErreur,"Importation effectuer");
        close();
    }
    else
    {
       errorMessage(ErrorImport,donnee.detErreur);
       close();

    }




}

cahier_de_jeu_donnee import_database::getValues()
{
    return import_donnee;
}



