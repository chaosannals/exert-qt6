#ifndef WORKERCMD_H
#define WORKERCMD_H

#include <QThread>
#include <QProcess>
#include <QTextStream>
#include <QList>
#include <QStringList>

class WorkerCmd : public QThread
{
    Q_OBJECT
public:
    explicit WorkerCmd(QObject *parent = nullptr);

    QString runCommand(const QString &pwd, const QString &cmd, const QStringList &args);

    void setWorkDir(const QString &dir) {
        workdir = dir;
    }
signals:
private:
    QString workdir;
};

#endif // WORKERCMD_H
