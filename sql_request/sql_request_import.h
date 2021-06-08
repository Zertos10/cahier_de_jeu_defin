#ifndef SQL_REQUEST_IMPORT_H
#define SQL_REQUEST_IMPORT_H

#include "sqlrequest.h"

class SQLRequest_import : public SqlRequest
{
public:
    SQLRequest_import(SqlRequest db);
    SQLRequest_import();


    //Importer le cahier de jeu
    QList<cahier_de_jeu_mod> selectTable_Cahier_de_jeu() ;
    cahier_de_jeu_donnee importCahier_de_jeu(int id);

private:
    //Recupere la valeur de trajectoire du joueur

    QList<joueur> selectJoueur(int id_equipe, QString equipe_nom);
    ballon selectBallon(int id);
    trajectoire selectTrajectoire(int id_trajectoire);
    Points selectPoints(int id_trajectoire);

};

#endif // SQL_REQUEST_IMPORT_H
