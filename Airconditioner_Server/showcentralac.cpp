#include "showcentralac.h"
#include "ui_showcentralac.h"
#include <total.h>

ShowCentralAc::ShowCentralAc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowCentralAc)
{
    ui->setupUi(this);
    connect(&cen_ac,SIGNAL(show_state()),this,SLOT(set_state()));
    connect(&cen_ac,SIGNAL(show_energy()),this,SLOT(set_energy()));
    ui->default_temp->setAlignment(Qt::AlignCenter);
    ui->energy->setAlignment(Qt::AlignCenter);
    ui->temp_range->setAlignment(Qt::AlignCenter);
    if(cen_ac.get_model()==SUMMER)
        ui->model->setStyleSheet("border-image:url(:/pic/cold.png)");
    else
        ui->model->setStyleSheet("border-image:url(:/pic/hot.png)");
    ui->default_temp->setText(QString::number(cen_ac.get_def_temp()));
    ui->temp_range->setText(QString::number(cen_ac.get_min())+"°~~"+QString::number(cen_ac.get_max())+"°");
    set_state();
    set_energy();
}

ShowCentralAc::~ShowCentralAc()
{
    delete ui;
}

void ShowCentralAc::set_state()
{
    if(cen_ac.get_state()==WAIT){
        ui->state->setStyleSheet("border-image:url(:/pic/wait.png)");
    }
    else{
        ui->state->setStyleSheet("border-image:url(:/pic/work.png)");
    }
}

void ShowCentralAc::set_energy(){
    ui->energy->setText(QString::number(cen_ac.get_energy()));
}
