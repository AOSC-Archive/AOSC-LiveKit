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
}

AOSC_Installer_MainWindow::~AOSC_Installer_MainWindow()
{
    delete ui;
}

void AOSC_Installer_MainWindow::CheckButtonDisable(){
    if(MainTab->currentWidget() == Reading) ui->NextStepButton->setDisabled(true);
}

void AOSC_Installer_MainWindow::SLOT_NextButtonClicked(){
    MainTab->setCurrentIndex(MainTab->currentIndex()+1);
    CheckButtonDisable();
}

void AOSC_Installer_MainWindow::SLOT_PervButtonClicked(){
    MainTab->setCurrentIndex(MainTab->currentIndex()-1);
    CheckButtonDisable();
}

void AOSC_Installer_MainWindow::SLOT_IAgreeCheckBoxClicked(bool status){
    if(status == true)  ui->NextStepButton->setEnabled(true);
    else                ui->NextStepButton->setDisabled(true);
}
