#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QDialog>

namespace Ui {
class userLogIn;
}

class userLogIn : public QDialog
{
    Q_OBJECT

public:
    explicit userLogIn(QWidget *parent = nullptr);
    ~userLogIn();

private:
    Ui::userLogIn *ui;

private slots:
    void ok();
};

#endif // USERLOGIN_H
