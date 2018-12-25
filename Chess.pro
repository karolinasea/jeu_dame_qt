#-------------------------------------------------
#
# Project created by QtCreator 2018-11-5T17:19:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    damier.cpp \
    boite.cpp \
    bouton.cpp \
    pion.cpp

HEADERS  += \
    game.hpp \
    enumCouleur.hpp \
    damier.hpp \
    boite.hpp \
    bouton.hpp \
    pion.hpp

FORMS    +=

RESOURCES += \
    resource.qrc
