#ifndef FILESYNC_H
#define FILESYNC_H

#include <QObject>
#include "../network/models/textshredderpacket.h"
#include "../network/textshredderconnection.h"
#include "filemanager.h"

class FileSync : public QObject
{
    Q_OBJECT
public:
	/**
	 * Constructor. Connects sendDownload signal to the write slot
	 * Connects incomingFileRequestPacketContent signal to processFileRequest slot
	 * @param Qobject parent. Needed for accessing all the QObject methods.
	 * @param TextShredderConnection A TextShredderConnection pointer.
	 */
	explicit FileSync(QObject *parent, TextShredderConnection *);

	/**
	 * Creates a textshredderpacket to be downloaded and emits sendDownload signal.
	 * It also emits fileSyncFinished to FileSync
	 */
	void createDownload();


	void processDownload(TextShredderPacket &packet);

signals:
	void sendDownload(TextShredderPacket &);
	void fileSyncFinished();

public slots:
	void processFileRequest(QByteArray &content);

private:
	TextShredderConnection * connection;

};

#endif // FILESYNC_H
