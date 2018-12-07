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
    chessbox.cpp \
    chessboard.cpp \
    chesspiece.cpp \
    pawn.cpp \
    button.cpp

HEADERS  += \
    button.hpp \
    chessboard.hpp \
    chessbox.hpp \
    chesspiece.hpp \
    game.hpp \
    pawn.hpp \
    enumCouleur.hpp

FORMS    +=

RESOURCES += \
    resource.qrc
