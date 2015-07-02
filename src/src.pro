# -------------------------------------------------
# Project created by QtCreator 2009-03-26T22:25:24
# -------------------------------------------------
QT += core gui network network webkit xml xmlpatterns widgets

TARGET = FacElectronica
DESTDIR = ../bin
TEMPLATE = app

MOC_DIR = ../obj
OBJECTS_DIR = ../obj

SOURCES += main.cpp \
    sslclient.cpp
HEADERS += \
    sslclient.h
FORMS += sslclient.ui


RESOURCES += securesocketclient.qrc
