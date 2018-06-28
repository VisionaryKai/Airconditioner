#ifndef TOTAL_H
#define TOTAL_H

#define MAX_AC_NUM      5
#define MAX_WORK_NUM    3
#define ROOM_TEMP       22


#define BASE_ENERGY         0.25
#define HIGH_ENERGY         0.25
#define MID_ENERGY          0.5
#define LOW_ENERGY          0.75

#define MID_PERCENT         1
#define LOW_PERCENT         0.75
#define HIGH_PERSENT        1.25

#define COST_ENERGY         0.5

#define BASE_CHANGE_TEMP    0.5
#define BASE_CHANGE_TIME    15
#define MID_CHANGE_TIME     15
#define LOW_CHANGE_TIME     30
#define HIGH_CHANGE_TIME    0

#include <QtSql>
#include <QUdpSocket>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QHostInfo>
#include <QDateTime>
#include <QtNetwork>
#include <QDateTime>

#include "login_in.h"
#include "check_out.h"
#include "mainchoice.h"
#include "mainwindows.h"
#include "mythread.h"
#include "ac_mainwindow.h"
#include "init_config.h"
#include "showcentralac.h"
#include "showac.h"
#include "show_all_ac.h"
#include "show_summary_table.h"

enum MODEL{SUMMER,WINTER};
enum STATE{CLOSE,WORK,WAIT};
enum WIND{LOW=1,MID,HIGH};

class Summary_Table{
private:
    int time_spend;//分钟
    double cost;
    int on_off_times;
    int temp_adjust_times;
    int wind_adjust_times;
    int room_sche_times;
public:
    Summary_Table();
    ~Summary_Table();
    int get_on_off();
    int get_temp();
    int get_wind();
    int get_room();
    double get_cost();
    int get_time();
    void add_on_off();
    void add_temp();
    void add_wind();
    void add_room();
    void add_cost(double c);
    void add_time(int t);
    void init();
};

class Air_Conditioner{
private:
    QString room_id;
    int user_id;
    double aim_temp;
    double current_temp;
    double energy;
    enum WIND wind;
    enum STATE state;
    QDateTime start_time;//调控开始时间
    bool is_check_in;
    QString room_ip;
    QString room_port;
    Summary_Table sum_t;
public:
    Air_Conditioner();
    Air_Conditioner(Air_Conditioner *ac);
    ~Air_Conditioner();
    bool is_in();
    double get_cost();
    double get_energy();
    int get_aim_temp();
    WIND get_cur_wind();
    QString get_room_id();
    STATE get_state();
    double get_current_temp();
    QDateTime get_start_time();
    QString get_room_ip();
    QString get_room_port();
    Summary_Table *get_sum_t();
    void checkin();

    void set_room_id(QString roomid);
    void set_energy(double energy);
    void set_current_temp(double current_temp);
    void set_aim_temp(int aim_temp);
    void set_cur_wind(WIND cur_wind);
    void set_state(STATE state);
    void set_start_time(QDateTime t);
    void set_room_ip(QString ip);
    void set_room_port(QString port);
    void ini_info();
    int get_user_id();
};

class Work_Thread : public QThread
{
    Q_OBJECT
public:
    Work_Thread();
    void run();
    void stop();
    Air_Conditioner *get_ac();
    void set_ac(Air_Conditioner *ac);
    void emit_singal();
    void set_num(int num);
    int get_num();
private:
    int num;
    Air_Conditioner * ac;
    bool stopped;
signals:
    void show_info(int);
    void work_end(int,int);
    void clear(int);
};

class Central_Ac    : public QObject
{
    Q_OBJECT
private:
    int default_temp;
    enum MODEL model;
    int temp_min;
    int temp_max;
    Air_Conditioner all_ac[MAX_AC_NUM];//所有从控机
    int work_ac[MAX_WORK_NUM];
    Work_Thread *work_list[MAX_WORK_NUM];
    STATE state;
    double energy;
    void change_info_start(int i);
    void change_info_stop(int i);
    bool work_manage(int in,int out);
    void manage_list(int type, int list[]);
public:
    Central_Ac();
    ~Central_Ac();
    MODEL get_model();
    int get_def_temp();
    int get_min();
    int get_max();
    Air_Conditioner* get_all_ac();
    STATE get_state();
    double get_energy();
    void add_to_energy(double e);
    void set_model(MODEL mo);
    void set_def_temp(int d);
    void set_min(int m);
    void set_max(int m);
    Work_Thread *get_thread(int position);
    Air_Conditioner get_ac(int position);
    Air_Conditioner get_work_ac(int num);

public slots:
    void manage(int type,int will_manage_position);

signals:
    void change_state(int b);
    void show_state();
    void show_energy();
    void show_info(int);
    void clear_show(int);
private slots:
    void send_show_info(int);
    void send_clear_show(int);
};

class SQL_Server_Manager{
public:
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query;
    bool Login_Match(QString UserName, QString PassWord);
    void OpenDatabase();
    void insert_Room_Detail_Info(QString Room_id,QString Time,QString Info,QString Cost,QString Energy,QString User_id);
    void insert_Summary_Table(QString Room_id,QString Time_Spend,QString Cost,QString On_Off_Times,QString Temp_Adjust_Times,QString Wind_Adjust_Times,QString Room_Sche_Times,QString User_id,QString Time);
    QSqlQuery * query_Table(QString StartTime,QString EndTime);

};

extern SQL_Server_Manager sql_server;
extern Central_Ac cen_ac;
extern QSqlQueryModel *model;
extern QSqlQuery *query;
extern void OpenDatabase();
extern QUdpSocket *Receiver;
extern MyThread *my;
extern Air_Conditioner* find_room(QString ip, QString port);
//extern void bindInterface();


//extern UdpSocket *Rece;
#endif // TOTAL_H
