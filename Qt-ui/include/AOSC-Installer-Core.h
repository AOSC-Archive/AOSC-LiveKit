#ifndef _AOSC_INSTALLER_CORE_H_
#define _AOSC_INSTALLER_CORE_H_

#define _EN_LIVE_CD_    0
#define _INSTALL_FILE_  "/INSTALL_FILE"

class AOSC_Installer_Core{
public:
    AOSC_Installer_Core(void);
//##### Step ######//
    int Check_Environment(void);
};

#endif
