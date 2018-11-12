#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sqlconnection.h"

#include <QFontDatabase>
#include <QMainWindow>
#include <QSettings>
#include <QSqlQueryModel>

namespace Ui {
class MainWindow;
}

const QString APP_NAME = "Visual SQL";
const QString APP_VENDOR = "Kilab";
const QString APP_VERSION = "0.0.0";
const QString APP_HOMEPAGE_URL = "https://visualsql.kilab.pl";

// TODO: Sprawdzić, czy dobrze wybiera
const QFont FIXED_FONT = QFontDatabase::systemFont(QFontDatabase::FixedFont);

const QString URL_DOC_MARIADB = "https://mariadb.com/kb/en/library/sql-statements-structure/";
const QString URL_DOC_MYSQL = "https://dev.mysql.com/doc/";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CurrentConnection currentConnection;
    QSettings settings;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void prepareLayout();
    void openAboutDialog();
    void openConnectionsDialog();
    void openURL(QString url);
    void setActionTriggers();
    void dbQuery(QString query);
};

#endif // MAINWINDOW_H
