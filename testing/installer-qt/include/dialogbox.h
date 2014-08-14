#ifndef DIALOGBOX_H
#define DIALOGBOX_H
#include <QWidget>
#include <parted/parted.h>

class ChangeDialogBox : public QWidget{
    Q_OBJECT
public:
    explicit ChangeDialogBox(QWidget *parent = 0);
    ~ChangeDialogBox();
    void    SetCurrentPartition(PedPartition);
};

class AddDialogBox : public QWidget{
    Q_OBJECT
public:
    explicit AddDialogBox(QWidget *parent = 0);
    ~AddDialogBox();
    void    SetCurrentPartition(PedPartition CurrentPartition);
};

#endif // DIALOGBOX_H
