#include "installerpage.h"
#include "dialogbox.h"
#include <stdlib.h>
#include <parted/parted.h>
#include <stdio.h>
#include <QLabel>
#include <QTextBrowser>
#include <QFont>
#include <QFile>
#include <QPushButton>
#include <QDebug>

InstallerPage::InstallerPage(QWidget *parent):
    QWidget(parent){
    QFont cTitleFont;
    cTitleFont.setBold(true);
    cTitleFont.setPointSize(27);
    cTitle = new QLabel(this);
    cTitle->setFont(cTitleFont);
    cTitle->setGeometry(0,0,600,50);
    cContantFont.setBold(false);
    cContantFont.setPointSize(14);
}

InstallerPage::~InstallerPage(){

}

void InstallerPage::PervShow(){

}

int InstallerPage::SLOT_NextButtonClicked(void){
    return 0;
}

void InstallerPage::SLOT_PageChanged(QWidget *){

}

void InstallerPage::resizeEvent(QResizeEvent *){

}

void InstallerPage::SetContantTitle(const QString &str){
    cTitle->setText(str);
}

//----------------------------------//
//--------众神与愚民的分界线-----------//
//--------此刻正是昼夜交替时-----------//
//--------耀日将寝，皓月当空-----------//
//--------鬼哭狼嚎，铁骑千军-----------//
//----------------------------------//


WelcomePage::WelcomePage(InstallerPage *parent):
    InstallerPage(parent){
    Contant = new QLabel(this);
    this->SetContantTitle(tr("欢迎"));
    Contant->setText(tr("欢迎使用本AOSC系统半自动部署器\n您将在本部署器的指导下部署完成整个系统\n祝您使用愉快"));
    Contant->setGeometry(30,100,500,95);
    Contant->setFont(cContantFont);
}

WelcomePage::~WelcomePage(){
    delete Contant;
}

void WelcomePage::PervShow(){
    emit SIGN_SetPervButtonDisabled(true);
}

void WelcomePage::resizeEvent(QResizeEvent *){
}

int WelcomePage::SLOT_NextButtonClicked(void){
    return 0;
}






ReadingPage::ReadingPage(InstallerPage *parent):
    InstallerPage(parent){
    ReadingBrowser  = new QTextBrowser(this);
    isAgreed        = new QCheckBox(this);
    QFile file(":/Argeement/License");
    if(!file.open(QFile::ReadOnly | QFile::Text))
        qDebug() << "Can not open";
    QTextStream in(&file);
    ReadingBrowser->setHtml(in.readAll());
    isAgreed->setText(tr("I Agree"));
    this->connect(isAgreed,SIGNAL(clicked(bool)),this,SLOT(AgreementChanged(bool)));
}

ReadingPage::~ReadingPage(){

}

void ReadingPage::AgreementChanged(bool Status){
    if(Status == true){
        emit SIGN_SetNextButtonDisabled(false);
    }else{
        emit SIGN_SetNextButtonDisabled(true);
    }
}

void ReadingPage::PervShow(){
    if(isAgreed->isChecked() == false)
        emit SIGN_SetNextButtonDisabled(true);
}

void ReadingPage::resizeEvent(QResizeEvent *){
    ReadingBrowser->setGeometry(0,0,this->width(),this->height()-25);
    isAgreed->setGeometry(this->width()-90,this->height()-25,100,20);
}






PartedPage::PartedPage(InstallerPage *parent)
    :InstallerPage(parent){
    DeviceSelect = new MyTabWidget;
    ChangeButton = new QPushButton(this);
    AddButton    = new QPushButton(this);
    DelButton    = new QPushButton(this);
    List         = new PartitionList();
    AddDialog    = new AddDialogBox;
    ChangeDialog = new ChangeDialogBox;
    AddDialog->hide();
    ChangeDialog->hide();
    DeviceSelect->setGeometry(0,50,475,this->height()-180);
    DeviceSelect->insertTab(0,List,"Main");
    DeviceSelect->setDocumentMode(true);
    ChangeButton->setText("Change");
    AddButton->setText("+");
    DelButton->setText("-");
    AddButton->setGeometry(0,this->height()-120,20,20);
    ChangeButton->setGeometry(20,this->height()-120,55,20);
    DelButton->setGeometry(75,this->height()-120,20,20);
    SetContantTitle(tr("Parted!"));
    ped_device_probe_all();
    ChangeButton->setDisabled(true);
    AddButton->setDisabled(true);
    DelButton->setDisabled(true);
    this->connect(List,SIGNAL(SetAddButtonDisabled(bool)),this->AddButton,SLOT(setDisabled(bool)));
    this->connect(List,SIGNAL(SetChangeButtonDisabled(bool)),this->ChangeButton,SLOT(setDisabled(bool)));
    this->connect(List,SIGNAL(SetDelButtonDisabled(bool)),this->DelButton,SLOT(setDisabled(bool)));
    this->connect(AddButton,SIGNAL(clicked()),this,SLOT(ShowAddDialog()));
    this->connect(ChangeButton,SIGNAL(clicked()),this,SLOT(ShowChangeDialog()));
    this->connect(DelButton,SIGNAL(clicked()),this,SLOT(AskForDeletePartition()));
    this->connect(ChangeDialog,SIGNAL(MountPointChangeApplied(int)),this,SLOT(MountPointChangeApplied(int)));
    this->connect(ChangeDialog,SIGNAL(WorkDone()),this,SLOT(WorkDone()));
}

