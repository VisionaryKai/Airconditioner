#include "ac_mainwindow.h"
#include "ui_ac_mainwindow.h"
#include <total.h>

ac_mainwindow::ac_mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ac_mainwindow)
{
    ui->setupUi(this);
    this->parent=parent;
    QObject::connect(&cen_ac,SIGNAL(show_info(int)),this,SLOT(setinfo(int)));
    connect(&cen_ac,SIGNAL(change_state(int)),my,SLOT(send_5(int)));
    connect(&cen_ac,SIGNAL(clear_show(int)),this,SLOT(clearinfo(int)));
}

ac_mainwindow::~ac_mainwindow()
{
    delete ui;
}

void ac_mainwindow::setinfo(int num)
{
    switch(num){
    case 0:
        ui->ac_1->setinfo(num);
        break;
    case 1:
        ui->ac_2->setinfo(num);
        break;
    case 2:
        ui->ac_3->setinfo(num);
        break;
     default:
        break;
    }
}

void ac_mainwindow::clearinfo(int num){
    switch(num){
    case 0:
        ui->ac_1->setinfo(-1);
        break;
    case 1:
        ui->ac_2->setinfo(-1);
        break;
    case 2:
        ui->ac_3->setinfo(-1);
        break;
     default:
        break;
    }
}
