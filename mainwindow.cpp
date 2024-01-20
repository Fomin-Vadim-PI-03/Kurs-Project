#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , username(username)
{
    ui->setupUi(this);

    ui->WelcomeMessageLabel->setText("Вы вошли как:  " + username);
}

MainWindow::~MainWindow()
{
    delete ui;
}
