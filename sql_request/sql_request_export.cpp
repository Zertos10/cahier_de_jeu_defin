#include "sql_request_export.h"

SQLRequest_export::SQLRequest_export()
{

}

SQLRequest_export::SQLRequest_export(SqlRequest db):SqlRequest(db)
{

}

QString SQLRequest_export::insertCahier_de_jeu(cahier_de_jeu_donnee export_data)
{
    this->export_data = export_data;

    QString name = export_data.cahier_de_jeu.nom;
    QString date_export = export_data.cahier_de_jeu.date;
    bool terrain_export = export_data.cahier_de_jeu.terrain;
    qDebug() <<"date"<< date_export;
    qDebug() <<"terrain"<< terrain_export;

    QSqlQuery *queryInsertCah = new QSqlQuery(db);

      id_cahier_de_jeu =selectLastId(Table::ID_Cahier_de_jeu)+1;//Reprend le dernier id dans la base de donnée et ajoute 1
     qDebug() <<"id_cahier_de_jeu" <<id_cahier_de_jeu;
    QString requestInsertCah = "INSERT INTO cahier_de_jeu (`ID_CAHIER_DE_JEU`, `NOM`, `TERRAIN`, `DATE`)"
                               " VALUES ("+QString::number(id_cahier_de_jeu)+", '"+QString(name)+"', '"+QString::number(terrain_export)+"', '"+date_export+"')";
    qDebug() << "cahier_de_jeu request:" << requestInsertCah;
      if(!queryInsertCah->exec(requestInsertCah))//Si il a une erreur lors de l'exportation
      {
        return getErrorSql(queryInsertCah);
       }
      if(insertEquipe().split(':').value(0) == '0') return errorExport; //Inserer les équipes dans la base de donnée
      if(insertBallon().split(':').value(0) == '0') return errorExport; //Inserer le ballon dans la base de donnée

      return QString("-1:Pas d'erreur ,exportation effectuer sans erreur");

}

QString SQLRequest_export::insertJoueur()
{
    QSqlQuery *queryJoueur = new QSqlQuery(db);
    for(const joueur &joueur : qAsConst(export_data.joueurs))
    {
      //Vérifie si le nom de l'équipe du joueur est similaire
        if(insertTrajectoire(joueur.trajectoire).split(':').value(0) == '0')
        {
            delete queryJoueur;
            return errorExport;
        }
        if(insertPoints(joueur.trajectoire).split(':').value(0) == '0')
        {
            delete queryJoueur;
            return  errorExport;
        }
        //Ajout de la trajectoire de l'entité
             //Ajout des joueurs
              id_joueur = selectLastId(Table::ID_Joueur)+1;
              id_trajectoire = selectLastId(Table::ID_Trajectoire);
              id_equipe = selectLastId(Table::ID_Equipe);
          QString   requestInsertJoueur =  "INSERT INTO `joueur` (`ID_JOUEUR`, `ID_TRAJECTOIRE`, `ID_EQUIPE`, `NUMERO_JOUEUR`, `X_JOUEUR_BEGIN`, `Y_JOUEUR_BEGIN`) "
                                 "VALUES ('"+QString::number(id_joueur)+"', '"+QString::number(id_trajectoire)+"', '"+QString::number(id_equipe)+"',"
                                 " '"+QString::number(joueur.numero_joueur)+"', '"+QString::number(joueur.point_appr.x())+"', "
                                 "'"+QString::number(joueur.point_appr.x())+"')";

             if(!queryJoueur->exec(requestInsertJoueur)) return getErrorSql(queryJoueur);

    }
    delete  queryJoueur;
    return errorExport;

}

QString SQLRequest_export::insertEquipe()
{
    QSqlQuery *queryEquipe = new QSqlQuery(db);
    QVector<QString> nom_equipe;

    for(const joueur &joueur : qAsConst(export_data.joueurs))
    {
      if(!nom_equipe.contains(joueur.nom_equipe))
      {
        nom_equipe.append(joueur.nom_equipe);
      }
      qDebug() << nom_equipe;

    }

    //Ajout des équipes
    qDebug() << nom_equipe.size()<< "\nNom equipe 1: "<< nom_equipe.value(0)<<"\nNom equipe2"<<nom_equipe.value(1);
      for(int compt_equipe=0 ;compt_equipe<nom_equipe.size();compt_equipe++ )
      {
        id_cahier_de_jeu = selectLastId(Table::ID_Cahier_de_jeu);
        int id_equipe = selectLastId(Table::ID_Equipe)+1;

              QString nom_equipe_temp = export_data.joueurs.value(compt_equipe).nom_equipe;
            QString  requestInsertEquipe = "INSERT INTO `equipe` (`ID_EQUIPE`, `ID_CAHIER_DE_JEU`, `NOM_EQUIPE`)"
                                 "VALUES("+QString::number(id_equipe)+","+QString::number(id_cahier_de_jeu)+",'"+nom_equipe_temp+"')";

              qDebug() <<"equipe request : "<< requestInsertEquipe;
              if(!queryEquipe->exec(requestInsertEquipe))
              {
                  errorExport = "0 :"+getErrorSql(queryEquipe);
                  return errorExport;
               }
             if(insertJoueur().split(':').value(0) == '0') return errorExport;

      }
      delete  queryEquipe;
      return "Equipe : Exportation effectuer avec succée";

}

