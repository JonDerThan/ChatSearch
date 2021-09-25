#include "whatsappchat.h"

const QRegularExpression WhatsAppChat::messageRe{"^(\\d\\d)\\.(\\d\\d)\\.(\\d\\d), (\\d\\d):(\\d\\d) - ([^:]+): (.+)$|^.+$",
                                                QRegularExpression::MultilineOption};

const QString WhatsAppChat::matchEverything{"|^.+$"};

const QMap<WhatsAppChat::ChatType, QRegularExpression> WhatsAppChat::recognizeRegExp{
    std::initializer_list<std::pair<ChatType, QRegularExpression>>{
        std::pair<ChatType, QRegularExpression>{Android_12h, QRegularExpression{
                "^(\\d\\d)\\.(\\d\\d)\\.(\\d\\d), (\\d\\d?):(\\d\\d) ([^ ]+) - ([^:]+): ([^\\r\\n]+)",
                QRegularExpression::MultilineOption
            }},
        std::pair<ChatType, QRegularExpression>{Android_24h, QRegularExpression{
                "^(\\d\\d)\\.(\\d\\d)\\.(\\d\\d), (\\d\\d):(\\d\\d) - ([^:]+): ([^\\r\\n]+)",
                QRegularExpression::MultilineOption
            }},
        std::pair<ChatType, QRegularExpression>{IOS_12h, QRegularExpression{
                "^\\[(\\d\\d)\\.(\\d\\d)\\.(\\d\\d), (\\d\\d?):(\\d\\d):(\\d\\d) (AM|PM)\\] ([^:]+): ([^\\r\\n]+)",
                QRegularExpression::MultilineOption
            }},
        std::pair<ChatType, QRegularExpression>{IOS_24h, QRegularExpression{
                "^\\[(\\d\\d)\\.(\\d\\d)\\.(\\d\\d), (\\d\\d):(\\d\\d):(\\d\\d)\\] ([^:]+): ([^\\r\\n]+)",
                QRegularExpression::MultilineOption
            }}
    }
};

WhatsAppChat::WhatsAppChat(QFile &chatFile)
{
    if (chatFile.open(QIODevice::ReadOnly)) {
        const QString &chatStr = chatFile.readAll();

        chatFile.close();

        this->determineType(chatStr);
        loadFromString(chatStr);
    }

    else throw std::runtime_error("Couldn't open file");
}

WhatsAppChat::ChatType WhatsAppChat::determineType(const QString &chatStr)
{
    QPair<ChatType, int> likelyType{Unknown, 0};

    for (const ChatType &type: recognizeRegExp.keys()) {
        const int &count = chatStr.count(recognizeRegExp.value(type));

        if (count > likelyType.second) {
            likelyType.first = type;
            likelyType.second = count;
        }
    }

    this->type = likelyType.first;
    return likelyType.first;
}

const WhatsAppMessage &WhatsAppChat::operator [](const int &i) const
{
    return messageList.at(i);
}

int WhatsAppChat::length() const
{
    return messageList.length();
}

void WhatsAppChat::loadFromString(const QString &chatStr)
{
    if (type != Unknown) {
        QRegularExpression regExp{
            recognizeRegExp.value(type).pattern() + matchEverything,
            recognizeRegExp.value(type).patternOptions()
        };

        auto matches = regExp.globalMatch(chatStr);

        switch (this->type) {
        case Android_12h: // TODO: either write support for german and english and/or display a proper error message
            throw std::runtime_error("Application can't handle the 12h format on android");

            break;

        case Android_24h:
            while (matches.hasNext()) {
                auto match = matches.next();

                const bool isNewMessage = match.capturedTexts().length() > 1;

                if (isNewMessage) {
                    messageList.append(WhatsAppMessage{
                                           QDateTime{QDate{
                                                         ("20" + match.captured(3)).toInt(),
                                                         match.captured(2).toInt(),
                                                         match.captured(1).toInt()
                                                     },
                                                     QTime{
                                                         match.captured(4).toInt(),
                                                         match.captured(5).toInt()
                                                     }

                                           }, // dateTime
                                           QString{match.captured(6)}, // author
                                           QString{match.captured(7)} // content
                                       });
                }

                else if (!messageList.isEmpty()) messageList.last().append(match.captured(0));
            }
            break;

        case IOS_12h: // edit
            while (matches.hasNext()) {
                auto match = matches.next();

                const bool isNewMessage = match.capturedTexts().length() > 1;

                if (isNewMessage) {
                    QTime time{};

                    if (match.captured(7) == "AM") {
                        time.setHMS(match.captured(4).toInt(), match.captured(5).toInt(), 0);
                    }

                    else {
                        int hours = match.captured(4) == "12" ? 0 : match.captured(4).toInt() + 12;
                        time.setHMS(hours, match.captured(5).toInt(), 0);
                    }

                    messageList.append(WhatsAppMessage{
                                           QDateTime{QDate{
                                                         ("20" + match.captured(3)).toInt(),
                                                         match.captured(2).toInt(),
                                                         match.captured(1).toInt()
                                                     },
                                                     time
                                           }, // dateTime
                                           QString{match.captured(8)}, // author
                                           QString{match.captured(9)} // content
                                       });
                }

                else if (!messageList.isEmpty()) messageList.last().append(match.captured(0));
            }
            break;

        case IOS_24h: // edit
            while (matches.hasNext()) {
                auto match = matches.next();

                const bool isNewMessage = match.capturedTexts().length() > 1;

                if (isNewMessage) {
                    messageList.append(WhatsAppMessage{
                                           QDateTime{QDate{
                                                         ("20" + match.captured(3)).toInt(),
                                                         match.captured(2).toInt(),
                                                         match.captured(1).toInt()
                                                     },
                                                     QTime{
                                                         match.captured(4).toInt(),
                                                         match.captured(5).toInt()
                                                     }

                                           }, // dateTime
                                           QString{match.captured(7)}, // author
                                           QString{match.captured(8)} // content
                                       });
                }

                else if (!messageList.isEmpty()) messageList.last().append(match.captured(0));
            }
            break;

        default:
            throw std::runtime_error("unexpected case");

            break;
        }
    }

    else {
        // TODO: display a proper error message
        throw std::runtime_error("Unknown format");
    }
}

