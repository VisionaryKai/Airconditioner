#ifndef LOGIN_ROOM_H
#define LOGIN_ROOM_H

#include <QWidget>

namespace Ui {
class login_room;
}

class login_room : public QWidget
{
    Q_OBJECT

public:
    explicit login_room(QWidget *parent = 0);
    ~login_room();
signals:
    void sends_0();
private slots:
    void commit();
    void on_confirm_clicked();

private:
    Ui::login_room *ui;
};

#endif // LOGIN_ROOM_H
