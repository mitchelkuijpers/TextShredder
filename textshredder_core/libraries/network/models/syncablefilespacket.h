#ifndef SYNCABLEFILESPACKET_H
#define SYNCABLEFILESPACKET_H

#include "textshredderpacket.h"
#include "../../synchronization/models/syncablefile.h"

class SyncableFilesPacket : public TextShredderPacket
{
	Q_OBJECT

public:
	static void fillListWithContentsOfPacket(QList <SyncableFile> &list, QByteArray &content);
	SyncableFilesPacket(QObject *parent, QList<SyncableFile *> &files);

private:
	QByteArray contentForFiles(QList<SyncableFile *> &files);
};

#endif // SYNCABLEFILESPACKET_H
