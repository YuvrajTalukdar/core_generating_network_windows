#ifndef SET_CRITICAL_VARIABLE_H
#define SET_CRITICAL_VARIABLE_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class set_critical_variable;
}

class set_critical_variable : public QWidget
{
    Q_OBJECT

    chromosome *critical_variable;
    MainWindow *mainwindow;

public:
    void set_pointers(chromosome *critical_variable,MainWindow *mainwindow);
    explicit set_critical_variable(QWidget *parent = nullptr);
    ~set_critical_variable();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_set_critical_variable_clicked();

private:
    Ui::set_critical_variable *ui;
};

#endif // SET_CRITICAL_VARIABLE_H
