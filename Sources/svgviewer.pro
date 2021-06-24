HEADERS       = \
                filereader.h \
                imageloader.h \
                program.h \
                server.h \
                threadfilereaders.h \
                threadimageloaders.h \
                tilesanalyzer.h
SOURCES       = \
                filereader.cpp \
                imageloader.cpp \
                main.cpp \
                program.cpp \
                server.cpp \
                threadfilereaders.cpp \
                threadimageloaders.cpp \
                tilesanalyzer.cpp
QT += concurrent
QT += network
QT += svg
CONFIG += warn_off
CONFIG -= console
CONFIG(release, debug|release):DEFINES += QT_NO_INFO_OUTPUT
