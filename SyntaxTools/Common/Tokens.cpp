#include "Tokens.h"

using namespace syntax_tools;

StringToCompare::StringToCompare(const std::wstring& inputString, const long position, const long count_) {
    
    if (count_ > sizeOfBuffer) {
         isComparable = false;
         return;
    }
    
    count = count_;
    
    for (int i = 0; i < count; i++) {
        string[i] = CharToLowerCase(inputString[position + i]);
    }
}

bool StringToCompare::Compare(const wchar_t* stringToCompare, const size_t count_) const {
    
    if (!isComparable) {
        return false;
    }
    
    if (count_ != count) {
        return false;
    }
    
    return (wmemcmp(string, stringToCompare, count) == 0);
}

wchar_t StringToCompare::CharToLowerCase(const wchar_t char_) {
    const short offset = 32;
    
    if (((char_ >= 'A')
            && (char_ <= 'Z'))
        || ((char_ >= 0x0410)
            && (char_ <= 0x042f))) {
        return char_ + offset;
    }
    
    return char_;
}

Entity::~Entity() {
}

void Entity::SetEntity(const Entity& entity) {
    chrPos = entity.chrPos;
    numOfChrs = entity.numOfChrs;
    tknPos = entity.tknPos;
    numOfTkns = entity.numOfTkns;
}

void Entity::SetEntity(const Entity& entityA, const Entity& entityB) {
    chrPos = entityA.chrPos;
    numOfChrs = entityB.chrPos + entityB.numOfChrs - chrPos;
    tknPos = entityA.tknPos;
    numOfTkns = entityB.tknPos + entityB.numOfTkns - tknPos;
}

Token::Token() {
}

Token::Token(const TokenType type_, const int chrPos_, const int numOfChrs_) :
    type(type_) {
    chrPos = chrPos_;
    numOfChrs = numOfChrs_;
    numOfTkns = 1;
}

Token::~Token() {
}

bool Token::IsEmpty() const {
    return (type == TokenType::none);
}

TokenType Token::GetTypeForDirectiveString(const std::wstring& string, const int position, const int count) {
    if (count > StringToCompare::sizeOfBuffer) {
        return TokenType::none;
    }
    
    StringToCompare stringToCompare(string, position, count);
    
    if (stringToCompare.Compare(L"atclient", 8)) {
        return TokenType::directiveAtClient;
    }
    else if (stringToCompare.Compare(L"наклиенте", 9)) {
        return TokenType::directiveAtClient;
    }
    else if (stringToCompare.Compare(L"atserver", 8)) {
        return TokenType::directiveAtServer;
    }
    else if (stringToCompare.Compare(L"насервере", 9)) {
        return TokenType::directiveAtServer;
    }
    else if (stringToCompare.Compare(L"atservernocontext", 17)) {
        return TokenType::directiveAtServerNoContext;
    }
    else if (stringToCompare.Compare(L"насерверебезконтекста", 21)) {
        return TokenType::directiveAtServerNoContext;
    }
    else if (stringToCompare.Compare(L"atclientatservernocontext", 25)) {
        return TokenType::directiveAtClientAtServerNoContext;
    }
    else if (stringToCompare.Compare(L"наклиентенасерверебезконтекста", 30)) {
        return TokenType::directiveAtClientAtServerNoContext;
    }
    else if (stringToCompare.Compare(L"atclientatserver", 16)) {
        return TokenType::directiveAtClientAtServer;
    }
    else if (stringToCompare.Compare(L"наклиентенасервере", 18)) {
        return TokenType::directiveAtClientAtServer;
    }
    else if (stringToCompare.Compare(L"before", 6)) {
        return TokenType::directiveBefore;
    }
    else if (stringToCompare.Compare(L"перед", 5)) {
        return TokenType::directiveBefore;
    }
    else if (stringToCompare.Compare(L"after", 5)) {
        return TokenType::directiveAfter;
    }
    else if (stringToCompare.Compare(L"после", 5)) {
        return TokenType::directiveAfter;
    }
    else if (stringToCompare.Compare(L"instead", 7)) {
        return TokenType::directiveInstead;
    }
    else if (stringToCompare.Compare(L"вместо", 6)) {
        return TokenType::directiveInstead;
    }
    
    return TokenType::none;
}

