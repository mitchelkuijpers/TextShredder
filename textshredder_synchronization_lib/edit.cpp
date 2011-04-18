#include "edit.h"

Edit::Edit(QObject *parent) :
    QObject(parent), localVersion(0), patches(NULL)
{
}

Edit::Edit(const Edit &copy) : QObject(copy.parent())
{
	this->localVersion = copy.localVersion;
	this->patches = copy.patches;
}

Edit::Edit(QObject *parent, unsigned int localVersion, QList<Patch> *patches) :
        QObject(parent), localVersion(localVersion), patches(patches)
{
}

Edit& Edit::operator = (const Edit& other)
{
	this->localVersion = other.localVersion;
	this->patches = other.patches;
	return *this;
}

bool Edit::operator == (const Edit& other)
{
	if (this->localVersion == other.localVersion && this->patches == other.patches) {
		return true;
	}
	return false;
}


QString * Edit::allocateStringDictionaryRepresentation()
{
	QString *stringRepresentation = new QString();
	stringRepresentation->append("d");
	stringRepresentation->append(QString("12:localVersion"));
	stringRepresentation->append("i" + QString::number(localVersion) + "e");
	stringRepresentation->append(QString("7:patches"));
	stringRepresentation->append("l");

	for(int i=0; i < patches->count(); i++) {
		Patch p = patches->at(i);
		QString patchString = p.toString();
		stringRepresentation->append(QString::number(patchString.length()));
		stringRepresentation->append(":");
		stringRepresentation->append (patchString);
	}

	stringRepresentation->append("e");
	stringRepresentation->append("e");
	return stringRepresentation;
}


unsigned int Edit::getLocalVersion()
{
    return localVersion;
}

QList<Patch> * Edit::getPatches()
{
    return patches;
}


void Edit::setLocalVersion(unsigned int newLocalVersion)
{
    localVersion = newLocalVersion;
}

void Edit::setPatches(QList<Patch> *newPatches)
{
    this->patches = newPatches;
}
