#ifndef FILESYNC_H
#define FILESYNC_H

#include <QObject>
#include "../textshredder_synchronization_lib/textshredderpacket.h"
#include "../textshredder_synchronization_lib/textshredderconnection.h"
#include "filemanager.h"

class FileSync : public QObject
{
    Q_OBJECT
public:
	explicit FileSync(QObject *parent, TextShredderConnection *);
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
