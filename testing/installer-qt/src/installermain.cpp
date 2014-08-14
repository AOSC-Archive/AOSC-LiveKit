#include "installermain.h"
#include <QTabBar>
#include <QIcon>
#include <stdio.h>
#include <QPalette>
#include <QFont>

InstallerMain::InstallerMain(QWidget *parent) :
    QWidget(parent){
    PageTab     = new QTabWidget(this);
    NextButton  = new QPushButton(this);
    PervButton  = new QPushButton(this);
    Introduce   = new QLabel(this);
    Introduce->setText("AOSC CopyLeft 2014~65536,Power By 张峻锋 from Mars");
    TotalPages  = 0;
    //  Set Icon
    QIcon Icon(":/Icon/OSIcon");
    this->setWindowIcon(Icon);
    QIcon NextImage(":/Image/NextStepImage");
    NextButton->setIcon(NextImage);
    QIcon PervImage(":/Image/PervStepImage");
    PervButton->setIcon(PervImage);
    //  Show Button
    NextButton->show();
    PervButton->show();
    PageTab->show();
    Introduce->show();
    this->setWindowTitle(tr("AOSC 系统部署器"));
    PageTab->tabBar()->hide();
    this->AddPage(new WelcomePage);
    this->AddPage(new ReadingPage);
    PervButton->setDisabled(true);
    this->connect(PervButton,SIGNAL(clicked()),this,SLOT(SLOT_TurnToPervPage()));
    this->connect(NextButton,SIGNAL(clicked()),this,SLOT(SLOT_TurnToNextPage()));
    PageTab->setDocumentMode(true);
    NextButton->setFlat(true);
    PervButton->setFlat(true);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/Image/BackgroundImage")));
    this->setPalette(palette);
    this->setMinimumSize(600,500);
    this->setMaximumSize(600,500);
}

InstallerMain::~InstallerMain(){
    delete PageTab;
}

void InstallerMain::AddPage(InstallerPage* Page){
    PageTab->addTab(Page,tr("Tab"));
    TotalPages++;
    InstallerMap.insert(TotalPages-1,Page);
    this->connect(Page,SIGNAL(SIGN_SetNextButtonDisabled(bool)),this->NextButton,SLOT(setDisabled(bool)));
    this->connect(Page,SIGNAL(SIGN_SetPervButtonDisabled(bool)),this->PervButton,SLOT(setDisabled(bool)));
}

void InstallerMain::DelPage(InstallerPage *){
        // 我不觉得这个函数有用 ;-)
}

void InstallerMain::resizeEvent(QResizeEvent *){
    NextButton->setGeometry(this->width()-60,60,45,this->height()-90);
    PervButton->setGeometry(15,60,45,this->height()-90);
    PageTab->setGeometry(59,60,this->width()-118,this->height()-89);
    Introduce->setGeometry(25,this->height()-35,400,25);
}

void InstallerMain::SLOT_TurnToNextPage(){
    NextButton->setDisabled(false);
    PervButton->setDisabled(false);
    InstallerMapIterator = InstallerMap.find(PageTab->currentIndex()+1);
    PageTab->setCurrentIndex(PageTab->currentIndex()+1);
    InstallerPage *Page = InstallerMapIterator.value();
    Page->PervShow();
}

void InstallerMain::SLOT_TurnToPervPage(){
    NextButton->setDisabled(false);
    PervButton->setDisabled(false);
    PageTab->setCurrentIndex(PageTab->currentIndex()-1);
    InstallerMapIterator = InstallerMap.find(PageTab->currentIndex());
    InstallerPage *Page = InstallerMapIterator.value();
    Page->PervShow();
}

void InstallerMain::SLOT_TurnToSpecifyPage(QWidget*){

}

