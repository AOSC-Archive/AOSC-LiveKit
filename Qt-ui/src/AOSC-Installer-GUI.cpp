#include "AOSC-Installer-Basic-UI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <qt4/QtGui/QStyle>
#include <qt4/QtGui/QTabBar>
#include <qt4/QtGui/QMessageBox>
#include <qt4/QtCore/QFile>
#include <qt4/QtCore/QTextStream>
#include <qt4/QtCore/QByteArray>
#include <QProcess>

Th::Th(QThread *parent):
    QThread(parent){

}

void Th::run(){
    sleep(1);
    emit ST();
    this->terminate();
} 

ProgressTab::ProgressTab(QTabWidget *parent) :
    QTabWidget(parent){
    Core    = new AOSC_Installer_Core;
    SFSize  = new StatisticsFileSize;
/*    this->setMaximumSize(700,350);
    this->setMinimumSize(700,350); */
    this->showFullScreen(); 
    this->tabBar()->hide();

    Th *t = new Th;
    connect(t,SIGNAL(ST()),this,SLOT(AddTabs()));
    t->start();

    this->show(); 
} 

void ProgressTab::AddTabs(){
    printf("Now Size = %d\n",this->width());
/*    GPartedDisk = new GPartedDiskTab;
    this->addTab(GPartedDisk,tr("GPartedDisk")); */
    //Add Welcome Tab
    Welcome = new WelcomeTab;
    this->addTab(Welcome,tr("Welcome"));
    this->connect(Welcome,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(Welcome,SIGNAL(PervStep()),this,SLOT(PervStep()));
    //Add Get Started Tab
    GetStarted = new GetStartedTab;
    this->addTab(GetStarted,tr("GetStart"));
    this->connect(GetStarted,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(GetStarted,SIGNAL(PervStep()),this,SLOT(PervStep()));
    //Add Reading Tab
    Reading     = new ReadingTab;
    this->addTab(Reading,tr("Reading"));
    this->connect(Reading,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(Reading,SIGNAL(PervStep()),this,SLOT(PervStep()));
    //Add GParted Tab
    GPartedDisk = new GPartedDiskTab;
    this->addTab(GPartedDisk,tr("GPartedDisk"));
    this->connect(GPartedDisk,SIGNAL(PartedDone(QString,QString)),this,SLOT(PartedDone(QString,QString)));
    this->connect(GPartedDisk,SIGNAL(IsEFIDevice(QString)),Core,SLOT(IsEfiDevice(QString)));
    this->connect(GPartedDisk,SIGNAL(CurrentFileSystemChanged(QString)),Core,SLOT(CurrentFileSystemChanged(QString)));
    this->connect(GPartedDisk,SIGNAL(PervStep()),this,SLOT(PervStep()));
    this->connect(GPartedDisk,SIGNAL(AskHide()),this,SLOT(AskHide()));
    this->connect(GPartedDisk,SIGNAL(AskShow()),this,SLOT(AskShow()));
}

ProgressTab::~ProgressTab(){
    if(Core->isRunning() == true){
        system("sudo killall cp");
    }
}

void ProgressTab::resizeEvent(QResizeEvent *){
    this->resize(this->width(),this->height());
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
    MainWork = new MainWorkTab(_TargetPartition,_TargetDisk);
    this->addTab(MainWork,tr("MainWork"));
    this->connect(MainWork,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(MainWork,SIGNAL(PervStep()),this,SLOT(PervStep()));
    this->connect(MainWork,SIGNAL(S_StartInstall(QString,QString)),this,SLOT(StartInstall(QString,QString)));
    // Next Page
    int current = this->currentIndex();
    this->setCurrentIndex(current+1);
}

void ProgressTab::StartInstall(QString TargetPartition, QString TargetDisk){
    Core->SetInstallTarget(TargetPartition,TargetDisk);
    this->connect(SFSize,SIGNAL(Copyed(int))        ,MainWork,SLOT(FileCopying(int)));
    this->connect(Core,SIGNAL(CopyDone(int))        ,MainWork,SLOT(CopyDone(int)));
    this->connect(Core,SIGNAL(SFSizeStop())         ,SFSize  ,SLOT(CopyDone()));
    this->connect(Core,SIGNAL(TotalFile(int))       ,MainWork,SLOT(TotalFileDone(int)));
    this->connect(Core,SIGNAL(SFSizeStart(int))     ,SFSize  ,SLOT(GetReady(int)));
    this->connect(Core,SIGNAL(SetGrubDone(int))     ,MainWork,SLOT(SetGrubDone(int)));
    this->connect(Core,SIGNAL(MountFSDone(int))     ,MainWork,SLOT(MountFSDone(int)));
    this->connect(Core,SIGNAL(UpdateGrubDone(int))  ,MainWork,SLOT(UpdateGrubDone(int)));
    this->connect(Core,SIGNAL(UpdateFstabDone(int)) ,MainWork,SLOT(UpdateFstabDone(int)));
    Core->start();

    User    = new UserTab(this->width());
    Done    = new DoneTab;
    this->addTab(User,tr("User"));
    this->addTab(Done,tr("Done"));
    this->connect(User,SIGNAL(StartSetUserInformation(QString,QString,QString)),this,SLOT(StartSetUserInformation(QString,QString,QString)));
    this->connect(User,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(Done,SIGNAL(NextSetp()),this,SLOT(AllDone()));
}

void ProgressTab::StartSetUserInformation(QString RootPass, QString UserName, QString UserPass){
    this->connect(Core,SIGNAL(SetDone(int)),    Done,SLOT(SetDone(int)));
//    this->connect(Core,SIGNAL(SetRootDone(int)),User,SLOT(SetRootDone(int)));
//    this->connect(Core,SIGNAL(SetUserDone(int)),User,SLOT(SetUserDone(int)));
    Core->SetRootPassWord(RootPass);
    Core->SetUser(UserName,UserPass);
}

void ProgressTab::AllDone(){
    Core->AllDone();
    exit(0);
}

//##########################################################


ProgressTabWidget::ProgressTabWidget(QWidget *parent) :
    QWidget(parent){
    NextStepButton = new QPushButton(this);
    PervStepButton = new QPushButton(this);
    NextStepButton->setText(tr("前进"));
    PervStepButton->setText(tr("后退"));
    connect(NextStepButton,SIGNAL(clicked()),this,SLOT(NextStepClicked()));
    connect(PervStepButton,SIGNAL(clicked()),this,SLOT(PervStepClicked()));
    TitleFont.setPointSize(32);
    TitleFont.setBold(true);
    SecondaryTitleFont.setPointSize(24);
    SecondaryTitleFont.setBold(true);
    ContentFont.setPointSize(12);
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

void ProgressTabWidget::SetNextButtonText(QString Text){
    NextStepButton->setText(Text);
}

//#########################################################

WelcomeTab::WelcomeTab(ProgressTabWidget *parent) :
    ProgressTabWidget(parent){
    Title    = new QLabel(this);
    Content  = new QLabel(this);

    Title->setText(tr("诶，你好!"));
    Title->setFont(TitleFont);
    Title->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y,BASIC_TITLE_W,BASIC_TITLE_H);

    Content->setText(tr("感谢尝试安同开源社区最新的发行版!\n\n你准备好将发行版安装到你亲爱的电脑上了么?"));
    Content->setFont(ContentFont);
    Content->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE,BASIC_TITLE_W,BASIC_TITLE_H);

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

    Title->setText(tr("准备开始"));
    SecondaryTitle->setText(tr("我们接下来需要做这些事情……"));
    Content->setText(tr(" - 进行大量的阅读（托腮 \n\n - 将磁盘分区\n\n - 让我们认识一下你\n\n - 开始安装\n\n - 尽情享用!"));

    Title->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y,BASIC_TITLE_W,BASIC_TITLE_H);
    SecondaryTitle->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE,BASIC_TITLE_W,BASIC_TITLE_H);
    Content->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+BASIC_TITLE_CONTENT_SPACE,BASIC_TITLE_W,BASIC_TITLE_H+250);
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
    Title->setText(tr("阅读时间!"));
    Title->setGeometry(27,17,BASIC_TITLE_W,BASIC_TITLE_H);

    Content->setFont(ContentFont);
    Content->setText(tr("我保证会乖乖地遵守此许可协议!"));

    this->setLayout(VBoxLayout);

    VBoxLayout->addSpacing(100);
    VBoxLayout->addWidget(Browser);
    VBoxLayout->addLayout(HBoxLayout);
    HBoxLayout->addStretch(600);
    HBoxLayout->addWidget(Content);
    HBoxLayout->addStretch(30);
    HBoxLayout->addWidget(CheckBox);
    VBoxLayout->addSpacing(60);

    QFile file("/usr/share/ulinst/data/GNU_License.html");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        perror("Open License File");
        QMessageBox::warning(this,tr("打开许可文件"),tr("打开许可文件时出错!"),QMessageBox::Yes);
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
    Warning                  = new QLabel(this);
    Content                 = new QLabel(this);
    Content2                = new QLabel(this);
    Content3                = new QLabel(this);
    Content4                = new QLabel(this);
    FormatSwitchLabel       = new QLabel(this);
    EFISwitchLabel          = new QLabel(this);
    CheckBox                = new QCheckBox(this);
    isefi                   = new QCheckBox(this);
    DiskPartitingComboBox   = new QComboBox(this);
    DiskComboBox            = new QComboBox(this);
    EfiDiskPartiting        = new QComboBox(this);
    FormatSwitch            = new QComboBox(this);
    StartPartitingButton    = new QPushButton(this);
    DiskPath                = new char[64];
    DiskPartitingPath       = new char[64];

    this->connect(StartPartitingButton,SIGNAL(clicked()),this,SLOT(StartPartiting()));
    efi = 0;
    isFileSystemChanged = 0;
    this->connect(isefi,SIGNAL(stateChanged(int)),this,SLOT(iseficlicked(int)));
    this->connect(CheckBox,SIGNAL(stateChanged(int)),this,SLOT(FormatClicked(int)));

    EfiDiskPartiting->hide();
    FormatSwitch->hide();
    FormatSwitchLabel->hide();
    EFISwitchLabel->hide();
    //-----------------------------------------------
    //Read DiskPartiting-----------------------------
    //-----------------------------------------------
    DiskPartitingComboBox->clear();
    int DiskPartitingCount = 0;
    char ExecBuff[64];
    sprintf(ExecBuff,"ls /dev/sd?? > %s",_TMP_PARTITION_FILE);
    system(ExecBuff);
    sprintf(ExecBuff,"ls /dev/sd??? >> %s",_TMP_PARTITION_FILE);
    system(ExecBuff);
    fp = fopen(_TMP_PARTITION_FILE,"r");
    DiskPartitingComboBox->insertItem(-1,tr("---"));
    bzero(DiskPartitingPath,64);
    while(fscanf(fp,"%s",DiskPartitingPath) != EOF){
        DiskPartitingComboBox->insertItem(DiskCount,tr(DiskPartitingPath));
        bzero(DiskPartitingPath,64);
        DiskPartitingCount ++;
    }
    sprintf(ExecBuff,"rm -rf %s",_TMP_PARTITION_FILE);
    system(ExecBuff);
    //--------------------------------------
    //Read Disk-----------------------------
    //--------------------------------------
    int DiskCount=0;
    DiskComboBox->clear();
    sprintf(ExecBuff,"ls /dev/sd? > %s",_TMP_DISK_FILE);
    system(ExecBuff);
    fp = fopen(_TMP_DISK_FILE,"r");
    DiskComboBox->insertItem(-1,tr("---"));
    bzero(DiskPath,64);
    while(fscanf(fp,"%s",DiskPath) != EOF){
        DiskComboBox->insertItem(DiskCount,tr(DiskPath));
        bzero(DiskPath,64);
        DiskCount++;
    }
    sprintf(ExecBuff,"rm -rf %s",_TMP_DISK_FILE);
    system(ExecBuff);
    //Done
    FormatSwitch->clear();
    FormatSwitch->insertItem(-1,tr("---"));
    FormatSwitch->insertItem(0,tr("ext2"));
    FormatSwitch->insertItem(1,tr("ext3"));
    FormatSwitch->insertItem(2,tr("ext4"));
    FormatSwitch->insertItem(3,tr("btrfs"));
    FormatSwitch->insertItem(4,tr("xfs"));

    QFont D1;
    D1.setPointSize(10);

    Title->setFont(TitleFont);
    Title->setText(tr("磁盘分区中……"));
    Title->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y,BASIC_TITLE_W,BASIC_TITLE_H);

    Warning->setText(tr("<h2><font color=red>这事儿很重要，请检查清楚再继续!</font></h2>"));
    Warning->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE,BASIC_TITLE_W,BASIC_TITLE_H);

    StartPartitingButton->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+55,BASIC_TITLE_W,BASIC_TITLE_H);
    StartPartitingButton->setText(tr("点击我打开磁盘分区软件"));

    Content->setFont(D1);
    Content->setText(tr("请选择你的主分区"));
    Content->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+55+75,BASIC_TITLE_W,BASIC_TITLE_H);
    Content2->setFont(D1);
    Content2->setText(tr("格式化"));
    Content2->setGeometry(BASIC_TITLE_X+100+10+25+25,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140+9,90,30);
    CheckBox->setGeometry(BASIC_TITLE_X+100+10+25,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140+5+9,25,25);

    Content4->setFont(D1);
    EFISwitchLabel->setFont(D1);
    Content4->setText(tr("是否为EFI设备"));
    EFISwitchLabel->setText(tr("选择你的EFI分区"));
    Content4->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140+70,90,30);
    isefi->setGeometry(BASIC_TITLE_X+100,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140+70+5,25,25);
    EFISwitchLabel->setGeometry(BASIC_TITLE_X+100+25,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140+35+35,120,30);
    EfiDiskPartiting->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140+35+70,200,30);

    FormatSwitchLabel->setFont(D1);
    FormatSwitchLabel->setText(tr("选择分区文件系统"));
    FormatSwitchLabel->setGeometry(BASIC_TITLE_X+100+10+25+150,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140+35+35,90,30);
    FormatSwitch->setGeometry(BASIC_TITLE_X+100+10+25+150,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140+35+70,200,30);

    Content3->setFont(D1);
    Content3->setText(tr("请选择你的引导设备"));
    Content3->setGeometry(BASIC_TITLE_X+100+10+25+150,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+55+85+10,150,30);
    DiskComboBox->setGeometry(BASIC_TITLE_X+100+10+25+150,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140+35,200,30);

    DiskPartitingComboBox->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140+35,200,30);

    this->connect(DiskPartitingComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(SetCurrentDiskPartition(QString)));
    this->connect(DiskComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(SetCurrentDisk(QString)));
    this->connect(FormatSwitch,SIGNAL(currentIndexChanged(QString)),this,SLOT(SetCurrentFormatFileSystem(QString)));
    this->connect(NextStepButton,SIGNAL(clicked()),this,SLOT(ReadyToGo()));
}

