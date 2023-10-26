#include "tickets.h"
#include "ui_tickets.h"

#include "adminmain.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QStandardItemModel>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QQueue>
#include <QMessageBox>

tickets::tickets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tickets)
{
    ui->setupUi(this);

    qDebug() << " ================= HERE ================= ";
    // Table
    model = new QStandardItemModel(this);
    model->setColumnCount(2);
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Book");
    tableView = findChild<QTableView*>("tableView");
    tableView->setModel(model);
    tableView->setSortingEnabled(true);

    // sEEcREt tAAbLe for bookRepository.txt
    // Coz it was that hard to access 2 files and take a condition from 1 to affect the other
    model2 = new QStandardItemModel(this);
    model2->setColumnCount(2);
    model2->setHorizontalHeaderLabels(QStringList() << "ID" << "Book");
    tableView2 = findChild<QTableView*>("tableView2");
    tableView2->setModel(model2);
    tableView2->setSortingEnabled(true);

    // seEcREt tAbLe for unqueued tickets
    // If I ever need it
    model3 = new QStandardItemModel(this);
    model3->setColumnCount(2);
    model3->setHorizontalHeaderLabels(QStringList() << "ID" << "Book");
    tableView3 = findChild<QTableView*>("tableView3");
    tableView3->setModel(model3);
    tableView3->setSortingEnabled(true);

    // Buttons
    QPushButton *accept = findChild<QPushButton*>("acceptButton");
    QPushButton *reject = findChild<QPushButton*>("rejectButton");
    QPushButton *goBack = findChild<QPushButton*>("backButton");
    connect(accept, &QPushButton::clicked, this, &tickets::acceptTicket);
    connect(reject, &QPushButton::clicked, this, &tickets::rejectTicket);
    connect(goBack, &QPushButton::clicked, this, &tickets::goToAdmin);

    loadData2("bookRepository.txt");
    loadData3("borrowedBooks.txt");
        // For comparison
    loadData("borrowedBooks.txt");
        // For Ticketing & Queue
    addRowsToQueue();
}

tickets::~tickets()
{
    delete ui;
}


void tickets::loadData(const QString &filename) {
    QFile file("borrowedBooks.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        qDebug() << "created file";

        while (!in.atEnd()) {
            qDebug() << "While loop for atEnd()";
            QString line = in.readLine();
            QStringList fields = line.split("|");

            if (fields.size() >= 2) {
                qDebug() << "if statement for fields";
                bool hasInventory = false;

                for (int row = 0; row < model2->rowCount(); ++row) {
                    qDebug() << "for loop for rows";
                    if (model2->item(row, 0)->text().toInt() == fields[1].toInt() && model2->item(row, 4)->text().toInt() > 0) {
                        qDebug() << "if statement for inventory";
                        hasInventory = true;
                        break;
                    }
                }

                if (hasInventory) {
                    QList<QStandardItem*> rowItems;
                    for (const QString& field : fields) {
                        qDebug() << "for loop for fields";
                        QStandardItem* item = new QStandardItem(field);
                        rowItems.append(item);
                    }
                    model->appendRow(rowItems);
                }
            }
        }
        file.close();
    }
}

//    for (int row = 0; row < model->rowCount(); ++row) {
//        if (model->item(row, idColumn)->text() == bookNameOrID || model->item(row, nameColumn)->text() == bookNameOrID) {
//            bookExists = true;
//            if (model->item(row, inventoryColumn)->text().toInt() > 0) {
//                QFile file("borrowedBooks.txt");
//                if (file.open(QIODevice::Append | QIODevice::Text)) {
//                    QTextStream out(&file);
//                    out << userName << " | " << bookNameOrID << "\n";
//                    file.close();
//                }
//            } else {
//                QMessageBox::critical(this, "Error", "The selected book is no longer in stock.");
//            }
//            break;
//        }
//    }



void tickets::loadData2(const QString &filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList fields = line.split("|");
            QList<QStandardItem *> row;
            for (const QString &field : fields)
            {
                row.append(new QStandardItem(field));
            }
            model2->appendRow(row);
        }
        file.close();
    }
}

