#ifndef READINGTAB_H
#define READINGTAB_H

#include <QWidget>

namespace Ui {
class ReadingTab;
}

class ReadingTab : public QWidget
{
    Q_OBJECT

public:
    explicit ReadingTab(QWidget *parent = 0);
    ~ReadingTab();
    bool is_IAgreeCheckBox_Status(void);
signals:
    void SIGNAL_IAgreeCheckBoxClicked(bool);
public slots:
    void SLOT_IAgreeCheckBoxClicked(bool);

private:
    Ui::ReadingTab *ui;
};

#endif // READINGTAB_H
