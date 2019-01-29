#-------------------------------------------------
#
# Project created by QtCreator 2018-03-26T15:08:05
#
#-------------------------------------------------

QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Korttipeli
TEMPLATE = app


SOURCES += main.cc\
        mainwindow.cc \
    deck.cc \
    card.cc \
    opendeck.cc \
    cardslot.cc \
    gamerules.cc

HEADERS  += mainwindow.hh \
    deck.hh \
    card.hh \
    opendeck.hh \
    cardslot.hh \
    gamerules.hh

RESOURCES += \
    images.qrc
