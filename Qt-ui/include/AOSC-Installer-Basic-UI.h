#ifndef _AOSC_INSTALLER_BASIC_UI_H_
#define _AOSC_INSTALLER_BASIC_UI_H_

#include <qt4/QtGui/QMainWindow>
#include <AOSC-Installer-Core.h>


class AOSC_Installer_GUI : public QMainWindow{
    Q_OBJECT
public:
    explicit AOSC_Installer_GUI(QWidget *parent = 0);
protected:
    AOSC_Installer_Core Installer_Core;
};

#endif
