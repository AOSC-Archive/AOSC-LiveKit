#ifndef WORKPROCESSTAB_H
#define WORKPROCESSTAB_H

#include <QWidget>

namespace Ui {
class WorkProcessTab;
}

class WorkProcessTab : public QWidget
{
    Q_OBJECT

public:
    explicit WorkProcessTab(QWidget *parent = 0);
    ~WorkProcessTab();

private:
    Ui::WorkProcessTab *ui;
};

#endif // WORKPROCESSTAB_H
