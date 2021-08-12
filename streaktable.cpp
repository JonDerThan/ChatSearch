#include "streaktable.h"

StreakTable::StreakTable(PhraseCounter &counter, QWidget *parent) :
    QWidget(parent),
    counter{counter}
{
    table = new QTableWidget(0, 2, this);
    table->setHorizontalHeaderLabels(QStringList{"Name", "Streak"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    table->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(table);

    connect(&counter, &PhraseCounter::searchCompleted,
            this, &StreakTable::updateTable);
}

void StreakTable::updateTable()
{
    table->clearContents();

    const QVector<Streak> &streaks = counter.getStreaks();

    table->setRowCount(streaks.length());

    for (int i = 0; i < streaks.length(); i++) {
        QTableWidgetItem *name = new QTableWidgetItem(streaks[i].getAuthor()),
                *count = new QTableWidgetItem(QString::fromStdString(std::to_string(streaks[i].getCount())));

        table->setItem(i, 0, name);
        table->setItem(i, 1, count);
    }
}
