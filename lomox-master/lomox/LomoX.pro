# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = lomox
DESTDIR = ../Release
QT += core sql network xml script webkit widgets webkitwidgets
CONFIG += debug
DEFINES += QT_LARGEFILE_SUPPORT QT_XML_LIB QT_SQL_LIB QT_NETWORK_LIB QT_WEBKIT_LIB QT_PHONON_LIB LOMOX_LIB
INCLUDEPATH += ./GeneratedFiles \
    ./GeneratedFiles/Release \
    . \
    ./include \
    ./implement
LIBS += -lphonon4
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(lomox.pri)
