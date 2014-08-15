#include "workingthread.h"
#include <stdlib.h>

WorkingThread::WorkingThread(QThread *parent):
    QThread(parent){

}

WorkingThread::~WorkingThread(){

}

void WorkingThread::run(){
    system(Work.toUtf8().data());
}

void WorkingThread::SetWork(QString Joy){
    Work = Joy;
}
