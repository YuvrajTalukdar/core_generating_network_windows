#ifndef TRAIN_AND_TEST_NETWORK_H
#define TRAIN_AND_TEST_NETWORK_H

#include <QWidget>

namespace Ui {
class train_and_test_network;
}

class train_and_test_network : public QWidget
{
    Q_OBJECT

public:
    explicit train_and_test_network(QWidget *parent = nullptr);
    ~train_and_test_network();

private:
    Ui::train_and_test_network *ui;
};

#endif // TRAIN_AND_TEST_NETWORK_H
