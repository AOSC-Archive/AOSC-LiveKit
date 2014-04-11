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
}

WorkProcessTab::~WorkProcessTab()
{
    delete ui;
}

void WorkProcessTab::SLOT_StartButtonClicked(){
    ui->StartButton->hide();
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
