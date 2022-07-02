#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <QtConcurrent/QtConcurrent>
#include "core_generating_network_win/segment_class.h"
//#include"segment_thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class segment_thread : public QThread
{
    Q_OBJECT
private:
    string file_name_local;
    int test_train_predict;
    string segment_save_file_name;
    int no_of_threads;
    chromosome critical_variables;
    unsigned int iterations;
    unsigned int population_size;
    unsigned int mutation_percentage;
    //QTextEdit *status_box1;
public:
    explicit segment_thread(QObject *parent):QThread(parent)
    {}
    void load_settings(string file_name_local1,
           int test_train_predict1,
           string segment_save_file_name1,
           int no_of_threads1,
           chromosome critical_variables1,
           unsigned int iterations1,
           unsigned int population_size1,
           unsigned int mutation_percentage1)
    {
        file_name_local=file_name_local1;
        test_train_predict=test_train_predict1;
        segment_save_file_name=segment_save_file_name1;
        no_of_threads=no_of_threads1;
        critical_variables=critical_variables1;
        iterations=iterations1;
        population_size=population_size1;
        mutation_percentage=mutation_percentage1;
    }

    void print_function2(string status)
    {
        emit segment_thread::send_status(status);
    }

    void run();
signals:
     void send_status(string status);
     void send_complete_signal();

signals:

public slots:

};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    chromosome critical_variable;
    bool critical_variable_set=false;
public:
    void cv_set();
    void stop_predict_mode();
    void add_predict_info(vector<float> data,int label);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void display_elements(int index);

    void on_pushButton_select_dataset_clicked();

    void on_pushButton_select_network_clicked();

    void on_pushButton_set_critical_variable_clicked();

    void on_pushButton_clear_critical_variable_clicked();

    void on_pushButton_start_clicked();

    bool check_if_settings_ok(int index);

    bool is_num_float(string s);

    bool is_num_int(string s);

public slots:
    void receive_status(string status);
    void receive_complete_signal();

private:
    //QThread *s_thread;
    Ui::MainWindow *ui;
    segment_class *segment;
};
#endif // MAINWINDOW_H
