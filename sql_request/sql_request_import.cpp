#include "sql_request_import.h"

SQLRequest_import::SQLRequest_import(SqlRequest db):SqlRequest(db)
{

}

SQLRequest_import::SQLRequest_import()
{

}

//Requête SELECT qui renvoie la table cahier de jeu
QList<cahier_de_jeu_mod> SQLRequest_import::selectTable_Cahier_de_jeu()
{
       QList<cahier_de_jeu_mod> *cahier_de_jeu_response = new QList<cahier_de_jeu_mod>;
      QSqlQuery *query = new QSqlQuery(db);

    qDebug() << "Access a selectTable_Cahier_de_jeu ,"<< db.isOpen() <<"Nom:"<< db.databaseName();

    if(query->exec("SELECT * FROM `cahier_de_jeu` WHERE 1"))
    {
        int name_cahier_de_jeu_No = query->record().indexOf("nom");
        int id_cahier_de_jeu_No = query->record().indexOf("id_Cahier_de_jeu");
        int terrain_type_No = query->record().indexOf("terrain");
        int date_No = query->record().indexOf("date");
        cahier_de_jeu_mod cahier_de_jeu;

        qDebug() <<"Requête effectuer";
        while(query->next())
        {
            cahier_de_jeu.nom = query->value(name_cahier_de_jeu_No).toString();
            cahier_de_jeu.id = query->value(id_cahier_de_jeu_No).toInt();
            cahier_de_jeu.terrain = query->value(terrain_type_No).toBool();
            cahier_de_jeu.date = query->value(date_No).toString();
            cahier_de_jeu_response->append(cahier_de_jeu);
        }
        for(int i=0;i<cahier_de_jeu_response->size();i++)
          qDebug() << "Id: "<<cahier_de_jeu_response->value(i).id<<"\nNom" << cahier_de_jeu_response->value(i).nom <<"\nTerrain:"<<cahier_de_jeu_response->value(i).terrain
                   <<"\nDate de création:" << cahier_de_jeu_response->value(i).date;
        return  *cahier_de_jeu_response;
    }
    else
     {
        qDebug() << "echec";
        return  *cahier_de_jeu_response;
    }
    qDebug() << query->isActive();

}
//Methode pour importer le cahier de jeu sélectionner vers la classe MainWindows
cahier_de_jeu_donnee SQLRequest_import::importCahier_de_jeu(int id)
{

    QSqlQuery *query = new QSqlQuery(db);
    //Importation donnee
    cahier_de_jeu_donnee *importData = new cahier_de_jeu_donnee;
    qDebug() << "Access a selectTable_Cahier_de_jeu ,"<< db.isOpen();
    QString requestImport("SELECT cahier_de_jeu.NOM,cahier_de_jeu.TERRAIN FROM cahier_de_jeu WHERE cahier_de_jeu.ID_CAHIER_DE_JEU = "+QString::number(id));
    qDebug() <<"cahier de jeu request" << requestImport;

    if(!query->exec(requestImport))
    {
      qDebug() << query->lastError().text();
      importData->detErreur = query->lastError().text();
      return *importData;
    }
        query->first();
        int name_cahier_de_jeu_No = query->record().indexOf("NOM");
        int terrain_type_No = query->record().indexOf("TERRAIN");
        cahier_de_jeu_mod *cahier_import = new cahier_de_jeu_mod;

        cahier_import->nom =  query->value(name_cahier_de_jeu_No).toString();
        cahier_import->terrain = query->value(terrain_type_No).toBool();


        importData->ballon = selectBallon(id);
         qDebug() << "nom cahier de jeu : "<< cahier_import->nom <<"terrain :"<<cahier_import->terrain;

       importData->cahier_de_jeu = *cahier_import;
       //Importation des équipes
       requestImport = "SELECT * FROM equipe WHERE equipe.ID_CAHIER_DE_JEU = "+QString::number(id);
       qDebug() <<"equipes request" << requestImport;
       if(!query->exec(requestImport))
       {
         qDebug() << query->lastError().text();
         importData->detErreur = query->lastError().text();
         return *importData;
      }

           int id_equipe_int = query->record().indexOf("ID_EQUIPE");
           int  equipe_nom_int = query->record().indexOf("NOM_EQUIPE");
           //importation des joueurs
           while(query->next())
           {
               QString equipe_nom = query->value(equipe_nom_int).toString();
               int id_equipe = query->value(id_equipe_int).toInt();
               importData->joueurs << selectJoueur(id_equipe,equipe_nom);
               qDebug() << "Joueur n°"<<importData->joueurs.last().numero_joueur << ",equipe :"<< importData->joueurs.last().nom_equipe
                        <<"\nAvec trajectoire dep:" << importData->joueurs.last().trajectoire.point_dep;

           }

           return *importData;
}

