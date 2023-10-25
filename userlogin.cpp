#include "userlogin.h"
#include "ui_userlogin.h"

userLogIn::userLogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userLogIn)
{
    ui->setupUi(this);

    // Dialog Button thinga ma bob
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &userLogIn::ok);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

userLogIn::~userLogIn()
{
    delete ui;
}

void userLogIn::ok() {


    accept();
}
