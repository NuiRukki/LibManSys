#ifndef ADMINMAIN_H
#define ADMINMAIN_H

#include <QDialog>
#include <QtCore>

namespace Ui {
class adminMain;
}

class adminMain : public QDialog
{
    Q_OBJECT

public:
    explicit adminMain(QWidget *parent = nullptr);
    ~adminMain();

private:
    Ui::adminMain *ui;

private slots:
    void loadTable();
};

#endif // ADMINMAIN_H
