#include "total.h"

SQL_Server_Manager sql_server;
MyThread *my=new MyThread();
Central_Ac cen_ac;
QSqlQueryModel *model=new QSqlQueryModel();
QSqlQuery *query;
QUdpSocket *Receiver=new QUdpSocket();
Air_Conditioner* find_room(QString ip, QString port)
{
    Air_Conditioner* all_ac;
    all_ac=cen_ac.get_all_ac();
    for(int i=0;i<=MAX_AC_NUM-1;i++)
    {
        if(all_ac[i].get_room_ip()==ip&&all_ac[i].get_room_port()==port)
            return &all_ac[i];
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
    sql_server.OpenDatabase();
    Login_in l;
    l.show();
    QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());

    if (info.error() != QHostInfo::NoError)
    {
         qDebug() << "Lookup failed:" << info.errorString();
         //return;
    }
    QString localHostName = QHostInfo::localHostName();
    qDebug() <<"localHostName: "<<localHostName;
    for (int i = 0;i < QHostInfo::fromName(localHostName).addresses().size();i++)
    {
        if(info.addresses()[i].protocol() == QAbstractSocket::IPv4Protocol)
             qDebug() << "Found address:" << info.addresses()[i]<< endl;
    }
    my->start();
    return a.exec();
}
