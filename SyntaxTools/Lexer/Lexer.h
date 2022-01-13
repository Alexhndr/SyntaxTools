#ifndef SYNTAX_TOOLS_LEXER_LEXER_H
#define SYNTAX_TOOLS_LEXER_LEXER_H

#include <string>
#include <vector>

#include "../Common/Tokens.h"
#include "LHelpers.h"
#include "LRules.h"

struct Lexer {
public:
    Lexer();
    virtual ~Lexer();
    bool FillTokenStream(const std::wstring& string, TokenStream& tokenStream) const;

private:
    bool CheckInRules(LStream& stream, const std::vector<const LRule*>& rules, std::vector<Token>& tokens) const;
    void InitializeDirectiveRules();
    void InitializeMainRules();
    void InitializeTermRules();
    
    std::vector<const LRule*> directiveRules;
    std::vector<const LRule*> mainRules;
    std::vector<const LRule*> termRules;
};

#endif
