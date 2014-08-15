#include "dialogbox.h"
#include <stdio.h>
#include <string.h>
#include <QThread>

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

    DoWork           = new WorkingDialog;

    FileSystemSelect = new QComboBox(this);
    MountPointSelect = new QComboBox(this);
    MountPointLabel  = new QLabel(this);
    PartitionPath    = new QLabel(this);
    FileSystemLabel  = new QLabel(this);
    DoFormatLabel    = new QLabel(this);
    PartitionSizeLabel=new QLabel(this);
    DoFormatCheckBox = new QCheckBox(this);
    PartitionSize    = new QSpinBox(this);

    PartitionPath->setGeometry(35,10,200,20);
    FileSystemLabel->setGeometry(35,40,95,20);
    FileSystemSelect->setGeometry(130,40,75,20);
    MountPointLabel->setGeometry(35,60,95,20);
    MountPointSelect->setGeometry(130,60,75,20);
    DoFormatLabel->setGeometry(35,80,75,20);
    DoFormatCheckBox->setGeometry(130,80,110,20);
    PartitionSizeLabel->setGeometry(35,100,75,20);
    PartitionSize->setGeometry(130,100,75,20);


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

    PartitionSizeLabel->setText(tr("Size(MB)"));



    this->connect(ApplyButton,SIGNAL(clicked()),this,SLOT(ApplyButtonClicked()));
    this->connect(CancelButton,SIGNAL(clicked()),this,SLOT(CancelButtonClicked()));
    this->connect(FileSystemSelect,SIGNAL(currentIndexChanged(int)),this,SLOT(FileSystemSelectChanged(int)));
    this->connect(DoWork,SIGNAL(Stoped(int)),this,SLOT(FormatDone(int)));

}

ChangeDialogBox::~ChangeDialogBox(){

}

void ChangeDialogBox::SetCurrentPartition(PedPartition Partition, PedDisk Disk, PedDevice Device,int MountPoint, int _WorkType){
    memcpy((void*)&CurrentPartition,(void*)&Partition,sizeof(PedPartition));
    memcpy((void*)&CurrentDisk,(void*)&Disk,sizeof(PedDisk));
    memcpy((void*)&CurrentDevice,(void*)&Device,sizeof(PedDevice));
    WorkType = _WorkType;
    OriginMountPoint =MountPoint;
    char Name[64];
    sprintf(Name,"%s :%s",tr("Partition path").toUtf8().data(),ped_partition_get_path(&Partition));
    PartitionPath->setText(Name);
    if(MountPoint > 0){
        if(MountPoint == INSTALLER_MOUNT_POINT_ROOT){
            MountPointSelect->insertItem(MountPoint,tr("/"));
        }else if(MountPoint == INSTALLER_MOUNT_POINT_HOME){
            MountPointSelect->insertItem(MountPoint,tr("/home"));
        }
    }
    MountPointSelect->setCurrentIndex(MountPoint);
    PartitionSize->setRange(0,(CurrentPartition.geom.length * CurrentDevice.sector_size)/(1024*1024));
    PartitionSize->setValue((CurrentPartition.geom.length * CurrentDevice.sector_size)/(1024*1024));
    if(WorkType == INSTALLER_WORKTYPE_ADD){
        OriginFileSystem = INSTALLER_FILESYSTEM_FREESPACE;
        FileSystemSelect->setCurrentIndex(INSTALLER_FILESYSTEM_EXT4);
        return;
    }else if(Partition.fs_type != NULL){
        if(strcmp(Partition.fs_type->name,"ext2") == 0)          OriginFileSystem = INSTALLER_FILESYSTEM_EXT2;
        else if(strcmp(Partition.fs_type->name,"ext3") == 0)     OriginFileSystem = INSTALLER_FILESYSTEM_EXT3;
        else if(strcmp(Partition.fs_type->name,"ext4") == 0)     OriginFileSystem = INSTALLER_FILESYSTEM_EXT4;
        else if(strcmp(Partition.fs_type->name,"ntfs") == 0)     OriginFileSystem = INSTALLER_FILESYSTEM_NTFS;
        else if(strcmp(Partition.fs_type->name,"fat32")== 0)     OriginFileSystem = INSTALLER_FILESYSTEM_FAT32;
        FileSystemSelect->setCurrentIndex(OriginFileSystem);
    }else{
        OriginFileSystem = INSTALLER_FILESYSTEM_NONE;
        FileSystemSelect->setCurrentIndex(INSTALLER_FILESYSTEM_EXT4);
    }
}

void ChangeDialogBox::FormatDone(int Status){
    if(Status != 0){
        QMessageBox::warning(this,tr("Warning"),tr("Format failure!"),QMessageBox::Yes);
    }else{
        QMessageBox::information(this,tr("Information"),tr("Format success!"),QMessageBox::Yes);
    }
    this->close();
    emit WorkDone();
}

void ChangeDialogBox::ApplyButtonClicked(){
    emit MountPointChangeApplied(MountPointSelect->currentIndex());
    if(MountPointSelect->currentIndex()>0){
        MountPointSelect->removeItem(MountPointSelect->currentIndex());
    }
    if(DoFormatCheckBox->isChecked() == false){
        this->close();
    }else{
        if(WorkType == INSTALLER_WORKTYPE_ADD){
            PedPartition *NewPartition;
            PedFileSystemType *fstype = ped_file_system_type_get("msdos");
            int ToEnd = (((CurrentPartition.geom.length * CurrentDevice.sector_size)/(1024*1024) - PartitionSize->value()))
                                                                *(1024*1024)/CurrentDevice.sector_size;
            NewPartition = ped_partition_new(&CurrentDisk,PED_PARTITION_NORMAL,fstype,CurrentPartition.geom.start,CurrentPartition.geom.end - ToEnd);
            if(NewPartition){
                ped_disk_add_partition(&CurrentDisk,NewPartition,ped_constraint_exact(&NewPartition->geom));
                ped_disk_commit_to_dev(&CurrentDisk);
                ped_disk_commit_to_os(&CurrentDisk);
            }
            char Name[64];
            bzero(Name,64);
            sprintf(Name,"%s :%s",tr("Partition path").toUtf8().data(),ped_partition_get_path(NewPartition));
            PartitionPath->setText(Name);
            char Work[64];
            bzero(Work,64);
            sprintf(Work,"mkfs.%s %s -F",FileSystemSelect->currentText().toUtf8().data(),ped_partition_get_path(NewPartition));
            DoWork->SetWork(tr(Work));
            DoWork->SetWorkingtText(tr("Formating......"));
            DoWork->Start();
            return;
        }
        char Work[64];
        bzero(Work,64);
        sprintf(Work,"mkfs.%s %s -F",FileSystemSelect->currentText().toUtf8().data(),ped_partition_get_path(&CurrentPartition));
        DoWork->SetWork(tr(Work));
        DoWork->SetWorkingtText(tr("Formating......"));
        DoWork->Start();
    }
}

void ChangeDialogBox::CancelButtonClicked(){
    if(OriginMountPoint > 0){
        MountPointSelect->removeItem(OriginMountPoint);
    }
    this->close();
}

void ChangeDialogBox::FileSystemSelectChanged(int Now){
    if(Now != OriginFileSystem){
        DoFormatCheckBox->setDisabled(true);
        DoFormatCheckBox->setChecked(true);
    }else{
        DoFormatCheckBox->setDisabled(false);
    }
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
