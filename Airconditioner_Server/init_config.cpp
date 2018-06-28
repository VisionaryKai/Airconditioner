#include "init_config.h"
#include "ui_init_config.h"
#include "total.h"

init_config::init_config(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::init_config)
{
    ui->setupUi(this);
    ui->temp_max->setSuffix("°");
    ui->temp_min->setSuffix("°");
    if(cen_ac.get_model()==SUMMER){
        ui->temp_min->setRange(18,25);
        ui->temp_max->setRange(18,25);
        ui->temp_min->setValue(18);
        ui->temp_max->setValue(25);
        ui->summer->setStyleSheet("border-image: url(:/pic/cold.png);");
        ui->winter->setStyleSheet("border-image: url(:/pic/hot_off.png);");
        ui->summer->setEnabled(false);
    }
    else{
        ui->temp_min->setRange(25,30);
        ui->temp_max->setRange(25,30);
        ui->temp_min->setValue(25);
        ui->temp_max->setValue(30);
        ui->winter->setStyleSheet("border-image: url(:/pic/hot.png);");
        ui->summer->setStyleSheet("border-image: url(:/pic/cold_off.png);");
        ui->winter->setEnabled(false);
    }
}

init_config::~init_config()
{
    delete ui;
}

void init_config::on_issure_clicked()
{
    cen_ac.set_max(ui->temp_max->value());
    cen_ac.set_min(ui->temp_min->value());
    //cen_ac.info();
    mainwindows *m=new mainwindows();
    m->show();
    this->close();
}

void init_config::on_summer_clicked()
{
    ui->temp_min->setRange(18,25);
    ui->temp_max->setRange(18,25);
    ui->temp_min->setValue(18);
    ui->temp_max->setValue(25);
    ui->summer->setEnabled(false);
    ui->winter->setEnabled(true);
    ui->summer->setStyleSheet("border-image: url(:/pic/cold.png);");
    ui->winter->setStyleSheet("border-image: url(:/pic/hot_off.png);");
    cen_ac.set_model(SUMMER);
}

void init_config::on_winter_clicked()
{
    ui->temp_min->setRange(25,30);
    ui->temp_max->setRange(25,30);
    ui->temp_min->setValue(25);
    ui->temp_max->setValue(30);
    ui->winter->setEnabled(false);
    ui->summer->setEnabled(true);
    ui->winter->setStyleSheet("border-image: url(:/pic/hot.png);");
    ui->summer->setStyleSheet("border-image: url(:/pic/cold_off.png);");
    cen_ac.set_model(WINTER);
}
