#include "database.h"

database::database()
{

}

QStringList database::ipDecomp(QString adresseIP)
{
    return  adresseIP.split(QChar('.'));
}

bool database::isIpValid(QStringList adresseIp_Dec)
{

  for(int i=0;i<adresseIp_Dec.size();i++)
  {
   if(adresseIp_Dec[i].isEmpty())
   {
       return false;
   }
   else
   {
      for(int j=0;j<adresseIp_Dec[i].size();j++)
      {

      }
   }


  }
  return  true;

}

QVector<short> database::isEditEmpty(QString username, QString password, QString adresse_ip, QString port)
{
   QVector<short> *errorEdit = new QVector<short>;
   if(username.isEmpty())  errorEdit->append(ErreurEdit::UserERROR);
   //if(password.isEmpty())  errorEdit->append(ErreurEdit::PasswordERROR);
   if(adresse_ip.isEmpty()) errorEdit->append(ErreurEdit::IpERROR);
   if(port.isEmpty())   errorEdit->append(ErreurEdit::PortERROR);
   return  *errorEdit;

}

QString database::getStyleError()
{
    return styleError;
}



