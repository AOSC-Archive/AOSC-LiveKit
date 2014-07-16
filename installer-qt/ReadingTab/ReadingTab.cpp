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

void ReadingTab::SLOT_IAgreeCheckBoxClicked(bool status){       //  其实就是转发信号【话说我可以用namespace的】
    emit SIGNAL_IAgreeCheckBoxClicked(status);
}

bool ReadingTab::is_IAgreeCheckBox_Status(){
    return ui->IAgreeCheckBox->isChecked();
}
