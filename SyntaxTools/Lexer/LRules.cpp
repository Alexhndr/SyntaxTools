#include "LRules.h"

const LhEndHelper endHelper;

LRule::~LRule() {
}

bool LRule::Check(LStream& stream, Token& token) const {
    if (!CheckStream(stream, token)) {
        return false;
    }
    
    CheckState(stream);
    CheckCanReadPreprocessorDirective(stream);
    CheckCanReadKeyword(stream);
    CheckCanReadSignedFloat(stream);
    return true;
}

void LRule::CheckCanReadKeyword(LStream& stream) const {
    stream.canReadKeyword = true;
}

void LRule::CheckCanReadPreprocessorDirective(LStream& stream) const {
    stream.canReadPreprocessorDirective = false;
}

void LRule::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = false;
}

void LRule::CheckState([[maybe_unused]] LStream& stream) const {
}

void LrComment::CheckCanReadSignedFloat([[maybe_unused]] LStream& stream) const {
}

bool LrComment::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharR('\r');
    LhFromChar fromCharN('\n');
    LhAnyCharExcept anyCharExcept(&fromCharR, &fromCharN, &endHelper);
    
    LfNewlineOfString newlineOfString;
    LhEof eof;
    LhAnyOf anyOf(&newlineOfString, &eof, &endHelper);
    
    LhFromChar fromCharSolidus('/');
    LhSeveral several(&anyCharExcept);
    LhAddition addition(&fromCharSolidus, &fromCharSolidus, &several, &anyOf, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::comment, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrWhitespace::CheckCanReadKeyword([[maybe_unused]] LStream& stream) const {
}

void LrWhitespace::CheckCanReadPreprocessorDirective([[maybe_unused]] LStream& stream) const {
}

void LrWhitespace::CheckCanReadSignedFloat([[maybe_unused]] LStream& stream) const {
}

bool LrWhitespace::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharT('\t');
    LhFromChar fromCharSpace(' ');
    LhAnyCharOf anyCharOf(&fromCharT, &fromCharSpace, &endHelper);
    
    LhOnceOrMore onceOrMore(&anyCharOf);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!onceOrMore.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::whitespace, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrNewline::CheckCanReadPreprocessorDirective(LStream& stream) const {
    stream.canReadPreprocessorDirective = true;
}

void LrNewline::CheckState(LStream& stream) const {
    stream.state = LState::main;
}

bool LrNewline::CheckStream(LStream& stream, Token& token) const {
    LfNewline newline;
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!newline.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::newline, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrTermNumberSign::CheckState(LStream& stream) const {
    stream.state = LState::term;
}

bool LrTermNumberSign::CheckStream(LStream& stream, Token& token) const {
    if (!stream.canReadPreprocessorDirective) {
        return false;
    }
    
    LhFromChar fromCharNumberSign('#');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharNumberSign.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::termNumberSign, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrTermIdentifierOrKeyword::CheckStream(LStream& stream, Token& token) const {
    LfLetter letter;
    LhFromChar fromCharLowLine('_');
    LhAnyOf anyOf(&letter, &fromCharLowLine, &endHelper);
    
    LfDigit digit;
    LhAnyOf anyOfHlSeveral(&letter, &digit, &fromCharLowLine, &endHelper);
    
    LhSeveral several(&anyOfHlSeveral);
    LhAddition addition(&anyOf, &several, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    TokenType type = Token::GetTypeForTermString(*newStream.string, stream.position, count);
    Token newToken(type, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrTermLeftParenthesis::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharLeftParenthesis('(');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharLeftParenthesis.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::termLeftParenthesis, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrTermRightParenthesis::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharRightParenthesis(')');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharRightParenthesis.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::termRightParenthesis, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrDirectiveAmpersand::CheckState(LStream& stream) const {
    stream.state = LState::directive;
}

bool LrDirectiveAmpersand::CheckStream(LStream& stream, Token& token) const {
    if (!stream.canReadPreprocessorDirective) {
        return false;
    }
    
    LhFromChar fromCharAmpersand('&');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharAmpersand.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::directiveAmpersand, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrDirectiveKeyword::CheckStream(LStream& stream, Token& token) const {
    LfLetter letter;
    LhFromChar fromCharLowLine('_');
    LhAnyOf anyOf(&letter, &fromCharLowLine, &endHelper);
    
    LfDigit digit;
    LhAnyOf anyOfHlSeveral(&letter, &digit, &fromCharLowLine, &endHelper);
    
    LhSeveral several(&anyOfHlSeveral);
    LhAddition addition(&anyOf, &several, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    TokenType type = Token::GetTypeForDirectiveString(*newStream.string, stream.position, count);
    
    if (type == TokenType::none) {
        return false;
    }
    
    Token newToken(type, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrDirectiveLeftParenthesis::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharLeftParenthesis('(');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharLeftParenthesis.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::directiveLeftParenthesis, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrDirectiveRightParenthesis::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharRightParenthesis(')');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharRightParenthesis.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::directiveRightParenthesis, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrDirectiveString::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharR('\r');
    LhFromChar fromCharN('\n');
    LhFromChar fromCharQuotationMark('\"');
    LhAnyCharExcept anyCharExcept(&fromCharR, &fromCharN, &fromCharQuotationMark, &endHelper);
    
    LhAddition additionDouble(&fromCharQuotationMark, &fromCharQuotationMark, &endHelper);
    LhAnyOf anyOf(&anyCharExcept, &additionDouble, &endHelper);
    LhSeveral several(&anyOf);
    LhAddition addition(&fromCharQuotationMark, &several, &fromCharQuotationMark, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::directiveString, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrIdentifierOrKeyword::CheckStream(LStream& stream, Token& token) const {
    LfLetter letter;
    LhFromChar fromCharLowLine('_');
    LhAnyOf anyOf(&letter, &fromCharLowLine, &endHelper);
    
    LfDigit digit;
    LhAnyOf anyOfHlSeveral(&letter, &digit, &fromCharLowLine, &endHelper);
    LhSeveral several(&anyOfHlSeveral);
    LhAddition addition(&anyOf, &several, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token::TypePair typePair = Token::GetTypePairForString(*newStream.string, stream.position, count,
        newStream.canReadKeyword);
    Token newToken(std::get<0>(typePair), stream.position, count);
    token = newToken;
    
    newStream.canReadSignedFloat = std::get<1>(typePair);
    stream.Set(newStream);
    return true;
}

bool LrSignedFloat::CheckStream(LStream& stream, Token& token) const {
    if (!stream.canReadSignedFloat) {
        return false;
    }
    
    LhFromChar fromCharPlus('+');
    LhFromChar fromCharMinus('-');
    LhAnyOf anyOf(&fromCharPlus, &fromCharMinus, &endHelper);
    
    LfDigit digit;
    LhOnceOrMore onceOrMore(&digit);
    LhFromChar fromCharFullStop('.');
    LhAddition additionEnd(&fromCharFullStop, &onceOrMore, &endHelper);
    
    LhOnceOrNot onceOrNotEnd(&additionEnd);
    LhAddition addition(&anyOf, &onceOrMore, &onceOrNotEnd, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::signedFloat, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrFloat::CheckStream(LStream& stream, Token& token) const {
    LfDigit digit;
    LhOnceOrMore onceOrMore(&digit);
    LhFromChar fromCharFullStop('.');
    LhAddition additionEnd(&fromCharFullStop, &onceOrMore, &endHelper);
    
    LhOnceOrNot onceOrNotEnd(&additionEnd);
    LhAddition addition(&onceOrMore, &onceOrNotEnd, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::float_, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrDate::CheckStream(LStream& stream, Token& token) const {
    LfDigit digit;
    LhSeveral several(&digit);
    LhFromChar fromCharApostrophe('\'');
    LhAddition addition(&fromCharApostrophe, &several, &fromCharApostrophe, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::date, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrString::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharR('\r');
    LhFromChar fromCharN('\n');
    LhFromChar fromCharQuotationMark('\"');
    LhAnyCharExcept anyCharExcept(&fromCharR, &fromCharN, &fromCharQuotationMark, &endHelper);
    
    LhAddition additionDouble(&fromCharQuotationMark, &fromCharQuotationMark, &endHelper);
    LhAnyOf anyOf(&anyCharExcept, &additionDouble, &endHelper);
    LhSeveral several(&anyOf);
    LhAddition addition(&fromCharQuotationMark, &several, &fromCharQuotationMark, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::string, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrStringBeginning::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharR('\r');
    LhFromChar fromCharN('\n');
    LhFromChar fromCharQuotationMark('\"');
    LhAnyCharExcept anyCharExcept(&fromCharR, &fromCharN, &fromCharQuotationMark, &endHelper);
    
    LhAddition additionDouble(&fromCharQuotationMark, &fromCharQuotationMark, &endHelper);
    LhAnyOf anyOf(&anyCharExcept, &additionDouble, &endHelper);
    LhSeveral several(&anyOf);
    LfNewlineOfString newlineOfString;
    LhAddition addition(&fromCharQuotationMark, &several, &newlineOfString, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::stringBeginning, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrStringContinue::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharR('\r');
    LhFromChar fromCharN('\n');
    LhFromChar fromCharQuotationMark('\"');
    LhAnyCharExcept anyCharExcept(&fromCharR, &fromCharN, &fromCharQuotationMark, &endHelper);
    
    LhAddition additionDouble(&fromCharQuotationMark, &fromCharQuotationMark, &endHelper);
    LhAnyOf anyOf(&anyCharExcept, &additionDouble, &endHelper);
    
    LhFromChar fromCharVerticalLine('|');
    LhSeveral several(&anyOf);
    LfNewlineOfString newlineOfString;
    LhAddition addition(&fromCharVerticalLine, &several, &newlineOfString, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::stringContinue, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrStringEnding::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharR('\r');
    LhFromChar fromCharN('\n');
    LhFromChar fromCharQuotationMark('\"');
    LhAnyCharExcept anyCharExcept(&fromCharR, &fromCharN, &fromCharQuotationMark, &endHelper);
    
    LhAddition additionDouble(&fromCharQuotationMark, &fromCharQuotationMark, &endHelper);
    LhAnyOf anyOf(&anyCharExcept, &additionDouble, &endHelper);
    
    LhFromChar fromCharVerticalLine('|');
    LhSeveral several(&anyOf);
    LhAddition addition(&fromCharVerticalLine, &several, &fromCharQuotationMark, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::stringEnding, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrLeftSquareBracket::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrLeftSquareBracket::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharLeftSquareBracket('[');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharLeftSquareBracket.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::leftSquareBracket, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrRightSquareBracket::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharRightSquareBracket(']');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharRightSquareBracket.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::rightSquareBracket, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrLeftParenthesis::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrLeftParenthesis::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharLeftParenthesis('(');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharLeftParenthesis.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::leftParenthesis, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrRightParenthesis::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharRightParenthesis(')');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharRightParenthesis.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::rightParenthesis, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrFullStop::CheckCanReadKeyword(LStream& stream) const {
    stream.canReadKeyword = false;
}

bool LrFullStop::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharFullStop('.');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharFullStop.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::fullStop, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrComma::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrComma::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharComma(',');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharComma.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::comma, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrSemicolon::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharSemicolon(';');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharSemicolon.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::semicolon, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrPlus::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrPlus::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharPlus('+');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharPlus.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::plus, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrMinus::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrMinus::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharMinus('-');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharMinus.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::minus, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrAsterisk::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrAsterisk::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharAsterisk('*');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharAsterisk.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::asterisk, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrSolidus::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrSolidus::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharSolidus('/');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharSolidus.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::solidus, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrPercent::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrPercent::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharPercent('%');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharPercent.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::percent, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrQuestionMark::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharQuestionMark('?');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharQuestionMark.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::questionMark, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrColon::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharColon(':');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharColon.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::colon, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrEquals::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrEquals::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharEquals('=');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharEquals.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::equals, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrNotEquals::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrNotEquals::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharLess('<');
    LhFromChar fromCharGreater('>');
    LhAddition addition(&fromCharLess, &fromCharGreater, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::notEquals, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrLessOrEquals::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrLessOrEquals::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharLess('<');
    LhFromChar fromCharEquals('=');
    LhAddition addition(&fromCharLess, &fromCharEquals, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::lessOrEquals, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrLess::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrLess::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharLess('<');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharLess.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::less, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrGreaterOrEquals::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrGreaterOrEquals::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharGreater('>');
    LhFromChar fromCharEquals('=');
    LhAddition addition(&fromCharGreater, &fromCharEquals, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::greaterOrEquals, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

void LrGreater::CheckCanReadSignedFloat(LStream& stream) const {
    stream.canReadSignedFloat = true;
}

bool LrGreater::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharGreater('>');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharGreater.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::greater, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}

bool LrTilde::CheckStream(LStream& stream, Token& token) const {
    LhFromChar fromCharTilde('~');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!fromCharTilde.CheckStream(newStream)) {
        return false;
    }
    
    int count = newStream.position - stream.position;
    Token newToken(TokenType::tilde, stream.position, count);
    token = newToken;
    
    stream.Set(newStream);
    return true;
}
