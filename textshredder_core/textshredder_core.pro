#-------------------------------------------------
#
# Project created by QtCreator 2011-04-12T10:27:47
#
#-------------------------------------------------

QT			+= core network

QT			-= gui

TARGET		= textshredder_core
CONFIG		+= console
CONFIG		-= app_bundle

TEMPLATE	= app


SOURCES		+= \
	libraries/synchronization/models/edit.cpp \
    libraries/synchronization/editlist.cpp \
    libraries/synchronization/syncthread.cpp \
    libraries/synchronization/models/backupcopy.cpp \
    libraries/synchronization/models/patchable.cpp \
    libraries/synchronization/models/shadowcopy.cpp \
    libraries/synchronization/models/workingcopy.cpp \
    libraries/network/textshredderconnection.cpp \
    libraries/network/textshredderpacketparser.cpp \
    libraries/network/models/textshredderheader.cpp \
    libraries/network/models/textshredderpacket.cpp \
    libraries/diff_match_patch/diff_match_patch.cpp \
    server/server.cpp \
    libraries/synchronization/models/syncablefile.cpp \
    libraries/synchronization/filemanager.cpp \
    libraries/synchronization/filesync.cpp \
    libraries/synchronization/clientrepresentation.cpp


HEADERS		+= \
	libraries/synchronization/models/edit.h \
    libraries/synchronization/editlist.h \
    libraries/synchronization/syncthread.h \
    libraries/synchronization/models/backupcopy.h \
    libraries/synchronization/models/patchable.h \
    libraries/synchronization/models/shadowcopy.h \
    libraries/synchronization/models/workingcopy.h \
    libraries/network/textshredderconnection.h \
    libraries/network/textshredderpacketparser.h \
    libraries/network/models/textshredderheader.h \
    libraries/network/models/textshredderpacket.h \
    libraries/diff_match_patch/diff_match_patch.h \
    server/server.h \
    libraries/synchronization/models/syncablefile.h \
    libraries/synchronization/filemanager.h \
    libraries/synchronization/filesync.h \
    libraries/synchronization/clientrepresentation.h
