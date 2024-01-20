#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , username(username)
{
    ui->setupUi(this);

    ui->WelcomeMessageLabel->setText("Вы вошли как:  " + username);

    this->model = new QStandardItemModel();
    this->proxyModel = new QSortFilterProxyModel();

    proxyModel->setSourceModel(model);
    connect(ui->searchField, SIGNAL(textChanged(const QString&)), proxyModel, SLOT(setFilterFixedString(const QString&)));    // Подключение ui->searchField к proxyModel для функционала поиска по списку
    ui->table->setModel(proxyModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
