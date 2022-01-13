#ifndef SYNTAX_TOOLS_PARSER_PARSER_H
#define SYNTAX_TOOLS_PARSER_PARSER_H

#include <algorithm>
#include <vector>
#include <queue>

#include "../Common/Tokens.h"
#include "PRules.h"

class Parser {
public:
    virtual ~Parser();
    bool FillAst(const TokenStream& tokenStream, Ast& ast);
};

#endif
