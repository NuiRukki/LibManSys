#include "userlogin.h"
#include "ui_userlogin.h"

UserLogIn::UserLogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLogIn)
{
    ui->setupUi(this);
}

UserLogIn::~UserLogIn()
{
    delete ui;
}
