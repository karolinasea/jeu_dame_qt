#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T17:19:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    chesspiece.cpp \
    pawn.cpp \
    damier.cpp \
    boite.cpp \
    bouton.cpp

HEADERS  += \
    chesspiece.hpp \
    game.hpp \
    pawn.hpp \
    enumCouleur.hpp \
    damier.hpp \
    boite.hpp \
    bouton.hpp

FORMS    +=

RESOURCES += \
    resource.qrc
