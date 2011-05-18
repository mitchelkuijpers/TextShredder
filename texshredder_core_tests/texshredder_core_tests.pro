#-------------------------------------------------
#
# Project created by QtCreator 2011-05-18T09:47:09
#
#-------------------------------------------------

QT       += core

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
    syncpropertiestests.cpp \
    syncthreadsub.cpp \
    syncthreadtests.cpp \
    textshredderheadertests.cpp \
    textshredderpacketparsertests.cpp \
    textshredderpackettests.cpp \
    textshreddersockettests.cpp \
    workingcopytests.cpp

HEADERS += \
    autotest.h \
    backupcopytests.h \
    editlisttests.h \
    edittests.h \
    patchabletests.h \
    shadowcopytests.h \
    syncpropertiestests.h \
    syncthreadsub.h \
    syncthreadtests.h \
    textshredderheadertests.h \
    textshredderpacketparsertests.h \
    textshredderpackettests.h \
    textshreddersockettests.h \
    workingcopytests.h
