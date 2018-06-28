#ifndef CLIENT_HEAD
#define CLIENT_HEAD

#define NATURE_CHANGE 0.05

#include <QString>
#include<QTime>
#include<QTimer>
#include"thread"
#include"thread_communicate.h"
#include"login_room.h"
#include"slave_interface.h"
#include"QMessageBox"

enum MODEL{SUMMER,WINTER};      //工作模式
enum STATE{CLOSE,WORK,WAIT};    //空调状态
enum WIND{LOW=1,MID,HIGH};      //风速

class center_ac{
private:
    QHostAddress serverAddress;     //中央空调ip地址
    int serverPort;                 //中央空调端口号
public:

    void set_serverAddress(QHostAddress);
    void set_serverPort(int);

    QHostAddress get_serverAddress();
    int get_serverPort();
};

class air_conditioner{
private:
    QString room_id;                //房间号

    STATE state;                    //当前状态
    WIND cur_wind;                  //当前风速
    MODEL work_mode;                //工作模式

    bool chang_time_var=false;      //变化时间间隔变化

    int aim_temp;                   //目标温度
    int max_temp;                   //最高温度
    int min_temp;                   //最低温度

    double current_temp;            //当前温度
    double wait_begin_temp;         //待机开始时温度
    double cost;                    //消费金额
    double energy;                  //消耗能量



public:
    int envir_temp;
    air_conditioner();

    QString get_room_id();

    STATE get_state();
    WIND get_cur_wind();
    MODEL get_work_mode();

    bool get_chang_time_var();

    int get_aim_temp();
    int get_max_temp();
    int get_min_temp();

    double get_current_temp();
    double get_wait_begin_temp();
    double get_cost();
    double get_energy();

    void set_room_id(QString roomid);

    void set_state(STATE state);
    void set_cur_wind(WIND cur_wind);
    void set_work_mode(MODEL workmode);

    void set_chang_time_var(bool chang_time_var);

    void set_aim_temp(int aim_temp);
    void set_max_temp(int max_temp);
    void set_min_temp(int min_temp);

    void set_current_temp(double current_temp);
    void set_wait_begin_temp(double begin_temp);
    void set_cost(double cost);
    void set_energy(double energy);
};

extern air_conditioner ac;
extern center_ac cc;

extern QTimer *timer;           //
extern QTimer *worktime;            //
extern QTimer *send_timer;
extern QTimer *change_temp_timer;   //设置温度自然变化的定时器

extern Thread_Commun *commun_thread;

#endif // CLIENT_HEAD

