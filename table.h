#ifndef TABLE_H
#define TABLE_H

#include "database.h"

#include <QString>

class Table
{
public:
    Table();

    Table(QString name);

    QString getName() const;
    void setName(const QString &value);

    Database getDatabase() const;
    void setDatabase(const Database &value);

    QString getComment() const;
    void setComment(const QString &value);

    QString getEngine() const;
    void setEngine(const QString &value);

    QString getCollaction() const;
    void setCollaction(const QString &value);

    int getAutoIncrement() const;
    void setAutoIncrement(int value);

private:
    QString name;

    Database database;

    QString comment;

    QString engine;

    QString collaction;

    int autoIncrement;
};

#endif // TABLE_H
