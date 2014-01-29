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
    //Add Welcome Tab
    Welcome = new WelcomeTab;
    this->insertTab(0,Welcome,tr("Welcome"));
    this->connect(Welcome,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(Welcome,SIGNAL(PervStep()),this,SLOT(PervStep()));
    //Add Get Started Tab
    GetStarted = new GetStartedTab;
    this->insertTab(1,GetStarted,tr("Get Started"));
    this->connect(GetStarted,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(GetStarted,SIGNAL(PervStep()),this,SLOT(PervStep()));
    //Add Reading Tab
    Reading     = new ReadingTab;
    this->insertTab(2,Reading,tr("Reading Time"));
    this->connect(Reading,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(Reading,SIGNAL(PervStep()),this,SLOT(PervStep()));

}

void ProgressTab::NextStep(void){
    int current = this->currentIndex();
    this->setCurrentIndex(current+1);
}

void ProgressTab::PervStep(void){
    int current = this->currentIndex();
    this->setCurrentIndex(current-1);
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
    TitleFont.setPointSize(27);
    TitleFont.setBold(true);
    SecondaryTitleFont.setPointSize(15);
    SecondaryTitleFont.setBold(true);
    ContentFont.setPointSize(10);
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

void ProgressTabWidget::SetNextButtonDisable(void){
    NextStepButton->setDisabled(true);
}
void ProgressTabWidget::SetNextButtonEnable(void){
    NextStepButton->setEnabled(true);
}

void ProgressTabWidget::SetPervButtonDisable(void){
    PervStepButton->setDisabled(true);
}

void ProgressTabWidget::SetPervButtonEnable(void){
    PervStepButton->setEnabled(true);
}

//#########################################################

WelcomeTab::WelcomeTab(ProgressTabWidget *parent) :
    ProgressTabWidget(parent){
    Title    = new QLabel(this);
    Content  = new QLabel(this);

    Title->setText(tr("Hi."));
    Title->setFont(TitleFont);
    Title->setGeometry(27,27,27*3,27);

    Content->setText(tr("Thank you for trying the latest Linux Distribution from Anthon Open Source Community!\n\nOkay, are you now ready to install [DistroName] to your dear computer?"));
    Content->setFont(ContentFont);
    Content->setGeometry(27,27+50,600,50);

    SetPervButtonHide();
}

//--------------------------------------------------------

GetStartedTab::GetStartedTab(ProgressTabWidget *parent):
    ProgressTabWidget(parent){
    Title         = new QLabel(this);
    SecondaryTitle= new QLabel(this);
    Content       = new QLabel(this);

    Title->setFont(TitleFont);
    SecondaryTitle->setFont(SecondaryTitleFont);
    Content->setFont(ContentFont);

    Title->setText(tr("Get Started"));
    SecondaryTitle->setText(tr("Let's see what we are doing here..."));
    Content->setText(tr(" - Do some serious reading.\n\n - Get your drive partitioned.\n\n - Find out who you are.\n\n - Start installing.\n\n - Install boot loader.\n\n - All set!"));

    Title->setGeometry(27,27,27*11,27);
    SecondaryTitle->setGeometry(27,15+40,600,50);
    Content->setGeometry(27,27+70,600,200);
}

//--------------------------------------------------------------

ReadingTab::ReadingTab(ProgressTabWidget *parent):
    ProgressTabWidget(parent){
    Title       = new QLabel(this);
    Content     = new QLabel;
    Browser     = new QTextBrowser(this);
    CheckBox    = new QCheckBox(this);
    HBoxLayout  = new QHBoxLayout;
    VBoxLayout  = new QVBoxLayout;

    connect(CheckBox,SIGNAL(clicked()),this,SLOT(CheckBoxChanged()));
    SetNextButtonDisable();
    CheckBoxStatus = false;

    Title->setFont(TitleFont);
    Title->setText(tr("Reading Time!"));
    Title->setGeometry(27,27,27*11,27);

    Content->setFont(ContentFont);
    Content->setText(tr("I promise to be nice"));

    this->setLayout(VBoxLayout);

    VBoxLayout->addSpacing(60);
    VBoxLayout->addWidget(Browser);
    VBoxLayout->addLayout(HBoxLayout);
    HBoxLayout->addStretch(500);
    HBoxLayout->addWidget(Content);
    HBoxLayout->addStretch(10);
    HBoxLayout->addWidget(CheckBox);
    VBoxLayout->addSpacing(30);
}

void ReadingTab::CheckBoxChanged(){
    if(CheckBoxStatus == true){
        SetNextButtonDisable();
        CheckBoxStatus = false;
    }
    else{
        SetNextButtonEnable();
        CheckBoxStatus = true;
    }
}
