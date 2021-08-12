#ifndef STREAK_H
#define STREAK_H

#include "whatsappmessage.h"

class Streak
{
public:
    Streak() = default;
    Streak(const WhatsAppMessage &message);

    bool add(const WhatsAppMessage &message);

    bool messageOnSameDay(const WhatsAppMessage &message);
    bool messageContinuesStreak(const WhatsAppMessage &message);

    QString getAuthor() const;
    int getCount() const;
    QDate getFirstOccurence() const;
    QDate getLastOccurence() const;

    void setAuthor(const QString &value);

private:
    QString author;
    int count;
    QDate firstOccurence;
    QDate lastOccurence;
};

#endif // STREAK_H
