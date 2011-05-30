#ifndef EDITLISTPACKET_H
#define EDITLISTPACKET_H

#include "textshredderpacket.h"
#include "../../synchronization/models/editlist.h"

class EditListPacket : public TextShredderPacket
{
public:
	/**
	  * Constructor to make a packet with its content representing an EditList.
	  *
	  * @param parent The parent object.
	  * @param editList The EditList which will be used to make the content.
	  */
	EditListPacket(QObject *parent, EditList &editList);

	/**
	  * Static method to create an EditList object from packet content.
	  *
	  * @param packetContent The bytes representing the EditList.
	  *
	  * @return The new EditList instance.
	  */
	static EditList * GetAllocatedEditListFromPacketContent(QByteArray packetContent);

private:
	/**
	  * Method will fill an byteArray with an EditList instance.
	  *
	  * @param packetContent The array in which the byte representation should be stored in.
	  * @param editList The EditList which has to be serialized.
	  */
	void fillByteArrayWithEditList(QByteArray &packetContent, EditList &editList);

	/**
	  * Method will fill an byteArray with an Edit instance.
	  *
	  * @param packetContent The array in which the byte representation should be stored in.
	  * @param editList The Edit which has to be serialized.
	  */
	void appendEditBytesToByteArray(QByteArray &byteArray, Edit edit);

	/**
	  * Method will setup a Edit with bytes.
	  *
	  * @param edit The Edit that has to be initialized.
	  * @param bytes The bytes used for the Edit initialization.
	  */
	static void setupEditWithBytes(Edit &edit, QByteArray &bytes);
};

#endif // EDITLISTPACKET_H
