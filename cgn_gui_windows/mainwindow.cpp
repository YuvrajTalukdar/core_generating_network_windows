#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "train_and_test_network.h"
#include "set_critical_variable.h"
#include "make_individual_prediction.h"

segment_thread *worker;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Train and Test Network");
    ui->comboBox->addItem("Make Perdictions");
    ui->comboBox->addItem("Make individual Predictions");
    ui->comboBox->addItem("Test the network");
    ui->lineEdit_select_dataset->setReadOnly(true);
    ui->lineEdit_select_network->setReadOnly(true);
    ui->textEdit_status->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display_elements(int index)
{
    if(index==0)
    {
        ui->lineEdit_select_dataset->setDisabled(false);
        ui->pushButton_select_dataset->setDisabled(false);

        ui->lineEdit_select_network->setDisabled(true);
        ui->pushButton_select_network->setDisabled(true);

        ui->textEdit_no_of_threads->setDisabled(false);

        ui->pushButton_set_critical_variable->setDisabled(false);
        ui->pushButton_clear_critical_variable->setDisabled(false);
        ui->label_critical_variable->setText("Critical Variable not set");

        ui->textEdit_no_of_iterations->setDisabled(false);
        ui->textEdit_initial_population->setDisabled(false);
        ui->textEdit_mutation_percentage->setDisabled(false);

        ui->pushButton_start->setText("Start Training");
    }
    else if(index==1)
    {
        ui->lineEdit_select_dataset->setDisabled(false);
        ui->pushButton_select_dataset->setDisabled(false);

        ui->lineEdit_select_network->setDisabled(false);
        ui->pushButton_select_network->setDisabled(false);

        ui->textEdit_no_of_threads->setDisabled(true);

        ui->pushButton_set_critical_variable->setDisabled(true);
        ui->pushButton_clear_critical_variable->setDisabled(true);
        ui->label_critical_variable->setText("Critical Variable not set");

        ui->textEdit_no_of_iterations->setDisabled(true);
        ui->textEdit_initial_population->setDisabled(true);
        ui->textEdit_mutation_percentage->setDisabled(true);

        ui->pushButton_start->setText("Start Prediction");
    }
    else if(index==2)
    {
        ui->lineEdit_select_dataset->setDisabled(true);
        ui->pushButton_select_dataset->setDisabled(true);

        ui->lineEdit_select_network->setDisabled(false);
        ui->pushButton_select_network->setDisabled(false);

        ui->textEdit_no_of_threads->setDisabled(true);

        ui->pushButton_set_critical_variable->setDisabled(true);
        ui->pushButton_clear_critical_variable->setDisabled(true);
        ui->label_critical_variable->setText("Critical Variable not set");

        ui->textEdit_no_of_iterations->setDisabled(true);
        ui->textEdit_initial_population->setDisabled(true);
        ui->textEdit_mutation_percentage->setDisabled(true);

        ui->pushButton_start->setText("Enter Data");
    }
    else if(index==3)
    {
        ui->lineEdit_select_dataset->setDisabled(false);
        ui->pushButton_select_dataset->setDisabled(false);

        ui->lineEdit_select_network->setDisabled(false);
        ui->pushButton_select_network->setDisabled(false);

        ui->textEdit_no_of_threads->setDisabled(true);

        ui->pushButton_set_critical_variable->setDisabled(true);
        ui->pushButton_clear_critical_variable->setDisabled(true);
        ui->label_critical_variable->setText("Critical Variable not set");

        ui->textEdit_no_of_iterations->setDisabled(true);
        ui->textEdit_initial_population->setDisabled(true);
        ui->textEdit_mutation_percentage->setDisabled(true);

        ui->pushButton_start->setText("Test Network");
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    critical_variable_set=false;
    display_elements(index);
}

void MainWindow::on_pushButton_select_dataset_clicked()
{
    QString file_name=QFileDialog::getOpenFileName(this,"Select .csv file","./","*.csv");
    ui->lineEdit_select_dataset->setText(file_name);
}

void MainWindow::on_pushButton_select_network_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Network Directory"),"./",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_select_network->setText(dir);
}

