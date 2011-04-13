#-------------------------------------------------
#
# Project created by QtCreator 2011-04-12T12:46:58
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = textshredderheadertests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += textshredderheadertests.cpp \
        ../textshredder_synchronization_lib/*.cpp
HEADERS += ../textshredder_synchronization_lib/*.h
DEFINES += SRCDIR=\\\"$$PWD/\\\"
