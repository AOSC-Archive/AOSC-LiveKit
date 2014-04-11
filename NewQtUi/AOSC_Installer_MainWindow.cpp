#include "AOSC_Installer_MainWindow.h"
#include "ui_AOSC_Installer_MainWindow.h"
#include <QTabBar>

AOSC_Installer_MainWindow::AOSC_Installer_MainWindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::AOSC_Installer_MainWindow)
{
    BuildObject();
    AddToTabWidget();
/*    MountSquashfs = new QProcess(this);       // Mount Squashfs....
    this->connect(MountSquashfs,SIGNAL(finished(int)),this,SLOT(SLOT_MountSquashfsDone(int)));
    QStringList ArgList;
    ArgList << "mount" << _INSTALL_FILE_ << _INSTALL_FILE_FROM_ ;
    MountSquashfs->start("sudo",ArgList);*/
//##########链接基本的信号与槽#############
    this->connect(ui->NextStepButton,SIGNAL(clicked()),this,SLOT(SLOT_NextButtonClicked()));
    this->connect(ui->PervStepButton,SIGNAL(clicked()),this,SLOT(SLOT_PervButtonClicked()));
    this->connect(Reading,SIGNAL(SIGNAL_IAgreeCheckBoxClicked(bool)),this,SLOT(SLOT_IAgreeCheckBoxClicked(bool)));
    this->connect(PartedDisk,SIGNAL(SIG_AskForHide()),this,SLOT(hide()));
    this->connect(PartedDisk,SIGNAL(SIG_AskForShow()),this,SLOT(show()));
    this->connect(WorkProcess,SIGNAL(SIG_StartButtonClicked()),this,SLOT(SLOT_StartInstall()));
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
    system("sudo umount -Rf /target");
    system("sudo umount -Rf /mnt/squash/");
    printf("析构函数被调用\n");
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

void AOSC_Installer_MainWindow::SLOT_MountSquashfsDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,tr("错误！"),tr("安装程序遇到致命错误，强制退出"),QMessageBox::Yes);
        delete this;
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
        QMessageBox::warning(this,tr("严重错误"),tr("挂载目标分区失败，请确认目标分区是否在使用中！"),QMessageBox::Yes);
        exit(0);
    }else{
        if(system("sudo mount --bind /dev /target/dev")!=0){
            QMessageBox::warning(this,tr("严重错误"),tr("挂载dev列表到目标安装位置失败"),QMessageBox::Yes);
            delete this;
        }
        if(system("sudo mount --bind /proc /target/proc")!=0){
            QMessageBox::warning(this,tr("严重错误"),tr("挂载proc到目标安装位置失败"),QMessageBox::Yes);
            delete this;
        }
        if(system("sudo mount --bind /sys /target/sys")!=0){
            QMessageBox::warning(this,tr("严重错误"),tr("挂载sys到目标安装位置失败"),QMessageBox::Yes);
            delete this;
        }
        if(system("sudo mount --bind /dev/pts /target/dev/pts")!=0){
            QMessageBox::warning(this,tr("严重错误"),tr("挂载sys到目标安装位置失败"),QMessageBox::Yes);
            delete this;
        }
        StatisticsFiles = new StatisticsFileSize();
        this->connect(StatisticsFiles,SIGNAL(TotalFile(int)),this,SLOT(SLOT_TotalFiles(int)));
        this->connect(StatisticsFiles,SIGNAL(Copyed(int)),this,SLOT(SLOT_NowCopyed(int)));
        StatisticsFiles->start();
        WorkProcess->SetProcessBarShow(true);
        WorkProcess->SetLabelText(tr("准备安装中"));
    }
}

void AOSC_Installer_MainWindow::SLOT_TotalFiles(int TotalFile){
    WorkProcess->SetTotalFiles(TotalFile);
    AllFiles = TotalFile;
    WorkProcess->SetLabelText(tr("安装基础系统中....."));
    CopyFile = new QProcess(this);
    this->connect(CopyFile,SIGNAL(finished(int)),this,SLOT(SLOT_CopyFileDone(int)));
    QStringList ArgList;
    ArgList << "cp" << _INSTALL_FILE_DEST_ << PartedDisk->GetTargetPartition();
}

void AOSC_Installer_MainWindow::SLOT_NowCopyed(int NowCopyed){
    WorkProcess->SetNowCopyed(NowCopyed);
}

void AOSC_Installer_MainWindow::SLOT_CopyFileDone(int Status){
    if(Status != 0){
        StatisticsFiles->CopyDone();
        QMessageBox::warning(this,tr("错误"),tr("复制文件出现错误！"),QMessageBox::Yes);
        delete this;
    }else{
        WorkProcess->SetLabelText(tr("设置Grub"));
        //........
        QMessageBox::warning(this,tr("嗯"),tr("这里就先停下了，因为后面还没写"));
    }
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
    sprintf(ExecBuff,"sudo find %s | wc -l > %s",_INSTALL_FILE_FROM_,_TMP_TOTAL_SIZE_);
    fp = fopen(_TMP_TOTAL_SIZE_,"r");
    fscanf(fp,"%d",&NowSize);
    emit TotalFile(NowSize);
    fclose(fp);

    sprintf(ExecBuff,"sudo find %s | wc -l > %s",_INSTALL_FILE_DEST_,_TMP_TOTAL_SIZE_);
    system(ExecBuff);
    fp = fopen(_TMP_TOTAL_SIZE_,"r");
    while(1){
        sleep(2);
        fscanf(fp,"%d",&NowSize);
        emit Copyed(NowSize);
        printf("Debug >> Now Copyed Files Size ==  %d\n",NowSize);
        fclose(fp);     //!
        fp = NULL;
        system(ExecBuff);
        fp = fopen(_TMP_TOTAL_SIZE_,"r");       //!
    }
}

void StatisticsFileSize::CopyDone(){
    this->terminate();
    if(fp != NULL){
        fclose(fp);
        fp = NULL;
    }
    sprintf(ExecBuff,"sudo rm -rf %s",_TMP_TOTAL_SIZE_);
    system(ExecBuff);
    this->terminate();
}
