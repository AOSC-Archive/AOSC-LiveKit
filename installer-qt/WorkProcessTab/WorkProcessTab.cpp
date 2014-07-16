#include "WorkProcessTab.h"
#include "ui_WorkProcessTab.h"
#include <QByteArray>
#include <QScrollArea>
#include <QScrollBar>
#include <QMoveEvent>

WorkProcessTab::WorkProcessTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkProcessTab)
{
    ui->setupUi(this);
    this->connect(ui->StartButton,SIGNAL(clicked()),this,SLOT(SLOT_StartButtonClicked()));
    ui->MainProcessBar->hide();
    ui->MainProcessBar->setRange(0,0);
    isFormat = false;
}

WorkProcessTab::~WorkProcessTab()
{
    delete ui;
}

void WorkProcessTab::SetIsFormat(bool k){
    isFormat = k;
}

void WorkProcessTab::SLOT_StartButtonClicked(){
    ui->StartButton->hide();
    if(isFormat == true){
        printf("Emited\n");
        emit SIG_StartButtonClicked_WithFormat();
        return;
    }
    printf("NotEmited!\n");
    emit SIG_StartButtonClicked();
}

void WorkProcessTab::SetTotalFiles(int Total){
    ui->MainProcessBar->setRange(0,Total);
}

void WorkProcessTab::SetNowCopyed(int Now){
    ui->MainProcessBar->setValue(Now);
}

void WorkProcessTab::SetProcessBarShow(bool s){
    if(s == true)   ui->MainProcessBar->show();
    else            ui->MainProcessBar->hide();
}

void WorkProcessTab::SetLabelText(QString s){
    ui->NowCOntentLabel->setText(s);
}

void WorkProcessTab::SLOT_CopyDone(int){
    ui->MainProcessBar->setRange(0,0);
}