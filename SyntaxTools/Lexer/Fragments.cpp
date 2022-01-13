#include "Fragments.h"

const LhEndHelper endHelper;

bool LfNewline::CheckStream(LStream& stream) const {
    LhFromChar fromCharR('\r');
    LhOnceOrNot onceOrNot(&fromCharR);
    LhFromChar fromCharN('\n');
    LhAddition addition(&onceOrNot, &fromCharN, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    stream.Set(newStream);
    return true;
}

bool LfNewlineOfString::CheckStream(LStream& stream) const {
    LhFromChar fromCharR('\r');
    LhOnceOrNot onceOrNot(&fromCharR);
    LhFromChar fromCharN('\n');
    LhAddition addition(&onceOrNot, &fromCharN, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!addition.CheckStream(newStream)) {
        return false;
    }
    
    return true;
}

bool LfLCapitalLetter::CheckStream(LStream& stream) const {
    LhAnyCharOfInterval anyCharOfInterval('A', 'Z');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!anyCharOfInterval.CheckStream(newStream)) {
        return false;
    }
    
    stream.Set(newStream);
    return true;
}

bool LfLSmallLetter::CheckStream(LStream& stream) const {
    LhAnyCharOfInterval anyCharOfInterval('a', 'z');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!anyCharOfInterval.CheckStream(newStream)) {
        return false;
    }
    
    stream.Set(newStream);
    return true;
}

bool LfCCapitalLetter::CheckStream(LStream& stream) const {
    LhAnyCharOfInterval anyCharOfInterval(wchar_t(0x0410), wchar_t(0x042f));
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!anyCharOfInterval.CheckStream(newStream)) {
        return false;
    }
    
    stream.Set(newStream);
    return true;
}

bool LfCSmallLetter::CheckStream(LStream& stream) const {
    LhAnyCharOfInterval anyCharOfInterval(wchar_t(0x0430), wchar_t(0x044f));
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!anyCharOfInterval.CheckStream(newStream)) {
        return false;
    }
    
    stream.Set(newStream);
    return true;
}

bool LfLetter::CheckStream(LStream& stream) const {
    LfLCapitalLetter lCapitalLetter;
    LfLSmallLetter lSmallLetter;
    LfCCapitalLetter cCapitalLetter;
    LfCSmallLetter cSmallLetter;
    LhAnyOf anyOf(&lCapitalLetter, &lSmallLetter, &cCapitalLetter, &cSmallLetter, &endHelper);
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!anyOf.CheckStream(newStream)) {
        return false;
    }
    
    stream.Set(newStream);
    return true;
}

bool LfDigit::CheckStream(LStream& stream) const {
    LhAnyCharOfInterval anyCharOfInterval('0', '9');
    
    LStream newStream;
    newStream.Set(stream);
    
    if (!anyCharOfInterval.CheckStream(newStream)) {
        return false;
    }
    
    stream.Set(newStream);
    return true;
}
