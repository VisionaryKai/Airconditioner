#include "mainwindows.h"
#include "ui_mainwindows.h"
#include <total.h>

mainwindows::mainwindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindows)
{
    ui->setupUi(this);
    MainChoice *m=new MainChoice(ui->in_and_out);
    m->show();
    ac_mainwindow *a=new ac_mainwindow(ui->ac);
    a->show();
    ShowCentralAc *s=new ShowCentralAc(ui->cental_ac);
    s->show();
}

mainwindows::~mainwindows()
{
    delete ui;
}