void MainWindow::cv_set()
{
    ui->label_critical_variable->setText("Critical Variable set");
    ui->label_critical_variable->setStyleSheet("QLabel { color : lightgreen; }");
    critical_variable_set=true;
    ui->textEdit_no_of_iterations->setDisabled(true);
    ui->textEdit_mutation_percentage->setDisabled(true);
    ui->textEdit_initial_population->setDisabled(true);
}

void MainWindow::on_pushButton_set_critical_variable_clicked()
{
    set_critical_variable *wdg = new set_critical_variable();
    wdg->set_pointers(&critical_variable,this);
    wdg->show();
}

void MainWindow::on_pushButton_clear_critical_variable_clicked()
{
    ui->label_critical_variable->setText("Critical Variable not set");
    ui->label_critical_variable->setStyleSheet("QLabel { color : black; }");
    critical_variable_set=false;
    ui->textEdit_no_of_iterations->setDisabled(false);
    ui->textEdit_mutation_percentage->setDisabled(false);
    ui->textEdit_initial_population->setDisabled(false);
}

bool MainWindow::is_num_float(string s)
{
    try
    {
        int x=stof(s);
        return true;
    }
    catch(exception e)
    {   return false;}
}

bool MainWindow::is_num_int(string s)
{
    try
    {
        int x=stoi(s);
        return true;
    }
    catch(exception e)
    {   return false;}
}

bool MainWindow::check_if_settings_ok(int index)
{
    ui->textEdit_status->setText("");
    ui->textEdit_status->setTextColor(Qt::black);
    bool all_is_well=true;
    string status="";
    if(index==0)
    {
        if(ui->lineEdit_select_dataset->text().length()==0)
        {
            all_is_well=false;
            status+="Dataset not selected!\n";
        }
        if(ui->textEdit_no_of_threads->toPlainText().length()==0 || !stoi(ui->textEdit_no_of_threads->toPlainText().toStdString()))
        {
            all_is_well=false;
            status+="no of threads value incorrect!\n";
        }
        if(!critical_variable_set)
        {
            if(ui->textEdit_no_of_iterations->toPlainText().length()==0 || !stoi(ui->textEdit_no_of_iterations->toPlainText().toStdString()))
            {
                all_is_well=false;
                status+="No of Iterations not set!\n";
            }
            if(ui->textEdit_initial_population->toPlainText().length()==0 || !stoi(ui->textEdit_initial_population->toPlainText().toStdString()))
            {
                all_is_well=false;
                status+="Initial Population Size not set!\n";
            }
            if(ui->textEdit_mutation_percentage->toPlainText().length()==0 || !stoi(ui->textEdit_mutation_percentage->toPlainText().toStdString()))
            {
                all_is_well=false;
                status+="Mutation Percentage not set!\n";
            }
        }

    }
    else if(index==1)
    {
        if(ui->lineEdit_select_dataset->text().length()==0)
        {
            all_is_well=false;
            status+="Dataset not selected!\n";
        }
        if(ui->lineEdit_select_network->text().length()==0)
        {
            all_is_well=false;
            status+="Network not selected!\n";
        }
    }
    else if(index==2)
    {
        if(ui->lineEdit_select_network->text().length()==0)
        {
            all_is_well=false;
            status+="Network not selected!\n";
        }
    }
    else if(index==3)
    {
        if(ui->lineEdit_select_dataset->text().length()==0)
        {
            all_is_well=false;
            status+="Dataset not selected!\n";
        }
        if(ui->lineEdit_select_network->text().length()==0)
        {
            all_is_well=false;
            status+="Network not selected!\n";
        }
    }
    if(!all_is_well)
    {
        ui->textEdit_status->setTextColor(Qt::red);
        ui->textEdit_status->setText(status.c_str());
    }

    return all_is_well;
}

