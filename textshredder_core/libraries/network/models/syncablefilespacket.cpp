#include "syncablefilespacket.h"

SyncableFilesPacket::SyncableFilesPacket(QObject *parent, QList<SyncableFile *> &files) :
	TextShredderPacket(parent, kPacketTypeAvailableFiles)
{
	QByteArray newContent = contentForFiles(files);
	this->setContent(newContent);
}

QByteArray SyncableFilesPacket::contentForFiles(QList<SyncableFile *> &files) {
	QByteArray array;

	for (int i = 0; i < files.count(); i++) {
		SyncableFile *file = files.at(i);
		array.append("{");
		array.append(file->getFileIdentifier());
		array.append(",");
		array.append(file->getFileAlias());
		array.append("}");
	}
	return array;
}

void SyncableFilesPacket::fillListWithContentsOfPacket(QList <SyncableFile> &list, TextShredderPacket &packet) {
	int count = 0;
	bool startedFileParsing = false;
	QString uniqueIdentifier;
	QString fileAlias;

	QByteArray con = packet.getContent();
	while (count < con.length()) {
		if (!startedFileParsing) {
			if(con.at(count) != '{') {
				throw QString("Part should start with acculader");
			} else {
				startedFileParsing = true;
			}
		} else {

			if (uniqueIdentifier.size() == 0) {
				while (con.at(count) != ',') {
					uniqueIdentifier.append(con.at(count));
					count++;
				}
			} else {
				while (con.at(count) != '}') {
					uniqueIdentifier.append(con.at(count));
					count++;
				}
				startedFileParsing = false;
				SyncableFile newSyncFile(NULL, uniqueIdentifier, fileAlias);
				list.append(newSyncFile);
			}
		}
		count++;
	}
}
