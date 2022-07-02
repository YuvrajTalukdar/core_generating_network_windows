#include "set_critical_variable.h"
#include "ui_set_critical_variable.h"
#include "string"

set_critical_variable::set_critical_variable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::set_critical_variable)
{
    ui->setupUi(this);
    ui->comboBox_extreame_weight->addItem("True");
    ui->comboBox_extreame_weight->addItem("False");
    ui->comboBox_zero_weight->addItem("True");
    ui->comboBox_zero_weight->addItem("False");
    ui->comboBox_flatening->addItem("True");
    ui->comboBox_flatening->addItem("False");
}

void set_critical_variable::set_pointers(chromosome *critical_variable1, MainWindow *mainwindow1)
{
    critical_variable=critical_variable1;
    mainwindow=mainwindow1;
}

set_critical_variable::~set_critical_variable()
{
    delete ui;
}

void set_critical_variable::on_pushButton_cancel_clicked()
{
    close();
}

bool is_num(std::string s)
{
    try
    {
        int x=std::stoi(s);
        return true;
    }
    catch(std::exception e)
    {   return false;}
}

bool is_num_float(std::string s)
{
    try
    {
        int x=std::stof(s);
        return true;
    }
    catch(std::exception e)
    {   return false;}
}

void set_critical_variable::on_pushButton_set_critical_variable_clicked()
{
    QPalette palred,palblack;
    palred.setColor(QPalette::Text, Qt::red);
    palblack.setColor(QPalette::Text, Qt::black);

    ui->lineEdit_firing_point->setPalette(palblack);
    ui->lineEdit_summation_temp->setPalette(palblack);
    ui->lineEdit_rhs_upper->setPalette(palblack);
    ui->lineEdit_rhs_lower->setPalette(palblack);
    ui->lineEdit_attribute_per_core->setPalette(palblack);
    ui->lineEdit_data_division->setPalette(palblack);

    bool all_is_well=true;

    if(ui->comboBox_flatening->currentIndex()==0)
    {   critical_variable->flatening_fx_enabled=true;}
    else
    {   critical_variable->flatening_fx_enabled=false;}

    if(ui->comboBox_zero_weight->currentIndex()==0)
    {   critical_variable->zero_weight_remover=true;}
    else
    {   critical_variable->zero_weight_remover=false;}

    if(ui->comboBox_extreame_weight->currentIndex()==0)
    {   critical_variable->extreame_weight_remover=true;}
    else
    {   critical_variable->extreame_weight_remover=false;}

    if(is_num(ui->lineEdit_firing_point->text().toStdString()))
    {   critical_variable->fp_change_value=std::stoi(ui->lineEdit_firing_point->text().toStdString());}
    else
    {
        all_is_well=false;
        ui->lineEdit_firing_point->setPalette(palred);
    }

    if(is_num(ui->lineEdit_summation_temp->text().toStdString()))
    {   critical_variable->summation_temp_thershold=std::stoi( ui->lineEdit_summation_temp->text().toStdString());}
    else
    {
        all_is_well=false;
        ui->lineEdit_summation_temp->setPalette(palred);
    }

    if(is_num(ui->lineEdit_rhs_upper->text().toStdString()))
    {   critical_variable->rhs_upper=std::stoi(ui->lineEdit_rhs_upper->text().toStdString());}
    else
    {
        all_is_well=false;
        ui->lineEdit_rhs_upper->setPalette(palred);
    }

    if(is_num(ui->lineEdit_rhs_lower->text().toStdString()))
    {   critical_variable->rhs_lower=std::stoi(ui->lineEdit_rhs_lower->text().toStdString());}
    else
    {
        all_is_well=false;
        ui->lineEdit_rhs_lower->setPalette(palred);
    }

    if(is_num(ui->lineEdit_attribute_per_core->text().toStdString()))
    {   critical_variable->attributes_per_core=std::stoi(ui->lineEdit_attribute_per_core->text().toStdString());}
    else
    {
        all_is_well=false;
        ui->lineEdit_attribute_per_core->setPalette(palred);
    }

    if(is_num_float(ui->lineEdit_data_division->text().toStdString()))
    {   critical_variable->data_division=std::stof(ui->lineEdit_data_division->text().toStdString());}
    else
    {
        all_is_well=false;
        ui->lineEdit_data_division->setPalette(palred);
    }

    if(all_is_well)
    {
        mainwindow->cv_set();
        close();
    }
}

