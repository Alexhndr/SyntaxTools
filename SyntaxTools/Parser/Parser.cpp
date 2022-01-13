#include "Parser.h"

Parser::~Parser() {
}

bool Parser::FillAst(const TokenStream& tokenStream, Ast& ast) {
    std::vector<Token> tokens;
    std::copy_if(tokenStream.tokens.begin(), tokenStream.tokens.end(), std::back_inserter(tokens),
        [](const Token& token) {
            return ((token.type != TokenType::comment)
                && (token.type != TokenType::whitespace)
                && (token.type != TokenType::newline));
        });
    
    if (tokens.empty()) {
        return false;
    }
    
    PrBlock block;
    PStream stream(&tokens);
    
    if (!block.Check(stream)) {
        return false;
    }
    
    if (stream.position != stream.tokens->size()) {
        return false;
    }
    
    ast.block = block.GetBlock(&ast);
    ast.SetEntity(*ast.block);
    return true;
}
