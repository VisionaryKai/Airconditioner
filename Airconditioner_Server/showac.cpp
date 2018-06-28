#include "showac.h"
#include "ui_showac.h"
#include "total.h"

ShowAc::ShowAc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowAc)
{
    ui->setupUi(this);
    ui->temp->setAlignment(Qt::AlignCenter);
    ui->cur_temp->setAlignment(Qt::AlignCenter);
    ui->money->setAlignment(Qt::AlignCenter);
}

ShowAc::~ShowAc()
{
    delete ui;
}

void ShowAc::setinfo(int num)
{
    if(num==-1){
        on_off_All(false);
        return;
    }
    else
        on_off_All(true);
    Air_Conditioner a=cen_ac.get_work_ac(num);
    ui->cur_temp->setText(QString::number(a.get_current_temp()));
    ui->temp->setText(QString::number(a.get_aim_temp()));
    ui->home_id->setText(a.get_room_id());
    ui->money->setText(QString::number(a.get_cost()));
    ui->energy->setText(QString::number(a.get_energy()));
    switch (a.get_state()) {
    case WORK:
        ui->work_state->setStyleSheet("border-image:url(:/pic/work.png)");
        break;
    case WAIT:
        ui->work_state->setStyleSheet("border-image:url(:/pic/wait.png)");
        break;
    }
    switch(a.get_cur_wind()){
    case LOW:
        ui->wind->setStyleSheet("border-image:url(:/pic/low_wind.png)");
        break;
    case MID:
        ui->wind->setStyleSheet("border-image:url(:/pic/mid_wind.png)");
        break;
    case HIGH:
        ui->wind->setStyleSheet("border-image:url(:/pic/high_wind.png)");
        break;
    }
}

void ShowAc::on_off_All(bool b){
    ui->cur_temp->setVisible(b);
    ui->energy->setVisible(b);
    ui->home_id->setVisible(b);
    ui->money->setVisible(b);
    ui->temp->setVisible(b);
    ui->wind->setVisible(b);
    ui->work_state->setVisible(b);
}
