#include "MySortingFilterProxyModel.h"

// сортировка данных таблицы с учетом особенностей данных выводимых в представление
bool MySortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    QVariant leftData = sourceModel()->data(source_left, Qt::InitialSortOrderRole);
    QVariant rightData = sourceModel()->data(source_right, Qt::InitialSortOrderRole);
    switch (source_left.column()) {
        case 0: return leftData.toString() < rightData.toString();
        case 1:  {
            return leftData.toInt() < rightData.toInt();
        }
        case 2: {
            return leftData.toFloat() < rightData.toFloat();
        }
    }

    return leftData.toString() < rightData.toString();
}
