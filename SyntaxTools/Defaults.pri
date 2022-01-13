HEADERS += \
    ../SyntaxTools/Common/AstNodes.h \
    ../SyntaxTools/Common/Helper.h \
    ../SyntaxTools/Common/Tokens.h \
    ../SyntaxTools/Lexer/Fragments.h \
    ../SyntaxTools/Lexer/Lexer.h \
    ../SyntaxTools/Lexer/LHelpers.h \
    ../SyntaxTools/Lexer/LRules.h \
    ../SyntaxTools/Parser/Parser.h \
    ../SyntaxTools/Parser/PHelpers.h \
    ../SyntaxTools/Parser/PRules.h \
    ../SyntaxTools/SyntaxTools.h

SOURCES += \
    ../SyntaxTools/Common/AstNodes.cpp \
    ../SyntaxTools/Common/Helper.cpp \
    ../SyntaxTools/Common/Tokens.cpp \
    ../SyntaxTools/Lexer/Fragments.cpp \
    ../SyntaxTools/Lexer/Lexer.cpp \
    ../SyntaxTools/Lexer/LHelpers.cpp \
    ../SyntaxTools/Lexer/LRules.cpp \
    ../SyntaxTools/Parser/Parser.cpp \
    ../SyntaxTools/Parser/PHelpers.cpp \
    ../SyntaxTools/Parser/PRules.cpp \
    ../SyntaxTools/SyntaxTools.cpp

INCLUDEPATH += $$PWD/../SyntaxTools
