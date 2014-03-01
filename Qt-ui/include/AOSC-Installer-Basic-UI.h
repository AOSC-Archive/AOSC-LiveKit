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
#include <qt4/QtGui/QLineEdit>
#include "AOSC-Installer-Core.h"

#define BUTTON_WIDTH    80
#define BUTTON_HEIGHT   30
#define WIDTH_SPACE     10
#define HEIGHT_SPACE    5

#define BASIC_TITLE_X   150
#define BASIC_TITLE_Y   100
#define BASIC_TITLE_W   500
#define BASIC_TITLE_H   70

#define EDITLINE_HEIGTH   45

#define BASIC_TITLE_CONTENT_SPACE   70

class Th : public QThread{
    Q_OBJECT
public:
    explicit Th(QThread *parent = 0);
    void run();
signals:
    void ST(void);
};

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
    void SetNextButtonText(QString Text);
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
    void IsEFIDevice(QString);
public slots:
    void SetCurrentDiskPartition(QString);
    void SetCurrentDisk(QString);
    void SetCurrentEfiPartition(QString);
    void StartPartiting(void);
    void ReadyToGo(void);
    void iseficlicked(int);
protected:
    QLabel          *Title;
    QLabel          *Warning;
    QLabel          *Content;
    QLabel          *Content2;
    QLabel          *Content3;
    QLabel          *Content4;
    QCheckBox       *CheckBox;
    QCheckBox       *isefi;
    QPushButton     *StartPartitingButton;
    QComboBox       *DiskComboBox;
    QComboBox       *DiskPartitingComboBox;
    QComboBox       *EfiDiskPartiting;
    char            *DiskPath;
    char            *DiskPartitingPath;
    int              DiskCount;
    int              DiskPartitingCount;
    QString          CurrentDiskPartition;
    QString          CurrentDisk;
    QString          CurrentEfiPartition;
    FILE            *fp;
    int              efi;
};
//------------------------------------------------------
class MainWorkTab : public ProgressTabWidget{
    Q_OBJECT
public:
    explicit MainWorkTab(QString _TargetPartition, QString _TargetDisk, ProgressTabWidget *parent = 0);
signals:
    void MountFS(QString);
    void S_StartInstall(QString,QString);
public slots:
    void StartInstall(void);
    void MountFSDone(int Status);
    void TotalFileDone(int);
    void FileCopying(int);
    void CopyDone(int);
    void SetGrubDone(int);
    void UpdateGrubDone(int);
    void UpdateFstabDone(int);
protected:
    QLabel          *Title;
    QLabel          *Content;
    QLabel          *Content2;
    QPushButton     *Start;
    QProgressBar    *ProgressBar;
    int             TotalFile;
    QString         TargetPartition;
    QString         TargetDisk;
};

class UserTab : public ProgressTabWidget{
    Q_OBJECT
public:
    explicit UserTab(int x,ProgressTabWidget *parent = 0);
public slots:
    void SetUserInformation(void);
    void SetRootDone(int);
    void SetUserDone(int);
signals:
    void StartSetUserInformation(QString,QString,QString);
    void AllDone(void);
protected:
    QLabel          *Title;

    QLabel          *RootPassTitle;
    QLabel          *RootPassTitle2;
    QLineEdit       *RootPassEdit;
    QLineEdit       *RootPassEdit2;

    QLabel          *UserNameTitle;
    QLabel          *UserPassTitle;
    QLabel          *UserPassTitle2;
    QLineEdit       *UserNameEdit;
    QLineEdit       *UserPassEdit;
    QLineEdit       *UserPassEdit2;

    QString         RootPass;
    QString         RootPass2;
    QString         UserName;
    QString         UserPass;
    QString         UserPass2;
};

class DoneTab : public ProgressTabWidget{
    Q_OBJECT
public:
    DoneTab(ProgressTabWidget *parent = 0);
public slots:
    void SetDone(int);
protected:
    int NowStep;
    QLabel          *Title;
    QLabel          *Content;
};

//-------------------------------------------------------


//#################### Main Tab ####################//

class ProgressTab : public QTabWidget{
    Q_OBJECT
public:
    explicit ProgressTab(QTabWidget *parent = 0);
    ~ProgressTab();
public slots:
    void NextStep(void);
    void PervStep(void);
    void AskHide(void);
    void AskShow(void);
    void PartedDone(QString, QString);
    void StartInstall(QString, QString);
    void StartSetUserInformation(QString,QString,QString);
    void AllDone(void);
    void resizeEvent(QResizeEvent *);
    void AddTabs(void);
signals:
    void Resized(int,int);
protected:
    AOSC_Installer_Core *Core;
    StatisticsFileSize  *SFSize;
    char                 TargetPartition[64];
    char                 TargetDisk[64];
    WelcomeTab          *Welcome;
    GetStartedTab       *GetStarted;
    ReadingTab          *Reading;
    GPartedDiskTab      *GPartedDisk;
    MainWorkTab         *MainWork;
    UserTab             *User;
    DoneTab             *Done;
};

#endif
