#include "partitionselect.h"
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
    layout          = new QHBoxLayout(this);
    this->setLayout(layout);
    layout->addWidget(PartitionLabel);
    layout->addWidget(FileSystemLabel);
    layout->addWidget(SizeLabel);
}
void PartitionItem::SetPartiton(PedPartition *_Partition,PedDevice *Device){
    if(_Partition->type == PED_PARTITION_FREESPACE){  //Free Space
        PartitionLabel->setText(tr("Free Space").toUtf8().data());
        char size[36];
        sprintf(size,"%lld GB",(_Partition->geom.length * Device->sector_size)/(1024*1024*1024));
        SizeLabel->setText(size);
        FileSystemLabel->setText(tr("Unknown"));
    }
    else if(_Partition->type == PED_PARTITION_NORMAL){  //  Normal Partition
        PartitionLabel->setText(ped_partition_get_path(_Partition));
        char size[36];
        sprintf(size,"%lld GB",(_Partition->geom.length * Device->sector_size)/(1024*1024*1024));
        SizeLabel->setText(size);
        if(_Partition->fs_type)
            FileSystemLabel->setText(_Partition->fs_type->name);
        else
            FileSystemLabel->setText(tr("Unknown"));
    }
    else{
        PartitionLabel->setText(tr("Disabled").toUtf8().data());
        char size[36];
        sprintf(size,"%lld GB",(_Partition->geom.length * Device->sector_size)/(1024*1024*1024));
        SizeLabel->setText(size);
        FileSystemLabel->setText(tr("Unknown"));
    }
    memcpy((void*)&Partition,(void*)_Partition,sizeof(PedPartition));
    PartitionLabel->setGeometry(0,0,50,20);
    PartitionLabel->show();
}

PedPartition PartitionItem::GetPartition(){
    return Partition;
}

void PartitionItem::SetUnselected(bool Status){
    if(Status == true)
        this->setStyleSheet("border:none");
    else
        this->setStyleSheet("border:1px solid black");
}

void PartitionItem::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit clicked(Partition);
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
    FriendLabelList->resize(1,1);
    List = new QScrollArea(this);
    List->setWidget(FriendLabelList);
    FriendLabelList->show();
    List->show();
    this->show();
    PartitionCount = 0;
    NowSelected = new PedPartition;
    bzero(NowSelected,sizeof(PedPartition));
}

void PartitionList::AddPartition(PedPartition *_Partition, PedDevice *Device){
    if ((_Partition->type & PED_PARTITION_METADATA) ||
                    (_Partition->type & PED_PARTITION_EXTENDED))
        return;
     PartitionItem *f = new PartitionItem(this);
     PartitionCount++;
        f->SetPartiton(_Partition,Device);
     FriendLabelList->resize(List->width()-20,_FRIEND_LABEL_HEIGTH*PartitionCount);
     PartitionLayout->addWidget(f);
     this->connect(f,SIGNAL(clicked(PedPartition)),this,SLOT(ItemClicked(PedPartition)));
     PartitionMap[PartitionCount] = f;
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

void PartitionList::ItemClicked(PedPartition Partition){
    if(PartitionMap.isEmpty() == false){
        for(Result = PartitionMap.begin();Result != PartitionMap.end();Result++)
            Result.value()->SetUnselected(true);
    }
    if(Partition.type == PED_PARTITION_NORMAL){
        emit SetChangeButtonDisabled(false);
        emit SetAddButtonDisabled(true);
        emit SetDelButtonDisabled(false);
    }else if(Partition.type == PED_PARTITION_FREESPACE){
        emit SetChangeButtonDisabled(true);
        emit SetAddButtonDisabled(false);
        emit SetDelButtonDisabled(true);
    }else{
        emit SetChangeButtonDisabled(true);
        emit SetAddButtonDisabled(true);
        emit SetDelButtonDisabled(true);
    }
    memcpy((void*)NowSelected,(void*)&Partition,sizeof(PedPartition));
}

PedPartition PartitionList::GetPartitionDataByUID(uint32_t UID){
    Result = PartitionMap.find(UID);
    return Result.value()->GetPartition();
}

PedPartition PartitionList::GetCurrentSelectedPartition(){
    return *NowSelected;
}
