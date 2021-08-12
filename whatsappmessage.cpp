#include "whatsappmessage.h"

WhatsAppMessage::WhatsAppMessage(const QRegularExpressionMatch &match) :
    dateTime{
        QDate{
            ("20" + match.captured(3)).toInt(),
            match.captured(2).toInt(),
            match.captured(1).toInt()
        },
        QTime{
            match.captured(4).toInt(),
            match.captured(5).toInt()
        }},
    author{match.captured(6)},
    content{match.captured(7)}
{

}

void WhatsAppMessage::append(const QRegularExpressionMatch &match)
{
    content.append("\n" + match.captured(0));
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
