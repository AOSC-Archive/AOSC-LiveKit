#ifndef WORKDONETAB_H
#define WORKDONETAB_H

#include <QWidget>

namespace Ui {
class WorkDoneTab;
}

class WorkDoneTab : public QWidget
{
    Q_OBJECT

public:
    explicit WorkDoneTab(QWidget *parent = 0);
    ~WorkDoneTab();

private:
    Ui::WorkDoneTab *ui;
};

#endif // WORKDONETAB_H
