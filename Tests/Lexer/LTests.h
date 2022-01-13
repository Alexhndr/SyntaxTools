#ifndef SYNTAX_TOOLS_LEXER_L_TESTS_H
#define SYNTAX_TOOLS_LEXER_L_TESTS_H

#include <string>

#include <QObject>
#include <QtTest/QtTest>

#include "../../SyntaxTools/Lexer/Lexer.h"

struct TkStrPos final {
    TkStrPos();
    TkStrPos(const int chrPos_, const int tknPos_);
    
    int chrPos = 0;
    int tknPos = 0;
};

class LexerTests: public QObject {
    Q_OBJECT

public:
    void Test() const;
    virtual ~LexerTests();

private:
    TkStrPos MoveToNextToken(const TkStrPos& tkStrPos, const int numOfChrs) const;
    TkStrPos ProcessToken(const TokenStream& tokenStream, const TkStrPos& tkStrPos, const TokenType type,
        const int numOfChrs) const;
    void VerifyToken(const Token& token, const TkStrPos& tkStrPos, const TokenType type, const int numOfChrs) const;
};

#endif
