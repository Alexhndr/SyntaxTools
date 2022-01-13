#include "LHelpers.h"

LStream::LStream() {
    NextChar();
}

LStream::LStream(const std::wstring* string_) :
    string(string_),
    count(string_->size()) {
    NextChar();
}

wchar_t LStream::GetCurrentChar() const {
    return currentChar;
}

bool LStream::GetIsEof() const {
    return isEof;
}

void LStream::NextChar() {
    if (position == count) {
        return;
    }
    
    position++;
    
    if (position != count) {
        currentChar = (*string)[position];
    }
    else {
        isEof = true;
        currentChar = 0;
    }
}

void LStream::Set(const LStream& stream) {
    string = stream.string;
    count = stream.count;
    
    state = stream.state;
    canReadPreprocessorDirective = stream.canReadPreprocessorDirective;
    canReadKeyword = stream.canReadKeyword;
    canReadSignedFloat = stream.canReadSignedFloat;
    
    position = stream.position;
    isEof = stream.isEof;
    currentChar = stream.currentChar;
}

void LStream::Reset() {
    state = LState::main;
    canReadPreprocessorDirective = true;
    canReadKeyword = true;
    canReadSignedFloat = false;
    
    position = -1;
    isEof = false;
    currentChar = 0;
}

LHelper::~LHelper() {
}

LCharHelper::~LCharHelper() {
}

LhAnyCharExcept::LhAnyCharExcept(LCharHelper* charHelper, ...) {
    va_list list;
    va_start(list, charHelper);
    int numberOfHelpers = 0;
    
    if (!charHelper->GetIsEnding()) {
        charHelpers.push_back(charHelper);
        numberOfHelpers++;
    }
    
    LCharHelper* charHelper_;
    
    while (true) {
        charHelper_ = va_arg(list, LCharHelper*);
        
        if (charHelper_->GetIsEnding()) {
            break;
        }
        
        numberOfHelpers++;
    }
    
    va_start(list, charHelper);
    charHelpers.reserve(numberOfHelpers);
    
    for (int i = 1; i < numberOfHelpers; i++) {
        charHelper_ = va_arg(list, LCharHelper*);
        charHelpers.push_back(charHelper_);
    }
    
    va_end(list);
}

bool LhAnyCharExcept::CheckStream(LStream& stream) const {
    LStream newStream;
    newStream.Set(stream);
    
    for (LCharHelper* charHelper : charHelpers) {
        if (charHelper->CheckStream(newStream)) {
            return false;
        }
    }
    
    if (stream.GetIsEof()) {
        return false;
    }
    
    stream.NextChar();
    return true;
}

LhAnyCharOf::LhAnyCharOf(LCharHelper* charHelper, ...) {
    va_list list;
    va_start(list, charHelper);
    int numberOfHelpers = 0;
    
    if (!charHelper->GetIsEnding()) {
       charHelpers.push_back(charHelper);
       numberOfHelpers++;
    }
    
    LCharHelper* charHelper_;
    
    while (true) {
        charHelper_ = va_arg(list, LCharHelper*);
        
        if (charHelper_->GetIsEnding()) {
            break;
        }
        
        numberOfHelpers++;
    }
    
    va_start(list, charHelper);
    charHelpers.reserve(numberOfHelpers);
    
    for (int i = 1; i < numberOfHelpers; i++) {
        charHelper_ = va_arg(list, LCharHelper*);
        charHelpers.push_back(charHelper_);
    }
    
    va_end(list);
}

bool LhAnyCharOf::CheckStream(LStream& stream) const {
    LStream newStream;
    newStream.Set(stream);
    
    for (LCharHelper* charHelper : charHelpers) {
        if (charHelper->CheckStream(newStream)) {
            stream.Set(newStream);
            return true;
        }
    }
    
    return false;
}

LhAnyCharOfInterval::LhAnyCharOfInterval(wchar_t startChar_, wchar_t endChar_) {
    startChar = startChar_;
    endChar = endChar_;
}

