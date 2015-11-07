#include "Task.hpp"

Task::Task() { }

Task::Task(const QString& content)
    : m_content(content) { }

Task::Task(const QString& content, const QString& module)
    : m_content(content), m_module(module) { }

Task::Task(const QString& content, const QDate& date)
    : m_content(content), m_date(date) { }

Task::Task(const QString& content, const QString& module, const QDate& date)
    : m_content(content), m_module(module), m_date(date) { }

Task::Task(const QString& content, const QString& module, const QDate& date, const bool complete)
    : m_content(content), m_module(module), m_date(date), m_complete(complete) { }

const QString& Task::GetContent() const
{
    return m_content;
}

const QString& Task::GetModule() const
{
    return m_module;
}

const QDate& Task::GetDate() const
{
    return m_date;
}

bool Task::IsComplete() const
{
    return m_complete;
}

void Task::SetContent(const QString& content)
{
    m_content = content;
}

void Task::SetModule(const QString& module)
{
    m_module = module;
}

void Task::SetDate(const QDate& date)
{
    m_date = date;
}

void Task::SetComplete(bool complete)
{
    m_complete = complete;
}
