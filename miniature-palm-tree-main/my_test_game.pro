#-------------------------------------------------
#
# Project created by QtCreator 2022-05-29T20:55:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_test_game
TEMPLATE = app


SOURCES += main.cpp\
        mainmenu.cpp \
    optionbutton.cpp \
    gamescene.cpp \
    zombie.cpp \
    plant.cpp \
    missile.cpp

HEADERS  += mainmenu.h \
    optionbutton.h \
    gamescene.h \
    zombie.h \
    plant.h \
    missile.h

FORMS    += mainmenu.ui

RESOURCES += \
    res.qrc



