#include "adminmain.h"
#include "ui_adminmain.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QStandardItemModel>
#include <QTableView>


adminMain::adminMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminMain)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(this);

    QFile file("C:/Users/asus/Downloads/Book1.csv");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int row = 0;

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            int column = 0;

            for (const QString &field : fields) {
                QStandardItem *item = new QStandardItem(field);
                model->setItem(row, column, item);
                column++;
            }

            row++;
        }

        file.close();
    }

    ui->tableView->setModel(model);
    // This code reads the csv on execution



    QPushButton *button[4];
    button[1] = adminMain::findChild<QPushButton *>("Button1");
    connect(button[1], SIGNAL(released()), this, SLOT(loadTable()));

//    for (int i = 1; i != 5; i++) {
//        QString butName = "Button" + QString::number(i);
//        button[i] = adminMain::findChild<QPushButton *>(butName);
//        connect(button[i], SIGNAL(released()), this, SLOT(buttonIsPressed()));
//    }
}

adminMain::~adminMain()
{
    delete ui;
}

void adminMain::loadTable() {

}
