#ifndef TESTERMODEL_H
#define TESTERMODEL_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDateTime>
#include <QList>

class TesterModel
{
public:
    explicit TesterModel(int id=0);
    static void init();
    static QList<TesterModel> find(const QString &plain);
    void save();
    int getId() { return id; }
    QString getAccount() { return account; }
    QString getPassword() { return password; }
    QString getNickname() { return nickname; }
    QDateTime getCreatedAt() { return created_at; }

    void setAccount(const QString &v) { account = v; }
    void setPassword(const QString &v) { password = v; }
    void setNickName(const QString &v) { nickname = v; }
    void setCreatedAt(const QDateTime &v) { created_at = v; }
private:
    static QSqlDatabase database;
    int id;
    QString account;
    QString password;
    QString nickname;
    QDateTime created_at;
};

#endif // TESTERMODEL_H
