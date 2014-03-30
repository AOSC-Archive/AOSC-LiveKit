#include "AOSC_Installer_MainWindow.h"
#include "ui_AOSC_Installer_MainWindow.h"
#include <QHBoxLayout>
#include <QTabBar>

AOSC_Installer_MainWindow::AOSC_Installer_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AOSC_Installer_MainWindow)
{
    ui->setupUi(this);                      //  初始化基本UI
    MainTab = new QTabWidget;               //  总Tab
    GetStart= new GetStartTab;
    Reading = new ReadingTab;
    MainTab->tabBar()->setHidden(true);     //  Qt5大法好！
    QHBoxLayout *layout = new QHBoxLayout;  //  设置Layout
    layout->addWidget(MainTab);             //  添加到UI中
    MainTab->addTab(GetStart,tr("准备开始"));//   准备开始吧
    MainTab->addTab(Reading,tr("阅读协议"));
    ui->CenterProcess->setLayout(layout);   //  装载Layout
    this->connect(ui->NextStepButton,SIGNAL(clicked()),this,SLOT(SLOT_NextButtonClicked()));
    this->connect(ui->PervStepButton,SIGNAL(clicked()),this,SLOT(SLOT_PervButtonClicked()));
    this->connect(Reading,SIGNAL(SIGNAL_IAgreeCheckBoxClicked(bool)),this,SLOT(SLOT_IAgreeCheckBoxClicked(bool)));

    ui->PervStepButton->hide();
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
    if(MainTab->currentWidget() == Reading) ui->NextStepButton->setDisabled(true);
    else if(MainTab->currentWidget()==GetStart)ui->PervStepButton->hide();
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
