#ifndef _AOSC_INSTALLER_CORE_H_
#define _AOSC_INSTALLER_CORE_H_

#include <qt4/QtCore/QFile>
#include <qt4/QtCore/QDir>
#include <qt4/QtCore/QObject>
#include <qt4/QtCore/QFileInfoList>

#define _EN_LIVE_CD_    0
#define _INSTALL_FILE_  "/squash"

class AOSC_Installer_Core : public QObject{
    Q_OBJECT
public:
    explicit AOSC_Installer_Core(QObject *parent = 0);
//##### Step ######//
    int     Check_Environment(void);
    int     Find_Disk(char ***DP);
    int     MainWork(char *TargetPartiting);

    //Main Step
    int     MountFS(char *TargetPartiting);
    bool    CopyFileToNewSystem(void);
    int     SetGrub(char *TargetDisk);
    int     SetUser(char *UserName,char *PassWord);
    int     SetRootPassWord(char *PassWord);
    int     UpdateGrub(void);
    int     UpdateFstab(void);

    bool    qCopyDirectory(const QDir& fromDir, const QDir& toDir, bool bCoverIfFileExists);
signals:
    void    Copyed(int);
protected:
    int     NowCopy;
    int     ThisTime;
};

#endif
