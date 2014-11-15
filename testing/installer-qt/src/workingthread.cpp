#include "workingthread.h"
#include <stdlib.h>

WorkingThread::WorkingThread(QThread *parent):
    QThread(parent){

}

WorkingThread::~WorkingThread(){

}

void WorkingThread::run(){
    int Status = system(Work.toUtf8().data());
    emit WorkDone(Work,Status);
}

void WorkingThread::SetWork(QString Joy){
    Work = Joy;
}




WorkingDialog::WorkingDialog(QWidget *parent):
    QWidget(parent){
    Thread              = new WorkingThread;
    WorkingDescription  = new QLabel(this);
    CancelButton        = new QPushButton(this);
    DoneButton          = new QPushButton(this);
    CancelButton->setText("Cancel");
    DoneButton->setText("Done");
    CancelButton->hide();
    DoneButton->hide();

    this->setMaximumSize(150,100);
    this->setMinimumSize(150,100);
    WorkingDescription->setGeometry(35,30,100,20);
    CancelButton->setGeometry(90,65,55,25);
    DoneButton->setGeometry(90,65,55,25);
    this->connect(Thread,SIGNAL(started()),this,SLOT(pWorkStarted()));
    this->connect(Thread,SIGNAL(WorkDone(QString,int)),this,SLOT(pWorkStoped(QString,int)));
    this->connect(CancelButton,SIGNAL(clicked()),this,SLOT(Stop()));
    this->connect(DoneButton,SIGNAL(clicked()),this,SLOT(close()));
    this->setWindowTitle(tr("Working..."));
}

WorkingDialog::~WorkingDialog(){

}

void WorkingDialog::SetWork(QString Work){
    Thread->SetWork(Work);
}

void WorkingDialog::SetWorkingtText(QString Text){
    WorkingDescription->setText(Text);
    WorkingDescription->show();
}

void WorkingDialog::Start(){
    Thread->start();
    this->show();
    CancelButton->show();
}

void WorkingDialog::Stop(){
    Thread->terminate();
    this->close();
    emit Stoped(-1);
}


void WorkingDialog::pWorkStarted(){
    this->show();
}

void WorkingDialog::pWorkStoped(QString,int Status){
    if(Status != 0){
        WorkingDescription->setText(tr("Failure!"));
    }else{
        WorkingDescription->setText(tr("Success"));
    }
    this->hide();
    emit Stoped(Status);
}
