#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qstandarditemmodel.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel *model;
        // Makes it possible to access model in other parts of the program

private:
    Ui::MainWindow *ui;

private slots:
    void buttonPressed();
        // Function to connect User and Administrator buttons with their
        // respective views. See 'mainwindow.cpp' for more information
};

#endif // MAINWINDOW_H
