#include "filerequestpacket.h"

FileRequestPacket::FileRequestPacket(QObject *parent, quint16 port, QString &fileAlias) :
		TextShredderPacket(parent, kPacketTypeFileRequest)
{
	QByteArray newContent;
	newContent.append("{");
	newContent.append(QString::number(port));
	newContent.append(",");
	newContent.append(fileAlias);
	newContent.append("}");
	this->setContent(newContent);
}

quint16 FileRequestPacket::getSourceHandle(TextShredderPacket & packet)
{
	QByteArray bytes = packet.getContent();
	if	(bytes.at(0) != '{') {
		return 0;
	}

	char *pointerToBegin = &(bytes.data()[1]);
	quint16 portValue = atoi(pointerToBegin);
	return portValue;
}

QString FileRequestPacket::getFileIdentifier(TextShredderPacket & packet)
{
	QString contentString(packet.getContent());
	int commaIndex = contentString.indexOf(',');
	return contentString.mid(commaIndex+1, contentString.length() - commaIndex - 2);
}

