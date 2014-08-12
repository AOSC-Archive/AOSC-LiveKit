#include "installerpage.h"
#include <QLabel>

InstallerPage::InstallerPage(QWidget *parent):
    QWidget(parent){
    cTitle = new QLabel(this);
    cTitle->setGeometry(30,15,500,35);
}

InstallerPage::~InstallerPage(){

}

void InstallerPage::PervShow(){

}

void InstallerPage::SLOT_NextButtonClicked(void){

}

void InstallerPage::SLOT_PageChanged(QWidget *){

}

void InstallerPage::resizeEvent(QResizeEvent *){

}

void InstallerPage::SetContantTitle(const QString &str){
    cTitle->setText(str);
}

//----------------------------------//
//--------众神与愚民的分界线-----------//
//--------此刻正是昼夜交替时-----------//
//--------耀日将寝，皓月当空-----------//
//--------鬼哭狼嚎，铁骑千军-----------//
//----------------------------------//


WelcomePage::WelcomePage(InstallerPage *parent):
    InstallerPage(parent){
    this->SetContantTitle(tr("Welcome"));
}

WelcomePage::~WelcomePage(){

}
