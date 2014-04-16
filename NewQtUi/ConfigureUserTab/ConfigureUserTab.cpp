#include "ConfigureUserTab.h"
#include "ui_ConfigureUserTab.h"

ConfigureUserTab::ConfigureUserTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigureUserTab)
{
    ui->setupUi(this);
}

ConfigureUserTab::~ConfigureUserTab()
{
    delete ui;
}
