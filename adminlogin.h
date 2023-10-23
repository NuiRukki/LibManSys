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

private slots:
    void signIn();
        // Function to check if the text in the box is = to the password
        // and if so, open adminMain
};

#endif // ADMINLOGIN_H
