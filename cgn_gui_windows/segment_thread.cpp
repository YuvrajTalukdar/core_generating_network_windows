#include"segment_thread.h"

segment_thread::segment_thread(QObject *parent):QThread(parent)
{}

void segment_thread::run()
{
    QMutex mutex;
    mutex.lock();
    segment_starter(file_name_local.toStdString(),test_train_predict,segment_save_file_name.toStdString(),no_of_threads,critical_variables,iterations,population_size,mutation_percentage,status_box1);
    mutex.unlock();
}
