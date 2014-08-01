#ifndef INSTALLERMAIN_H
#define INSTALLERMAIN_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QMap>
#include "installerpage.h"

typedef QMap<int,InstallerPage*> InstallerPagesMap_t;

class InstallerMain : public QWidget{
    Q_OBJECT
public:
    explicit InstallerMain(QWidget *parent = 0);
    ~InstallerMain();
    void    AddPage(InstallerPage *);
    void    DelPage(InstallerPage *);

signals:
    void    SIGN_PageChanged(QWidget*);

public slots:
    void    SLOT_TurnToNextPage(void);
    void    SLOT_TurnToPervPage(void);
    void    SLOT_TurnToSpecifyPage(QWidget*);

private:
    QTabWidget                      *PageTab;
    QPushButton                     *NextButton;
    QPushButton                     *PervButton;
    InstallerPagesMap_t              InstallerMap;
    InstallerPagesMap_t::Iterator    InstallerMapIterator;
    int                              TotalPages;

};

#endif // INSTALLERMAIN_H
