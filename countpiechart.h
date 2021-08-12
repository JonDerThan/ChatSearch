#ifndef COUNTPIECHART_H
#define COUNTPIECHART_H

#define MAXIMUM_HUE 359

#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

#include "phrasecounter.h"

class CountPieChart : public QWidget
{
    Q_OBJECT
public:
    explicit CountPieChart(PhraseCounter &counter, QWidget *parent = nullptr);

private:
    PhraseCounter &counter;
    QPieSeries *series;

private slots:
    void updateChart();
};

#endif // COUNTPIECHART_H
