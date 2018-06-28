#include "login_in.h"
#include "ui_login_in.h"
#include "total.h"

Login_in::Login_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login_in)
{
    ui->setupUi(this);
}


bool Login_in::Login_Match(QString UserName, QString PassWord)
{
    /*model->setQuery(QObject::tr("select * from dbo.Login"));

    qDebug() <<model->rowCount();
    for(int i = 0; i < model->rowCount(); i++)
    {
        if(UserName==model->record(i).value("UserName").toString()&&PassWord==model->record(i).value("PassWord").toString())
            return true;
    }*/
    return true;
}

Login_in::~Login_in()
{
    delete ui;
}

void Login_in::on_Login_Btn_clicked()
{
    if(this->Login_Match(ui->UseName_lineEdit->text(),ui->PassWord_lineEdit->text()))
    {
         QMessageBox::information(NULL, QObject::tr("提示"), QObject::tr("登陆成功!"));
         init_config *i=new init_config();
         i->show();
         this->close();
    }
    else
         QMessageBox::critical(NULL, QObject::tr("提示"), QObject::tr("登陆失败!"));

}

