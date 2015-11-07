#-------------------------------------------------
#
# Project created by QtCreator 2015-11-05T03:21:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UniScheduler
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Task.cpp \
    TaskListModel.cpp \
    AddTaskDialog.cpp

HEADERS  += MainWindow.hpp \
    Task.hpp \
    TaskListModel.hpp \
    AddTaskDialog.hpp

FORMS    += MainWindow.ui \
    AddTaskDialog.ui

CONFIG += c++11

RESOURCES += \
    Resources.qrc