void tickets::loadData3(const QString &filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList fields = line.split("|");
            QList<QStandardItem *> row;
            for (const QString &field : fields)
            {
                row.append(new QStandardItem(field));
            }
            model3->appendRow(row);
        }
        file.close();
    }
}


void tickets::goToAdmin() {

    adminMain uLogIn;
    this->hide();
    uLogIn.setModal(true);
    uLogIn.exec();

}

void tickets::addRowsToQueue() {
    for (int row = 0; row < model->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < 2; col++) {
            rowData.append(model->data(model->index(row, col)).toString());
        }
        ticketQueue.enqueue(rowData);
    }
}

void tickets::acceptTicket()
{
    if (!ticketQueue.isEmpty())
    {
        QFile file("borrowedBooks.txt");
        QStringList rowData = ticketQueue.dequeue();
        QString user = rowData[0];
        QString book = rowData[1];
        int rowToUpdate = -1;
        QList<QStringList> updatedData;

        for (int row = 0; row < model->rowCount(); ++row)
        {
            QString userInTable = model->data(model->index(row, 0)).toString();
            QString bookInTable = model->data(model->index(row, 1)).toString();

            if (userInTable == user && bookInTable == book)
            {
                model->removeRow(row);
                break;
            }
        }

        for (int row = 0; row < model->rowCount(); ++row)
        {
            QStringList updatedRow;
            for (int col = 0; col < 2; col++)
            {
                updatedRow.append(model->data(model->index(row, col)).toString());
            }
            updatedData.append(updatedRow);
        }
        saveData("borrowedBooks.txt", updatedData);
        file.close();






        //        // Update bookRepository.txt here
        //        QString filename = "bookRepository.txt";
        //        QFile ofile(filename);

        //        if (ofile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        //            QTextStream in(&ofile);
        //            QString fileContents;

        //            while (!in.atEnd()) {
        //                QString line = in.readLine();
        //                QStringList fields = line.split("|");

        //                if (fields.size() >= 2 && fields[1].trimmed().compare(rowData[1].trimmed(), Qt::CaseInsensitive) == 0) {
        //
        //                    int inventory = fields[4].toInt();
        //                    if (inventory > 0) {
        //                        inventory--;
        //                        fields[4] = QString::number(inventory);
        //                    }
        //                }

        //                fileContents.append(fields.join("|") + "\n");
        //            }

        //            ofile.seek(0);
        //            ofile.write(fileContents.toUtf8());
        //            ofile.flush();
        //            ofile.resize(ofile.pos());
        //            ofile.close();
        //        }
        //        else {
        //            QMessageBox::critical(this, "Error", "Failed to open bookRepository");
        //        }

        QMessageBox::information(this, "Book Accepted", "The book '" + user + " | " + book + "' has been accepted.");
    }
    else
    {
        QMessageBox::information(this, "No Tickets", "There are no pending book borrowing requests.");
    }
}

void tickets::rejectTicket()
{
    if (!ticketQueue.isEmpty())
    {
        QFile file("borrowedBooks.txt");
        QStringList rowData = ticketQueue.dequeue();
        QString user = rowData[0];
        QString book = rowData[1];
        int rowToUpdate = -1;
        QList<QStringList> updatedData;

        for (int row = 0; row < model->rowCount(); ++row)
        {
            QString userInTable = model->data(model->index(row, 0)).toString();
            QString bookInTable = model->data(model->index(row, 1)).toString();

            if (userInTable == user && bookInTable == book)
            {
                model->removeRow(row);
                break;
            }
        }

        for (int row = 0; row < model->rowCount(); ++row)
        {
            QStringList updatedRow;
            for (int col = 0; col < 2; col++)
            {
                updatedRow.append(model->data(model->index(row, col)).toString());
            }
            updatedData.append(updatedRow);
        }
        saveData("borrowedBooks.txt", updatedData);
        file.close();
        QMessageBox::information(this, "Book rejected", "The book '" + user + " | " + book + "' has been rejected.");
    }
    else
    {
        QMessageBox::information(this, "No Tickets", "There are no pending book borrowing requests.");
    }


}


void tickets::saveData(const QString &filename, const QList<QStringList> &data)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream out(&file);
        for (const QStringList &rowData : data)
        {
            out << rowData.join(" | ") << "\n";
        }
        file.close();
    }
}
