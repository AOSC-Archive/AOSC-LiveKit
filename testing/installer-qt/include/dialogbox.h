#ifndef DIALOGBOX_H
#define DIALOGBOX_H
#include "workingthread.h"
#include <QWidget>
#include <parted/parted.h>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QString>
#include <QThread>
#include <QMessageBox>
#include <QSpinBox>
#include <QTabWidget>
#include <QTabBar>

#define     INSTALLER_MOUNT_POINT_NONE  0
#define     INSTALLER_MOUNT_POINT_ROOT  1
#define     INSTALLER_MOUNT_POINT_HOME  2
#define     INSTALLER_MOUNT_POINT_USR   3
#define     INSTALLER_MOUNT_POINT_BOOT  4

#define     INSTALLER_FILESYSTEM_NONE   -2
#define     INSTALLER_FILESYSTEM_FREESPACE -1
#define     INSTALLER_FILESYSTEM_EXT2   0
#define     INSTALLER_FILESYSTEM_EXT3   1
#define     INSTALLER_FILESYSTEM_EXT4   2
#define     INSTALLER_FILESYSTEM_NTFS   3
#define     INSTALLER_FILESYSTEM_FAT32  4

#define     INSTALLER_WORKTYPE_ADD      1
#define     INSTALLER_WORKTYPE_CHANGE   2

class ChangeDialogBox : public QWidget{
    Q_OBJECT
public:
    explicit ChangeDialogBox(QWidget *parent = 0);
    ~ChangeDialogBox();
    void    SetCurrentPartition(PedPartition Partition, PedDisk Disk, PedDevice Device, int, int WorkType);
signals:
    void    MountPointChangeApplied(int);     // MountPoint;
    void    WorkDone(void);

public slots:
    void    ApplyButtonClicked(void);
    void    CancelButtonClicked(void);
    void    FileSystemSelectChanged(int);
    void    FormatDone(int);
private:
    PedPartition     CurrentPartition;
    PedDisk          CurrentDisk;
    PedDevice        CurrentDevice;
    int              OriginMountPoint;
    int              OriginFileSystem;
    int              WorkType;
    QPushButton     *ApplyButton;
    QPushButton     *CancelButton;
    QLabel          *PartitionPath;
    QLabel          *FileSystemLabel;
    QLabel          *MountPointLabel;
    QLabel          *DoFormatLabel;
    QComboBox       *FileSystemSelect;
    QComboBox       *MountPointSelect;
    QCheckBox       *DoFormatCheckBox;
    QSpinBox        *PartitionSize;
    QLabel          *PartitionSizeLabel;

    QString         CurrentFileSystem;
    QString         CurrentMountPoint;
    WorkingDialog   *DoWork;
};

class AddDialogBox : public QWidget{
    Q_OBJECT
public:
    explicit AddDialogBox(QWidget *parent = 0);
    ~AddDialogBox();
    void    SetCurrentPartition(PedPartition CurrentPartition);
private:
    int              OriginMountPoint;
    int              OriginFileSystem;
    QPushButton     *ApplyButton;
    QPushButton     *CancelButton;
    QLabel          *PartitionPath;
    QComboBox       *FileSystemSelect;
    QComboBox       *MountPointSelect;
};


class MyTabWidget : public QTabWidget{
    Q_OBJECT
public:
    explicit MyTabWidget(QWidget *parent = 0);
};



#endif // DIALOGBOX_H
