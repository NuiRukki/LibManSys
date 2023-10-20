#include "usersignon.h"
#include "ui_usersignon.h"

UserSignOn::UserSignOn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSignOn)
{
    ui->setupUi(this);
}

UserSignOn::~UserSignOn()
{
    delete ui;
}
