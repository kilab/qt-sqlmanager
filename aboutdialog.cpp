#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "mainwindow.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("About " + APP_NAME);

    QString AboutBoxContent = "<p><font size=\"5\">" + APP_NAME + "</font></p>";
    AboutBoxContent.append("<p>v. " + APP_VERSION + "</p>");
    AboutBoxContent.append("<p>Author: Paweł Balicki <pawel@kilab.pl></p>");
    AboutBoxContent.append("<p>Homepage: <a href=\" + APP_HOMEPAGE_URL + \">" + APP_HOMEPAGE_URL + "</a></p>");
    AboutBoxContent.append("<hr />");

    ui->TextBox_About->setHtml(AboutBoxContent);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
