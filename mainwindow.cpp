#include <string>

#include "adminlogin.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "userlogin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    model = new QStandardItemModel(this);
//    model->setColumnCount(5);
        // This is for the txt file
        // 5 because: ID, Book Name, Book Author, Genre, Inventory

//    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Book Name" << "Author" << "Genre" << "Inventory");


    QPushButton *button[2];
    for (int i = 1; i != 3; i++) {
        QString butName = "Button" + QString::number(i);
        button[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(button[i], SIGNAL(released()), this, SLOT(buttonPressed()));
    }
        // Connects the User and Administrator button with the function
        // buttonPressed() on the signal 'release' of button.
        // Had an error here that connected Button0 and Button1 with the
        // Function instead of Button1 and Button2.

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonPressed() {

    QPushButton *button = (QPushButton *)sender();
    QString butName = button->text();
    std::string name = butName.toStdString();
        // This basically takes the sender button (the one sending the signal released)
        // And takes the text contained in that button and stores it in a string after
        // converting it from QString to string

    if (name == "User") {
        UserLogIn uLogIn;
        this->hide();
        uLogIn.setModal(true);
        uLogIn.exec();
    } else {
        AdminLogIn aLogIn;
        this->hide();
        aLogIn.setModal(true); // test
        aLogIn.exec();
    }
        // If-Else statement that checks if the button signaling is the User or
        // Administrator button. After which hides the main window, makes it so
        // that you can only interact with the new window, and executes that
        // window from what I understand



}
