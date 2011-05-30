#include "editlist.h"

EditList::EditList(QObject *parent, int remoteVersion) :
	QObject(parent), remoteVersion(remoteVersion)
{
}

EditList::EditList(const EditList &otherEditList)
	: QObject(NULL), QMutex()
{
	this->remoteVersion = otherEditList.remoteVersion;
	this->edits = otherEditList.edits;
}

unsigned int EditList::getRemoteVersion()
{
	return remoteVersion;
}

EditList & EditList::operator=( EditList & otherEditList )
{
	this->remoteVersion = otherEditList.remoteVersion;
	this->edits = otherEditList.edits;
	return *this;
}

bool EditList::operator==( EditList & otherList )
{
	return (this->remoteVersion == otherList.remoteVersion && this->edits == otherList.edits);
}

void EditList::addEdit( const Edit & e )
{
	this->edits.push_back(e);
}


void EditList::setRemoteVersion( unsigned int newRemoteVersion )
{
	remoteVersion = newRemoteVersion;
}

QList<Edit> & EditList::getEdits()
{
	return edits;
}

bool EditList::isEmpty()
{
	return (this->edits.count() == 0);
}

void EditList::empty() {
	edits.empty();
}

QList<Edit> EditList::popEditsUpToLocalVersion( unsigned int version ) {
	QList<Edit> returnEdits;
	int count = 0;
	while(count < edits.count()) {
		Edit e = edits.at(count);
		if (e.getLocalVersion() < version) {
			returnEdits.append(e);
			edits.removeAt(count);
		} else {
			count++;
		}
	}
	return returnEdits;
}
