#ifndef USERMAIN_H
#define USERMAIN_H

#include <QDialog>

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
};

#endif // USERMAIN_H
