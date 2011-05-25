#ifndef ONLINEUSERSPACKET_H
#define ONLINEUSERSPACKET_H

#include "textshredderpacket.h"

class OnlineUsersPacket : public TextShredderPacket
{
	Q_OBJECT

public:
	/**
	 * Constructor, appends the users to the userlist
	 * @param *parent To have access to the Q methods
	 * @param userList A Qlist which holds the online users
	 */
	OnlineUsersPacket(QObject *packet, QList<QString> userList);
	/**
	 * Searches the &original bytearray and splits it until it comes across the given char c.
	 * @param &original The QByteArray whichs holds the original content.
	 * @param c The character to find which ends the split
	 * @return The QByteArray which holds the online users.
	 */
	static QByteArray splitContentTillCharacter(QByteArray &original, char c);
	/**
	 * Constructor,subtracts the online users from the packet parameter.
	 * appends the users to the list and returns it.
	 * @param packet A TextShredderPacket which holds the data
	 * @return The qlist which holds the online users, substracted from the packet.
	 */
	static QList<QString> userListFromPacket(TextShredderPacket & packet);
};

#endif // ONLINEUSERSPACKET_H
