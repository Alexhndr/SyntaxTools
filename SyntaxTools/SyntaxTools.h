#ifndef SYNTAX_TOOLS_SYNTAX_TOOLS_H
#define SYNTAX_TOOLS_SYNTAX_TOOLS_H

#include <string>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

class SyntaxTools {
public:
    virtual ~SyntaxTools();
    static bool GetAst(const TokenStream& tokenStream, Ast& ast);
    static bool GetTokenStream(const std::wstring& string, TokenStream& tokenStream);
};

#endif
