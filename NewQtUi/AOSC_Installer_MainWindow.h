#ifndef AOSC_INSTALLER_MAINWINDOW_H
#define AOSC_INSTALLER_MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidgetItem>
#include "GetStartTab/GetStartTab.h"
#include "ReadingTab/ReadingTab.h"

namespace Ui {
class AOSC_Installer_MainWindow;
}

class AOSC_Installer_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AOSC_Installer_MainWindow(QWidget *parent = 0);
    ~AOSC_Installer_MainWindow();
    void CheckButtonDisable(void);
public slots:
    void SLOT_NextButtonClicked(void);
    void SLOT_PervButtonClicked(void);
    void SLOT_IAgreeCheckBoxClicked(bool);

private:
    Ui::AOSC_Installer_MainWindow *ui;
    QTabWidget  *MainTab;
    GetStartTab *GetStart;
    ReadingTab  *Reading;

};

#endif // AOSC_INSTALLER_MAINWINDOW_H
