#-------------------------------------------------
#
# Project created by QtCreator 2019-02-14T10:36:36
#
#-------------------------------------------------

QT       += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RLS_TI_Locator
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

CONFIG += c++11 plugin

SOURCES += \
    Math/bMath.cpp \
    Scene/camera.cpp \
    Scene/scene.cpp \
    TcpHandler/incomingdatahandler.cpp \
    Widgets/ControlPanels/controlpanelwidget.cpp \
    Widgets/Map/mapdebugger.cpp \
    Widgets/basewidget.cpp \
    main.cpp \
    uicontroller.cpp \
    widget.cpp



HEADERS += \
    CommonEntities/global.h \
    Math/bMath.h \
    Scene/camera.h \
    Scene/camera_p.h \
    Scene/scene.h \
    TcpHandler/incomingdatahandler.h \
    Widgets/ControlPanels/controlpanelwidget.h \
    Widgets/Map/mapdebugger.h \
    Widgets/basewidget.h \
    uicontroller.h \
    widget.h


DISTFILES +=


RESOURCES += \
    resources.qrc
