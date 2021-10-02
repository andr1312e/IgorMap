QT += concurrent svg network

HEADERS       = \
                filereader.h \
                server.h \
                threadfilereaders.h \
                tilesanalyzer.h \
                tilescoordinats.h
SOURCES       = \
                filereader.cpp \
                main.cpp \
                server.cpp \
                threadfilereaders.cpp \
                tilesanalyzer.cpp

CONFIG += warn_off
CONFIG -= console
CONFIG(release, debug|release):DEFINES += QT_NO_INFO_OUTPUT
