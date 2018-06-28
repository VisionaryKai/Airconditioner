#include "login_room.h"
#include "ui_login_room.h"
#include"client_head.h"

login_room::login_room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_room)
{
    ui->setupUi(this);
    connect(this,SIGNAL(sends_0()),commun_thread,SLOT(send_0()));
    connect(commun_thread,SIGNAL(login_commit()),this,SLOT(commit()));

}

login_room::~login_room()
{
    delete ui;
}

void login_room::commit()
{
    Slave_interface *s=new Slave_interface();
    s->show();
    this->close();
}

void login_room::on_confirm_clicked()
{
    if(ui->ip_edit->text()!=""&&ui->port_edit->text()!="")
    {
        QHostAddress address=(QHostAddress)ui->ip_edit->text();
        cc.set_serverAddress(address);
        cc.set_serverPort(ui->port_edit->text().toInt());
        emit(sends_0());
    }
    else
    {
        QMessageBox::information(NULL, QString("警告"), QString("输入错误"));
        ui->ip_edit->clear();
        ui->port_edit->clear();
    }
}
