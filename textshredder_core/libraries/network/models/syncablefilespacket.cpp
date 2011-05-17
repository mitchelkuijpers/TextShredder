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

void SyncableFilesPacket::fillListWithContentsOfPacket(QList <SyncableFile> &list, QByteArray &content) {
	int count = 0;
	bool startedFileParsing = false;
	QString uniqueIdentifier;
	QString fileAlias;

	qDebug(content);
	qDebug("A");
	while (count < content.length()) {
		qDebug("B");
		if (!startedFileParsing) {
			qDebug("C");
			if(content.at(count) != '{') {
				qDebug("Port should start with acculader");
				//throw QString("Part should start with acculader");
			} else {
				qDebug("D");
				startedFileParsing = true;
			}
		} else {
			qDebug("F");
			qDebug() << count;
			if (uniqueIdentifier.size() == 0) {
				while (content.at(count) != ',') {
					uniqueIdentifier.append(content.at(count));
					count++;
				}
			} else {
				qDebug("E");
				while (content.at(count) != '}') {
					qDebug("G");
					qDebug() << count;
					uniqueIdentifier.append(content.at(count));
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
