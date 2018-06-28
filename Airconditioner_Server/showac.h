#ifndef SHOWAC_H
#define SHOWAC_H

#include <QWidget>
#include "total.h"

namespace Ui {
class ShowAc;
}

class Air_Conditioner;

class ShowAc : public QWidget
{
    Q_OBJECT

public:
    explicit ShowAc(QWidget *parent = 0);
    ~ShowAc();
    //void setinfo(int num);
    void on_off_All(bool b);
public:
    //void setinfo(Air_Conditioner ac);
    void setinfo(int num);

private:
    Ui::ShowAc *ui;
};

#endif // SHOWAC_H
