#ifndef TASK_HPP
#define TASK_HPP

#include <QString>
#include <QDate>

class Task
{
private:
    QString m_content;
    QDate m_date;

public:
    Task();
    Task(const QString& content);
    Task(const QString& content, const QDate& date);
    const QString& GetContent() const;
    const QDate& GetDate() const;
    void SetContent(const QString& content);
    void SetDate(const QDate& date);
};

#endif
