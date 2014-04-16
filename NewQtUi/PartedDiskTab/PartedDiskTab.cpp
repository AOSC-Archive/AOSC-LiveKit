#include "PartedDiskTab.h"
#include "ui_PartedDiskTab.h"

PartedDiskTab::PartedDiskTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PartedDiskTab)
{
    ui->setupUi(this);
}

PartedDiskTab::~PartedDiskTab()
{
    delete ui;
}
