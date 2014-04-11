#ifndef PARTEDDISKTAB_H
#define PARTEDDISKTAB_H

#include <QWidget>
#include <QProcess>
#include <QString>
#include <stdio.h>
#include <string.h>
#include <QDebug>
#define _TMP_PARTITION_FILE_    "/tmp/.Partition.tmp"
#define _TMP_DISK_FILE_         "/tmp/.Disk.tmp"
#define _TMP_EFI_PARTITION_FILE_ "/tmp/.EFI_Disk_Partition.tmp"
#define NO_DISK_SELECT              1
#define NO_PARTITION_SELECT         2
#define NO_EFI_PARTITION_SELECT     3
#define NO_FILESYSTEM_TYPE_SELECT   4
#define NO_FORMAT                   5

namespace Ui {
class PartedDiskTab;
}

class PartedDiskTab : public QWidget
{
    Q_OBJECT

public:
    explicit PartedDiskTab(QWidget *parent = 0);
    ~PartedDiskTab();
    void UpdateDiskMap(void);
    void UpdatePartitionMap(void);
    void UpdateEFIPartitionMap(void);
    int CheckInput(void);
    int isEFIDevice(void);
    QString GetTargetDisk(void);
    QString GetTargetPartition(void);
    QString GetEFIPartition(void);



signals:
    void SIG_FormatDiskPartition(QString,int,bool);
    void SIG_MyDeviceIsEFI(QString,bool);
    void SIG_PartitionDiskButtonClicked(void);
    void SIG_AskForHide(void);
    void SIG_AskForShow(void);

public slots:
    void SLOT_FormatDiskPartitionCheckBoxClicked(bool);
    void SLOT_MyDeviceIsEFICheckBoxClicked(bool);
    void SLOT_PartitionDiskButtonClicked(void);

private:
    Ui::PartedDiskTab *ui;
};

#endif // PARTEDDISKTAB_H
