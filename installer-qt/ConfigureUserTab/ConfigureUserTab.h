#ifndef CONFIGUREUSERTAB_H
#define CONFIGUREUSERTAB_H

#include <QWidget>

#define NO_ROOT_PASS        1
#define NO_USER_NAME        2
#define NO_USER_PASS        3
#define ROOT_PASS_NOT_MATCH 4
#define USER_PASS_NOT_MATCH 5
#define USER_NAME_HAS_SPACE 6

namespace Ui {
class ConfigureUserTab;
}

class ConfigureUserTab : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigureUserTab(QWidget *parent = 0);
    ~ConfigureUserTab();
    int CheckInput(void);
    QString GetUserName(void);
    QString GetUserPass(void);
    QString GetRootPass(void);

private:
    Ui::ConfigureUserTab *ui;
};

#endif // CONFIGUREUSERTAB_H
