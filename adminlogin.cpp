#include "adminlogin.h"
#include "ui_adminlogin.h"

#include "adminmain.h"

AdminLogIn::AdminLogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogIn)
{
    ui->setupUi(this);


    QPushButton *button = AdminLogIn::findChild<QPushButton *>("pushButton");
    connect(button, SIGNAL(released()), this, SLOT(signIn()));

}

AdminLogIn::~AdminLogIn()
{
    delete ui;
}


void AdminLogIn::signIn() {

    QString pass = ui->lineEdit->text();
    if (QString::compare(pass, "password")) {
        ui->lineEdit->setText("Incorrect Password");
    } else {
        adminMain signIn;
        this->hide();
        signIn.setModal(true);
        signIn.exec();
    }
        // Code for simple log in. This isn't the focus of the program, soooo
        // password is password!
        // Also no ***** stuff!
        // If it works it works!
}
