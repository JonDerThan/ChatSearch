#ifndef WHATSAPPCHAT_H
#define WHATSAPPCHAT_H

#include <QFile>
#include <QVector>
#include <QRegularExpression>

#include "whatsappmessage.h"

class WhatsAppChat
{
public:
    static const QRegularExpression messageRe; // remove this variable
    static const QString matchEverything;
    enum ChatType {
        Android_12h,
        Android_24h,
        IOS_12h,
        IOS_24h,
        Unknown
    };

    static const QMap<ChatType, QRegularExpression> recognizeRegExp;

    WhatsAppChat() = default;
    WhatsAppChat(QFile &chatFile);

    ChatType determineType(const QString &chatStr);

    const WhatsAppMessage &operator[](const int &i) const;
    int length() const;

private:
    ChatType type;
    QVector<WhatsAppMessage> messageList;

    void loadFromString(const QString &chatStr);
};

#endif // WHATSAPPCHAT_H
