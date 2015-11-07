#ifndef ADDTASKDIALOG_HPP
#define ADDTASKDIALOG_HPP

#include <QDialog>
#include <QDebug>
#include <MainWindow.hpp>

namespace Ui
{
    class AddTaskDialog;
}

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget* parent = 0);
    ~AddTaskDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddTaskDialog* mp_ui;
};

#endif
