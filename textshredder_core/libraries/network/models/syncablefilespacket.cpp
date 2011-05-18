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
		qDebug() << file->getFileIdentifier();
		array.append(file->getFileIdentifier());
		array.append(",");
		array.append(file->getFileAlias());
		array.append("}");
	}
	return array;
}

void SyncableFilesPacket::fillListWithContentsOfPacket(QList <SyncableFile *> &list, QByteArray &content) {
	int count = 0;
	bool startedFileParsing = false;
	QString uniqueIdentifier;
	QString fileAlias;

	while (count < content.length()) {
		if (!startedFileParsing) {
			if(content.at(count) != '{') {
				qDebug("Port should start with acculader");
				//throw QString("Part should start with acculader");
			} else {
				startedFileParsing = true;
			}
		} else {
			if (uniqueIdentifier.size() == 0) {
				while (content.at(count) != ',') {
					uniqueIdentifier.append(content.at(count));
					count++;
				}
			} else {
				while (content.at(count) != '}') {
					uniqueIdentifier.append(content.at(count));
					count++;
				}
				startedFileParsing = false;
				SyncableFile *newSyncFile = new SyncableFile(NULL, uniqueIdentifier, fileAlias);
				list.append(newSyncFile);
			}
		}
		count++;
	}
}
