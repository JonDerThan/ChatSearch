#ifndef COUNTTABLE_H
#define COUNTTABLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTableWidget>

#include "phrasecounter.h"

class CountTable : public QWidget
{
    Q_OBJECT
public:
    explicit CountTable(PhraseCounter &counter, QWidget *parent = nullptr);

private:
    PhraseCounter &counter;
    QTableWidget *table;

private slots:
    void updateTable();
};

#endif // COUNTTABLE_H
