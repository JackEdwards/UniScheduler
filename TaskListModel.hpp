#ifndef TASKLISTMODEL_HPP
#define TASKLISTMODEL_HPP

#include <QAbstractListModel>
#include <QVector>
#include "Task.hpp"

class TaskListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ColumnType
    {
        Content = 0,
        Module,
        Date,
        ColumnCount
    };
private:
    QVector<Task> m_tasks;

public:
    TaskListModel(QObject* parent = 0);
    TaskListModel(const QVector<Task>& tasks, QObject* parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex());
};

#endif
