#-------------------------------------------------
#
# Project created by QtCreator 2019-02-14T10:36:36
#
#-------------------------------------------------

QT       += core gui opengl network qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = practiceOpenGL
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
    TcpHandler/incomingdatahandler.cpp \
    #TrackingManager/DataModel/ktamarkmodel.cpp \
    #TrackingManager/DataModel/trackmarkmodel.cpp \
    #TrackingManager/datamodel.cpp \
    #TrackingManager/trackingcontroller.cpp \
    bMath.cpp \
    basewidget.cpp \
    camera.cpp \
    controlpanelwidget.cpp \
    customdata.cpp \
    #datahandler.cpp \
    #detectionsectorwidget.cpp \
    ftcustom.cpp \
    ktainfowindow.cpp \
    #llfreadercontrolwidget.cpp \
    main.cpp \
    #mainwidgetcontroller.cpp \
    #openglwindow.cpp \
    scene.cpp \
    scenecustomazingwindow.cpp \
    sectorsviewerwidget.cpp \
    uicontroller.cpp \
    widget.cpp \
    #openglwidget.cpp \
    customplotter.cpp \
    circlepalette.cpp \
    tracewidget.cpp \
    dspwidget.cpp \
    signalnoiseratiowidget.cpp \
    mapdebugger.cpp

HEADERS += \
    TcpHandler/datamessage.h \
    TcpHandler/incomingdatahandler.h \
    #TrackingManager/DataModel/ktamarkmodel.h \
    #TrackingManager/DataModel/trackmarkmodel.h \
    #TrackingManager/datamodel.h \
    #TrackingManager/trackingcontroller.h \
    bMath.h \
    basewidget.h \
    camera.h \
    camera_p.h \
    controlpanelwidget.h \
    customdata.h \
    #datahandler.h \
    #detectionsectorwidget.h \
    ftcustom.h \
    global.h \
    ktainfowindow.h \
    #llfreadercontrolwidget.h \
    #mainwidgetcontroller.h \
    #openglwindow.h \
    scene.h \
    scenecustomazingwindow.h \
    sectorsviewerwidget.h \
    uicontroller.h \
        widget.h \
    #openglwidget.h \
    customplotter.h \
    circlepalette.h \
    tracewidget.h \
    dspwidget.h \
    signalnoiseratiowidget.h \
    mapdebugger.h

unix {
    LIBS += -L/usr/lib/x86_64-linux-gnu/ -lfreetype -lfftw3
    LIBS += -L/usr/lib/ -lqwt-qt5 -lqwtmathml-qt5  #-lqwtplot3d-qt5
    INCLUDEPATH += /usr/include/qwt headers
    #INCLUDEPATH += /usr/include/qwtplot3d headers
    INCLUDEPATH += /usr/include/freetype2 headers
}

win32 {
    LIBS += -Lc:/Qwt-6.1.2/lib/ -lqwt
    INCLUDEPATH += c:/Qwt-6.1.2/src/ headers
    INCLUDEPATH += $$PWD/freetype2/include
    LIBS += -L$$PWD/freetype2/win32/ -lfreetype
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    icon.qrc \
    qmlSystemControl.qrc \
    res.qrc \
    qmloscilloscope.qrc
