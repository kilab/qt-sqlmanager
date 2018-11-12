#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "connectionsdialog.h"
#include "sqlconnection.h"

#include <QDebug>
#include <QDesktopServices>
#include <QFontDatabase>
#include <QLabel>
#include <QSettings>
#include <QUrl>
#include <QSqlQuery>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->prepareLayout();
    this->setActionTriggers();

    ConnectionsDialog connectionsDialog;
    connectionsDialog.exec();

    currentConnection = connectionsDialog.currentConnection;

    qDebug() << "Connection name: " << currentConnection.name;

    if (currentConnection.name == "") {
        // TODO: ogarnąć zamknięcie bo żaden sposób nie działa :/
        QApplication::exit();
        MainWindow::close();
        close();
    }

    ui->Input_Logs->append(tr("# Connected to: %1").arg(currentConnection.hostname));

    dbQuery("SELECT table_schema, table_name FROM information_schema.tables;");

    QSqlQuery queryDatabases, queryTables;
    queryDatabases.exec("SELECT DISTINCT table_schema FROM information_schema.tables;");
    queryTables.exec("SELECT table_schema, table_name FROM information_schema.tables;");


    QFont parentItemFont;
    parentItemFont.setBold(true);

    QTreeWidgetItem * parentItem = new QTreeWidgetItem();
    parentItem->setText(0, currentConnection.name);
    parentItem->setFont(0, parentItemFont);

    ui->Tree_Structure->insertTopLevelItem(0, parentItem);

    while (queryDatabases.next()) {
        QString databaseName = queryDatabases.value(0).toString();
        QTreeWidgetItem * databaseItem = new QTreeWidgetItem();

        databaseItem->setText(0, databaseName);

        while (queryTables.next()) {
            QString tableName = queryTables.value(1).toString();

            if (databaseName == queryTables.value(0).toString()) {
                QTreeWidgetItem * tableItem = new QTreeWidgetItem();
                tableItem->setText(0, tableName);

                databaseItem->addChild(tableItem);
            }
        }

        parentItem->addChild(databaseItem);
    }
}

void MainWindow::openURL(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::openAboutDialog()
{   
    AboutDialog aboutDialog;
    aboutDialog.exec();
}

void MainWindow::openConnectionsDialog()
{
    ConnectionsDialog connectionsDialog;
    connectionsDialog.exec();
}

void MainWindow::prepareLayout()
{
    QList<int> topSplitterSizes = {200, 400};
    QList<int> mainSplitterSizes = {220, 80};

    ui->Splitter_Top->setSizes(mainSplitterSizes);
    ui->Splitter_Main->setSizes(mainSplitterSizes);

    QWidget *widgetSplitterMain = ui->Splitter_Main->widget(0);
    QSizePolicy policySplitterMain = widgetSplitterMain->sizePolicy();
    policySplitterMain.setVerticalStretch(1);
    widgetSplitterMain->setSizePolicy(policySplitterMain);

    QWidget *widgetSplitterTop = ui->Splitter_Top->widget(1);
    QSizePolicy policySplitterTop = widgetSplitterTop->sizePolicy();
    policySplitterTop.setHorizontalStretch(1);
    widgetSplitterTop->setSizePolicy(policySplitterTop);

    ui->Input_Logs->setFontFamily(FIXED_FONT.toString());
}

void MainWindow::setActionTriggers()
{
    connect(ui->Menu_Help_AboutVisual_SQL, &QAction::triggered, this, &MainWindow::openAboutDialog);
    connect(ui->Menu_File_Connections, &QAction::triggered, this, &MainWindow::openConnectionsDialog);
    connect(ui->Menu_Help_MariaDB_documentation, &QAction::triggered, this, [this]{ MainWindow::openURL(URL_DOC_MARIADB); });
    connect(ui->Menu_Help_MariaDB_documentation, &QAction::triggered, this, [this]{ MainWindow::openURL(URL_DOC_MYSQL); });
}

void MainWindow::dbQuery(QString query) {
    QSqlQueryModel model;
    QSqlQuery sqlQuery;

    // TODO: dokończyć

    ui->Input_Logs->append(query);
}

MainWindow::~MainWindow()
{
    delete ui;
}

