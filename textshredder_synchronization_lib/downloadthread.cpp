#include "downloadthread.h"

DownloadThread::DownloadThread(	QObject *parent,
								SyncProperties *properties,
								bool isServer)
	: QThread(parent), syncProperties(properties), isServer(isServer)
{
}

void DownloadThread::waitForFileRequest()
{
	//Wait for file request
	QByteArray byteArray;
	TextShredderSocket *socket = syncProperties->getSocket();
	TextShredderPacket *packet = socket->readPacket();
	if(! packet->isFileRequestPacket()) {
		emit wrongPacketInDownloadThread (packet);
		delete packet;
		return;
	}

	//Get Working copy content
	syncProperties->getWorkingCopy()->lock();
	byteArray.append (*(syncProperties->getWorkingCopy()->getContent()));
	syncProperties->getWorkingCopy()->unlock();

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
	QByteArray emptyByteArray;
	TextShredderPacket fileRequestPacket(this, kPacketTypeFileRequest,emptyByteArray);
	TextShredderSocket *socket = syncProperties->getSocket();
	socket->writePacket (&fileRequestPacket);

	TextShredderPacket *fileDataPacket = socket->readPacket();
	if (fileDataPacket->isFileDataPacket()) {
		//Signal
		return;
	}
}

void DownloadThread::run()
{
	if (isServer) {
		waitForFileRequest();
	} else {
		makeFileRequest();
	}
}
