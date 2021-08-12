#ifndef STREAKTABLE_H
#define STREAKTABLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTableWidget>

#include "phrasecounter.h"

class StreakTable : public QWidget
{
    Q_OBJECT
public:
    explicit StreakTable(PhraseCounter &counter, QWidget *parent = nullptr);

private:
    PhraseCounter &counter;
    QTableWidget *table;

private slots:
    void updateTable();

signals:

};

#endif // STREAKTABLE_H
