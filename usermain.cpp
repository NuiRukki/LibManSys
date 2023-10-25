#include "usermain.h"
#include "ui_usermain.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QComboBox>

userMain::userMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userMain)
{
    ui->setupUi(this);

    // Table
    model = new QStandardItemModel(this);
    model->setColumnCount(6);
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Book Name" << "Author" << "Genre" << "Inventory" << "Description");
    tableView = findChild<QTableView*>("tableView");
    tableView->setModel(model);
    tableView->setSortingEnabled(true);

    // Buttons
    QPushButton *sortButton = findChild<QPushButton*>("sortTable");
    QPushButton *borrowButton = findChild<QPushButton*>("borrowBook");
    QPushButton *searchButton = findChild<QPushButton*>("searchTable");
    connect(sortButton, &QPushButton::clicked, this, &userMain::sortTable);
    connect(borrowButton, &QPushButton::clicked, this, &userMain::borrowBook);
    connect(searchButton, &QPushButton::clicked, this, &userMain::searchTable);


    loadData("bookRepository.txt");
}

userMain::~userMain()
{
    delete ui;
}

void userMain::loadData(const QString &filename){
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
} // adapted from adminmain.cpp

void userMain::sortTable(){
    bool ok;
    QStringList columnNames;
    for (int col = 0; col < model->columnCount(); ++col) {
        columnNames << model->horizontalHeaderItem(col)->text();
    }

    QString item = QInputDialog::getItem(this, "Sort Table", "Select a column to sort by:", columnNames, 0, false, &ok);

    if (ok) {
        int column = columnNames.indexOf(item);

        if (column != -1) {
            model->sort(column, Qt::AscendingOrder);
            model->submit();
        } else {
            QMessageBox::information(this, "Sort Table", "Invalid column selected.");
        }
    }
}

void userMain::searchTable() {
    // Create a dialog to input search criteria
    QDialog searchDialog(this);
    QVBoxLayout layout(&searchDialog);

    QLabel searchLabel("Search by:");
    QComboBox searchCriteria;
    searchCriteria.addItems(QStringList() << "ID" << "Book Name" << "Author" << "Genre" << "Inventory" << "Description");
    QLineEdit searchInput;
    QPushButton searchButton("Search");
    QPushButton cancelButton("Cancel");

    layout.addWidget(&searchLabel);
    layout.addWidget(&searchCriteria);
    layout.addWidget(&searchInput);
    layout.addWidget(&searchButton);
    layout.addWidget(&cancelButton);

    searchDialog.setLayout(&layout);

    connect(&searchButton, &QPushButton::clicked, &searchDialog, &QDialog::accept);
    connect(&cancelButton, &QPushButton::clicked, &searchDialog, &QDialog::reject);

    if (searchDialog.exec() == QDialog::Accepted) {
        QString searchTerm = searchInput.text();
        int column = searchCriteria.currentIndex();
        bool found = false;

        for (int row = 0; row < model->rowCount(); ++row) {
            QString cellText = model->item(row, column)->text();
            if (cellText.contains(searchTerm, Qt::CaseInsensitive)) {
                tableView->selectRow(row); // Highlight the found row in the table
                found = true;
                break;
            }
        }

        if (!found) {
            QMessageBox::information(this, "Search", "No matching records found.");
        }
    }
}

void userMain::borrowBook() {
    bool ok;
    QString userName = QInputDialog::getText(this, "Enter User's Name", "User's Name:", QLineEdit::Normal, "", &ok);

    if (ok && !userName.isEmpty()) {
        QString bookNameOrID = QInputDialog::getText(this, "Enter Book Name or ID", "Book Name or ID:", QLineEdit::Normal, "", &ok);

        if (ok && !bookNameOrID.isEmpty()) {
            // Check if the book exists
            bool bookExists = false;
            int idColumn = 0;
            int nameColumn = 1;
            int inventoryColumn = 4;
            for (int row = 0; row < model->rowCount(); ++row) {
                if (model->item(row, idColumn)->text() == bookNameOrID || model->item(row, nameColumn)->text() == bookNameOrID) {
                    bookExists = true;
                    if (model->item(row, inventoryColumn)->text().toInt() > 0) {
                        QFile file("borrowedBooks.txt");
                        if (file.open(QIODevice::Append | QIODevice::Text)) {
                            QTextStream out(&file);
                            out << "User: " << userName << " | Book: " << bookNameOrID << "\n";
                            file.close();
                        }
                    } else {
                        QMessageBox::critical(this, "Error", "The selected book is no longer in stock.");
                    }
                    break;
                }
            }

            if (!bookExists) {
                QMessageBox::critical(this, "Error", "The selected book does not exist.");
            }
        }
    }
}


