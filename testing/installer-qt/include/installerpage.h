#ifndef INSTALLERPAGE_H
#define INSTALLERPAGE_H

#include <QWidget>

class InstallerPage : public QWidget{
    Q_OBJECT
public:
    explicit InstallerPage(QWidget *parent = 0);
    ~InstallerPage();

    virtual void PervShow();                    //  在跳转到这个页面时要做的操作【例如将按钮disable之类的】
                                                //  每跳转到这个页面就会执行一次


signals:
    void    SIGN_SetNextButtonDisabled(bool);
    void    SIGN_SetPervButtonDisabled(bool);
    void    SIGN_TurnToSpecialPage(QWidget *);

public slots:
    virtual void SLOT_NextButtonClicked(void);  //  下一步按钮被按下时所执行的操作
    virtual void SLOT_PageChanged(QWidget *);
};

#endif // INSTALLERPAGE_H
