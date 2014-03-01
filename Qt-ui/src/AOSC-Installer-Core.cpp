#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QByteArray>
#include "AOSC-Installer-Core.h"

AOSC_Installer_Core::AOSC_Installer_Core(QThread *parent):
    QThread(parent){
    isEfi = 0;
}

void AOSC_Installer_Core::run(){
    int status = 0;
    status = MountFS();
    if(status == 0)
        status = CopyFileToNewSystem();
    if(status == 0)
        status = SetGrub();
    if (status == 0)
        status = UpdateGrub();
    if(status == 0)
        UpdateFstab();
}

int AOSC_Installer_Core::CheckEnvironment(void){
    int result = access(_INSTALL_FILE_,0);
    if(result != F_OK){
        perror("Loading Install File ");
        return -1;
    }
    return _EN_LIVE_CD_;
}

bool AOSC_Installer_Core::CopyFileToNewSystem(void){
    NowCopy = 0;
    ThisTime = 0;
    char ExecBuff[128];
    sprintf(ExecBuff,"sudo du -s /mnt/squash > %s",_TMP_TOTAL_SIZE_);
    system(ExecBuff);
    FILE *f = fopen(_TMP_TOTAL_SIZE_,"r");
    int Total;
    int TargetSize;
    fscanf(f,"%d",&Total);
    sprintf(ExecBuff,"sudo rm -rf %s",_TMP_TOTAL_SIZE_);
    system(ExecBuff);
    sprintf(ExecBuff,"sudo du -s /target > %s",_TMP_TARGET_SIZE_);
    fclose(f);
    fopen(_TMP_TARGET_SIZE_,"r");
    fscanf(f,"%d",&TargetSize);
    emit TotalFile(Total);
    emit SFSizeStart(TargetSize);
    sprintf(ExecBuff,"sudo cp -arv %s %s",_INSTALL_FILE_FROM_,_INSTALL_FILE_DEST_);
    int status = system(ExecBuff);
    emit CopyDone(status);
    emit SFSizeStop();
    return status;
}

//#################Main Step#####################
int AOSC_Installer_Core::MountFS(){
    int status;
    char ExecBuff[128];
    sprintf(ExecBuff,"sudo mount %s /target",TargetPartition);
    status = system(ExecBuff);
    emit MountFSDone(status);
    return status;
}

int AOSC_Installer_Core::SetGrub(){
    int status;
    char ExecBuff[128];
    system("sudo mount --bind /dev /target/dev");
    system("sudo mount --bind /proc /target/proc");
    system("sudo mount --bind /sys /target/sys");
    system("sudo mount --bind /dev/pts /target/dev/pts");
    if(isEfi == 0){
#ifdef _AOSC_LIVE_CD_
        sprintf(ExecBuff,"sudo chroot /target grub-install --target=i386-pc %s",TargetDisk);
#else
        sprintf(ExecBuff,"sudo grub-install %s",TargetDisk);
#endif
        status = system(ExecBuff);
        emit SetGrubDone(status);
        return status;
    }else{
        if(access("/target/efi",F_OK) < 0){
            if(system("sudo mkdir /target/efi") != 0){
                emit SetGrubDone(-1);
                return -1;
            }
        }
        sprintf(ExecBuff,"sudo mount %s /target/efi",TargetEfiPartiton);
        if(system(ExecBuff) != 0){
            emit SetGrubDone(-1);
            return -1;
        }
        if(system("sudo chroot /target grub-install --target=x86_64-efi --efi-directory=/efi --bootloader-id=AOSC-GRUB --recheck") != 0){
            emit SetGrubDone(-1);
            return -1;
        }
        emit SetGrubDone(0);
        return 0;
    }
    return 0;
}

int AOSC_Installer_Core::UpdateGrub(){
    int status;
    char ExecBuff[128];
#ifdef _AOSC_LIVE_CD_
    sprintf(ExecBuff,"sudo chroot /target grub-mkconfig -o /boot/grub/grub.cfg");
#else
    sprintf(ExecBuff,"grub-mkconfig -o /boot/grub/grub.cfg");
#endif
    status = system(ExecBuff);
    emit UpdateGrubDone(status);
    return status;
}

