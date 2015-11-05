#include "TaskListModel.hpp"

TaskListModel::TaskListModel(QObject* parent)
    : QAbstractListModel(parent) { }

TaskListModel::TaskListModel(const QVector<Task>& tasks, QObject* parent)
    : QAbstractListModel(parent), m_tasks(tasks) { }

int TaskListModel::rowCount(const QModelIndex& parent) const
{
    return m_tasks.size();
}

int TaskListModel::columnCount(const QModelIndex& parent) const
{
    return ColumnType::ColumnCount;
}

QVariant TaskListModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    if (!index.isValid())
        return QVariant();

    if (row < 0 || row >= m_tasks.size())
        return QVariant();

    if (column < 0 || column > ColumnType::ColumnCount)
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case ColumnType::Content:
            return m_tasks[row].GetContent();
            break;
        case ColumnType::Date:
            return m_tasks[row].GetDate();
            break;
        }
    }

    return QVariant();
}

Qt::ItemFlags TaskListModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TaskListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    int row = index.row();
    int column = index.column();

    if (index.isValid() && role == Qt::EditRole)
    {
        switch (column)
        {
        case ColumnType::Content:
            m_tasks[row].SetContent(value.toString());
            break;
        case ColumnType::Date:
            m_tasks[row].SetDate(value.toDate());
            break;
        }

        emit dataChanged(index, index);

        return true;
    }

    return false;
}

bool TaskListModel::insertRows(int position, int rows, const QModelIndex& index)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        m_tasks.insert(position, Task());

    endInsertRows();

    return true;
}
