#include "loginform.h"
#include "ui_loginform.h"

#include <QMessageBox>
#include <fstream>

LoginForm::LoginForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginForm)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);  // Отключение кнопки "Помощь"

    ui->setupUi(this);

    std::ifstream file("user_data.txt");
    std::string username, password;

    while (file >> username >> password) {    // Чтение логинов и паролей из файла
        usernames.push_back(username);
        passwords.push_back(password);
    }

    file.close();
}

void LoginForm::SubmitCredentials()            // slot: Вызов при нажатии на кнопку "Войти"
{
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    bool found = false;
    for (int i = 0; i < usernames.size(); ++i) {        // Проверка - совпадают ли введенные данные с данными из файла
        if (login == QString::fromStdString(usernames[i]) && password == QString::fromStdString(passwords[i])) {
            found = true;
            break;
        }
    }

    if (found) {
        this->accept();       // Если введенные данные совпадают - разрешить перейти к главной форме (пояснение в main.cpp)
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль");
    }
}

QString LoginForm::getEnteredUsername() const {         // Получить введенное имя пользователя
    return ui->loginLineEdit->text();
}

LoginForm::~LoginForm()
{
    delete ui;
}
