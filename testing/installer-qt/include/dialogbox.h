#ifndef DIALOGBOX_H
#define DIALOGBOX_H
#include <QWidget>
#include <parted/parted.h>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QString>

#define     INSTALLER_MOUNT_POINT_NONE  0
#define     INSTALLER_MOUNT_POINT_ROOT  1
#define     INSTALLER_MOUNT_POINT_HOME  2
#define     INSTALLER_MOUNT_POINT_USR   3
#define     INSTALLER_MOUNT_POINT_BOOT  4

class ChangeDialogBox : public QWidget{
    Q_OBJECT
public:
    explicit ChangeDialogBox(QWidget *parent = 0);
    ~ChangeDialogBox();
    void    SetCurrentPartition(PedPartition,int);
signals:
    void    ChangeApplied(int);     // MountPoint;

public slots:
    void    ApplyButtonClicked(void);
    void    CancelButtonClicked(void);
private:
    int              OriginMountPoint;
    QPushButton     *ApplyButton;
    QPushButton     *CancelButton;
    QLabel          *PartitionPath;
    QLabel          *FileSystemLabel;
    QLabel          *MountPointLabel;
    QLabel          *DoFormatLabel;
    QComboBox       *FileSystemSelect;
    QComboBox       *MountPointSelect;
    QCheckBox       *DoFormatCheckBox;

    QString         CurrentFileSystem;
    QString         CurrentMountPoint;
};

class AddDialogBox : public QWidget{
    Q_OBJECT
public:
    explicit AddDialogBox(QWidget *parent = 0);
    ~AddDialogBox();
    void    SetCurrentPartition(PedPartition CurrentPartition);
private:
    int              OriginMountPoint;
    QPushButton     *ApplyButton;
    QPushButton     *CancelButton;
    QLabel          *PartitionPath;
    QComboBox       *FileSystemSelect;
    QComboBox       *MountPointSelect;
};

#endif // DIALOGBOX_H
