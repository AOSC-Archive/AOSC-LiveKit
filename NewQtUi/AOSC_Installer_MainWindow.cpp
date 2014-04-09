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
    this->connect(PartedDisk,SIGNAL(SIG_AskForHide()),this,SLOT(hide()));
    this->connect(PartedDisk,SIGNAL(SIG_AskForShow()),this,SLOT(show()));
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
/*    else if(MainTab->currentWidget()==WorkProcess){       // 当发布时这里的注释去掉
        ui->NextStepButton->setDisabled(true);
        ui->PervStepButton->setDisabled(true);
    }*/
    else if(MainTab->currentWidget()==ConfigureUser)ui->PervStepButton->setDisabled(true);
    else if(MainTab->currentWidget()==WorkDone)ui->NextStepButton->setText(tr("完成安装"));
}

void AOSC_Installer_MainWindow::SLOT_NextButtonClicked(){
    if(MainTab->currentWidget()==PartedDisk){                   //  如果是分区相关，则判断
        int result = PartedDisk->CheckInput();
            if(result == -1){
                QMessageBox::warning(this,tr("警告"),tr("严重错误！"),QMessageBox::Yes);
            }else if(result == NO_DISK_SELECT){
                QMessageBox::warning(this,tr("警告"),tr("请选择安装的硬盘"),QMessageBox::Yes);
            }else if(result == NO_EFI_PARTITION_SELECT){
                QMessageBox::warning(this,tr("警告"),tr("请选择你的EFI分区"),QMessageBox::Yes);
            }else if(result == NO_PARTITION_SELECT){
                QMessageBox::warning(this,tr("警告"),tr("请选择安装的分区"),QMessageBox::Yes);
            }else if(result == NO_FILESYSTEM_TYPE_SELECT){
                QMessageBox::warning(this,tr("警告"),tr("请选择格式化分区的文件系统"),QMessageBox::Yes);
            }else if(result == NO_FORMAT){
                if(QMessageBox::warning(this,tr("警告"),tr("您确定不格式化就安装系统，这可能会导致安装失败"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::No){
                    return;
                }result = 0;
            }
            if(result != 0)
                return;
        }
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

void AOSC_Installer_MainWindow::SLOT_MyDeviceIsEFI(QString Partition, bool Status){

}

void AOSC_Installer_MainWindow::SLOT_INeedFormatMyPartiton(QString Partition, int Type, bool Status){

}
