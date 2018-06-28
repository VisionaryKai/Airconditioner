#include "total.h"

bool SQL_Server_Manager::Login_Match(QString UserName, QString PassWord)
{
    model->setQuery(QObject::tr("select * from dbo.Login"));
    qDebug() <<model->rowCount();
    for(int i = 0; i < model->rowCount(); i++)
    {
        if(UserName==model->record(i).value("UserName").toString()&&PassWord==model->record(i).value("PassWord").toString())
            return true;
    }
    return true;
}

void SQL_Server_Manager::OpenDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                               "SERVER=%1;"
                               "DATABASE=%2;"
                               "UID=%3;"
                               "PWD=%4;").arg("SLIY")
                       .arg("AC_Login")
                       .arg("")
                       .arg(""));
    if(!db.open())
    {

        QMessageBox::warning(0, qApp->tr("Cannot open database"),
                db.lastError().databaseText(), QMessageBox::Cancel);
    }
    else
    {
        query=new QSqlQuery(db);
    }
}

void SQL_Server_Manager::insert_Room_Detail_Info(QString Room_id, QString Time, QString Info, QString Cost, QString Energy, QString User_id)
{
    query->prepare(QObject::tr("insert into dbo.Room_Detail_Info(Room_id,Time,Info,Cost,Energy,User_id)" "values(?,?,?,?,?,?)"));
    query->addBindValue(Room_id);
    query->addBindValue(Time);
    query->addBindValue(Info);
    query->addBindValue(Cost);
    query->addBindValue(Energy);
    query->addBindValue(User_id);
    if (!query->execBatch()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  query->lastError().text());
    }
    qDebug()<<query->exec();
}

void SQL_Server_Manager::insert_Summary_Table(QString Room_id,QString Time_Spend,QString Cost,QString On_Off_Times,QString Temp_Adjust_Times,QString Wind_Adjust_Times,QString Room_Sche_Times,QString User_id,QString Time)
{
    query->prepare(QObject::tr("insert into dbo.Summary_Table(Room_id,Time_Spend,Cost,On_Off_Times,Temp_Adjust_Times,Wind_Adjust_Times,Room_Sche_Times,User_id,Time)" "values(?,?,?,?,?,?,?,?,?)"));

    query->addBindValue(Room_id);
    query->addBindValue(Time_Spend);
    query->addBindValue(Cost);
    query->addBindValue(On_Off_Times);
    query->addBindValue(Temp_Adjust_Times);
    query->addBindValue(Wind_Adjust_Times);
    query->addBindValue(Room_Sche_Times);
    query->addBindValue(User_id);
    query->addBindValue(Time);
    if (!query->execBatch()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  query->lastError().text());
    }
    query->exec();
    qDebug()<<query->lastError().text();
}

QSqlQuery * SQL_Server_Manager:: query_Table(QString StartTime,QString EndTime)
{
    query->exec(QObject::tr("select * from dbo.Summary_Table where Time between '%1' and '%2'").arg(StartTime).arg(EndTime));
    return query;
    return NULL;
}