void GPartedDiskTab::iseficlicked(int status){
    if(status == 2){
        efi = 1;
        EFISwitchLabel->show();
        EfiDiskPartiting->show();
        EfiDiskPartiting->clear();
        int DiskPartitingCount = 0;
        char ExecBuff[64];
        sprintf(ExecBuff,"ls /dev/sd?? > %s",_TMP_PARTITION_FILE);
        system(ExecBuff);
        sprintf(ExecBuff,"ls /dev/sd??? >> %s",_TMP_PARTITION_FILE);
        system(ExecBuff);
        fp = fopen(_TMP_PARTITION_FILE,"r");
        EfiDiskPartiting->insertItem(-1,tr("---"));
        bzero(DiskPartitingPath,64);
        while(fscanf(fp,"%s",DiskPartitingPath) != EOF){
            EfiDiskPartiting->insertItem(DiskCount,tr(DiskPartitingPath));
            bzero(DiskPartitingPath,64);
            DiskPartitingCount ++;
        }
        sprintf(ExecBuff,"rm -rf %s",_TMP_PARTITION_FILE);
        system(ExecBuff);
    }else{
        efi = 0;
        EFISwitchLabel->hide();
        EfiDiskPartiting->hide();
    }
}

void GPartedDiskTab::FormatClicked(int status){
    if(status == 2){
        isFileSystemChanged = 1;
        FormatSwitch->show();
        FormatSwitchLabel->show();
    }
    else{
        isFileSystemChanged = 0;
        FormatSwitch->hide();
        FormatSwitchLabel->hide();
    }
}

