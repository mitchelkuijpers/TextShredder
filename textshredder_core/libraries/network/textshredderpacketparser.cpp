#include "textshredderpacketparser.h"

TextShredderPacketParser::TextShredderPacketParser():
	incompletePacket(NULL)
{

}

TextShredderPacket * TextShredderPacketParser::makeAllocatedPacketFromBytes(
	QByteArray * bytes)
{
	QByteArray protocolVersion = bytes->mid(kProtocolVersionOffset,
											(int) sizeof(unsigned char));
	if(protocolVersion.data()[0] != kProtocolVersion) {
		qDebug("Wrong protocol version");
	}

	QByteArray length = bytes->mid(kPacketLengthOffset,
								  (int) sizeof(unsigned int));
	QByteArray type = bytes->mid(kPacketTypeOffset,
								(int) sizeof(unsigned char));
	unsigned int iLength = *((unsigned int *)length.data());
	QByteArray connectionHandleBytes = bytes->mid(kPacketHandleOffset,
												  (int) sizeof(unsigned int));
	unsigned int connectionHandle;
	memcpy(&connectionHandle, connectionHandleBytes.data(), sizeof(unsigned int));

	QByteArray content(bytes->mid(kHeaderLength, iLength));
	TextShredderHeader header(
				NULL,
				(unsigned char) * protocolVersion.data(),
				(unsigned int) iLength,
				(unsigned char) * type.data(),
				connectionHandle);
	return new TextShredderPacket(
				NULL, header, content);
}

void TextShredderPacketParser::handleData(QByteArray & incomingData)
{
	if(incompleteData.length() > 0) {
		incomingData.insert(0, incompleteData);
		incompleteData.clear();
	}
	if(incompletePacket != NULL) {
		QByteArray restData;
		unsigned int appendableBytes = incompletePacket->numberOfBytesNeeded();
		if(appendableBytes > (unsigned int) incomingData.length()) {
			incompletePacket->appendContentData(incomingData);
		} else {
			QByteArray temp(incomingData.mid(0, appendableBytes));
			incompletePacket->appendContentData(temp);
			queuedPackets.append(incompletePacket);
			incompletePacket = NULL;
			restData = incomingData.mid(appendableBytes,
										incomingData.length() - appendableBytes);
			this->handleData(restData);
		}
	} else {
		if(incomingData.length() < kHeaderLength) {
			incompleteData.append(incomingData);
			return;
		}
		TextShredderPacket * packet = this->makeAllocatedPacketFromBytes(&incomingData);
		if(packet->isIncomplete()) {
			incompletePacket = packet;
			return;
		}
		queuedPackets.append(packet);
		unsigned int newPacketLength = packet->length();
		if(newPacketLength < (unsigned int) incomingData.length()) {
			QByteArray temp(incomingData.mid(newPacketLength,
											 incompleteData.length() - newPacketLength));
			this->handleData(temp);
		}
	}
}

bool TextShredderPacketParser::hasMorePackets()
{
	return (queuedPackets.count() > 0);
}

TextShredderPacket * TextShredderPacketParser::nextPacket()
{
	TextShredderPacket * packet = queuedPackets.first();
	queuedPackets.removeFirst();
	return packet;
}
