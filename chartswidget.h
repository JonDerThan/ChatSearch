#ifndef CHARTSWIDGET_H
#define CHARTSWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

#include "phrasecounter.h"

#include "counttable.h"
#include "countpiechart.h"
#include "streaktable.h"

class ChartsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChartsWidget(PhraseCounter &counter, QWidget *parent = nullptr);

signals:

};

#endif // CHARTSWIDGET_H
