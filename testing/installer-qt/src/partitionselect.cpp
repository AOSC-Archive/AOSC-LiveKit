#include "partitionselect.h"
#include "dialogbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <QToolBox>
#include <QListWidget>
#include <QLabel>
#include <QtGui>
#include <QListView>
#include <QFrame>
#include <QScrollArea>
#include <QMap>
#include <QDebug>
#include <QObject>

PartitionItem::PartitionItem(QWidget *parent)
    :QWidget(parent){
    this->show();
//    this->setStyleSheet("border:1px solid black");
    PartitionLabel  = new QLabel(this);
    FileSystemLabel = new QLabel(this);
    SizeLabel       = new QLabel(this);
    MountPointLabel = new QLabel(this);
    layout          = new QHBoxLayout(this);
    this->setLayout(layout);
    layout->addWidget(PartitionLabel);
    layout->addWidget(FileSystemLabel);
    layout->addWidget(SizeLabel);
    layout->addWidget(MountPointLabel);
}
void PartitionItem::SetPartiton(PedPartition *_Partition, PedDevice *_Device, PedDisk *_Disk, int MountPoint = INSTALLER_MOUNT_POINT_NONE){
    if(_Partition->type == PED_PARTITION_FREESPACE){  //Free Space
        PartitionLabel->setText(tr("Free Space").toUtf8().data());
        char size[36];
        sprintf(size,"%lld GB",(_Partition->geom.length * _Device->sector_size)/(1024*1024*1024));
        SizeLabel->setText(size);
        FileSystemLabel->setText(tr("Unknown"));
    }
    else if(_Partition->type == PED_PARTITION_NORMAL){  //  Normal Partition
        PartitionLabel->setText(ped_partition_get_path(_Partition));
        char size[36];
        sprintf(size,"%lld GB",(_Partition->geom.length * _Device->sector_size)/(1024*1024*1024));
        SizeLabel->setText(size);
        if(_Partition->fs_type)
            FileSystemLabel->setText(_Partition->fs_type->name);
        else
            FileSystemLabel->setText(tr("Unknown"));
    }
    else{
        PartitionLabel->setText(tr("Disabled").toUtf8().data());
        char size[36];
        sprintf(size,"%lld GB",(_Partition->geom.length * _Device->sector_size)/(1024*1024*1024));
        SizeLabel->setText(size);
        FileSystemLabel->setText(tr("Unknown"));
    }
    if(MountPoint == INSTALLER_MOUNT_POINT_NONE)
        MountPointLabel->setText(tr("NULL"));
    else if(MountPoint == INSTALLER_MOUNT_POINT_ROOT)
        MountPointLabel->setText(tr("/"));
    else if(MountPoint == INSTALLER_MOUNT_POINT_HOME)
        MountPointLabel->setText(tr("/home"));
    memcpy((void*)&Partition,(void*)_Partition,sizeof(PedPartition));
    memcpy((void*)&Device,(void*)_Device,sizeof(PedDevice));
    memcpy((void*)&Disk,(void*)_Disk,sizeof(PedDisk));
    PartitionLabel->setGeometry(0,0,50,20);
    PartitionLabel->show();
}

PedPartition PartitionItem::GetPartition(){
    return Partition;
}

PedDisk PartitionItem::GetDisk(){
    return Disk;
}

PedDevice PartitionItem::GetDevice(){
    return Device;
}

int PartitionItem::GetMountPoint(){
    return MountPoint;
}

void PartitionItem::SetMountPoint(int _MountPoint){
    MountPoint = _MountPoint;
    if(MountPoint == INSTALLER_MOUNT_POINT_NONE)
        MountPointLabel->setText(tr("NULL"));
    else if(MountPoint == INSTALLER_MOUNT_POINT_ROOT)
        MountPointLabel->setText(tr("/"));
    else if(MountPoint == INSTALLER_MOUNT_POINT_HOME)
        MountPointLabel->setText(tr("/home"));
}

void PartitionItem::SetUnselected(bool Status){
    if(Status == true)
        this->setStyleSheet("border:none");
    else
        this->setStyleSheet("border:1px solid black");
}

void PartitionItem::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit clicked(this);
        this->setStyleSheet("border:1px solid black");
    }else
        QWidget::mousePressEvent(event);
}

//#############################################################

PartitionList::PartitionList(QWidget *parent)
    :QWidget(parent){
    PartitionLayout = new QVBoxLayout;
    FriendLabelList = new QWidget(this);
    FriendLabelList->setLayout(PartitionLayout);
    PartitionLayout->setMargin(0);
    PartitionLayout->setSpacing(0);
    PartitionLayout->setContentsMargins(0,0,0,0);
    FriendLabelList->resize(1,1);
    List = new QScrollArea(this);
    List->setWidget(FriendLabelList);
    FriendLabelList->show();
    List->show();
    this->show();
    PartitionCount = 0;
    NowMountPoint = INSTALLER_MOUNT_POINT_NONE;
}

