#include "WorkDoneTab.h"
#include "ui_WorkDoneTab.h"

WorkDoneTab::WorkDoneTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkDoneTab)
{
    ui->setupUi(this);
}

WorkDoneTab::~WorkDoneTab()
{
    delete ui;
}


