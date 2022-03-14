QT += concurrent svg network

VERSION = 1.0.2

CONFIG += no_lflags_merge rtti_off warn_on c++latest strict_c++ precompile_header utf8_source

DEFINES +=                 \
  QT_DISABLE_DEPRECATED_BEFORE=0x050B00 \# отключить API, устаревший в 5.11 или более ранних версиях
  QT_USE_FAST_CONCATENATION\
  QT_DEPRECATED_WARNINGS   \
  QT_USE_FAST_OPERATOR_PLUS\
  DQT_NO_URL_CAST_FROM_STRING\
  QT_USE_STRING_BUILDER \

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
