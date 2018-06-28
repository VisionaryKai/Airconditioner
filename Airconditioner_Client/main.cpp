#include "slave_interface.h"
#include"thread_communicate.h"
#include "client_head.h"
#include"login_room.h"
#include <QApplication>
#include <QDebug>
air_conditioner ac;
center_ac cc;
Thread_Commun *commun_thread=new Thread_Commun();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    commun_thread->start();
    login_room *s=new login_room();
    s->show();
    //Thread_Commun *commun_thread=new Thread_Commun();

    return a.exec();
}
