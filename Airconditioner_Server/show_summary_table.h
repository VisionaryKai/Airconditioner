#ifndef SHOW_SUMMARY_TABLE_H
#define SHOW_SUMMARY_TABLE_H

#include <QWidget>

namespace Ui {
class Show_Summary_Table;
}

class Show_Summary_Table : public QWidget
{
    Q_OBJECT

public:
    explicit Show_Summary_Table(QWidget *parent = 0);
    ~Show_Summary_Table();

private slots:
    void on_pushButton_clicked();

    void on_RetBtn_clicked();

private:
    Ui::Show_Summary_Table *ui;
    QWidget *parent=0;
};

#endif // SHOW_SUMMARY_TABLE_H
