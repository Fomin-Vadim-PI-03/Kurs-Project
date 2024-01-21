#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>

#include "basicbook.h"
#include "childrennovel.h"
#include "educationalbook.h"
#include "magazine.h"
#include "novel.h"
#include "sciencemagazine.h"

#include <vector>

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
    void readDatabase();        // Прочитать базу данных из файла
    void writeDatabase();       // Записать базу данных в файл
    void receiveSubmittedEntry(const QString &text);   // Получить строку, введенную в AddItemDialog
    ~MainWindow();

public slots:
    void refreshDatabase();     // slot: Обновить базу данных
    void addDatabaseItem();     // slot: Добавить новый элемент в базу данных
    void deleteDatabaseItem();  // slot: Удалить элемент из базы данных
    void acceptDatabaseChanges(); // slot: Принять изменения в базе данных

private:
    Ui::MainWindow *ui;
    QString username;                    // Имя пользователя, полученное из LoginForm
    std::vector<BasicBook*> database;    // База данных книг библиотеки
    QStandardItemModel *model;           // Модель для ui->table (QListView) - для хранения данных
    QSortFilterProxyModel *proxyModel;   // Proxy для ui->table (QListView) - для системы поиска по списку
};
#endif // MAINWINDOW_H