int AOSC_Installer_Core::UpdateFstab(void){
    int status;
#ifdef _AOSC_LIVE_CD_
    char ExecBuff[128];
    sprintf(ExecBuff,"echo %s / ext4 defaults 1 1 | sudo tee -a /target/etc/fstab",TargetPartition);
    status = system(ExecBuff);
#else
    status = 0;
#endif
    emit UpdateFstabDone(status);
    return status;
}

int AOSC_Installer_Core::SetUser(QString _UserName, QString _PassWord){
    char UserName[64];
    char PassWord[64];
    bzero(UserName,64);
    bzero(PassWord,64);
    TranslateQStringToChar(_UserName,UserName);
    TranslateQStringToChar(_PassWord,PassWord);
    char ExecBuff[128];
    sprintf(ExecBuff,"sudo chroot /target usermod -l %s -md /home/%s live",UserName,UserName);
    Exth = new ExecThread;
    this->connect(Exth,SIGNAL(WorkDone(int,int)),this,SLOT(WorkDone(int,int)));
    Exth->SetType(SET_USER);
    Exth->SetExecBuff(ExecBuff);
    Exth->start();
    sprintf(ExecBuff,"sudo chroot /target /usr/bin/cpw.sh %s %s",UserName,PassWord);
    Exth2 = new ExecThread;
    this->connect(Exth2,SIGNAL(WorkDone(int,int)),this,SLOT(WorkDone(int,int)));
    Exth2->SetType(SET_USER);
    Exth2->SetExecBuff(ExecBuff);
    Exth2->start();
    return 0;
}


int AOSC_Installer_Core::SetRootPassWord(QString _RootPass){
    char RootPass[64];
    bzero(RootPass,64);
    TranslateQStringToChar(_RootPass,RootPass);
    char ExecBuff[256];
    sprintf(ExecBuff,"sudo chroot /target  /usr/bin/cpw.sh root %s",RootPass);
    Exth3 = new ExecThread;
    this->connect(Exth3,SIGNAL(WorkDone(int,int)),this,SLOT(WorkDone(int,int)));
    Exth3->SetType(SET_ROOT);
    Exth3->SetExecBuff(ExecBuff);
    Exth3->start();
    return 0;
} 

void AOSC_Installer_Core::TranslateQStringToChar(QString in, char *Out){
    QByteArray ba = in.toLatin1();
    strcpy(Out,ba.data());
}

void AOSC_Installer_Core::SetInstallTarget(QString _TargetPartition, QString _TargetDisk){
    TargetPartition = new char[64];
    bzero(TargetPartition,64);
    TranslateQStringToChar(_TargetPartition,TargetPartition);

    TargetDisk      = new char[64];
    bzero(TargetDisk,64);
    TranslateQStringToChar(_TargetDisk,TargetDisk);
}

void AOSC_Installer_Core::IsEfiDevice(QString _target){
    TargetEfiPartiton = new char[64];
    bzero(TargetEfiPartiton,64);
    TranslateQStringToChar(_target,TargetEfiPartiton);

    isEfi = 1;
}

void AOSC_Installer_Core::AllDone(){
    system("sync");
    system("umount -R /target");
}

void AOSC_Installer_Core::WorkDone(int status, int type){
    emit SetDone(status);
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
    char ExecBuff[128];
    int  NowSize;
    sprintf(ExecBuff,"sudo du -s %s 2>/dev/null > %s",_INSTALL_FILE_DEST_,_TMP_TOTAL_SIZE_);
    system(ExecBuff);
    fp = fopen(_TMP_TOTAL_SIZE_,"r");
    while(1){
        sleep(2);
        fscanf(fp,"%d",&NowSize);
        emit Copyed(NowSize-Size);
        printf("Debug >> Now Copying Files Size ==  %d\n",NowSize-Size);
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
    char ExecBuff[128];
    sprintf(ExecBuff,"sudo rm -rf %s",_TMP_TOTAL_SIZE_);
    system(ExecBuff);
    this->terminate();
}

ExecThread::ExecThread(QThread *parent):
    QThread(parent){
}
void ExecThread::SetExecBuff(char *Buff){
    if(Buff != NULL)    strcpy(ExecBuff,Buff);
}
void ExecThread::SetType(int Type){
    ActionType=Type;
}

void ExecThread::run(){
    int result = -1;
    if(ExecBuff != NULL)
        result = system(ExecBuff);
    emit WorkDone(result,ActionType);
}
