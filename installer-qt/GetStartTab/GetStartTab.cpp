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
//如果说这都要我打注释也太不近人情了
