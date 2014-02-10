#ifndef _AOSC_INSTALLER_CORE_H_
#define _AOSC_INSTALLER_CORE_H_

#include <qt4/QtCore/QFile>
#include <qt4/QtCore/QDir>
#include <qt4/QtCore/QObject>
#include <qt4/QtCore/QThread>
#include <qt4/QtCore/QFileInfoList>

#define _EN_LIVE_CD_        0
#define _INSTALL_FILE_      "/squash"
#define _TMP_TOTAL_SIZE_    "/tmp/.TotalSize.conf"
#define _TMP_TARGET_SIZE_   "/tmp/.TargetSize.conf"
#define _TMP_DISK_FILE      "/tmp/.Disk.conf"
#define _TMP_PARTITION_FILE "/tmp/.Partition.conf"
#define _INSTALL_FILE_FROM_ "/mnt/squash/."
#define _INSTALL_FILE_DEST_ "/target"

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

    void    AllDone(void);
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

    void    SFSizeStart(int);
    void    SFSizeStop();

protected:
    int     NowCopy;
    int     ThisTime;
    char    *TargetPartition;
    char    *TargetDisk;
};

class StatisticsFileSize : public QThread{
    Q_OBJECT
public:
    explicit StatisticsFileSize(QThread *parent = 0);
    void run();
signals:
    void Copyed(int);
public slots:
    void CopyDone();
    void GetReady(int);
protected:
    FILE *fp;
    int Size;
};

#endif
