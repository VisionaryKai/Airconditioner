#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T09:49:11
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Airconditioner_Server
TEMPLATE = app


SOURCES += main.cpp\
    mythread.cpp \
    mainwindows.cpp \
    mainchoice.cpp \
    check_out.cpp \
    ac_mainwindow.cpp \
    init_config.cpp \
    showcentralac.cpp \
    showac.cpp \
    work_thread.cpp \
    central_ac.cpp \
    air_conditioner.cpp \
    show_all_ac.cpp \
    sql_server_manager.cpp \
    show_summary_table.cpp \
    summary_table.cpp \
    login_in.cpp

HEADERS  += \
    mythread.h \
    total.h \
    communicate.h \
    mainwindows.h \
    mainchoice.h \
    check_out.h \
    ac_mainwindow.h \
    init_config.h \
    showcentralac.h \
    showac.h \
    show_all_ac.h \
    show_summary_table.h \
    login_in.h

FORMS    += \
    mainwindows.ui \
    mainchoice.ui \
    check_out.ui \
    ac_mainwindow.ui \
    init_config.ui \
    showcentralac.ui \
    showac.ui \
    show_all_ac.ui \
    show_summary_table.ui \
    login_in.ui

RESOURCES += \
    image.qrc

DISTFILES +=
