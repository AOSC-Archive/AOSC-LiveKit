#ifndef CONFIGUREUSERTAB_H
#define CONFIGUREUSERTAB_H

#include <QWidget>

namespace Ui {
class ConfigureUserTab;
}

class ConfigureUserTab : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigureUserTab(QWidget *parent = 0);
    ~ConfigureUserTab();

private:
    Ui::ConfigureUserTab *ui;
};

#endif // CONFIGUREUSERTAB_H
