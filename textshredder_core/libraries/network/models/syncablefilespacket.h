#ifndef SYNCABLEFILESPACKET_H
#define SYNCABLEFILESPACKET_H

#include "textshredderpacket.h"
#include "../../synchronization/models/syncablefile.h"

#include <QSharedPointer>

class SyncableFilesPacket : public TextShredderPacket
{
	Q_OBJECT

public:
	static void fillListWithContentsOfPacket(QList <QSharedPointer<SyncableFile> > &list, QByteArray &content);
	SyncableFilesPacket(QObject *parent, QList< QSharedPointer<SyncableFile> > &files);

	void appendFileDataToArray(QByteArray &byteArray, SyncableFile *file);
private:
	QByteArray contentForFiles(QList< QSharedPointer<SyncableFile> > &files);
};

#endif // SYNCABLEFILESPACKET_H
