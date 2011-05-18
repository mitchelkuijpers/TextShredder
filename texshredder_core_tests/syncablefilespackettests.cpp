#include "syncablefilespackettests.h"
#include "../textshredder_core/libraries/synchronization/models/syncablefile.h"
#include <QList>
#include <QSharedPointer>
#include <QUuid>
#include <QTest>

void SyncableFilesPacketTests::testFillListWithContentsOfPacket()
{
	QList<QSharedPointer<SyncableFile> > list;
	QString file1Alias("file1.txt");
	QString file2Alias("file2.txt");
	QString file3Alias("file3.txt");
	QString file1UUID(QUuid::createUuid().toString());
	QString file2UUID(QUuid::createUuid().toString());
	QString file3UUID(QUuid::createUuid().toString());
	QSharedPointer<SyncableFile> file1 = QSharedPointer<SyncableFile>(
				new SyncableFile(NULL, file1UUID, file1Alias ));
	QSharedPointer<SyncableFile> file2 = QSharedPointer<SyncableFile>(
				new SyncableFile(NULL, file2UUID, file2Alias));
	QSharedPointer<SyncableFile> file3 = QSharedPointer<SyncableFile>(
				new SyncableFile(NULL, file3UUID, file3Alias));
	list.append(file1);
	list.append(file2);
	list.append(file3);
	SyncableFilesPacket packet(this, list);

	QList<QSharedPointer<SyncableFile> > newList;
	SyncableFilesPacket::fillListWithContentsOfPacket(newList, packet.getContent());

	QVERIFY2(list.count() == newList.count(), "List don't have the same list");

	if(list.count() == newList.count()){
		QVERIFY2(list.at(0).data()->getFileAlias() == newList.at(0).data()->getFileAlias(), "list(0) is not the same as newList(0)");
		QVERIFY2(list.at(1).data()->getFileAlias() == newList.at(1).data()->getFileAlias(), "list(1) is not the same as newList(1)");
		QVERIFY2(list.at(2).data()->getFileAlias() == newList.at(2).data()->getFileAlias(), "list(2) is not the same as newList(2)");

		QVERIFY2(list.at(0).data()->getFileIdentifier() == newList.at(0).data()->getFileIdentifier(), "list(0) is not the same as newList(0)");
		QVERIFY2(list.at(1).data()->getFileIdentifier() == newList.at(1).data()->getFileIdentifier(), "list(1) is not the same as newList(1)");
		QVERIFY2(list.at(2).data()->getFileIdentifier() == newList.at(2).data()->getFileIdentifier(), "list(2) is not the same as newList(2)");
	}

	}
