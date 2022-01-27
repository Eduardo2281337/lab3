#ifndef CHARTSWIDGET_H
#define CHARTSWIDGET_H
#include "Data.h"
#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <memory>
#include <QtCharts/QAbstractSeries>
#include "FileBrowserObserver.h"

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

// базовый класс использующий паттерн шаблонный метод
class Charts : public FileBrowserObserver
{
public:
    virtual ~Charts();
    Charts() = default;
    Charts(QLayout* l);

    void setChart(const QList<Data>& data) const;

    // добавление данных в диаграмму
    void addWidgetToLayout(QLayout* l);
    void UpdateDisplay(const QList<Data>& data) override;
    void setDataToChart(const QList<Data>& data) const;
    void removeSeriesFromChart(QChart* c) const;
    virtual QList<QAbstractSeries*> addDataToSeries(const QList<Data>& data) const = 0;
    virtual void addAxes() const;
    void addSeriesToChart(QList<QAbstractSeries*> series) const;
    QChart* chart_model;
private:
    QChartView* chart_view;

};

// создание круговой диаграммы
class PieChart : public Charts
{
public:
    explicit PieChart(QLayout* l);
    PieChart() = default;
    QList<QAbstractSeries*> addDataToSeries(const QList<Data> &data) const override;
};

//создание вертикальной диаграммы
class BarChart : public Charts
{
public:
    explicit BarChart(QLayout* l);
    BarChart() = default;
    QList<QAbstractSeries*> addDataToSeries(const QList<Data> &data) const override;
};

class AreaChart : public Charts
{
public:
    explicit AreaChart(QLayout* l);
    void addAxes() const override;
    AreaChart() = default;
    QList<QAbstractSeries*> addDataToSeries(const QList<Data> &data) const override;
};


#endif // CHARTSWIDGET_H
