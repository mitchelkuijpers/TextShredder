#-------------------------------------------------
#
# Project created by QtCreator 2011-04-12T12:46:58
#
#-------------------------------------------------

QT       += core testlib network

QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += editlisttests.cpp \
    textshredderheadertests.cpp \
    backupcopytests.cpp \
    ../textshredder_synchronization_lib/*.cpp \
    edittests.cpp \
    shadowcopytests.cpp \
    syncpropertiestests.cpp \
    textshredderpackettests.cpp \
    textshredderpacketparsertests.cpp \
    textshreddersockettests.cpp \
    workingcopytests.cpp \
    patchabletests.cpp \
    main.cpp

HEADERS += ../textshredder_synchronization_lib/*.h \
    autotest.h \
    backupcopytests.h \
    editlisttests.h \
    shadowcopytests.h \
    syncpropertiestests.h \
    textshredderheadertests.h \
    textshredderpacketparsertests.h \
    textshredderpackettests.h \
    textshreddersockettests.h \
    workingcopytests.h \
    patchabletests.h \
    edittests.h
DEFINES += SRCDIR=\\\"$$PWD/\\\"
