#include "slave_interface.h"
#include "ui_slave_interface.h"
#include "client_head.h"
#include <QDebug>
QTimer *timer=new QTimer();
QTimer *send_timer=new QTimer();
QTimer *worktime=new QTimer();
QTimer *change_temp_timer=new QTimer();

Slave_interface::Slave_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Slave_interface)
{
    ui->setupUi(this);
    ui->room_edit->setText(ac.get_room_id());
    ui->operate_edit->setVisible(false);
    ui->cost_edit->setVisible(false);
    ui->curr_edit->setVisible(false);
    ui->preset_edit->setVisible(false);
    ui->wind_edit->setVisible(false);
    ui->wow_edit->setVisible(false);
    ui->temp_up->setEnabled(false);
    ui->temp_down->setEnabled(false);
    ui->wind_up->setEnabled(false);
    ui->wind_down->setEnabled(false);

    connect(timer,SIGNAL(timeout()),this,SLOT(change_states()));

    //connect(worktime,SIGNAL(timeout()),this,SLOT(time_operate()));

    connect(send_timer,SIGNAL(timeout()),commun_thread,SLOT(send_1()));
    connect(this,SIGNAL(control_request1()),commun_thread,SLOT(send_1()));
    connect(send_timer,SIGNAL(timeout()),send_timer,SLOT(stop()));
    connect(this,SIGNAL(control_request()),this,SLOT(time_control()));

    connect(this,SIGNAL(info_request()),commun_thread,SLOT(send_2()));
    connect(commun_thread,SIGNAL(change_argument()),this,SLOT(change_arguments()));

    connect(commun_thread,SIGNAL(change_state()),this,SLOT(change_states()));
    connect(commun_thread,SIGNAL(change_state(int)),timer,SLOT(start(int)));

    connect(this,SIGNAL(init_ac()),commun_thread,SLOT(send_3()));
    connect(this,SIGNAL(init_ac(int)),change_temp_timer,SLOT(start(int)));
    connect(change_temp_timer,SIGNAL(timeout()),this,SLOT(change_curr_temp()));
    connect(commun_thread,SIGNAL(stop_temp_timer()),change_temp_timer,SLOT(stop()));
    connect(commun_thread,SIGNAL(start_temp_timer(int)),change_temp_timer,SLOT(start(int)));

    connect(commun_thread,SIGNAL(init_argument()),this,SLOT(init_arguments()));

    connect(this,SIGNAL(close_ac()),commun_thread,SLOT(send_4()));
    connect(commun_thread,SIGNAL(close_ack()),this,SLOT(closed_ac()));
    connect(commun_thread,SIGNAL(control()),commun_thread,SLOT(send_1()));
}

Slave_interface::~Slave_interface()
{
    delete ui;
}

void Slave_interface::change_states()
{
    if(ac.get_state()==WORK)
    {
        emit(info_request());
        ui->wow_edit->setStyleSheet("border-image: url(:/source/work.png);");
    }
    else if(ac.get_state()==WAIT)
    {
        ui->wow_edit->setStyleSheet("border-image: url(:/source/wait.png);");
        timer->stop();
    }
    else
        this->close();
}
void Slave_interface::init_arguments()
{
    if(ac.get_work_mode()==SUMMER)
        ui->operate_edit->setStyleSheet("border-image: url(:/source/cool.png);");
    else if(ac.get_work_mode()==WINTER)
        ui->operate_edit->setStyleSheet("border-image: url(:/source/heat.png);");
    ui->preset_edit->setText(QString::number(ac.get_aim_temp()));
}

void Slave_interface::change_arguments()
{
    ui->energy_edit->setText(QString::number(ac.get_energy()));
    ui->cost_edit->setText(QString::number(ac.get_cost()));
    ui->preset_edit->setText(QString::number(ac.get_aim_temp()));
    ui->curr_edit->setText(QString::number(ac.get_current_temp()));
    if(ac.get_aim_temp()==ac.get_max_temp())
        ui->temp_up->setEnabled(false);
    else if(ac.get_aim_temp()==ac.get_min_temp())
        ui->temp_down->setEnabled(false);
    else
    {
        ui->temp_up->setEnabled(true);
        ui->temp_down->setEnabled(true);
    }
}

//温度上升按钮按下
void Slave_interface::on_temp_up_clicked()
{
    QString upEdit=ui->preset_edit->text();
    int upEdit_int=upEdit.toInt();      //当前目标温度
    if(upEdit_int<ac.get_max_temp())
    {
        upEdit_int++;                   //目标温度上升1°
        ui->preset_edit->setText(QString::number(upEdit_int));
        ac.set_aim_temp(upEdit_int);
        emit(control_request());
        ui->temp_down->setEnabled(true);
    }
    if(upEdit_int==ac.get_max_temp())
        ui->temp_up->setEnabled(false);
}

