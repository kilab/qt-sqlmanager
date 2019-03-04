#include "connectionsdialog.h"
#include "ui_connectionsdialog.h"
#include "mainwindow.h"
#include "sqlconnection.h"

#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QtSql>

ConnectionsDialog::ConnectionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionsDialog)
{
    ui->setupUi(this);

    QList<int> topSplitterSizes = {150, 300};

    ui->Splitter_Top->setSizes(topSplitterSizes);

    QWidget *widgetSplitterTop = ui->Splitter_Top->widget(0);
    QSizePolicy policySplitterMain = widgetSplitterTop->sizePolicy();
    policySplitterMain.setVerticalStretch(1);
    widgetSplitterTop->setSizePolicy(policySplitterMain);

    for (int i = 0; i < SqlDriversString.size(); i++) {
        ui->Input_Driver->addItem(SqlDriversString.at(i));
    }

    connectionsModel = new QStandardItemModel(ui->List_Connections);
    settings.beginGroup("connections");

    for (QString connectionName: settings.childGroups()) {
        QStandardItem *connectionItem = new QStandardItem;
        connectionItem->setText(connectionName);
        connectionItem->setEditable(false);

        connectionsModel->setItem(connectionsModel->rowCount(), 0, connectionItem);
    }
    settings.endGroup();

    ui->List_Connections->setModel(connectionsModel);
}

ConnectionsDialog::~ConnectionsDialog()
{
    delete ui;
}

/**
 * Connect to selected database.
 *
 * @brief ConnectionsDialog::ConnectDatabase
 */
void ConnectionsDialog::ConnectDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setPort(ui->Input_Port->value());
    db.setHostName(ui->Input_Hostname->text());
    db.setUserName(ui->Input_Username->text());
    db.setPassword(ui->Input_Password->text());

    if (db.open() == false) {
        QMessageBox errorDialog;
        errorDialog.setIcon(QMessageBox::Critical);
        errorDialog.setText(db.lastError().databaseText());
        errorDialog.exec();
    } else {
        currentConnection.db = db;
        currentConnection.name = ui->Input_ConnectionName->text();
        currentConnection.hostname = ui->Input_Hostname->text();

        close();
    }
}

/**
 * Check connection to database.
 *
 * @brief ConnectionsDialog::CheckConnection
 * @return
 */
ConnectionValid ConnectionsDialog::CheckConnection() {
    ConnectionValid connectionValid;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setPort(ui->Input_Port->value());
    db.setHostName(ui->Input_Hostname->text());
    db.setUserName(ui->Input_Username->text());
    db.setPassword(ui->Input_Password->text());

    if (db.open() == true) {
        connectionValid.status = true;
    } else {
        connectionValid.status = false;
        connectionValid.message = db.lastError().databaseText();
    }

    db.close();
    QSqlDatabase::removeDatabase("QMYSQL");

    return connectionValid;
}

/**
 * Check if form inputs are valid.
 *
 * @brief ConnectionsDialog::CheckConnectionInputs
 * @return
 */
bool ConnectionsDialog::CheckConnectionInputs()
{
    QMessageBox messageDialog;
    messageDialog.setIcon(QMessageBox::Critical);

    if (ui->Input_Password->text() == "") {
        messageDialog.setText(tr("Empty password"));
    }
    if (ui->Input_Username->text() == "") {
        messageDialog.setText(tr("Empty username"));
    }
    if (ui->Input_Hostname->text() == "") {
        messageDialog.setText(tr("Empty hostname"));
    }
    if (ui->Input_ConnectionName->text() == "") {
        messageDialog.setText(tr("Empty connection name"));
    }

    if (messageDialog.text() != "") {
        messageDialog.exec();

        return false;
    } else {
        return true;
    }
}

/**
 * Clear all form inputs.
 *
 * @brief ConnectionsDialog::ClearForm
 */
void ConnectionsDialog::ClearForm() {
    ui->Input_ConnectionName->clear();
    ui->Input_Hostname->clear();
    ui->Input_Username->clear();
    ui->Input_Password->clear();
    ui->Input_Port->setValue(3306);

    const QModelIndex emptyIndex;
    ui->List_Connections->setCurrentIndex(emptyIndex);
}

