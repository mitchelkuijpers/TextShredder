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
		throw QString(protocolVersion); //wrong protocolVersion
	}

	QByteArray length = bytes->mid(kPacketLengthOffset,
								  (int) sizeof(unsigned int));
	QByteArray type = bytes->mid(kPacketTypeOffset,
								(int) sizeof(unsigned char));
	unsigned int iLength = *((unsigned int *)length.data());

	QByteArray content(bytes->mid(kHeaderLength, iLength));
	TextShredderHeader header(
				NULL,
				(unsigned char) * protocolVersion.data(),
				(unsigned int) iLength,
				(unsigned char) * type.data());
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
		qDebug("we have incomplete packet");
		QByteArray restData;
		unsigned int appendableBytes = incompletePacket->numberOfBytesNeeded();
		if(appendableBytes > (unsigned int) incomingData.length()) {
			incompletePacket->appendContentData(incomingData);
			qDebug("packet still not complete");
		} else {
			qDebug("packet is complete");
			QByteArray temp(incomingData.mid(0, appendableBytes));
			incompletePacket->appendContentData(temp);
			queuedPackets.append(incompletePacket);
			incompletePacket = NULL;
			restData = incomingData.mid(appendableBytes,
										incomingData.length() - appendableBytes);
			this->handleData(restData);
		}
	} else {
		qDebug("we do not have incomplete packet");
		if(incomingData.length() < kHeaderLength) {
			incompleteData.append(incomingData);
			return;
		}
		TextShredderPacket * packet = this->makeAllocatedPacketFromBytes(&incomingData);
		if(packet->isIncomplete()) {
			qDebug("new packet is incomplete");
			incompletePacket = packet;
			return;
		}
		queuedPackets.append(packet);
		qDebug("new packet is complete");
		unsigned int newPacketLength = packet->length();
		if(newPacketLength < (unsigned int) incomingData.length()) {
			qDebug("make more packets");
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
