#define _CRT_SECURE_NO_WARNINGS

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additemdialog.h"

#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <ctime>


MainWindow::MainWindow(QString username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , username(username)
{
    ui->setupUi(this);

    clientsServed = 0;

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

void MainWindow::addDatabaseItem(){     // slot: Добавить новый элемент в базу данных
    AddItemDialog *form = new AddItemDialog();
    connect(form, &AddItemDialog::sendText, this, &MainWindow::receiveSubmittedEntry);   // Создать связь между сигналом (AddItemDialog::sendText) и слотом (MainWindow::receiveSubmittedEntry)
    form->show();            // Вызов формы ввода нового элемента
}

void MainWindow::receiveSubmittedEntry(const QString &text){   // Получить строку, введенную в AddItemDialog, обработать строку по алгоритму, аналогичному readDatabase()
    std::string s = text.toStdString();
    std::istringstream iss(s);

    std::string type;
    std::string bookID, bookName;
    int numOfCopiesTotal, numOfCopiesLeft, numOfPages;

    if (!(iss >> type >> bookID >> bookName >> numOfCopiesTotal >> numOfCopiesLeft >> numOfPages)) { QMessageBox::warning(this, "Ошибка", "Неверный формат строки."); return; }    // При возникновении ошибки (неверно форматированная информация)

    if (type == "BB") {
        BasicBook* newBook = new BasicBook(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages);
        database.push_back(newBook);
    }
    else if (type == "N") {
        std::string genre, publisher;
        int yearPublished;

        if (!(iss >> genre >> publisher >> yearPublished)) { QMessageBox::warning(this, "Ошибка", "Неверный формат строки."); return; }

        Novel* newBook = new Novel(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, genre, publisher, yearPublished);
        database.push_back(newBook);
    }
    else if (type == "CN") {
        std::string genre, publisher, illustrator, ageGroup;
        int yearPublished;

        if (!(iss >> genre >> publisher >> yearPublished >> illustrator >> ageGroup)) { QMessageBox::warning(this, "Ошибка", "Неверный формат строки."); return; }

        ChildrenNovel* newBook = new ChildrenNovel(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, genre, publisher, yearPublished, illustrator, ageGroup);
        database.push_back(newBook);
    }
    else if (type == "EB") {
        std::string subject, level, author;

        if (!(iss >> subject >> level >> author)) { QMessageBox::warning(this, "Ошибка", "Неверный формат строки."); return; }

        EducationalBook* newBook = new EducationalBook(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, subject, level, author);
        database.push_back(newBook);
    }
    else if (type == "M") {
        int issueNumber;
        std::string month;
        int year;

        if (!(iss >> issueNumber >> month >> year)) { QMessageBox::warning(this, "Ошибка", "Неверный формат строки."); return; }

        Magazine* newBook = new Magazine(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, issueNumber, month, year);
        database.push_back(newBook);
    }
    else if (type == "SM") {
        int issueNumber;
        std::string month, topic;
        int year;

        if (!(iss >> issueNumber >> month >> year >> topic)) { QMessageBox::warning(this, "Ошибка", "Неверный формат строки."); return; }

        ScienceMagazine* newBook = new ScienceMagazine(bookID, bookName, numOfCopiesTotal, numOfCopiesLeft, numOfPages, issueNumber, month, year, topic);
        database.push_back(newBook);
    }

    QStandardItem *item = new QStandardItem(s.c_str());    // Отразить изменения в ui->table
    model->appendRow(item);                                // ^^
}

void MainWindow::deleteDatabaseItem(){  // slot: Удалить элемент из базы данных

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

void MainWindow::giveBook(){                // slot: Выдать копии книги
    QModelIndex selected = ui->table->currentIndex();         // Получение индекса выбранного элемента
    if (selected.isValid())   //Проверка - Выбрана ли запись в table?
    {
        if(!(ui->BooksNumLineEdit->text().isEmpty()) && !(ui->ClientNameLineEdit->text().isEmpty())){   //Проверка - введены ли Имя Пользователя и Количество Копий?
            QModelIndex sourceIndex = proxyModel->mapToSource(selected);    // Получение настоящего индекса элемента из model, а не из proxy (необходимо для функции поиска)
            int index = sourceIndex.row();                                  // Перевод настоящего индекса элемента в int
            if (index >= 0 && index < database.size())   //Доп. проверка - Имеет ли индекс вектора допустимое значение?
            {
                if(!(database[index]->giveCopies(ui->BooksNumLineEdit->text().toInt()))){
                    QMessageBox::warning(this, "Ошибка", "Ошибка при выдаче.\nНедостаточно книг для выдачи или введено неверное значение.");
                }
                else {
                    std::ofstream file;
                    file.open("logbook.txt", std::ios::app);

                    if (!file.is_open()) {
                        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл лога.");
                    }else{
                        std::time_t now = std::time(nullptr);      // Для вывода локального времени в лог (logbook.txt)
                        std::tm* ptm = std::localtime(&now);       // ^^
                        char buffer[32];                           // ^^
                        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S: ", ptm);

                        std::string timeStr = buffer;

                        file << timeStr << username.toStdString() << " выдал(-а) книгу " << database[index]->getID() << " клиенту " << ui->ClientNameLineEdit->text().toStdString() << " в кол-ве " << ui->BooksNumLineEdit->text().toStdString() << " шт." << std::endl;
                        file.close();
                    }

                    this->writeDatabase();
                    this->refreshDatabase();

                    ui->ClientCounterLabel->setNum(++clientsServed);
                }
            }
        }else{
            QMessageBox::warning(this, "Ошибка", "Введите число копий и имя клиента.");
        }
    }
}

void MainWindow::receiveBook(){         // slot: Получить (вернуть) копии книги
    QModelIndex selected = ui->table->currentIndex();         // Получение индекса выбранного элемента
    if (selected.isValid())   //Проверка - Выбрана ли запись в table?
    {
        if(!(ui->BooksNumLineEdit->text().isEmpty()) && !(ui->ClientNameLineEdit->text().isEmpty())){   //Проверка - введены ли Имя Пользователя и Количество Копий?
            QModelIndex sourceIndex = proxyModel->mapToSource(selected);    // Получение настоящего индекса элемента из model, а не из proxy (необходимо для функции поиска)
            int index = sourceIndex.row();                                  // Перевод настоящего индекса элемента в int
            if (index >= 0 && index < database.size())   //Доп. проверка - Имеет ли индекс вектора допустимое значение?
            {
                if(!(database[index]->receiveCopies(ui->BooksNumLineEdit->text().toInt()))){
                    QMessageBox::warning(this, "Ошибка", "Ошибка при выдаче.\nСлишком много книг для возврата или введено неверное значение.");
                }
                else {
                    std::ofstream file;
                    file.open("logbook.txt", std::ios::app);

                    if (!file.is_open()) {
                        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл лога.");
                    }else{
                        std::time_t now = std::time(nullptr);      // Для вывода локального времени в лог (logbook.txt)
                        std::tm* ptm = std::localtime(&now);       // ^^
                        char buffer[32];                           // ^^
                        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S: ", ptm);

                        std::string timeStr = buffer;

                        file << timeStr << username.toStdString() << " принял(-а) книгу " << database[index]->getID() << " от клиента " << ui->ClientNameLineEdit->text().toStdString() << " в кол-ве " << ui->BooksNumLineEdit->text().toStdString() << " шт." << std::endl;
                        file.close();
                    }

                    this->writeDatabase();
                    this->refreshDatabase();

                    ui->ClientCounterLabel->setNum(++clientsServed);
                }
            }
        }else{
            QMessageBox::warning(this, "Ошибка", "Введите число копий и имя клиента.");
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
