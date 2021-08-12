#include "countpiechart.h"

CountPieChart::CountPieChart(PhraseCounter &counter, QWidget *parent) :
    QWidget(parent),
    counter{counter}
{
    this->series = new QPieSeries();

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);

    connect(&counter, &PhraseCounter::searchCompleted,
            this, &CountPieChart::updateChart);
}

void CountPieChart::updateChart()
{
    series->clear();

    const QVector<QPair<QString, int>> &users{counter.getUsers()};

    QColor color{};
    color.setHsv(0, 255, 255);
    const int colorIncrement{MAXIMUM_HUE / std::max(1, users.length())};

    for (const QPair<QString, int> &user: users) {
        QString label{user.first + " (" + QString::fromStdString(std::to_string(user.second)) + ")"};

        QPieSlice *slice = new QPieSlice(label, user.second);
        slice->setColor(color);

        series->append(slice);

        color.setHsv(std::min(color.hue() + colorIncrement, MAXIMUM_HUE), 255, 255);
    }

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelOutside);
}
