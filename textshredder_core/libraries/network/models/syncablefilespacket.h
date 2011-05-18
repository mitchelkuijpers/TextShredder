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
	SyncableFilesPacket(QObject *parent, QList<SyncableFile *> &files);

private:
	static void doDeleteLater(SyncableFile *obj);
	QByteArray contentForFiles(QList<SyncableFile *> &files);
};

#endif // SYNCABLEFILESPACKET_H
