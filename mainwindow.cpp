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
#include <QSortFilterProxyModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlQueryModel>

/**
 * MainWindow constructor.
 *
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->prepareLayout();
    this->setActionTriggers();

    ConnectionsDialog connectionsDialog;
    connectionsDialog.exec();

    if (connectionsDialog.currentConnection.name == "") {
        exit(0);
    }

    MainWindow::connectToDatabase(connectionsDialog.currentConnection);

    QCompleter *completer = new QCompleter();
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->Input_Filter->setCompleter(completer);

    QSortFilterProxyModel *dbSortFilterModel = new QSortFilterProxyModel(this);
    dbSortFilterModel->setDynamicSortFilter(true);
    dbSortFilterModel->setSourceModel(&dbModel);
    ui->DataTable->setModel(dbSortFilterModel);

    QSortFilterProxyModel *dbCustomQuerySortFilterModel = new QSortFilterProxyModel(this);
    dbCustomQuerySortFilterModel->setDynamicSortFilter(true);
    dbCustomQuerySortFilterModel->setSourceModel(&dbModelCustomQuery);
    ui->DataTable_CustomQuery->setModel(dbCustomQuerySortFilterModel);
}

/**
 * MainWindow destructor.
 *
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
    currentConnection.db.close();
    QSqlDatabase::removeDatabase("QMYSQL");
}

/**
 * Connect to selected database from Connections dialog.
 *
 * @brief connectToDatabase
 * @param currentConnection
 */
void MainWindow::connectToDatabase(CurrentConnection currentConnection) {
    this->currentConnection = currentConnection;

    MainWindow::setWindowTitle(currentConnection.hostname + ": --- - " + APP_NAME);

    ui->Input_Logs->append(tr("/* Connected to: %1 */").arg(currentConnection.hostname));

    QVector<QStringList> databases = dbQuery("SHOW DATABASES;");
    QVector<QStringList> databaseTables = dbQuery("SELECT `table_schema`, `table_name` FROM `information_schema`.`tables` ORDER BY table_schema ASC, table_name ASC;");
    QFont parentItemFont;
    parentItemFont.setBold(true);

    QSqlQuery availableTableCollactionsQuery;
    availableTableCollactionsQuery.exec("SELECT COLLATION_NAME FROM `information_schema`.`COLLATIONS` ORDER BY COLLATION_NAME ASC;");
    ui->Input_Logs->append("SELECT COLLATION_NAME FROM `information_schema`.`COLLATIONS` ORDER BY COLLATION_NAME ASC;");

    while (availableTableCollactionsQuery.next()) {
        ui->Input_Table_Options_Collaction->addItem(availableTableCollactionsQuery.value(0).toString());
    }

    QSqlQuery availableTableEnginesQuery;
    availableTableEnginesQuery.exec("SELECT ENGINE FROM `information_schema`.`ENGINES` ORDER BY ENGINE ASC;");
    ui->Input_Logs->append("SELECT ENGINE FROM `information_schema`.`ENGINES` ORDER BY ENGINE ASC;");

    while (availableTableEnginesQuery.next()) {
        ui->Input_Table_Options_Engine->addItem(availableTableEnginesQuery.value(0).toString());
    }

    QTreeWidgetItem *parentItem = new QTreeWidgetItem();
    parentItem->setText(0, currentConnection.name);
    parentItem->setFont(0, parentItemFont);

    ui->Tree_Structure->insertTopLevelItem(0, parentItem);

    parentItem->setExpanded(true);

    foreach (const QStringList &database, databases) {
        QTreeWidgetItem *databaseItem = new QTreeWidgetItem();

        databaseItem->setData(0, Qt::UserRole, "database");
        databaseItem->setText(0, database.value(0));
        parentItem->addChild(databaseItem);
    }

    foreach (const QStringList &schema, databaseTables) {
        QTreeWidgetItem *tableItem = new QTreeWidgetItem();
        // TODO: check only one level (database level)
        QList<QTreeWidgetItem *> foundDatabaseItem = ui->Tree_Structure->findItems(schema.value(0), Qt::MatchContains|Qt::MatchRecursive, 0);

        tableItem->setData(0, Qt::UserRole, "table");
        tableItem->setText(0, schema.value(1));
        foundDatabaseItem.first()->addChild(tableItem);

        dbSchema[schema.value(0)] << schema.value(1);
    }
}

/**
 * Execute query in Custom query tab.
 *
 * @brief MainWindow::executeCustomQuery
 */
void MainWindow::executeCustomQuery()
{
    QString query = ui->Input_CustomQuery->toPlainText().trimmed();

    if (query == "") {
        return;
    }

    if (query.endsWith(";") == false) {
        query += ";";
    }

    QRegularExpression databaseLimitRegex("LIMIT\\s[0-9]+");
    QRegularExpressionMatch databaseLimitMatch = databaseLimitRegex.match(query);

    if (databaseLimitMatch.hasMatch() == false) {
        query.insert(query.length() - 1, " LIMIT 1000");
    }

    dbModelCustomQuery.setQuery(query);
    ui->Input_Logs->append(query);

    if (dbModel.lastError().databaseText() != "") {
        ui->Input_Logs->append("/* SQL error (" + dbModel.lastError().nativeErrorCode() + "): " + dbModel.lastError().databaseText() + " */");
    }
}

