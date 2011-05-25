#include "editlist.h"

EditList::EditList(QObject *parent, int remoteVersion) :
	QObject(parent), remoteVersion(remoteVersion)
{
}

EditList::EditList(const EditList &otherEditList)
	: QObject(NULL), QMutex()
{
	this->remoteVersion = otherEditList.remoteVersion;
	this->edits = otherEditList.edits;
}

EditList::EditList(QObject *parent, QByteArray &content)
	: QObject(parent)
{
	int offSet = 0;

	if (content[offSet++] != '{') {
		qDebug() << "EditList::EditList = " << "Edit packet is not starting with a accolade, cannot make EditList";
	}

	remoteVersion = atoi(&(content.data()[offSet]));
	offSet += (QString::number (remoteVersion).length () + 1);

	if (content[offSet++] != '{') {
		qDebug() << "EditList::EditList = " << "Edits part in EditList packet is not starting with a accolade, cannot make EditList";
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
				qDebug() << "EditList::EditList = " << "Edits part in EditList packet is not starting with a accolade, cannot make EditList";
			}

			Edit newEdit(this, editBytes);
			edits.push_back(newEdit);
		} else {
			return;
		}
	}
}

EditList::EditList(QObject *parent, TextShredderPacket &packet)
	: QObject(parent)
{
	int offSet = 0;
	QByteArray content = packet.getContent();

	if (content[offSet++] != '{') {
		qDebug() << "EditList::EditList = " << "Edit packet is not starting with a accolade, cannot make EditList";
	}

	remoteVersion = atoi(&(content.data()[offSet]));
	offSet += (QString::number (remoteVersion).length () + 1);

	if (content[offSet++] != '{') {
		qDebug() << "EditList::EditList = " << "Edits part in EditList packet is not starting with a accolade, cannot make EditList";
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
				qDebug() << "EditList::EditList = " << "Edits part in EditList packet is not starting with a accolade, cannot make EditList";
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

EditList & EditList::operator=(EditList & otherEditList) {
	this->remoteVersion = otherEditList.remoteVersion;
	this->edits = otherEditList.edits;
	return *this;
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

void EditList::empty() {
	edits.empty();
}

QList<Edit> EditList::popEditsUpToLocalVersion(unsigned int version) {
	QList<Edit> returnEdits;
	int count = 0;
	while(count < edits.count()) {
		Edit e = edits.at(count);
		if (e.getLocalVersion() < version) {
			returnEdits.append(e);
			edits.removeAt(count);
		} else {
			count++;
		}
	}
	return returnEdits;
}
