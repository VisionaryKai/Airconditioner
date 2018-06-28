#ifndef SHOWCENTRALAC_H
#define SHOWCENTRALAC_H

#include <QWidget>

namespace Ui {
class ShowCentralAc;
}

class ShowCentralAc : public QWidget
{
    Q_OBJECT

public:
    explicit ShowCentralAc(QWidget *parent = 0);
    ~ShowCentralAc();
private slots:
    void set_state();
    void set_energy();
private:
    Ui::ShowCentralAc *ui;
};

#endif // SHOWCENTRALAC_H
