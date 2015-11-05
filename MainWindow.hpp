#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include "TaskListModel.hpp"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* mp_ui;
    TaskListModel* mp_taskListModel;
    QDataWidgetMapper* mp_mapper;

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
};

#endif
