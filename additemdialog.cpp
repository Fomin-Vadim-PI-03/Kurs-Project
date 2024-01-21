#include "additemdialog.h"
#include "ui_additemdialog.h"

AddItemDialog::AddItemDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddItemDialog)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);;      //Отключение кнопки "Помощь"

    ui->setupUi(this);
}

void AddItemDialog::submitString(){             // slot: Послать введенный текст в главную форму
    QString text = ui->lineEdit->text();
    emit sendText(text);         // Текст посылается в MainWindow (Функция receiveSubmittedEntry), связь определяется в addDatabaseItem в MainWindow
    this->close();               // Закрыть форму
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}
