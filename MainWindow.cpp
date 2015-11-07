#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    mp_ui(new Ui::MainWindow)
{
    mp_ui->setupUi(this);
    m_taskFilePath = QCoreApplication::applicationDirPath() + "/tasks.xml";

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

    SaveTasksToFile();
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
            checkBox->setChecked(task.IsComplete());
            connect(checkBox, SIGNAL(clicked(bool)), this, SLOT(updateComplete(bool)));
            mp_ui->taskListFrame->layout()->addWidget(checkBox);
            checkBox->show();
        }
    }
}

void MainWindow::LoadTasksFromFile()
{
    QFile file(m_taskFilePath);

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
                    QString completeText = reader.attributes().value("complete").toString();
                    bool complete = completeText == "true" ? true : false;
                    QString content = reader.readElementText();

                    m_taskMap[date].push_back(Task(content, module, date, complete));
                }
            }
        }

        file.close();

        if (reader.hasError())
            qDebug() << "XML reader error: " << reader.errorString();
    }
}

void MainWindow::SaveTasksToFile()
{
    QFile file(m_taskFilePath);

    if (file.open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);

        writer.writeStartDocument();
        writer.writeStartElement("Tasks");

        QMap<QDate, QVector<Task> >::const_iterator i;
        for (i = m_taskMap.begin(); i != m_taskMap.end(); ++i)
        {
            for (const Task& task : i.value())
            {
                if (task.IsComplete())
                    qDebug() << "True!";

                QString completeText = task.IsComplete() ? "true" : "false";

                writer.writeStartElement("Task");
                writer.writeAttribute("date", task.GetDate().toString(Qt::ISODate));
                writer.writeAttribute("module", task.GetModule());
                writer.writeAttribute("complete", completeText);
                writer.writeCharacters(task.GetContent());
                writer.writeEndElement();
            }
        }

        writer.writeEndElement();
        writer.writeEndDocument();

        file.close();
    }
    else
    {
        qDebug() << "Could not open file.";
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
    AddTaskDialog* dialog = new AddTaskDialog(this);
    dialog->exec();
}

void MainWindow::updateComplete(bool checked)
{
    if (checked)
        qDebug() << "Checked";
    else
        qDebug() << "Unchecked";
}
