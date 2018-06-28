#include "total.h"

Summary_Table::Summary_Table(){
    init();
}

Summary_Table::~Summary_Table()
{
    ;
}

void Summary_Table::init(){
    time_spend=0;
    cost=0;
    on_off_times=0;
    temp_adjust_times=0;
    wind_adjust_times=0;
    room_sche_times=0;
}

int Summary_Table::get_on_off()
{
    return this->on_off_times;
}

int Summary_Table::get_temp()
{
    return this->temp_adjust_times;
}

int Summary_Table::get_wind()
{
    return this->wind_adjust_times;
}

int Summary_Table::get_room()
{
    return this->room_sche_times;
}

double Summary_Table::get_cost()
{
    return this->cost;
}

int Summary_Table::get_time()
{
    return this->time_spend;
}

void Summary_Table::add_on_off()
{
    this->on_off_times+=1;
}

void Summary_Table::add_temp()
{
    this->temp_adjust_times+=1;
}

void Summary_Table::add_wind()
{
    this->wind_adjust_times+=1;
}

void Summary_Table::add_room()
{
    this->room_sche_times+=1;
}

void Summary_Table::add_cost(double c)
{
    this->cost+=c;
}

void Summary_Table::add_time(int t)
{
    this->time_spend+=t;
}
