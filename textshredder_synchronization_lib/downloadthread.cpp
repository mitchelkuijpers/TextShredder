#include "downloadthread.h"

DownloadThread::DownloadThread(	QObject *parent,
								SyncProperties &properties,
								bool isServer)
	: QThread(parent), syncPropertiesPointer(&properties), isServer(isServer)
{
	qDebug("DownloadThread::DownloadThread();");
}

void DownloadThread::waitForFileRequest()
{
	qDebug("DownloadThread::waitForFileRequest();");
	//Wait for file request
	QByteArray byteArray;
	TextShredderSocket *socket = syncPropertiesPointer->getSocket();
	socket->waitForReadyRead();
	TextShredderPacket *packet;
	try{
		packet = socket->readPacket();
	} catch (QString error) {
		emit sendTimeOut();
		return;
	}

	if(! packet->isFileRequestPacket()) {
		emit wrongPacketInDownloadThread (packet);
		delete packet;
		return;
	}

	//Get Working copy content
	syncPropertiesPointer->getWorkingCopy()->lock();
	byteArray.append (*(syncPropertiesPointer->getWorkingCopy()->getContent()));
	syncPropertiesPointer->getWorkingCopy()->unlock();

	//Write and error check sending working copy data
	TextShredderPacket fileDataPacket(this,
									  kPacketTypeFileData,
									  byteArray);
	socket->writePacket(&fileDataPacket);
	bool result = socket->waitForBytesWritten(15000);
	if (!result) {
		emit sendTimeOut();
	} else {
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
	socket->waitForReadyRead (15000);
	if (! fileDataPacket->isFileDataPacket()) {
		qDebug("DownloadThread::makeFileRequest(); read file data failed");
		emit receiveTimeOut();
		return;
	}

	qDebug("DownloadThread::makeFileRequest(); did read file data");
	QString *workingCopyContent = syncPropertiesPointer->getWorkingCopy()->getContent();
	*workingCopyContent = QString(fileDataPacket->getContent());
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
