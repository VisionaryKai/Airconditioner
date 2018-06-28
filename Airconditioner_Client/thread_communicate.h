#ifndef THREAD_COMMUNICATE
#define THREAD_COMMUNICATE

#include<QThread>
#include<iostream>
#include<QUdpSocket>
class QUdpSocket;
class Thread_Commun:public QThread
{
    Q_OBJECT
public:
    Thread_Commun();

    void run();
    void stop();
    void processPendingDatagram();
protected:

    void communicate();

private:
    volatile bool stopped;
    QUdpSocket *Sender;

signals:
    void login_commit();
    void change_argument();
    void change_state();
    void change_state(int);
    void close_ack();
    void init_argument();
    void control();//开机时当前温度不等于目标温度时发送温控请求
    void stop_temp_timer();
    void start_temp_timer(int);
private slots:
    void send_0();
    void send_1();
    void send_2();
    void send_3();
    void send_4();
    void send_5();
};

#endif // THREAD_COMMUNICATE

