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
	SyncThread(QObject * parent, QSharedPointer<TextShredderConnection>conn,
						   QSharedPointer< WorkingCopy> workingCopyPointer);
	//SyncThread(QObject *, int port, QString &address, WorkingCopy &);
	SyncThread(QObject * parent, QSharedPointer <WorkingCopy> newWorkingCopy);

	qint16 getLocalPort();

	void setDestinationHandle(quint16 destination);
	quint16 getDestinationHandle();
	quint16 getSourceHandle();

	void processChanges(QByteArray &content);
	void applyReceivedEditList(EditList &incomingEditList);
	void receivedDownloadedContent(QByteArray & content);
	void sendFileDataAndStart();
	void stop();
	virtual void startSync();

public slots:
	void pushChanges();
	void receivedEditPacketContent(QByteArray &content, quint16 destination);
	void receivedFileDataPacketContent(QByteArray &content, quint16 destination);

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

	QSharedPointer<TextShredderConnection> connectionPointer;
	QSharedPointer <WorkingCopy> workingCopyPointer;
	ShadowCopy shadowCopy;
	EditList editList;
	QTimer timer;
	int syncThreadNumber;
	static int sharedIndex;

	TextShredderLogging logging;

private:
	void connectSignalsForConnection();

	quint16 sourceSyncThreadHandle;
	quint16 destinationSyncThreadHandle;

	static quint16 nextSyncThreadHandle;
};

#endif // SYNCTHREAD_H
