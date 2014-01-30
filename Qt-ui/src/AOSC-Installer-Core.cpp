#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AOSC-Installer-Core.h"

AOSC_Installer_Core::AOSC_Installer_Core(QObject *parent):
    QObject(parent){

}

int AOSC_Installer_Core::Check_Environment(void){
    int result = access(_INSTALL_FILE_,0);
    if(result != F_OK){
        perror("Loading Install File ");
        return -1;
    }
    return _EN_LIVE_CD_;
}

int AOSC_Installer_Core::Find_Disk(char ***DP){     // BUG!!!!!!!!!!!
    int k=0;
    system("ls /dev/sd* > /tmp/.DiskParted.info");
    FILE *fp = fopen("/tmp/.DiskParted.info","r");
    char *Temp = (char *)malloc(2500);    // 50 x 50
    bzero(Temp,2500);
    int i = 0;
    char *DiskPath[50];
    DiskPath[0] = (char *)malloc(64);
    printf("Malloc OK\n");
    bzero(DiskPath[0],64);
    while(fscanf(fp,"%s",DiskPath[i]) != EOF){
        printf("%s\n",DiskPath[i]);
        DiskPath[i+1] = (char *)malloc(64);
        bzero(DiskPath[i+1],64);
        k++;
    }
    *DP = DiskPath;
    return k;
}

bool AOSC_Installer_Core::CopyFileToNewSystem(void){
//    system("cp -arv /mnt/* /target/");
    NowCopy = 0;
    ThisTime = 0;
    QDir    From("/mnt/");
    QDir    Dest("/target");
    return qCopyDirectory(From,Dest,0);
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
