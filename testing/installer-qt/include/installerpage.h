#ifndef INSTALLERPAGE_H
#define INSTALLERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QResizeEvent>
#include <QCheckBox>
#include <QTabWidget>
#include <QPushButton>
#include <QTabBar>
#include <QProgressBar>
#include <QFont>
#include "partitionselect.h"
#include "dialogbox.h"


#define CMD_COPYFILES    "Which command should I run to copy files ???"

class InstallerPage : public QWidget{
    Q_OBJECT
public:
    explicit InstallerPage(QWidget *parent = 0);
    ~InstallerPage();

    virtual void PervShow();                    //  在跳转到这个页面时要做的操作【例如将按钮disable之类的】
                                                //  每跳转到这个页面就会执行一次
    void    SetContantTitle(const QString &);
    void    resizeEvent(QResizeEvent* );
    QFont   cContantFont;
    virtual int  SLOT_NextButtonClicked(void);  //  下一步按钮被按下时所执行的操作


signals:
    void    SIGN_SetNextButtonDisabled(bool);
    void    SIGN_SetPervButtonDisabled(bool);
    void    SIGN_TurnToSpecialPage(QWidget *);

public slots:
    virtual void SLOT_PageChanged(QWidget *);
private:
    QLabel *cTitle;
};

typedef QMap<int,InstallerPage*> InstallerPagesMap_t;
//----------------------------------//
//--------众神与愚民的分界线-----------//
//--------此刻正是昼夜交替时-----------//
//--------耀日将寝，皓月当空-----------//
//--------鬼哭狼嚎，铁骑千军-----------//
//----------------------------------//

class WelcomePage : public InstallerPage{
    Q_OBJECT
public:
    explicit WelcomePage(InstallerPage *parent = 0);
    ~WelcomePage();
    void    resizeEvent(QResizeEvent *);
    void    PervShow();
    int     SLOT_NextButtonClicked();
private:
    QLabel  *Contant;
};

class ReadingPage : public InstallerPage{
    Q_OBJECT
public:
    explicit ReadingPage(InstallerPage *parent = 0);
    ~ReadingPage();
    void    resizeEvent(QResizeEvent *);
    void    PervShow();

public slots:
    void    AgreementChanged(bool);
private:
    QTextBrowser    *ReadingBrowser;
    QCheckBox       *isAgreed;
};

class PartedPage : public InstallerPage{
    Q_OBJECT
public:
    explicit PartedPage(InstallerPage *parent = 0);
    ~PartedPage();
    void PervShow();
    void            DelPartition(PedPartition TargetPartition,PedDisk TargetDisk);
    PartitionList   *List;
    int             SLOT_NextButtonClicked();
public slots:
    void            ShowChangeDialog(void);
    void            ShowAddDialog(void);
    void            AskForDeletePartition(void);
    void            MountPointChangeApplied(int);
    void            WorkDone(void);
private:
    MyTabWidget     *DeviceSelect;
    QPushButton     *ChangeButton;
    QPushButton     *AddButton;
    QPushButton     *DelButton;
    AddDialogBox    *AddDialog;
    ChangeDialogBox *ChangeDialog;
};

class InstallPage : public InstallerPage{
    Q_OBJECT
public:
    explicit InstallPage(InstallerPage *parent = 0);
    ~InstallPage();
    void PervShow();

    QFont           DefaultFont;
    QFont           BlodFont;
public slots:
    void            WorkDone(QString,int);
private:
    QProgressBar    *MainProgressBar;
    QLabel          *PreparingLabel;
    QLabel          *CopyFilesLabel;
    QLabel          *SetGrubLabel;
    QLabel          *PostInstLabel;

    WorkingThread   *Work;
};

#endif // INSTALLERPAGE_H
