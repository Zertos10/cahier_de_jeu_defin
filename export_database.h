#ifndef EXPORT_DATABASE_H
#define EXPORT_DATABASE_H

#include <QDialog>
#include "sql_request/sql_request_export.h"
#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include "database.h"


namespace Ui {
class export_database;
}

class export_database : public QDialog ,public database
{
    Q_OBJECT

public:
    //explicit export_database(QWidget *parent = nullptr);
    explicit export_database(cahier_de_jeu_donnee* donnee,QWidget *parent = nullptr);

    ~export_database();
    //Connexion vers la base de donnée si succée fait apparaitre les widgets
    void isConnexionValid();
    //Envoie des donnée vers la classe sqlRequest
    bool submitCahier_de_jeu();
    //Envoie la mise a jours des donnée
    int updateCahier_de_jeu();
    void showError(QString erreurString);
    void trieParEquipe();


private slots:
    void on_Connextion_clicked();

private:


    Ui::export_database *ui;
    SQLRequest_export addRequest;
    QString username;
    QString password;
    QString adresse_IP;
    QString port;
    cahier_de_jeu_donnee* data_export= new cahier_de_jeu_donnee;

};

#endif // EXPORT_DATABASE_H
