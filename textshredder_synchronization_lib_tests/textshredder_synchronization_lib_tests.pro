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
    workingcopytests.cpp

HEADERS += ../textshredder_synchronization_lib/*.h
DEFINES += SRCDIR=\\\"$$PWD/\\\"
