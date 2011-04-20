#-------------------------------------------------
#
# Project created by QtCreator 2011-04-20T14:02:15
#
#-------------------------------------------------

QT       += core gui network

TARGET = textshredder_server_console
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
	../textshredder_diff_match_patch/diff_match_patch.cpp \
	../textshredder_synchronization_lib/*.cpp \
	../textshredder_gui/*.cpp

HEADERS +=../textshredder_diff_match_patch/diff_match_patch.h \
	../textshredder_synchronization_lib/*.h \
	../textshredder_gui/*.h

FORMS +=../textshredder_gui/*.ui
