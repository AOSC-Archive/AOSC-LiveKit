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

ProgressTab::ProgressTab(QTabWidget *parent) :
    QTabWidget(parent){
    Core    = new AOSC_Installer_Core;
    SFSize  = new StatisticsFileSize;
    if(Core->CheckEnvironment() != _EN_LIVE_CD_){
        QMessageBox::warning(this,tr("错误"),tr("你现在不在LiveCD环境下，安装程序将立即退出。"),QMessageBox::Yes);
        exit(-1);
    }
    this->setMaximumSize(900,500);
    this->setMinimumSize(700,350);
    this->tabBar()->hide();
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
    this->connect(GPartedDisk,SIGNAL(PervStep()),this,SLOT(PervStep()));
    this->connect(GPartedDisk,SIGNAL(AskHide()),this,SLOT(AskHide()));
    this->connect(GPartedDisk,SIGNAL(AskShow()),this,SLOT(AskShow()));
}
ProgressTab::~ProgressTab(){
    if(Core->isRunning() == true){
        system("sudo killall cp");
    }
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

    User    = new UserTab;
    Done    = new DoneTab;
    this->addTab(User,tr("User"));
    this->addTab(Done,tr("Done"));
    this->connect(User,SIGNAL(StartSetUserInformation(QString,QString,QString)),this,SLOT(StartSetUserInformation(QString,QString,QString)));
    this->connect(User,SIGNAL(NextSetp()),this,SLOT(NextStep()));
    this->connect(Done,SIGNAL(NextSetp()),this,SLOT(AllDone()));
}

void ProgressTab::StartSetUserInformation(QString RootPass, QString UserName, QString UserPass){
    this->connect(Core,SIGNAL(SetRootDone(int)),User,SLOT(SetRootDone(int)));
    this->connect(Core,SIGNAL(SetUserDone(int)),User,SLOT(SetUserDone(int)));
    Core->SetRootPassWord(RootPass);
    Core->SetUser(UserName,UserPass);
}

void ProgressTab::AllDone(){
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
    Title->setGeometry(27,17,27*6,50);

    Content->setText(tr("感谢尝试安同开源社区最新的发行版!\n\n你准备好将发行版安装到你亲爱的电脑上了么?"));
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

    Title->setText(tr("准备开始"));
    SecondaryTitle->setText(tr("我们接下来需要做这些事情……"));
    Content->setText(tr(" - 进行大量的阅读（托腮 \n\n - 将磁盘分区\n\n - 让我们认识一下你\n\n - 开始安装\n\n - 尽情享用!"));

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
    Title->setText(tr("阅读时间!"));
    Title->setGeometry(27,17,500,50);

    Content->setFont(ContentFont);
    Content->setText(tr("我保证会乖乖地遵守此许可协议!"));

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
    Title->setFont(TitleFont);
    Title->setText(tr("磁盘分区中……"));
    Title->setGeometry(27,17,500,50);

    Warning->setText(tr("<h2><font color=red>这事儿很重要，请检查清楚再继续!</font></h2>"));
    Warning->setGeometry(27,17+40,600,50);

    StartPartitingButton->setGeometry(27,17+40+50+15,200,70);
    StartPartitingButton->setText(tr("点击我打开磁盘分区软件"));

    Content->setFont(ContentFont);
    Content->setText(tr("请选择你的主分区"));
    Content->setGeometry(27,17+40+50+15+70+15,120,30);
    Content2->setFont(ContentFont);
    Content2->setText(tr("格式化"));
    Content2->setGeometry(100+27+10+25+10+5,17+40+50+15+70+15,90,30);
    CheckBox->setGeometry(100+27+10+10+10+5,17+40+50+15+70+15+3,25,25);

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
        QMessageBox::warning(this,"Warning",tr("请选择一个分区"),QMessageBox::Yes);
        return;
    }
    if(strlen(TargetDisk) == 0){
        QMessageBox::warning(this,"Warning",tr("请选择引导设备"),QMessageBox::Yes);
        return;
    }
    int result;
    result = QMessageBox::question(this,"Question",tr("确定开始安装?"),QMessageBox::Yes|QMessageBox::No);
    if(result == QMessageBox::No)
        return;
    if(CheckBox->isChecked() == true){
        result = QMessageBox::question(this,"Questing",tr("你确定要格式化此分区?"),QMessageBox::Yes|QMessageBox::No);
        if(result == QMessageBox::Yes){
            char ExecBuff[512];
            bzero(ExecBuff,512);
            sprintf(ExecBuff,"sudo mkfs.ext4 %s",TargetPartition);
            result = system(ExecBuff);
            if(result != 0){
                QMessageBox::warning(this,"Warning",tr("OMG, 格式化分区失败!"),QMessageBox::Yes);
                return;
            }
        }else{
            return;
        }
    }
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
    SetNextButtonDisable();
    SetPervButtonDisable();

    Title->setFont(TitleFont);
    Title->setText(tr("系统已完成安装前的准备"));
    Title->setGeometry(27,17,500,50);

    Content->setFont(ContentFont);
    Content->setGeometry(27,17+50,500,25);

    Content2->setFont(ContentFont);
    Content2->setGeometry(27,17+50+25,500,25);

    Start->setText(tr("Click to Start"));
    Start->setGeometry(27,17+40+50+15+70+15,200,60);

    this->connect(Start,SIGNAL(clicked()),this,SLOT(StartInstall()));
    TargetPartition = _TargetPartition;
    TargetDisk      = _TargetDisk;
}

