#include "usermain.h"
#include "ui_usermain.h"

//#include "userlogin.h"



userMain::userMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userMain)
{
//    QString name = UserLogIn.userFullName;
    ui->setupUi(this);
//    ui->lineEdit->setText();
}

userMain::~userMain()
{
    delete ui;
}

