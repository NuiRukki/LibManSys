#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QDialog>

namespace Ui {
class UserLogIn;
}

class UserLogIn : public QDialog
{
    Q_OBJECT

public:
    explicit UserLogIn(QWidget *parent = nullptr);
    ~UserLogIn();

private:
    Ui::UserLogIn *ui;
};

#endif // USERLOGIN_H