void GPartedDiskTab::SetCurrentFormatFileSystem(QString Current){
    CurrentFormatFileSystem = Current;
}

void GPartedDiskTab::StartPartiting(){
    emit AskHide();
    system("sudo gparted");
    //-----------------------------------------------
    //Read DiskPartiting-----------------------------
    //-----------------------------------------------
    DiskPartitingComboBox->clear();
    int DiskPartitingCount = 0;
    char ExecBuff[64];
    sprintf(ExecBuff,"ls /dev/sd?? > %s",_TMP_PARTITION_FILE);
    system(ExecBuff);
    fp = fopen(_TMP_PARTITION_FILE,"r");
    DiskPartitingComboBox->insertItem(-1,tr("---"));
    bzero(DiskPartitingPath,64);
    while(fscanf(fp,"%s",DiskPartitingPath) != EOF){
        DiskPartitingComboBox->insertItem(DiskCount,tr(DiskPartitingPath));
        bzero(DiskPartitingPath,64);
        DiskPartitingCount ++;
    }
    sprintf(ExecBuff,"rm -rf %s",_TMP_PARTITION_FILE);
    system(ExecBuff);
    //--------------------------------------
    //Read Disk-----------------------------
    //--------------------------------------
    int DiskCount=0;
    DiskComboBox->clear();
    sprintf(ExecBuff,"ls /dev/sd? > %s",_TMP_DISK_FILE);
    system(ExecBuff);
    fp = fopen(_TMP_DISK_FILE,"r");
    DiskComboBox->insertItem(-1,tr("---"));
    bzero(DiskPath,64);
    while(fscanf(fp,"%s",DiskPath) != EOF){
        DiskComboBox->insertItem(DiskCount,tr(DiskPath));
        bzero(DiskPath,64);
        DiskCount++;
    }
    sprintf(ExecBuff,"rm -rf %s",_TMP_DISK_FILE);
    system(ExecBuff);
    //Done
    emit AskShow();
}

