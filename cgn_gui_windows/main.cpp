#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPalette pal = a.palette();
    pal.setColor(QPalette::Window, Qt::darkGray);
    a.setPalette(pal);
    MainWindow w;
    w.show();
    return a.exec();
}
