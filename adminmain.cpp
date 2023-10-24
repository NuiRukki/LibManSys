#include "adminmain.h"
#include "ui_adminmain.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QStandardItemModel>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
//#include <QDir>
    // Just needed QDir to find out whr my text file was, dont mind that (￣_￣|||)

adminMain::adminMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminMain)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    model->setColumnCount(6);
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Book Name" << "Author" << "Genre" << "Inventory" << "Description");
        // ID, Book Name, Author, Genre, Inventory
        // For the table

    tableView = new QTableView(this);
    tableView->setModel(model);

    // Buttons & Functions
    QPushButton *addButton = new QPushButton("Add", this);
    QPushButton *updateButton = new QPushButton("Update", this);
    QPushButton *deleteButton = new QPushButton("Delete", this);
    connect(addButton, &QPushButton::clicked, this, &adminMain::addRow);
    connect(updateButton, &QPushButton::clicked, this, &adminMain::updateRow);
    connect(deleteButton, &QPushButton::clicked, this, &adminMain::deleteRow);

    // Layout Setup
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(addButton);
    layout->addWidget(updateButton);
    layout->addWidget(deleteButton);
    layout->addWidget(tableView);
        // For some reason it didnt work with the buttons/table I placed in the UI
        // Soooo resort to this and it worked- somehow-
        // I want to question it but at the same time I don't
        // ;-;

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setLayout(layout);

    // Load data from txt
    loadData("bookRepository.txt");
}


adminMain::~adminMain()
{
    delete ui;
}

void adminMain::addRow()
{
    // Get data from admin
    QStringList rowData = getBookData();
    model->appendRow(createRow(rowData));

    // Save to txt file
    saveData("bookRepository.txt");
}

void adminMain::updateRow()
{
    // Ask admin for ID of book to update
    QString idToUpdate = QInputDialog::getText(this, "Update Book", "Enter the ID of the book to update:");

    // Find row with matching ID
    int rowCount = model->rowCount();
    int rowToUpdate = -1;
    for (int row = 0; row < rowCount; ++row)
    {
        if (model->data(model->index(row, 0)).toString() == idToUpdate)
        {
            rowToUpdate = row;
            break;
        } // Findie!
        // Finds the book with matching ID
    }

    // Check if ID exists
    if (rowToUpdate != -1)
    {
        // ID exists
        QStringList existingData;
        for (int col = 0; col < 6; col++) {
            existingData.append(model->data(model->index(rowToUpdate, col)).toString());
        }

        QStringList updatedData;
        for (int col = 0; col < 6; col++) {
            QString fieldName = model->horizontalHeaderItem(col)->text();
            QString existingValue = existingData.at(col);

            QString field = QInputDialog::getText(this, "Update Book", "Enter " + fieldName + ":", QLineEdit::Normal, existingValue);

            if (field.isEmpty()) {
                updatedData.append(existingValue);
                // if empty, keep whats already there
            } else {
                // For Commas (THIS HURT TO CODE FSR)
                if (field.contains(",")) {
                    QMessageBox::critical(this, "Invalid Input", "Input cannot contain commas.");
                    return;
                    // I prolly coulda just used a do while loop with an if condition
                    // But this works!
                }
                updatedData.append(field);

            }
        }

        for (int col = 0; col < 6; col++) {
            model->setData(model->index(rowToUpdate, col), updatedData.at(col), Qt::DisplayRole);
        }

        //Save
        saveData("bookRepository.txt");
    }
    else
    {
        // ID doesn't exist,
        QMessageBox::information(this, "Book Not Found", "The book with ID " + idToUpdate + " does not exist.");
    }
}

void adminMain::deleteRow()
{
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();

    if (!selectedRows.isEmpty())
    {
        int row = selectedRows.at(0).row();
        model->removeRow(row);

        // Sa- you get it.
        saveData("bookRepository.txt");
    }
}

QStringList adminMain::getBookData()
{
    QStringList bookData;
    bool repeat = false;
    for (int col = 0; col < 6; col++)
    {
        do {
            QString field = QInputDialog::getText(this, "Enter Data", QString("Enter %1:").arg(model->horizontalHeaderItem(col)->text()));
            repeat = false;
            if (field.contains(",")) {
                QMessageBox::critical(this, "Invalid Input", "Input cannot contain commas.");
                repeat = true;
            }
            if (!repeat) {
                bookData.append(field);
                // oh hey I actually used what I thought of
            }
        } while (repeat == true);

        // Do While If for comma handling
    }
    return bookData;
}

QList<QStandardItem *> adminMain::createRow(const QStringList &data)
{
    QList<QStandardItem *> row;
    for (const QString &item : data)
    {
        QStandardItem *cell = new QStandardItem(item);
        row.append(cell);
    }
    return row;
}

void adminMain::loadData(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        //  qDebug() << QDir::currentPath();
            // ignore the debug, just needed to see where the directory for bookRepository.txt was lol

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            QList<QStandardItem *> row = createRow(fields);
            model->appendRow(row);
        }

        file.close();
    }
}

void adminMain::saveData(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream out(&file);
        for (int row = 0; row < model->rowCount(); row++)
        {
            QStringList rowData;
            for (int col = 0; col < 6; col++)
            {
                rowData.append(model->item(row, col)->text());
            }
            out << rowData.join(",") << "\n";
        }
        file.close();
    }
}
