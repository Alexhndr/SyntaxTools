#ifndef SYNTAX_TOOLS_PARSER_P_HELPERS_H
#define SYNTAX_TOOLS_PARSER_P_HELPERS_H

#include <memory>
#include <vector>
#include <stdarg.h>

#include "../Common/AstNodes.h"
#include "../Common/Helper.h"
#include "../Common/Tokens.h"

using namespace syntax_tools;

enum class PState {
    global,
    local
};

struct PStream final {
    PStream();
    PStream(std::vector<Token>* tokens_);
    void Set(PStream& stream);
    
    PState state = PState::global;
    bool readyForBlockElement = true;
    std::vector<Token>* tokens = nullptr;
    int position = 0;
};

class PHelper: public Helper {
public:
    ~PHelper();
    virtual bool Check(PStream& stream) = 0;
    bool GetChecked() const;
    virtual void Reset();

protected:
    void SetChecked();
    
    bool checked = false;
};

class PhAddition final: public PHelper {
public:
    PhAddition(PHelper* helper, ...);
    bool Check(PStream& stream) override;
    void Reset() override;

private:
    std::vector<PHelper*> helpers;
};

class PhAnyOf final: public PHelper {
public:
    PhAnyOf(PHelper* helper, ...);
    bool Check(PStream& stream) override;
    void Reset() override;

private:
    std::vector<PHelper*> helpers;
};

class PhEof final: public PHelper {
public:
    bool Check(PStream& stream) override;
    void Reset() override;
};

class PhFromToken final: public PHelper {
public:
    PhFromToken(TokenType type_);
    bool Check(PStream& stream) override;
    int GetTknPos() const;
    AstToken GetToken(void* prnt);
    void Reset() override;

private:
    TokenType type;
    AstToken token;
};

template <typename T>
class PhOnceOrMore final: public PHelper {
public:
    bool Check(PStream& stream) override;
    std::vector<std::unique_ptr<T>>& GetHelpers();
    void Reset() override;

private:
    std::vector<std::unique_ptr<T>> helpers;
};

template <typename T>
bool PhOnceOrMore<T>::Check(PStream& stream) {
    PStream newStream;
    newStream.Set(stream);
    std::unique_ptr<T> rule = std::make_unique<T>();
    
    if (!rule->Check(newStream)) {
        return false;
    }
    
    helpers.push_back(std::move(rule));
    stream.Set(newStream);
    
    rule = std::make_unique<T>();
    
    while (rule->Check(stream)) {
        helpers.push_back(std::move(rule));
        rule = std::make_unique<T>();
    }
    
    SetChecked();
    return true;
}

template <typename T>
std::vector<std::unique_ptr<T>>& PhOnceOrMore<T>::GetHelpers() {
    return helpers;
}

template <typename T>
void PhOnceOrMore<T>::Reset() {
    PHelper::Reset();
    
    for (std::unique_ptr<T>& rule : helpers) {
        rule->Reset();
    }
}

class PhOnceOrNot final: public PHelper {
public:
    PhOnceOrNot(PHelper* helper_);
    bool Check(PStream& stream) override;
    void Reset() override;

private:
    PHelper* helper;
};

template <typename T>
class PhSeveral final: public PHelper {
public:
    bool Check(PStream& stream) override;
    std::vector<std::unique_ptr<T>>& GetHelpers();
    void Reset() override;

private:
    std::vector<std::unique_ptr<T>> helpers;
};

template <typename T>
bool PhSeveral<T>::Check(PStream& stream) {
    std::unique_ptr<T> rule = std::make_unique<T>();
    
    while (rule->Check(stream)) {
        helpers.push_back(std::move(rule));
        rule = std::make_unique<T>();
    }
    
    SetChecked();
    return true;
}

template <typename T>
std::vector<std::unique_ptr<T>>& PhSeveral<T>::GetHelpers() {
    return helpers;
}

template <typename T>
void PhSeveral<T>::Reset() {
    PHelper::Reset();
    
    for (std::unique_ptr<T>& rule : helpers) {
        rule->Reset();
    }
}

class PhEndHelper final: public PHelper {
public:
    PhEndHelper();
    bool Check([[maybe_unused]] PStream& stream) override;
    void Reset() override;
};

#endif
