#include "phrasecounter.h"

PhraseCounter::PhraseCounter(QObject *parent) :
    QObject(parent),
    onlyContain{false}
{
    loadNames();
}

void PhraseCounter::setChat(const WhatsAppChat &value)
{
    chat = value;
}

QVector<QPair<QString, int>> PhraseCounter::getUsers() const
{
    QVector<QPair<QString, int>> userList;

    for (const QString &key: users.keys()) {
        userList.append(QPair<QString, int>{getName(key), users.value(key)});
    }

    std::sort(userList.begin(), userList.end(),
              [](const QPair<QString, int> &user1, const QPair<QString, int> &user2)
    {
        return user1.second > user2.second;
    });

    return userList;
}

QVector<Streak> PhraseCounter::getStreaks() const
{
    QVector<Streak> streakList;

    for (const Streak &streak: streaks) {
        Streak newStreak = streak;

        newStreak.setAuthor(getName(streak.getAuthor()));

        streakList.append(newStreak);
    }

    return streakList;
}

const QVector<QPair<QDate, int> > &PhraseCounter::getDays() const
{
    return daysList;
}

void PhraseCounter::search()
{
    users.clear();
    streaks.clear();
    activeStreaks.clear();
    days.clear();

    for (int i = 0; i < chat.length(); i++) {
        const WhatsAppMessage &message = chat[i];

        if (messageMatches(message)) {
            if (activeStreaks.contains(message.getAuthor())) {
                Streak &streak = activeStreaks[message.getAuthor()];

                if (streak.messageOnSameDay(message)) continue;


                if (!streak.add(message)) {
                    streaks.append(streak);

                    activeStreaks.remove(message.getAuthor());
                    activeStreaks.insert(message.getAuthor(), Streak{message});
                }
            }

            else {
                activeStreaks.insert(message.getAuthor(), Streak{message});
            }

            users[message.getAuthor()] += 1;

            const QDate &date = message.getDateTime().date();
            days.insert(date, days.value(date, 0) + 1);
        }
    }

    for (const QString &author : activeStreaks.keys()) {
        streaks.append(activeStreaks.take(author));
    }

    orderStreaks();
    orderDays();

    emit searchCompleted();
}

void PhraseCounter::setEndTime(const QTime &value)
{
    endTime = value;
}

void PhraseCounter::setStartTime(const QTime &value)
{
    startTime = value;
}

void PhraseCounter::setOnlyContain(const bool &value)
{
    onlyContain = value;
}

void PhraseCounter::setCaseSensitive(const bool &value)
{
    caseSensitive = value;
}

void PhraseCounter::setPhrase(const QString &value)
{
    phrase = value;
}

QRegularExpression PhraseCounter::getRegEx() const
{
    QRegularExpression re{};

    if (onlyContain)
        re.setPattern(QRegularExpression::escape(phrase));
    else
        re.setPattern("^" + QRegularExpression::escape(phrase) + "$");

    if (!caseSensitive)
        re.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

    return re;
}

bool PhraseCounter::messageMatches(const WhatsAppMessage &message)
{
    const QTime &messageTime = message.getDateTime().time();
    const QRegularExpressionMatch &match = getRegEx().match(message.getContent());

    return match.hasMatch()
            && messageTime >= startTime
            && messageTime <= endTime;
}

void PhraseCounter::orderStreaks()
{
    int i = 0;
    while (i < streaks.length()) {
        if (streaks.at(i).getCount() < 2) streaks.remove(i);

        else i++;
    }

    std::sort(streaks.begin(), streaks.end(), [](const Streak &streak1, const Streak &streak2) {
        return streak1.getCount() > streak2.getCount();
    });
}

void PhraseCounter::orderDays()
{
    daysList.clear();

    for (const QDate &date : days.keys()) {
        daysList.append(QPair<QDate, int>{date, days.value(date)});
    }

    std::sort(daysList.begin(), daysList.end(), [](const QPair<QDate, int> &day1, const QPair<QDate, int> &day2) {
        return day1.second > day2.second;
    });
}

void PhraseCounter::loadNames()
{
    QFile namesFile{"./names.txt"};

    if (namesFile.exists()) {
        namesFile.open(QIODevice::ReadOnly);
        const QString &namesStr = namesFile.readAll();
        namesFile.close();

        for (const QString &entry: namesStr.split("\n")) {
            const auto &x = entry.split("=");

            if (x.length() == 2) {
                names.insert(x[0].trimmed(), x[1].trimmed());
            }
        }
    }
}

QString PhraseCounter::getName(const QString &key) const
{
    if (names.contains(key)) return names.value(key);

    else return key;
}
