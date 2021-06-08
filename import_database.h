#ifndef IMPORT_DATABASE_H
#define IMPORT_DATABASE_H

#include  <QDialog>
#include <QDebug>
#include <QWidget>
#include <QAbstractItemView>
#include <QTableView>
#include <QTableWidget>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QHeaderView>
#include <database.h>
#include "trace_traj.h"

#include <QLabel>
#include <QtSql/QSql>
#include "sql_request/sql_request_import.h"
#include <QMessageBox>
#include <QHBoxLayout>

enum ErrorMessage {PasErreur=2,ErrorConnexion = 0,ErrorEmptyCahier_de_jeu = -1,ErrorImport = 1};

namespace Ui {
class import_database;
}

class import_database : public QDialog, public database
{
  Q_OBJECT

public:
  explicit import_database(QWidget *parent = nullptr);
  ~import_database();


  //Affichage de la requête:
  void displayCahier_de_jeu();

  //Affichage des erreurs
  void errorMessage(ErrorMessage errorCode , QString errorDet = nullptr);

  ErrorMessage getErrorMessage();
  //getter vers mainWindows
  cahier_de_jeu_donnee getValues();


private slots:
  void import_cahier_de_jeu(QString id_number);
  void on_connection_clicked();
  void suppr_cahier_de_jeu(QString id_number);
private:
  Ui::import_database *ui;
  QString styleError = QString("background-color: rgba(255,54,0,0.44)");
  unsigned short taille = 0;
  QTableWidget *tableWidg = new QTableWidget;
  SQLRequest_import selectRequest;
  cahier_de_jeu_donnee import_donnee;
  ErrorMessage errorCode = PasErreur;




};

#endif // IMPORT_DATABASE_H
