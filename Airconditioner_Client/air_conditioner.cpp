#include"client_head.h"

air_conditioner::air_conditioner()  //构造函数，初始化从控机的部分属性
{
    state=WAIT;             //初始状态为待机
    cur_wind=MID;           //初始风速为中风
    current_temp=30;        //初始温度为30度
    wait_begin_temp=25;     //初始待机开始温度为25度
    aim_temp=25;            //目标温度初始值为25度
    cost=0;                 //初始消费金额
    energy=0;               //初始消耗能量
    envir_temp=30;          //环境温度为30度，待机时会趋近于此温度
}

QString air_conditioner::get_room_id(){return this->room_id;}

STATE air_conditioner::get_state(){return this->state;}
WIND air_conditioner::get_cur_wind(){return this->cur_wind;}
MODEL air_conditioner::get_work_mode(){return work_mode;}

bool air_conditioner::get_chang_time_var(){return this->chang_time_var;}

int air_conditioner::get_aim_temp(){return this->aim_temp;}
int air_conditioner::get_max_temp(){return this->max_temp;}
int air_conditioner::get_min_temp(){return this->min_temp;}

double air_conditioner::get_current_temp(){return this->current_temp;}
double air_conditioner::get_wait_begin_temp(){return this->wait_begin_temp;}
double air_conditioner::get_cost(){return this->cost;}
double air_conditioner::get_energy(){return this->energy;}

void air_conditioner::set_room_id(QString roomid){this->room_id=roomid;}

void air_conditioner::set_state(STATE state){this->state=state;}
void air_conditioner::set_cur_wind(WIND cur_wind){this->cur_wind=cur_wind;}
void air_conditioner::set_work_mode(MODEL workmode){this->work_mode=workmode;}

void air_conditioner::set_chang_time_var(bool chang_time_var){this->chang_time_var=chang_time_var;}

void air_conditioner::set_aim_temp(int aim_temp){this->aim_temp=aim_temp;}
void air_conditioner::set_max_temp(int max_temp){this->max_temp=max_temp;}
void air_conditioner::set_min_temp(int min_temp){this->min_temp=min_temp;}

void air_conditioner::set_current_temp(double current_temp){this->current_temp=current_temp;}
void air_conditioner::set_wait_begin_temp(double begin_temp){this->wait_begin_temp=begin_temp;}
void air_conditioner::set_cost(double cost){this->cost=cost;}
void air_conditioner::set_energy(double energy){this->energy=energy;}
