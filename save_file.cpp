#include "save_file.h"

Save_file::Save_file()
{
    QFile file("in.json") ;


    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&file);
        out << "{ trajectoire : [ traj1 : { pointDep : 1 }]}";
        // writes "Result: 3.14      2.7       "
    }

}
