#include "total.h"

Central_Ac::Central_Ac(){
    default_temp=25;
    model=SUMMER;
    state=WAIT;
    energy=0;
    if(model==SUMMER){
        temp_min=18;
        temp_max=25;
    }
    else{
        temp_min=25;
        temp_max=30;
    }
    for(int i=0;i<MAX_WORK_NUM;i++)
        work_ac[i]=-1;
    for(int i=0;i<MAX_AC_NUM;i++){
        all_ac[i].set_room_id(QString::number(100+i));
    }
    for(int i=0;i<MAX_WORK_NUM;i++){
        work_list[i]=NULL;
    }
}

Central_Ac::~Central_Ac(){;}

void Central_Ac::change_info_start(int i){
    int j=work_ac[i];
    all_ac[j].set_state(WORK);
    all_ac[j].set_start_time(QDateTime::currentDateTime());
    all_ac[j].get_sum_t()->add_room();
    work_list[i]=new Work_Thread();
    work_list[i]->set_ac(&all_ac[j]);
    work_list[i]->set_num(i);
    work_list[i]->start();
    //发消息工作
    emit(change_state(j));
}

void Central_Ac::change_info_stop(int i){
    work_list[i]->stop();
    while(work_list[i]->isRunning()){;}
    delete work_list[i];
    work_list[i]=NULL;
    int j=work_ac[i];
    all_ac[j].set_state(WAIT);
    int t=all_ac[j].get_start_time().secsTo(QDateTime::currentDateTime());
    all_ac[j].get_sum_t()->add_time(t);
    //发消息工作结束
    emit(change_state(j));
}

//前者表示要调入的空调all_ac下标，后者表示要调出的空调all_ac下标
bool Central_Ac::work_manage(int in_position, int out_position){
    int out_work_position;  //存放后者在work_ac的下标
    if(out_position==-1)     //表示没有要调出的空调
        out_work_position=-1;
    else{       //找到后者在work_ac的下标
        int i;
        for(i=0;i<MAX_WORK_NUM;i++){
            if(work_ac[i]==out_position)
                break;
        }
        if(i==MAX_WORK_NUM) //未找到，出错。
            return false;
        else
            out_work_position=i;
    }
    if(in_position<-1||in_position>MAX_AC_NUM)
        return false;
    if(out_work_position==-1){
        int i;
        for(i=0;i<MAX_WORK_NUM;i++){
            if(work_ac[i]==-1)
                break;
        }
        if(i==MAX_WORK_NUM||in_position==-1){
            return false;
        }
        else{
            work_ac[i]=in_position;
            change_info_start(i);
        }
    }
    else{
        if(in_position==-1){
            change_info_stop(out_work_position);
            work_ac[out_work_position]=-1;
        }
        else{
            //work_list[out_work_position].sleep(1);
            change_info_stop(out_work_position);
            work_ac[out_work_position]=in_position;
            change_info_start(out_work_position);
        }
    }
    int k;
    for(k=0;k<MAX_WORK_NUM;k++){
        if(work_ac[k]!=-1)
            break;
    }
    if(k!=MAX_WORK_NUM)
        this->state=WORK;
    else
        this->state=WAIT;
    emit show_state();
    return true;
}

MODEL Central_Ac::get_model(){
    return model;
}

int Central_Ac::get_def_temp(){
    return default_temp;
}

int Central_Ac::get_min(){
    return temp_min;
}

int Central_Ac::get_max(){
    return temp_max;
}

Air_Conditioner *Central_Ac::get_all_ac()
{
    return all_ac;
}

STATE Central_Ac::get_state()
{
    return this->state;
}

double Central_Ac::get_energy()
{
    double e=this->energy;
    for(int i=0;i<MAX_AC_NUM;i++){
        e+=all_ac[i].get_energy();
    }
    return e;
}

void Central_Ac::add_to_energy(double e)
{
    this->energy+=e;
}

void Central_Ac::set_model(MODEL mo){
    model=mo;
}

void Central_Ac::set_def_temp(int d)
{
    default_temp=d;
}

void Central_Ac::set_min(int m){
    temp_min=m;
}

void Central_Ac::set_max(int m){
    temp_max=m;
}

Work_Thread *Central_Ac::get_thread(int position)
{
    return work_list[position];
}

Air_Conditioner Central_Ac::get_ac(int position)
{
    return all_ac[position];
}

Air_Conditioner Central_Ac::get_work_ac(int num)
{
    return all_ac[work_ac[num]];
}

void Central_Ac::send_show_info(int num)
{
    emit show_info(num);
}

void Central_Ac::send_clear_show(int num)
{
    emit clear_show(num);
}

//type=0,表示后者工作完成要退出调度队列，重新安排一个新空调入队列
//type=1,表示后者有新的温控请求，请求进去调度队列
//will_manage_position表示要处理空调所处的all_ac下标
void Central_Ac::manage(int type,int will_manage_position)
{
    for(int i=0;type==1&&i<MAX_WORK_NUM;i++){
        if(will_manage_position==work_ac[i]){
            work_list[i]->emit_singal();
            return;
        }
    }
    if(type==-1){
        will_manage_position=this->work_ac[will_manage_position];
        type=0;
    }
    int list[MAX_AC_NUM];   //参与调度的空调表
    for(int j=0;j<MAX_AC_NUM;j++)   //初始化
        list[j]=-1;
    manage_list(type,list);    //进一步初始化，把参加调度的空调放入数组中
    if(type==0){       //type=0
        int will_in=list[0];
        for(int j=1;j<MAX_AC_NUM&&list[j]!=-1;j++){
            int now=list[j];
            if(all_ac[will_in].get_cur_wind()<all_ac[now].get_cur_wind()){
                will_in=now;
            }
            else if(all_ac[will_in].get_cur_wind()==all_ac[now].get_cur_wind()){
                if(all_ac[will_in].get_start_time()>all_ac[now].get_start_time())
                    will_in=now;
            }
        }
        if(will_in==-1){    //没有能进入队列的空调
            work_manage(-1,will_manage_position);
        }
        else{
            work_manage(will_in,will_manage_position);
        }
    }
    else if(type==1){  //type=1
        int will_out=will_manage_position;
        for(int j=0;j<MAX_WORK_NUM;j++){
            int now=list[j];
            if(now==-1){
                will_out=-1;
                break;
            }
            else{
                if(all_ac[will_out].get_cur_wind()>all_ac[now].get_cur_wind()){
                    will_out=now;
                }
                else if(all_ac[will_out].get_cur_wind()==all_ac[now].get_cur_wind()&&will_out!=will_manage_position){
                    if(all_ac[will_out].get_start_time()<all_ac[now].get_start_time())
                        will_out=now;
                }
            }
        }
        if(will_out!=will_manage_position){
            work_manage(will_manage_position,will_out);
        }
    }

}

//生成list数组，里面存放参与调度的所有空调在all_ac中的位置下标
void Central_Ac::manage_list(int type,int list[]){
    int k;
    int j;
    if(type==0){
        for(j=0,k=0;j<MAX_AC_NUM;j++){
            if(all_ac[j].get_aim_temp()!=all_ac[j].get_current_temp()&&all_ac[j].get_state()==WAIT){
                list[k]=j;
                k++;
            }
        }
    }
    else if(type==1){
        for(int j=0;j<MAX_WORK_NUM;j++){
            list[j]=work_ac[j];
        }
    }
}
/*
void Central_Ac::work_end_request(int num)
{
    manage(0,work_list[num]);
}
*/
