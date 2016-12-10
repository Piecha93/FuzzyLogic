#-------------------------------------------------
#
# Project created by QtCreator 2016-12-04T20:14:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FuzzyLogic
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lfuzzylite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lfuzzylited

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

RESOURCES += \
    Resources.qrc
