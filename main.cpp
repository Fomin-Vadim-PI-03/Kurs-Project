#include "mainwindow.h"
#include "loginform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginForm loginForm;
    if (loginForm.exec() != QDialog::Accepted) {     // После выполнения loginForm - закрытие программы, если пользователь не ввел верные логин и пароль
        return 1;
    }

    MainWindow w(loginForm.getEnteredUsername());    // Конструктор MainWindow принимает имя пользователя, полученное из LoginForm
    w.show();
    return a.exec();
}
