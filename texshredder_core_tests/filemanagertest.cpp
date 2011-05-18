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
	QString file4Alias("file4.txt");
	QString file1UUID(QUuid::createUuid().toString());
	QString file2UUID(QUuid::createUuid().toString());
	QString file3UUID(QUuid::createUuid().toString());
	QString file4UUID(QUuid::createUuid().toString());
	QSharedPointer<SyncableFile> file1 = QSharedPointer<SyncableFile>(
				new SyncableFile(NULL, file1UUID, file1Alias ));
	QSharedPointer<SyncableFile> file2 = QSharedPointer<SyncableFile>(
				new SyncableFile(NULL, file2UUID, file2Alias));
	QSharedPointer<SyncableFile> file3 = QSharedPointer<SyncableFile>(
				new SyncableFile(NULL, file3UUID, file3Alias));
	QSharedPointer<SyncableFile> file4 = QSharedPointer<SyncableFile>(
				new SyncableFile(NULL, file4UUID, file4Alias));
	list.append(file1);
	list.append(file2);
	list.append(file3);

	SyncableFilesPacket packet(this, list);

	manager->handleReceivedSyncableFiles(packet.getContent());

	QVERIFY2(manager->getAllFiles().count() == list.count(), "they should have the same size");

	packet.deleteLater();

	list.removeAt(1);
	list.removeAt(2);
	list.append(file4);

	SyncableFilesPacket secondPacket(this, list);
	manager->handleReceivedSyncableFiles(secondPacket.getContent());

	QVERIFY2(manager->getAllFiles().count() == list.count(), "removing of syncablefiles fails");
}

void FileManagerTest::testHandleReceivedSyncableFilesWithChangedAlias() {
	FileManager *manager = FileManager::Instance();
	QList<QSharedPointer<SyncableFile> > list;

	QString file1Alias("file1.txt");
	QString file1UUID(QUuid::createUuid().toString());
	QSharedPointer<SyncableFile> file1 = QSharedPointer<SyncableFile>(
				new SyncableFile(NULL, file1UUID, file1Alias ));
	list.append(file1);
	SyncableFilesPacket packet(this, list);

	manager->handleReceivedSyncableFiles(packet.getContent());

	QVERIFY2(manager->getAllFiles().at(0).data()->getFileAlias() == QString("file1.txt"),
			 "first name is already wrong?");
	QString newFileAlias("changedTheName.txt");
	list.at(0).data()->setFileAlias(newFileAlias);

	manager->handleReceivedSyncableFiles(packet.getContent());

	QVERIFY2(manager->getAllFiles().at(0).data()->getFileAlias() == QString("changedTheName.txt"),
			 "Name change does not get synced");
}
