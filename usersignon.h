#ifndef USERSIGNON_H
#define USERSIGNON_H

#include <QDialog>

namespace Ui {
class UserSignOn;
}

class UserSignOn : public QDialog
{
    Q_OBJECT

public:
    explicit UserSignOn(QWidget *parent = nullptr);
    ~UserSignOn();

private:
    Ui::UserSignOn *ui;
};

#endif // USERSIGNON_H
