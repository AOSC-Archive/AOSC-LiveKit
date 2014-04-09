#include "PartedDiskTab.h"
#include "ui_PartedDiskTab.h"

PartedDiskTab::PartedDiskTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PartedDiskTab)
{
    ui->setupUi(this);
    ui->MyDeviceIsEFIComboBox->hide();
    ui->FormatPartitionSelect->hide();
    ui->MyDeviceIsEFILabel->hide();
    ui->FileSystemTypeLabel->hide();
    this->connect(ui->MyDeviceIsEFICheckBox,SIGNAL(clicked(bool)),this,SLOT(SLOT_MyDeviceIsEFICheckBoxClicked(bool)));
    this->connect(ui->FormatCheckBox,SIGNAL(clicked(bool)),this,SLOT(SLOT_FormatDiskPartitionCheckBoxClicked(bool)));
    this->connect(ui->PartitionDiskButton,SIGNAL(clicked()),this,SLOT(SLOT_PartitionDiskButtonClicked()));
    this->UpdatePartitionMap();
    this->UpdateDiskMap();
    this->UpdateEFIPartitionMap();
}

PartedDiskTab::~PartedDiskTab()
{
    delete ui;
}

void PartedDiskTab::SLOT_FormatDiskPartitionCheckBoxClicked(bool Status){
    if(Status == true){
        ui->FormatPartitionSelect->show();
        ui->FileSystemTypeLabel->show();
    }else{
        ui->FormatPartitionSelect->hide();
        ui->FileSystemTypeLabel->hide();
    }
}

void PartedDiskTab::SLOT_MyDeviceIsEFICheckBoxClicked(bool Status){
    if(Status == true){
        ui->MyDeviceIsEFIComboBox->show();
        ui->MyDeviceIsEFILabel->show();
    }else{
        ui->MyDeviceIsEFIComboBox->hide();
        ui->MyDeviceIsEFILabel->hide();
    }
}

void PartedDiskTab::SLOT_PartitionDiskButtonClicked(){
    emit SIG_AskForHide();
    system("sudo gparted");
    this->UpdateDiskMap();
    this->UpdatePartitionMap();
    this->UpdateDiskMap();
    this->UpdateEFIPartitionMap();
    emit SIG_AskForShow();
}

void PartedDiskTab::UpdatePartitionMap(){
    ui->DiskPartitionSelect->clear();
    char ExecBuff[64];
    char TmpString[64];
    int TmpInt;
    FILE *fp;
    sprintf(ExecBuff,"ls /dev/sd?? > %s",_TMP_PARTITION_FILE_);
    system(ExecBuff);
    sprintf(ExecBuff,"ls /dev/sd??? >> %s",_TMP_PARTITION_FILE_);
    system(ExecBuff);
    fp = fopen(_TMP_PARTITION_FILE_,"r");
    ui->DiskPartitionSelect->insertItem(-1,tr("---"));
    bzero(TmpString,64);
    TmpInt = 0;
    while(fscanf(fp,"%s",TmpString) != EOF){
        ui->DiskPartitionSelect->insertItem(TmpInt,tr(TmpString));
        bzero(TmpString,64);
        TmpInt ++;
    }
    sprintf(ExecBuff,"rm -rf %s",_TMP_PARTITION_FILE_);
    system(ExecBuff);
}

void PartedDiskTab::UpdateDiskMap(){
    ui->DiskSelect->clear();
    char ExecBuff[64];
    char TmpString[64];
    int TmpInt;
    FILE *fp;
    sprintf(ExecBuff,"ls /dev/sd? > %s",_TMP_DISK_FILE_);
    system(ExecBuff);
    fp = fopen(_TMP_DISK_FILE_,"r");
    ui->DiskSelect->insertItem(-1,tr("---"));
    bzero(TmpString,64);
    TmpInt = 0;
    while(fscanf(fp,"%s",TmpString) != EOF){
        ui->DiskSelect->insertItem(TmpInt,tr(TmpString));
        bzero(TmpString,64);
        TmpInt ++;
    }
    sprintf(ExecBuff,"rm -rf %s",_TMP_DISK_FILE_);
    system(ExecBuff);
}

void PartedDiskTab::UpdateEFIPartitionMap(){
    ui->MyDeviceIsEFIComboBox->clear();
    char ExecBuff[64];
    char TmpString[64];
    int TmpInt;
    FILE *fp;
    sprintf(ExecBuff,"ls /dev/sd?? > %s",_TMP_EFI_PARTITION_FILE_);
    system(ExecBuff);
    sprintf(ExecBuff,"ls /dev/sd??? >> %s",_TMP_EFI_PARTITION_FILE_);
    system(ExecBuff);
    fp = fopen(_TMP_EFI_PARTITION_FILE_,"r");
    ui->MyDeviceIsEFIComboBox->insertItem(-1,tr("---"));
    bzero(TmpString,64);
    TmpInt = 0;
    while(fscanf(fp,"%s",TmpString) != EOF){
        ui->MyDeviceIsEFIComboBox->insertItem(TmpInt,tr(TmpString));
        bzero(TmpString,64);
        TmpInt ++;
    }
    sprintf(ExecBuff,"rm -rf %s",_TMP_EFI_PARTITION_FILE_);
    system(ExecBuff);
}

int PartedDiskTab::CheckInput(){
    if(ui->DiskPartitionSelect->currentText()=="---"){
        return NO_PARTITION_SELECT;
    }
    else if(ui->DiskSelect->currentText()=="---"){
        return NO_DISK_SELECT;
    }
    if(ui->MyDeviceIsEFICheckBox->isChecked() == true){
        if(ui->MyDeviceIsEFIComboBox->currentText()=="---"){
            return NO_EFI_PARTITION_SELECT;
        }
    }
    if(ui->FormatCheckBox->isChecked() == true){
        if(ui->FormatPartitionSelect->currentText()=="---"){
            return NO_FILESYSTEM_TYPE_SELECT;
        }
    }else{
        return NO_FORMAT;
    }
    return -1;
}
