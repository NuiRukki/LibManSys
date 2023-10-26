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
    QTableView *tableView2;
    QStandardItemModel *model2;
    QTableView *tableView3;
    QStandardItemModel *model3;

private slots:
    void loadData(const QString &filename);
    void loadData2(const QString &filename);
    void loadData3(const QString &filename);
    void acceptTicket();
    void rejectTicket();
    void goToAdmin();
    void addRowsToQueue();
    void saveData(const QString &filename, const QList<QStringList> &data);

};

#endif // TICKETS_H
