#ifndef LOGIN_IN
#define LOGIN_IN

#include <QMainWindow>
#include <QString>

namespace Ui {
class Login_in;
}

class Login_in : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login_in(QWidget *parent = 0);
    ~Login_in();
    bool Login_Match(QString UserName, QString PassWord);

private slots:
    void on_Login_Btn_clicked();

private:
    Ui::Login_in *ui;
};
#endif // LOGIN_IN

