#ifndef SYNTAX_TOOLS_COMMON_TOKENS_H
#define SYNTAX_TOOLS_COMMON_TOKENS_H

#include <cwchar>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace syntax_tools {

enum class TokenType {
    none,
    comment,
    whitespace,
    newline,
    termNumberSign,
    termIf,
    termThen,
    termElsIf,
    termElse,
    termEndIf,
    termRegion,
    termEndRegion,
    termClient,
    termAtClient,
    termAtServer,
    termMobileAppClient,
    termMobileAppServer,
    termThickClientOrdinaryApplication,
    termThickClientManagedApplication,
    termServer,
    termExternalConnection,
    termThinClient,
    termWebClient,
    termAnd,
    termOr,
    termNot,
    termIdentifier,
    termLeftParenthesis,
    termRightParenthesis,
    directiveAmpersand,
    directiveAtClient,
    directiveAtServer,
    directiveAtServerNoContext,
    directiveAtClientAtServerNoContext,
    directiveAtClientAtServer,
    directiveBefore,
    directiveAfter,
    directiveInstead,
    directiveLeftParenthesis,
    directiveRightParenthesis,
    directiveString,
    if_,
    then,
    elsIf,
    else_,
    endIf,
    and_,
    or_,
    not_,
    var,
    export_,
    procedure,
    val,
    return_,
    endProcedure,
    function,
    endFunction,
    for_,
    to,
    do_,
    break_,
    continue_,
    endDo,
    each,
    in,
    while_,
    try_,
    except,
    raise,
    endTry,
    goto_,
    new_,
    execute,
    async,
    await,
    addHandler,
    removeHandler,
    null,
    undefined,
    false_,
    true_,
    identifier,
    signedFloat,
    float_,
    date,
    string,
    stringBeginning,
    stringContinue,
    stringEnding,
    leftSquareBracket,
    rightSquareBracket,
    leftParenthesis,
    rightParenthesis,
    fullStop,
    comma,
    semicolon,
    plus,
    minus,
    asterisk,
    solidus,
    percent,
    questionMark,
    colon,
    equals,
    notEquals,
    lessOrEquals,
    less,
    greaterOrEquals,
    greater,
    tilde
};

class StringToCompare final {
public:
    StringToCompare(const std::wstring& inputString, const long position, const long count_);
    bool Compare(const wchar_t* stringToCompare, const size_t count_) const;
    
    static const short sizeOfBuffer = 100;

private:
    static wchar_t CharToLowerCase(const wchar_t char_);
    
    bool isComparable = true;
    size_t count = 0;
    wchar_t string[sizeOfBuffer];
};

struct Entity {
    virtual ~Entity();
    void SetEntity(const Entity& entity);
    void SetEntity(const Entity& entityA, const Entity& entityB);
    
    int chrPos = -1;
    int numOfChrs = 0;
    int tknPos = -1;
    int numOfTkns = 0;
};

struct Token: public Entity {
    using TypePair = std::pair<TokenType, bool>;
    
    Token();
    Token(const TokenType type_, const int chrPos_, const int numOfChrs_);
    virtual ~Token();
    bool IsEmpty() const;
    
    static TokenType GetTypeForDirectiveString(const std::wstring& string, const int position, const int count);
    static TokenType GetTypeForTermString(const std::wstring& string, const int position, const int count);
    static TypePair GetTypePairForString(const std::wstring& string, const int position, const int count,
        const bool canReadKeyword);
    
    TokenType type = TokenType::none;
};

struct TokenStream {
    virtual ~TokenStream();
    
    std::vector<Token> tokens;
};

}

#endif
