#include "make_individual_prediction.h"
#include "ui_make_individual_prediction.h"

make_individual_prediction::make_individual_prediction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::make_individual_prediction)
{
    ui->setupUi(this);
}

make_individual_prediction::~make_individual_prediction()
{
    delete ui;
}

void make_individual_prediction::on_pushButton_close_clicked()
{
    close();
}

void make_individual_prediction::closeEvent(QCloseEvent *event)
{
    mainwindow->stop_predict_mode();
}

void make_individual_prediction::on_pushButton_make_prediction_clicked()
{
    int label=segment->make_prediction_on_user_entered_data(data)/100;
    ui->label_predicted_label->setText(to_string(label).c_str());
    mainwindow->add_predict_info(data,label);
}


void make_individual_prediction::on_lineEdit_enter_data_textChanged(const QString &arg1)
{
    string text=arg1.toStdString();
    data.clear();
    string element="";
    bool error=false;
    for(int a=0;a<text.size();a++)
    {
        if(text.at(a)==',')
        {
            error=false;
            try{
                data.push_back(stof(element)*100);
                element="";
            }
            catch(exception e)
            {
                error=true;
                element="";
                break;
            }
        }
        else
        {   element+=text.at(a);}
    }
    if(error || data.size()!=length || text.at(text.length()-1)!=',')
    {
        QPalette palred;
        palred.setColor(QPalette::Text, Qt::red);
        ui->lineEdit_enter_data->setPalette(palred);
        ui->pushButton_make_prediction->setDisabled(true);
    }
    else
    {
        QPalette palblack;
        palblack.setColor(QPalette::Text, Qt::black);
        ui->lineEdit_enter_data->setPalette(palblack);
        ui->pushButton_make_prediction->setDisabled(false);
    }
}

void make_individual_prediction::set_pointers(MainWindow *mainwindow1,segment_class *segment1)
{
    mainwindow=mainwindow1;
    segment=segment1;
}

void make_individual_prediction::load_settings()
{
    length=segment->get_data_length();
    string data_format;
    for(int a=0;a<length;a++)
    {
        data_format+=to_string(a);
        data_format+=",";
    }
    data_format+=("  size: "+to_string(length));
    ui->label_data_format->setText(data_format.c_str());
    ui->label_element_left->setText(to_string(length).c_str());
    ui->pushButton_make_prediction->setDisabled(true);
}

