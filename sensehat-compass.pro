#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T11:20:13
#
#-------------------------------------------------

QT       += core sensors gui
CONFIG += c++11


TARGET = sensehat-compass
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    qsensehatfb.cpp \
    sensehatcompass.cpp
HEADERS += \
    qsensehatfb.h \
    sensehatcompass.h
