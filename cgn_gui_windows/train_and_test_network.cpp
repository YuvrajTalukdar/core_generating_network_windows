#include "train_and_test_network.h"
#include "ui_train_and_test_network.h"

train_and_test_network::train_and_test_network(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::train_and_test_network)
{
    ui->setupUi(this);
}

train_and_test_network::~train_and_test_network()
{
    delete ui;
}
