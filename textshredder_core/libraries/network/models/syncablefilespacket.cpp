#include "syncablefilespacket.h"

SyncableFilesPacket::SyncableFilesPacket(QObject *parent, QList< QSharedPointer<SyncableFile> > &files) :
	TextShredderPacket(parent, kPacketTypeAvailableFiles)
{
	QByteArray newContent = contentForFiles(files);
	this->setContent(newContent);
}

QByteArray SyncableFilesPacket::contentForFiles(QList< QSharedPointer<SyncableFile> > &files) {
	QByteArray array;

	for (int i = 0; i < files.count(); i++) {
		QSharedPointer<SyncableFile> file  = files.at(i);
		//SyncableFile *file = files.at(i);
		array.append("{");
		qDebug() << file.data()->getFileIdentifier();
		array.append(file.data()->getFileIdentifier());
		array.append(",");
		array.append(file.data()->getFileAlias());
		array.append("}");
	}
	return array;
}

void SyncableFilesPacket::fillListWithContentsOfPacket(QList <QSharedPointer<SyncableFile> > &list, QByteArray &content) {
	int count = 0;
	bool startedFileParsing = false;
	QString uniqueIdentifier;
	QString fileAlias;

	qDebug() << content.length();
	qDebug(content);
	qDebug("A");

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
					fileAlias.append(content.at(count));
					count++;
				}
				startedFileParsing = false;

				QSharedPointer<SyncableFile> obj =
						QSharedPointer<SyncableFile>(new SyncableFile(NULL, uniqueIdentifier, fileAlias),
													 SyncableFile::doDeleteLater);
				list.append(obj);
				obj.clear();
				count++;
			}
		}
		count++;
	}
}
