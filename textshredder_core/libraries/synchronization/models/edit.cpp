#include "edit.h"

Edit::Edit(QObject *parent) :
	QObject(parent), localVersion(0)
{
}

Edit::Edit(const Edit &copy) : QObject(copy.parent())
{
	this->localVersion = copy.localVersion;
	this->patches = copy.patches;
}

Edit::Edit(QObject *parent, unsigned int localVersion, QList<Patch> &patches) :
        QObject(parent), localVersion(localVersion), patches(patches)
{
}

Edit::Edit(QObject *parent, QByteArray &byteArray)
	: QObject(parent), localVersion(0)
{
	int offSet = 0;
	localVersion = atoi(&(byteArray.data()[offSet]));
	offSet += (QString::number (localVersion).length () + 1);

	if(byteArray.at(offSet++) != '{') {
		qDebug() << "Edit::Edit" << "Could not parse Patches from Edit byte array";
	}

	diff_match_patch dmp;
	int tempPatchLength;
	while(1) {

		if (byteArray[offSet++] == '{') {
			//Will start next edit
			tempPatchLength = atoi(&(byteArray.data()[offSet]));
			offSet += (QString::number (tempPatchLength).length () + 1);

			QByteArray editBytes = byteArray.mid (offSet, tempPatchLength);
			offSet += tempPatchLength;

			if (byteArray.at(offSet++) != '}') {
				qDebug() << "Edit::Edit" << "Edits part in EditList packet is not starting with a accolade, cannot make EditList";
			}

			QList<Patch> newPatchList = dmp.patch_fromText(QString(editBytes));
			patches.append (newPatchList);
		} else {
			return;
		}
	}
}

Edit& Edit::operator = (const Edit& other)
{
	this->localVersion = other.localVersion;
	this->patches = other.patches;
	return *this;
}

bool Edit::operator == (const Edit& other)
{
	if (this->localVersion == other.localVersion &&
		(this->patches == other.patches)) {
		return true;
	}
	return false;
}

void Edit::appendEditBytesToByteArray(QByteArray &bytesArray)
{
	bytesArray.append(QString::number(localVersion));
	bytesArray.append(',');
	bytesArray.append('{');

	for(int i=0; i < patches.count(); i++) {
		Patch p = patches.at(i);
		QString patchString = p.toString();
		bytesArray.append ('{');
		bytesArray.append(QString::number(patchString.length()));
		bytesArray.append(",");
		bytesArray.append (patchString);
		bytesArray.append ('}');
	}
	bytesArray.append("}");
}

unsigned int Edit::getLocalVersion()
{
    return localVersion;
}

QList<Patch> & Edit::getPatches()
{
    return patches;
}


void Edit::setLocalVersion(unsigned int newLocalVersion)
{
    localVersion = newLocalVersion;
}

void Edit::setPatches(QList<Patch> &newPatches)
{
    this->patches = newPatches;
}
