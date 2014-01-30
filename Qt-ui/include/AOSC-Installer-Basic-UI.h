#ifndef _AOSC_INSTALLER_PROGRESSTAB_H_
#define _AOSC_INSTALLER_PROGRESSTAB_H_

#include <qt4/QtGui/QWidget>
#include <qt4/QtGui/QTabWidget>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QLayout>
#include <qt4/QtGui/QFont>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtCore/QEvent>
#include <qt4/QtGui/QTextBrowser>
#include <qt4/QtGui/QCheckBox>
#include <qt4/QtGui/QComboBox>
#include <qt4/QtCore/QString>
#include <qt4/QtCore/QThread>
#include <qt4/QtGui/QProgressBar>
#include "AOSC-Installer-Core.h"

#define BUTTON_WIDTH    80
#define BUTTON_HEIGHT   30
#define WIDTH_SPACE     10
#define HEIGHT_SPACE    5

class ProgressTabWidget : public QWidget{
    Q_OBJECT
public:
    explicit ProgressTabWidget(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *);
    void SetNextButtonHide(void);
    void SetPervButtonHide(void);
    void SetNextButtonDisable(void);
    void SetNextButtonEnable(void);
    void SetPervButtonDisable(void);
    void SetPervButtonEnable(void);

    QFont       TitleFont;
    QFont       SecondaryTitleFont;
    QFont       ContentFont;

signals:
    void NextSetp(void);
    void PervStep(void);
    void AskHide(void);
    void AskShow(void);
public slots:
    void NextStepClicked(void);
    void PervStepClicked(void);
protected:
    QPushButton *NextStepButton;
    QPushButton *PervStepButton;
};

//################## 分支 Tab 区 ##################//
class WelcomeTab : public ProgressTabWidget{
    Q_OBJECT
public:
    explicit WelcomeTab(ProgressTabWidget *parent = 0);
protected:
    QLabel  *Title;
    QLabel  *Content;
};
//--------------------------------------------------
class GetStartedTab : public ProgressTabWidget{
    Q_OBJECT
public:
    explicit GetStartedTab(ProgressTabWidget *parent = 0);
protected:
    QLabel  *Title;
    QLabel  *SecondaryTitle;
    QLabel  *Content;
};
//---------------------------------------------------
class ReadingTab : public ProgressTabWidget{
    Q_OBJECT
public:
    explicit ReadingTab(ProgressTabWidget *parent = 0);
public slots:
    void CheckBoxChanged(void);
protected:
    QLabel          *Title;
    QLabel          *Content;
    QTextBrowser    *Browser;
    QCheckBox       *CheckBox;
    QVBoxLayout     *VBoxLayout;
    QHBoxLayout     *HBoxLayout;
    bool             CheckBoxStatus;
};
//-----------------------------------------------------
class GPartedDiskTab : public ProgressTabWidget{
    Q_OBJECT
public:
    explicit GPartedDiskTab(ProgressTabWidget *parent = 0);
signals:
    void PartedDone(QString,QString);
public slots:
    void SetCurrentDiskPartition(QString);
    void SetCurrentDisk(QString);
    void StartPartiting(void);
    void ReadyToGo(void);
protected:
    QLabel          *Title;
    QLabel          *Waring;
    QLabel          *Content;
    QLabel          *Content2;
    QLabel          *Content3;
    QCheckBox       *CheckBox;
    QPushButton     *StartPartitingButton;
    QComboBox       *DiskComboBox;
    QComboBox       *DiskPartitingComboBox;
    char            *DiskPath;
    char            *DiskPartitingPath;
    int              DiskCount;
    int              DiskPartitingCount;
    QString          CurrentDiskPartition;
    QString          CurrentDisk;
    FILE            *fp;
};
//------------------------------------------------------
class MainWorkThread : public QThread{
    Q_OBJECT
public:
    explicit MainWorkThread(char *_TargetPartition, char *_TargetDisk);
    void run();
signals:
    void CopyFileDone(int);             // int is Status
    void TotalFile(int);
    void NowCopy(int);
    void SetGrubDone(int);
    void SetUseeDone(int);
    void SetRootDone(int);
    void UpdateGrubDone(int);
    void UpdateFstabDOne(int);
public slots:
    void FileCopyed(int);
    void SetUser(QString Name,QString Pass);
    void SetRoot(QString Pass);
protected:
    char *TargetPartition;
    char *TargetDisk;
    int   Total;
    AOSC_Installer_Core *Core;
};

class MainWorkTab : public ProgressTabWidget{
    Q_OBJECT
public:
    explicit MainWorkTab(char *_TargetPartition, char *_TargetDisk, ProgressTabWidget *parent = 0);
public slots:
    void Install_Start(void);
    void TotalFileDone(int);
    void FileCopying(int);
    void CopyDone(int);
    void SetGrubDone(int);
    void SetUseeDone(int);
    void SetRootDone(int);
    void UpdateGrubDone(int);
    void UpdateFstabDOne(int);
protected:
    QLabel          *Title;
    QLabel          *Content;
    QPushButton     *Start;
    MainWorkThread  *MainWork;
    QProgressBar    *ProgressBar;
    int             TotalFile;
    char            TargetPartition[64];
    char            TargetDisk[64];
};
//-------------------------------------------------------


//#################### Main Tab ####################//

class ProgressTab : public QTabWidget{
    Q_OBJECT
public:
    explicit ProgressTab(QTabWidget *parent = 0);
public slots:
    void NextStep(void);
    void PervStep(void);
    void AskHide(void);
    void AskShow(void);
    void PartedDone(QString, QString);
protected:
    char                 TargetPartition[64];
    char                 TargetDisk[64];
    WelcomeTab          *Welcome;
    GetStartedTab       *GetStarted;
    ReadingTab          *Reading;
    GPartedDiskTab      *GPartedDisk;
    MainWorkTab         *MainWork;
};

#endif
