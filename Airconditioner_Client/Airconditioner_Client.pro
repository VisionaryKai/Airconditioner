#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T14:01:28
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Airconditioner_Client
TEMPLATE = app


SOURCES += main.cpp\
        slave_interface.cpp \
    thread_communicate.cpp \
    login_room.cpp \
    air_conditioner.cpp \
    center_ac.cpp

HEADERS  += slave_interface.h \
    client_head.h \
    thread_communicate.h \
    login_room.h

FORMS    += slave_interface.ui \
    login_room.ui

RESOURCES += \
    client_ui.qrc

DISTFILES +=


