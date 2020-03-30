#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QLabel>
#include <QStandardItem>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    //open and work with xmlfile

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                          "/desktop",
                                                          tr("XmlFiles (*.xml)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
                return;

    QXmlStreamReader reader;
    reader.addData(file.readAll());

    //create and work with table

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    //table will always be cleared after user open new file
    item = new QStandardItem();
    model->setItem(0, 0, item);

    QStringList horizontalHeader;
    horizontalHeader.append("Date");
    horizontalHeader.append("Title");
    horizontalHeader.append("Description");
    horizontalHeader.append("Link");

    model->setHorizontalHeaderLabels(horizontalHeader);

    item = new QStandardItem();
    model->setItem(0, 0, item);

    ui->tableView->setModel(model);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();

    int count_date = 0, count_title = 0, count_description = 0, count_link = 0;

    //parsing

    while (!reader.atEnd() && !reader.hasError())
    {
        reader.readNextStartElement();
        if(reader.name() == "date"){

            QStringList stl1;
            stl1 << reader.readElementText();
            qDebug() << stl1;
            QString str = stl1.join("");
            item = new QStandardItem(str);
            model->setItem(count_date, 0, item);
            count_date +=1;
        }

        if(reader.name() == "title"){

            QStringList stl1;
            stl1 << reader.readElementText();
            qDebug() << stl1;
            QString str = stl1.join("");
            item = new QStandardItem(str);
            model->setItem(count_title, 1, item);
            count_title +=1;
        }

        if(reader.name() == "description"){

            QStringList stl1;
            stl1 << reader.readElementText();
            qDebug() << stl1;
            QString str = stl1.join("");
            item = new QStandardItem(str);
            model->setItem(count_description, 2, item);
            count_description +=1;
        }

        if(reader.name() == "link"){

            QStringList stl1;
            stl1 << reader.readElementText();
            qDebug() << stl1;
            QString str = stl1.join("");
            item = new QStandardItem(str);
            model->setItem(count_link, 3, item);
            count_link +=1;
        }
    }


    // table optimization

    for ( int i = 0; i < model->rowCount(); i++){
    ui->tableView->setRowHeight(i, 240);
    }

    for ( int i = 0; i < model->columnCount(); i++){
    ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

}
