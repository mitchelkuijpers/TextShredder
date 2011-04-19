#-------------------------------------------------
#
# Project created by QtCreator 2011-04-11T13:57:29
#
#-------------------------------------------------

QT       += core gui network

TARGET = textshredder_gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    servertabwindow.cpp \
	serverthread.cpp \
    clientconnectwindow.cpp \
    server.cpp \
	clientactivewindow.cpp \
    guicontroller.cpp

HEADERS  += mainwindow.h \
    servertabwindow.h \
    clientconnectwindow.h \
    server.h \
    serverthread.h \
    clientactivewindow.h \
    guicontroller.h

FORMS    += mainwindow.ui \
    servertabwindow.ui \
    clientactivewindow.ui \
    clientconnectwindow.ui
