include(../SyntaxTools/Defaults.pri)

TARGET = Tests
TEMPLATE = app

CONFIG += console testcase c++17
CONFIG -= app_bundle

QT += core testlib
QT -= gui

HEADERS += \
    Tests.h \
    Lexer/LTests.h \
    Parser/PTests.h

SOURCES += \
    Tests.cpp \
    Lexer/LTests.cpp \
    Parser/PTests.cpp
