#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    mp_ui(new Ui::MainWindow)
{
    mp_ui->setupUi(this);
    statusBar()->showMessage("Tasks can be added by right clicking on a date in the calendar!");

    LoadTasksFromFile();

    mp_ui->taskCalendar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mp_ui->taskCalendar, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customMenuRequested(QPoint)));

    mp_addTaskAction = new QAction("Add Task", this);
    connect(mp_addTaskAction, SIGNAL(triggered()), this, SLOT(addTask()));
}

MainWindow::~MainWindow()
{
    delete mp_ui;
}

void MainWindow::AddTask(const Task& task)
{
    m_taskMap[task.GetDate()].push_back(task);
}

void MainWindow::UpdateCheckBoxes()
{
    for (auto& child : mp_ui->taskListFrame->children())
        delete child;

    qDebug() << mp_ui->taskCalendar->selectedDate().toString();

    QDate selectedDate = mp_ui->taskCalendar->selectedDate();

    if (m_taskMap[selectedDate].size() > 0)
    {
        mp_ui->taskListFrame->setLayout(new QVBoxLayout());

        for (Task& task : m_taskMap[selectedDate])
        {
            QCheckBox* checkBox = new QCheckBox(task.GetContent(), mp_ui->taskListFrame);
            mp_ui->taskListFrame->layout()->addWidget(checkBox);
            checkBox->show();
        }
    }
}

void MainWindow::LoadTasksFromFile()
{
    QFile file(":tasks.xml");

    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader reader(&file);

        while (!reader.atEnd())
        {
            reader.readNextStartElement();

            if (reader.isStartElement())
            {
                if (reader.name().toString() == "Task")
                {
                    QDate date = QDate::fromString(reader.attributes().value("date").toString(), Qt::ISODate);
                    QString module = reader.attributes().value("module").toString();
                    QString content = reader.readElementText();

                    m_taskMap[date].push_back(Task(content, module, date));

                    qDebug() << "Date: " << date.toString();
                    qDebug() << "Module: " << module;
                    qDebug() << "Content: " << content;
                }
            }
        }

        file.close();

        if (reader.hasError())
            qDebug() << "Error: " << reader.errorString();
    }
}

void MainWindow::on_taskCalendar_selectionChanged()
{
    UpdateCheckBoxes();
}

void MainWindow::customMenuRequested(QPoint point)
{
    QMenu* menu = new QMenu(this);
    menu->addAction(mp_addTaskAction);
    menu->popup(mp_ui->taskCalendar->mapToGlobal(point));
}

void MainWindow::addTask()
{
    qDebug() << "Task added!";
    AddTaskDialog* dialog = new AddTaskDialog(this);
    dialog->exec();
}
