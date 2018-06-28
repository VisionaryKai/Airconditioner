#ifndef CHECK_OUT_H
#define CHECK_OUT_H

#include <QWidget>

namespace Ui {
class Check_out;
}

class Check_out : public QWidget
{
    Q_OBJECT

public:
    explicit Check_out(QWidget *parent = 0);
    ~Check_out();
    QString get_cost(QString);

private slots:
    void on_SureBtn_clicked();

    void on_Check_Btn_clicked();

    void on_Ret_Btn_clicked();

private:
    Ui::Check_out *ui;
    QWidget *parent=0;
};

#endif // CHECK_OUT_H
