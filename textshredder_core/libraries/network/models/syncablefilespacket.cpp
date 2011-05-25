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
		appendFileDataToArray(array, file.data());
	}
	return array;
}

void SyncableFilesPacket::appendFileDataToArray(QByteArray &byteArray, SyncableFile *file) {
	byteArray.append("{");
	byteArray.append(file->getFileIdentifier());
	byteArray.append(",");
	byteArray.append(file->getFileAlias());
	byteArray.append("}");
}

void SyncableFilesPacket::fillListWithContentsOfPacket(QList <QSharedPointer<SyncableFile> > &list, QByteArray &content) {
	QByteArray contentCopy(content);
	QByteArray parsedPiece;

	while (contentCopy.length() > 0) {
		QString uniqueIdentifier;
		QString fileAlias;
		parsedPiece = splitContentTillCharacter(contentCopy, '{');
		if (parsedPiece.length() > 0 ) {
			qDebug("SyncableFilesPacket::fillListWithContentsOfPacket Should not happen");
		}
		parsedPiece = splitContentTillCharacter(contentCopy, ',');
		uniqueIdentifier.append(parsedPiece);

		parsedPiece = splitContentTillCharacter(contentCopy, '}');
		fileAlias.append(parsedPiece);


		QSharedPointer<SyncableFile> obj =
				QSharedPointer<SyncableFile>(new SyncableFile(NULL, uniqueIdentifier, fileAlias));
		list.append(obj);
		obj.clear();
	}
}

QByteArray SyncableFilesPacket::splitContentTillCharacter(QByteArray &original, char c)
{
	QByteArray returnValue;
	int count = 0;
	while ( count < original.size()) {
		if (original.at(count) == c) {
			returnValue.append(original.mid(0, count));
			original.remove(0,count+1);
			return returnValue;
		}
		count++;
	}
	returnValue.append(original);
	original.clear();
	return returnValue;
}
