#ifndef SQLREQUEST_H
#define SQLREQUEST_H

#include <QtSql>
#include <QWidget>
#include <QDebug>
#include <QList>
struct cahier_de_jeu_mod
{
  int id;
  QString  nom;
  bool terrain = true;
  QString date;
};
struct Points
{
    unsigned int posPoint;
    QPoint pointStock;
    int speedPoint;
    //Le point peut modifier la courbure de la trajectoire
    bool pointModif =false;
};

struct trajectoire
{
    QPoint point_dep;
    QPoint point_arriv;
    QList<Points> point_intermed;
};

struct joueur
{
    int numero_joueur;
    QString nom_equipe;
    QPoint point_appr;
    trajectoire trajectoire;
};
struct ballon
{
    QPoint pointAppr;
    trajectoire ballonTraj;
};

struct cahier_de_jeu_donnee
{
   cahier_de_jeu_mod cahier_de_jeu;
   QList<joueur> joueurs;
   ballon ballon;
   QString detErreur = "Aucune erreur lors de l'importation";
};

enum Table{ID_Cahier_de_jeu,ID_Equipe,ID_Joueur,ID_Trajectoire,ID_Point,ID_Ballon};

class SqlRequest
{
public:


    //Constructeur de la classe
  SqlRequest(QString dbName,QString ip, QString name,QString password);
  SqlRequest(QString dbName,QString ip, QString name,QString password,QString port);
  SqlRequest();
  //Connexion vers la base de donnée
  bool requestConnexion(QString port);
  bool requestConnexion();

 //Importation d'un cahier de jeu vers le logiciel

  //Recupere le dernier id entrée:
  int selectLastId(Table table);

 // La mise a jours se fait au niveau de la partie ballon , joueur ,trajectoire ... d'abord puis le nom des équipe ou du cahier de jeu les autres variable



  //Requête UPDATE vers la base de donnée
  bool hasExist(QString nom_cahier_de_jeu);//Vérifie si le cahier de jeu existe déja si oui execute updateCahier_de_jeu
  void updateCahier_de_jeu(); //Met à jour les donnée entree sous methode

  //Reqûete INSERT vers la base de donnée



  //Requête DELETE vers la base de donnée


  /*
 La suppression ce fait dans l'ordre suivant :
    -Point
    -Trajectoire
    -Ballon et Joueur
    -Equipe
    -Cahier de jeu
    *si suppresion cascade non fonctionnel

 */
  QString removeCahier_de_jeu(int id_cahier_de_jeu); //Supprimer le cahier de jeu


  //Recupere error

  //Getter de la classe
  QString getDbName();
  QString getIP();
  QString getName();
  QString getPassword();
  QString getPort();
  //Setter de la classe
  void setDbName(QString dbName);
  void setIp(QString ip);
  void setName(QString name);
  void setPassword(QString password);
  void setPort(QString port);

  //Erreur
  QString getErrorSql(QSqlQuery* query);
protected:
  QSqlDatabase db ;
  QString dbName;
  QString ip;
  QString name;
  QString password;
  QString port;
  QString sqlDriver ="QMYSQL";





};

#endif // SQLREQUEST_H
