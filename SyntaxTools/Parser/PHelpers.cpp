#include "PHelpers.h"

PStream::PStream() {
}

PStream::PStream(std::vector<Token>* tokens_) {
    state = PState::global;
    readyForBlockElement = true;
    tokens = tokens_;
    position = 0;
}

void PStream::Set(PStream& stream) {
    state = stream.state;
    readyForBlockElement = stream.readyForBlockElement;
    tokens = stream.tokens;
    position = stream.position;
}

PHelper::~PHelper() {
}

bool PHelper::GetChecked() const {
    return checked;
}

void PHelper::Reset() {
    checked = false;
}

void PHelper::SetChecked() {
    checked = true;
}

PhAddition::PhAddition(PHelper* helper, ...) {
    va_list list;
    va_start(list, helper);
    int numberOfHelpers = 0;
    
    if (!helper->GetIsEnding()) {
        helpers.push_back(helper);
        numberOfHelpers++;
    }
    
    PHelper* helper_;
    
    while (true) {
        helper_ = va_arg(list, PHelper*);
        
        if (helper_->GetIsEnding()) {
            break;
        }
        
        numberOfHelpers++;
    }
    
    va_start(list, helper);
    helpers.reserve(numberOfHelpers);
    
    for (int i = 1; i < numberOfHelpers; i++) {
        helper_ = va_arg(list, PHelper*);
        helpers.push_back(helper_);
    }
    
    va_end(list);
}

bool PhAddition::Check(PStream& stream) {
    PStream newStream;
    newStream.Set(stream);
    std::vector<PHelper*> helpersToReset;
    helpersToReset.reserve(helpers.size());
    
    for (PHelper* helper : helpers) {
        helpersToReset.push_back(helper);
        
        if (!helper->Check(newStream)) {
            for (PHelper* helperToReset : helpersToReset) {
                helperToReset->Reset();
            }
            
            return false;
        }
    }
    
    stream.Set(newStream);
    SetChecked();
    return true;
}

void PhAddition::Reset() {
    PHelper::Reset();
    
    for (PHelper* helper : helpers) {
        helper->Reset();
    }
}

PhAnyOf::PhAnyOf(PHelper* helper, ...) {
    va_list list;
    va_start(list, helper);
    int numberOfHelpers = 0;
    
    if (!helper->GetIsEnding()) {
        helpers.push_back(helper);
        numberOfHelpers++;
    }
    
    PHelper* helper_;
    
    while (true) {
        helper_ = va_arg(list, PHelper*);
        
        if (helper_->GetIsEnding()) {
            break;
        }
        
        numberOfHelpers++;
    }
    
    va_start(list, helper);
    helpers.reserve(numberOfHelpers);
    
    for (int i = 1; i < numberOfHelpers; i++) {
        helper_ = va_arg(list, PHelper*);
        helpers.push_back(helper_);
    }
    
    va_end(list);
}

bool PhAnyOf::Check(PStream& stream) {
    PStream newStream;
    newStream.Set(stream);
    
    for (PHelper* helper : helpers) {
        if (helper->Check(newStream)) {
            stream.Set(newStream);
            SetChecked();
            return true;
        }
    }
    
    return false;
}

void PhAnyOf::Reset() {
    PHelper::Reset();
    
    for (PHelper* helper : helpers) {
        helper->Reset();
    }
}

bool PhEof::Check(PStream& stream) {
    if (stream.position == stream.tokens->size()) {
        SetChecked();
        return true;
    }
    else {
        return false;
    }
}

void PhEof::Reset() {
    PHelper::Reset();
}

PhFromToken::PhFromToken(TokenType type_) :
    type(type_) {
}

bool PhFromToken::Check(PStream& stream) {
    if (stream.position == stream.tokens->size()) {
        return false;
    }
    
    Token currentToken = (*stream.tokens)[stream.position];
    
    if (currentToken.type != type) {
        return false;
    }
    
    stream.position++;
    token.SetFromToken(currentToken);
    SetChecked();
    return true;
}

int PhFromToken::GetTknPos() const {
    return token.tknPos;
}

AstToken PhFromToken::GetToken(void* prnt) {
    token.prnt = prnt;
    return token;
}

void PhFromToken::Reset() {
    PHelper::Reset();
}

PhOnceOrNot::PhOnceOrNot(PHelper* helper_) :
    helper(helper_) {
}

bool PhOnceOrNot::Check(PStream& stream) {
    helper->Check(stream);
    SetChecked();
    return true;
}

void PhOnceOrNot::Reset() {
    PHelper::Reset();
    helper->Reset();
}

PhEndHelper::PhEndHelper() {
    isEnding = true;
}

bool PhEndHelper::Check([[maybe_unused]] PStream& stream) {
    return true;
}

void PhEndHelper::Reset() {
    PHelper::Reset();
}