void print_function_3(string status)
{
    //cout<<(status);
    worker->print_function2(status);
}

QTextEdit *status_box;
void print_function_2(string status)
{
    string text=status_box->toPlainText().toStdString();
    text+=status;
    status_box->setText(text.c_str());
}

void MainWindow::on_pushButton_start_clicked()
{
    if(check_if_settings_ok(ui->comboBox->currentIndex()))
    {
        string dataset="";
        int train_test_predict=ui->comboBox->currentIndex();
        string network="";
        int no_of_threads=1;
        int no_of_iterations;
        int initial_population;
        int mutation_percentage;

        int index=ui->comboBox->currentIndex();
        if(index==0)
        {
            dataset=ui->lineEdit_select_dataset->text().toStdString();
            network=ui->lineEdit_select_network->text().toStdString();
            no_of_threads=stoi( ui->textEdit_no_of_threads->toPlainText().toStdString());
            if(!critical_variable_set)
            {
                no_of_iterations=stoi(ui->textEdit_no_of_iterations->toPlainText().toStdString());
                initial_population=stoi(ui->textEdit_initial_population->toPlainText().toStdString());
                mutation_percentage=stoi(ui->textEdit_mutation_percentage->toPlainText().toStdString());
                critical_variable.id=-1;
            }
        }
        else if(index==1 || index==3)
        {
            dataset=ui->lineEdit_select_dataset->text().toStdString();
            network=ui->lineEdit_select_network->text().toStdString();
        }
        else if(index==2)
        {
            network=ui->lineEdit_select_network->text().toStdString();
        }
        train_test_predict++;
        cout<<"\ncheck";
        if(index!=2)
        {
            worker=new segment_thread(this);
            connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
            connect(worker, SIGNAL(send_status(string)), this, SLOT(receive_status(string)));
            connect(worker, SIGNAL(send_complete_signal()), this, SLOT(receive_complete_signal()));

            worker->load_settings(dataset,train_test_predict,network,no_of_threads,critical_variable,no_of_iterations,initial_population,mutation_percentage);
            worker->start();
        }
        else
        {
            status_box=ui->textEdit_status;
            segment=new segment_class(0,0,"default_segment",print_function_2);
            segment->load_segment(network);
            //int length=segment->get_data_length();
            make_individual_prediction *wdg = new make_individual_prediction();
            wdg->set_pointers(this,segment);
            wdg->show();
            wdg->load_settings();
        }
        ui->pushButton_start->setDisabled(true);
    }
}

void MainWindow::add_predict_info(vector<float> data,int label)
{
    string text=ui->textEdit_status->toPlainText().toStdString();
    text+="\n";
    for(int a=0;a<data.size();a++)
    {
        text+=to_string(data[a]);
        text+=",";
    }
    text+=" : ";
    text+=to_string(label);
    ui->textEdit_status->setText(text.c_str());
}
void MainWindow::stop_predict_mode()
{
    free(segment);
    //ui->textEdit_status->setText("");
    ui->pushButton_start->setDisabled(false);
}

void segment_thread::run()
{
    QMutex mutex;
    mutex.lock();
    segment_starter(file_name_local,test_train_predict,segment_save_file_name,no_of_threads,critical_variables,iterations,population_size,mutation_percentage,&print_function_3);
    emit send_complete_signal();
    mutex.unlock();
}

void MainWindow::receive_status(string status)
{
    string text=ui->textEdit_status->toPlainText().toStdString();
    text+=status;
    ui->textEdit_status->setText(text.c_str());
    ui->textEdit_status->verticalScrollBar()->setValue(ui->textEdit_status->verticalScrollBar()->maximum());
}

void MainWindow::receive_complete_signal()
{   ui->pushButton_start->setDisabled(false);}

