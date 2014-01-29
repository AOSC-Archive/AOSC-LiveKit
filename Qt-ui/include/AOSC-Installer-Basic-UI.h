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
    void PartedDone(QString);
public slots:
    void SetCurrentDiskPartition(QString);
    void StartPartiting(void);
    void ReadyToGo(void);
protected:
    QLabel          *Title;
    QLabel          *Waring;
    QLabel          *Content;
    QLabel          *Content2;
    QCheckBox       *CheckBox;
    QPushButton     *StartPartitingButton;
    QComboBox       *ComboBox;
    char            *DiskPath;
    char             Disk[50][50];
    int              DiskCount;
    QString          CurrentDiskPartition;
};
//------------------------------------------------------
class MainWorkThread : public QThread{
    Q_OBJECT
public:
    explicit MainWorkThread(char *TargetPartiting);
    void run();
signals:
    void CopyFileDone(int);             // int is Status
    void InstallBootLoaderDone(int);    // As well
protected:
    char *Target;
};



class MainWorkTab : public ProgressTabWidget{
    Q_OBJECT
public:
    explicit MainWorkTab(char *TargetPartiting,ProgressTabWidget *parent = 0);
protected:
    QLabel          *Title;
    QPushButton     *Start;
    MainWorkThread  *MainWork;
};

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
    void PartedDone(QString);
protected:
    char                 TargetPartiting[50];
    WelcomeTab          *Welcome;
    GetStartedTab       *GetStarted;
    ReadingTab          *Reading;
    GPartedDiskTab      *GPartedDisk;
    MainWorkTab         *MainWork;
};

#endif
