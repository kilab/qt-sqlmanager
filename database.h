#ifndef DATABASE_H
#define DATABASE_H

#include <QString>

class Database
{
public:
    Database();

    Database(QString name);

    QString getHostname() const;
    void setHostname(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getCollaction() const;
    void setCollaction(const QString &value);

private:
    QString hostname;

    QString name;

    QString collaction;
};

#endif // DATABASE_H
