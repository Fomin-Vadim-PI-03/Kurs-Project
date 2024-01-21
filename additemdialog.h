#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemDialog(QWidget *parent = nullptr);
    ~AddItemDialog();

public slots:
    void submitString();      // slot: Послать введенный текст в главную форму

private:
    Ui::AddItemDialog *ui;

signals:
    void sendText(const QString &text);       // signal: Послать введенный текст в главную форму
};

#endif // ADDITEMDIALOG_H
