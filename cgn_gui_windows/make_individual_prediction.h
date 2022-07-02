#ifndef MAKE_INDIVIDUAL_PREDICTION_H
#define MAKE_INDIVIDUAL_PREDICTION_H

#include <QWidget>
#include <mainwindow.h>

namespace Ui {
class make_individual_prediction;
}

class make_individual_prediction : public QWidget
{
    Q_OBJECT

public:
    void load_settings();
    void set_pointers(MainWindow *mainwindow,segment_class *segment1);
    explicit make_individual_prediction(QWidget *parent = nullptr);
    ~make_individual_prediction();

private slots:
    void on_pushButton_close_clicked();

    void on_pushButton_make_prediction_clicked();

    void on_lineEdit_enter_data_textChanged(const QString &arg1);

private:
    Ui::make_individual_prediction *ui;
    MainWindow *mainwindow;
    segment_class *segment;
    int length;
    vector<float> data;
    void closeEvent(QCloseEvent *event);
};

#endif // MAKE_INDIVIDUAL_PREDICTION_H
