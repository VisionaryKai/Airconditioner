#include "total.h"

Work_Thread::Work_Thread()
{
    num=-1;
    this->ac=NULL;
    stopped=false;
    connect(this,SIGNAL(show_info(int)),&cen_ac,SLOT(send_show_info(int)));
    connect(this,SIGNAL(work_end(int,int)),&cen_ac,SLOT(manage(int,int)));
    connect(this,SIGNAL(clear(int)),&cen_ac,SLOT(send_clear_show(int)));
}

void Work_Thread::run()
{
    stopped=false;
    emit_singal();
    while(!stopped){     //5秒发生一次变化，用于测试
       sleep(BASE_CHANGE_TIME);
       if(qAbs(ac->get_aim_temp()-ac->get_current_temp())<0.5){
           ac->set_current_temp(ac->get_aim_temp());
       }
       if(ac->get_current_temp()<ac->get_aim_temp()){
           if(ac->get_cur_wind()==HIGH){
               sleep(HIGH_CHANGE_TIME);
               ac->set_current_temp(ac->get_current_temp()+BASE_CHANGE_TEMP);
               ac->set_energy(ac->get_energy()+HIGH_ENERGY*HIGH_PERSENT);
           }
           else if(ac->get_cur_wind()==MID){
               sleep(MID_CHANGE_TIME);
               ac->set_current_temp(ac->get_current_temp()+BASE_CHANGE_TEMP);
               ac->set_energy(ac->get_energy()+MID_ENERGY*MID_PERCENT);
           }
           else if(ac->get_cur_wind()==LOW){
               sleep(LOW_CHANGE_TIME);
               ac->set_current_temp(ac->get_current_temp()+BASE_CHANGE_TEMP);
               ac->set_energy(ac->get_energy()+LOW_ENERGY*LOW_PERCENT);
           }
           if(!stopped)
                emit_singal();
       }
       else if(ac->get_current_temp()>ac->get_aim_temp()){
           if(ac->get_cur_wind()==HIGH){
               sleep(HIGH_CHANGE_TIME);
               ac->set_current_temp(ac->get_current_temp()-BASE_CHANGE_TEMP);
               ac->set_energy(ac->get_energy()+HIGH_ENERGY*HIGH_PERSENT);
           }
           else if(ac->get_cur_wind()==MID){
               sleep(MID_CHANGE_TIME);
               ac->set_current_temp(ac->get_current_temp()-BASE_CHANGE_TEMP);
               ac->set_energy(ac->get_energy()+MID_ENERGY*MID_PERCENT);
           }
           else if(ac->get_cur_wind()==LOW){
               sleep(LOW_CHANGE_TIME);
               ac->set_current_temp(ac->get_current_temp()-BASE_CHANGE_TEMP);
               ac->set_energy(ac->get_energy()+LOW_ENERGY*LOW_PERCENT);
           }
           if(!stopped)
                emit_singal();
       }
       else{
           emit work_end(-1,num);
           while(!stopped){;}
           //工作完成，发信号，结束线程
       }
    }
    num=-1;
    ac=NULL;
    this->quit();
}

void Work_Thread::stop()
{ 
    emit clear(num);
    stopped=true;
}

Air_Conditioner *Work_Thread::get_ac()
{
    return this->ac;
}

void Work_Thread::set_ac(Air_Conditioner *ac)
{
    this->ac=ac;
}

void Work_Thread::emit_singal(){
    emit cen_ac.show_energy();
    emit show_info(num);
}

void Work_Thread::set_num(int num)
{
    this->num=num;
}

int Work_Thread::get_num()
{
    return this->num;
}