void GPartedDiskTab::SetCurrentDiskPartition(QString Now){
    CurrentDiskPartition = Now;
}

void GPartedDiskTab::SetCurrentDisk(QString Now){
    CurrentDisk = Now;
}

void GPartedDiskTab::SetCurrentEfiPartition(QString Now){
    CurrentEfiPartition = Now;
}

void GPartedDiskTab::ReadyToGo(){
    char TargetDisk[50];
    bzero(TargetDisk,50);
    char TargetPartition[50];
    bzero(TargetPartition,50);
    char CurrentFileSystem[50];
    QByteArray ba = CurrentDiskPartition.toLatin1();
    strncpy(TargetPartition,ba.data(),strlen(ba.data()));
    TargetPartition[strlen(ba.data())] = '\0';

    ba = CurrentDisk.toLatin1();
    strncpy(TargetDisk,ba.data(),strlen(ba.data()));
    TargetDisk[strlen(ba.data())] = '\0';

    // umount TargetPartition before you do anything
    char ExecBuff[512];
    bzero(ExecBuff,512);
    sprintf(ExecBuff,"sudo umount %s",TargetPartition);
    system(ExecBuff);

    if(strlen(TargetPartition) == 0){
        QMessageBox::warning(this,"Warning",tr("请选择一个分区"),QMessageBox::Yes);
        return;
    }
    if(strlen(TargetDisk) == 0){
        QMessageBox::warning(this,"Warning",tr("请选择引导设备"),QMessageBox::Yes);
        return;
    }
    if(efi == 1){
        if(CurrentEfiPartition == ""){
            QMessageBox::warning(this,"Warning",tr("请选择一EFI个分区"),QMessageBox::Yes);
            return;
        }
        // umount target EFIPartition
        sprintf(ExecBuff,"sudo umount %s",TargetPartition);
        system(ExecBuff);
    }
    int result;
    if(CheckBox->isChecked() == true){
        ba = CurrentFormatFileSystem.toLatin1();
        strncpy(CurrentFileSystem,ba.data(),strlen(ba.data()));
        CurrentFileSystem[strlen(ba.data())] = '\0';
        if(strlen(CurrentFileSystem) == 0){
            QMessageBox::warning(this,tr("Warning"),tr("请选择分区文件系统"),QMessageBox::Yes);
            return;
        }
        result = QMessageBox::question(this,"Questing",tr("你确定要格式化此分区?"),QMessageBox::Yes|QMessageBox::No);
        if(result == QMessageBox::Yes){
            sprintf(ExecBuff,"sudo mkfs.%s %s",CurrentFileSystem,TargetPartition);
            result = system(ExecBuff);
            if(result != 0){
                QMessageBox::warning(this,"Warning",tr("OMG, 格式化分区失败!"),QMessageBox::Yes);
                return;
            }
            emit CurrentFileSystemChanged(CurrentFormatFileSystem);
        }else{
            return;
        }
    }else{
        result = QMessageBox::warning(this,tr("Warning"),tr("如果不格式化分区，我们不保证系统能够正常工作，继续？"),QMessageBox::Yes|QMessageBox::No);
        if(result == QMessageBox::No)   return;
    }
    result = QMessageBox::question(this,"Question",tr("确定开始安装?"),QMessageBox::Yes|QMessageBox::No);
    if(result == QMessageBox::No)
        return;
    if(efi == 1)    emit IsEFIDevice(CurrentEfiPartition);
    emit PartedDone(CurrentDiskPartition,CurrentDisk);
}

