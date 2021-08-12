#ifndef WHATSAPPMESSAGE_H
#define WHATSAPPMESSAGE_H

#include <QDateTime>
#include <QRegularExpressionMatch>

class WhatsAppMessage
{
public:
    WhatsAppMessage() = default;
    WhatsAppMessage(const QRegularExpressionMatch &match);

    void append(const QRegularExpressionMatch &match);

    QDateTime getDateTime() const;
    QString getAuthor() const;
    QString getContent() const;

private:
    const QDateTime dateTime;
    const QString author;
    QString content;
};

#endif // WHATSAPPMESSAGE_H
