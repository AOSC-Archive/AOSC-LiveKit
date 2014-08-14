#include "dialogbox.h"

ChangeDialogBox::ChangeDialogBox(QWidget *parent):
    QWidget(parent){
    this->setMinimumSize(300,200);
    this->setMaximumSize(300,200);
    this->setWindowTitle(tr("Change partition"));
}

ChangeDialogBox::~ChangeDialogBox(){

}

void ChangeDialogBox::SetCurrentPartition(PedPartition){

}


AddDialogBox::AddDialogBox(QWidget *parent):
    QWidget(parent){
    this->setMinimumSize(300,200);
    this->setMaximumSize(300,200);
    this->setWindowTitle(tr("Change partition"));
}

AddDialogBox::~AddDialogBox(){

}

void AddDialogBox::SetCurrentPartition(PedPartition){

}
