#ifndef SYNTAX_TOOLS_LEXER_L_RULES_H
#define SYNTAX_TOOLS_LEXER_L_RULES_H

#include "../Common/Tokens.h"
#include "Fragments.h"
#include "LHelpers.h"

using namespace syntax_tools;

class LRule {
public:
    virtual ~LRule();
    bool Check(LStream& stream, Token& token) const;
    virtual void CheckCanReadKeyword(LStream& stream) const;
    virtual void CheckCanReadPreprocessorDirective(LStream& stream) const;
    virtual void CheckCanReadSignedFloat(LStream& stream) const;
    virtual void CheckState([[maybe_unused]] LStream& stream) const;
    virtual bool CheckStream(LStream& stream, Token& token) const = 0;
};

class LrComment final: public LRule {
public:
    void CheckCanReadSignedFloat([[maybe_unused]] LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrWhitespace final: public LRule {
public:
    void CheckCanReadKeyword([[maybe_unused]] LStream& stream) const override;
    void CheckCanReadPreprocessorDirective([[maybe_unused]] LStream& stream) const override;
    void CheckCanReadSignedFloat([[maybe_unused]] LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrNewline final: public LRule {
public:
    void CheckCanReadPreprocessorDirective(LStream& stream) const override;
    void CheckState(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrTermNumberSign final: public LRule {
public:
    void CheckState(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrTermIdentifierOrKeyword final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrTermLeftParenthesis final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrTermRightParenthesis final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrDirectiveAmpersand final: public LRule {
public:
    void CheckState(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrDirectiveKeyword final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrDirectiveLeftParenthesis final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrDirectiveRightParenthesis final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrDirectiveString final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrIdentifierOrKeyword final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrSignedFloat final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrFloat final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrDate final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrString final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrStringBeginning final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrStringContinue final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrStringEnding final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrLeftSquareBracket final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrRightSquareBracket final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrLeftParenthesis final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrRightParenthesis final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrFullStop final: public LRule {
public:
    void CheckCanReadKeyword(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrComma final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrSemicolon final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrPlus final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrMinus final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrAsterisk final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrSolidus final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrPercent final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrQuestionMark final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrColon final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrEquals final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrNotEquals final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrLessOrEquals final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrLess final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrGreaterOrEquals final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrGreater final: public LRule {
public:
    void CheckCanReadSignedFloat(LStream& stream) const override;
    bool CheckStream(LStream& stream, Token& token) const override;
};

class LrTilde final: public LRule {
public:
    bool CheckStream(LStream& stream, Token& token) const override;
};

#endif
