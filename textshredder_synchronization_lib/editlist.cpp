#include "editlist.h"

EditList::EditList(QObject *parent, int remoteVersion) :
	QObject(parent), remoteVersion(remoteVersion)
{
}

EditList::EditList(QObject *parent, TextShredderPacket &packet)
	: QObject(parent)
{
	int offSet = 0;
	QByteArray content = packet.getContent();

	if (content[offSet++] != '{') {
		throw QString("Edit packet is not starting with a accolade, cannot make EditList");
	}

	remoteVersion = atoi(&(content.data()[offSet]));
	offSet += (QString::number (remoteVersion).length () + 1);

	if (content[offSet++] != '{') {
		throw QString("Edits part in EditList packet is not starting with a accolade, cannot make EditList");
	}

	int tempEditLength = 0;
	while (1) {
		if (content[offSet++] == '{') {
			//Will start next edit
			tempEditLength = atoi(&(content.data()[offSet]));
			offSet += (QString::number (tempEditLength).length () + 1);

			QByteArray editBytes = content.mid (offSet, tempEditLength);
			offSet += tempEditLength;

			if (content.at(offSet++) != '}') {
				throw QString("Edits part in EditList packet is not starting with a accolade, cannot make EditList");
			}

			Edit newEdit(this, editBytes);
			edits.push_back(newEdit);
		} else {
			return;
		}
	}
}

unsigned int EditList::getRemoteVersion()
{
	return remoteVersion;
}

void EditList::updateToRemoteAndLocalVersion(	unsigned int newRemoteVersion,
												unsigned int newLocalVersion)
{
	this->remoteVersion = newRemoteVersion;
	for(int i = edits.count()-1; i >= 0; i--) {
		Edit e = this->edits.at(i);
		if ( e.getLocalVersion() < newLocalVersion) {
			edits.removeAt(i);
		}
	}
}

bool EditList::operator==(EditList & otherList)
{
	return (this->remoteVersion == otherList.remoteVersion && this->edits == otherList.edits);
}

void EditList::addEdit(const Edit &e)
{
	this->edits.push_back(e);
}


void EditList::setRemoteVersion(unsigned int newRemoteVersion)
{
	remoteVersion = newRemoteVersion;
}

QList<Edit> & EditList::getEdits()
{
	return edits;
}

TextShredderPacket * EditList::getAllocatedPacket()
{
	QByteArray packetContent;
	packetContent.append('{');
	packetContent.append (QString::number(remoteVersion));
	packetContent.append (',');
	packetContent.append('{');

	for(int i = 0; i < edits.count(); i++ ) {
		packetContent.append('{');
		Edit currentEdit = edits.at(i);

		QByteArray editByteRepresentation;
		currentEdit.appendEditBytesToByteArray(editByteRepresentation);
		packetContent.append (QString::number(editByteRepresentation.length()));
		packetContent.append(',');
		packetContent.append(editByteRepresentation);
		packetContent.append('}');
	}
	packetContent.append('}');
	packetContent.append('}');
	return new TextShredderPacket(NULL, kPacketTypeEdits ,packetContent);;
}

bool EditList::isEmpty()
{
	return (this->edits.count() == 0);
}


