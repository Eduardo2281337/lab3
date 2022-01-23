#ifndef LISTVIEWMEDIATOR_H
#define LISTVIEWMEDIATOR_H

#include "FileBrowserObserver.h"
#include "FileBrowserModel.h"
#include <QTableView>
#include "MySortingFilterProxyModel.h"


class ListViewMediator : public FileBrowserObserver
{
private:
    FileBrowserModel* model;
    MySortFilterProxyModel* proxyModel;
    QTableView* view;
public:
    explicit ListViewMediator(QLayout* l);
    ~ListViewMediator();
    void UpdateDisplay(const QList<Data> &data) override;
};



#endif // LISTVIEWMEDIATOR_H
