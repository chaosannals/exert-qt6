#include "workercmd.h"

WorkerCmd::WorkerCmd(QObject *parent) : QThread(parent)
{

}

/**
 * 执行命令并获取输出。
 * @brief exec
 * @param cmd
 * @param args
 * @return
 */
QString WorkerCmd::runCommand(const QString &pwd, const QString &cmd, const QStringList &args) {
    QProcess process;
    QString result;
    QTextStream stream(&result);
    connect(&process, &QProcess::readyReadStandardOutput, this, [&]() {
        stream << process.readAllStandardOutput();
    });
    connect(&process, &QProcess::readyReadStandardError, this, [&]() {
        stream << process.readAllStandardError();
    });
    process.setWorkingDirectory(pwd);
    process.start(cmd, args);
    process.waitForStarted();
    process.waitForFinished(-1);
    return result;
}