bool LhAnyCharOfInterval::CheckStream(LStream& stream) const {
    if (stream.GetIsEof()) {
        return false;
    }
    
    wchar_t currentChar = stream.GetCurrentChar();
    
    if ((currentChar < startChar) ||
        (currentChar > endChar)) {
        return false;
    }
    
    stream.NextChar();
    return true;
}

LhFromChar::LhFromChar(wchar_t char__) {
    char_ = char__;
}

bool LhFromChar::CheckStream(LStream& stream) const {
    if (stream.GetIsEof()) {
        return false;
    }
    
    wchar_t currentChar = stream.GetCurrentChar();
    
    if (currentChar != char_) {
        return false;
    }
    
    stream.NextChar();
    return true;
}

LhEndHelper::LhEndHelper() {
    isEnding = true;
}

bool LhEndHelper::CheckStream([[maybe_unused]] LStream& stream) const {
    return true;
}

LhAddition::LhAddition(LHelper* helper, ...) {
    va_list list;
    va_start(list, helper);
    int numberOfHelpers = 0;
    
    if (!helper->GetIsEnding()) {
        helpers.push_back(helper);
        numberOfHelpers++;
    }
    
    LHelper* helper_;
    
    while (true) {
        helper_ = va_arg(list, LHelper*);
        
        if (helper_->GetIsEnding()) {
            break;
        }
        
        numberOfHelpers++;
    }
    
    va_start(list, helper);
    helpers.reserve(numberOfHelpers);
    
    for (int i = 1; i < numberOfHelpers; i++) {
        helper_ = va_arg(list, LHelper*);
        helpers.push_back(helper_);
    }
    
    va_end(list);
}

bool LhAddition::CheckStream(LStream& stream) const {
    LStream newStream;
    newStream.Set(stream);
    
    for (LHelper* helper : helpers) {
        if (!helper->CheckStream(newStream)) {
            return false;
        }
    }
    
    stream.Set(newStream);
    return true;
}

bool LhAnyChar::CheckStream(LStream& stream) const {
    if (stream.GetIsEof()) {
        return false;
    }
    
    stream.NextChar();
    return true;
}

LhAnyOf::LhAnyOf(LHelper* helper, ...) {
    va_list list;
    va_start(list, helper);
    int numberOfHelpers = 0;
    
    if (!helper->GetIsEnding()) {
        helpers.push_back(helper);
        numberOfHelpers++;
    }
    
    LHelper* helper_;
    
    while (true) {
        helper_ = va_arg(list, LHelper*);
        
        if (helper_->GetIsEnding()) {
            break;
        }
        
        numberOfHelpers++;
    }
    
    va_start(list, helper);
    helpers.reserve(numberOfHelpers);
    
    for (int i = 1; i < numberOfHelpers; i++) {
        helper_ = va_arg(list, LHelper*);
        helpers.push_back(helper_);
    }
    
    va_end(list);
}

bool LhAnyOf::CheckStream(LStream& stream) const {
    LStream newStream;
    newStream.Set(stream);
    
    for (LHelper* helper : helpers) {
        if (helper->CheckStream(newStream)) {
            stream.Set(newStream);
            return true;
        }
    }
    
    return false;
}

bool LhEof::CheckStream(LStream& stream) const {
    if (stream.GetIsEof()) {
        return true;
    }
    
    return false;
}

LhOnceOrMore::LhOnceOrMore(LHelper* helper_) {
    helper = helper_;
}

bool LhOnceOrMore::CheckStream(LStream& stream) const {
    LStream newStream;
    newStream.Set(stream);
    
    if (!helper->CheckStream(newStream)) {
        return false;
    }
    
    stream.Set(newStream);
    
    while (helper->CheckStream(stream)) {
    }
    
    return true;
}

LhOnceOrNot::LhOnceOrNot(LHelper* helper_) {
    helper = helper_;
}

bool LhOnceOrNot::CheckStream(LStream& stream) const {
    helper->CheckStream(stream);
    return true;
}

LhSeveral::LhSeveral(LHelper* helper_) {
    helper = helper_;
}

bool LhSeveral::CheckStream(LStream& stream) const {
    while (helper->CheckStream(stream)) {
    }
    
    return true;
}
