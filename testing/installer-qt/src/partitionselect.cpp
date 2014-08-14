#include "partitionselect.h"
#include <stdio.h>
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
    this->setStyleSheet("border:1px solid black");
    PartitionPath = new QLabel(this);
    layout        = new QHBoxLayout(this);
    this->setLayout(layout);
    layout->addWidget(PartitionPath);
}
void PartitionItem::SetPartiton(const PedPartition _Partition){
    memcpy((void*)&_Partition,(void*)&Partition,sizeof(PedPartition));
    PartitionPath->setText("Hello");
    PartitionPath->setGeometry(0,0,50,20);
    PartitionPath->show();
}

PedPartition PartitionItem::GetPartition(){
    return Partition;
}

void PartitionItem::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit clicked(Partition);
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
}

void PartitionList::AddPartition(PedPartition _Partition){
     PartitionItem *f = new PartitionItem(this);
     f->SetPartiton(_Partition);
     FriendLabelList->resize(List->width()-20,_FRIEND_LABEL_HEIGTH*PartitionCount);
     PartitionLayout->addWidget(f);
     this->connect(f,SIGNAL(clicked(PedPartition)),this,SLOT(ItemClicked(PedPartition)));
     PartitionMap[_Partition.num] = f;
}

void PartitionList::ClearPartitionList(){
    if(PartitionMap.isEmpty() == false){
        for(Result = PartitionMap.begin();Result != PartitionMap.end();Result++)
            delete Result.value();
        PartitionMap.clear();
        PartitionCount = 0;
    }
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

void PartitionList::ItemClicked(PedPartition Data){
}

PedPartition PartitionList::GetPartitionDataByUID(uint32_t UID){
    Result = PartitionMap.find(UID);
    return Result.value()->GetPartition();
}
