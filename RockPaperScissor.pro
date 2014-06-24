#-------------------------------------------------
#
# Project created by QtCreator 2014-06-20T18:39:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RockPaperScissor
TEMPLATE = app

LIBS += `pkg-config opencv --libs`

SOURCES += main.cpp\
        dialog.cpp \
    mythread.cpp \
    game.cpp \
    gamethread.cpp \
    artificialintelligence.cpp \
    deffensivestrategy.cpp \
    pattern_strategy.cpp \
    rock_paper_scissors_si.cpp

HEADERS  += dialog.h \
    mythread.h \
    game.h \
    gamethread.h \
    artificialintelligence.h \
    rock_paper_scissors_si.h

FORMS    += dialog.ui \
    game.ui

OTHER_FILES += \
    fist.xml \
    hand1.xml \
    palm.xml \
    image.png \
    Images/1.png \
    Images/2.png \
    Images/3.png
