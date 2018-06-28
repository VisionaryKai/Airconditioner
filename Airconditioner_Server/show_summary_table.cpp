#include "show_summary_table.h"
#include "ui_show_summary_table.h"
#include "total.h"

Show_Summary_Table::Show_Summary_Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_Summary_Table)
{
    ui->setupUi(this);
    this->parent=parent;
    ui->tableWidget->hide();
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setRowCount(13);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色
    QStringList header;
    header.append("Room_id");
    header.append("Time_Spend");
    header.append("Cost");
    header.append("On_Off_TImes");
    header.append("Temp_Adjust_Times");
    header.append("Wind_Adjust_Times");
    header.append("Room_Sche_Times");
    header.append("User_id");
    header.append("Time");
    ui->tableWidget->setHorizontalHeaderLabels(header);
}

Show_Summary_Table::~Show_Summary_Table()
{
    delete ui;
}

void Show_Summary_Table::on_pushButton_clicked()
{
    ui->tableWidget->clearContents();
    QString StartTime=ui->YearBox->currentText()+"-"+ui->MonthBox->currentText()+"-"+ui->DayBox->currentText().append(" 00:00:00");
    QString EndTime=ui->YearBox_3->currentText()+"-"+ui->MonthBox_3->currentText()+"-"+ui->DayBox_3->currentText().append(" 23:59:59");
    QSqlQuery *quer=sql_server.query_Table(StartTime,EndTime);
    ui->tableWidget->show();
    int i=0;
    while(quer->next())
    {
        QSqlRecord record = quer->record();
        QTableWidgetItem* l1 = new QTableWidgetItem(record.value("Room_id").toString());
        ui->tableWidget->setItem(i,0,l1);
        QTableWidgetItem* l2 = new QTableWidgetItem(record.value("Time_Spend").toString());
        ui->tableWidget->setItem(i,1,l2);
        QTableWidgetItem* l3 = new QTableWidgetItem(record.value("Cost").toString());
        ui->tableWidget->setItem(i,2,l3);
        QTableWidgetItem* l4 = new QTableWidgetItem(record.value("On_Off_TImes").toString());
        ui->tableWidget->setItem(i,3,l4);
        QTableWidgetItem* l5 = new QTableWidgetItem(record.value("Temp_Adjust_Times").toString());
        ui->tableWidget->setItem(i,4,l5);
        QTableWidgetItem* l6 = new QTableWidgetItem(record.value("Wind_Adjust_Times").toString());
        ui->tableWidget->setItem(i,5,l6);
        QTableWidgetItem* l7 = new QTableWidgetItem(record.value("Room_Sche_Times").toString());

        ui->tableWidget->setItem(i,6,l7);
        QTableWidgetItem* l8 = new QTableWidgetItem(record.value("User_id").toString());
        ui->tableWidget->setItem(i,7,l8);
        QTableWidgetItem* l9 = new QTableWidgetItem(record.value("Time").toString());
        ui->tableWidget->setItem(i,8,l9);
        i++;
    }
}

void Show_Summary_Table::on_RetBtn_clicked()
{
    MainChoice *ma=new MainChoice(this->parent);
    ma->show();
    this->close();
}
