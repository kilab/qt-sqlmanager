#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include "QList"
#include "QString"
#include "QSqlDatabase"

struct CurrentConnection {
    QString name;
    QString hostname;
    QSqlDatabase db;
};

enum SqlDriver { mysql, mariadb };

const QList<QString> SqlDriversString = { "MySQL", "MariaDB" };

class SqlConnection
{
public:

    SqlDriver driver;
    QString hostname;
    unsigned short int port;
    QString username;
    QString password;

    SqlConnection();
};

#endif // SQLCONNECTION_H