//-----------------------------------
void MainWorkTab::FileCopying(int Now){
    ProgressBar->setValue(Now);
}

MainWorkTab::MainWorkTab(QString _TargetPartition, QString _TargetDisk, ProgressTabWidget *parent):
    ProgressTabWidget(parent){
    Title       = new QLabel(this);
    Content     = new QLabel(this);
    Content2    = new QLabel(this);
    Start       = new QPushButton(this);
    EditFstab   = new QPushButton(this);
    SetNextButtonDisable();
    SetPervButtonDisable();

    Title->setFont(TitleFont);
    Title->setText(tr("系统已完成安装前的准备"));
    Title->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y,700,BASIC_TITLE_H);

    Content->setFont(ContentFont);
    Content->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE,BASIC_TITLE_W,BASIC_TITLE_H);

    Content2->setFont(ContentFont);
    Content2->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+25,BASIC_TITLE_W,BASIC_TITLE_H);;

    Start->setText(tr("Click to Start"));
    Start->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140,200,50);
    EditFstab->setText(tr("我要自行修改Fstab"));
    EditFstab->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+140,150,25);
    EditFstab->hide();

    this->connect(Start,SIGNAL(clicked()),this,SLOT(StartInstall()));
    TargetPartition = _TargetPartition;
    TargetDisk      = _TargetDisk;
}

