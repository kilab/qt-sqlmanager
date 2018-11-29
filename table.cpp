#include "table.h"

Table::Table() {}

Table::Table(QString name) {
    this->name = name;
}

QString Table::getName() const
{
    return name;
}

Database Table::getDatabase() const
{
    return database;
}

void Table::setName(const QString &value)
{
    name = value;
}

void Table::setDatabase(const Database &value)
{
    database = value;
}

QString Table::getComment() const
{
    return comment;
}

void Table::setComment(const QString &value)
{
    comment = value;
}

QString Table::getEngine() const
{
    return engine;
}

void Table::setEngine(const QString &value)
{
    engine = value;
}

QString Table::getCollaction() const
{
    return collaction;
}

void Table::setCollaction(const QString &value)
{
    collaction = value;
}

int Table::getAutoIncrement() const
{
    return autoIncrement;
}

void Table::setAutoIncrement(int value)
{
    autoIncrement = value;
}
