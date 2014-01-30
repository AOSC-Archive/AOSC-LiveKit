#include "AOSC-Installer-Basic-UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <qt4/QtGui/QStyle>
#include <qt4/QtGui/QTabBar>
#include <qt4/QtGui/QMessageBox>
#include <qt4/QtCore/QFile>
#include <qt4/QtCore/QTextStream>
#include <qt4/QtCore/QByteArray>

AOSC_Installer_Core *Installer_Core = new AOSC_Installer_Core;

ProgressTab::ProgressTab(QTabWidget *parent) :
    QTabWidget(parent){
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
    //Add GParted Tab
    GPartedDisk = new GPartedDiskTab;
    this->insertTab(3,GPartedDisk,tr("Parted Your Disk"));
    this->connect(GPartedDisk,SIGNAL(PartedDone(QString,QString)),this,SLOT(PartedDone(QString,QString)));
    this->connect(GPartedDisk,SIGNAL(PervStep()),this,SLOT(PervStep()));
    this->connect(GPartedDisk,SIGNAL(AskHide()),this,SLOT(AskHide()));
    this->connect(GPartedDisk,SIGNAL(AskShow()),this,SLOT(AskShow()));
}

void ProgressTab::NextStep(void){
    int current = this->currentIndex();
    this->setCurrentIndex(current+1);
}

void ProgressTab::PervStep(void){
    int current = this->currentIndex();
    this->setCurrentIndex(current-1);
}

void ProgressTab::AskHide(){
    this->hide();
}

void ProgressTab::AskShow(){
    this->show();
}

