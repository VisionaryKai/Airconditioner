#include "check_out.h"
#include "ui_check_out.h"
#include <total.h>

Check_out::Check_out(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Check_out)
{
    ui->setupUi(this);
    this->parent=parent;
    ui->Check_widget->hide();
}

Check_out::~Check_out()
{
    delete ui;
}

QString Check_out::get_cost(QString room_id)
{
    Air_Conditioner* all_ac;
    all_ac=cen_ac.get_all_ac();
    for(int i=0;i<=MAX_AC_NUM-1;i++){
        if(all_ac[i].get_room_id()==room_id){
            if(all_ac[i].is_in())
                return QString::number(all_ac[i].get_cost());
        }
    }
    return "NULL";
}

void Check_out::on_SureBtn_clicked()
{
    if(this->get_cost(ui->comboBox->currentText())!="NULL")
    {
        ui->Check_widget->show();
        ui->Cost_label->setText(QObject::tr("当前用户的消费金额为:")+this->get_cost(ui->comboBox->currentText()));
    }
    else
    {
        QMessageBox::critical(NULL, QObject::tr("提示"), QObject::tr("该房间未入住!"));
    }
}

void Check_out::on_Check_Btn_clicked()
{
    QMessageBox::information(NULL, QObject::tr("提示"), QObject::tr("结账成功!"));
    QString Room_id;
    Room_id=ui->comboBox->currentText();
    Air_Conditioner* all_ac;
    all_ac=cen_ac.get_all_ac();
    for(int i=0;i<=MAX_AC_NUM-1;i++){
        if(all_ac[i].get_room_id()==Room_id){
            all_ac[i].set_state(CLOSE);
            emit(cen_ac.change_state(i));
            QThread::sleep(1);
            all_ac[i].ini_info();
        }
    }
    MainChoice *ma=new MainChoice(this->parent);
    ma->show();
    this->close();
}

void Check_out::on_Ret_Btn_clicked()
{
    MainChoice *ma=new MainChoice(this->parent);
    ma->show();
    this->close();
}
