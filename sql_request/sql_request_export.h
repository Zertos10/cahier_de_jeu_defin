#ifndef SQL_REQUEST_EXPORT_H
#define SQL_REQUEST_EXPORT_H

#include "sqlrequest.h"

class SQLRequest_export : public SqlRequest
{
public:
    SQLRequest_export();
    SQLRequest_export(SqlRequest db);

    //Ajoute le cahier de jeu a la base de donnée
    QString insertCahier_de_jeu(cahier_de_jeu_donnee export_data); //Rajoute un cahier de jeu dans la base de donnée

private:
    QString insertJoueur();
    QString insertEquipe();
    QString insertBallon();
    QString insertTrajectoire(trajectoire trajectoire);


    QString insertPoints(trajectoire trajectoire);

    QString errorExport = "1:Pas d'erreur lors de l'exportation";
    cahier_de_jeu_donnee export_data ;
    int id_cahier_de_jeu;
    int id_joueur;
    int id_equipe;
    int id_ballon;
    int id_trajectoire;
    int id_point;
};

#endif // SQL_REQUEST_EXPORT_H
