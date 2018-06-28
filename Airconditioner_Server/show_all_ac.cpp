#include "show_all_ac.h"
#include "ui_show_all_ac.h"
#include "total.h"

Show_All_Ac::Show_All_Ac(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_All_Ac)
{
    ui->setupUi(this);
    this->parent=parent;
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(MAX_AC_NUM);
    QStringList header;
    header.append("room_id");
    header.append("is_in");
    header.append("aim_temp");
    header.append("current_temp");
    header.append("cost");
    header.append("energy");
    header.append("wind");
    header.append("state");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    Air_Conditioner* all_ac;
    all_ac=cen_ac.get_all_ac();
    for(int j=0;j<=MAX_AC_NUM-1;j++)
    {
        QTableWidgetItem* l1 = new QTableWidgetItem(all_ac[j].get_room_id());
        QTableWidgetItem* l2 = new QTableWidgetItem(QString::number(all_ac[j].is_in()));
        QTableWidgetItem* l3 = new QTableWidgetItem(QString::number(all_ac[j].get_aim_temp()));
        QTableWidgetItem* l4 = new QTableWidgetItem(QString::number(all_ac[j].get_current_temp()));
        QTableWidgetItem* l5 = new QTableWidgetItem(QString::number(all_ac[j].get_cost()));
        QTableWidgetItem* l6 = new QTableWidgetItem(QString::number(all_ac[j].get_energy()));
        QTableWidgetItem* l7 = new QTableWidgetItem(QString::number(all_ac[j].get_cur_wind()));
        QTableWidgetItem* l8 = new QTableWidgetItem(QString::number(all_ac[j].get_state()));
        for(int k=0;k<=7;k++)
        {
            if(k==0)
                ui->tableWidget->setItem(j,k,l1);
            else if(k==1)
                ui->tableWidget->setItem(j,k,l2);
            else if(k==2)
                ui->tableWidget->setItem(j,k,l3);
            else if(k==3)
                ui->tableWidget->setItem(j,k,l4);
            else if(k==4)
                ui->tableWidget->setItem(j,k,l5);
            else if(k==5)
                ui->tableWidget->setItem(j,k,l6);
            else if(k==6)
                ui->tableWidget->setItem(j,k,l7);
            else
                ui->tableWidget->setItem(j,k,l8);
        }
    }
}

Show_All_Ac::~Show_All_Ac()
{
    delete ui;
}

void Show_All_Ac::on_RetBtn_clicked()
{
    MainChoice *ma=new MainChoice(this->parent);
    ma->show();
    this->close();
}
