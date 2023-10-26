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

    // Table
    model = new QStandardItemModel(this);
    model->setColumnCount(2);
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Book");
    tableView = findChild<QTableView*>("tableView");
    tableView->setModel(model);
    tableView->setSortingEnabled(true);

    // Buttons
    QPushButton *accept = findChild<QPushButton*>("acceptButton");
    QPushButton *reject = findChild<QPushButton*>("rejectButton");
    QPushButton *goBack = findChild<QPushButton*>("backButton");
    connect(accept, &QPushButton::clicked, this, &tickets::acceptTicket);
    connect(reject, &QPushButton::clicked, this, &tickets::rejectTicket);
    connect(goBack, &QPushButton::clicked, this, &tickets::goToAdmin);

    loadData("borrowedBooks.txt");
    addRowsToQueue();
}

tickets::~tickets()
{
    delete ui;
}

void tickets::loadData(const QString &filename){
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
            model->appendRow(row);
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

void tickets::checkAndRemoveOutOfStockBooks() {
    QString borrowedBooksFilename = "borrowedBooks.txt";
    QString bookRepositoryFilename = "bookRepository.txt";

    QList<QStringList> updatedData;

    QFile borrowedBooksFile(borrowedBooksFilename);
    QFile bookRepositoryFile(bookRepositoryFilename);

    QTextStream borrowedBooksIn(&borrowedBooksFile);
    QTextStream bookRepositoryIn(&bookRepositoryFile);

    while (!borrowedBooksIn.atEnd()) {
        QString borrowedLine = borrowedBooksIn.readLine();
        QStringList borrowedFields = borrowedLine.split(" | ");
        QString borrowedUser = borrowedFields[1];
        QString borrowedBook = borrowedFields[3];

        bool hasStock = false;

        // Check if the book has stock in bookRepository.txt
        while (!bookRepositoryIn.atEnd()) {
            QString repositoryLine = bookRepositoryIn.readLine();
            QStringList repositoryFields = repositoryLine.split(" | ");

            if (repositoryFields.size() >= 2 &&
                repositoryFields[1].trimmed().compare(borrowedBook, Qt::CaseInsensitive) == 0) {
                int inventory = repositoryFields[4].toInt(); // Convert inventory to an integer
                if (inventory > 0) {
                    hasStock = true;
                    break;
                }
            }
        }

        // If the book doesn't have stock, do not add it to updatedData
        if (hasStock) {
            updatedData.append(borrowedFields);
        }

        // Reset the read position of bookRepositoryFile for the next iteration
        bookRepositoryFile.seek(0);
    }

    borrowedBooksFile.close();
    bookRepositoryFile.close();

    // Save the updated data back to borrowedBooks.txt
    saveData(borrowedBooksFilename, updatedData);
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
//                    // Found a match, update the inventory
//                    int inventory = fields[4].toInt(); // Convert inventory to an integer
//                    if (inventory > 0) {
//                        inventory--;
//                        fields[4] = QString::number(inventory); // Update the inventory as text
//                    }
//                }

//                fileContents.append(fields.join("|") + "\n"); // Add the updated line to fileContents
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

