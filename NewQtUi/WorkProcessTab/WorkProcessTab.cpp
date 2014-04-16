#include "WorkProcessTab.h"
#include "ui_WorkProcessTab.h"

WorkProcessTab::WorkProcessTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkProcessTab)
{
    ui->setupUi(this);
}

WorkProcessTab::~WorkProcessTab()
{
    delete ui;
}
