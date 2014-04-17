#ifndef AOSC_INSTALLER_MAINWINDOW_H
#define AOSC_INSTALLER_MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QThread>
#include "GetStartTab/GetStartTab.h"
#include "ReadingTab/ReadingTab.h"
#include "PartedDiskTab/PartedDiskTab.h"
#include "WorkProcessTab/WorkProcessTab.h"
#include "ConfigureUserTab/ConfigureUserTab.h"
#include "WorkDoneTab/WorkDoneTab.h"

//define _INSTALL_FILE_      "/squash" //No need to mount squash, it's already there mounted...
#define _INSTALL_FILE_DEST_ "/target"
#define _TMP_TOTAL_SIZE_    "/tmp/TotleFile.tmp"
#define _TMP_NOW_SIZE       "/tmp/NowSize.tmp"

namespace Ui {
class AOSC_Installer_MainWindow;
class StatisticsFileSize;
}

class MyTabWidget : public QTabWidget{
    Q_OBJECT
public:
    explicit MyTabWidget(QTabWidget *parent = 0);
    ~MyTabWidget(){}
};

class StatisticsFileSize : public QThread{
    Q_OBJECT
public:
    explicit StatisticsFileSize(QThread *parent = 0);
    void run();
signals:
    void Copyed(int);
    void TotalFile(int);
public slots:
    void CopyDone();
    void GetReady(int);
protected:
    int NowSize;
    int AllSize;
    char ExecBuff[128];
    FILE *fp;
    int Size;
};

class AOSC_Installer_MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AOSC_Installer_MainWindow(QMainWindow *parent = 0);
    ~AOSC_Installer_MainWindow();
    void BuildObject(void);             //  为对象分配内存空间
    void AddToTabWidget(void);          //  将对象载入总tab里面
    void SetAllButtonEnable(void);
    void CheckButtonDisable(void);
    void closeEvent(QCloseEvent *);
signals:
    void SIG_StartCopyFile(void);
public slots:
    void SLOT_NextButtonClicked(void);
    void SLOT_PervButtonClicked(void);
    void SLOT_IAgreeCheckBoxClicked(bool);
    void SLOT_MountSquashfsDone(int);
    void SLOT_StartInstall(void);
    void SLOT_StartInstall_WithFormat(void);
    void SLOT_FormatDone(int);
    void SLOT_MountTargetDone(int);
    void SLOT_TotalFiles(int);
    void SLOT_NowCopyed(int);
    void SLOT_CopyFileDone(int Status);
    void SLOT_SetGrubDone(int);
    void SLOT_UpdateGrubDone(int);

    void SLOT_SetUserNameDone(int);
    void SLOT_SetUserPassDone(int);
    void SLOT_SetRootPassDone(int);
    void SLOT_DoPostInstDone(int);

    void SLOT_PrintStdOutput();

private:
    int                 AllFiles;
    int                 fh;
    Ui::AOSC_Installer_MainWindow *ui;
    QHBoxLayout         *layout;
    MyTabWidget         *MainTab;
    GetStartTab         *GetStart;
    ReadingTab          *Reading;
    PartedDiskTab       *PartedDisk;
    WorkProcessTab      *WorkProcess;
    ConfigureUserTab    *ConfigureUser;
    WorkDoneTab         *WorkDone;
    StatisticsFileSize  *StatisticsFiles;
    QProcess            *Format;
    QProcess            *SizeFile;
    QProcess            *MountTarget;
    QProcess            *MountSquashfs;
    QProcess            *MountEFIPartition;
    QProcess            *CopyFile;
    QProcess            *SetGrub;
    QProcess            *UpDateGrub;

    QProcess            *SetUserName;
    QProcess            *SetUserPass;
    QProcess            *SetRootPass;
    QProcess            *DoPostInst;

};


#endif // AOSC_INSTALLER_MAINWINDOW_H
