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
	servercontrolview.cpp \
	serverthread.cpp \
	clientcontrolview.cpp \
    server.cpp \
	clienteditingwindow.cpp \
	guicontroller.cpp \
	../textshredder_diff_match_patch/diff_match_patch.cpp \
	../textshredder_synchronization_lib/*.cpp \
    syncablefile.cpp \
    filemanager.cpp \
    filesync.cpp

HEADERS  += mainwindow.h \
	servercontrolview.h \
	clientcontrolview.h \
    server.h \
    serverthread.h \
	clienteditingwindow.h \
	guicontroller.h \
	../textshredder_diff_match_patch/diff_match_patch.h \
	../textshredder_synchronization_lib/*.h \
    syncablefile.h \
    filemanager.h \
    filesync.h

FORMS    += mainwindow.ui \
	servercontrolview.ui \
	clienteditingwindow.ui \
	clientcontrolview.ui
