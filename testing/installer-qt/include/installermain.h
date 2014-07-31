#ifndef INSTALLERMAIN_H
#define INSTALLERMAIN_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>

class InstallerMain : public QWidget{
    Q_OBJECT
public:
    explicit InstallerMain(QWidget *parent = 0);
    ~InstallerMain();
    void    AddPage(QWidget *);
    void    DelPage(QWidget *);

signals:
    void    SIGN_PageChanged(QWidget*);

public slots:
    void    SLOT_TurnToNextPage(void);
    void    SLOT_TurnToPervPage(void);
    void    SLOT_TurnToSpecifyPage(QWidget*);
    void    SLOT_SetNextButtonDisabel(bool);
    void    SLOT_SetPervButtonDisable(bool);

private:
    QTabWidget  *PageTab;
    QPushButton *NextButton;
    QPushButton *PervButton;

};

#endif // INSTALLERMAIN_H