void PartitionList::AddPartition(PedPartition *_Partition, PedDevice *Device, PedDisk *Disk){
    if ((_Partition->type & PED_PARTITION_METADATA) ||
                    (_Partition->type & PED_PARTITION_EXTENDED))
        return;
     PartitionItem *f = new PartitionItem(this);
     PartitionCount++;
     f->SetPartiton(_Partition,Device,Disk);
     f->resize(List->width()-20,_FRIEND_LABEL_HEIGTH);
     FriendLabelList->resize(List->width()-20,_FRIEND_LABEL_HEIGTH*PartitionCount);
     PartitionLayout->addWidget(f);
     this->connect(f,SIGNAL(clicked(PartitionItem*)),this,SLOT(ItemClicked(PartitionItem*)));
     PartitionMap[PartitionCount] = f;
     char Path[36];
     bzero(Path,36);
     memcpy(Path,ped_partition_get_path(_Partition),strlen(ped_partition_get_path(_Partition)));
     if(MountPointMap.contains(INSTALLER_MOUNT_POINT_ROOT)){
        MountPointIterator = MountPointMap.find(INSTALLER_MOUNT_POINT_ROOT);
        if(MountPointIterator.value() == Path){
            f->SetMountPoint(INSTALLER_MOUNT_POINT_ROOT);
                return;
        }
    }
    if(MountPointMap.contains(INSTALLER_MOUNT_POINT_HOME)){
        MountPointIterator = MountPointMap.find(INSTALLER_MOUNT_POINT_HOME);
        if(MountPointIterator.value() == Path){
            f->SetMountPoint(INSTALLER_MOUNT_POINT_HOME);
                return;
        }
    }
}

void PartitionList::ClearPartitionList(){
    if(PartitionMap.isEmpty() == false){
        for(Result = PartitionMap.begin();Result != PartitionMap.end();Result++)
            delete Result.value();
        PartitionMap.clear();
    }
    PartitionCount = 0;
}

void PartitionList::resizeEvent(QResizeEvent *){
    List->resize(this->width(),this->height());
    FriendLabelList->resize(List->width()-20,_FRIEND_LABEL_HEIGTH*PartitionCount);
}

void PartitionList::SetPartitionCount(int n){
    PartitionCount=n;
}

int PartitionList::GetPartitionCount(){
    return PartitionCount;
}

void PartitionList::ItemClicked(PartitionItem *Item){
    if(PartitionMap.isEmpty() == false){
        for(Result = PartitionMap.begin();Result != PartitionMap.end();Result++){
            Result.value()->SetUnselected(true);
        }
    }
    if(Item->GetPartition().type == PED_PARTITION_NORMAL){
        emit SetChangeButtonDisabled(false);
        emit SetAddButtonDisabled(true);
        emit SetDelButtonDisabled(false);
    }else if(Item->GetPartition().type == PED_PARTITION_FREESPACE){
        emit SetChangeButtonDisabled(true);
        emit SetAddButtonDisabled(false);
        emit SetDelButtonDisabled(true);
    }else{
        emit SetChangeButtonDisabled(true);
        emit SetAddButtonDisabled(true);
        emit SetDelButtonDisabled(true);
    }
    CurrentSelelcted = Item;
}

PedPartition PartitionList::GetPartitionDataByUID(uint32_t UID){
    Result = PartitionMap.find(UID);
    return Result.value()->GetPartition();
}

void PartitionList::SetCurrentMountPoint(int MountPoint){
    if(MountPoint == INSTALLER_MOUNT_POINT_NONE){
        return;
    }
    CurrentSelelcted->SetMountPoint(MountPoint);
    PedPartition t = CurrentSelelcted->GetPartition();
    MountPointMap[MountPoint]=ped_partition_get_path(&t);
}

int PartitionList::GetCurrentMountPoint(){
    return CurrentSelelcted->GetMountPoint();
}

PedPartition PartitionList::GetCurrentSelectedPartition(){
    return CurrentSelelcted->GetPartition();
}

PedDisk PartitionList::GetCurrentSelectedDisk(){
    return CurrentSelelcted->GetDisk();
}

PedDevice PartitionList::GetCurrentSelectedDevice(){
    return CurrentSelelcted->GetDevice();
}

void PartitionList::RefreshList(){
    ClearPartitionList();
    PedPartition Part;
    PedDevice *dev = 0;
    while((dev = ped_device_get_next(dev))){
      /*printf("\n ==============================================\n");
        printf("device model: %s\n", dev->model);
        printf("path: %s\n",dev->path);
        long long size = (dev->sector_size * dev->length)/(1024*1024*1024);
        printf("size: %lld G\n", size);*/
        PedDisk* disk = ped_disk_new(dev);
        PedPartition* part = 0;
        while((part = ped_disk_next_partition(disk, part))){
            //略过不是分区的空间
      /*    if ((part->type & PED_PARTITION_METADATA) ||
                (part->type & PED_PARTITION_FREESPACE) ||
                (part->type & PED_PARTITION_EXTENDED))
                    continue;*/
          /*printf("++++++++++++++++++++++++++++++++++++\n");
            printf("partition: %s\n", ped_partition_get_path(part));
            if(part->fs_type)
                printf("fs_type: %s\n", part->fs_type->name);
            else
                printf("fs_type: (null)\n");
            //printf("partition start:%lld/n", part->geom.start);
            //printf("partition end: %lld/n", part->geom.end);
            printf("partition length:%lld M\n", (part->geom.length * dev->sector_size)/(1024*1024));*/
            memcpy((void*)&Part,(void*)part,sizeof(Part));
            AddPartition(part,dev,disk);
        }
    }
}
