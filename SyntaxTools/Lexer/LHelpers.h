#ifndef SYNTAX_TOOLS_LEXER_L_HELPERS_H
#define SYNTAX_TOOLS_LEXER_L_HELPERS_H

#include <stdarg.h>
#include <string>
#include <vector>

#include "../Common/Helper.h"

enum class LState {
    main,
    term,
    directive
};

class LStream final {
public:
    LStream();
    LStream(const std::wstring* string_);
    wchar_t GetCurrentChar() const;
    bool GetIsEof() const;
    void NextChar();
    void Set(const LStream& stream);
    
    const std::wstring* string = nullptr;
    size_t count = 0;
    
    LState state = LState::main;
    bool canReadKeyword = true;
    bool canReadPreprocessorDirective = true;
    bool canReadSignedFloat = false;
    
    int position = -1;

private:
    void Reset();
    
    bool isEof = false;
    wchar_t currentChar = 0;
};

class LHelper: public Helper {
public:
    virtual ~LHelper();
    virtual bool CheckStream(LStream& stream) const = 0;
};

class LCharHelper: public LHelper {
public:
    virtual ~LCharHelper();
    virtual bool CheckStream(LStream& stream) const override = 0;
};

class LhAnyCharExcept final: public LCharHelper {
public:
    LhAnyCharExcept(LCharHelper* charHelper, ...);
    bool CheckStream(LStream& stream) const override;

private:
    std::vector<LCharHelper*> charHelpers;
};

class LhAnyCharOf final: public LCharHelper {
public:
    LhAnyCharOf(LCharHelper* charHelper, ...);
    bool CheckStream(LStream& stream) const override;

private:
    std::vector<LCharHelper*> charHelpers;
};

class LhAnyCharOfInterval final: public LCharHelper {
public:
    LhAnyCharOfInterval(wchar_t startChar_, wchar_t endChar_);
    bool CheckStream(LStream& stream) const override;

private:
    wchar_t startChar;
    wchar_t endChar;
};

class LhFromChar final: public LCharHelper {
public:
    LhFromChar(wchar_t char__);
    bool CheckStream(LStream& stream) const override;

private:
    wchar_t char_;
};

class LhEndHelper final: public LCharHelper {
public:
    LhEndHelper();
    bool CheckStream([[maybe_unused]] LStream& stream) const override;
};

class LhAddition final: public LHelper {
public:
    LhAddition(LHelper* helper, ...);
    bool CheckStream(LStream& stream) const override;

private:
    std::vector<LHelper*> helpers;
};

class LhAnyChar final: public LHelper {
public:
    bool CheckStream(LStream& stream) const override;
};

class LhAnyOf final: public LHelper {
public:
    LhAnyOf(LHelper* helper, ...);
    bool CheckStream(LStream& stream) const override;

private:
    std::vector<LHelper*> helpers;
};

class LhEof final: public LHelper {
public:
    bool CheckStream(LStream& stream) const override;
};

class LhOnceOrMore final: public LHelper {
public:
    LhOnceOrMore(LHelper* helper_);
    bool CheckStream(LStream& stream) const override;

private:
    LHelper* helper;
};

class LhOnceOrNot final: public LHelper {
public:
    LhOnceOrNot(LHelper* helper_);
    bool CheckStream(LStream& stream) const override;

private:
    LHelper* helper;
};

class LhSeveral final: public LHelper {
public:
    LhSeveral(LHelper* helper_);
    bool CheckStream(LStream& stream) const override;

private:
    LHelper* helper;
};

#endif