//温度下降按钮按下
void Slave_interface::on_temp_down_clicked()
{
    QString downEdit=ui->preset_edit->text();
    int downEdit_int=downEdit.toInt();
    if(downEdit_int>ac.get_min_temp())
    {
        downEdit_int--;
        ui->preset_edit->setText(QString::number(downEdit_int));
        ac.set_aim_temp(downEdit_int);
        emit(control_request());
        ui->temp_up->setEnabled(true);
    }
    if(downEdit_int==ac.get_min_temp())
        ui->temp_down->setEnabled(false);
}

//风速下降按钮按下
void Slave_interface::on_wind_down_clicked()
{
    if(ac.get_cur_wind()==MID)
    {
        ui->wind_edit->setStyleSheet("border-image: url(:/source/low_wind.png);");
        ac.set_cur_wind(LOW);
        emit(control_request());
        ui->wind_down->setEnabled(false);
    }
    else if(ac.get_cur_wind()==HIGH)
    {
        ui->wind_edit->setStyleSheet("border-image: url(:/source/mid_wind.png);");
        ac.set_cur_wind(MID);
        emit(control_request());
        ui->wind_up->setEnabled(true);
    }
}

//风速上升按钮按下
void Slave_interface::on_wind_up_clicked()
{
    if(ac.get_cur_wind()==LOW)
    {
        ui->wind_edit->setStyleSheet("border-image: url(:/source/mid_wind.png);");
        ac.set_cur_wind(MID);
        emit(control_request());
        ui->wind_down->setEnabled(true);
    }
    else if(ac.get_cur_wind()==MID)
    {
        ui->wind_edit->setStyleSheet("border-image: url(:/source/high_wind.png);");
        ac.set_cur_wind(HIGH);
        emit(control_request());
        ui->wind_up->setEnabled(false);
    }
}

//从控机开关按下
void Slave_interface::on_switch_2_clicked()
{
    if(!switch_1)       //当前是关机状态
    {
        emit(init_ac());
        emit(init_ac(1000));
        switch_1=true;
        ui->wow_edit->setStyleSheet("border-image: url(:/source/wait.png);");
        ui->switch_2->setStyleSheet("border-image: url(:/source/switch_on.jpg);");
        ui->wind_edit->setStyleSheet("border-image: url(:/source/mid_wind.png);");
        ui->operate_edit->setVisible(true);
        ui->cost_edit->setVisible(true);
        ui->energy_edit->setVisible(true);
        ui->curr_edit->setVisible(true);
        ui->preset_edit->setVisible(true);
        ui->wind_edit->setVisible(true);
        ui->wow_edit->setVisible(true);
        ui->wind_up->setEnabled(true);
        ui->wind_down->setEnabled(true);
        if(25==ac.get_max_temp())
        {
            ui->temp_up->setEnabled(false);
            ui->temp_down->setEnabled(true);
        }
        else if(25==ac.get_min_temp())
        {
            ui->temp_down->setEnabled(false);
            ui->temp_up->setEnabled(true);
        }
        else
        {
            ui->temp_up->setEnabled(true);
            ui->temp_down->setEnabled(true);
        }
        //timer->start(1000);
    }
    else    //当前是开机状态
    {
        emit(close_ac());
    }
}

void Slave_interface::closed_ac()
{
    switch_1=false;
    ui->switch_2->setStyleSheet("border-image: url(:/source/switch_off.jpg);");
    ui->operate_edit->setVisible(false);
    ui->cost_edit->setVisible(false);
    ui->energy_edit->setVisible(false);
    ui->curr_edit->setVisible(false);
    ui->preset_edit->setVisible(false);
    ui->wind_edit->setVisible(false);
    ui->wow_edit->setVisible(false);
    ui->temp_up->setEnabled(false);
    ui->temp_down->setEnabled(false);
    ui->wind_up->setEnabled(false);
    ui->wind_down->setEnabled(false);
}

void Slave_interface::time_control()
{
    send_timer->stop();
    send_timer->start(1000);
}

void Slave_interface::change_curr_temp()
{
    double curr=ac.get_current_temp();
    if(ac.get_work_mode()==SUMMER&&curr<=ac.envir_temp-NATURE_CHANGE)
        curr+=NATURE_CHANGE;
    else if(ac.get_work_mode()==WINTER&&curr>=ac.envir_temp+NATURE_CHANGE)
        curr-=NATURE_CHANGE;
    ac.set_current_temp(curr);
    ui->curr_edit->setText(QString::number(curr));
    if(qAbs(curr-ac.get_wait_begin_temp())>=1&&switch_1)
        emit(control_request1());
}
