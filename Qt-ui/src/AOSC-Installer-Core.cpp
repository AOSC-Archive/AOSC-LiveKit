#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AOSC-Installer-Core.h"

AOSC_Installer_Core::AOSC_Installer_Core(void){

}

int AOSC_Installer_Core::Check_Environment(void){
    int result = access(_INSTALL_FILE_,0);
    if(result != F_OK){
        perror("Loading Install File ");
        return -1;
    }
    return _EN_LIVE_CD_;
}

int AOSC_Installer_Core::Find_Disk(char ***DP){     // BUG!!!!!!!!!!!
    int k=0;
    system("ls /dev/sd* > /tmp/.DiskParted.info");
    FILE *fp = fopen("/tmp/.DiskParted.info","r");
    char *Temp = (char *)malloc(2500);    // 50 x 50
    bzero(Temp,2500);
    int i = 0;
    char *DiskPath[50];
    DiskPath[0] = (char *)malloc(64);
    printf("Malloc OK\n");
    bzero(DiskPath[0],64);
    while(fscanf(fp,"%s",DiskPath[i]) != EOF){
        printf("%s\n",DiskPath[i]);
        DiskPath[i+1] = (char *)malloc(64);
        bzero(DiskPath[i+1],64);
        k++;
    }
    *DP = DiskPath;
    return k;
}
