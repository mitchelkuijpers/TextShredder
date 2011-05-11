#ifndef SYNCTHREAD_H
#define SYNCTHREAD_H

#include <QObject>
#include <QTimer>
#include "textshredderconnection.h"
#include "editlist.h"
#include "shadowcopy.h"
#include "workingcopy.h"

#include "../textshredder_gui/textshredderlogging.h"

#define WRITETHREAD_INTERVAL 1000

class SyncThread : public QObject
{
	Q_OBJECT

public:
	SyncThread(QObject *, TextShredderConnection &, WorkingCopy &);

signals:

public slots:
	void processChanges(QByteArray &content);
	void stop();
	void pushChanges();

protected://Must be protected for test purposes
	void applyReceivedEditList(EditList &incomingEditList);

	/**
	  * Will change the current editlist into a packet
	  * and call the writePacketOnConnection with that packet
	  */
	void writePacketOfEditList();

	/**
	  * Will write a packet on the connction
	  */
	void writePacketOnConnection(TextShredderPacket &packet);

	TextShredderConnection * connection;
	WorkingCopy * workingCopy;
	ShadowCopy shadowCopy;
	EditList editList;
	QTimer timer;
	int syncThreadNumber;
	static int sharedIndex;

        TextShredderLogging logging;
};

#endif // SYNCTHREAD_H
