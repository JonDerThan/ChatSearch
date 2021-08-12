#ifndef WHATSAPPCHAT_H
#define WHATSAPPCHAT_H

#include <QFile>
#include <QVector>
#include <QRegularExpression>

#include "whatsappmessage.h"

class WhatsAppChat
{
public:
    static const QRegularExpression messageRe;

    WhatsAppChat() = default;
    WhatsAppChat(QFile &chatFile);

    const WhatsAppMessage &operator[](const int &i) const;
    int length() const;

private:
    QVector<WhatsAppMessage> messageList;

    void loadFromString(const QString &chatStr);
};

#endif // WHATSAPPCHAT_H
