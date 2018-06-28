#ifndef SLAVE_INTERFACE_H
#define SLAVE_INTERFACE_H

#include <QMainWindow>
//#include"thread"
//#include"thread_communicate.h"
namespace Ui {
class Slave_interface;
}

class Slave_interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Slave_interface(QWidget *parent = 0);
    bool switch_1=false;
    ~Slave_interface();

signals:
    void control_request();
    void info_request();
    void close_ac();
    void init_ac();
    void init_ac(int);
    void control_request1();

private slots:
    void on_temp_up_clicked();

    void on_temp_down_clicked();

    void on_wind_up_clicked();

    void on_switch_2_clicked();

    void on_wind_down_clicked();

    void change_arguments();

    void change_states();

    void time_control();

    void closed_ac();

    void init_arguments();

    void change_curr_temp();
    //void time_operate();
private:
    Ui::Slave_interface *ui;

    //Thread_Commun thread_com;
};

#endif // SLAVE_INTERFACE_H
