#ifndef INSTALLERMAIN_H
#define INSTALLERMAIN_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QMap>
#include <QResizeEvent>
#include <QLabel>
#include <QTabBar>
#include "installerpage.h"

class InstallerMain : public QWidget{
    Q_OBJECT
public:
    explicit InstallerMain(QWidget *parent = 0);
    ~InstallerMain();
    void    AddPage(InstallerPage *);
    void    DelPage(InstallerPage *);
    void    resizeEvent(QResizeEvent *);

signals:
    void    SIGN_PageChanged(QWidget*);

public slots:
    void    SLOT_TurnToNextPage(void);
    void    SLOT_TurnToPervPage(void);
    void    SLOT_TurnToSpecifyPage(QWidget*);

private:
    MyTabWidget                      *PageTab;
    QPushButton                     *NextButton;
    QPushButton                     *PervButton;
    QMap<int,InstallerPage*>              InstallerMap;
    QMap<int,InstallerPage*>::Iterator    InstallerMapIterator;
    QMap<int,QString>                  MountPoint;
    QMap<int,QString>::Iterator        MountPointMapIterator;
    int                              TotalPages;
    QLabel                          *Introduce;
};

#endif // INSTALLERMAIN_H
