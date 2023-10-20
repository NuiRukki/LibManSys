#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>

namespace Ui {
class AdminLogIn;
}

class AdminLogIn : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLogIn(QWidget *parent = nullptr);
    ~AdminLogIn();

private:
    Ui::AdminLogIn *ui;
};

#endif // ADMINLOGIN_H
