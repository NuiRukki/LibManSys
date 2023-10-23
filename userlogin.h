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

private slots:
    void signOn();
        // Function to check open userMain and store the full name as data for use
        // later
};

#endif // USERLOGIN_H
