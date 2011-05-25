#ifndef FILEREQUESTPACKET_H
#define FILEREQUESTPACKET_H

#include "textshredderpacket.h"
#include <stdlib.h>

class FileRequestPacket : public TextShredderPacket
{
public:
	/**
	 * Constructor, sets values and appends the content to the bytearray
	 * @param *parent To have access to the Q methods
	 * @param port The port the server listens on.
	 * @param &fileAlias Holds the name alias of the file
	 */
	FileRequestPacket(QObject *parent, quint16 port, QString &fileAlias);
	/**
	 * Get the source handler of the packet
	 * @param TextShredderPacket & The textshredderpacket which holds the data
	 * @return & The source identifier, the sender of the packet.
	 */
	static quint16 getSourceHandle(TextShredderPacket &);
	/**
	 * Get the file identifier of the packet
	 * @param TextShredderPacket & The textshredderpacket which holds the data
	 * @return The file identifier, unique id of the file
	 */
	static QString getFileIdentifier(TextShredderPacket &);
};

#endif // FILEREQUESTPACKET_H
