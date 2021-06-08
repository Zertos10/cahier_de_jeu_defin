#include "sqlrequest.h"


//Constructeur de la classe
SqlRequest::SqlRequest(QString dbName, QString ip, QString name, QString password)
{
  db =  QSqlDatabase::addDatabase(sqlDriver);

    this->dbName = dbName;
    this->ip = ip;
    this->name = name;
    this->password = password;



}

SqlRequest::SqlRequest(QString dbName, QString ip, QString name, QString password, QString port)
{
     db =  QSqlDatabase::addDatabase(sqlDriver);
    this->dbName = dbName;
    this->ip = ip;
    this->name = name;
    this->password = password;
    this->port = port;

}

SqlRequest::SqlRequest()
{
  db =  QSqlDatabase::addDatabase(sqlDriver);
}


//Connexion vers la base de donnée
bool SqlRequest::requestConnexion(QString port)
{

    this->port = port;
    db.setDatabaseName(dbName);
    db.setHostName(ip);
    db.setUserName(name);
    db.setPassword(password);
    db.setPort(port.toInt());
    if(db.open())
    {
        qDebug() << "Connexion à la base de donnée effectuer à "+db.databaseName();
        return true;
    }
    else
    {
        qDebug() << "Echec de connexion";
        return false;
    }
}
//Surcharge de la méthode requestConnexion(QString port)
bool SqlRequest::requestConnexion()
{
    db.setDatabaseName(dbName);
    db.setHostName(ip);
    db.setUserName(name);
    db.setPassword(password);
    db.setPort(port.toInt());
    qDebug() << "dbName = " << dbName << "ip = " << ip <<"name = " << name ;

    if(db.open())
    {
        qDebug() << "Connexion à la base de donnée effectuer à "+db.databaseName();
        return true;

    }
    else
    {
        qDebug() << "Echec de connexion";
        return  false;
    }

}


//Donne le dernier id de la table
int SqlRequest::selectLastId(Table table)
{
  QSqlQuery *querySelectId = new QSqlQuery(db);
  QString id_select;
  switch (table) {
     case Table::ID_Cahier_de_jeu:
        id_select = "cahier_de_jeu/cahier_de_jeu.ID_CAHIER_DE_JEU";
    break;

    case Table::ID_Equipe :
       id_select = "equipe/equipe.ID_EQUIPE";
    break;

    case Table::ID_Joueur :
     id_select = "joueur/joueur.ID_JOUEUR";
    break;

    case Table::ID_Ballon :
     id_select = "ballon/ballon.ID_BALLON";
    break;

  case Table::ID_Trajectoire:
    id_select = "trajectoire/trajectoire.ID_TRAJECTOIRE";
    break;

  case Table::ID_Point :
     id_select = "point/point.ID_POINT";
    break;


  }
  QString requestLastId = "SELECT "+id_select.split('/').value(1)+" FROM "+id_select.split('/').value(0)+" ORDER BY "+id_select.split('/').value(1)+" DESC LIMIT 0,1";

  qDebug() << "LastId :" << requestLastId;
  if(querySelectId->exec(requestLastId))
  {


    querySelectId->next();
    qDebug() <<querySelectId->value(0).toInt();
    return  querySelectId->value(0).toInt();
  }
  else
  {
    return -1;
  }


}
//Verifie si le nom existe déja
bool SqlRequest::hasExist(QString nom_cahier_de_jeu)
{
    QSqlQuery *queryExist = new QSqlQuery(db);
    QString requestExist = "SELECT cahier_de_jeu.NOM FROM `cahier_de_jeu` WHERE cahier_de_jeu.NOM = '"+nom_cahier_de_jeu+"'";
    if(queryExist->exec(requestExist))
    {
        return queryExist->next();
    }
    else
    {
        return false;

    }

}

void SqlRequest::updateCahier_de_jeu()
{

}


QString SqlRequest::removeCahier_de_jeu(int id_cahier_de_jeu)
{
  QSqlQuery *deleteQuery = new QSqlQuery(db);
  QString deleteRequest = "DELETE FROM cahier_de_jeu WHERE ID_CAHIER_DE_JEU="+QString::number(id_cahier_de_jeu);
  if(deleteQuery->exec(deleteRequest)) return deleteQuery->lastError().text();
  return "Cahier de jeu supprimer";
}

//Méthode des getters de la classe
QString SqlRequest::getDbName()
{
    return dbName;
}

QString SqlRequest::getIP()
{
    return  ip;
}

QString SqlRequest::getName()
{
    return name;
}

QString SqlRequest::getPassword()
{
    return  password;
}

QString SqlRequest::getPort()
{
    return port;
}


//Méthode des setters de la classe
void SqlRequest::setDbName(QString dbName)
{
    this->dbName = dbName;
}

void SqlRequest::setIp(QString ip)
{
    this->ip = ip;
}

void SqlRequest::setName(QString name)
{
    this->name = name;

}

void SqlRequest::setPassword(QString password)
{
    this->password = password;
}

void SqlRequest::setPort(QString port)
{
  this->port = port;
}

QString SqlRequest::getErrorSql(QSqlQuery *query)
{
  return "Erreur: "+query->lastError().text();
}

