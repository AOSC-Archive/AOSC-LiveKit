#include "dialogbox.h"

ChangeDialogBox::ChangeDialogBox(QWidget *parent):
    QWidget(parent){
    this->setMinimumSize(300,200);
    this->setMaximumSize(300,200);
    this->setWindowTitle(tr("Change partition"));
    ApplyButton     = new QPushButton(this);
    CancelButton    = new QPushButton(this);
    ApplyButton->setText(tr("Apply"));
    CancelButton->setText(tr("Cancel"));
    ApplyButton->setGeometry(160,160,60,30);
    CancelButton->setGeometry(230,160,60,30);

    FileSystemSelect = new QComboBox(this);
    MountPointSelect = new QComboBox(this);
    MountPointLabel  = new QLabel(this);
    PartitionPath    = new QLabel(this);
    FileSystemLabel  = new QLabel(this);
    DoFormatLabel    = new QLabel(this);
    DoFormatCheckBox = new QCheckBox(this);

    PartitionPath->setGeometry(35,10,200,20);
    FileSystemLabel->setGeometry(35,40,95,20);
    FileSystemSelect->setGeometry(130,40,75,20);
    MountPointLabel->setGeometry(35,60,95,20);
    MountPointSelect->setGeometry(130,60,75,20);
    DoFormatLabel->setGeometry(35,80,75,20);
    DoFormatCheckBox->setGeometry(130,80,110,20);




    PartitionPath->setText(tr("Partition path: /dev/sda1"));
    FileSystemLabel->setText(tr("Filesystem"));
    MountPointLabel->setText(tr("Mount point"));
    DoFormatLabel->setText(tr("Format"));

    FileSystemSelect->addItem(tr("ext2"));
    FileSystemSelect->addItem(tr("ext3"));
    FileSystemSelect->addItem(tr("ext4"));
    FileSystemSelect->addItem(tr("ntfs"));
    FileSystemSelect->addItem(tr("fat32"));

    MountPointSelect->addItem(tr("---"));
    MountPointSelect->addItem(tr("/"));
    MountPointSelect->addItem(tr("/home"));



    this->connect(ApplyButton,SIGNAL(clicked()),this,SLOT(ApplyButtonClicked()));
    this->connect(CancelButton,SIGNAL(clicked()),this,SLOT(CancelButtonClicked()));
}

ChangeDialogBox::~ChangeDialogBox(){

}

void ChangeDialogBox::SetCurrentPartition(PedPartition Data, int MountPoint){
    OriginMountPoint =MountPoint;
    char Name[64];
    sprintf(Name,"%s :%s",tr("Partition path").toUtf8().data(),ped_partition_get_path(&Data));
    PartitionPath->setText(Name);
    FileSystemSelect->setCurrentText(Data.fs_type->name);
    if(MountPoint > 0){
        if(MountPoint == INSTALLER_MOUNT_POINT_ROOT){
            MountPointSelect->insertItem(MountPoint,tr("/"));
        }else if(MountPoint == INSTALLER_MOUNT_POINT_HOME){
            MountPointSelect->insertItem(MountPoint,tr("/home"));
        }
    }
    MountPointSelect->setCurrentIndex(MountPoint);

}

void ChangeDialogBox::ApplyButtonClicked(){
    emit ChangeApplied(MountPointSelect->currentIndex());
    if(MountPointSelect->currentIndex()>0){
        MountPointSelect->removeItem(MountPointSelect->currentIndex());
    }
    this->hide();
}

void ChangeDialogBox::CancelButtonClicked(){
    if(OriginMountPoint > 0){
        MountPointSelect->removeItem(OriginMountPoint);
    }
    this->hide();
}


AddDialogBox::AddDialogBox(QWidget *parent):
    QWidget(parent){
    this->setMinimumSize(300,200);
    this->setMaximumSize(300,200);
    this->setWindowTitle(tr("New partition"));
    ApplyButton     = new QPushButton(this);
    CancelButton    = new QPushButton(this);
}

AddDialogBox::~AddDialogBox(){

}

void AddDialogBox::SetCurrentPartition(PedPartition){

}