void MainWorkTab::StartInstall(void){
    Content->setText(tr("正在准备安装文件"));
    Start->hide();
    EditFstab->show();
//    emit S_StartInstall(TargetPartition,TargetDisk);
    ManualEditFstab();
}

void MainWorkTab::MountFSDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,"Warning",tr("挂载磁盘出错!"),QMessageBox::Yes);
        exit(-1);
    }
}

void MainWorkTab::TotalFileDone(int Total){
    TotalFile = Total;
    Content->setText(tr("正在复制安装文件"));
    Title->setText(tr("系统正在安装……"));
    printf("TotalFile = %d\n",Total);
    ProgressBar = new QProgressBar(this);
    ProgressBar->setRange(0,TotalFile);
    ProgressBar->setGeometry(12,BASIC_TITLE_Y+BASIC_TITLE_CONTENT_SPACE+40+15+30,this->width()-24,40);
    Start->hide();
    ProgressBar->show();
}

void MainWorkTab::CopyDone(int Status){
    if(Status == 0){
        ProgressBar->setValue(TotalFile);
        Content->setText(tr("基础系统安装完毕"));
        Content2->setText(tr("正在安装Grub......"));
    }else{
        QMessageBox::warning(this,"Warning",tr("系统安装出错!"),QMessageBox::Yes);
        exit(-1);
    }
}

