#include "ReadingTab.h"
#include "ui_ReadingTab.h"

ReadingTab::ReadingTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadingTab)
{
    ui->setupUi(this);
    this->connect(ui->IAgreeCheckBox,SIGNAL(clicked(bool)),this,SLOT(SLOT_IAgreeCheckBoxClicked(bool)));
}

ReadingTab::~ReadingTab()
{
    delete ui;
}

void ReadingTab::SLOT_IAgreeCheckBoxClicked(bool status){
    emit SIGNAL_IAgreeCheckBoxClicked(status);
}
