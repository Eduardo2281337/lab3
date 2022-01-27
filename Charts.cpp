#include "Charts.h"
#include <QBarSeries>
#include <QPieSeries>
#include <QAreaSeries>
#include <QLineSeries>
#include <QBarSet>
#include <QGraphicsLayout>
#include <QChartView>
#include <QLayout>


using namespace QtCharts;


Charts::~Charts()
{
    delete chart_model;
    delete chart_view;
}

Charts::Charts(QLayout *l)
{
    chart_model = new QChart();
    chart_view = new QChartView();
    chart_view->setRenderHint(QPainter::Antialiasing); // сглаживание
    // отображаем легенду справа
    chart_model->legend()->setAlignment(Qt::AlignRight);
    chart_view->setChart(chart_model);
    addWidgetToLayout(l);
}

void Charts::setChart(const QList<Data> &data) const
{
    // подсчитываем общий размер папки
    qint64 total_size = 0;
    for (auto& x : data) {
        total_size += x._size;
    }
    chart_model->setTitle("");
    // в случае когда папка пуста выводим надпись
    if (total_size == 0 || data.isEmpty()) {
        chart_model->setTitle("Folder is empty");
        chart_model->removeAllSeries();
        return;
    }
    // элементы идущие после 6 относим к маленьким
    // подсчитываем их общий размер и размещаем их в категорию others
    if (data.size() > 6) {
        QList<Data> data2;
        for (int i = 0; i < 6 ; i++) {
            data2.append(data.at(i));
        }
        qint64 others_size = 0;
        auto it = data.begin() + 5;
        while (it != data.end()) {
            others_size += it->_size;
            it++;
        }


        data2.push_back(Data("Others", others_size, (qreal)others_size / total_size));
        setDataToChart(data2);
        return;
    }
    // набор данных устанавливаются в диаграмму
    setDataToChart(data);
}

void Charts::addWidgetToLayout(QLayout *l)
{
    l->addWidget(chart_view);
}

void Charts::UpdateDisplay(const QList<Data>& data)
{
    setChart(data);
}


void Charts::removeSeriesFromChart(QChart *c) const
{
    c->removeAllSeries();
}

void Charts::addAxes() const
{

}

void Charts::addSeriesToChart(QList<QAbstractSeries*> series) const
{
    for (auto& x : series) {
        chart_model->addSeries(x);
    }
}



// шаблонный метод
void Charts::setDataToChart(const QList<Data> &data) const
{
    removeSeriesFromChart(chart_model);
    QList<QAbstractSeries*> series = addDataToSeries(data);
    addSeriesToChart(series);
    addAxes();
}


BarChart::BarChart(QLayout *l) : Charts(l) {}


QList<QAbstractSeries*> BarChart::addDataToSeries(const QList<Data> &data) const
{
    QBarSeries* series = new QBarSeries();
    series->setBarWidth(1);
    for (auto& item : data) {
        if (item._ratio < 0) {
            QBarSet* set = new QBarSet(item._name + QString("(< 0.01 %)").toHtmlEscaped());
            set->append(std::abs(item._ratio));
            series->append(set);
        } else {
            QBarSet* set = new QBarSet(item._name + "(" + QString::number(item._ratio * 100 , 'f', 2) + " %)");
            set->append(item._ratio);
            series->append(set);
        }
    }
    return QList<QAbstractSeries*> {series};
}


PieChart::PieChart(QLayout *l) : Charts(l) {}


QList<QAbstractSeries*> PieChart::addDataToSeries(const QList<Data> &data) const
{
    QPieSeries* series = new QPieSeries();
    series->setPieSize(1);
    for (auto& item : data) {
        if (item._ratio < 0) {
            series->append(item._name + QString("(< 0.01 %)").toHtmlEscaped(), std::abs(item._ratio));
        } else {
            series->append(item._name + "(" + QString::number(item._ratio * 100, 'f', 2) + " %)", item._ratio);
        }
    }
    return QList<QAbstractSeries*> {series};
}

AreaChart::AreaChart(QLayout *l) : Charts(l) {}

void AreaChart::addAxes() const
{
    chart_model->createDefaultAxes();
    QList<QAbstractAxis *> vertical_axes = chart_model->axes(Qt::Vertical);
    vertical_axes.first()->setRange(0, 100);
}

QList<QAbstractSeries*> AreaChart::addDataToSeries(const QList<Data> &data) const
{
    QList<QAbstractSeries*> area_series;
    QLineSeries* lower_series = 0;
    for (int i = 0; i < data.size(); i++) {
        QLineSeries *upper_series = new QLineSeries();
        if (lower_series) {
            QVector<QPointF> points = lower_series->pointsVector();
            *upper_series << QPointF(0, data.at(i)._ratio * 100 + points[0].y()) << QPointF(1, data.at(i)._ratio * 100 + points[0].y());
        } else {
            *upper_series << QPointF(0, data.at(i)._ratio * 100) << QPointF(1, data.at(i)._ratio * 100);
        }
        area_series.append(new QAreaSeries(upper_series, lower_series));
        if (data.at(i)._ratio < 0) {
            area_series.at(i)->setName(data.at(i)._name + QString("(< 0.01 %)").toHtmlEscaped());
        } else {
            area_series.at(i)->setName(data.at(i)._name + " (" + QString::number(data.at(i)._ratio * 100, 'f', 2) + " %)");
        }

        lower_series = upper_series;
    }
    return area_series;
}