void MainWorkTab::SetGrubDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,"Warning",tr("安装 GRUB 失败!"),QMessageBox::Yes);
        exit(-1);
    }
    Content->setText(tr("GRUB 安装成功!"));
    Content2->setText(tr("正在配置Grub......"));
    ProgressBar->setRange(0,0);
}

void MainWorkTab::ManualEditFstab(){
    QProcess *FstabEditor = new QProcess(this);
    QString Program = "sudo";
    QStringList ArgList;
    ArgList << "gvim" << "/target/etc/fstab";
    FstabEditor->start(Program,ArgList);
}

void MainWorkTab::UpdateFstabDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,"Warning",tr("更新 /etc/fstab 失败!"),QMessageBox::Yes);
        exit(-1);
    }
    Content->setText(tr("更新 /etc/fstab 成功!"));
    Content2->setText(tr("基础系统安装完毕!"));
    ProgressBar->setRange(0,1);
    ProgressBar->setValue(1);
    SetNextButtonEnable();
}

void MainWorkTab::UpdateGrubDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,"Warning",tr("GRUB 配置失败!"),QMessageBox::Yes);
        exit(-1);
    }
    Content->setText(tr("GRUB 配置成功!"));
}

//--------------------------------------
UserTab::UserTab(int x, ProgressTabWidget *parent):
    ProgressTabWidget(parent){
    Title           = new QLabel(this);
    RootPassTitle   = new QLabel(this);
    RootPassTitle2  = new QLabel(this);
    RootPassEdit    = new QLineEdit(this);
    RootPassEdit2   = new QLineEdit(this);

    SetPervButtonDisable();

    RootPassEdit->setEchoMode(QLineEdit::Password);
    RootPassEdit2->setEchoMode(QLineEdit::Password);

    Title->setFont(TitleFont);
    Title->setText(tr("告诉我们你是谁"));
    Title->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y,BASIC_TITLE_W,BASIC_TITLE_H);

    RootPassTitle->setFont(ContentFont);
    RootPassTitle->setText(tr("设置Root的密码"));
    RootPassTitle->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+15+50,x/2-(BASIC_TITLE_X*2),EDITLINE_HEIGTH);

    RootPassEdit->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+15+50+EDITLINE_HEIGTH,x/2-(BASIC_TITLE_X*2),EDITLINE_HEIGTH);

    RootPassTitle2->setFont(ContentFont);
    RootPassTitle2->setText(tr("再次输入密码"));
    RootPassTitle2->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+15+50+EDITLINE_HEIGTH*2,x/2-(BASIC_TITLE_X*2),EDITLINE_HEIGTH);

    RootPassEdit2->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+15+50+EDITLINE_HEIGTH*3,x/2-(BASIC_TITLE_X*2),EDITLINE_HEIGTH);


    UserNameTitle = new QLabel(this);
    UserNameEdit  = new QLineEdit(this);
    UserNameTitle->setFont(ContentFont);
    UserNameTitle->setText(tr("设置你主用户的用户名"));
    UserNameTitle->setGeometry(BASIC_TITLE_X+x/2,BASIC_TITLE_Y+15+50,x/2-(BASIC_TITLE_X*2),EDITLINE_HEIGTH);
    UserNameEdit->setGeometry(BASIC_TITLE_X+x/2,BASIC_TITLE_Y+15+50+EDITLINE_HEIGTH,x/2-(BASIC_TITLE_X*2),EDITLINE_HEIGTH);

    UserPassTitle = new QLabel(this);
    UserPassTitle2= new QLabel(this);
    UserPassEdit  = new QLineEdit(this);
    UserPassEdit2 = new QLineEdit(this);
    UserPassEdit->setEchoMode(QLineEdit::Password);
    UserPassEdit2->setEchoMode(QLineEdit::Password);
    UserPassTitle->setFont(ContentFont);
    UserPassTitle->setText(tr("设置你主用户的密码"));
    UserPassTitle2->setFont(ContentFont);
    UserPassTitle2->setText(tr("再次输入密码"));
    UserPassTitle->setGeometry(BASIC_TITLE_X+x/2,BASIC_TITLE_Y+15+50+EDITLINE_HEIGTH*2,x/2-(BASIC_TITLE_X*2),EDITLINE_HEIGTH);
    UserPassEdit->setGeometry(BASIC_TITLE_X+x/2,BASIC_TITLE_Y+15+50+EDITLINE_HEIGTH*3,x/2-(BASIC_TITLE_X*2),EDITLINE_HEIGTH);
    UserPassTitle2->setGeometry(BASIC_TITLE_X+x/2,BASIC_TITLE_Y+15+50+EDITLINE_HEIGTH*4,x/2-(BASIC_TITLE_X*2),EDITLINE_HEIGTH);
    UserPassEdit2->setGeometry(BASIC_TITLE_X+x/2,BASIC_TITLE_Y+15+50+EDITLINE_HEIGTH*5,x/2-(BASIC_TITLE_X*2),EDITLINE_HEIGTH);

    this->connect(NextStepButton,SIGNAL(clicked()),this,SLOT(SetUserInformation()));
}

