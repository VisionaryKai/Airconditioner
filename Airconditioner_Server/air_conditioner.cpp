#include "total.h"

Air_Conditioner::Air_Conditioner(){
    is_check_in=false;
    user_id=1;
    current_temp=-1;
    aim_temp=-1;
    state=CLOSE;
    this->wind=MID;
    this->energy=0;
    this->room_ip=QString::number(-1);
    this->room_port=QString::number(-1);
}

void Air_Conditioner::ini_info(){
    is_check_in=false;
    cen_ac.add_to_energy(this->energy);
    sum_t.add_cost(this->get_cost());
    sql_server.insert_Summary_Table(this->room_id,
                                    QString::number(this->sum_t.get_time()),
                                    QString::number(this->sum_t.get_cost()),
                                    QString::number(this->sum_t.get_on_off()),
                                    QString::number(this->sum_t.get_temp()),
                                    QString::number(this->sum_t.get_wind()),
                                    QString::number(this->sum_t.get_room()),
                                    QString::number(this->user_id),
                                    QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
                                    );
    user_id+=1;
    current_temp=-1;
    aim_temp=-1;
    state=CLOSE;
    this->wind=MID;
    this->energy=0;
    this->room_ip=QString::number(-1);
    this->room_port=QString::number(-1);
    this->sum_t.init();
}

Air_Conditioner::Air_Conditioner(Air_Conditioner *ac){
    this->room_id=ac->get_room_id();
    this->aim_temp=ac->get_aim_temp();
    this->current_temp=ac->get_current_temp();
    this->energy=ac->get_energy();
    this->wind=ac->get_cur_wind();
    this->state=ac->get_state();
}

Air_Conditioner::~Air_Conditioner(){;}

bool Air_Conditioner::is_in()
{
    return this->is_check_in;
}

double Air_Conditioner::get_energy()
{
    return this->energy;
}

double Air_Conditioner::get_cost(){
    return this->energy*COST_ENERGY;
}

int Air_Conditioner::get_aim_temp(){
    return this->aim_temp;
}

WIND Air_Conditioner::get_cur_wind(){
    return this->wind;
}

QString Air_Conditioner::get_room_id(){
    return this->room_id;
}

STATE Air_Conditioner::get_state(){
    return this->state;
}

double Air_Conditioner::get_current_temp(){
    return this->current_temp;
}

QDateTime Air_Conditioner::get_start_time()
{
    return this->start_time;
}

QString Air_Conditioner::get_room_ip()
{
    return this->room_ip;
}

QString Air_Conditioner::get_room_port()
{
    return this->room_port;
}

Summary_Table *Air_Conditioner::get_sum_t()
{
    return &sum_t;
}

void Air_Conditioner::checkin()
{
    this->is_check_in=true;
}

int Air_Conditioner::get_user_id(){
    return this->user_id;
}

void Air_Conditioner::set_room_id(QString roomid){
    this->room_id=roomid;
}

void Air_Conditioner::set_energy(double energy)
{
    this->energy=energy;
}

void Air_Conditioner::set_current_temp(double current_temp){
    this->current_temp=current_temp;
}

void Air_Conditioner::set_aim_temp(int aim_temp){
    this->aim_temp=aim_temp;
}

void Air_Conditioner::set_cur_wind(WIND cur_wind){
    this->wind=cur_wind;
}

void Air_Conditioner::set_state(STATE state){
    this->state=state;
}

void Air_Conditioner::set_start_time(QDateTime t)
{
    this->start_time=t;
}

void Air_Conditioner::set_room_ip(QString ip)
{
    this->room_ip=ip;
}

void Air_Conditioner::set_room_port(QString port)
{
    this->room_port=port;
}
