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

public:
    Task();
    Task(const QString& content);
    Task(const QString& content, const QString& module);
    Task(const QString& content, const QDate& date);
    Task(const QString& content, const QString& module, const QDate& date);
    const QString& GetContent() const;
    const QString& GetModule() const;
    const QDate& GetDate() const;
    void SetContent(const QString& content);
    void SetModule(const QString& module);
    void SetDate(const QDate& date);
};

#endif
