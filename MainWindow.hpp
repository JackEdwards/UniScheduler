#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QDebug>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include <QCheckBox>
#include <QMap>
#include <QFile>
#include <QXmlStreamReader>
#include <QLayout>
#include <QActionGroup>
#include <QTableView>
#include "Task.hpp"
#include "AddTaskDialog.hpp"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* mp_ui;
    QMap<QDate, QVector<Task> > m_taskMap;
    QAction* mp_addTaskAction;
    QString m_taskFilePath;

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void AddTask(const Task& task);
    void UpdateCheckBoxes();
private:
    void LoadTasksFromFile();
    void SaveTasksToFile();
private slots:
    void on_taskCalendar_selectionChanged();
    void customMenuRequested(QPoint point);
    void addTask();
    void updateComplete(bool checked);
};

#endif
