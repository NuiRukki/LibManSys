#ifndef ADMINMAIN_H
#define ADMINMAIN_H

#include <QDialog>
#include <QtCore>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QtAlgorithms>

namespace Ui {
class adminMain;
}

class adminMain : public QDialog
{
    Q_OBJECT

public:
    explicit adminMain(QWidget *parent = nullptr);
    ~adminMain();
    void addRow();
        // Function to create rows when adding new books

    void updateRow();
        // Function to update information in existing books

    void deleteRow();
        // Function to delete existing books

    void sortTable();
        // Function to sort the table

    QStringList getBookData();
        // Function called when executing function addRow and updateRow
        // Asks the user to input the data needed to create a book
        // Does not check if the information is valid.

    QList<QStandardItem *> createRow(const QStringList &data);
        // Function that creates rows
        // Is called by loadDataFromTextFile and addRow

    void loadData(const QString &filename);
        // Function that loads in the text file.

    void saveData(const QString &filename);
        // Saves data to the text file.
        // Is called by functions addRow, updateRow, and deleteRow




private:
    Ui::adminMain *ui;
    QTableView *tableView;
    QStandardItemModel *model;
};

#endif // ADMINMAIN_H
