#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <sstream>

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

    this->refreshDatabase();
}

void MainWindow::readDatabase(){     // Прочитать базу данных из файла

    for (BasicBook* obj : database) {       // Очистить внутреннюю базу данных database
        delete obj;
    }
    database.clear();

    std::ifstream file("database.txt");
    std::string line;

    while (std::getline(file, line)) {      // Считывать файл "database.txt" пока не достигнут конец файла
        std::istringstream iss(line);   // Переменная, в которую записывается очередная строка файла
        std::string type;                                    // Временные переменные для инициализации объектов
        std::string bookID, bookName;                        // ^^
        int numOfCopiesTotal, numOfCopiesLeft, numOfPages;   // ^^

        if (!(iss >> type >> bookID >> bookName >> numOfCopiesTotal >> numOfCopiesLeft >> numOfPages)) { continue; }    // При возникновении ошибки (неверно форматированная строка) - на следующий проход цикла

        if (type == "BB") {
            BasicBook* newBook = new BasicBook(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages);
            database.push_back(newBook);
        }
        else if (type == "N") {
            std::string genre, publisher;
            int yearPublished;

            if (!(iss >> genre >> publisher >> yearPublished)) { continue; }

            Novel* newBook = new Novel(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, genre, publisher, yearPublished);
            database.push_back(newBook);
        }
        else if (type == "CN") {
            std::string genre, publisher, illustrator, ageGroup;
            int yearPublished;

            if (!(iss >> genre >> publisher >> yearPublished >> illustrator >> ageGroup)) { continue; }

            ChildrenNovel* newBook = new ChildrenNovel(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, genre, publisher, yearPublished, illustrator, ageGroup);
            database.push_back(newBook);
        }
        else if (type == "EB") {
            std::string subject, level, author;

            if (!(iss >> subject >> level >> author)) { continue; }

            EducationalBook* newBook = new EducationalBook(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, subject, level, author);
            database.push_back(newBook);
        }
        else if (type == "M") {
            int issueNumber;
            std::string month;
            int year;

            if (!(iss >> issueNumber >> month >> year)) { continue; }

            Magazine* newBook = new Magazine(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, issueNumber, month, year);
            database.push_back(newBook);
        }
        else if (type == "SM") {
            int issueNumber;
            std::string month, topic;
            int year;

            if (!(iss >> issueNumber >> month >> year >> topic)) { continue; }

            ScienceMagazine* newBook = new ScienceMagazine(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, issueNumber, month, year, topic);
            database.push_back(newBook);
        }
    }

    file.close();
}

void MainWindow::writeDatabase(){    // Записать базу данных в файл
    std::ofstream file("database.txt", std::ios::trunc);    //Открыть файл: Создать его, если не существует; Очистить, если существует.
    if (file.is_open()) {
        for (BasicBook* obj : database) {
            file << obj->toString() << "\n";
        }
        file.close();
    }
}

void MainWindow::refreshDatabase(){     // slot: Обновить базу данных
    model->setRowCount(0);    // Очистить ui->table
    this->readDatabase();
    for (BasicBook* obj : database) {   // Составить table заново
        QStandardItem *item = new QStandardItem(obj->toString().c_str());
        model->appendRow(item);
    }
}

void MainWindow::deleteDatabaseItem(){  // slot: Удалить запись из базы данных

    QModelIndex selected = ui->table->currentIndex();   // Получение индекса выбранного элемента
    if (selected.isValid())
    {
        QModelIndex sourceIndex = proxyModel->mapToSource(selected);    // Получение настоящего индекса элемента из model, а не из proxy (необходимо для функции поиска)
        ui->table->model()->removeRow(selected.row());                  // Удаление записи из table
        int index = sourceIndex.row();                                  // Перевод настоящего индекса элемента в int
        if (index >= 0 && index < database.size())
        {
            database.erase(database.begin() + index);    // Удаление объекта из вектора
        }
    }
}

void MainWindow::acceptDatabaseChanges(){   // slot: Принять изменения в базе данных
    this->writeDatabase();
    this->refreshDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}
