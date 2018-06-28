#ifndef AC_MAINWINDOW_H
#define AC_MAINWINDOW_H

#include <QWidget>

namespace Ui {
class ac_mainwindow;
}

class ac_mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit ac_mainwindow(QWidget *parent = 0);
    ~ac_mainwindow();

private:
    Ui::ac_mainwindow *ui;
    QWidget *parent=0;
private slots:
    void setinfo(int num);
    void clearinfo(int num);
};

#endif // AC_MAINWINDOW_H
