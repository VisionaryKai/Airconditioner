#include "total.h"

MyThread::MyThread(QObject *parent):
    QThread(parent)
{
    stopped = false;
}

void MyThread::run()
{
    Receiver=new QUdpSocket;
    bool con=Receiver->bind(6665,QUdpSocket::ShareAddress);
    if(!con)
    {
        QMessageBox::critical(NULL, QObject::tr("warning!"), QObject::tr("failed!"));
    }
    else
    {
        communicate();
        stopped=false;
    }
}

void MyThread::stop()
{
    this->stopped=true;
}

void MyThread::communicate()
{
    while(1)
    {
        if(Receiver->hasPendingDatagrams())
            processPendingDatagram();
    }
}

void MyThread::processPendingDatagram()
{
    while(this->Receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        QHostAddress sender;
        quint16 senderPort;

        datagram.resize(this->Receiver->pendingDatagramSize());
        this->Receiver->readDatagram(datagram.data(),datagram.size(),&sender, &senderPort);
        this->MessageDealing(datagram.data(),sender,senderPort);
    }
}

void MyThread::MessageDealing(QString Message, QHostAddress address, quint16 port)
{
    QString ipadress=address.toString();
    QString port1=QString::number(port);
    QString room_id;
    int i=0;
    Air_Conditioner *ac;
    if(Message.startsWith("0;"))
    {
        room_id=bind_ip_room(ipadress,port1);
        QString temp="0;"+room_id+";";
        QByteArray datagram=temp.toLatin1();
        this->Receiver->writeDatagram(datagram.data(),datagram.size(),address,port);

        for(i=0;i<=MAX_AC_NUM-1;i++)
        {
            if(cen_ac.get_ac(i).get_room_id()==room_id)
                break;
        }
        sql_server.insert_Room_Detail_Info(room_id,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),"Check_in","0","0",QString::number(cen_ac.get_ac(i).get_user_id()));
    }
    else if(Message.startsWith("1"))
    {
        QStringList strlist=Message.split(";");

        QString curr=static_cast<QString>(strlist.at(1));
        QString wind=static_cast<QString>(strlist.at(2));
        QString aimTemp=static_cast<QString>(strlist.at(3));
        Air_Conditioner* air_conditioner=cen_ac.get_all_ac();
        ac=find_room(ipadress,port1);
        if(ac->get_cur_wind()!=wind.toInt()){
            ac->get_sum_t()->add_wind();
        }
        if(aimTemp!=curr){
            ac->get_sum_t()->add_temp();
        }
        for(int i=0;i<=MAX_AC_NUM-1;i++)
        {
            if(cen_ac.get_ac(i).get_room_ip()==ipadress)
            {
                air_conditioner[i].set_current_temp(curr.toDouble());
                if(wind=="1")
                    air_conditioner[i].set_cur_wind(LOW);
                else if(wind=="2")
                    air_conditioner[i].set_cur_wind(MID);
                else if(wind=="3")
                    air_conditioner[i].set_cur_wind(HIGH);
                air_conditioner[i].set_aim_temp(aimTemp.toInt());

                cen_ac.manage(1,i);//加入调度队列
            }
        }

        QString temp="1;";
        QByteArray datagram=temp.toLatin1();
        this->Receiver->writeDatagram(datagram.data(),datagram.size(),address,port);
        room_id=ac->get_room_id();
        sql_server.insert_Room_Detail_Info(room_id,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),"Temp_And_Wind",QString::number(ac->get_cost()),QString::number(ac->get_energy()),QString::number(ac->get_user_id()));
    }
    else if(Message.startsWith("2;"))
    {

        for(int i=0;i<=MAX_AC_NUM-1;i++)
        {
            if(cen_ac.get_ac(i).get_room_ip()==ipadress)
            {
                QString energy=QString::number(cen_ac.get_ac(i).get_energy());
                QString cost=QString::number(cen_ac.get_ac(i).get_cost());
                QString curr=QString::number(cen_ac.get_ac(i).get_current_temp());
                QString aim=QString::number(cen_ac.get_ac(i).get_aim_temp());
                QString temp="2;"+energy+";"+cost+";"+curr+";"+aim+";";
                QByteArray datagram=temp.toLatin1();
                this->Receiver->writeDatagram(datagram.data(),datagram.size(),address,port);
                break;
            }
        }
    }
    else if(Message.startsWith("3;"))
    {
        QString mode1;
        if(cen_ac.get_model()==WINTER)
            mode1="1";
        else if(cen_ac.get_model()==SUMMER)
            mode1="0";
        QString temp="3;"+mode1+";"+QString::number(cen_ac.get_min())+";"+QString::number(cen_ac.get_max())+";"+QString::number(cen_ac.get_def_temp())+";";
        QByteArray datagram=temp.toLatin1();
        this->Receiver->writeDatagram(datagram.data(),datagram.size(),address,port);
        ac=find_room(ipadress,port1);
        ac->get_sum_t()->add_on_off();
        sql_server.insert_Room_Detail_Info(ac->get_room_id(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),"Initiate_AC",QString::number(ac->get_cost()),QString::number(ac->get_energy()),QString::number(ac->get_user_id()));
    }
    else if(Message.startsWith("4;"))
    {

        for(int i=0;i<=MAX_AC_NUM-1;i++)
        {
            if(cen_ac.get_ac(i).get_room_ip()==ipadress)
            {
                if(cen_ac.get_ac(i).get_state()==WAIT)
                    cen_ac.get_ac(i).set_state(CLOSE);
                else if(cen_ac.get_ac(i).get_state()==WORK)
                {
                    cen_ac.manage(0,i);
                    cen_ac.get_ac(i).set_state(CLOSE);
                }
            }
        }

        QString temp="4;";
        QByteArray datagram=temp.toLatin1();
        this->Receiver->writeDatagram(datagram.data(),datagram.size(),address,port);
        ac=find_room(ipadress,port1);
        ac->get_sum_t()->add_on_off();
        sql_server.insert_Room_Detail_Info(ac->get_room_id(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),"CLose_AC",QString::number(ac->get_cost()),QString::number(ac->get_energy()),QString::number(ac->get_user_id()));

    }
    else if(Message.startsWith("5;"))
    {
        ac=find_room(ipadress,port1);
        sql_server.insert_Room_Detail_Info(ac->get_room_id(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),"State_Change",QString::number(ac->get_cost()),QString::number(ac->get_energy()),QString::number(ac->get_user_id()));
    }
    else
    {
        QString temp="send back!";
        QByteArray datagram=temp.toLatin1();
        this->Receiver->writeDatagram(datagram.data(),datagram.size(),address,port);
    }
}

QString MyThread::bind_ip_room(QString ip, QString port)
{
    Air_Conditioner* all_ac;
    all_ac=cen_ac.get_all_ac();
    for(int i=0;i<=MAX_AC_NUM-1;i++)
    {
        if(all_ac[i].get_room_ip()=="-1")
        {
            all_ac[i].set_room_ip(ip);
            all_ac[i].set_room_port(port);
            all_ac[i].checkin();
            return all_ac[i].get_room_id();
        }
    }
    return NULL;
}



void MyThread::send_5(int b)
{
    Air_Conditioner* all_ac=cen_ac.get_all_ac();
    QString works;
    if(all_ac[b].get_state()==WORK)
        works="2";
    else if(all_ac[b].get_state()==WAIT)
        works="1";
    else if(all_ac[b].get_state()==CLOSE)
        works="0";
    QHostAddress serverAddress = QHostAddress(all_ac[b].get_room_ip());
    int port=all_ac[b].get_room_port().toInt();
    QString temp="5;"+works+";";
    QByteArray datagram=temp.toLatin1();
    Receiver->writeDatagram(datagram.data(),datagram.size(),serverAddress,port);
}
