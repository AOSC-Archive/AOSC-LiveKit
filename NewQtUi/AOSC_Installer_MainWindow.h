#ifndef AOSC_INSTALLER_MAINWINDOW_H
#define AOSC_INSTALLER_MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include "GetStartTab/GetStartTab.h"
#include "ReadingTab/ReadingTab.h"
#include "PartedDiskTab/PartedDiskTab.h"
#include "WorkProcessTab/WorkProcessTab.h"
#include "ConfigureUserTab/ConfigureUserTab.h"
#include "WorkDoneTab/WorkDoneTab.h"

namespace Ui {
class AOSC_Installer_MainWindow;
}

class AOSC_Installer_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AOSC_Installer_MainWindow(QWidget *parent = 0);
    ~AOSC_Installer_MainWindow();
    void BuildObject(void);             //  为对象分配内存空间
    void AddToTabWidget(void);          //  将对象载入总tab里面
    void SetAllButtonEnable(void);
    void CheckButtonDisable(void);
public slots:
    void SLOT_NextButtonClicked(void);
    void SLOT_PervButtonClicked(void);
    void SLOT_IAgreeCheckBoxClicked(bool);

private:
    Ui::AOSC_Installer_MainWindow *ui;
    QHBoxLayout     *layout;
    QTabWidget      *MainTab;
    GetStartTab     *GetStart;
    ReadingTab      *Reading;
    PartedDiskTab   *PartedDisk;
    WorkProcessTab  *WorkProcess;
    ConfigureUserTab*ConfigureUser;
    WorkDoneTab     *WorkDone;

};

#endif // AOSC_INSTALLER_MAINWINDOW_H
