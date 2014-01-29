#include "AOSC-Installer-Basic-UI.h"
#include <stdio.h>
#include <qt4/QtGui/QStyle>
#include <qt4/QtGui/QTabBar>
#include <qt4/QtGui/QMessageBox>

ProgressTab::ProgressTab(QTabWidget *parent) :
    QTabWidget(parent){
    Installer_Core = new AOSC_Installer_Core;
    if(Installer_Core->Check_Environment() != _EN_LIVE_CD_){
        QMessageBox::warning(this,tr("警告"),tr("你现在不是在LiveCD环境下！"),QMessageBox::Yes);
        exit(0);
    }
    this->setMaximumSize(900,500);
    this->setMinimumSize(700,350);
    this->tabBar()->hide();
    Welcome = new WelcomeTab;
    this->addTab(Welcome,tr("Welcome"));
    this->connect(Welcome,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(Welcome,SIGNAL(PervStep()),this,SLOT(PervStep()));
}

void ProgressTab::NextStep(void){
    int current = this->currentIndex();
    this->currentChanged(current+1);
    printf("Next\n");
}

void ProgressTab::PervStep(void){
    int current = this->currentIndex();
    this->currentChanged(current-1);
}

//##########################################################


ProgressTabWidget::ProgressTabWidget(QWidget *parent) :
    QWidget(parent){
    NextStepButton = new QPushButton(this);
    PervStepButton = new QPushButton(this);
    NextStepButton->setText(tr("Next"));
    PervStepButton->setText(tr("Back"));
    connect(NextStepButton,SIGNAL(clicked()),this,SLOT(NextStepClicked()));
    connect(PervStepButton,SIGNAL(clicked()),this,SLOT(PervStepClicked()));
}

void ProgressTabWidget::resizeEvent(QResizeEvent *){
    PervStepButton->setGeometry(this->width()-WIDTH_SPACE*2-BUTTON_WIDTH*2,this->height()-BUTTON_HEIGHT-HEIGHT_SPACE,BUTTON_WIDTH,BUTTON_HEIGHT);
    NextStepButton->setGeometry(this->width()-WIDTH_SPACE*1-BUTTON_WIDTH*1,this->height()-BUTTON_HEIGHT-HEIGHT_SPACE,BUTTON_WIDTH,BUTTON_HEIGHT);
}

void ProgressTabWidget::NextStepClicked(void){
    emit NextSetp();
}

void ProgressTabWidget::PervStepClicked(void){
    emit PervStep();
}

void ProgressTabWidget::SetNextButtonHide(void){
    NextStepButton->hide();
}

void ProgressTabWidget::SetPervButtonHide(void){
    PervStepButton->hide();
}

//#########################################################

WelcomeTab::WelcomeTab(ProgressTabWidget *parent) :
    ProgressTabWidget(parent){
    WelcomeTitle    = new QLabel(this);
    WelcomeContent  = new QLabel(this);

    WelcomeTitle->setText(tr("Hi."));
    TitleFont.setPointSize(27);
    WelcomeTitle->setFont(TitleFont);
    WelcomeTitle->setGeometry(27,27,27*3,27);

    WelcomeContent->setText(tr("Thank you for trying the latest Linux Distribution from Anthon Open Source Community!\n\nOkay, are you now ready to install [DistroName] to your dear computer?"));
    ContentFont.setPointSize(10);
    WelcomeContent->setFont(ContentFont);
    WelcomeContent->setGeometry(27,27+50,600,50);

    SetPervButtonHide();
}
