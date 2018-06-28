#ifndef MAINCHOICE_H
#define MAINCHOICE_H

#include <QWidget>

namespace Ui {
class MainChoice;
}

class MainChoice : public QWidget
{
    Q_OBJECT

public:
    explicit MainChoice(QWidget *parent = 0);
    ~MainChoice();

private slots:
    //void on_Check_inBtn_clicked();

    void on_CheckOutBtn_clicked();

    void on_Check_Btn_clicked();

    void on_Sum_Tab_Btn_clicked();

private:
    Ui::MainChoice *ui;
    QWidget *parent=0;
};

#endif // MAINCHOICE_H