void ProgressTab::PartedDone(QString _TargetPartiting,QString _TargetDisk){
    bzero(TargetPartiting,64);
    QByteArray ba = _TargetPartiting.toLatin1();
    strcpy(TargetPartiting,ba.data());
    bzero(TargetDisk,64);
    ba = _TargetDisk.toLatin1();
    strcpy(TargetDisk,ba.data());
    printf("Target Partiting = %s\nTarget Disk= %s\n",TargetPartiting,TargetDisk);
    //Add MainWork Tab
    MainWork = new MainWorkTab(TargetPartiting,TargetDisk);
    this->insertTab(4,MainWork,tr("Main Work"));
    this->connect(MainWork,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(MainWork,SIGNAL(PervStep()),this,SLOT(PervStep()));
    // Next Page
    int current = this->currentIndex();
    this->setCurrentIndex(current+1);
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
    Title->setGeometry(27,17,27*3,50);

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

    Title->setGeometry(27,17,27*11,50);
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
    Title->setGeometry(27,17,500,50);

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

    QFile file("/usr/share/ulinst/data/GNU_License.html");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        perror("Open License File");
        QMessageBox::warning(this,tr("Open License File"),tr("Open License File Error"),QMessageBox::Yes);
        exit(0);
    }
    QTextStream in(&file);
    Browser->setHtml(in.readAll());
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
//-------------------------------------------

GPartedDiskTab::GPartedDiskTab(ProgressTabWidget *parent):
    ProgressTabWidget(parent){
    Title                   = new QLabel(this);
    Waring                  = new QLabel(this);
    Content                 = new QLabel(this);
    Content2                = new QLabel(this);
    Content3                = new QLabel(this);
    CheckBox                = new QCheckBox(this);
    DiskPartitingComboBox   = new QComboBox(this);
    DiskComboBox            = new QComboBox(this);
    StartPartitingButton    = new QPushButton(this);
    DiskPath                = new char[64];
    DiskPartitingPath       = new char[64];

    this->connect(StartPartitingButton,SIGNAL(clicked()),this,SLOT(StartPartiting()));

    //-----------------------------------------------
    //Read DiskPartiting-----------------------------
    //-----------------------------------------------
    int DiskPartitingCount = 0;
    system("ls /dev/sd?? > /tmp/.DiskPartiting.info");
    fp = fopen("/tmp/.DiskPartiting.info","r");
    DiskPartitingComboBox->insertItem(-1,tr("---"));
    bzero(DiskPartitingPath,64);
    while(fscanf(fp,"%s",DiskPartitingPath) != EOF){
        DiskPartitingComboBox->insertItem(DiskCount,tr(DiskPartitingPath));
        bzero(DiskPartitingPath,64);
        DiskPartitingCount ++;
    }
    system("rm /tmp/.DiskPartiting.info");
    //--------------------------------------
    //Read Disk-----------------------------
    //--------------------------------------
    int DiskCount=0;
    system("ls /dev/sd? > /tmp/.Disk.info");
    fp = fopen("/tmp/.Disk.info","r");
    DiskComboBox->insertItem(-1,tr("---"));
    bzero(DiskPath,64);
    while(fscanf(fp,"%s",DiskPath) != EOF){
        DiskComboBox->insertItem(DiskCount,tr(DiskPath));
        bzero(DiskPath,64);
        DiskCount++;
    }
    system("rm /tmp/.Disk.info");
    //Done
    Title->setFont(TitleFont);
    Title->setText(tr("Partitioning..."));
    Title->setGeometry(27,17,500,50);

    Waring->setText(tr("<h2><font color=red>This is serious business, double check before you go!</font></h2>"));
    Waring->setGeometry(27,17+40,600,50);

    StartPartitingButton->setGeometry(27,17+40+50+15,200,70);
    StartPartitingButton->setText(tr("Start Partiting Your Disk"));

    Content->setFont(ContentFont);
    Content->setText(tr("请选择你的主分区"));
    Content->setGeometry(27,17+40+50+15+70+15,120,30);
    Content2->setFont(ContentFont);
    Content2->setText(tr("格式化"));
    Content2->setGeometry(100+27+10+25,17+40+50+15+70+15,90,30);
    CheckBox->setGeometry(100+27+10+25+15+30,17+40+50+15+70+15+3,25,25);

    Content3->setFont(ContentFont);
    Content3->setText(tr("请选择你的引导设备"));
    Content3->setGeometry(100+27+10+25+150,17+40+50+15+70+15,150,30);
    DiskComboBox->setGeometry(100+27+10+25+150,17+40+50+15+70+15+20+15,200,30);


    DiskPartitingComboBox->setGeometry(27,17+40+50+15+70+20+15+15,200,30);

    this->connect(DiskPartitingComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(SetCurrentDiskPartition(QString)));
    this->connect(DiskComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(SetCurrentDisk(QString)));
    this->connect(NextStepButton,SIGNAL(clicked()),this,SLOT(ReadyToGo()));
}

void GPartedDiskTab::StartPartiting(){
    emit AskHide();
    system("gparted");
    //-----------------------------------------------
    //Read DiskPartiting-----------------------------
    //-----------------------------------------------
    DiskPartitingComboBox->clear();
    int DiskPartitingCount = 0;
    system("ls /dev/sd?? > /tmp/.DiskPartiting.info");
    fp = fopen("/tmp/.DiskPartiting.info","r");
    DiskPartitingComboBox->insertItem(-1,tr("---"));
    bzero(DiskPartitingPath,64);
    while(fscanf(fp,"%s",DiskPartitingPath) != EOF){
        DiskPartitingComboBox->insertItem(DiskCount,tr(DiskPartitingPath));
        bzero(DiskPartitingPath,64);
        DiskPartitingCount ++;
    }
    system("rm /tmp/.DiskPartiting.info");
    //--------------------------------------
    //Read Disk-----------------------------
    //--------------------------------------
    int DiskCount=0;
    DiskComboBox->clear();
    system("ls /dev/sd? > /tmp/.Disk.info");
    fp = fopen("/tmp/.Disk.info","r");
    DiskComboBox->insertItem(-1,tr("---"));
    bzero(DiskPath,64);
    while(fscanf(fp,"%s",DiskPath) != EOF){
        DiskComboBox->insertItem(DiskCount,tr(DiskPath));
        bzero(DiskPath,64);
        DiskCount++;
    }
    system("rm /tmp/.Disk.info");
    //Done
    emit AskShow();
}

void GPartedDiskTab::SetCurrentDiskPartition(QString Now){
    CurrentDiskPartition = Now;
}

void GPartedDiskTab::SetCurrentDisk(QString Now){
    CurrentDisk = Now;
}

void GPartedDiskTab::ReadyToGo(){
    char TargetDisk[50];
    bzero(TargetDisk,50);
    char TargetPartiting[50];
    bzero(TargetPartiting,50);
    QByteArray ba = CurrentDiskPartition.toLatin1();
    strncpy(TargetPartiting,ba.data(),strlen(ba.data()));
    TargetPartiting[strlen(ba.data())] = '\0';

    ba = CurrentDisk.toLatin1();
    strncpy(TargetDisk,ba.data(),strlen(ba.data()));
    TargetDisk[strlen(ba.data())] = '\0';

    if(strlen(TargetPartiting) == 0){
        QMessageBox::warning(this,"Waring",tr("请选择分区"),QMessageBox::Yes);
        return;
    }
    if(strlen(TargetDisk) == 0){
        QMessageBox::warning(this,"Waring",tr("请选择引导设备"),QMessageBox::Yes);
        return;
    }

    if(CheckBox->isChecked() == true){
        int result;
        result = QMessageBox::question(this,"Questing",tr("你确定要格式化本分区？"),QMessageBox::Yes|QMessageBox::No);
        if(result == QMessageBox::Yes){
            char ExecBuff[512];
            bzero(ExecBuff,512);
            sprintf(ExecBuff,"mkfs.ext4 %s",TargetPartiting);
            result = system(ExecBuff);
            if(result != 0){
                QMessageBox::warning(this,"Waring",tr("格式化分区失败"),QMessageBox::Yes);
                return;
            }
        }else{
            return;
        }
    }
    emit PartedDone(CurrentDiskPartition,CurrentDisk);
}

//-----------------------------------

MainWorkThread::MainWorkThread(char *_TargetPartiting, char *_TargetDisk){
    TargetPartiting = new char[strlen(_TargetPartiting)+1];
    TargetDisk = new char[strlen(_TargetDisk)+1];
    strncpy(TargetPartiting,_TargetPartiting,strlen(_TargetPartiting));
    TargetPartiting[strlen(_TargetPartiting)] = '\0';
    strncpy(TargetDisk,_TargetDisk,strlen(_TargetDisk));
    TargetDisk[strlen(_TargetDisk)] = '\0';
}

void MainWorkThread::run(){
    //Installing System [Please Edit There]
}

MainWorkTab::MainWorkTab(char *TargetPartiting, char *TargetDisk, ProgressTabWidget *parent):
    ProgressTabWidget(parent){
    Title = new QLabel(this);
    Start = new QPushButton(this);
    MainWork = new MainWorkThread(TargetPartiting,TargetDisk);
    Title->setFont(TitleFont);
    Title->setText(tr("System Is Installing......"));
    Title->setGeometry(27,17,500,50);

    Start->setText(tr("Click to Start"));
    Start->setGeometry(27,17+40+50+15+70+15,200,60);
}