QString SQLRequest_export::insertBallon()
{
    QSqlQuery *queryInsertBallon = new QSqlQuery(db);
       if(insertTrajectoire(export_data.ballon.ballonTraj).split(':').value(0) == '0')
       {
           delete queryInsertBallon;
           return errorExport;
       }
       if(insertPoints(export_data.ballon.ballonTraj).split(':').value(0) == '0')
       {
           delete queryInsertBallon;
           return errorExport;
       }

     id_ballon = selectLastId(Table::ID_Ballon)+1;
    QString requestInsertBallon = "INSERT INTO `ballon` (`ID_BALLON`, `ID_CAHIER_DE_JEU`, `ID_TRAJECTOIRE`, `X_BALLON_BEGIN`, `Y_BALLON_BEGIN`) "
                    "VALUES ('"+QString::number(id_ballon)+"', '"+QString::number(id_cahier_de_jeu)+"',"
                    " '"+QString::number(id_trajectoire)+"', '"+QString::number(export_data.ballon.pointAppr.rx())+"', "
                    "'"+QString::number(export_data.ballon.pointAppr.ry())+"')";
    qDebug() << "ballon request"<<requestInsertBallon;
if(!queryInsertBallon->exec(requestInsertBallon))
{
    errorExport = getErrorSql(queryInsertBallon);
    return errorExport;
}
    return errorExport;
}

QString SQLRequest_export::insertTrajectoire(trajectoire trajectoire)
{
    //Ajout de la trajectoire
    QSqlQuery *queryTrajectoire = new QSqlQuery(db);
    int id_trajectoire = selectLastId(Table::ID_Trajectoire)+1;
    qDebug() <<"id_trajectoire :" <<id_trajectoire ;
    QPoint pointDep = trajectoire.point_dep;
    QPoint pointArrv = trajectoire.point_arriv;
    qDebug() << "point dep ,trajectoire"<<id_trajectoire<<":" << pointDep <<"\npoint dep"<<trajectoire.point_dep;

    qDebug() << "point Arriv ,trajectoire"<<id_trajectoire<<":" << pointArrv<<"point arrv"<<trajectoire.point_arriv;
    QString requestInsertTrajectoire = "INSERT INTO `trajectoire` (`ID_TRAJECTOIRE`, `ID_CAHIER_DE_JEU`, `X_DEPART`, `Y_DEPART`, `X_ARRIVEE`, `Y_ARRIVEE`) "
                       "VALUES("+QString::number(id_trajectoire)+", "+QString::number(id_cahier_de_jeu)+", "
           ""+QString::number(pointDep.x())+","+QString::number(pointDep.y())+","+QString::number(pointArrv.x())+","
     ""+QString::number(pointArrv.y())+")";
    qDebug()<< "trajectoire joueur request: "<< requestInsertTrajectoire;
    if(!queryTrajectoire->exec(requestInsertTrajectoire))
     {
        errorExport = getErrorSql(queryTrajectoire);
        return errorExport;
      }
    return errorExport;

}

QString SQLRequest_export::insertPoints(trajectoire trajectoire)
{
    QSqlQuery *queryPoints = new QSqlQuery(db);
    //Ajouts des points
    for(Points point_de_traj : qAsConst(trajectoire.point_intermed))
    {
      id_trajectoire = selectLastId(Table::ID_Trajectoire);
      int id_point = selectLastId(Table::ID_Point)+1;
     QString requestInsertPoint = "INSERT INTO `point` (`ID_POINT`, `ID_TRAJECTOIRE`, `POSITION_POINT`, `X_POINT`, `Y_POINT`, `Vitesse_point`) "
                        "VALUES('"+QString::number(id_point)+"','"+QString::number(id_trajectoire)+"'"+
                        ",'"+QString::number(point_de_traj.posPoint)+"',"
                       "'"+QString::number(point_de_traj.pointStock.x())+"','"+QString::number(point_de_traj.pointStock.y())+"',"
                      ""+QString::number(point_de_traj.speedPoint)+")";
      qDebug() << "point request :"<< requestInsertPoint ;
      if(!queryPoints->exec(requestInsertPoint) )
      {
          errorExport = getErrorSql(queryPoints);
          return errorExport;
        }
    }
    delete queryPoints;
    return errorExport;

}



