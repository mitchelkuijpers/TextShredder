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
    clientconnectwindow.cpp \
    server.cpp \
    serverthread.cpp \
    clientactivewindow.cpp

HEADERS  += mainwindow.h \
    servertabwindow.h \
    clientconnectwindow.h \
    server.h \
    serverthread.h \
    clientactivewindow.h

FORMS    += mainwindow.ui \
    servertabwindow.ui \
    clienttabwindow.ui \
    clientactivewindow.ui
