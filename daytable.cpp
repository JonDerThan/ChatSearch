#include "daytable.h"

DayTable::DayTable(PhraseCounter &counter, QWidget *parent) :
    QWidget(parent),
    counter{counter}
{
    table = new QTableWidget(0, 2, this);
    table->setHorizontalHeaderLabels(QStringList{"Day", "Count"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    table->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(table);

    connect(&counter, &PhraseCounter::searchCompleted,
            this, &DayTable::updateTable);
}

void DayTable::updateTable()
{
    table->clearContents();

    const QVector<QPair<QDate, int>> &days = counter.getDays();

    table->setRowCount(days.size());

    for (int i = 0; i < days.length(); i++) {
        QTableWidgetItem *dateItem = new QTableWidgetItem(days[i].first.toString("yyyy-MM-dd")),
                *count = new QTableWidgetItem(QString::fromStdString(std::to_string(days[i].second)));

        table->setItem(i, 0, dateItem);
        table->setItem(i, 1, count);
    }
}