/**
 * Open given URL in system webbrowser.
 *
 * @brief MainWindow::openURL
 * @param url
 */
void MainWindow::openURL(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}

/**
 * Open About dialog.
 *
 * @brief MainWindow::openAboutDialog
 */
void MainWindow::openAboutDialog()
{
    AboutDialog *aboutDialog = new AboutDialog(this);
    aboutDialog->show();
    aboutDialog->raise();
    aboutDialog->activateWindow();
}

/**
 * Open Connections dialog.
 *
 * @brief MainWindow::openConnectionsDialog
 */
void MainWindow::openConnectionsDialog()
{
    ConnectionsDialog connectionsDialog;
    connectionsDialog.exec();

     MainWindow::connectToDatabase(connectionsDialog.currentConnection);
}

/**
 * Set layout elements attributes (sizes, fonts, highlights, etc.).
 *
 * @brief MainWindow::prepareLayout
 */
void MainWindow::prepareLayout()
{
    QList<int> topSplitterSizes = {200, 400};
    QList<int> mainSplitterSizes = {220, 80};
    QList<int> customQuerySplitterSizes = {200, 600};

    ui->Splitter_Top->setSizes(mainSplitterSizes);
    ui->Splitter_Main->setSizes(mainSplitterSizes);
    ui->Splitter_CustomQuery->setSizes(customQuerySplitterSizes);

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

    ui->DataTable->verticalHeader()->setDefaultSectionSize(22);
    ui->DataTable->horizontalHeader()->setStretchLastSection(true);
    ui->DataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->DataTable_CustomQuery->verticalHeader()->setDefaultSectionSize(22);
    ui->DataTable_CustomQuery->horizontalHeader()->setStretchLastSection(true);
    ui->DataTable_CustomQuery->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    new Highlighter(ui->Input_Logs->document());
    new Highlighter(ui->Input_CustomQuery->document());
}

/**
 * Bind all actions to slots.
 *
 * @brief MainWindow::setActionTriggers
 */
void MainWindow::setActionTriggers()
{
    connect(ui->Menu_Help_AboutQt_SQL_Manager, &QAction::triggered, this, &MainWindow::openAboutDialog);
    connect(ui->Menu_File_Connections, &QAction::triggered, this, &MainWindow::openConnectionsDialog);
    connect(ui->Menu_Help_MariaDB_documentation, &QAction::triggered, this, [this]{ MainWindow::openURL(URL_DOC_MARIADB); });
    connect(ui->Menu_Help_MariaDB_documentation, &QAction::triggered, this, [this]{ MainWindow::openURL(URL_DOC_MYSQL); });
    connect(ui->Menu_File_ExecuteQuery, &QAction::triggered, this, &MainWindow::executeCustomQuery);
}

/**
 * Execute SQL query and return results as QVector<QStringList>.
 *
 * @brief MainWindow::dbQuery
 * @param query
 * @return
 */
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

/**
 * Handle event when text is changed in filter input.
 *
 * @brief MainWindow::on_Input_Filter_textChanged
 * @param arg1
 */
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

/**
 * Handle event when element on structure tree is changed.
 *
 * @brief MainWindow::on_Tree_Structure_itemSelectionChanged
 */
void MainWindow::on_Tree_Structure_itemSelectionChanged()
{
    QTreeWidgetItem *selectedItem = ui->Tree_Structure->currentItem();

    if (selectedItem->data(0, Qt::UserRole) == "database") {
        currentDatabase = *new Database(selectedItem->text(0));
        currentDatabase.setHostname(currentConnection.hostname);

        MainWindow::setWindowTitle(currentConnection.hostname + ": " + selectedItem->text(0) + " - " + APP_NAME);
    }

    if (selectedItem->data(0, Qt::UserRole) == "table") {
        currentTable = *new Table(selectedItem->text(0));
        currentTable.setDatabase(currentDatabase);

        QSqlQuery dataTableQuery;
        QString dataTableQueryString = QString("SELECT * FROM `%1`.`%2` LIMIT 1000;")
                .arg(currentDatabase.getName())
                .arg(currentTable.getName());
        dataTableQuery.exec(dataTableQueryString);

        dbModel.setQuery(dataTableQuery);
        ui->Input_Logs->append(dataTableQuery.lastQuery());

        QSqlQuery tableInfoQuery;
        QString tableInfoQueryQtring = QString("SELECT * FROM `information_schema`.`tables` WHERE table_schema = '%1' AND table_name = '%2'")
                .arg(currentDatabase.getName())
                .arg(currentTable.getName());
        tableInfoQuery.exec(tableInfoQueryQtring);

        while (tableInfoQuery.next()) {
            qDebug() << this->ui->Input_Table_Options_Collaction->findText("utf8mb4_unicode_ci");
            this->ui->Input_Table_Options_Name->setText(currentTable.getName());
            this->ui->Input_Table_Options_Comment->setText(tableInfoQuery.value(20).toString());
            this->ui->Input_Table_Options_Engine->setCurrentIndex(
                this->ui->Input_Table_Options_Engine->findText(tableInfoQuery.value(4).toString())
            );
            this->ui->Input_Table_Options_Collaction->setCurrentIndex(
                this->ui->Input_Table_Options_Collaction->findText(tableInfoQuery.value(17).toString())
            );
            this->ui->Input_Table_Options_AutoIncrement->setValue(tableInfoQuery.value(13).toInt());
        }
    }
}
