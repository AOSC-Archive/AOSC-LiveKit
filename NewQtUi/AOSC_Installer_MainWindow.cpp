#include "AOSC_Installer_MainWindow.h"
#include "ui_AOSC_Installer_MainWindow.h"
#include <QTabBar>
#include <QTabWidget>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

MyTabWidget::MyTabWidget(QTabWidget *parent):
    QTabWidget(parent){
    this->tabBar()->hide();
}

AOSC_Installer_MainWindow::AOSC_Installer_MainWindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::AOSC_Installer_MainWindow)
{
    BuildObject();
    AddToTabWidget();
    system("sudo umount -Rf /target");
//##########链接基本的信号与槽#############
    this->connect(ui->NextStepButton,SIGNAL(clicked()),this,SLOT(SLOT_NextButtonClicked()));
    this->connect(ui->PervStepButton,SIGNAL(clicked()),this,SLOT(SLOT_PervButtonClicked()));
    this->connect(Reading,SIGNAL(SIGNAL_IAgreeCheckBoxClicked(bool)),this,SLOT(SLOT_IAgreeCheckBoxClicked(bool)));
    this->connect(PartedDisk,SIGNAL(SIG_AskForHide()),this,SLOT(hide()));
    this->connect(PartedDisk,SIGNAL(SIG_AskForShow()),this,SLOT(show()));
    this->connect(WorkProcess,SIGNAL(SIG_StartButtonClicked()),this,SLOT(SLOT_StartInstall()));
    this->connect(WorkProcess,SIGNAL(SIG_StartButtonClicked_WithFormat()),this,SLOT(SLOT_StartInstall_WithFormat()));
    ui->PervStepButton->hide();
    MainTab->setDocumentMode(true);
}

void AOSC_Installer_MainWindow::BuildObject(){
    ui->setupUi(this);                      //  初始化基本UI
    MainTab     = new MyTabWidget;          //  总Tab
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

void AOSC_Installer_MainWindow::closeEvent(QCloseEvent *){
    delete this;
}

void AOSC_Installer_MainWindow::AddToTabWidget(){
    MainTab->addTab(GetStart,tr("Prepare for Installation"));//   准备开始吧
    MainTab->addTab(Reading,tr("License Agreement"));
    MainTab->addTab(PartedDisk,tr("Partitioning"));
    MainTab->addTab(WorkProcess,tr("Building System"));
    MainTab->addTab(ConfigureUser,tr("Set-up User"));
    MainTab->addTab(WorkDone,tr("Finalizing"));
}

AOSC_Installer_MainWindow::~AOSC_Installer_MainWindow()
{
    delete ui;
    system("sudo umount -Rf /target");
    printf("Destructor called.\n");
    exit(0);
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
    else if(MainTab->currentWidget()==WorkProcess){
        ui->NextStepButton->setDisabled(true);
        ui->PervStepButton->setDisabled(true);
        WorkProcess->SLOT_StartButtonClicked();
    }
    else if(MainTab->currentWidget()==ConfigureUser)ui->PervStepButton->setDisabled(true);
    else if(MainTab->currentWidget()==WorkDone){
        ui->NextStepButton->hide();
        ui->PervStepButton->setDisabled(true);
    }
}

void AOSC_Installer_MainWindow::SLOT_NextButtonClicked(){
    int result;
    if(MainTab->currentWidget()==PartedDisk){                   //  如果是分区相关，则判断
        result = PartedDisk->CheckInput();
        if(result == -1){
            QMessageBox::warning(this,tr("Warning"),tr("Critial Error!"),QMessageBox::Yes);
        }else if(result == NO_DISK_SELECT){
            QMessageBox::warning(this,tr("Warning"),tr("Please select your target Disk before proceeding."),QMessageBox::Yes);
        }else if(result == NO_EFI_PARTITION_SELECT){
            QMessageBox::warning(this,tr("Warning"),tr("Please select your EFI System Partition befor proceeding."),QMessageBox::Yes);
        }else if(result == NO_PARTITION_SELECT){
            QMessageBox::warning(this,tr("Warning"),tr("Please select your target partition before proceeding."),QMessageBox::Yes);
        }else if(result == NO_FILESYSTEM_TYPE_SELECT){
            QMessageBox::warning(this,tr("Warning"),tr("Please select File System to format the parition!"),QMessageBox::Yes);
        }else if(result == NO_FORMAT){
            if(QMessageBox::warning(this,tr("Warning"),tr("Are you sure that you want to start the installation without formatting? This can lead to serious problem afterwards..."),QMessageBox::Yes|QMessageBox::No)==QMessageBox::No){
                return;
           }result = 0;
        }
        if(result != 0)
            return;
        if(PartedDisk->isFormat() == true){
            WorkProcess->SetIsFormat(true);
        }
    }else if(MainTab->currentWidget()==ConfigureUser){
        result = ConfigureUser->CheckInput();
        if(result == NO_ROOT_PASS){
            QMessageBox::warning(this,tr("Warning"),tr("Please input a new password for root."),QMessageBox::Yes);
        }else if(result == NO_USER_NAME){
            QMessageBox::warning(this,tr("Warning"),tr("Please input a username for the base user."),QMessageBox::Yes);
        }else if(result == NO_USER_PASS){
            QMessageBox::warning(this,tr("Warning"),tr("Please input a new password for the base user."),QMessageBox::Yes);
        }else if(result == ROOT_PASS_NOT_MATCH){
            QMessageBox::warning(this,tr("Warning"),tr("Root password does not match, please double check."),QMessageBox::Yes);
        }else if(result == USER_PASS_NOT_MATCH){
            QMessageBox::warning(this,tr("Warning"),tr("Base user password does not match, please double check."),QMessageBox::Yes);
        }else if(result == USER_NAME_HAS_SPACE){
            QMessageBox::warning(this,tr("Warning"),tr("Space is not allowed in username! Please double check and try again."),QMessageBox::Yes);
        }
        if(result != 0) return;
        SetUserName = new QProcess(this);
        this->connect(SetUserName,SIGNAL(finished(int)),this,SLOT(SLOT_SetUserNameDone(int)));
        SetUserName->start("sudo",QStringList()<<"chroot"<<"/target" << "usermod" << "-l" << ConfigureUser->GetUserName() << "live");
    }
    MainTab->setCurrentIndex(MainTab->currentIndex()+1);        //  跳转到下一步
    SetAllButtonEnable();                                       //  将按钮全部激活
    CheckButtonDisable();                                       //  检查同时disable某些按钮
    if(MainTab->currentWidget()==WorkDone){
        SLOT_DoPostInstDone(0);
    }
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

void AOSC_Installer_MainWindow::SLOT_MountSquashfsDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,tr("Error"),tr("Installation has encountered a critical error and must exit now."),QMessageBox::Yes);
        delete this;
        exit(-1);
    }
}

