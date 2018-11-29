#include "database.h"

Database::Database() {}

Database::Database(QString name) {
    this->name = name;
}

QString Database::getHostname() const
{
    return hostname;
}

void Database::setHostname(const QString &value)
{
    hostname = value;
}

QString Database::getName() const
{
    return name;
}

void Database::setName(const QString &value)
{
    name = value;
}

QString Database::getCollaction() const
{
    return collaction;
}

void Database::setCollaction(const QString &value)
{
    collaction = value;
}
