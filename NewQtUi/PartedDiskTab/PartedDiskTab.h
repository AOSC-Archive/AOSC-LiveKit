#ifndef PARTEDDISKTAB_H
#define PARTEDDISKTAB_H

#include <QWidget>

namespace Ui {
class PartedDiskTab;
}

class PartedDiskTab : public QWidget
{
    Q_OBJECT

public:
    explicit PartedDiskTab(QWidget *parent = 0);
    ~PartedDiskTab();

private:
    Ui::PartedDiskTab *ui;
};

#endif // PARTEDDISKTAB_H
