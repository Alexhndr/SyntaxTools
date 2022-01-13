#include "Tests.h"

TkStrPos::TkStrPos() {
}

TkStrPos::TkStrPos(const int chrPos_, const int tknPos_) :
    chrPos(chrPos_),
    tknPos(tknPos_) {
}

void LexerTests::Test() const {
    Lexer lexer;
    std::wstring inputString =
        L"// Комментарий 1\n"
        "// Comment 1\n"
        "    \n"
        "\t\t\t\t\n"
        "#If\n"
        "#Если\n"
        "#Then\n"
        "#Тогда\n"
        "#ElsIf\n"
        "#ИначеЕсли\n"
        "#Else\n"
        "#Иначе\n"
        "#EndIf\n"
        "#КонецЕсли\n"
        "#Region\n"
        "#Область\n"
        "#EndRegion\n"
        "#КонецОбласти\n"
        "#Client\n"
        "#Клиент\n"
        "#AtClient\n"
        "#НаКлиенте\n"
        "#AtServer\n"
        "#НаСервере\n"
        "#MobileAppClient\n"
        "#МобильноеПриложениеКлиент\n"
        "#MobileAppServer\n"
        "#МобильноеПриложениеСервер\n"
        "#ThickClientOrdinaryApplication\n"
        "#ТолстыйКлиентОбычноеПриложение\n"
        "#ThickClientManagedApplication\n"
        "#ТолстыйКлиентУправляемоеПриложение\n"
        "#Server\n"
        "#Сервер\n"
        "#ExternalConnection\n"
        "#ВнешнееСоединение\n"
        "#ThinClient\n"
        "#ТонкийКлиент\n"
        "#WebClient\n"
        "#ВебКлиент\n"
        "#And\n"
        "#И\n"
        "#Or\n"
        "#Или\n"
        "#Not\n"
        "#Не\n"
        "#Region_1\n"
        "#Область_1\n"
        "#(\n"
        "#)\n"
        "&AtClient\n"
        "&НаКлиенте\n"
        "&AtServer\n"
        "&НаСервере\n"
        "&AtServerNoContext\n"
        "&НаСервереБезКонтекста\n"
        "&AtClientAtServerNoContext\n"
        "&НаКлиентеНаСервереБезКонтекста\n"
        "&AtClientAtServer\n"
        "&НаКлиентеНаСервере\n"
        "&Before\n"
        "&Перед\n"
        "&After\n"
        "&После\n"
        "&Instead\n"
        "&Вместо\n"
        "&(\n"
        "&)\n"
        "&\"Procedure_1\"\n"
        "&\"Процедура_1\"\n"
        "If\n"
        "Если\n"
        "Then\n"
        "Тогда\n"
        "ElsIf\n"
        "ИначеЕсли\n"
        "Else\n"
        "Иначе\n"
        "EndIf\n"
        "КонецЕсли\n"
        "And\n"
        "И\n"
        "Or\n"
        "Или\n"
        "Not\n"
        "Не\n"
        "Var\n"
        "Перем\n"
        "Export\n"
        "Экспорт\n"
        "Procedure\n"
        "Процедура\n"
        "Val\n"
        "Знач\n"
        "Return\n"
        "Возврат\n"
        "EndProcedure\n"
        "КонецПроцедуры\n"
        "Function\n"
        "Функция\n"
        "EndFunction\n"
        "КонецФункции\n"
        "For\n"
        "Для\n"
        "To\n"
        "По\n"
        "Do\n"
        "Цикл\n"
        "Break\n"
        "Прервать\n"
        "Continue\n"
        "Продолжить\n"
        "EndDo\n"
        "КонецЦикла\n"
        "Each\n"
        "Каждого\n"
        "In\n"
        "Из\n"
        "While\n"
        "Пока\n"
        "Try\n"
        "Попытка\n"
        "Except\n"
        "Исключение\n"
        "Raise\n"
        "ВызватьИсключение\n"
        "EndTry\n"
        "КонецПопытки\n"
        "Goto\n"
        "Перейти\n"
        "New\n"
        "Новый\n"
        "Execute\n"
        "Выполнить\n"
        "Async\n"
        "Асинх\n"
        "Await\n"
        "Ждать\n"
        "AddHandler\n"
        "ДобавитьОбработчик\n"
        "RemoveHandler\n"
        "УдалитьОбработчик\n"
        "Null\n"
        "Undefined\n"
        "Неопределено\n"
        "False\n"
        "Ложь\n"
        "True\n"
        "Истина\n"
        "Identifier_1\n"
        "Идентификатор_1\n"
        "= -10\n"
        "= +10.00\n"
        "-10\n"
        "+10.00\n"
        "- 10\n"
        "+ 10.00\n"
        "10\n"
        "10.00\n"
        "\'00010101\'\n"
        "\'20000101000000\'\n"
        "\"String\"\n"
        "\"Строка\"\n"
        "\"Beginning of string\n"
        "\"Начало строки\n"
        "|Continue of string\n"
        "|Продолжение строки\n"
        "|End of string\"\n"
        "|Конец строки\"\n"
        "[\n"
        "]\n"
        "(\n"
        ")\n"
        ".\n"
        ",\n"
        ";\n"
        "+\n"
        "-\n"
        "*\n"
        "/\n"
        "%\n"
        "?\n"
        ":\n"
        "=\n"
        "<>\n"
        "<=\n"
        "<\n"
        ">=\n"
        ">\n"
        "~";
    
    TokenStream tokenStream;
    
    if (!lexer.FillTokenStream(inputString, tokenStream)) {
        QFAIL("Can't fill tokens");
    }
    
    TkStrPos tkStrPos;
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::comment, 16);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::comment, 12);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::whitespace, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::whitespace, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termIf, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termIf, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termThen, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termThen, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termElsIf, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termElsIf, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termElse, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termElse, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termEndIf, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termEndIf, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termRegion, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termRegion, 7);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termEndRegion, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termEndRegion, 12);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termClient, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termClient, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termAtClient, 8);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termAtClient, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termAtServer, 8);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termAtServer, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termMobileAppClient, 15);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termMobileAppClient, 25);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termMobileAppServer, 15);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termMobileAppServer, 25);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termThickClientOrdinaryApplication, 30);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termThickClientOrdinaryApplication, 30);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termThickClientManagedApplication, 29);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termThickClientManagedApplication, 34);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termServer, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termServer, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termExternalConnection, 18);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termExternalConnection, 17);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termThinClient, 10);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termThinClient, 12);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termWebClient, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termWebClient, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termAnd, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termAnd, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termOr, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termOr, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNot, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNot, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termIdentifier, 8);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termIdentifier, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termLeftParenthesis, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termNumberSign, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::termRightParenthesis, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAtClient, 8);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAtClient, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAtServer, 8);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAtServer, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAtServerNoContext, 17);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAtServerNoContext, 21);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAtClientAtServerNoContext, 25);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAtClientAtServerNoContext, 30);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAtClientAtServer, 16);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAtClientAtServer, 18);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveBefore, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveBefore, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAfter, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAfter, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveInstead, 7);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveInstead, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveLeftParenthesis, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveRightParenthesis, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveString, 13);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveAmpersand, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::directiveString, 13);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::if_, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::if_, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::then, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::then, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::elsIf, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::elsIf, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::else_, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::else_, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::endIf, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::endIf, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::and_, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::and_, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::or_, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::or_, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::not_, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::not_, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::var, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::var, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::export_, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::export_, 7);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::procedure, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::procedure, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::val, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::val, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::return_, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::return_, 7);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::endProcedure, 12);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::endProcedure, 14);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::function, 8);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::function, 7);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::endFunction, 11);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::endFunction, 12);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::for_, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::for_, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::to, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::to, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::do_, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::do_, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::break_, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::break_, 8);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::continue_, 8);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::continue_, 10);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::endDo, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::endDo, 10);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::each, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::each, 7);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::in, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::in, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::while_, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::while_, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::try_, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::try_, 7);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::except, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::except, 10);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::raise, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::raise, 17);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::endTry, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::endTry, 12);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::goto_, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::goto_, 7);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::new_, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::new_, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::execute, 7);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::execute, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::async, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::async, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::await, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::await, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::addHandler, 10);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::addHandler, 18);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::removeHandler, 13);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::removeHandler, 17);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::null, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::undefined, 9);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::undefined, 12);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::false_, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::false_, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::true_, 4);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::true_, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::identifier, 12);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::identifier, 15);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::equals, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::whitespace, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::signedFloat, 3);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::equals, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::whitespace, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::signedFloat, 6);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::minus, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::float_, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::plus, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::float_, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::minus, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::whitespace, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::float_, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::plus, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::whitespace, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::float_, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::float_, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::float_, 5);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::date, 10);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::date, 16);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::string, 8);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::string, 8);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::stringBeginning, 20);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::stringBeginning, 14);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::stringContinue, 19);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::stringContinue, 19);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::stringEnding, 15);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::stringEnding, 14);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::leftSquareBracket, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::rightSquareBracket, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::leftParenthesis, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::rightParenthesis, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::fullStop, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::comma, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::semicolon, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::plus, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::minus, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::asterisk, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::solidus, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::percent, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::questionMark, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::colon, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::equals, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::notEquals, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::lessOrEquals, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::less, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::greaterOrEquals, 2);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::greater, 1);
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::newline, 1);
    
    tkStrPos = ProcessToken(tokenStream, tkStrPos, TokenType::tilde, 1);
}

LexerTests::~LexerTests() {
}

TkStrPos LexerTests::MoveToNextToken(const TkStrPos& tkStrPos, const int numOfChrs) const {
    TkStrPos newTkStrPos(tkStrPos.chrPos + numOfChrs, tkStrPos.tknPos + 1);
    return newTkStrPos;
}

TkStrPos LexerTests::ProcessToken(const TokenStream& tokenStream, const TkStrPos& tkStrPos, const TokenType type,
    const int numOfChrs) const {
    const Token& token = tokenStream.tokens[tkStrPos.tknPos];
    VerifyToken(token, tkStrPos, type, numOfChrs);
    return MoveToNextToken(tkStrPos, token.numOfChrs);
}

void LexerTests::VerifyToken(const Token& token, const TkStrPos& tkStrPos, const TokenType type,
    const int numOfChrs) const {
    QVERIFY(token.type == type);
    QVERIFY(token.chrPos == tkStrPos.chrPos);
    QVERIFY(token.numOfChrs == numOfChrs);
    QVERIFY(token.tknPos == tkStrPos.tknPos);
    QVERIFY(token.numOfTkns == 1);
}
