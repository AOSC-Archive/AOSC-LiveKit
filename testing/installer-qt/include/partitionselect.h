#ifndef PARTITIONSELECT_H
#define PARTITIONSELECT_H

#include <QScrollArea>
#include <QtGui>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QMenu>
#include <parted/parted.h>
#include <QHBoxLayout>
#include <QLabel>

#define _FRIEND_LABEL_HEIGTH    40

class PartitionItem : public QWidget{
    Q_OBJECT
public:
    explicit        PartitionItem(QWidget *parent = 0);
    void            SetPartiton(PedPartition *_Partiton, PedDevice *Device);
    PedPartition    GetPartition(void);
    void            SetUnselected(bool);
signals:
    void clicked(PedPartition);
protected:
    QHBoxLayout     *layout;
    PedPartition     Partition;
    QLabel          *PartitionLabel;
    QLabel          *FileSystemLabel;
    QLabel          *SizeLabel;
    virtual void mousePressEvent(QMouseEvent *event);
};



class PartitionList : public QWidget{
    Q_OBJECT
public:
    explicit        PartitionList(QWidget *parent = 0);
    void            ClearPartitionList(void);
    void            AddPartition(PedPartition *_Partition, PedDevice *Device);
    void            resizeEvent(QResizeEvent *);
    void            SetPartitionCount(int n);
    int             GetPartitionCount(void);

    PedPartition    GetPartitionDataByUID(uint32_t UID);
    PedPartition    GetCurrentSelectedPartition(void);
public slots:
    void            ItemClicked(PedPartition);
signals:
    void            SetAddButtonDisabled(bool);
    void            SetDelButtonDisabled(bool);
    void            SetChangeButtonDisabled(bool);
protected:
    int             PartitionCount;
    typedef         QMap<int,PartitionItem *>   _Map;
    QScrollArea         *List;
    PedPartition        *NowSelected;
    QWidget             *PartitionWidget;
    QWidget             *FriendLabelList;
    QVBoxLayout         *PartitionLayout;
    _Map                PartitionMap;
    _Map::iterator      Result;
};


#endif // PARTITIONSELECT_CPP
