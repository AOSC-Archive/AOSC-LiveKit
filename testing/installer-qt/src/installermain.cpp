#include "installermain.h"
#include <QTabBar>

InstallerMain::InstallerMain(QWidget *parent) :
    QWidget(parent){
    PageTab     = new QTabWidget(this);
    NextButton  = new QPushButton(this);
    PervButton  = new QPushButton(this);
    Introduce   = new QLabel(this);
    Introduce->setText(tr("AOSC CopyLeft 2014~2048"));
    TotalPages  = 0;
    NextButton->show();
    PervButton->show();
    PageTab->show();
    Introduce->show();
    this->setWindowTitle(tr("AOSC 系统部署器"));
    this->setMinimumSize(600,500);
    PageTab->tabBar()->hide();
    this->AddPage(new WelcomePage);
}

InstallerMain::~InstallerMain(){
    delete PageTab;
}

void InstallerMain::AddPage(InstallerPage* Page){
    PageTab->addTab(Page,tr("Tab"));
    TotalPages++;
    InstallerMap.insert(TotalPages,Page);
    this->connect(Page,SIGNAL(SIGN_SetNextButtonDisabled(bool)),this->NextButton,SLOT(setDisabled(bool)));
    this->connect(Page,SIGNAL(SIGN_SetPervButtonDisabled(bool)),this->PervButton,SLOT(setDisabled(bool)));
}

void InstallerMain::DelPage(InstallerPage *){
        // 我不觉得这个函数有用 ;-)
}

void InstallerMain::resizeEvent(QResizeEvent *){
    NextButton->setGeometry(this->width()-60,50,45,this->height()-100);
    PervButton->setGeometry(25,50,45,this->height()-100);
    PageTab->setGeometry(70,100,this->width()-130,this->height()-150);
    Introduce->setGeometry(25,this->height()-45,300,25);
}

void InstallerMain::SLOT_TurnToNextPage(){
    PageTab->setCurrentIndex(PageTab->currentIndex()+1);
    InstallerMapIterator = InstallerMap.find(PageTab->currentIndex());
    InstallerPage *Page = InstallerMapIterator.value();
    Page->PervShow();

}

void InstallerMain::SLOT_TurnToPervPage(){
    PageTab->setCurrentIndex(PageTab->currentIndex()-1);
    InstallerMapIterator = InstallerMap.find(PageTab->currentIndex());
    InstallerPage *Page = InstallerMapIterator.value();
    Page->PervShow();
}

void InstallerMain::SLOT_TurnToSpecifyPage(QWidget*){

}

