#-------------------------------------------------
#
# Project created by QtCreator 2011-05-09T11:58:16
#
#-------------------------------------------------

QT       += core gui network

TARGET = textshredder_ui
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp \
    editorview.cpp \
    editorribbon.cpp \
    debugview.cpp \
	notificationmanager.cpp \
    notificationoption.cpp \
    notification.cpp \
    ../textshredder_core/server/server.cpp \
    ../textshredder_core/libraries/synchronization/clientrepresentation.cpp \
    ../textshredder_core/libraries/synchronization/filemanager.cpp \
    ../textshredder_core/libraries/synchronization/filesync.cpp \
    ../textshredder_core/libraries/synchronization/syncthread.cpp \
    ../textshredder_core/libraries/synchronization/models/backupcopy.cpp \
    ../textshredder_core/libraries/synchronization/models/edit.cpp \
    ../textshredder_core/libraries/synchronization/models/editlist.cpp \
    ../textshredder_core/libraries/synchronization/models/patchable.cpp \
    ../textshredder_core/libraries/synchronization/models/shadowcopy.cpp \
    ../textshredder_core/libraries/synchronization/models/syncablefile.cpp \
    ../textshredder_core/libraries/synchronization/models/workingcopy.cpp \
    ../textshredder_core/libraries/network/textshredderconnection.cpp \
    ../textshredder_core/libraries/network/textshredderpacketparser.cpp \
    ../textshredder_core/libraries/network/models/textshredderheader.cpp \
    ../textshredder_core/libraries/network/models/textshredderpacket.cpp \
    ../textshredder_core/libraries/logging/textshredderlogdir.cpp \
    ../textshredder_core/libraries/logging/textshredderlogging.cpp \
    ../textshredder_core/libraries/diff_match_patch/diff_match_patch.cpp

HEADERS  += mainwindow.h \
    editorview.h \
    editorribbon.h \
    debugview.h \
	notificationmanager.h \
    notificationoption.h \
    notification.h \
    ../textshredder_core/server/server.h \
    ../textshredder_core/libraries/synchronization/clientrepresentation.h \
    ../textshredder_core/libraries/synchronization/filemanager.h \
    ../textshredder_core/libraries/synchronization/filesync.h \
    ../textshredder_core/libraries/synchronization/syncthread.h \
    ../textshredder_core/libraries/synchronization/models/backupcopy.h \
    ../textshredder_core/libraries/synchronization/models/edit.h \
    ../textshredder_core/libraries/synchronization/models/editlist.h \
    ../textshredder_core/libraries/synchronization/models/patchable.h \
    ../textshredder_core/libraries/synchronization/models/shadowcopy.h \
    ../textshredder_core/libraries/synchronization/models/syncablefile.h \
    ../textshredder_core/libraries/synchronization/models/workingcopy.h \
    ../textshredder_core/libraries/network/textshredderconnection.h \
    ../textshredder_core/libraries/network/textshredderpacketparser.h \
    ../textshredder_core/libraries/network/models/textshredderheader.h \
    ../textshredder_core/libraries/network/models/textshredderpacket.h \
    ../textshredder_core/libraries/logging/textshredderlogdir.h \
    ../textshredder_core/libraries/logging/textshredderlogging.h \
    ../textshredder_core/libraries/diff_match_patch/diff_match_patch.h

FORMS    += mainwindow.ui \
    editorview.ui \
    editorribbon.ui \
    debugview.ui

RESOURCES += images.qrc \
    fonts.qrc
