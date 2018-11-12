#ifndef CONNECTIONSDIALOG_H
#define CONNECTIONSDIALOG_H

#include "sqlconnection.h"

#include <QDialog>
#include <QListWidgetItem>
#include <QSettings>
#include <QString>

namespace Ui {
class ConnectionsDialog;
}

struct ConnectionValid {
    bool status;
    QString message;
};

class ConnectionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionsDialog(QWidget *parent = nullptr);
    ~ConnectionsDialog();

    CurrentConnection currentConnection;

private slots:
    void on_Button_Connect_clicked();

    void on_Button_Remove_clicked();

    void on_Button_Save_clicked();

    void on_Button_Add_clicked();

    void on_Button_Test_clicked();

    void on_List_Connections_itemClicked(QListWidgetItem *item);

    void on_List_Connections_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ConnectionsDialog *ui;

    QSettings settings;

    void ConnectDatabase();

    ConnectionValid CheckConnection();

    bool CheckConnectionInputs();

    void ClearForm();

    void ResfreshConnectionsList();
};

#endif // CONNECTIONSDIALOG_H
