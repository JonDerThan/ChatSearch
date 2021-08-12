#include "whatsappchat.h"

const QRegularExpression WhatsAppChat::messageRe{"^(\\d\\d)\\.(\\d\\d)\\.(\\d\\d), (\\d\\d):(\\d\\d) - ([^:]+): (.+)$|^.+$",
                                                QRegularExpression::MultilineOption};

WhatsAppChat::WhatsAppChat(QFile &chatFile)
{
    if (chatFile.open(QIODevice::ReadOnly)) {
        const QString &chatStr = chatFile.readAll();

        chatFile.close();

        loadFromString(chatStr);
    }

    else throw std::runtime_error("Couldn't open file");
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
    auto matches = messageRe.globalMatch(chatStr);

    while (matches.hasNext()) {
        auto match = matches.next();

        const bool isNewMessage = match.capturedTexts().length() > 1;

        if (isNewMessage) messageList.append(WhatsAppMessage{match});

        else if (!messageList.isEmpty()) messageList.last().append(match);
    }
}

