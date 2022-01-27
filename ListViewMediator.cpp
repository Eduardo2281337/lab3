#include "ListViewMediator.h"
#include "Explorer.h"
#include <QLayout>
#include <QHeaderView>

ListViewMediator::ListViewMediator(QLayout* l)
{
    model = new FileBrowserModel();
    proxyModel = new MySortFilterProxyModel();
    proxyModel->setSourceModel(model);
    qDebug() << proxyModel->filterRole();
    view = new QTableView();
    view->setModel(proxyModel);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    view->setSortingEnabled(true);
    l->addWidget(view);
}

void ListViewMediator::UpdateDisplay(const QList<Data> &data)
{
    model->setModelData(data);
}

ListViewMediator::~ListViewMediator()
{
    delete model;
    delete proxyModel;
    delete view;
}
