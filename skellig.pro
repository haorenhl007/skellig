#-------------------------------------------------
#
# Project created by QtCreator 2016-09-20T19:15:10
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = skellig
TEMPLATE    = app

SOURCES     +=  main.cpp \
                mainwindow.cpp \
                glwidget.cpp \
                camera.cpp \
                model.cpp \
                mesh.cpp \
                animationdialog.cpp

HEADERS     +=  mainwindow.h \
                glwidget.h \
                camera.h \
                model.h \
                mesh.h \
                animationdialog.h

FORMS       +=  mainwindow.ui \
                animationdialog.ui

DISTFILES   +=  shader.vert \
                shader.frag

win32:INCLUDEPATH   += c:/libraries/include
unix:INCLUDEPATH    += /usr/include/assimp

win32:LIBS          += c:/libraries/lib/assimp.lib
unix:LIBS           += -lassimp
