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

#define _FRIEND_LABEL_HEIGTH    35

class PartitionItem : public QWidget{
    Q_OBJECT
public:
    explicit        PartitionItem(QWidget *parent = 0);
    void            SetPartiton(PedPartition *_Partiton, PedDevice *Device, int MountPoint);
    PedPartition    GetPartition(void);
    int             GetMountPoint(void);
    void            SetUnselected(bool);
    void            SetMountPoint(int);
signals:
    void clicked(PartitionItem*);
protected:
    QHBoxLayout     *layout;
    PedPartition     Partition;
    int              MountPoint;
    QLabel          *PartitionLabel;
    QLabel          *FileSystemLabel;
    QLabel          *SizeLabel;
    QLabel          *MountPointLabel;
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
    int             GetCurrentMountPoint(void);

    void            SetCurrentMountPoint(int);

    void            RefreshList(void);
public slots:
    void            ItemClicked(PartitionItem*);
signals:
    void            SetAddButtonDisabled(bool);
    void            SetDelButtonDisabled(bool);
    void            SetChangeButtonDisabled(bool);
protected:
    int             PartitionCount;
    typedef         QMap<int,PartitionItem *>   _Map;
    typedef         QMap<int,QString>               _MountPointMap;
    QScrollArea         *List;
    PartitionItem       *CurrentSelelcted;
    int                  NowMountPoint;
    QWidget             *PartitionWidget;
    QWidget             *FriendLabelList;
    QVBoxLayout         *PartitionLayout;
    _Map                PartitionMap;
    _Map::iterator      Result;
    _MountPointMap      MountPointMap;
    _MountPointMap::iterator    MountPointIterator;
};


#endif // PARTITIONSELECT_CPP
