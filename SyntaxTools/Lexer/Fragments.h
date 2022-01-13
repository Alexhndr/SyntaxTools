#ifndef SYNTAX_TOOLS_LEXER_FRAGMENTS_H
#define SYNTAX_TOOLS_LEXER_FRAGMENTS_H

#include "LHelpers.h"

class LfNewline final: public LHelper {
public:
    bool CheckStream(LStream& stream) const override;
};

class LfNewlineOfString final: public LHelper {
public:
    bool CheckStream(LStream& stream) const override;
};

class LfLCapitalLetter final: public LHelper {
public:
    bool CheckStream(LStream& stream) const override;
};

class LfLSmallLetter final: public LHelper {
public:
    bool CheckStream(LStream& stream) const override;
};

class LfCCapitalLetter final: public LHelper {
public:
    bool CheckStream(LStream& stream) const override;
};

class LfCSmallLetter final: public LHelper {
public:
    bool CheckStream(LStream& stream) const override;
};

class LfLetter final: public LHelper {
public:
    bool CheckStream(LStream& stream) const override;
};

class LfDigit final: public LHelper {
public:
    bool CheckStream(LStream& stream) const override;
};

#endif
