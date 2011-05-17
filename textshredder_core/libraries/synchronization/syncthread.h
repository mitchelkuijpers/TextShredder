#ifndef SYNCTHREAD_H
#define SYNCTHREAD_H

#include <QObject>
#include <QTimer>
#include "../network/textshredderconnection.h"
#include "models/editlist.h"
#include "models/shadowcopy.h"
#include "models/workingcopy.h"

#include "../logging/textshredderlogging.h"

#define WRITETHREAD_INTERVAL 1000

class SyncThread : public QObject
{
	Q_OBJECT

public:
	SyncThread(QObject *, int port, QString &address, WorkingCopy &);
	SyncThread(QObject *, WorkingCopy &);

	qint16 getLocalPort();

signals:

public slots:
	void processChanges(QByteArray &content);
	void stop();
	void pushChanges();

	void applyReceivedEditList(EditList &incomingEditList);

	virtual void startSync();

protected://Must be protected for test purposes
	/**
	  * Will change the current editlist into a packet
	  * and call the writePacketOnConnection with that packet
	  */
	virtual void writePacketOfEditList();

	/**
	  * Will write a packet on the connction
	  * @param packet the TextShredderPacket
	  */
	void writePacketOnConnection(TextShredderPacket &packet);

	TextShredderConnection connection;
	WorkingCopy * workingCopy;
	ShadowCopy shadowCopy;
	EditList editList;
	QTimer timer;
	int syncThreadNumber;
	static int sharedIndex;

	TextShredderLogging logging;
};

#endif // SYNCTHREAD_H
