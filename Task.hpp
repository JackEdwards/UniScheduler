#ifndef TASK_HPP
#define TASK_HPP

#include <QString>
#include <QDate>

class Task
{
private:
    QString m_content;
    QString m_module;
    QDate m_date;
    bool m_complete;

public:
    Task();
    Task(const QString& content);
    Task(const QString& content, const QString& module);
    Task(const QString& content, const QDate& date);
    Task(const QString& content, const QString& module, const QDate& date);
    Task(const QString& content, const QString& module, const QDate& date, bool complete);
    const QString& GetContent() const;
    const QString& GetModule() const;
    const QDate& GetDate() const;
    bool IsComplete() const;
    void SetContent(const QString& content);
    void SetModule(const QString& module);
    void SetDate(const QDate& date);
    void SetComplete(bool complete);
};

#endif
