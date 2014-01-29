#ifndef _AOSC_INSTALLER_PROGRESSTAB_H_
#define _AOSC_INSTALLER_PROGRESSTAB_H_

#include <qt4/QtGui/QWidget>
#include <qt4/QtGui/QTabWidget>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QLayout>
#include <qt4/QtGui/QFont>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtCore/QEvent>
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

    QFont       TitleFont;
    QFont       SecondaryTitleFont;
    QFont       ContentFont;

signals:
    void NextSetp(void);
    void PervStep(void);
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

//#################### Main Tab ####################//

class ProgressTab : public QTabWidget{
    Q_OBJECT
public:
    explicit ProgressTab(QTabWidget *parent = 0);
public slots:
    void NextStep(void);
    void PervStep(void);
protected:
    AOSC_Installer_Core *Installer_Core;
    WelcomeTab *Welcome;
    GetStartedTab *GetStarted;
};

#endif
