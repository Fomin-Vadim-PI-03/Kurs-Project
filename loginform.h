#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>

#include <vector>
#include <string>

namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    QString getEnteredUsername() const;         // Получить введенное имя пользователя

public slots:
    void SubmitCredentials();            // slot: Вызов при нажатии на кнопку "Войти"

private:
    Ui::LoginForm *ui;
    std::vector<std::string> usernames;
    std::vector<std::string> passwords;
};

#endif // LOGINFORM_H
