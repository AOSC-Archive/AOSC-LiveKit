#ifndef _AOSC_INSTALLER_CORE_H_
#define _AOSC_INSTALLER_CORE_H_

#include <qt4/QtCore/QFile>
#include <qt4/QtCore/QDir>
#include <qt4/QtCore/QObject>
#include <qt4/QtCore/QThread>
#include <qt4/QtCore/QFileInfoList>

#define _EN_LIVE_CD_        0
#define _INSTALL_FILE_      "/squash"
#define _TMP_TOTAL_FILE_    "/tmp/.TotalFile.conf"
#define _TMP_DISK_FILE      "/tmp/.Disk.conf"
#define _TMP_PARTITION_FILE "/tmp/.Partition.conf"

#define FAILED(x) ((x != 0) ? 1 : 0)
#define CHECK_FAILED(x) ({ if (FAILED(x)) return;})


class AOSC_Installer_Core : public QThread{
    Q_OBJECT
public:
    explicit AOSC_Installer_Core(QThread *parent = 0);
//##### Step ######//
    void    run();
    int     CheckEnvironment(void);
    //Main Step
    int     MountFS();
    bool    CopyFileToNewSystem(void);
    int     SetGrub();
    int     SetUser(QString _UserName,QString _PassWord);
    int     SetRootPassWord(QString);
    int     UpdateGrub(void);
    int     UpdateFstab(void);

    bool    qCopyDirectory(const QDir& fromDir, const QDir& toDir, bool bCoverIfFileExists);

    void    TranslateQStringToChar(QString in,char *Out);
    void    SetInstallTarget(QString _TargetPartition,QString _TargetDisk);
signals:
    void    MountFSDone(int);
    void    TotalFile(int);
    void    Copyed(int);
    void    CopyDone(int);
    void    SetGrubDone(int);
    void    UpdateGrubDone(int);
    void    UpdateFstabDone(int);
    void    SetUserDone(int);
    void    SetRootDone(int);

protected:
    int     NowCopy;
    int     ThisTime;
    char    *TargetPartition;
    char    *TargetDisk;
};

#endif
