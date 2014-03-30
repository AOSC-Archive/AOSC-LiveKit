#ifndef GETSTARTTAB_H
#define GETSTARTTAB_H

#include <QWidget>

namespace Ui {
class GetStartTab;
}

class GetStartTab : public QWidget
{
    Q_OBJECT

public:
    explicit GetStartTab(QWidget *parent = 0);
    ~GetStartTab();

private:
    Ui::GetStartTab *ui;
};

#endif // GETSTARTTAB_H