TokenType Token::GetTypeForTermString(const std::wstring& string, const int position, const int count) {
    if (count > StringToCompare::sizeOfBuffer) {
        return TokenType::termIdentifier;
    }
    
    StringToCompare stringToCompare(string, position, count);
    
    if (stringToCompare.Compare(L"if", 2)) {
        return TokenType::termIf;
    }
    else if (stringToCompare.Compare(L"если", 4)) {
        return TokenType::termIf;
    }
    else if (stringToCompare.Compare(L"then", 4)) {
        return TokenType::termThen;
    }
    else if (stringToCompare.Compare(L"тогда", 5)) {
        return TokenType::termThen;
    }
    else if (stringToCompare.Compare(L"elsif", 5)) {
        return TokenType::termElsIf;
    }
    else if (stringToCompare.Compare(L"иначеесли", 9)) {
        return TokenType::termElsIf;
    }
    else if (stringToCompare.Compare(L"else", 4)) {
        return TokenType::termElse;
    }
    else if (stringToCompare.Compare(L"иначе", 5)) {
        return TokenType::termElse;
    }
    else if (stringToCompare.Compare(L"endif", 5)) {
        return TokenType::termEndIf;
    }
    else if (stringToCompare.Compare(L"конецесли", 9)) {
        return TokenType::termEndIf;
    }
    else if (stringToCompare.Compare(L"region", 6)) {
        return TokenType::termRegion;
    }
    else if (stringToCompare.Compare(L"область", 7)) {
        return TokenType::termRegion;
    }
    else if (stringToCompare.Compare(L"endregion", 9)) {
        return TokenType::termEndRegion;
    }
    else if (stringToCompare.Compare(L"конецобласти", 12)) {
        return TokenType::termEndRegion;
    }
    else if (stringToCompare.Compare(L"client", 6)) {
        return TokenType::termClient;
    }
    else if (stringToCompare.Compare(L"клиент", 6)) {
        return TokenType::termClient;
    }
    else if (stringToCompare.Compare(L"atclient", 8)) {
        return TokenType::termAtClient;
    }
    else if (stringToCompare.Compare(L"наклиенте", 9)) {
        return TokenType::termAtClient;
    }
    else if (stringToCompare.Compare(L"atserver", 8)) {
        return TokenType::termAtServer;
    }
    else if (stringToCompare.Compare(L"насервере", 9)) {
        return TokenType::termAtServer;
    }
    else if (stringToCompare.Compare(L"mobileappclient", 15)) {
        return TokenType::termMobileAppClient;
    }
    else if (stringToCompare.Compare(L"мобильноеприложениеклиент", 25)) {
        return TokenType::termMobileAppClient;
    }
    else if (stringToCompare.Compare(L"mobileappserver", 15)) {
        return TokenType::termMobileAppServer;
    }
    else if (stringToCompare.Compare(L"мобильноеприложениесервер", 25)) {
        return TokenType::termMobileAppServer;
    }
    else if (stringToCompare.Compare(L"thickclientordinaryapplication", 30)) {
        return TokenType::termThickClientOrdinaryApplication;
    }
    else if (stringToCompare.Compare(L"толстыйклиентобычноеприложение", 30)) {
        return TokenType::termThickClientOrdinaryApplication;
    }
    else if (stringToCompare.Compare(L"thickclientmanagedapplication", 29)) {
        return TokenType::termThickClientManagedApplication;
    }
    else if (stringToCompare.Compare(L"толстыйклиентуправляемоеприложение", 34)) {
        return TokenType::termThickClientManagedApplication;
    }
    else if (stringToCompare.Compare(L"server", 6)) {
        return TokenType::termServer;
    }
    else if (stringToCompare.Compare(L"сервер", 6)) {
        return TokenType::termServer;
    }
    else if (stringToCompare.Compare(L"externalconnection", 18)) {
        return TokenType::termExternalConnection;
    }
    else if (stringToCompare.Compare(L"внешнеесоединение", 17)) {
        return TokenType::termExternalConnection;
    }
    else if (stringToCompare.Compare(L"thinclient", 10)) {
        return TokenType::termThinClient;
    }
    else if (stringToCompare.Compare(L"тонкийклиент", 12)) {
        return TokenType::termThinClient;
    }
    else if (stringToCompare.Compare(L"webclient", 9)) {
        return TokenType::termWebClient;
    }
    else if (stringToCompare.Compare(L"вебклиент", 9)) {
        return TokenType::termWebClient;
    }
    else if (stringToCompare.Compare(L"and", 3)) {
        return TokenType::termAnd;
    }
    else if (stringToCompare.Compare(L"и", 1)) {
        return TokenType::termAnd;
    }
    else if (stringToCompare.Compare(L"or", 2)) {
        return TokenType::termOr;
    }
    else if (stringToCompare.Compare(L"или", 3)) {
        return TokenType::termOr;
    }
    else if (stringToCompare.Compare(L"not", 3)) {
        return TokenType::termNot;
    }
    else if (stringToCompare.Compare(L"не", 2)) {
        return TokenType::termNot;
    }
    
    return TokenType::termIdentifier;
}

