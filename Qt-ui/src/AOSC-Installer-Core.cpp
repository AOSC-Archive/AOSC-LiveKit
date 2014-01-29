#include <unistd.h>
#include <stdio.h>
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
