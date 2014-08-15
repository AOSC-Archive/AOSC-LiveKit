#ifndef INSTALLERPAGE_H
#define INSTALLERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QResizeEvent>
#include <QCheckBox>
#include <QTabWidget>
#include <QPushButton>
#include "partitionselect.h"
#include "dialogbox.h"

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


signals:
    void    SIGN_SetNextButtonDisabled(bool);
    void    SIGN_SetPervButtonDisabled(bool);
    void    SIGN_TurnToSpecialPage(QWidget *);

public slots:
    virtual void SLOT_NextButtonClicked(void);  //  下一步按钮被按下时所执行的操作
    virtual void SLOT_PageChanged(QWidget *);
private:
    QLabel *cTitle;
};

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
public slots:
    void            ShowChangeDialog(void);
    void            ShowAddDialog(void);
    void            ChangeApplied(int);
private:
    QTabWidget      *DeviceSelect;
    QPushButton     *ChangeButton;
    QPushButton     *AddButton;
    QPushButton     *DelButton;
    PartitionList   *List;
    AddDialogBox    *AddDialog;
    ChangeDialogBox *ChangeDialog;
};

#endif // INSTALLERPAGE_H
