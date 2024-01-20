#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString username, QWidget *parent = nullptr);   // Конструктор принимает имя пользователя, полученное из LoginForm
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString username;
};
#endif // MAINWINDOW_H
