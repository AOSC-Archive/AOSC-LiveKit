#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QByteArray>
#include "AOSC-Installer-Core.h"

AOSC_Installer_Core::AOSC_Installer_Core(QThread *parent):
    QThread(parent){

}

void AOSC_Installer_Core::run(){
#ifdef  _AOSC_LIVE_CD_
    CHECK_FAILED(MountFS());
#endif
    if (CopyFileToNewSystem() != true)  return;
    if (SetGrub() != 0)                 return;
    if (UpdateGrub() != 0)              return;
    if (UpdateFstab() != 0)             return;
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
    QDir    From("/mnt/");
    QDir    Dest("/target");
    char ExecBuff[512];
    sprintf(ExecBuff,"ls -lR /mnt | grep ^- | wc -l > /tmp/.TotalFile.conf");
    system(ExecBuff);
    FILE *f = fopen(_TMP_TOTAL_FILE_,"r");
    int Total;
    fscanf(f,"%d",&Total);
    sprintf(ExecBuff,"rm -rf %s",_TMP_TOTAL_FILE_);
    system(ExecBuff);
    emit TotalFile(Total);
    int status = qCopyDirectory(From,Dest,0);
    emit CopyDone(status);
    return status;
}

/*********************************************************************/
  /*功能：拷贝文件夹
    qCopyDirectory -- 拷贝目录
    fromDir : 源目录
    toDir   : 目标目录
    bCoverIfFileExists : ture:同名时覆盖  false:同名时返回false,终止拷贝
    返回: ture拷贝成功 false:拷贝未完成*/
/***********************************************************************/
bool AOSC_Installer_Core::qCopyDirectory(const QDir& fromDir, const QDir& toDir, bool bCoverIfFileExists)
{
    QDir formDir_ = fromDir;
    QDir toDir_ = toDir;

    if(!toDir_.exists())
    {
        if(!toDir_.mkdir(toDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = formDir_.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        //拷贝子目录
        if(fileInfo.isDir())
        {
            //递归调用拷贝
            if(!qCopyDirectory(fileInfo.filePath(), toDir_.filePath(fileInfo.fileName()),true))
                return false;
        }
        //拷贝子文件
        else
        {
            if(bCoverIfFileExists && toDir_.exists(fileInfo.fileName()))
            {
                toDir_.remove(fileInfo.fileName());
            }
            if(!QFile::copy(fileInfo.filePath(), toDir_.filePath(fileInfo.fileName())))
            {
                return false;
            }else{
                ThisTime++;
                if(ThisTime > 128){
                    NowCopy += ThisTime;
                    ThisTime = 0;
                    emit Copyed(NowCopy);
                }
            }
        }
    }
    return true;
}

//#################Main Step#####################
int AOSC_Installer_Core::MountFS(){
    char ExecBuff[512];
    int status;
    sprintf(ExecBuff,"mount -o loop %s /mnt",_INSTALL_FILE_);
    status = system(ExecBuff);
    if(status != 0){
        emit MountFSDone(status);
        return status;
    }
    sprintf(ExecBuff,"mount %s /target",TargetPartition);
    status = system(ExecBuff);
    emit MountFSDone(status);
    return status;
}

int AOSC_Installer_Core::SetGrub(){
    char ExecBuff[512];
    int status;
#ifdef _AOSC_LIVE_CD_
    sprintf(ExecBuff,"chroot /target grub-install %s",TargetDisk);
#else
    sprintf(ExecBuff,"grub-install %s",TargetDisk);
#endif
    status = system(ExecBuff);
    emit SetGrubDone(status);
    return status;
}

int AOSC_Installer_Core::UpdateGrub(){
    char ExecBuff[512];
    int status;
#ifdef _AOSC_LIVE_CD_
    sprintf(ExecBuff,"chroot /target grub-mkconfig -o /boot/grub/grub.cfg");
#else
    sprintf(ExecBuff,"grub-mkconfig -o /boot/grub/grub.cfg");
#endif
    status = system(ExecBuff);
    emit UpdateGrubDone(status);
    return status;
}

int AOSC_Installer_Core::UpdateFstab(void){
    char ExecBuff[512];
    int status;
#ifdef _AOSC_LIVE_CD_
    sprintf(ExecBuff,"chroot /target echo \"%s / ext4 defaults 1 1\" > /target/etc/fstab",TargetPartition);
    status = system(ExecBuff);
#else
    status = 0;
#endif
    emit UpdateFstabDone(status);
    return status;
}

int AOSC_Installer_Core::SetUser(char *UserName, char *PassWord){
    char ExecBuff[512];
    int status;
    sprintf(ExecBuff,"chroot /target usermod -l %s -md /home/%s live",UserName,UserName);
    status = system(ExecBuff);
    if(status < 0){
        return status;
    }
    sprintf(ExecBuff,"chroot /target /usr/bin/cpw.sh %s %s",UserName,PassWord);
    status = system(ExecBuff);
    emit SetUserDone(status);
    return status;
}

/* 
int AOSC_Installer_Core::SetRootPassWord(char *PassWord){
    char ExecBuff[256];
    int status;
    sprintf(ExecBuff,"/usr/bin/cpw.sh root %s",PassWord);
    status = system(ExecBuff);
    if(status < 0){
        return status;
    }
    return 0;
}
*/ 

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
