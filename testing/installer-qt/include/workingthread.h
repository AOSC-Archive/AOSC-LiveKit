#ifndef WORKINGTHREAD_H
#define WORKINGTHREAD_H

#include <QString>
#include <QThread>

class WorkingThread : public QThread{
    Q_OBJECT
public:
    explicit WorkingThread(QThread *parent = 0);
    ~WorkingThread();
    void    SetWork(QString);
    void    run();
private:
    QString Work;
};

#endif // WORKINGTHREAD_H