QList<joueur> SQLRequest_import::selectJoueur(int id_equipe,QString equipe_nom)
{
    QSqlQuery *query_player =new QSqlQuery(db);
    QList<joueur> *list_player = new QList<joueur>;
    QString requestPlayer ="SELECT ID_TRAJECTOIRE,NUMERO_JOUEUR,X_JOUEUR_BEGIN,Y_JOUEUR_BEGIN FROM `joueur` WHERE ID_EQUIPE ="+QString::number(id_equipe)+"";
    qDebug() <<"joueur request :"<< requestPlayer;
    if(!query_player->exec(requestPlayer))
    {
      qDebug() << "erreur joueur :"<< query_player->lastError().text();
      return *list_player;
    }
        qDebug() << "size de la requête :" << query_player->size();
        int  id_trajectoire = query_player->record().indexOf("ID_TRAJECTOIRE");
        int num_joueur = query_player->record().indexOf("NUMERO_JOUEUR");
        int  X_joueur_begin = query_player->record().indexOf("X_JOUEUR_BEGIN");
        int  Y_joueur_begin = query_player->record().indexOf("Y_JOUEUR_BEGIN");
        while(query_player->next())
        {
            qDebug() << "crash ?";
            joueur joueurs;
            joueurs.nom_equipe = equipe_nom;
            joueurs.numero_joueur = query_player->value(num_joueur).toInt();
            joueurs.point_appr.setX(query_player->value(X_joueur_begin).toInt());
            joueurs.point_appr.setY(query_player->value(Y_joueur_begin).toInt());
            qDebug() << "Joueur :" << joueurs.numero_joueur <<" de l'équipe : "<<joueurs.nom_equipe <<"point App"<<joueurs.point_appr;

            trajectoire joueur_traj = selectTrajectoire(query_player->value(id_trajectoire).toInt());
            if(!(joueur_traj.point_arriv.isNull() || joueur_traj.point_dep.isNull() || joueur_traj.point_intermed.isEmpty()))
            {
             joueurs.trajectoire = joueur_traj;
             qDebug() << "Trajectoire du joueur : point Depart"<< joueur_traj.point_dep <<"point arrivée :"<<joueur_traj.point_arriv;

             list_player->append(joueurs);
            }
        }
        return *list_player;
}

ballon SQLRequest_import::selectBallon(int id)
{
    QSqlQuery *queryBallon = new QSqlQuery(db);
    QString requestBallon = "SELECT * FROM ballon WHERE ballon.ID_CAHIER_DE_JEU = "+QString::number(id);
    ballon *ballonImport = new ballon;
    if(queryBallon->exec(requestBallon))
    {
      qDebug() << queryBallon->lastError().text();
      return *ballonImport;
    }
        queryBallon->first();
        int id_trajectoire = queryBallon->record().indexOf("ID_TRAJECTOIRE");
        int X_Ballon_begin = queryBallon->record().indexOf("X_BALLON_BEGIN");
        int Y_Ballon_begin = queryBallon->record().indexOf("Y_BALLON_BEGIN");
        ballonImport->pointAppr.setX(queryBallon->value(X_Ballon_begin).toInt());
        ballonImport->pointAppr.setX(queryBallon->value(Y_Ballon_begin).toInt());
        ballonImport->ballonTraj = selectTrajectoire(queryBallon->value(id_trajectoire).toInt());
        qDebug() << "Ballon cahier_de_jeu "<<id <<"Ballon_appr" << ballonImport->pointAppr;
        return *ballonImport;



}

trajectoire SQLRequest_import::selectTrajectoire(int id_trajectoire)
{
    trajectoire trajectory;
    QSqlQuery *queryTraj = new QSqlQuery(db);
    QString requestTraject = "SELECT X_DEPART,Y_DEPART,X_ARRIVEE,Y_ARRIVEE FROM trajectoire WHERE trajectoire.ID_TRAJECTOIRE ="+QString::number(id_trajectoire);
    qDebug() <<"trajectoire request :"<<requestTraject;
   if(!queryTraj->exec(requestTraject))
   {
     qDebug() << queryTraj->lastError().text();
     return trajectory;
   }
       while(queryTraj->next())
       {
           int X_depart = queryTraj->record().indexOf("X_DEPART");
           int Y_depart = queryTraj->record().indexOf("Y_DEPART");
           int X_arrivee = queryTraj->record().indexOf("X_ARRIVEE");
           int Y_arrivee = queryTraj->record().indexOf("Y_ARRIVEE");

           trajectory.point_dep.setX(queryTraj->value(X_depart).toInt());
           trajectory.point_dep.setY(queryTraj->value(Y_depart).toInt());
           trajectory.point_arriv.setX(queryTraj->value(X_arrivee).toInt());
           trajectory.point_arriv.setY(queryTraj->value(Y_arrivee).toInt());

       QString requestPoint = "SELECT * FROM point WHERE point.ID_TRAJECTOIRE ="+QString::number(id_trajectoire);
       qDebug() <<"point request" <<requestPoint;
       if(!queryTraj->exec(requestPoint))
       {
         qDebug() << queryTraj->lastError().text();
         return trajectory;
       }
           qDebug() << "taille de la requête :" << queryTraj->size();
           int id_point = queryTraj->record().indexOf("ID_POINT");
           int pos_pt = queryTraj->record().indexOf("POSITION_POINT");
           int X_pt = queryTraj->record().indexOf("X_POINT");
           int Y_pt = queryTraj->record().indexOf("Y_POINT");
           int speedPoint =queryTraj->record().indexOf("VITESSE_POINT");
           Points pt;
           while (queryTraj->next()) {
               qDebug() << "Point n°:" <<queryTraj->value(id_point).toInt();
               pt.pointStock.setX(queryTraj->value(X_pt).toInt());
               pt.pointStock.setY(queryTraj->value(Y_pt).toInt());
               pt.posPoint = queryTraj->value(pos_pt).toInt();
               pt.pointStock.setX(queryTraj->value(X_pt).toInt());
               pt.speedPoint = queryTraj->value(speedPoint).toInt();
               qDebug() <<"Position n°"<< pt.posPoint<< " Point" << pt.pointStock << "Vitesse:" << pt.speedPoint;
               trajectory.point_intermed.append(pt);


           }

       }
       qDebug() << "Valeur trajectoire " << trajectory.point_arriv ;
       return trajectory;

}
