#include "counttable.h"

CountTable::CountTable(PhraseCounter &counter, QWidget *parent)  :
    QWidget(parent),
    counter{counter}
{
    table = new QTableWidget(0, 2, this);
    table->setHorizontalHeaderLabels(QStringList{"Name", "Count"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    table->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(table);

    connect(&counter, &PhraseCounter::searchCompleted,
            this, &CountTable::updateTable);
}

void CountTable::updateTable()
{
    table->clearContents();

    const QVector<QPair<QString, int>> &users = counter.getUsers();

    table->setRowCount(users.length());

    for (int i = 0; i < users.length(); i++) {
        QTableWidgetItem *name = new QTableWidgetItem(users[i].first),
                *count = new QTableWidgetItem(QString::fromStdString(std::to_string(users[i].second)));

        table->setItem(i, 0, name);
        table->setItem(i, 1, count);
    }
}
