#ifndef INIT_CONFIG_H
#define INIT_CONFIG_H

#include <QWidget>

namespace Ui {
class init_config;
}

class init_config : public QWidget
{
    Q_OBJECT

public:
    explicit init_config(QWidget *parent = 0);
    ~init_config();

private slots:
    void on_issure_clicked();

    void on_summer_clicked();

    void on_winter_clicked();

private:
    Ui::init_config *ui;
};

#endif // INIT_CONFIG_H
