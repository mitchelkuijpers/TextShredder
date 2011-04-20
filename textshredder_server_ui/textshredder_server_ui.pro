#-------------------------------------------------
#
# Project created by QtCreator 2011-04-20T14:26:46
#
#-------------------------------------------------

QT       += core gui network

TARGET = textshredder_server_ui
TEMPLATE = app

SOURCES += main.cpp \
	serverui.cpp \
	../textshredder_diff_match_patch/diff_match_patch.cpp \
	../textshredder_gui/server.h

HEADERS += serverui.h \
	../textshredder_diff_match_patch/diff_match_patch.h \
	../textshredder_gui/server.h

FORMS += serverui.ui
