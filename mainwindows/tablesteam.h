#ifndef TABLESTEAM_H
#define TABLESTEAM_H

#include <QDebug>
#include <QAbstractItemModel>
#include "sql_request/sqlrequest.h"
#include <QtWidgets>



class TablesTeam : public QTableWidget
{
    Q_OBJECT
public:

    //Constructeur de la classe
    explicit TablesTeam(QWidget *parent = nullptr);
    //Ajoute les images qui corresponds aux joueurs de chaque équipes.
    void addTeams();




    //Methode pour les caractéristique du QTableWidget
    void showTable();
    void resetTable();
    void importTable(QVector<QVector<int>> tableauNumJoueur);

    //Setter
    void setTeamName(int index,QString teamName );
    void setTeamName(QVector<QString> teamsName);

    static QString TablePlayerMimeType() { return QStringLiteral("image/png"); }


//Setter de la classe


protected:
    void startDrag(Qt::DropActions) override;

private slots:
    void openTeamModif(int index);
private:

    QString teamsName[2] = {"equipe 1","equipe 2"};
    QVector<QVector<int>> numJoueur ;
    //QWidget *parent = new QWidget;
    QSize *sizeIcon = new QSize(100,100);
    QVector<QString> numplacer;
    QIcon emptyIcon;



signals:

};

#endif // TABLESTEAM_H
