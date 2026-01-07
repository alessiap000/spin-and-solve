# Spin & Solve Qt Project File

QT       += core gui widgets

CONFIG   += c++17 console
CONFIG   -= app_bundle

TEMPLATE = app

# Source files
SOURCES += \
    src/main.cpp \
    src/game.cpp \
    src/Difficulty.cpp \
    src/GameController.cpp \
    src/Help.cpp \
    src/Instructions.cpp \
    src/LetterGuesser.cpp \
    src/MainController.cpp \
    src/PhraseHandler.cpp \
    src/PhraseLibrary.cpp \
    src/Wheel.cpp \
    src/mainwindow.cpp \
    src/timer.cpp

# Header files
HEADERS += \
    src/game.h \
    src/Difficulty.h \
    src/GameController.h \
    src/Help.h \
    src/Instructions.h \
    src/Instructionss.h \
    src/LetterGuesser.h \
    src/MainController.h \
    src/PhraseHandler.h \
    src/PhraseLibrary.h \
    src/Wheel.h \
    src/mainwindow.h \
    src/timer.h \
    src/PlayerGems.h

# UI files
FORMS += \
    src/mainwindow.ui

# Resource files
RESOURCES += \
    src/resources.qrc \
    src/images.qrc
