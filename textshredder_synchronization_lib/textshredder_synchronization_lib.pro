#-------------------------------------------------
#
# Project created by QtCreator 2011-04-12T10:27:47
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = textshredder_synchronization_lib
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    editlist.cpp \
    edit.cpp \
    syncproperties.cpp \
    ../textshredder_diff_match_patch/*.cpp \
    textshredderheader.cpp \
    shadowcopy.cpp \
    backupcopy.cpp \
    textshredderpacket.cpp \
    textshredderpacketparser.cpp \
    textshreddersocket.cpp \
    workingcopy.cpp \
    patchable.cpp \
    syncthread.cpp \
    downloadthread.cpp

HEADERS += \
    textshredderheader.h \
    editlist.h \
    edit.h \
    syncproperties.h \
    ../textshredder_diff_match_patch/*.h\
    textshredderheader.h \
    shadowcopy.h \
    backupcopy.h \
    textshredderpacket.h \
    textshredderpacketparser.h \
    textshreddersocket.h \
    workingcopy.h \
    ../textshredder_diff_match_patch/patchable.h \
    patchable.h \
    syncthread.h \
    downloadthread.h
