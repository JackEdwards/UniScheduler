#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    mp_ui(new Ui::MainWindow)
{
    mp_ui->setupUi(this);

    QDate birthday(1994, 9, 20);

    QVector<Task> tasks;
    tasks.push_back(Task("First task", QDate::currentDate()));
    tasks.push_back(Task("Second task", birthday));

    mp_taskListModel = new TaskListModel(tasks);
    mp_mapper = new QDataWidgetMapper();

    mp_mapper->setModel(mp_taskListModel);
    mp_mapper->addMapping(mp_ui->plainTextEdit, TaskListModel::ColumnType::Date);
    mp_mapper->addMapping(mp_ui->calendarWidget, TaskListModel::ColumnType::Date);
    mp_mapper->setCurrentIndex(1);

    mp_ui->taskListView->setModel(mp_taskListModel);
}

MainWindow::~MainWindow()
{
    // git test
    delete mp_ui;
}
