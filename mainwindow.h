#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sqlconnection.h"
#include "database.h"
#include "table.h"

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
const QString APP_HOMEPAGE_URL = "https://bitbucket.org/kilab/visual-sql";
const QString URL_DOC_MARIADB = "https://mariadb.com/kb/en/library/sql-statements-structure/";
const QString URL_DOC_MYSQL = "https://dev.mysql.com/doc/";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CurrentConnection currentConnection;

    Database currentDatabase;

    Table currentTable;

    QMap<QString, QStringList> dbSchema;

    QSettings settings;

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_Input_Filter_textChanged(const QString &arg1);

    void on_Tree_Structure_itemSelectionChanged();

private:
    Ui::MainWindow *ui;

    void connectToDatabase(CurrentConnection currentConnection);

    void executeCustomQuery();

    void prepareLayout();

    void openAboutDialog();

    void openConnectionsDialog();

    void openURL(QString url);

    void setActionTriggers();

    QList<QString> availableTableEngines = {};

    QList<QString> availableTableCollactions = {};

    QVector<QStringList> dbQuery(QString query);

    QSqlQueryModel dbModel;

    QSqlQueryModel dbModelCustomQuery;
};

#endif // MAINWINDOW_H
