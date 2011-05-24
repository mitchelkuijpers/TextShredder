#include "onlineuserspacket.h"

OnlineUsersPacket::OnlineUsersPacket(QObject *parent, QList<QString> userList)
	: TextShredderPacket(parent, kPacketTypeOnlineUsers)
{
	QByteArray bytes;
	if (userList.count() > 0) {
		bytes.append(userList.at(0));
		for (int i = 1; i < userList.count(); i++ ) {
			bytes.append(",");
			bytes.append(userList.at(i));
		}
	}
	this->setContent(bytes);
}

QList<QString> OnlineUsersPacket::userListFromPacket(TextShredderPacket & packet)
{
	QList<QString> userList;
	QByteArray contentCopy(packet.getContent());
	while (contentCopy.size() > 0 ) {
		QByteArray chunk = splitContentTillCharacter(contentCopy, ',');
		userList.append(QString(chunk));
	}
	return userList;
}

QByteArray OnlineUsersPacket::splitContentTillCharacter(QByteArray &original, char c)
{
	QByteArray returnValue;
	int count = 0;
	while ( count < original.size()) {
		if (original.at(count) == c) {
			returnValue.append(original.mid(0, count));
			original.remove(0,count+1);
			return returnValue;
		}
		count++;
	}
	returnValue.append(original);
	original.clear();
	return returnValue;
}

