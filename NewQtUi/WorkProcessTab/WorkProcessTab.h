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
    void SetFormat(QString,QString);
    void SetTotalFiles(int);
    void SetNowCopyed(int);
    void SetProcessBarShow(bool);
    void SetLabelText(QString);
public slots:
    void SLOT_StartButtonClicked(void);
    void SLOT_CopyDone(int);

signals:
    void SIG_StartButtonClicked(void);
    void SIG_StartButtonClicked_WithFormat(void);

private:
    Ui::WorkProcessTab *ui;
    QByteArray Data;
    bool isFormat;
};

#endif // WORKPROCESSTAB_H
