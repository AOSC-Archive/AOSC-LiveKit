# How To Work

##  基本类

###     InstallerMain   安装器主体
---
####    函数

>>   AddPage(QWidget *)

> 添加一个页面[按照顺序]，也就是说AddPage函数执行的先后顺序决定了Pages呈现的顺序

>>   DelPage(QWidget *)

>      删除指定页面

####    接口信号

>>   SIGN_PageChanged(QWidget *)

>      页面更换到(这个信号在AddPage(QWidget*)中默认与到virtual void InstallerPage::SLOT_PageChanged)，可是默认没有任何操作

####    接口槽

>>   SLOT_TurnToNextPage(void)

>      转向下一个页面(这个信号在构造函数中和InstallerMain::NextButton的clicked()信号相链接)

>>   SLOT_TurnToPervPage(void)

>      转向上一个页面(这个信号在构造函数中和InstallerMain::PervButton的clicked()信号相链接)

>>   SLOT_SLOT_TurnToSpecifyPage(QWidget*)

>      跳转向指定页面(怎样用还没想好)

>>   SLOT_SetNextButtonDisabel(bool)

>      设置InstallerMain::NextButton的不可点击状态(在InstallerMain::AddPage(QWidget *)中默认与InstallerPage::SIGN_SetNextButtonDisable(void)链接，true时禁用按钮，flase时启用按钮)

>>   SLOT_SetPervButtonDisabel(bool)

>      设置InstallerMain::PervButton的不可点击状态(在InstallerMain::AddPage(QWidget *)中默认与InstallerPage::SIGN_SetPervButtonDisable(void)链接，true时禁用按钮，flase时启用按钮)

###   InstallerPage   每个页面[也就是比如分区页面等]
---
####    函数

>>   virtual void PervShow();

>      在切换到这个Page的时候执行相应的操作(例如禁用按钮，输出信息等)。本函数为虚函数，需要重新编写

####    接口信号

>>   void    SIGN_SetNextButtonDisable(bool);

>      设置InstallerMain::NextButton的不可点击状态(在InstallerMain::AddPage(QWidget *)中默认与InstallerPage::SIGN_SetNextButtonDisable(void)链接，true时禁用按钮，flase时启用按钮)

>>   void    SIGN_SetPervButtonDisable(bool);

>      设置InstallerMain::PervButton的不可点击状态(在InstallerMain::AddPage(QWidget *)中默认与InstallerPage::SIGN_SetPervButtonDisable(void)链接，true时禁用按钮，flase时启用按钮)

####    接口槽

>>   virtual void SLOT_NextButtonClicked(void); 

>      当 InstallerMain::NextButton 按下时所执行的操作(这个槽在InstallerMain::TurnToNextPage(void)中与InstallerMain::NextButton链接，当切换到其他Page时，断开链接。本槽函数是虚函数，需要重新编写)

>>     virtual void SLOT_PageChanged(QWidget *);

>      当 InstallerMain::TurnToNextPage(void) 执行后当前的Page的信息(这个槽在InstallerMain::AddPage(QWidget*)中与Installer::SIGN_PageChanged(QWidget*)链接。本槽函数是虚函数，需要重新编写)
