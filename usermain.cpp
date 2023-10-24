#include "usermain.h"
#include "ui_usermain.h"

userMain::userMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userMain)
{
    ui->setupUi(this);

}

userMain::~userMain()
{
    delete ui;
}

