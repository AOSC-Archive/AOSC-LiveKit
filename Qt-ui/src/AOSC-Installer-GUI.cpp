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

void ProgressTab::PartedDone(QString _TargetPartition,QString _TargetDisk){
    bzero(TargetPartition,64);
    QByteArray ba = _TargetPartition.toLatin1();
    strcpy(TargetPartition,ba.data());
    bzero(TargetDisk,64);
    ba = _TargetDisk.toLatin1();
    strcpy(TargetDisk,ba.data());
    printf("Target Partiting = %s\nTarget Disk= %s\n",TargetPartition,TargetDisk);
    //Add MainWork Tab
    MainWork = new MainWorkTab(TargetPartition,TargetDisk);
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
    char TargetPartition[50];
    bzero(TargetPartition,50);
    QByteArray ba = CurrentDiskPartition.toLatin1();
    strncpy(TargetPartition,ba.data(),strlen(ba.data()));
    TargetPartition[strlen(ba.data())] = '\0';

    ba = CurrentDisk.toLatin1();
    strncpy(TargetDisk,ba.data(),strlen(ba.data()));
    TargetDisk[strlen(ba.data())] = '\0';

    if(strlen(TargetPartition) == 0){
        QMessageBox::warning(this,"Waring",tr("请选择分区"),QMessageBox::Yes);
        return;
    }
    if(strlen(TargetDisk) == 0){
        QMessageBox::warning(this,"Waring",tr("请选择引导设备"),QMessageBox::Yes);
        return;
    }
    int result;
    result = QMessageBox::question(this,"Question",tr("你确定执行下一步骤？"),QMessageBox::Yes|QMessageBox::No);
    if(result == QMessageBox::No)
        return;
    if(CheckBox->isChecked() == true){
        result = QMessageBox::question(this,"Questing",tr("你确定要格式化本分区？"),QMessageBox::Yes|QMessageBox::No);
        if(result == QMessageBox::Yes){
            char ExecBuff[512];
            bzero(ExecBuff,512);
            sprintf(ExecBuff,"mkfs.ext4 %s",TargetPartition);
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

MainWorkThread::MainWorkThread(char *_TargetPartition, char *_TargetDisk){
    TargetPartition = new char[strlen(_TargetPartition)+1];
    TargetDisk = new char[strlen(_TargetDisk)+1];
    strncpy(TargetPartition,_TargetPartition,strlen(_TargetPartition));
    TargetPartition[strlen(_TargetPartition)] = '\0';
    strncpy(TargetDisk,_TargetDisk,strlen(_TargetDisk));
    TargetDisk[strlen(_TargetDisk)] = '\0';
}

void MainWorkThread::run(){
    Core = new AOSC_Installer_Core();
    int status = Core->MountFS(TargetPartition);
    if(status < 0){
        perror("Mount");
        emit CopyFileDone(-1);
        return;
    }
    system("ls -lR /mnt | grep ^- | wc -l > /tmp/.TotalFile.info");
    FILE *f = fopen("/tmp/.TotalFile.info","r");
    fscanf(f,"%d",&Total);
    printf("Total File = %d\n",Total);
    emit TotalFile(Total);
    connect(Core,SIGNAL(Copyed(int)),this,SLOT(FileCopyed(int)));
    int Status = Core->CopyFileToNewSystem();
    emit CopyFileDone(Status);
    //-----Set Grub--------------//
    emit SetGrubDone(Core->SetGrub(TargetDisk));
    //-----Update Grub-----------//
    emit UpdateGrubDone(Core->UpdateGrub());
    //-----Update Fstab----------//
    emit UpdateFstabDOne(Core->UpdateFstab(TargetPartition));
}
void MainWorkThread::FileCopyed(int Now){
    emit NowCopy(Now);
}

void MainWorkThread::SetUser(QString Name, QString Pass){
    char *UserName = new char[64];
    char *PassWord = new char[64];
    bzero(UserName,64);
    bzero(PassWord,64);
    QByteArray ba;
    ba = Name.toLatin1();
    strcpy(UserName,ba.data());
    UserName[strlen(ba.data())] = '\0';
    ba = Pass.toLatin1();
    strcpy(PassWord,ba.data());
    PassWord[strlen(ba.data())] = '\0';
    emit SetUseeDone(Core->SetUser(UserName,PassWord));
}

void MainWorkThread::SetRoot(QString Pass){
    char *PassWord = new char[64];
    bzero(PassWord,64);
    QByteArray ba;
    ba = Pass.toLatin1();
    strcpy(PassWord,ba.data());
    PassWord[strlen(ba.data())] = '\0';
    emit SetRootDone(Core->SetRootPassWord(PassWord));
}

//------------------------------------------
void MainWorkTab::FileCopying(int Now){
    ProgressBar->setValue(Now);
}

MainWorkTab::MainWorkTab(char *_TargetPartition, char *_TargetDisk, ProgressTabWidget *parent):
    ProgressTabWidget(parent){
    Title       = new QLabel(this);
    Content     = new QLabel(this);
    Start       = new QPushButton(this);
    SetNextButtonDisable();
    SetPervButtonDisable();
    bzero(TargetDisk,64);
    bzero(TargetPartition,64);
    strncpy(TargetPartition,_TargetPartition,strlen(_TargetPartition));
    TargetPartition[strlen(_TargetPartition)] = '\0';
    strncpy(TargetDisk,_TargetDisk,strlen(_TargetDisk));
    TargetDisk[strlen(_TargetDisk)] = '\0';

    Title->setFont(TitleFont);
    Title->setText(tr("System Is Ready To Install"));
    Title->setGeometry(27,17,500,50);

    Content->setFont(ContentFont);
    Content->setGeometry(27,17+50,500,50);

    Start->setText(tr("Click to Start"));
    Start->setGeometry(27,17+40+50+15+70+15,200,60);

    this->connect(Start,SIGNAL(clicked()),this,SLOT(Install_Start()));
}

void MainWorkTab::Install_Start(){
    Content->setText(tr("正在准备安装文件"));
    MainWork = new MainWorkThread(TargetPartition,TargetDisk);
    this->connect(MainWork,SIGNAL(TotalFile(int)),this,SLOT(TotalFileDone(int)));

    MainWork->run();
}

void MainWorkTab::TotalFileDone(int Total){
    TotalFile = Total;
    Content->setText(tr("正在复制安装文件"));
    Title->setText(tr("System is installing......"));
    ProgressBar = new QProgressBar(this);
    ProgressBar->setRange(0,TotalFile);
    ProgressBar->setGeometry(27,17+40+50+15+30,600,40);
    Start->hide();
    ProgressBar->show();
    this->connect(MainWork,SIGNAL(NowCopy(int)),this,SLOT(FileCopying(int)));
    this->connect(MainWork,SIGNAL(CopyFileDone(int)),this,SLOT(CopyDone(int)));
}

void MainWorkTab::CopyDone(int Status){
    if(Status == true){
        ProgressBar->setValue(TotalFile);
        Content->setText(tr("Basic System Installed"));
    }else{
        QMessageBox::warning(this,"Waring",tr("Install System Error!"),QMessageBox::Yes);
        exit(-1);
    }
}

void MainWorkTab::SetGrubDone(int Status){
    if(Status < 0){
        QMessageBox::warning(this,"Waring",tr("安装Grub失败!"),QMessageBox::Yes);
        exit(-1);
    }
    Content->setText(tr("Install Grub Success!"));
}

void MainWorkTab::SetUseeDone(int Status){
    if(Status < 0){
        QMessageBox::warning(this,"Waring",tr("设置用户数据失败!"),QMessageBox::Yes);
        exit(-1);
    }
    Content->setText(tr("Set User Information Success!"));
}

void MainWorkTab::SetRootDone(int Status){
    if(Status < 0){
        QMessageBox::warning(this,"Waring",tr("设置Root用户失败!"),QMessageBox::Yes);
        exit(-1);
    }
    Content->setText(tr("Set Root Information Success!"));
}

void MainWorkTab::UpdateGrubDone(int Status){
    if(Status < 0){
        QMessageBox::warning(this,"Waring",tr("配置Grub失败!"),QMessageBox::Yes);
        exit(-1);
    }
    Content->setText(tr("Update Grub Success!"));
}

void MainWorkTab::UpdateFstabDOne(int Status){
    if(Status < 0){
        QMessageBox::warning(this,"Waring",tr("更新Fstab失败!"),QMessageBox::Yes);
        exit(-1);
    }
    Content->setText(tr("Update Fstab Success!"));
}

//--------------------------------------
