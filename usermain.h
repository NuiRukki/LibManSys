#ifndef USERMAIN_H
#define USERMAIN_H

#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QHeaderView>

namespace Ui {
class userMain;
}

class userMain : public QDialog
{
    Q_OBJECT

public:
    explicit userMain(QWidget *parent = nullptr);
    ~userMain();

private:
    Ui::userMain *ui;
    QStandardItemModel *model;
    QTableView *tableView;

private slots:
    void loadData(const QString &filename);
        // Loads txt file
    void sortTable();
        // Sorts the table depending on user input on a dialog box
    void borrowBook();
        // Creates a dialog box that takes the user's name and the book's id or name
        // and outputs this into the txt file.
    void searchTable();
        // Uses a sequential search to find a book

};

#endif // USERMAIN_H
