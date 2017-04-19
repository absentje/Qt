QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = project
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += main.cpp\
        dialog.cpp \
    make_full_html_file.cpp \
    tag.cpp \
    html_parser.cpp

HEADERS  += dialog.h \
    make_full_html_file.h \
    html_parser.h \
    tag.h

# include Boost
INCLUDEPATH += C:\boost_1_63_0
LIBS += "-LC:\boost_1_63_0\lib64-msvc-14.0"
# include OpenSSL
INCLUDEPATH += C:\Build-OpenSSL-VC-64\include
LIBS += -LC:\Build-OpenSSL-VC-64\lib -llibeay32
LIBS += -LC:\Build-OpenSSL-VC-64\lib -lssleay32
