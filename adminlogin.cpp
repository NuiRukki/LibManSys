#include "adminlogin.h"
#include "ui_adminlogin.h"

AdminLogIn::AdminLogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogIn)
{
    ui->setupUi(this);
}

AdminLogIn::~AdminLogIn()
{
    delete ui;
}
