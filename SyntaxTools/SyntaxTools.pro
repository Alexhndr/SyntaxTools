TARGET = SyntaxTools
TEMPLATE = lib
CONFIG += c++17

HEADERS += \
    Common/AstNodes.h \
    Common/Helper.h \
    Common/Tokens.h \
    Lexer/Fragments.h \
    Lexer/Lexer.h \
    Lexer/LHelpers.h \
    Lexer/LRules.h \
    Parser/Parser.h \
    Parser/PHelpers.h \
    Parser/PRules.h \
    SyntaxTools.h

SOURCES += \
    Common/AstNodes.cpp \
    Common/Helper.cpp \
    Common/Tokens.cpp \
    Lexer/Fragments.cpp \
    Lexer/Lexer.cpp \
    Lexer/LHelpers.cpp \
    Lexer/LRules.cpp \
    Parser/Parser.cpp \
    Parser/PHelpers.cpp \
    Parser/PRules.cpp \
    SyntaxTools.cpp
