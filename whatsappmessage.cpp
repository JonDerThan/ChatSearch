#include "whatsappmessage.h"

WhatsAppMessage::WhatsAppMessage(const QDateTime &dateTime, const QString &author, const QString &content) :
    dateTime{dateTime},
    author{author},
    content{content}
{

}

void WhatsAppMessage::append(const QString &text)
{
    content.append("\n" + text);
}

QDateTime WhatsAppMessage::getDateTime() const
{
    return dateTime;
}

QString WhatsAppMessage::getAuthor() const
{
    return author;
}

QString WhatsAppMessage::getContent() const
{
    return content;
}
