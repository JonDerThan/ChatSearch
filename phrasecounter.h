#ifndef PHRASECOUNTER_H
#define PHRASECOUNTER_H

#include <QTime>
#include <QVector>
#include <QObject>
#include <QRegularExpression>

#include "whatsappchat.h"
#include "streak.h"

class PhraseCounter : public QObject
{
    Q_OBJECT
public:
    explicit PhraseCounter(QObject *parent = nullptr);

    void setChat(const WhatsAppChat &value);

    QVector<QPair<QString, int>> getUsers() const;
    QVector<Streak> getStreaks() const;

public slots:
    void search();

    void setPhrase(const QString &value);
    void setCaseSensitive(const bool &value);
    void setOnlyContain(const bool &value);
    void setStartTime(const QTime &value);
    void setEndTime(const QTime &value);

private:
    QString phrase;
    bool caseSensitive;
    bool onlyContain;
    QTime startTime;
    QTime endTime;
    QRegularExpression getRegEx() const;

    WhatsAppChat chat;

    QMap<QString, int> users;
    QMap<QString, Streak> activeStreaks;
    QVector<Streak> streaks;

    bool messageMatches(const WhatsAppMessage &message);

    void orderStreaks();

    QMap<QString, QString> names;
    void loadNames();
    QString getName(const QString &key) const;

signals:
    void searchCompleted();
};

#endif // PHRASECOUNTER_H
