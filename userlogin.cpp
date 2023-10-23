#include "userlogin.h"
#include "ui_userlogin.h"

#include "usermain.h"

UserLogIn::UserLogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLogIn)
{
    ui->setupUi(this);

    QPushButton *button = UserLogIn::findChild<QPushButton *>("pushButton");
    connect(button, SIGNAL(released()), this, SLOT(signOn()));
}

UserLogIn::~UserLogIn()
{
    delete ui;
}

void UserLogIn::signOn() {

    QString userFullName = ui->lineEdit->text();
    userMain letsgo;
    this->hide();
    letsgo.setModal(true);
    letsgo.exec();

}

