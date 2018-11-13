#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "mainwindow.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("About - " + APP_NAME);

    QString AboutBoxContent = "<img src=\":/img/img/logo.png\" style=\"float: left; margin-right: 10px;\" width=\"128\" />";
    AboutBoxContent.append("<p><font size=\"5\">" + APP_NAME + "</font></p>");
    AboutBoxContent.append("<p>v. " + APP_VERSION + "</p>");
    AboutBoxContent.append("<p>Author: Paweł Balicki &lt;pawel@kilab.pl&gt;</p>");
    AboutBoxContent.append("<p>Homepage: <a href=\"" + APP_HOMEPAGE_URL + "\">" + APP_HOMEPAGE_URL + "</a></p>");
    AboutBoxContent.append("<hr />");

    AboutBoxContent.append("<p>MIT License</p>");
    AboutBoxContent.append("<p>Copyright (c) Paweł Balicki</p>");

    AboutBoxContent.append(R"(<p>Permission is hereby granted, free of charge, to any person obtaining a copy
                           of this software and associated documentation files (the "Software"), to deal
                           in the Software without restriction, including without limitation the rights
                           to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
                           copies of the Software, and to permit persons to whom the Software is
                           furnished to do so, subject to the following conditions:</p>)");

    AboutBoxContent.append(R"(<p>The above copyright notice and this permission notice shall be included in all
                           copies or substantial portions of the Software.</p>)");

    AboutBoxContent.append(R"(<p>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
                           IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
                           FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
                           AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
                           LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
                           OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
                           SOFTWARE.</p>)");

    ui->TextBox_About->setHtml(AboutBoxContent);
    ui->TextBox_About->setOpenExternalLinks(true);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
