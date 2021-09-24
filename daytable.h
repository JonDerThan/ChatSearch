#ifndef DAYTABLE_H
#define DAYTABLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTableWidget>

#include "phrasecounter.h"

class DayTable : public QWidget
{
    Q_OBJECT
public:
    explicit DayTable(PhraseCounter &counter, QWidget *parent = nullptr);

private:
    PhraseCounter &counter;
    QTableWidget *table;

private slots:
    void updateTable();

signals:

};

#endif // DAYTABLE_H
