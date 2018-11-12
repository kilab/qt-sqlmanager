#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "highlighter.h"
#include "connectionsdialog.h"
#include "sqlconnection.h"

#include <QCompleter>
#include <QDebug>
#include <QDesktopServices>
#include <QFontDatabase>
#include <QLabel>
#include <QSettings>
#include <QUrl>
#include <QSqlRecord>
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
        exit(0);
    }

    ui->Input_Logs->append(tr("# Connected to: %1").arg(currentConnection.hostname));

    QVector<QStringList> databases = dbQuery("SHOW DATABASES;");
    QVector<QStringList> databaseTables = dbQuery("SELECT `table_schema`, `table_name` FROM `information_schema`.`tables`;");
    QFont parentItemFont;
    parentItemFont.setBold(true);

    QTreeWidgetItem *parentItem = new QTreeWidgetItem();
    parentItem->setText(0, currentConnection.name);
    parentItem->setFont(0, parentItemFont);

    ui->Tree_Structure->insertTopLevelItem(0, parentItem);

    foreach (const QStringList &database, databases) {
        QTreeWidgetItem *databaseItem = new QTreeWidgetItem();

        databaseItem->setText(0, database.value(0));
        parentItem->addChild(databaseItem);
    }

    foreach (const QStringList &schema, databaseTables) {
        QTreeWidgetItem *tableItem = new QTreeWidgetItem();
        // TODO: check only one level (database level)
        QList<QTreeWidgetItem *> foundDatabaseItem = ui->Tree_Structure->findItems(schema.value(0), Qt::MatchContains|Qt::MatchRecursive, 0);

        tableItem->setText(0, schema.value(1));
        foundDatabaseItem.first()->addChild(tableItem);

        dbSchema[schema.value(0)] << schema.value(1);
    }

    QCompleter *completer = new QCompleter(dbSchema.keys());
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->Input_Filter->setCompleter(completer);
}

MainWindow::~MainWindow()
{
    delete ui;
    currentConnection.db.close();
    QSqlDatabase::removeDatabase("QMYSQL");
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

    ui->Input_Logs->setFontFamily("Consolas, Monaco, Fira Mono, Ubuntu Mono, monospace");
    ui->Input_Logs->setFontPointSize(10);
    new Highlighter(ui->Input_Logs->document());
}

void MainWindow::setActionTriggers()
{
    connect(ui->Menu_Help_AboutVisual_SQL, &QAction::triggered, this, &MainWindow::openAboutDialog);
    connect(ui->Menu_File_Connections, &QAction::triggered, this, &MainWindow::openConnectionsDialog);
    connect(ui->Menu_Help_MariaDB_documentation, &QAction::triggered, this, [this]{ MainWindow::openURL(URL_DOC_MARIADB); });
    connect(ui->Menu_Help_MariaDB_documentation, &QAction::triggered, this, [this]{ MainWindow::openURL(URL_DOC_MYSQL); });
}

QVector<QStringList> MainWindow::dbQuery(QString query)
{
    QSqlQuery sqlQuery(query);
    QVector<QStringList> results;

    while (sqlQuery.next()) {
        QSqlRecord record = sqlQuery.record();
        QStringList tmp;

        for(int i=0; i < record.count(); i++)
        {
            tmp << record.value(i).toString();
        }

        results.append(tmp);
    }

    ui->Input_Logs->append(query);

    return results;
}

void MainWindow::on_Input_Filter_textChanged(const QString &arg1)
{
    QTreeWidgetItem *hostnameItem = ui->Tree_Structure->topLevelItem(0);

    if (arg1 == "") {
        for (int i = 0; i < hostnameItem->childCount(); i++) {
            hostnameItem->child(i)->setHidden(false);
        }
    } else {
        for (int i = 0; i < hostnameItem->childCount(); i++) {
            if (hostnameItem->child(i)->text(0).contains(arg1)) {
                hostnameItem->child(i)->setHidden(false);
            } else {
                hostnameItem->child(i)->setHidden(true);
            }
        }
    }
}
