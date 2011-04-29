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
    ../textshredder_diff_match_patch/diff_match_patch.cpp \
    ../textshredder_synchronization_lib/*.cpp \
    edittests.cpp \
    shadowcopytests.cpp \
    textshredderpackettests.cpp \
    textshredderpacketparsertests.cpp \
    workingcopytests.cpp \
    patchabletests.cpp \
    main.cpp

HEADERS += ../textshredder_synchronization_lib/*.h \
    autotest.h \
    backupcopytests.h \
    ../textshredder_diff_match_patch/diff_match_patch.h\
    editlisttests.h \
    shadowcopytests.h \
    textshredderheadertests.h \
    textshredderpacketparsertests.h \
    textshredderpackettests.h \
    workingcopytests.h \
    patchabletests.h \
    edittests.h
DEFINES += SRCDIR=\\\"$$PWD/\\\"
