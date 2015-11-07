#include "AddTaskDialog.hpp"
#include "ui_AddTaskDialog.h"

AddTaskDialog::AddTaskDialog(QWidget *parent) :
    QDialog(parent),
    mp_ui(new Ui::AddTaskDialog)
{
    mp_ui->setupUi(this);
}

AddTaskDialog::~AddTaskDialog()
{
    delete mp_ui;
}

void AddTaskDialog::on_buttonBox_accepted()
{
    QString content = mp_ui->contentTextEdit->toPlainText();
    QString module = mp_ui->moduleComboBox->itemText(mp_ui->moduleComboBox->currentIndex());
    QDate date = mp_ui->dateEdit->date();

    MainWindow* mainWindow = static_cast<MainWindow*>(parent());

    mainWindow->AddTask(Task(content, module, date));
    mainWindow->UpdateCheckBoxes();
}
