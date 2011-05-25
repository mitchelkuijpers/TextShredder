#ifndef FILEDATAPACKET_H
#define FILEDATAPACKET_H

#include "textshredderpacket.h"

class FileDataPacket : public TextShredderPacket
{
	Q_OBJECT
public:
	/**
	 * Constructor, sets values and appends the content to the bytearray
	 * @param *parent To have access to the Q methods
	 * @param content A bytearray which holds the packet content
	 * @param connectionHandle Holds the internal location of the packet.
	 */
	FileDataPacket(QObject *parent, QByteArray &content, quint16 connectionHandle);
	/**
	 * Get the file content from the packet parameter
	 * @param packet The textshredderpacket which holds the data
	 * @return QByteArray which holds the filedata.
	 */
	static QByteArray getFileDataContent(TextShredderPacket &packet);
	/**
	 * Get the connection handle from the packet parameter
	 * @param packet The textshredderpacket which holds the data
	 * @return Quint16 Which holds the internal location of the packet
	 */
	static quint16 getConnectionHandle(TextShredderPacket &packet);
};

#endif // FILEDATAPACKET_H
