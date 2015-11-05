#include "Task.hpp"

Task::Task() { }

Task::Task(const QString& content)
    : m_content(content) { }

Task::Task(const QString& content, const QDate& date)
    : m_content(content), m_date(date) { }

const QString& Task::GetContent() const
{
    return m_content;
}

const QDate& Task::GetDate() const
{
    return m_date;
}

void Task::SetContent(const QString& content)
{
    m_content = content;
}

void Task::SetDate(const QDate& date)
{
    m_date = date;
}
