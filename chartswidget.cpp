#include "chartswidget.h"

ChartsWidget::ChartsWidget(PhraseCounter &counter, QWidget *parent) : QWidget(parent)
{
    CountTable *countTable = new CountTable(counter, this);
    CountPieChart *countPieChart = new CountPieChart(counter, this);
    StreakTable *streakTable = new StreakTable(counter, this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(countTable);
    layout->addWidget(countPieChart);
    layout->addSpacerItem(new QSpacerItem{50, 20, QSizePolicy::Minimum, QSizePolicy::Minimum});
    layout->addWidget(streakTable);
}
