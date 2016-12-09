#-------------------------------------------------
#
# Project created by QtCreator 2016-12-04T15:24:22
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TakeAway
TEMPLATE = app


SOURCES += main.cpp\
    menuwindow.cpp \
    registerwindow.cpp \
    mainwindow.cpp \
    reguserdb.cpp \
    sellerdb.cpp \
    userds.cpp \
    bardelegate.cpp \
    menudb.cpp \
    orderwindow.cpp \
    orderdb.cpp \
    buyerwindow.cpp \
    sellerwindow.cpp \
    smenudb.cpp \
    sellerorderwindow.cpp \
    sorderdb.cpp \
    abstractdb.cpp

HEADERS  += \
    menuwindow.h \
    registerwindow.h \
    mainwindow.h \
    userds.h \
    sellerdb.h \
    reguserdb.h \
    bardelegate.h \
    menudb.h \
    orderwindow.h \
    orderdb.h \
    orderds.h \
    buyerwindow.h \
    sellerwindow.h \
    smenudb.h \
    sellerorderwindow.h \
    sorderdb.h \
    abstractdb.h \
    prerequisite.h

FORMS += \
    menuwindow.ui \
    registerwindow.ui \
    mainwindow.ui \
    orderwindow.ui \
    buyerwindow.ui \
    sellerwindow.ui \
    sellerorderwindow.ui
