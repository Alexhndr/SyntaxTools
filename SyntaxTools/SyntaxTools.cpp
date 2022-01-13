#include "SyntaxTools.h"

SyntaxTools::~SyntaxTools() {
}

bool SyntaxTools::GetAst(const TokenStream& tokenStream, Ast& ast) {
    Parser parser;
    return parser.FillAst(tokenStream, ast);
}

bool SyntaxTools::GetTokenStream(const std::wstring& string, TokenStream& tokenStream) {
    Lexer lexer;
    return lexer.FillTokenStream(string, tokenStream);
}
