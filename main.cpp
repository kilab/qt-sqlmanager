#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName(APP_VENDOR);
    QCoreApplication::setOrganizationDomain(APP_NAME);

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
