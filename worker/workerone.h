#ifndef WORKERONE_H
#define WORKERONE_H

#include <QObject>

class WorkerOne : public QObject
{
    Q_OBJECT
public:
    explicit WorkerOne(QObject *parent = nullptr);

signals:

};

#endif // WORKERONE_H
