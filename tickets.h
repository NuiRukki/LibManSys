#ifndef TICKETS_H
#define TICKETS_H

#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QQueue>

namespace Ui {
class tickets;
}

class tickets : public QDialog
{
    Q_OBJECT

public:
    explicit tickets(QWidget *parent = nullptr);
    ~tickets();

private:
    Ui::tickets *ui;
    QStandardItemModel *model;
    QTableView *tableView;
    QQueue<QStringList> ticketQueue;

private slots:
    void loadData(const QString &filename);
    void acceptTicket();
    void rejectTicket();
    void goToAdmin();
    void addRowsToQueue();
    void saveData(const QString &filename, const QList<QStringList> &data);
    void checkAndRemoveOutOfStockBooks();

//    connect(accept, &QPushButton::clicked, this, &tickets::acceptTicket);
//    connect(reject, &QPushButton::clicked, this, &tickets::rejectTicker);
//    connect(goBack, &QPushButton::clicked, this, &tickets::goToAdmin);
};

#endif // TICKETS_H
