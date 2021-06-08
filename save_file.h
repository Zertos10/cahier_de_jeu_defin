#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include <QWidget>
#include <QFileDevice>
#include <QFile>
#include <QTextStream>
#include "mainwindow.h"
class Save_file
{
public:
    Save_file();
    //Methode permettant de sauvegarder les paramêtre de conexion a la base de donnée
    void setDataFile();

    //Recupére le fichiers stocker en local
    void getSaveFile(QString nameFile);


private:

};

#endif // SAVE_FILE_H
