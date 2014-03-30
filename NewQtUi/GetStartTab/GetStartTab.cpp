#include "GetStartTab.h"
#include "ui_GetStartTab.h"

GetStartTab::GetStartTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetStartTab)
{
    ui->setupUi(this);
}

GetStartTab::~GetStartTab()
{
    delete ui;
}
