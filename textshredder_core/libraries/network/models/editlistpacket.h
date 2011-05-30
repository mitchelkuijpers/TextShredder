#ifndef EDITLISTPACKET_H
#define EDITLISTPACKET_H

#include "textshredderpacket.h"
#include "../../synchronization/models/editlist.h"

class EditListPacket : public TextShredderPacket
{
public:
	EditListPacket(QObject *parent, EditList &editList);

	static EditList * GetAllocatedEditListFromPacketContent(QByteArray packetContent);
private:
	void fillByteArrayWithEditList(QByteArray &packetContent, EditList &editList);
	void appendEditBytesToByteArray(QByteArray &byteArray, Edit edit);

	static void setupEditWithBytes(Edit &edit, QByteArray &bytes);
};

#endif // EDITLISTPACKET_H