void UserTab::SetUserInformation(){
    RootPass    = RootPassEdit->text();
    RootPass2   = RootPassEdit2->text();
    UserName    = UserNameEdit->text();
    UserPass    = UserPassEdit->text();
    UserPass2   = UserPassEdit2->text();
    if(RootPass == "" || RootPass2 == ""){
        QMessageBox::warning(this,"警告",tr("请设置Root密码"),QMessageBox::Yes);
        return;
    }
    if(RootPass != RootPass2){
        QMessageBox::warning(this,"警告",tr("Root密码不一致"),QMessageBox::Yes);
        return;
    }
    if(UserName == ""){
        QMessageBox::warning(this,"警告",tr("请设置主用的的用户名"),QMessageBox::Yes);
        return;
    }
    if(UserPass == "" || UserPass2 == ""){
        QMessageBox::warning(this,"警告",tr("请设置主用户的密码"),QMessageBox::Yes);
        return;
    }
    if(UserPass != UserPass2){
        QMessageBox::warning(this,"警告",tr("用户密码不一致"),QMessageBox::Yes);
        return;
    }
    int result = QMessageBox::question(this,"提示",tr("核对信息无误请继续"),QMessageBox::Yes|QMessageBox::No);
    if(result == QMessageBox::Yes)  emit StartSetUserInformation(RootPass,UserName,UserPass);
}

void UserTab::SetRootDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,"Warning",tr("Root 用户配置失败!"),QMessageBox::Yes);
        exit(-1);
    }
}

void UserTab::SetUserDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,"Warning",tr("设置用户数据失败!"),QMessageBox::Yes);
        exit(-1);
    }
}
//------------------------------------------------------------------
DoneTab::DoneTab(ProgressTabWidget *parent):
    ProgressTabWidget(parent){
    NowStep=0;
    Title   = new QLabel(this);
    Title->setFont(TitleFont);
    Title->setText(tr("工作圆满完成 ;-)"));
    Title->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y,BASIC_TITLE_W,BASIC_TITLE_H);

    Content = new QLabel(this);
    Content->setFont(ContentFont);
    
    Content->setText(tr("\n\n请稍候……目前完成按钮可能不能使用，还有部分配置正在运行。\n\n请手动重启计算机来启动新系统"));
    Content->setGeometry(BASIC_TITLE_X,BASIC_TITLE_Y+50,BASIC_TITLE_W,BASIC_TITLE_H);

    SetPervButtonDisable();
    SetNextButtonText(tr("完成"));
}

void DoneTab::SetDone(int status){
    NowStep++;
    if(status != 0){
        QMessageBox::warning(this,tr("Warning"),tr("配置环节出现致命错误"),QMessageBox::Yes);
        exit(0);
    }
    if(NowStep == 3){
        Title->setText(tr("工作圆满完成 ;-)"));
        Content->setText(tr("请手动重启计算机来启动新系统"));
        SetNextButtonEnable();
    }
}

