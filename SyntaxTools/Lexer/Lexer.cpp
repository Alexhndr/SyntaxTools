#include "Lexer.h"

const LrAsterisk lrAsterisk;
const LrColon lrColon;
const LrComma lrComma;
const LrComment lrComment;
const LrDate lrDate;
const LrDirectiveAmpersand lrDirectiveAmpersand;
const LrDirectiveKeyword lrDirectiveKeyword;
const LrDirectiveLeftParenthesis lrDirectiveLeftParenthesis;
const LrDirectiveRightParenthesis lrDirectiveRightParenthesis;
const LrDirectiveString lrDirectiveString;
const LrEquals lrEquals;
const LrFloat lrFloat;
const LrFullStop lrFullStop;
const LrGreater lrGreater;
const LrGreaterOrEquals lrGreaterOrEquals;
const LrIdentifierOrKeyword lrIdentifierOrKeyword;
const LrLeftParenthesis lrLeftParenthesis;
const LrLeftSquareBracket lrLeftSquareBracket;
const LrLess lrLess;
const LrLessOrEquals lrLessOrEquals;
const LrMinus lrMinus;
const LrNewline lrNewline;
const LrNotEquals lrNotEquals;
const LrPercent lrPercent;
const LrPlus lrPlus;
const LrQuestionMark lrQuestionMark;
const LrRightParenthesis lrRightParenthesis;
const LrRightSquareBracket lrRightSquareBracket;
const LrSemicolon lrSemicolon;
const LrSignedFloat lrSignedFloat;
const LrSolidus lrSolidus;
const LrString lrString;
const LrStringBeginning lrStringBeginning;
const LrStringContinue lrStringContinue;
const LrStringEnding lrStringEnding;
const LrTermIdentifierOrKeyword lrTermIdentifierOrKeyword;
const LrTermLeftParenthesis lrTermLeftParenthesis;
const LrTermRightParenthesis lrTermRightParenthesis;
const LrTermNumberSign lrTermNumberSign;
const LrTilde lrTilde;
const LrWhitespace lrWhitespace;

Lexer::Lexer() {
    InitializeMainRules();
    InitializeTermRules();
    InitializeDirectiveRules();
}

Lexer::~Lexer() {
}

bool Lexer::FillTokenStream(const std::wstring& string, TokenStream& tokenStream) const {
    LStream stream(&string);
    bool ruleFound;
    
    while (stream.position < stream.count) {
        ruleFound = false;
        
        switch (stream.state) {
        case LState::main:
            ruleFound = CheckInRules(stream, mainRules, tokenStream.tokens);
            break;
            
        case LState::term:
            ruleFound = CheckInRules(stream, termRules, tokenStream.tokens);
            break;
            
        case LState::directive:
            ruleFound = CheckInRules(stream, directiveRules, tokenStream.tokens);
            break;
        }
        
        if (!ruleFound) {
            return false;
        }
    }
    
    return true;
}

bool Lexer::CheckInRules(LStream& stream, const std::vector<const LRule*>& rules, std::vector<Token>& tokens) const {
    Token token;
    
    for (const LRule* rule : rules) {
        if (!rule->Check(stream, token)) {
            continue;
        }
        
        token.tknPos = tokens.size();
        tokens.push_back(token);
        return true;
    }
    
    return false;
}

void Lexer::InitializeDirectiveRules() {
    const short numberOfRules = 7;
    directiveRules.reserve(numberOfRules);
    
    directiveRules.push_back(&lrWhitespace);
    directiveRules.push_back(&lrNewline);
    directiveRules.push_back(&lrComment);
    directiveRules.push_back(&lrDirectiveKeyword);
    directiveRules.push_back(&lrDirectiveLeftParenthesis);
    directiveRules.push_back(&lrDirectiveRightParenthesis);
    directiveRules.push_back(&lrDirectiveString);
}

void Lexer::InitializeMainRules() {
    const short numberOfRules = 34;
    mainRules.reserve(numberOfRules);
    
    mainRules.push_back(&lrWhitespace);
    mainRules.push_back(&lrNewline);
    mainRules.push_back(&lrComment);
    mainRules.push_back(&lrIdentifierOrKeyword);
    mainRules.push_back(&lrFullStop);
    mainRules.push_back(&lrComma);
    mainRules.push_back(&lrSemicolon);
    mainRules.push_back(&lrLeftParenthesis);
    mainRules.push_back(&lrRightParenthesis);
    mainRules.push_back(&lrLeftSquareBracket);
    mainRules.push_back(&lrRightSquareBracket);
    mainRules.push_back(&lrSignedFloat);
    mainRules.push_back(&lrFloat);
    mainRules.push_back(&lrString);
    mainRules.push_back(&lrStringBeginning);
    mainRules.push_back(&lrStringContinue);
    mainRules.push_back(&lrStringEnding);
    mainRules.push_back(&lrDate);
    mainRules.push_back(&lrPlus);
    mainRules.push_back(&lrMinus);
    mainRules.push_back(&lrAsterisk);
    mainRules.push_back(&lrSolidus);
    mainRules.push_back(&lrPercent);
    mainRules.push_back(&lrQuestionMark);
    mainRules.push_back(&lrColon);
    mainRules.push_back(&lrEquals);
    mainRules.push_back(&lrNotEquals);
    mainRules.push_back(&lrLessOrEquals);
    mainRules.push_back(&lrLess);
    mainRules.push_back(&lrGreaterOrEquals);
    mainRules.push_back(&lrGreater);
    mainRules.push_back(&lrTilde);
    mainRules.push_back(&lrTermNumberSign);
    mainRules.push_back(&lrDirectiveAmpersand);
}

void Lexer::InitializeTermRules() {
    const short numberOfRules = 6;
    termRules.reserve(numberOfRules);
    
    termRules.push_back(&lrWhitespace);
    termRules.push_back(&lrNewline);
    termRules.push_back(&lrComment);
    termRules.push_back(&lrTermIdentifierOrKeyword);
    termRules.push_back(&lrTermLeftParenthesis);
    termRules.push_back(&lrTermRightParenthesis);
}
