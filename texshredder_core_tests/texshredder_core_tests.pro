#-------------------------------------------------
#
# Project created by QtCreator 2011-05-18T09:47:09
#
#-------------------------------------------------

QT       += core testlib network

QT       -= gui

TARGET = texshredder_core_tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    backupcopytests.cpp \
    editlisttests.cpp \
    edittests.cpp \
    patchabletests.cpp \
    shadowcopytests.cpp \
    syncthreadsub.cpp \
    syncthreadtests.cpp \
    textshredderheadertests.cpp \
    textshredderpacketparsertests.cpp \
    textshredderpackettests.cpp \
    workingcopytests.cpp \
    ../textshredder_core/libraries/synchronization/clientrepresentation.cpp \
    ../textshredder_core/libraries/synchronization/filemanager.cpp \
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
    ../textshredder_core/libraries/network/models/filerequestpacket.cpp \
    ../textshredder_core/libraries/network/models/syncablefilespacket.cpp \
    ../textshredder_core/libraries/network/models/textshredderheader.cpp \
    ../textshredder_core/libraries/network/models/textshredderpacket.cpp \
    ../textshredder_core/libraries/logging/textshredderlogdir.cpp \
    ../textshredder_core/libraries/logging/textshredderlogging.cpp \
    ../textshredder_core/libraries/configuration/configurationmanager.cpp \
    ../textshredder_core/libraries/configuration/models/configurationoptions.cpp \
    ../textshredder_core/libraries/diff_match_patch/diff_match_patch.cpp \
    syncablefilespackettests.cpp \
    filemanagertest.cpp \
    filerequestpackettest.cpp \
    ../textshredder_core/client/client.cpp \
    ../textshredder_core/server/server.cpp \
    ../textshredder_core/libraries/network/models/filedatapacket.cpp \
    filedatapackettest.cpp \
    configurationmanagertests.cpp \
    ../textshredder_core/libraries/network/models/endsynchronizationpacket.cpp \
    ../textshredder_core/libraries/network/models/onlineuserspacket.cpp \
	../textshredder_core/libraries/network/models/setaliaspacket.cpp \
    ../textshredder_core/server/usermanager.cpp \
    ../textshredder_core/libraries/performance/performancecalculator.cpp

HEADERS += \
    autotest.h \
    backupcopytests.h \
    editlisttests.h \
    edittests.h \
    patchabletests.h \
    shadowcopytests.h \
    syncthreadsub.h \
    syncthreadtests.h \
    textshredderheadertests.h \
    textshredderpacketparsertests.h \
    textshredderpackettests.h \
    workingcopytests.h \
    ../textshredder_core/libraries/synchronization/clientrepresentation.h \
    ../textshredder_core/libraries/synchronization/filemanager.h \
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
    ../textshredder_core/libraries/network/models/filerequestpacket.h \
    ../textshredder_core/libraries/network/models/syncablefilespacket.h \
    ../textshredder_core/libraries/network/models/textshredderheader.h \
    ../textshredder_core/libraries/network/models/textshredderpacket.h \
    ../textshredder_core/libraries/logging/textshredderlogdir.h \
    ../textshredder_core/libraries/logging/textshredderlogging.h \
    ../textshredder_core/libraries/configuration/configurationmanager.h \
    ../textshredder_core/libraries/configuration/models/configurationoptions.h \
    ../textshredder_core/libraries/diff_match_patch/diff_match_patch.h \
    syncablefilespackettests.h \
    filemanagertest.h \
    filerequestpackettest.h \
    ../textshredder_core/client/client.h \
    ../textshredder_core/server/server.h \
    ../textshredder_core/libraries/network/models/filedatapacket.h \
    filedatapackettest.h \
    configurationmanagertests.h \
    ../textshredder_core/libraries/network/models/endsynchronizationpacket.h \
    ../textshredder_core/libraries/network/models/onlineuserspacket.h \
	../textshredder_core/libraries/network/models/setaliaspacket.h \
    ../textshredder_core/server/usermanager.h \
    ../textshredder_core/libraries/performance/performancecalculator.h
