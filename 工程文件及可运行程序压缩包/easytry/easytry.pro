#-------------------------------------------------
#
# Project created by QtCreator 2019-12-16T23:12:36
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

RC_ICONS = logo.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = easytry
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    add_file.cpp \
    event_edit.cpp \
    role_edit.cpp \
    mylabel.cpp \
    item_edit.cpp \
    add_music.cpp \
    scene_edit.cpp \
    material_edit.cpp

HEADERS += \
        mainwindow.h \
    add_file.h \
    event_edit.h \
    role_edit.h \
    mylabel.h \
    item_edit.h \
    add_music.h \
    scene_edit.h \
    material_edit.h

FORMS += \
        mainwindow.ui \
    add_file.ui \
    event_edit.ui \
    role_edit.ui \
    item_edit.ui \
    add_music.ui \
    scene_edit.ui \
    material_edit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc
