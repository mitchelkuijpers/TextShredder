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
    debugview.cpp

HEADERS  += mainwindow.h \
    editorview.h \
    editorribbon.h \
    debugview.h

FORMS    += mainwindow.ui \
    editorview.ui \
    editorribbon.ui \
    debugview.ui

RESOURCES += images.qrc \
    fonts.qrc
