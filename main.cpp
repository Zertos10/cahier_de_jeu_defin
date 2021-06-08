#include "mainwindow.h"

#include <QApplication>
#include "save_file.h"
//Prévoit lors du démarrage ouvre le dernier fichiers si choisie

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Save_file file;
  MainWindow w;
  w.show();
  return a.exec();
}
