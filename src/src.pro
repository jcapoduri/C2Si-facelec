# -------------------------------------------------
# Project created by QtCreator 2009-03-26T22:25:24
# -------------------------------------------------
QT += core gui network network xml widgets

CONFIG += c++11

TARGET = FacElectronica
DESTDIR = ../bin
TEMPLATE = app

MOC_DIR = ../obj
OBJECTS_DIR = ../obj

SOURCES += main.cpp \
    client.cpp \
    wsaalogin.cpp \
    wsfemanager.cpp
HEADERS += \
    client.h \
    wsaalogin.h \
    wsfemanager.h
FORMS += sslclient.ui \
    wsfeform.ui


RESOURCES += securesocketclient.qrc