void AOSC_Installer_MainWindow::SLOT_StartInstall_WithFormat(){
    Format = new QProcess(this);
    connect(Format,SIGNAL(finished(int)),this,SLOT(SLOT_FormatDone(int)));
    char ch[64];
    WorkProcess->SetLabelText("Formatting target partition...");
    sprintf(ch,"mkfs.%s",PartedDisk->GetFormatFileSystem().toUtf8().data());
    Format->start("sudo",QStringList()<<ch<<PartedDisk->GetTargetPartition().toUtf8().data());
}

void AOSC_Installer_MainWindow::SLOT_FormatDone(int Status){
    if(Status != 0){
        printf("Status = %d\n",Status);
        QMessageBox::warning(this,tr("Error"),tr("Format your disk partition failure."),QMessageBox::Yes);
        delete this;
        exit(-1);
    }else{
        SLOT_StartInstall();
    }
}

void AOSC_Installer_MainWindow::SLOT_StartInstall(){
    MountTarget = new QProcess(this);
    this->connect(MountTarget,SIGNAL(finished(int)),this,SLOT(SLOT_MountTargetDone(int)));

    QStringList List;
    List << "mount" << PartedDisk->GetTargetPartition() << _INSTALL_FILE_DEST_;
    //debug
    printf("Install To %s\n",PartedDisk->GetTargetPartition().toUtf8().data());
    MountTarget->start("sudo",List);
}

void AOSC_Installer_MainWindow::SLOT_MountTargetDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,tr("Critical Error"),tr("Failed to mount target partition! Please check if it is corrupted or already mounted."),QMessageBox::Yes);
        exit(0);
    }else{
        StatisticsFiles = new StatisticsFileSize();
        this->connect(StatisticsFiles,SIGNAL(TotalFile(int)),this,SLOT(SLOT_TotalFiles(int)));
        this->connect(StatisticsFiles,SIGNAL(Copyed(int)),this,SLOT(SLOT_NowCopyed(int)));
        StatisticsFiles->start();
        WorkProcess->SetProcessBarShow(true);
        WorkProcess->SetLabelText(tr("Preparing for Installation..."));
    }
}