Token::TypePair Token::GetTypePairForString(const std::wstring& string, const int position, const int count,
    const bool canReadKeyword) {
    if (!canReadKeyword) {
        return TypePair{TokenType::identifier, false};
    }
    
    if (count > StringToCompare::sizeOfBuffer) {
        return TypePair{TokenType::identifier, false};
    }
    
    StringToCompare stringToCompare(string, position, count);
    
    if (stringToCompare.Compare(L"if", 2)) {
        return TypePair{TokenType::if_, true};
    }
    else if (stringToCompare.Compare(L"если", 4)) {
        return TypePair{TokenType::if_, true};
    }
    else if (stringToCompare.Compare(L"then", 4)) {
        return TypePair{TokenType::then, false};
    }
    else if (stringToCompare.Compare(L"тогда", 5)) {
        return TypePair{TokenType::then, false};
    }
    else if (stringToCompare.Compare(L"elsif", 5)) {
        return TypePair{TokenType::elsIf, true};
    }
    else if (stringToCompare.Compare(L"иначеесли", 9)) {
        return TypePair{TokenType::elsIf, true};
    }
    else if (stringToCompare.Compare(L"else", 4)) {
        return TypePair{TokenType::else_, false};
    }
    else if (stringToCompare.Compare(L"иначе", 5)) {
        return TypePair{TokenType::else_, false};
    }
    else if (stringToCompare.Compare(L"endif", 5)) {
        return TypePair{TokenType::endIf, false};
    }
    else if (stringToCompare.Compare(L"конецесли", 9)) {
        return TypePair{TokenType::endIf, false};
    }
    else if (stringToCompare.Compare(L"and", 3)) {
        return TypePair{TokenType::and_, true};
    }
    else if (stringToCompare.Compare(L"и", 1)) {
        return TypePair{TokenType::and_, true};
    }
    else if (stringToCompare.Compare(L"or", 2)) {
        return TypePair{TokenType::or_, true};
    }
    else if (stringToCompare.Compare(L"или", 3)) {
        return TypePair{TokenType::or_, true};
    }
    else if (stringToCompare.Compare(L"not", 3)) {
        return TypePair{TokenType::not_, true};
    }
    else if (stringToCompare.Compare(L"не", 2)) {
        return TypePair{TokenType::not_, true};
    }
    else if (stringToCompare.Compare(L"var", 3)) {
        return TypePair{TokenType::var, false};
    }
    else if (stringToCompare.Compare(L"перем", 5)) {
        return TypePair{TokenType::var, false};
    }
    else if (stringToCompare.Compare(L"export", 6)) {
        return TypePair{TokenType::export_, false};
    }
    else if (stringToCompare.Compare(L"экспорт", 7)) {
        return TypePair{TokenType::export_, false};
    }
    else if (stringToCompare.Compare(L"procedure", 9)) {
        return TypePair{TokenType::procedure, false};
    }
    else if (stringToCompare.Compare(L"процедура", 9)) {
        return TypePair{TokenType::procedure, false};
    }
    else if (stringToCompare.Compare(L"val", 3)) {
        return TypePair{TokenType::val, false};
    }
    else if (stringToCompare.Compare(L"знач", 4)) {
        return TypePair{TokenType::val, false};
    }
    else if (stringToCompare.Compare(L"return", 6)) {
        return TypePair{TokenType::return_, true};
    }
    else if (stringToCompare.Compare(L"возврат", 7)) {
        return TypePair{TokenType::return_, true};
    }
    else if (stringToCompare.Compare(L"endprocedure", 12)) {
        return TypePair{TokenType::endProcedure, false};
    }
    else if (stringToCompare.Compare(L"конецпроцедуры", 14)) {
        return TypePair{TokenType::endProcedure, false};
    }
    else if (stringToCompare.Compare(L"function", 8)) {
        return TypePair{TokenType::function, false};
    }
    else if (stringToCompare.Compare(L"функция", 7)) {
        return TypePair{TokenType::function, false};
    }
    else if (stringToCompare.Compare(L"endfunction", 11)) {
        return TypePair{TokenType::endFunction, false};
    }
    else if (stringToCompare.Compare(L"конецфункции", 12)) {
        return TypePair{TokenType::endFunction, false};
    }
    else if (stringToCompare.Compare(L"for", 3)) {
        return TypePair{TokenType::for_, false};
    }
    else if (stringToCompare.Compare(L"для", 3)) {
        return TypePair{TokenType::for_, false};
    }
    else if (stringToCompare.Compare(L"to", 2)) {
        return TypePair{TokenType::to, true};
    }
    else if (stringToCompare.Compare(L"по", 2)) {
        return TypePair{TokenType::to, true};
    }
    else if (stringToCompare.Compare(L"do", 2)) {
        return TypePair{TokenType::do_, false};
    }
    else if (stringToCompare.Compare(L"цикл", 4)) {
        return TypePair{TokenType::do_, false};
    }
    else if (stringToCompare.Compare(L"break", 5)) {
        return TypePair{TokenType::break_, false};
    }
    else if (stringToCompare.Compare(L"прервать", 8)) {
        return TypePair{TokenType::break_, false};
    }
    else if (stringToCompare.Compare(L"continue", 8)) {
        return TypePair{TokenType::continue_, false};
    }
    else if (stringToCompare.Compare(L"продолжить", 10)) {
        return TypePair{TokenType::continue_, false};
    }
    else if (stringToCompare.Compare(L"enddo", 5)) {
        return TypePair{TokenType::endDo, false};
    }
    else if (stringToCompare.Compare(L"конеццикла", 10)) {
        return TypePair{TokenType::endDo, false};
    }
    else if (stringToCompare.Compare(L"each", 4)) {
        return TypePair{TokenType::each, false};
    }
    else if (stringToCompare.Compare(L"каждого", 7)) {
        return TypePair{TokenType::each, false};
    }
    else if (stringToCompare.Compare(L"in", 2)) {
        return TypePair{TokenType::in, false};
    }
    else if (stringToCompare.Compare(L"из", 2)) {
        return TypePair{TokenType::in, false};
    }
    else if (stringToCompare.Compare(L"while", 5)) {
        return TypePair{TokenType::while_, true};
    }
    else if (stringToCompare.Compare(L"пока", 4)) {
        return TypePair{TokenType::while_, true};
    }
    else if (stringToCompare.Compare(L"try", 3)) {
        return TypePair{TokenType::try_, false};
    }
    else if (stringToCompare.Compare(L"попытка", 7)) {
        return TypePair{TokenType::try_, false};
    }
    else if (stringToCompare.Compare(L"except", 6)) {
        return TypePair{TokenType::except, false};
    }
    else if (stringToCompare.Compare(L"исключение", 10)) {
        return TypePair{TokenType::except, false};
    }
    else if (stringToCompare.Compare(L"raise", 5)) {
        return TypePair{TokenType::raise, true};
    }
    else if (stringToCompare.Compare(L"вызватьисключение", 17)) {
        return TypePair{TokenType::raise, true};
    }
    else if (stringToCompare.Compare(L"endtry", 6)) {
        return TypePair{TokenType::endTry, false};
    }
    else if (stringToCompare.Compare(L"конецпопытки", 12)) {
        return TypePair{TokenType::endTry, false};
    }
    else if (stringToCompare.Compare(L"goto", 4)) {
        return TypePair{TokenType::goto_, false};
    }
    else if (stringToCompare.Compare(L"перейти", 7)) {
        return TypePair{TokenType::goto_, false};
    }
    else if (stringToCompare.Compare(L"new", 3)) {
        return TypePair{TokenType::new_, false};
    }
    else if (stringToCompare.Compare(L"новый", 5)) {
        return TypePair{TokenType::new_, false};
    }
    else if (stringToCompare.Compare(L"execute", 7)) {
        return TypePair{TokenType::execute, true};
    }
    else if (stringToCompare.Compare(L"выполнить", 9)) {
        return TypePair{TokenType::execute, true};
    }
    else if (stringToCompare.Compare(L"async", 5)) {
        return TypePair{TokenType::async, false};
    }
    else if (stringToCompare.Compare(L"асинх", 5)) {
        return TypePair{TokenType::async, false};
    }
    else if (stringToCompare.Compare(L"await", 5)) {
        return TypePair{TokenType::await, true};
    }
    else if (stringToCompare.Compare(L"ждать", 5)) {
        return TypePair{TokenType::await, true};
    }
    else if (stringToCompare.Compare(L"addhandler", 10)) {
        return TypePair{TokenType::addHandler, true};
    }
    else if (stringToCompare.Compare(L"добавитьобработчик", 18)) {
        return TypePair{TokenType::addHandler, true};
    }
    else if (stringToCompare.Compare(L"removehandler", 13)) {
        return TypePair{TokenType::removeHandler, true};
    }
    else if (stringToCompare.Compare(L"удалитьобработчик", 17)) {
        return TypePair{TokenType::removeHandler, true};
    }
    else if (stringToCompare.Compare(L"null", 4)) {
        return TypePair{TokenType::null, false};
    }
    else if (stringToCompare.Compare(L"undefined", 9)) {
        return TypePair{TokenType::undefined, false};
    }
    else if (stringToCompare.Compare(L"неопределено", 12)) {
        return TypePair{TokenType::undefined, false};
    }
    else if (stringToCompare.Compare(L"false", 5)) {
        return TypePair{TokenType::false_, false};
    }
    else if (stringToCompare.Compare(L"ложь", 4)) {
        return TypePair{TokenType::false_, false};
    }
    else if (stringToCompare.Compare(L"true", 4)) {
        return TypePair{TokenType::true_, false};
    }
    else if (stringToCompare.Compare(L"истина", 6)) {
        return TypePair{TokenType::true_, false};
    }
    
    return TypePair{TokenType::identifier, false};
}

TokenStream::~TokenStream() {
}
