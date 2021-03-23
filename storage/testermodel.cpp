#include "testermodel.h"

QSqlDatabase TesterModel::database;

TesterModel::TesterModel(int id) :  id(id)
{

}

void TesterModel::init() {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("tester.db");
    if (database.open()) {
        database.exec("CREATE TABLE IF NOT EXISTS tester ( \
            id         INTEGER  PRIMARY KEY ASC AUTOINCREMENT, \
            account    STRING   UNIQUE \
                                NOT NULL, \
            password   STRING, \
            nickname   STRING, \
            created_at DATETIME DEFAULT ( (datetime('now', 'localtime') ) ) \
        );");
        database.close();
    }
}

QList<TesterModel> TesterModel::find(const QString &plain) {
    if (database.open()) {
        QSqlQuery query;
        QString sql = plain.isEmpty() ?
                    "SELECT * FROM tester" :
                    QString("SELECT * FROM tester WHERE account LIKE '%1' OR nickname LIKE '%%%1%%'").arg(plain);
        query.exec(sql);
        QList<TesterModel> result;
        while (query.next()) {
            TesterModel item(query.value(0).toInt());
            item.setAccount(query.value(1).toString());
            item.setPassword(query.value(2).toString());
            item.setNickName(query.value(3).toString());
            item.setCreatedAt(query.value(4).toDateTime());
            result.append(item);
        }
        database.close();
        return result;
    }
    throw 1;
}

void TesterModel::save() {
    if (database.open()) {
        QSqlQuery query;
        QString sql = id == 0 ?
           QString("INSERT INTO tester(account, password, nickname, created_at) VALUES ('%1', '%2', '%3', '%4')")
                  .arg(account, password, nickname, created_at.toString()) :
           QString("UPDATE tester SET account='%1', password='%2', nickname='%3', created_at='%4' WHERE id=%5")
                   .arg(account, password, nickname,created_at.toString()).arg(id);
        query.exec(sql);
        if (id == 0) {
            id = query.lastInsertId().toInt();
        }
        database.close();
    }
}
