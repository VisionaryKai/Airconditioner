#include<thread_communicate.h>
#include<QDebug>
#include"client_head.h"
#include<QtNetwork>
#include<QDebug>
#include<QMessageBox>
#include<slave_interface.h>
Thread_Commun::Thread_Commun()
{
    stopped =false;
}

void Thread_Commun::run()
{
    Sender=new QUdpSocket();
    bool con=Sender->bind(6664,QUdpSocket::ShareAddress);
    if(!con)
    {
        QMessageBox::critical(NULL, QObject::tr("warning!"), QObject::tr("failed!"));
    }
    communicate();
    stopped=false;
}

void Thread_Commun::stop()
{
    stopped = true;
}

void Thread_Commun::processPendingDatagram()
{
    while(this->Sender->hasPendingDatagrams())
    {
        QByteArray datagram;
        QHostAddress sender;
        quint16 senderPort;

        datagram.resize(this->Sender->pendingDatagramSize());
        this->Sender->readDatagram(datagram.data(),datagram.size(),&sender, &senderPort);
        QString data1;
        data1.prepend(datagram);
        if(data1.startsWith("0;"))
        {
           emit(login_commit());
           QStringList strlist=data1.split(";");
           ac.set_room_id(strlist.at(1));
        }
        if(data1.startsWith("1;"))
        {
        }
        if(data1.startsWith("2;"))
        {
            if(ac.get_state()==WAIT)
            {
                continue;
                qDebug()<<"--------"<<ac.get_current_temp();
            }
            else
            {
            QStringList strlist=data1.split(";");
            QString energy1=static_cast<QString>(strlist.at(1));
            ac.set_energy(energy1.toDouble());
            QString cost1=static_cast<QString>(strlist.at(2));
            ac.set_cost(cost1.toDouble());
            QString curr1=static_cast<QString>(strlist.at(3));
            ac.set_current_temp(curr1.toDouble());
            //QString aim1=static_cast<QString>(strlist.at(4));
            //ac.set_aim_temp(aim1.toInt());
            qDebug()<<"--------"<<ac.get_current_temp();
            emit(change_argument());
            }
        }
        if(data1.startsWith("3;"))
        {
            QStringList strlist=data1.split(";");
            QString workmode=static_cast<QString>(strlist.at(1));
            if(workmode=="0")
                ac.set_work_mode(SUMMER);
            else if(workmode=="1")
                ac.set_work_mode(WINTER);
            QString mintemp=static_cast<QString>(strlist.at(2));
            QString maxtemp=static_cast<QString>(strlist.at(3));
            QString aimtemp=static_cast<QString>(strlist.at(4));

            ac.set_min_temp(mintemp.toInt());
            ac.set_max_temp(maxtemp.toInt());
            ac.set_aim_temp(aimtemp.toInt());

            emit(init_argument());
            if(ac.get_aim_temp()!=(int)ac.get_current_temp())
                emit(control());
        }
        if(data1.startsWith("4;"))
        {
            emit(close_ack());
        }
        if(data1.startsWith("5;"))
        {
            QStringList strlist=data1.split(";");
            QString workstate=static_cast<QString>(strlist.at(1));
            if(workstate=="0")
            {
                ac.set_state(CLOSE);

            }
            else if(workstate=="1")
            {
                ac.set_state(WAIT);
                ac.set_wait_begin_temp(ac.get_current_temp());
                qDebug()<<"!!!!!!!!!!!"<<ac.get_wait_begin_temp();
                emit(start_temp_timer(5000));   //待机时温度自变换的定时器，每5秒增加0.05度
            }
            else if(workstate=="2")
            {
                ac.set_state(WORK);
                emit(stop_temp_timer());
            }
            emit(change_state());
            emit(change_state(3000));
            send_5();
        }
    }
}

void Thread_Commun::communicate()
{
    while(1)
    {
        if(Sender->hasPendingDatagrams())
            processPendingDatagram();
    }
}

void Thread_Commun::send_0()
{
    QHostAddress serverAddress = cc.get_serverAddress();
    QString temp="0;";
    QByteArray datagram=temp.toLatin1();
    Sender->writeDatagram(datagram.data(),datagram.size(),serverAddress,cc.get_serverPort());
}
void Thread_Commun::send_1()
{
    QHostAddress serverAddress = cc.get_serverAddress();
    int wind;
    if(ac.get_cur_wind()==LOW)
        wind=1;
    else if(ac.get_cur_wind()==MID)
        wind=2;
    else if(ac.get_cur_wind()==HIGH)
        wind=3;
    QString temp="1;"+QString::number(ac.get_current_temp())+";"+QString::number(wind)+";"+QString::number(ac.get_aim_temp())+";";
    QByteArray datagram=temp.toLatin1();
    Sender->writeDatagram(datagram.data(),datagram.size(),serverAddress,cc.get_serverPort());
}
void Thread_Commun::send_2()
{
    QHostAddress serverAddress = cc.get_serverAddress();
    QString temp="2;";
    QByteArray datagram=temp.toLatin1();
    Sender->writeDatagram(datagram.data(),datagram.size(),serverAddress,cc.get_serverPort());
}
void Thread_Commun::send_3()
{
    QHostAddress serverAddress = cc.get_serverAddress();
    QString temp="3;"+QString::number(ac.get_current_temp())+";";
    QByteArray datagram=temp.toLatin1();
    Sender->writeDatagram(datagram.data(),datagram.size(),serverAddress,cc.get_serverPort());
}
void Thread_Commun::send_4()
{
    QHostAddress serverAddress = cc.get_serverAddress();
    QString temp="4;";
    QByteArray datagram=temp.toLatin1();
    Sender->writeDatagram(datagram.data(),datagram.size(),serverAddress,cc.get_serverPort());
}
void Thread_Commun::send_5()
{
    QHostAddress serverAddress = cc.get_serverAddress();
    QString temp="5;";
    QByteArray datagram=temp.toLatin1();
    Sender->writeDatagram(datagram.data(),datagram.size(),serverAddress,cc.get_serverPort());
}
