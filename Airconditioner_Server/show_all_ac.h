#ifndef SHOW_ALL_AC_H
#define SHOW_ALL_AC_H

#include <QWidget>

namespace Ui {
class Show_All_Ac;
}

class Show_All_Ac : public QWidget
{
    Q_OBJECT

public:
    explicit Show_All_Ac(QWidget *parent = 0);
    ~Show_All_Ac();

private slots:
    void on_RetBtn_clicked();

private:
    Ui::Show_All_Ac *ui;
    QWidget *parent=0;
};

#endif // SHOW_ALL_AC_H