void MainWorkTab::StartInstall(void){
    Content->setText(tr("正在准备安装文件"));
    emit S_StartInstall(TargetPartition,TargetDisk);
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
    ProgressBar->setGeometry(27,17+40+50+15+30,600,40);
    Start->hide();
    ProgressBar->show();
}

void MainWorkTab::CopyDone(int Status){
    if(Status == true){
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
UserTab::UserTab(ProgressTabWidget *parent):
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
    Title->setGeometry(27,15,500,50);

    RootPassTitle->setFont(ContentFont);
    RootPassTitle->setText(tr("设置Root的密码"));
    RootPassTitle->setGeometry(27,50+15+50,100,25);

    RootPassEdit->setGeometry(27,50+15+50+25,300-27,25);

    RootPassTitle2->setFont(ContentFont);
    RootPassTitle2->setText(tr("再次输入密码"));
    RootPassTitle2->setGeometry(27,50+15+50+25+25,100,25);

    RootPassEdit2->setGeometry(27,50+15+50+25+25+25,300-27,25);


    UserNameTitle = new QLabel(this);
    UserNameEdit  = new QLineEdit(this);
    UserNameTitle->setFont(ContentFont);
    UserNameTitle->setText(tr("设置你主用户的用户名"));
    UserNameTitle->setGeometry(27+300,50+15+50,200,25);
    UserNameEdit->setGeometry(27+300,50+15+50+25,300-27,25);

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
    UserPassTitle->setGeometry(27+300,50+15+50+25+25,300-27,25);
    UserPassEdit->setGeometry(27+300,50+15+50+25+25+25,300-27,25);
    UserPassTitle2->setGeometry(27+300,50+15+50+25+25+25+25,300-27,25);
    UserPassEdit2->setGeometry(27+300,50+15+50+25+25+25+25+25,300-27,25);

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
    emit NextSetp();
}
//------------------------------------------------------------------
DoneTab::DoneTab(ProgressTabWidget *parent):
    ProgressTabWidget(parent){
    Title   = new QLabel(this);
    Title->setFont(TitleFont);
    Title->setText(tr("工作圆满完成 ;-)"));
    Title->setGeometry(27,17,500,50);

    Content = new QLabel(this);
    Content->setFont(ContentFont);
    Content->setText(tr("请手动重启计算机来启动新系统"));
    Content->setGeometry(27,17+50,500,25);

    SetPervButtonDisable();
    SetNextButtonText(tr("结束"));

}