void ConnectionsDialog::on_Button_Connect_clicked()
{
    ConnectDatabase();
}

void ConnectionsDialog::on_Button_Remove_clicked()
{
    QModelIndex currentConnectionIndex = ui->List_Connections->currentIndex();
    QVariant currentConnectionName = connectionsModel->data(currentConnectionIndex);

    QMessageBox::StandardButton confirmRemove;

    confirmRemove = QMessageBox::question(this, APP_NAME, tr("Are you sure you want remove selected connection?"), QMessageBox::Yes|QMessageBox::No);

    if (confirmRemove == QMessageBox::No) {
        return;
    }

    settings.remove("connections/" + currentConnectionName.toString());
    connectionsModel->removeRow(currentConnectionIndex.row());

    ClearForm();
}

void ConnectionsDialog::on_Button_Save_clicked()
{
    if (ConnectionsDialog::CheckConnectionInputs() == false) {
        return;
    }

    QString connectionName = ui->Input_ConnectionName->text();

    settings.setValue("connections/" + connectionName + "/driver", ui->Input_Driver->currentIndex());
    settings.setValue("connections/" + connectionName + "/hostname", ui->Input_Hostname->text());
    settings.setValue("connections/" + connectionName + "/username", ui->Input_Username->text());
    settings.setValue("connections/" + connectionName + "/password", ui->Input_Password->text());
    settings.setValue("connections/" + connectionName + "/port", ui->Input_Port->value());


    for(int r = 0; r < connectionsModel->rowCount(); ++r) {
        QModelIndex index = connectionsModel->index(r, 0);
        QVariant name = connectionsModel->data(index);

        if (connectionName == name) {
            return;
        }
    }

    settings.beginGroup("connections");

    QStandardItem *connectionItem = new QStandardItem;
    connectionItem->setText(connectionName);

    connectionsModel->setItem(connectionsModel->rowCount(), 0, connectionItem);
    ui->List_Connections->setCurrentIndex(connectionsModel->index(connectionsModel->rowCount() - 1, 0));
    settings.endGroup();

    ui->Button_Remove->setEnabled(true);
    ui->Button_Connect->setEnabled(true);
}

void ConnectionsDialog::on_Button_Add_clicked()
{
    ui->List_Connections->clearSelection();
    ClearForm();
}

void ConnectionsDialog::on_Button_Test_clicked()
{
    if (ConnectionsDialog::CheckConnectionInputs() == false) {
        return;
    }

    ConnectionValid connectionValid = ConnectionsDialog::CheckConnection();
    QMessageBox messageDialog;

    if (connectionValid.status == true) {
        messageDialog.setIcon(QMessageBox::Information);
        messageDialog.setText(tr("Connection established successfully"));
    } else {
        messageDialog.setIcon(QMessageBox::Critical);
        messageDialog.setText(tr("Connection fail: %1").arg(connectionValid.message));
    }

    messageDialog.exec();
}

void ConnectionsDialog::on_List_Connections_doubleClicked(const QModelIndex &index)
{
    ConnectDatabase();
}

void ConnectionsDialog::on_List_Connections_clicked(const QModelIndex &index)
{
    QStandardItem *item = connectionsModel->item(index.row(), index.column());

    ui->Button_Remove->setEnabled(true);
    ui->Button_Connect->setEnabled(true);

    ui->Input_ConnectionName->setText(item->text());
    ui->Input_Driver->setCurrentIndex(settings.value("connections/" + item->text() + "/driver").toInt());
    ui->Input_Hostname->setText(settings.value("connections/" + item->text() + "/hostname").toString());
    ui->Input_Username->setText(settings.value("connections/" + item->text() + "/username").toString());
    ui->Input_Password->setText(settings.value("connections/" + item->text() + "/password").toString());
    ui->Input_Port->setValue(settings.value("connections/" + item->text() + "/port").toInt());
}
