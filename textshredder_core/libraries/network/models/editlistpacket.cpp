#include "editlistpacket.h"

#include "../../synchronization/models/edit.h"

EditListPacket::EditListPacket(QObject *parent, EditList &editList)
	: TextShredderPacket(parent, kPacketTypeEdits)
{
	QByteArray newContent;
	fillByteArrayWithEditList(newContent, editList);
	this->setContent(newContent);
}

void EditListPacket::fillByteArrayWithEditList(QByteArray &packetContent, EditList &editList)
{
	packetContent.append('{');
	packetContent.append (QString::number(editList.getRemoteVersion()));
	packetContent.append (',');
	packetContent.append('{');
	QList<Edit> edits = editList.getEdits();
	for(int i = 0; i < edits.count(); i++ ) {
		packetContent.append('{');
		Edit currentEdit = edits.at(i);

		QByteArray editByteRepresentation;
		appendEditBytesToByteArray(editByteRepresentation, currentEdit);
		packetContent.append (QString::number(editByteRepresentation.length()));
		packetContent.append(',');
		packetContent.append(editByteRepresentation);
		packetContent.append('}');
	}
	packetContent.append('}');
	packetContent.append('}');
}

void EditListPacket::appendEditBytesToByteArray(QByteArray &bytesArray, Edit edit)
{
	bytesArray.append(QString::number(edit.getLocalVersion()));
	bytesArray.append(',');
	bytesArray.append('{');

	for(int i=0; i < edit.getPatches().count(); i++) {
		Patch p = edit.getPatches().at(i);
		QString patchString = p.toString();
		bytesArray.append ('{');
		bytesArray.append(QString::number(patchString.length()));
		bytesArray.append(",");
		bytesArray.append (patchString);
		bytesArray.append ('}');
	}
	bytesArray.append("}");
}

EditList * EditListPacket::GetAllocatedEditListFromPacketContent(QByteArray packetContent)
{
	EditList *newEditList = new EditList(NULL);
	int offSet = 0;
	if (packetContent[offSet++] != '{') {
		qDebug() << "EditList::EditList = " << "Edit packet is not starting with a accolade, cannot make EditList";
	}

	newEditList->setRemoteVersion(atoi(&(packetContent.data()[offSet])));
	//remoteVersion = ;
	offSet += (QString::number(newEditList->getRemoteVersion()).length () + 1);

	if (packetContent[offSet++] != '{') {
		qDebug() << "EditList::EditList = " << "Edits part in EditList packet is not starting with a accolade, cannot make EditList";
	}

	int tempEditLength = 0;
	while (1) {
		if (packetContent[offSet++] == '{') {
			//Will start next edit
			tempEditLength = atoi(&(packetContent.data()[offSet]));
			offSet += (QString::number (tempEditLength).length () + 1);

			QByteArray editBytes = packetContent.mid (offSet, tempEditLength);
			offSet += tempEditLength;

			if (packetContent.at(offSet++) != '}') {
				qDebug() << "EditList::EditList = " << "Edits part in EditList packet is not starting with a accolade, cannot make EditList";
			}

			Edit newEdit(NULL);
			setupEditWithBytes(newEdit, editBytes);
			newEditList->getEdits().push_back(newEdit);
		} else {
			return newEditList;
		}
	}
	return NULL;
}

void EditListPacket::setupEditWithBytes(Edit &edit, QByteArray &byteArray)
{
	int offSet = 0;
	edit.setLocalVersion(atoi(&(byteArray.data()[offSet])));
	offSet += (QString::number (edit.getLocalVersion()).length () + 1);

	if(byteArray.at(offSet++) != '{') {
		qDebug() << "Edit::Edit" << "Could not parse Patches from Edit byte array";
	}

	diff_match_patch dmp;
	int tempPatchLength;
	while(1) {

		if (byteArray[offSet++] == '{') {
			//Will start next edit
			tempPatchLength = atoi(&(byteArray.data()[offSet]));
			offSet += (QString::number (tempPatchLength).length () + 1);

			QByteArray editBytes = byteArray.mid (offSet, tempPatchLength);
			offSet += tempPatchLength;

			if (byteArray.at(offSet++) != '}') {
				qDebug() << "Edit::Edit" << "Edits part in EditList packet is not starting with a accolade, cannot make EditList";
			}

			QList<Patch> newPatchList = dmp.patch_fromText(QString(editBytes));
			edit.getPatches().append (newPatchList);
		} else {
			return;
		}
	}
}
