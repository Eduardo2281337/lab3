#ifndef MYSORTINGFILTERPROXYMODEL_H
#define MYSORTINGFILTERPROXYMODEL_H
#include <QSortFilterProxyModel>

class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    MySortFilterProxyModel(QObject *parent = 0) : QSortFilterProxyModel(parent) {}

    // QSortFilterProxyModel interface
protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;
};


#endif // MYSORTINGFILTERPROXYMODEL_H
