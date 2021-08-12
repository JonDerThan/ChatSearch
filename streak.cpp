#include "streak.h"

Streak::Streak(const WhatsAppMessage &message) :
    author{message.getAuthor()},
    count{1},
    firstOccurence{message.getDateTime().date()},
    lastOccurence{firstOccurence}
{

}

bool Streak::add(const WhatsAppMessage &message)
{
    if (messageContinuesStreak(message)) {
        count++;
        lastOccurence = message.getDateTime().date();

        return true;
    }

    else return false;
}

bool Streak::messageOnSameDay(const WhatsAppMessage &message)
{
    return lastOccurence.daysTo(message.getDateTime().date()) == 0;
}

bool Streak::messageContinuesStreak(const WhatsAppMessage &message)
{
    return lastOccurence.daysTo(message.getDateTime().date()) == 1;
}

QString Streak::getAuthor() const
{
    return author;
}

int Streak::getCount() const
{
    return count;
}

QDate Streak::getFirstOccurence() const
{
    return firstOccurence;
}

QDate Streak::getLastOccurence() const
{
    return lastOccurence;
}

void Streak::setAuthor(const QString &value)
{
    author = value;
}
