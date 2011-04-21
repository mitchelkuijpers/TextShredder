#include "downloadthread.h"

DownloadThread::DownloadThread(	QObject *parent,
								SyncProperties &properties,
								bool isServer)
	: QThread(0), syncPropertiesPointer(&properties), isServer(isServer)
{
	qDebug("DownloadThread::DownloadThread();");
}

void DownloadThread::waitForFileRequest()
{
	qDebug("DownloadThread::waitForFileRequest();");
	//Wait for file request
	QByteArray byteArray;
	TextShredderSocket *socket = syncPropertiesPointer->getSocket();
	TextShredderPacket *packet;
	qDebug("-- try receiving packet");
	try{
		packet = socket->readPacket();
	} catch (QString error) {
		emit sendTimeOut();
		return;
	}

	qDebug("-- received packet");
	if(! packet->isFileRequestPacket()) {
		qDebug("-- received packet is not file request packet");
		emit wrongPacketInDownloadThread (packet);
		delete packet;
		return;
	}
	delete packet;
	qDebug("-- did receive file request packet");

	//Get Working copy content
	syncPropertiesPointer->getWorkingCopy()->lock();
	byteArray.append (*(syncPropertiesPointer->getWorkingCopy()->getContent()));
	syncPropertiesPointer->getWorkingCopy()->unlock();

	qDebug("-- try to write file data");
	//Write and error check sending working copy data
	TextShredderPacket fileDataPacket(this,
									  kPacketTypeFileData,
									  byteArray);
	socket->writePacket(&fileDataPacket);
	bool result = socket->waitForBytesWritten(15000);
	qDebug("-- did write data");
	if (!result) {
		qDebug("-- failed to write data. did time out");
		emit sendTimeOut();
	} else {
		qDebug("-- file transfer complet-o");
		emit fileDownloadCompleted();
	}
}

void DownloadThread::makeFileRequest()
{
	qDebug("DownloadThread::makeFileRequest();");
	QByteArray emptyByteArray;
	TextShredderPacket fileRequestPacket(NULL, kPacketTypeFileRequest,emptyByteArray);
	TextShredderSocket *socket = syncPropertiesPointer->getSocket();
	socket->writePacket (&fileRequestPacket);

	qDebug("DownloadThread::makeFileRequest(); did write packet");
	bool result = socket->waitForBytesWritten (15000);
	if (!result) {
		qDebug("DownloadThread::makeFileRequest(); write file request failed");
		emit fileRequestFailed();
		return;
	}

	qDebug("DownloadThread::makeFileRequest(); write file request passed read file data");
	TextShredderPacket *fileDataPacket = socket->readPacket();
	if (! fileDataPacket->isFileDataPacket()) {
		qDebug("DownloadThread::makeFileRequest(); read file data failed");
		emit receiveTimeOut();
		return;
	}

	qDebug("DownloadThread::makeFileRequest(); did read file data");
	QString *workingCopyContent = syncPropertiesPointer->getWorkingCopy()->getContent();
	*workingCopyContent = QString(fileDataPacket->getContent());

	delete fileDataPacket;

	qDebug() << &workingCopyContent;
	qDebug() << *syncPropertiesPointer->getWorkingCopy()->getContent();
}

void DownloadThread::run()
{
	qDebug("DownloadThread::run();");
	if (isServer) {
		waitForFileRequest();
	} else {
		makeFileRequest();
	}
}
