#ifndef WORKINGTHREAD_H
#define WORKINGTHREAD_H

#include <QString>
#include <QThread>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class WorkingThread : public QThread{
    Q_OBJECT
public:
    explicit WorkingThread(QThread *parent = 0);
    ~WorkingThread();
    void    SetWork(QString);
    void    run();
signals:
    void    WorkDone(int);
private:
    QString Work;
};

class WorkingDialog : public QWidget{
    Q_OBJECT
public:
    explicit WorkingDialog(QWidget *parent = 0);
    ~WorkingDialog();
    void    SetWork(QString);
    void    SetWorkingtText(QString);
signals:
    void    Started(void);
    void    Stoped(int);
public slots:
    void    Start(void);
    void    Stop(void);
    void    pWorkStarted(void);
    void    pWorkStoped(int);
private:
    WorkingThread   *Thread;
    QLabel          *WorkingDescription;
    QPushButton     *CancelButton;
    QPushButton     *DoneButton;
};

#endif // WORKINGTHREAD_H