void PartedPage::ShowAddDialog(){
    ChangeDialog->SetCurrentPartition(List->GetCurrentSelectedPartition(),List->GetCurrentSelectedDisk(),List->GetCurrentSelectedDevice(),INSTALLER_MOUNT_POINT_NONE,INSTALLER_WORKTYPE_ADD);
    ChangeDialog->show();
}

void PartedPage::ShowChangeDialog(){
    ChangeDialog->SetCurrentPartition(List->GetCurrentSelectedPartition(),List->GetCurrentSelectedDisk(),List->GetCurrentSelectedDevice(),List->GetCurrentMountPoint(),INSTALLER_WORKTYPE_CHANGE);
    ChangeDialog->show();
}

void PartedPage::AskForDeletePartition(){
    if (QMessageBox::question(this,tr("Question"),tr("Do you want to delete this partition?"),QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
        DelPartition(List->GetCurrentSelectedPartition(),List->GetCurrentSelectedDisk());
        List->RefreshList();
    }
}

void PartedPage::DelPartition(PedPartition TargetPartition, PedDisk TargetDisk){
    PedDevice *dev = 0;
    while((dev = ped_device_get_next(dev))){
        PedDisk* disk = ped_disk_new(dev);
        PedPartition* part = 0;
        while((part = ped_disk_next_partition(disk, part))){
            //略过不是分区的空间
            if ((part->type & PED_PARTITION_METADATA) ||
                (part->type & PED_PARTITION_FREESPACE) ||
                (part->type & PED_PARTITION_EXTENDED))
                    continue;
            if(strcmp(ped_partition_get_path(part),ped_partition_get_path(&TargetPartition)) == 0){
                char Exec[64];
                bzero(Exec,64);
                sprintf(Exec,"parted %s rm %d",TargetDisk.dev->path,TargetPartition.num);
                system(Exec);
                ped_disk_commit(disk);
            }
        }
    }
}

PartedPage::~PartedPage(){

}

void PartedPage::PervShow(){
    //emit SIGN_SetNextButtonDisabled(true);
    List->RefreshList();
}

void PartedPage::MountPointChangeApplied(int MountPoint){
    List->SetCurrentMountPoint(MountPoint);
}

void PartedPage::WorkDone(){
    List->RefreshList();
    AddButton->setDisabled(true);
    DelButton->setDisabled(true);
    ChangeButton->setDisabled(true);
}

int PartedPage::SLOT_NextButtonClicked(){
    system("sudo umount -Rf /target");
    QString Path;
    char Exec[64];
    bzero(Exec,64);
    Path = List->GetMountPoint(INSTALLER_MOUNT_POINT_ROOT);
    if(Path.length() < 5){
        QMessageBox::warning(this,tr("警告"),tr("您没有选择root分区或选取分区无效，请选择挂载分区后重试"),QMessageBox::Yes);
        return -1;
    }
    sprintf(Exec,"mount %s /target",Path.toUtf8().data());
    if(system("Exec")!=0){
        if(QMessageBox::warning(this,tr("错误"),tr("root分区挂载失败，是否返回分区界面"),QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
            return -1;
        }
    }
    Path = List->GetMountPoint(INSTALLER_MOUNT_POINT_HOME);
    if(Path.length()>5){
        if(system("mkdir /target/home") != 0){
            QMessageBox::warning(this,tr("提示"),tr("无法创建%SYSTEMROOT%/home 目录，确认目标分区是否已经存在此同名文件"),QMessageBox::Yes);
        }
        bzero(Exec,64);
        sprintf(Exec,"mount %s /target/home",Path.toUtf8().data());
        if(system("Exec") != 0){
            QMessageBox::warning(this,tr("失败"),tr("挂载/home分区失败"),QMessageBox::Yes);
            return -1;
        }
    }
    Path = List->GetMountPoint(INSTALLER_MOUNT_POINT_BOOT);
    if(Path.length()>5){
        if(system("mkdir /target/boot") != 0){
            QMessageBox::warning(this,tr("提示"),tr("无法创建%SYSTEMROOT%/boot 目录，确认目标分区是否已经存在此同名文件"),QMessageBox::Yes);
            return 0;
        }
        bzero(Exec,64);
        sprintf(Exec,"mount %s /target/home",Path.toUtf8().data());
        if(system("Exec") != 0){
            QMessageBox::warning(this,tr("失败"),tr("挂载/home分区失败"),QMessageBox::Yes);
            return -1;
        }
    }
    return 0;
}
