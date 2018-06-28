#include "mainchoice.h"
#include "ui_mainchoice.h"
#include <total.h>

MainChoice::MainChoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainChoice)
{
    ui->setupUi(this);
    this->parent=parent;
}

MainChoice::~MainChoice()
{
    delete ui;
}


void MainChoice::on_CheckOutBtn_clicked()
{
    Check_out *out=new Check_out(this->parent);
    out->show();
    this->close();
}

void MainChoice::on_Check_Btn_clicked()
{
    Show_All_Ac *sh=new Show_All_Ac(this->parent);
    sh->show();
    this->close();
}

void MainChoice::on_Sum_Tab_Btn_clicked()
{
    Show_Summary_Table *shst=new Show_Summary_Table(this->parent);
    shst->show();
    this->close();
}
