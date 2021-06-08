#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include "sql_request/sqlrequest.h"

enum ErreurEdit {IpERROR,UserERROR,PasswordERROR,PortERROR};
class database
{
public:
    database();
    QStringList ipDecomp(QString);
    bool isIpValid(QStringList);
    QVector<short> isEditEmpty(QString username,QString password,QString adresse_ip,QString port);
    QString getStyleError();


protected:
    QString password;
    QString username;
    QString adresseIP;
    QString dbname = "base_cahier_de_jeu_2";
    QString port;

private:
   QString styleError = QString("background-color: rgba(255,54,0,0.44)");

   //identifiant

};


#endif // DATABASE_H
