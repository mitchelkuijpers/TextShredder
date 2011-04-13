#-------------------------------------------------
#
# Project created by QtCreator 2011-04-12T10:27:47
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = textshredder_synchronization_lib
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    editlist.cpp \
    edit.cpp \
    syncproperties.cpp \
    ../textshredder_diff_match_patch/*.cpp

HEADERS += \
    textshredderheader.h \
    editlist.h \
    edit.h \
    syncproperties.h \
    ../textshredder_diff_match_patch/*.h
