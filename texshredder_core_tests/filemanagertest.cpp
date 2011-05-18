#include "filemanagertest.h"
#include "../textshredder_core/libraries/synchronization/models/syncablefile.h"
#include "../textshredder_core/libraries/network/models/syncablefilespacket.h"

#include <QSharedPointer>
#include <QTest>

void FileManagerTest::testHandleReceivedSyncableFiles() {
	FileManager *manager = FileManager::Instance();
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

	manager->handleReceivedSyncableFiles(packet.getContent());

	QVERIFY2(manager->getAllFiles().count() == list.count(), "they should have the same size");

	packet.deleteLater();

	list.removeAt(1);
	SyncableFilesPacket secondPacket(this, list);
	manager->handleReceivedSyncableFiles(secondPacket.getContent());

	QVERIFY2(manager->getAllFiles().count() == list.count(), "removing of syncablefiles fails");
}