void AOSC_Installer_MainWindow::SLOT_TotalFiles(int TotalFile){
    WorkProcess->SetTotalFiles(TotalFile);
    AllFiles = TotalFile;
    WorkProcess->SetLabelText(tr("Copying system files..."));
    CopyFile = new QProcess(this);
    this->connect(CopyFile,SIGNAL(finished(int)),this,SLOT(SLOT_CopyFileDone(int)));
    this->connect(CopyFile,SIGNAL(finished(int)),StatisticsFiles,SLOT(CopyDone()));
    this->connect(CopyFile,SIGNAL(finished(int)),WorkProcess,SLOT(SLOT_CopyDone(int)));
    QStringList ArgList;
    ArgList << "cp" << "-arv" << "/lib/live/mount/rootfs/live.squashfs/." << _INSTALL_FILE_DEST_;
//    ArgList << "cp" << "-arv" << "/squash" << _INSTALL_FILE_DEST_;
    CopyFile->setStandardOutputFile(_TMP_TOTAL_SIZE_);
    CopyFile->start("sudo",ArgList);
    emit SIG_StartCopyFile();
}
void AOSC_Installer_MainWindow::SLOT_NowCopyed(int NowCopyed){
    WorkProcess->SetNowCopyed(NowCopyed);
}

void AOSC_Installer_MainWindow::SLOT_CopyFileDone(int Status){
        if(system("sudo mount --bind /dev /target/dev")!=0){
            QMessageBox::warning(this,tr("Critical Error"),tr("Mounting dev to target failed."),QMessageBox::Yes);
            delete this;
        }
        if(system("sudo mount --bind /proc /target/proc")!=0){
            QMessageBox::warning(this,tr("Critical Error"),tr("Mounting proc to target failed."),QMessageBox::Yes);
            delete this;
        }
        if(system("sudo mount --bind /sys /target/sys")!=0){
            QMessageBox::warning(this,tr("Critical Error"),tr("Mounting sys to target failed."),QMessageBox::Yes);
            delete this;
        }
        if(system("sudo mount --bind /dev/pts /target/dev/pts")!=0){
            QMessageBox::warning(this,tr("Critical Error"),tr("Mounting pts to target failed."),QMessageBox::Yes);
            delete this;
        }
    /*if(Status != 0){
        StatisticsFiles->CopyDone();
        printf("Status = %d\n",Status);
        QMessageBox::warning(this,tr("Error"),tr("Error occurred while copying files! Sad."),QMessageBox::Yes);
        delete this;
    }else{*/
        StatisticsFiles->CopyDone();
        WorkProcess->SetLabelText(tr("Installing and configuring GRUB..."));
        SetGrub = new QProcess(this);
        UpDateGrub = new QProcess(this);
        this->connect(SetGrub,SIGNAL(finished(int)),this,SLOT(SLOT_SetGrubDone(int)));
        SetGrub->setStandardErrorFile("./GRUB_StdErrorFile");
        if(PartedDisk->isEFIDevice() == false){
           SetGrub->start("sudo",QStringList() << "chroot" << _INSTALL_FILE_DEST_ << "grub-install" << "--target=i386-pc" << PartedDisk->GetTargetDisk());
           //SetGrub->start("sudo",QStringList() << "grub-install" << "--target=i386-pc" << PartedDisk->GetTargetDisk());
        }
        else{
            char ExecBuff[128];
            if(access("/target/efi",F_OK) < 0){
                if(system("sudo mkdir /target/efi") != 0){
                    QMessageBox::warning(this,tr("Critical Error"),tr("Failed while trying to create directory for ESP to mount."));
                    delete this;
                    exit(0);
                }
            }
            sprintf(ExecBuff,"sudo mount %s /target/efi",PartedDisk->GetEFIPartition().toUtf8().data());
            if(system(ExecBuff) != 0){
                QMessageBox::warning(this,tr("Critical Error"),tr("Failed mounting ESP"));
                delete this;
                exit(0);
            }
            if(PartedDisk->WhetherSetGrub() == false){
                   SLOT_UpdateGrubDone(0);
                   return;
            }
            SetGrub->start("sudo",QStringList() << "chroot" << _INSTALL_FILE_DEST_ << "grub-install" << "--target=x86_64-efi" << "--efi-directory=/efi" << "--bootloader-id=AOSC-GRUB" << "--recheck");

        }
//    }
}

void AOSC_Installer_MainWindow::SLOT_SetGrubDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,tr("Critical Error"),tr("Failed installing GRUB!"));
        delete this;
        exit(-1);
    }else{ 
        UpDateGrub = new QProcess(this);
        this->connect(UpDateGrub,SIGNAL(finished(int)),this,SLOT(SLOT_UpdateGrubDone(int)));
        WorkProcess->SetLabelText(tr("Updating GRUB..."));
        UpDateGrub->start("sudo",QStringList()<<"chroot"<<_INSTALL_FILE_DEST_<<"grub-mkconfig"<<"-o"<<"/boot/grub/grub.cfg");
    }
}

