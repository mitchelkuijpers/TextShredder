#ifndef ONLINEUSERSPACKET_H
#define ONLINEUSERSPACKET_H

#include "textshredderpacket.h"

class OnlineUsersPacket : public TextShredderPacket
{
	Q_OBJECT

public:
	OnlineUsersPacket(QObject *packet, QList<QString> userList);

	static QByteArray splitContentTillCharacter(QByteArray &original, char c);
	static QList<QString> userListFromPacket(TextShredderPacket & packet);
};

#endif // ONLINEUSERSPACKET_H
