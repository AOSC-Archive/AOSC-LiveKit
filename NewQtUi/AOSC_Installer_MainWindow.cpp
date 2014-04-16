#include "AOSC_Installer_MainWindow.h"
#include "ui_AOSC_Installer_MainWindow.h"
#include <QTabBar>

AOSC_Installer_MainWindow::AOSC_Installer_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AOSC_Installer_MainWindow)
{
    BuildObject();
    AddToTabWidget();
//##########链接基本的信号与槽#############3
    this->connect(ui->NextStepButton,SIGNAL(clicked()),this,SLOT(SLOT_NextButtonClicked()));
    this->connect(ui->PervStepButton,SIGNAL(clicked()),this,SLOT(SLOT_PervButtonClicked()));
    this->connect(Reading,SIGNAL(SIGNAL_IAgreeCheckBoxClicked(bool)),this,SLOT(SLOT_IAgreeCheckBoxClicked(bool)));

    ui->PervStepButton->hide();
    MainTab->tabBar()->setHidden(true);     //  Qt5大法好！
}

void AOSC_Installer_MainWindow::BuildObject(){
    ui->setupUi(this);                      //  初始化基本UI
    MainTab     = new QTabWidget;           //  总Tab
    GetStart    = new GetStartTab;          //  开始分页
    Reading     = new ReadingTab;           //  阅读协议分页
    PartedDisk  = new PartedDiskTab;        //  分区分页
    WorkProcess = new WorkProcessTab;       //  总安装过程分页
    ConfigureUser=new ConfigureUserTab;     //  配置用户分页
    WorkDone    = new WorkDoneTab;          //  完成安装分页
    layout = new QHBoxLayout;               //  设置Layout

    layout->addWidget(MainTab);             //  添加到UI中
    ui->CenterProcess->setLayout(layout);   //  装载Layout
}

void AOSC_Installer_MainWindow::AddToTabWidget(){
    MainTab->addTab(GetStart,tr("准备开始"));//   准备开始吧
    MainTab->addTab(Reading,tr("阅读协议"));
    MainTab->addTab(PartedDisk,tr("分区磁盘"));
    MainTab->addTab(WorkProcess,tr("构建系统"));
    MainTab->addTab(ConfigureUser,tr("配置用户"));
    MainTab->addTab(WorkDone,tr("安装完成"));
}

AOSC_Installer_MainWindow::~AOSC_Installer_MainWindow()
{
    delete ui;
}

void AOSC_Installer_MainWindow::SetAllButtonEnable(){
    ui->NextStepButton->setEnabled(true);
    ui->NextStepButton->show();
    ui->PervStepButton->setEnabled(true);
    ui->PervStepButton->show();
}

void AOSC_Installer_MainWindow::CheckButtonDisable(){
    if(MainTab->currentWidget() == Reading){
        if(Reading->is_IAgreeCheckBox_Status() == false)
            ui->NextStepButton->setDisabled(true);
    }
    else if(MainTab->currentWidget()==GetStart)ui->PervStepButton->hide();
/*    else if(MainTab->currentWidget()==WorkProcess){
        ui->NextStepButton->setDisabled(true);
        ui->PervStepButton->setDisabled(true);
    }*/
    else if(MainTab->currentWidget()==ConfigureUser)ui->PervStepButton->setDisabled(true);
    else if(MainTab->currentWidget()==WorkDone)ui->NextStepButton->setText(tr("完成安装"));
}

void AOSC_Installer_MainWindow::SLOT_NextButtonClicked(){
    MainTab->setCurrentIndex(MainTab->currentIndex()+1);        //  跳转到下一步
    SetAllButtonEnable();                                       //  将按钮全部激活
    CheckButtonDisable();                                       //  检查同时disable某些按钮
}

void AOSC_Installer_MainWindow::SLOT_PervButtonClicked(){
    MainTab->setCurrentIndex(MainTab->currentIndex()-1);        //  跳转到上一步
    SetAllButtonEnable();                                       //  同上
    CheckButtonDisable();                                       //  同上
}

void AOSC_Installer_MainWindow::SLOT_IAgreeCheckBoxClicked(bool status){   //  配置Reading发回的那个同意协议的按钮的状态
    if(status == true)  ui->NextStepButton->setEnabled(true);
    else                ui->NextStepButton->setDisabled(true);
}