void AOSC_Installer_MainWindow::SLOT_UpdateGrubDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,tr("Critical Error"),tr("Failed when updating GRUB configuration, your system may not be able to boot."),QMessageBox::Yes);
        delete this;
        exit(-1);
    }else{
        ui->NextStepButton->setEnabled(true);
        WorkProcess->SetLabelText(tr("Successfully installed system."));
        WorkProcess->SetProcessBarShow(false);
    }
}

void AOSC_Installer_MainWindow::SLOT_SetUserNameDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,tr("Critical Error"),tr("Failed setting up user."));
        delete this;
        exit(-1);
    }else{
        SetUserPass = new QProcess(this);
        this->connect(SetUserPass,SIGNAL(finished(int)),this,SLOT(SLOT_SetUserPassDone(int)));
        SetUserPass->start("sudo",QStringList()<<"chroot"<<"/target"<<"/usr/bin/cpw.sh"<<ConfigureUser->GetUserName()<<ConfigureUser->GetUserPass());
    }
}

void AOSC_Installer_MainWindow::SLOT_SetUserPassDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,tr("Critical Error"),tr("Setting password for user failed."));
        delete this;
        exit(-1);
    }else{
        SetRootPass = new QProcess(this);
        this->connect(SetRootPass,SIGNAL(finished(int)),this,SLOT(SLOT_SetRootPassDone(int)));
        SetRootPass->start("sudo",QStringList()<<"chroot"<<"/target"<<"/usr/bin/cpw.sh"<<"root"<<ConfigureUser->GetRootPass());
    }
}

void AOSC_Installer_MainWindow::SLOT_SetRootPassDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,tr("Critical Error"),tr("Setting password for root failed."));
        delete this;
        exit(-1);
    }else{
	system("genfstab -p /target | sudo tee /target/etc/fstab");
    }
}

void AOSC_Installer_MainWindow::SLOT_DoPostInstDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,tr("Critical Error"),tr("Finalization error occurred."));
        delete this;
        exit(-1);
    }else{
        int result = QMessageBox::question(this,tr("Question"),tr("Do you want to use AnthonUI - Desktop Environment customization from AOSC"),QMessageBox::Yes|QMessageBox::No);
        if(result == QMessageBox::No){
            system("sudo chroot /target rm -rf /home/*/.kde");
            system("sudo chroot /target dpkg -r anthonui-kde");
        }
        system("sudo chroot /target dpkg -r aosc-installer");
        QMessageBox::question(this,tr("Installation Complete"),tr("Please enjoy yourself in this distribution, if you got questions or troubles, DO NOT hesitate to report or ask for help."),QMessageBox::Yes);
        delete this;
        exit(0);
    }
}

void AOSC_Installer_MainWindow::SLOT_PrintStdOutput(){
    if(SetGrub->isReadable() == true)
        printf("%s\n",SetGrub->readAll().data());
    if(UpDateGrub->isReadable() == true)
        printf("%s\n",SetGrub->readAll().data());
}

//----------------------

StatisticsFileSize::StatisticsFileSize(QThread *parent):
    QThread(parent){

}

void StatisticsFileSize::GetReady(int _Size){
    Size = _Size;
    this->start();
}

void StatisticsFileSize::run(){
    sprintf(ExecBuff,"find /lib/live/mount/rootfs/live.squashfs | wc -l > %s",_TMP_NOW_SIZE);
//    sprintf(ExecBuff,"find /squash | wc -l > %s",_TMP_NOW_SIZE);
    system(ExecBuff);
    printf("Execed!\n");
    fp = fopen(_TMP_NOW_SIZE,"r");
    fscanf(fp,"%d",&AllSize);
    emit TotalFile(AllSize);
    fclose(fp);
    fp = NULL;
    printf("Fclosed!\n");
    sprintf(ExecBuff,"cat %s | wc -l > %s",_TMP_TOTAL_SIZE_,_TMP_NOW_SIZE);
    while(1){
        sleep(1);
        system(ExecBuff);
        fp = fopen(_TMP_NOW_SIZE,"r");       //!
        fscanf(fp,"%d",&NowSize);
        emit Copyed(NowSize);
        printf("Debug >> Now Copyed Files Count ==  %d\n",NowSize);
        fclose(fp);     //!
        fp = NULL;
    }
}

void StatisticsFileSize::CopyDone(){
    this->terminate();
    if(fp != NULL){
        fclose(fp);
        fp = NULL;
    }
/*  sprintf(ExecBuff,"sudo rm -rf %s",_TMP_NOW_SIZE);
    system(ExecBuff);
    this->terminate(); */
}

