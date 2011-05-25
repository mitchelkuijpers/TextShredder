#ifndef SYNCABLEFILESPACKET_H
#define SYNCABLEFILESPACKET_H

#include "textshredderpacket.h"
#include "../../synchronization/models/syncablefile.h"

#include <QSharedPointer>

class SyncableFilesPacket : public TextShredderPacket
{
	Q_OBJECT

public:
	/**
	 * Constructor which creates a new qbytearray and sets the content in that array.
	 * @param *parent To have access to the Q methods
	 * @param &files A QSharedPointer which points to a list of files
	 */
	SyncableFilesPacket(QObject *parent, QList< QSharedPointer<SyncableFile> > &files);

	/**
	 * Fills the list with contents of the given packets.
	 * @param &list A QSharedPointer which holds the content
	 * @param &content The content
	 */
	static void fillListWithContentsOfPacket(QList <QSharedPointer<SyncableFile> > &list, QByteArray &content);

	/**
	 * Append the file data to the bytearray
	 * @param &byteArray The bytearray to hold the the filedata
	 * @param *file The syncablefile which holds the filedata
	 */
	void appendFileDataToArray(QByteArray &byteArray, SyncableFile *file);
	/**
	 * Searches the &original bytearray and splits it until it comes across the given char c.
	 * @param &original The QByteArray whichs holds the original content.
	 * @param c The character to find which ends the split
	 * @return The QByteArray which holds the online users.
	 */
	static QByteArray splitContentTillCharacter(QByteArray &original, char c);
private:
	QByteArray contentForFiles(QList< QSharedPointer<SyncableFile> > &files);
};

#endif // SYNCABLEFILESPACKET_H
