#ifndef SYNCTHREAD_H
#define SYNCTHREAD_H

#include <QObject>
#include <QTimer>
#include <QSharedPointer>

#include "models/editlist.h"
#include "models/shadowcopy.h"
#include "models/workingcopy.h"

#include "../network/textshredderconnection.h"
#include "../network/models/filedatapacket.h"
#include "../network/models/endsynchronizationpacket.h"

#include "../logging/textshredderlogging.h"
#include "../performance/performancecalculator.h"


#define WRITETHREAD_INTERVAL 1000

class SyncThread : public QObject
{
	Q_OBJECT

public:
	/**
	  * Constuctor which will setup a SyncThread with an connection and working copy.
	  *
	  * @param parent the parent of the object.
	  * @param conn the connection on which the communication happens.
	  * @param workingCopyPointer the working copy used for the synchronization.
	  */
	SyncThread(QObject * parent, QSharedPointer<TextShredderConnection>conn,
						   QSharedPointer< WorkingCopy> workingCopyPointer);

	/**
	  * Constuctor which will setup a SyncThread with an working copy.
	  * This constructor is mainly used for testing.
	  *
	  * @param the parent of the object.
	  * @param the working copy used for the synchronization.
	  */
	SyncThread(QObject * parent, QSharedPointer <WorkingCopy> newWorkingCopy);

	/**
	  * Method will process changes from content of an packet.
	  * This packet should represent bytes of the edit.
	  *
	  * @param the bytes on which an edit list is made.
	  */
	void processChanges(QByteArray &content);

	/**
	  * Method that will apply an received edit list.
	  * It will process the edits on the shadow and working copy.
	  *
	  * @param incomingEditList received editlist.
	  */
	void applyReceivedEditList(EditList &incomingEditList);
	void receivedDownloadedContent(QByteArray & content);
	void sendFileDataAndStart();
	void stopSync();
	virtual void startSync();

	void setDestinationHandle(quint16 destination);
	quint16 getDestinationHandle();
	quint16 getSourceHandle();

public slots:
	void pushChanges();
	void receivedEditPacketContent(QByteArray &content, quint16 destination);
	void receivedFileDataPacket(TextShredderPacket &packet, quint16 destination);
	void receivedEndSynchronizationPacket(quint16);


signals:
	void syncThreadStoppedByOtherNode();
	#ifdef QT_DEBUG
		void addToAverageLockTime(uint);
	#endif
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
	TextShredderLogging performanceLog;


private:
	void breakDownSynchronization();
	void connectSignalsForSynchronization();
	void disconnectSignalsForSynchronization();

	quint16 sourceSyncThreadHandle;
	quint16 destinationSyncThreadHandle;

	static quint16 nextSyncThreadHandle;

	QTime performanceTime;
	void beforeLock();
	void afterLock();
};

#endif // SYNCTHREAD_H
