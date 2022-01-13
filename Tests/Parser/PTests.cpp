#include "Tests.h"

ParserTests::~ParserTests() {
}

void ParserTests::TestAst() const {
    const std::wstring inputString =
        L"#Region RegionA\n"
        "\n"
        "#EndRegion";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    VerifyAstNode(ast, AstNodeType::root, nullptr, -1, 0, 27, 0, 8);
}

void ParserTests::TestBlock() const {
    const std::wstring inputString =
        L"#Region RegionA\n"
        "\n"
        "#EndRegion\n"
        "\n"
        "#Region RegionB\n"
        "\n"
        "#EndRegion";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const Block* block = GetBlock(ast);
    
    if (block == nullptr) {
        return;
    }
    
    VerifyAstNode(*block, AstNodeType::block, &ast, -1, 0, 56, 0, 18);
    QVERIFY(block->blockElements.size() == 2);
}

void ParserTests::TestBlockElement() const {
    TestBlockElementPreprocessorRegionBlock();
    TestBlockElementPreprocessorIfBlock();
    TestBlockElementVariablesBlock();
    TestBlockElementFunctionsBlock();
    TestBlockElementOperationsBlock();
}

void ParserTests::TestBlockElementPreprocessorRegionBlock() const {
    const std::wstring inputString =
        L"#Region RegionA\n"
        "\n"
        "#EndRegion\n"
        "\n"
        "#Region RegionB\n"
        "\n"
        "#EndRegion";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const Block* block = GetBlock(ast);
    
    if (block == nullptr) {
        return;
    }
    
    const BlockElement* blockElement = GetBlockElement(ast, 1);
    
    if (blockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*blockElement, AstNodeType::blockElement, block, 1, 29, 27, 10, 8);
    QVERIFY(blockElement->preprocessorRegionBlock.get() != nullptr);
    QVERIFY(blockElement->preprocessorIfBlock.get() == nullptr);
    QVERIFY(blockElement->variablesBlock.get() == nullptr);
    QVERIFY(blockElement->functionsBlock.get() == nullptr);
    QVERIFY(blockElement->operationsBlock.get() == nullptr);
}

void ParserTests::TestBlockElementPreprocessorIfBlock() const {
    const std::wstring inputString =
        L"#Region RegionA\n"
        "\n"
        "#EndRegion\n"
        "\n"
        "#If Server Then\n"
        "\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const Block* block = GetBlock(ast);
    
    if (block == nullptr) {
        return;
    }
    
    const BlockElement* blockElement = GetBlockElement(ast, 1);
    
    if (blockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*blockElement, AstNodeType::blockElement, block, 1, 29, 23, 10, 10);
    QVERIFY(blockElement->preprocessorRegionBlock.get() == nullptr);
    QVERIFY(blockElement->preprocessorIfBlock.get() != nullptr);
    QVERIFY(blockElement->variablesBlock.get() == nullptr);
    QVERIFY(blockElement->functionsBlock.get() == nullptr);
    QVERIFY(blockElement->operationsBlock.get() == nullptr);
}

void ParserTests::TestBlockElementVariablesBlock() const {
    const std::wstring inputString =
        L"#Region RegionA\n"
        "\n"
        "#EndRegion\n"
        "\n"
        "Var VariableA;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const Block* block = GetBlock(ast);
    
    if (block == nullptr) {
        return;
    }
    
    const BlockElement* blockElement = GetBlockElement(ast, 1);
    
    if (blockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*blockElement, AstNodeType::blockElement, block, 1, 29, 14, 10, 4);
    QVERIFY(blockElement->preprocessorRegionBlock.get() == nullptr);
    QVERIFY(blockElement->preprocessorIfBlock.get() == nullptr);
    QVERIFY(blockElement->variablesBlock.get() != nullptr);
    QVERIFY(blockElement->functionsBlock.get() == nullptr);
    QVERIFY(blockElement->operationsBlock.get() == nullptr);
}

void ParserTests::TestBlockElementFunctionsBlock() const {
    const std::wstring inputString =
        L"#Region RegionA\n"
        "\n"
        "#EndRegion\n"
        "\n"
        "Procedure ProcedureA()\n"
        "\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const Block* block = GetBlock(ast);
    
    if (block == nullptr) {
        return;
    }
    
    const BlockElement* blockElement = GetBlockElement(ast, 1);
    
    if (blockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*blockElement, AstNodeType::blockElement, block, 1, 29, 36, 10, 8);
    QVERIFY(blockElement->preprocessorRegionBlock.get() == nullptr);
    QVERIFY(blockElement->preprocessorIfBlock.get() == nullptr);
    QVERIFY(blockElement->variablesBlock.get() == nullptr);
    QVERIFY(blockElement->functionsBlock.get() != nullptr);
    QVERIFY(blockElement->operationsBlock.get() == nullptr);
}

void ParserTests::TestBlockElementOperationsBlock() const {
    const std::wstring inputString =
        L"#Region RegionA\n"
        "\n"
        "#EndRegion\n"
        "\n"
        "VariableA = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const Block* block = GetBlock(ast);
    
    if (block == nullptr) {
        return;
    }
    
    const BlockElement* blockElement = GetBlockElement(ast, 1);
    
    if (blockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*blockElement, AstNodeType::blockElement, block, 1, 29, 14, 10, 6);
    QVERIFY(blockElement->preprocessorRegionBlock.get() == nullptr);
    QVERIFY(blockElement->preprocessorIfBlock.get() == nullptr);
    QVERIFY(blockElement->variablesBlock.get() == nullptr);
    QVERIFY(blockElement->functionsBlock.get() == nullptr);
    QVERIFY(blockElement->operationsBlock.get() != nullptr);
}

void ParserTests::TestPreprocessorRegionBlock() const {
    const std::wstring inputString =
        L"#Region RegionA\n"
        "\t\n"
        "\tVariableA = 0;\n"
        "\t\n"
        "#EndRegion";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const BlockElement* blockElement = GetBlockElement(ast, 0);
    
    if (blockElement == nullptr) {
        return;
    }
    
    const PreprocessorRegionBlock* preprocessorRegionBlock = GetPreprocessorRegionBlock(ast);
    
    if (preprocessorRegionBlock == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorRegionBlock, AstNodeType::preprocessorRegionBlock, blockElement, -1, 0, 46, 0, 19);
    VerifyToken(preprocessorRegionBlock->tkTermNumberSignRegion, TokenType::termNumberSign, preprocessorRegionBlock, 0,
        1, 0);
    VerifyToken(preprocessorRegionBlock->tkTermRegion, TokenType::termRegion, preprocessorRegionBlock, 1, 6, 1);
    QVERIFY(preprocessorRegionBlock->block.get() != nullptr);
    VerifyToken(preprocessorRegionBlock->tkTermIdentifier, TokenType::termIdentifier, preprocessorRegionBlock, 8, 7, 3);
    VerifyToken(preprocessorRegionBlock->tkTermNumberSignEndRegion, TokenType::termNumberSign,
        preprocessorRegionBlock, 36, 1, 17);
    VerifyToken(preprocessorRegionBlock->tkTermEndRegion, TokenType::termEndRegion, preprocessorRegionBlock, 37, 9, 18);
}

void ParserTests::TestPreprocessorIfBlock() const {
    const std::wstring inputString =
        L"#If Server Then\n"
        "\t\n"
        "\tVariableA = 0;\n"
        "\t\n"
        "#ElsIf ExternalConnection Then\n"
        "\t\n"
        "#ElsIf Client Then\n"
        "\t\n"
        "#Else\n"
        "\t\n"
        "\tVariableB = 0;\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const BlockElement* blockElement = GetBlockElement(ast, 0);
    
    if (blockElement == nullptr) {
        return;
    }
    
    const PreprocessorIfBlock* preprocessorIfBlock = GetPreprocessorIfBlock(ast);
    
    if (preprocessorIfBlock == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorIfBlock, AstNodeType::preprocessorIfBlock, blockElement, -1, 0, 122, 0, 54);
    VerifyToken(preprocessorIfBlock->tkTermNumberSignIf, TokenType::termNumberSign, preprocessorIfBlock, 0, 1, 0);
    VerifyToken(preprocessorIfBlock->tkTermIf, TokenType::termIf, preprocessorIfBlock, 1, 2, 1);
    QVERIFY(preprocessorIfBlock->preprocessorExpression.get() != nullptr);
    VerifyToken(preprocessorIfBlock->tkTermThen, TokenType::termThen, preprocessorIfBlock, 11, 4, 5);
    QVERIFY(preprocessorIfBlock->blockIf.get() != nullptr);
    QVERIFY(preprocessorIfBlock->preprocessorIfBlockElements.size() == 2);
    VerifyToken(preprocessorIfBlock->tkTermNumberSignElse, TokenType::termNumberSign, preprocessorIfBlock, 90, 1, 37);
    VerifyToken(preprocessorIfBlock->tkTermElse, TokenType::termElse, preprocessorIfBlock, 91, 4, 38);
    QVERIFY(preprocessorIfBlock->blockElse.get() != nullptr);
    VerifyToken(preprocessorIfBlock->tkTermNumberSignEndIf, TokenType::termNumberSign, preprocessorIfBlock, 116, 1, 52);
    VerifyToken(preprocessorIfBlock->tkTermEndIf, TokenType::termEndIf, preprocessorIfBlock, 117, 5, 53);
}

void ParserTests::TestPreprocessorIfBlockElement() const {
    const std::wstring inputString =
        L"#If Server Then\n"
        "\t\n"
        "#ElsIf ExternalConnection Then\n"
        "\t\n"
        "#ElsIf Client Then\n"
        "\t\n"
        "\tVariableA = 0;\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorIfBlock* preprocessorIfBlock = GetPreprocessorIfBlock(ast);
    
    if (preprocessorIfBlock == nullptr) {
        return;
    }
    
    const PreprocessorIfBlockElement* preprocessorIfBlockElement = GetPreprocessorIfBlockElement(ast, 1);
    
    if (preprocessorIfBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorIfBlockElement, AstNodeType::preprocessorIfBlockElement, preprocessorIfBlock, 1, 51, 36,
        18, 16);
    VerifyToken(preprocessorIfBlockElement->tkTermNumberSign, TokenType::termNumberSign, preprocessorIfBlockElement, 51,
        1, 18);
    VerifyToken(preprocessorIfBlockElement->tkTermElsIf, TokenType::termElsIf, preprocessorIfBlockElement, 52, 5, 19);
    QVERIFY(preprocessorIfBlockElement->preprocessorExpression.get() != nullptr);
    VerifyToken(preprocessorIfBlockElement->tkTermThen, TokenType::termThen, preprocessorIfBlockElement, 65, 4, 23);
    QVERIFY(preprocessorIfBlockElement->block.get() != nullptr);
}

void ParserTests::TestPreprocessorExpression() const {
    const std::wstring inputString =
        L"#If Server Or ExternalConnection Or Client Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorIfBlock* preprocessorIfBlock = GetPreprocessorIfBlock(ast);
    
    if (preprocessorIfBlock == nullptr) {
        return;
    }
    
    const PreprocessorExpression* preprocessorExpression = GetPreprocessorExpression(ast);
    
    if (preprocessorExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorExpression, AstNodeType::preprocessorExpression, preprocessorIfBlock, -1, 4, 38, 3, 9);
    QVERIFY(preprocessorExpression->preprocessorAndExpression.get() != nullptr);
    QVERIFY(preprocessorExpression->preprocessorExpressionElements.size() == 2);
}

void ParserTests::TestPreprocessorExpressionElement() const {
    const std::wstring inputString =
        L"#If Server Or ExternalConnection Or Client Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorExpression* preprocessorExpression = GetPreprocessorExpression(ast);
    
    if (preprocessorExpression == nullptr) {
        return;
    }
    
    const PreprocessorExpressionElement* preprocessorExpressionElement = GetPreprocessorExpressionElement(ast, 1);
    
    if (preprocessorExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorExpressionElement, AstNodeType::preprocessorExpressionElement, preprocessorExpression, 1,
        33, 9, 9, 3);
    VerifyToken(preprocessorExpressionElement->tkTermOr, TokenType::termOr, preprocessorExpressionElement, 33, 2, 9);
    QVERIFY(preprocessorExpressionElement->preprocessorAndExpression != nullptr);
}

void ParserTests::TestPreprocessorPrimeExpression() const {
    TestPreprocessorPrimeExpressionValue();
    TestPreprocessorPrimeExpressionExpressionInParenthesis();
}

void ParserTests::TestPreprocessorPrimeExpressionValue() const {
    const std::wstring inputString =
        L"#If Server Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorNotExpression* preprocessorNotExpression = GetPreprocessorNotExpression(ast);
    
    if (preprocessorNotExpression == nullptr) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorPrimeExpression, AstNodeType::preprocessorPrimeExpression, preprocessorNotExpression, -1,
        4, 6, 3, 1);
    QVERIFY(preprocessorPrimeExpression->preprocessorValue.get() != nullptr);
    QVERIFY(preprocessorPrimeExpression->tkTermLeftParenthesis.IsEmpty());
    QVERIFY(preprocessorPrimeExpression->preprocessorExpression.get() == nullptr);
    QVERIFY(preprocessorPrimeExpression->tkTermRightParenthesis.IsEmpty());
}

void ParserTests::TestPreprocessorPrimeExpressionExpressionInParenthesis() const {
    const std::wstring inputString =
        L"#If (Server) Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorNotExpression* preprocessorNotExpression = GetPreprocessorNotExpression(ast);
    
    if (preprocessorNotExpression == nullptr) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorPrimeExpression, AstNodeType::preprocessorPrimeExpression, preprocessorNotExpression, -1,
        4, 8, 3, 3);
    QVERIFY(preprocessorPrimeExpression->preprocessorValue.get() == nullptr);
    VerifyToken(preprocessorPrimeExpression->tkTermLeftParenthesis, TokenType::termLeftParenthesis,
        preprocessorPrimeExpression, 4, 1, 3);
    QVERIFY(preprocessorPrimeExpression->preprocessorExpression.get() != nullptr);
    VerifyToken(preprocessorPrimeExpression->tkTermRightParenthesis, TokenType::termRightParenthesis,
        preprocessorPrimeExpression, 11, 1, 5);
}

void ParserTests::TestPreprocessorValue() const {
    TestPreprocessorValueClient();
    TestPreprocessorValueAtClient();
    TestPreprocessorValueAtServer();
    TestPreprocessorValueMobileAppClient();
    TestPreprocessorValueMobileAppServer();
    TestPreprocessorValueThickClientOrdinaryApplication();
    TestPreprocessorValueThickClientManagedApplication();
    TestPreprocessorValueServer();
    TestPreprocessorValueExternalConnection();
    TestPreprocessorValueThinClient();
    TestPreprocessorValueWebClient();
}

void ParserTests::TestPreprocessorValueClient() const {
    const std::wstring inputString =
        L"#If Client Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 6, 3, 1);
    QVERIFY(preprocessorValue->isTermClient);
    QVERIFY(!preprocessorValue->isTermAtClient);
    QVERIFY(!preprocessorValue->isTermAtServer);
    QVERIFY(!preprocessorValue->isTermMobileAppClient);
    QVERIFY(!preprocessorValue->isTermMobileAppServer);
    QVERIFY(!preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(!preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(!preprocessorValue->isTermServer);
    QVERIFY(!preprocessorValue->isTermExternalConnection);
    QVERIFY(!preprocessorValue->isTermThinClient);
    QVERIFY(!preprocessorValue->isTermWebClient);
    
    VerifyToken(preprocessorValue->tkTermClient, TokenType::termClient, preprocessorValue, 4, 6, 3);
    QVERIFY(preprocessorValue->tkTermAtClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientManagedApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermExternalConnection.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThinClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermWebClient.IsEmpty());
}

void ParserTests::TestPreprocessorValueAtClient() const {
    const std::wstring inputString =
        L"#If AtClient Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 8, 3, 1);
    QVERIFY(!preprocessorValue->isTermClient);
    QVERIFY(preprocessorValue->isTermAtClient);
    QVERIFY(!preprocessorValue->isTermAtServer);
    QVERIFY(!preprocessorValue->isTermMobileAppClient);
    QVERIFY(!preprocessorValue->isTermMobileAppServer);
    QVERIFY(!preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(!preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(!preprocessorValue->isTermServer);
    QVERIFY(!preprocessorValue->isTermExternalConnection);
    QVERIFY(!preprocessorValue->isTermThinClient);
    QVERIFY(!preprocessorValue->isTermWebClient);
    
    QVERIFY(preprocessorValue->tkTermClient.IsEmpty());
    VerifyToken(preprocessorValue->tkTermAtClient, TokenType::termAtClient, preprocessorValue, 4, 8, 3);
    QVERIFY(preprocessorValue->tkTermAtServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientManagedApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermExternalConnection.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThinClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermWebClient.IsEmpty());
}

void ParserTests::TestPreprocessorValueAtServer() const {
    const std::wstring inputString =
        L"#If AtServer Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 8, 3, 1);
    QVERIFY(!preprocessorValue->isTermClient);
    QVERIFY(!preprocessorValue->isTermAtClient);
    QVERIFY(preprocessorValue->isTermAtServer);
    QVERIFY(!preprocessorValue->isTermMobileAppClient);
    QVERIFY(!preprocessorValue->isTermMobileAppServer);
    QVERIFY(!preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(!preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(!preprocessorValue->isTermServer);
    QVERIFY(!preprocessorValue->isTermExternalConnection);
    QVERIFY(!preprocessorValue->isTermThinClient);
    QVERIFY(!preprocessorValue->isTermWebClient);
    
    QVERIFY(preprocessorValue->tkTermClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtClient.IsEmpty());
    VerifyToken(preprocessorValue->tkTermAtServer, TokenType::termAtServer, preprocessorValue, 4, 8, 3);
    QVERIFY(preprocessorValue->tkTermMobileAppClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientManagedApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermExternalConnection.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThinClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermWebClient.IsEmpty());
}

void ParserTests::TestPreprocessorValueMobileAppClient() const {
    const std::wstring inputString =
        L"#If MobileAppClient Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 15, 3, 1);
    QVERIFY(!preprocessorValue->isTermClient);
    QVERIFY(!preprocessorValue->isTermAtClient);
    QVERIFY(!preprocessorValue->isTermAtServer);
    QVERIFY(preprocessorValue->isTermMobileAppClient);
    QVERIFY(!preprocessorValue->isTermMobileAppServer);
    QVERIFY(!preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(!preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(!preprocessorValue->isTermServer);
    QVERIFY(!preprocessorValue->isTermExternalConnection);
    QVERIFY(!preprocessorValue->isTermThinClient);
    QVERIFY(!preprocessorValue->isTermWebClient);
    
    QVERIFY(preprocessorValue->tkTermClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtServer.IsEmpty());
    VerifyToken(preprocessorValue->tkTermMobileAppClient, TokenType::termMobileAppClient, preprocessorValue, 4, 15, 3);
    QVERIFY(preprocessorValue->tkTermMobileAppServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientManagedApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermExternalConnection.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThinClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermWebClient.IsEmpty());
}

void ParserTests::TestPreprocessorValueMobileAppServer() const {
    const std::wstring inputString =
        L"#If MobileAppServer Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 15, 3, 1);
    QVERIFY(!preprocessorValue->isTermClient);
    QVERIFY(!preprocessorValue->isTermAtClient);
    QVERIFY(!preprocessorValue->isTermAtServer);
    QVERIFY(!preprocessorValue->isTermMobileAppClient);
    QVERIFY(preprocessorValue->isTermMobileAppServer);
    QVERIFY(!preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(!preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(!preprocessorValue->isTermServer);
    QVERIFY(!preprocessorValue->isTermExternalConnection);
    QVERIFY(!preprocessorValue->isTermThinClient);
    QVERIFY(!preprocessorValue->isTermWebClient);
    
    QVERIFY(preprocessorValue->tkTermClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppClient.IsEmpty());
    VerifyToken(preprocessorValue->tkTermMobileAppServer, TokenType::termMobileAppServer, preprocessorValue, 4, 15, 3);
    QVERIFY(preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientManagedApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermExternalConnection.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThinClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermWebClient.IsEmpty());
}

void ParserTests::TestPreprocessorValueThickClientOrdinaryApplication() const {
    const std::wstring inputString =
        L"#If ThickClientOrdinaryApplication Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 30, 3, 1);
    QVERIFY(!preprocessorValue->isTermClient);
    QVERIFY(!preprocessorValue->isTermAtClient);
    QVERIFY(!preprocessorValue->isTermAtServer);
    QVERIFY(!preprocessorValue->isTermMobileAppClient);
    QVERIFY(!preprocessorValue->isTermMobileAppServer);
    QVERIFY(preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(!preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(!preprocessorValue->isTermServer);
    QVERIFY(!preprocessorValue->isTermExternalConnection);
    QVERIFY(!preprocessorValue->isTermThinClient);
    QVERIFY(!preprocessorValue->isTermWebClient);
    
    QVERIFY(preprocessorValue->tkTermClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppServer.IsEmpty());
    VerifyToken(preprocessorValue->tkTermThickClientOrdinaryApplication, TokenType::termThickClientOrdinaryApplication,
        preprocessorValue, 4, 30, 3);
    QVERIFY(preprocessorValue->tkTermThickClientManagedApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermExternalConnection.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThinClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermWebClient.IsEmpty());
}

void ParserTests::TestPreprocessorValueThickClientManagedApplication() const {
    const std::wstring inputString =
        L"#If ThickClientManagedApplication Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 29, 3, 1);
    QVERIFY(!preprocessorValue->isTermClient);
    QVERIFY(!preprocessorValue->isTermAtClient);
    QVERIFY(!preprocessorValue->isTermAtServer);
    QVERIFY(!preprocessorValue->isTermMobileAppClient);
    QVERIFY(!preprocessorValue->isTermMobileAppServer);
    QVERIFY(!preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(!preprocessorValue->isTermServer);
    QVERIFY(!preprocessorValue->isTermExternalConnection);
    QVERIFY(!preprocessorValue->isTermThinClient);
    QVERIFY(!preprocessorValue->isTermWebClient);
    
    QVERIFY(preprocessorValue->tkTermClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty());
    VerifyToken(preprocessorValue->tkTermThickClientManagedApplication, TokenType::termThickClientManagedApplication,
        preprocessorValue, 4, 29, 3);
    QVERIFY(preprocessorValue->tkTermServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermExternalConnection.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThinClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermWebClient.IsEmpty());
}

void ParserTests::TestPreprocessorValueServer() const {
    const std::wstring inputString =
        L"#If Server Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 6, 3, 1);
    QVERIFY(!preprocessorValue->isTermClient);
    QVERIFY(!preprocessorValue->isTermAtClient);
    QVERIFY(!preprocessorValue->isTermAtServer);
    QVERIFY(!preprocessorValue->isTermMobileAppClient);
    QVERIFY(!preprocessorValue->isTermMobileAppServer);
    QVERIFY(!preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(!preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(preprocessorValue->isTermServer);
    QVERIFY(!preprocessorValue->isTermExternalConnection);
    QVERIFY(!preprocessorValue->isTermThinClient);
    QVERIFY(!preprocessorValue->isTermWebClient);
    
    QVERIFY(preprocessorValue->tkTermClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientManagedApplication.IsEmpty());
    VerifyToken(preprocessorValue->tkTermServer, TokenType::termServer, preprocessorValue, 4, 6, 3);
    QVERIFY(preprocessorValue->tkTermExternalConnection.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThinClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermWebClient.IsEmpty());
}

void ParserTests::TestPreprocessorValueExternalConnection() const {
    const std::wstring inputString =
        L"#If ExternalConnection Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 18, 3, 1);
    QVERIFY(!preprocessorValue->isTermClient);
    QVERIFY(!preprocessorValue->isTermAtClient);
    QVERIFY(!preprocessorValue->isTermAtServer);
    QVERIFY(!preprocessorValue->isTermMobileAppClient);
    QVERIFY(!preprocessorValue->isTermMobileAppServer);
    QVERIFY(!preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(!preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(!preprocessorValue->isTermServer);
    QVERIFY(preprocessorValue->isTermExternalConnection);
    QVERIFY(!preprocessorValue->isTermThinClient);
    QVERIFY(!preprocessorValue->isTermWebClient);
    
    QVERIFY(preprocessorValue->tkTermClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientManagedApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermServer.IsEmpty());
    VerifyToken(preprocessorValue->tkTermExternalConnection, TokenType::termExternalConnection, preprocessorValue, 4,
        18, 3);
    QVERIFY(preprocessorValue->tkTermThinClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermWebClient.IsEmpty());
}

void ParserTests::TestPreprocessorValueThinClient() const {
    const std::wstring inputString =
        L"#If ThinClient Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 10, 3, 1);
    QVERIFY(!preprocessorValue->isTermClient);
    QVERIFY(!preprocessorValue->isTermAtClient);
    QVERIFY(!preprocessorValue->isTermAtServer);
    QVERIFY(!preprocessorValue->isTermMobileAppClient);
    QVERIFY(!preprocessorValue->isTermMobileAppServer);
    QVERIFY(!preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(!preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(!preprocessorValue->isTermServer);
    QVERIFY(!preprocessorValue->isTermExternalConnection);
    QVERIFY(preprocessorValue->isTermThinClient);
    QVERIFY(!preprocessorValue->isTermWebClient);
    
    QVERIFY(preprocessorValue->tkTermClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientManagedApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermExternalConnection.IsEmpty());
    VerifyToken(preprocessorValue->tkTermThinClient, TokenType::termThinClient, preprocessorValue, 4, 10, 3);
    QVERIFY(preprocessorValue->tkTermWebClient.IsEmpty());
}

void ParserTests::TestPreprocessorValueWebClient() const {
    const std::wstring inputString =
        L"#If WebClient Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return;
    }
    
    const PreprocessorValue* preprocessorValue = GetPreprocessorValue(ast);
    
    if (preprocessorValue == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorValue, AstNodeType::preprocessorValue, preprocessorPrimeExpression, -1, 4, 9, 3, 1);
    QVERIFY(!preprocessorValue->isTermClient);
    QVERIFY(!preprocessorValue->isTermAtClient);
    QVERIFY(!preprocessorValue->isTermAtServer);
    QVERIFY(!preprocessorValue->isTermMobileAppClient);
    QVERIFY(!preprocessorValue->isTermMobileAppServer);
    QVERIFY(!preprocessorValue->isTermThickClientOrdinaryApplication);
    QVERIFY(!preprocessorValue->isTermThickClientManagedApplication);
    QVERIFY(!preprocessorValue->isTermServer);
    QVERIFY(!preprocessorValue->isTermExternalConnection);
    QVERIFY(!preprocessorValue->isTermThinClient);
    QVERIFY(preprocessorValue->isTermWebClient);
    
    QVERIFY(preprocessorValue->tkTermClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermAtServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppClient.IsEmpty());
    QVERIFY(preprocessorValue->tkTermMobileAppServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThickClientManagedApplication.IsEmpty());
    QVERIFY(preprocessorValue->tkTermServer.IsEmpty());
    QVERIFY(preprocessorValue->tkTermExternalConnection.IsEmpty());
    QVERIFY(preprocessorValue->tkTermThinClient.IsEmpty());
    VerifyToken(preprocessorValue->tkTermWebClient, TokenType::termWebClient, preprocessorValue, 4, 9, 3);
}

void ParserTests::TestPreprocessorAndExpression() const {
    const std::wstring inputString =
        L"#If Server And ExternalConnection And Client Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorExpression* preprocessorExpression = GetPreprocessorExpression(ast);
    
    if (preprocessorExpression == nullptr) {
        return;
    }
    
    const PreprocessorAndExpression* preprocessorAndExpression = GetPreprocessorAndExpression(ast);
    
    if (preprocessorAndExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorAndExpression, AstNodeType::preprocessorAndExpression, preprocessorExpression, -1, 4, 40,
        3, 9);
    QVERIFY(preprocessorAndExpression->preprocessorNotExpression.get() != nullptr);
    QVERIFY(preprocessorAndExpression->preprocessorAndExpressionElements.size() == 2);
}

void ParserTests::TestPreprocessorAndExpressionElement() const {
    const std::wstring inputString =
        L"#If Server And ExternalConnection And Client Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorAndExpression* preprocessorAndExpression = GetPreprocessorAndExpression(ast);
    
    if (preprocessorAndExpression == nullptr) {
        return;
    }
    
    const PreprocessorAndExpressionElement* preprocessorAndExpressionElement = GetPreprocessorAndExpressionElement(ast,
        1);
    
    if (preprocessorAndExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorAndExpressionElement, AstNodeType::preprocessorAndExpressionElement,
        preprocessorAndExpression, 1, 34, 10, 9, 3);
    VerifyToken(preprocessorAndExpressionElement->tkTermAnd, TokenType::termAnd, preprocessorAndExpressionElement, 34,
        3, 9);
    QVERIFY(preprocessorAndExpressionElement->preprocessorNotExpression.get() != nullptr);
}

void ParserTests::TestPreprocessorNotExpression() const {
    const std::wstring inputString =
        L"#If Not Not Server Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorAndExpression* preprocessorAndExpression = GetPreprocessorAndExpression(ast);
    
    if (preprocessorAndExpression == nullptr) {
        return;
    }
    
    const PreprocessorNotExpression* preprocessorNotExpression = GetPreprocessorNotExpression(ast);
    
    if (preprocessorNotExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorNotExpression, AstNodeType::preprocessorNotExpression, preprocessorAndExpression, -1, 4,
        14, 3, 5);
    QVERIFY(preprocessorNotExpression->preprocessorNotExpressionElements.size() == 2);
    QVERIFY(preprocessorNotExpression->preprocessorPrimeExpression.get() != nullptr);
}

void ParserTests::TestPreprocessorNotExpressionElement() const {
    const std::wstring inputString =
        L"#If Not Not Server Then\n"
        "\t\n"
        "#EndIf";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PreprocessorNotExpression* preprocessorNotExpression = GetPreprocessorNotExpression(ast);
    
    if (preprocessorNotExpression == nullptr) {
        return;
    }
    
    const PreprocessorNotExpressionElement* preprocessorNotExpressionElement = GetPreprocessorNotExpressionElement(ast,
        1);
    
    if (preprocessorNotExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*preprocessorNotExpressionElement, AstNodeType::preprocessorNotExpressionElement,
        preprocessorNotExpression, 1, 8, 3, 5, 1);
    VerifyToken(preprocessorNotExpressionElement->tkTermNot, TokenType::termNot, preprocessorNotExpressionElement, 8, 3,
        5);
}

void ParserTests::TestVariablesBlock() const {
    const std::wstring inputString =
        L"Var VariableA;\n"
        "Var VariableB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const BlockElement* blockElement = GetBlockElement(ast, 0);
    
    if (blockElement == nullptr) {
        return;
    }
    
    const VariablesBlock* variablesBlock = GetVariablesBlock(ast);
    
    if (variablesBlock == nullptr) {
        return;
    }
    
    VerifyAstNode(*variablesBlock, AstNodeType::variablesBlock, blockElement, -1, 0, 29, 0, 9);
    QVERIFY(variablesBlock->variablesBlockElements.size() == 2);
}

void ParserTests::TestVariablesBlockElement() const {
    const std::wstring inputString =
        L"Var VariableA;\n"
        "Var VariableB, VariableC, VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const VariablesBlock* variablesBlock = GetVariablesBlock(ast);
    
    if (variablesBlock == nullptr) {
        return;
    }
    
    const VariablesBlockElement* variablesBlockElement = GetVariablesBlockElement(ast, 1);
    
    if (variablesBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*variablesBlockElement, AstNodeType::variablesBlockElement, variablesBlock, 1, 15, 36, 5, 10);
    VerifyToken(variablesBlockElement->tkVar, TokenType::var, variablesBlockElement, 15, 3, 5);
    QVERIFY(variablesBlockElement->variable.get() != nullptr);
    QVERIFY(variablesBlockElement->variablesBlockElementElements.size() == 2);
    VerifyToken(variablesBlockElement->tkSemicolon, TokenType::semicolon, variablesBlockElement, 50, 1, 14);
}

void ParserTests::TestVariablesBlockElementElement() const {
    const std::wstring inputString =
        L"Var VariableA, VariableB, VariableC;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const VariablesBlockElement* variablesBlockElement = GetVariablesBlockElement(ast, 0);
    
    if (variablesBlockElement == nullptr) {
        return;
    }
    
    const VariablesBlockElementElement* variablesBlockElementElement = GetVariablesBlockElementElement(ast, 1);
    
    if (variablesBlockElementElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*variablesBlockElementElement, AstNodeType::variablesBlockElementElement, variablesBlockElement, 1,
        24, 11, 6, 3);
    VerifyToken(variablesBlockElementElement->tkComma, TokenType::comma, variablesBlockElementElement, 24, 1, 6);
    QVERIFY(variablesBlockElementElement->variable.get() != nullptr);
}

void ParserTests::TestVariable() const {
    const std::wstring inputString =
        L"Var VariableA Export;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const VariablesBlockElement* variablesBlockElement = GetVariablesBlockElement(ast, 0);
    
    if (variablesBlockElement == nullptr) {
        return;
    }
    
    const Variable* variable = GetVariable(ast);
    
    if (variable == nullptr) {
        return;
    }
    
    VerifyAstNode(*variable, AstNodeType::variable, variablesBlockElement, -1, 4, 16, 2, 3);
    VerifyToken(variable->tkIdentifier, TokenType::identifier, variable, 4, 9, 2);
    VerifyToken(variable->tkExport, TokenType::export_, variable, 14, 6, 4);
}

void ParserTests::TestFunctionsBlock() const {
    const std::wstring inputString =
        L"Procedure ProcedureA()\n"
        "\t\n"
        "EndProcedure\n"
        "\n"
        "Procedure ProcedureB()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const BlockElement* blockElement = GetBlockElement(ast, 0);
    
    if (blockElement == nullptr) {
        return;
    }
    
    const FunctionsBlock* functionsBlock = GetFunctionsBlock(ast);
    
    if (functionsBlock == nullptr) {
        return;
    }
    
    VerifyAstNode(*functionsBlock, AstNodeType::functionsBlock, blockElement, -1, 0, 76, 0, 20);
    QVERIFY(functionsBlock->functionsBlockElements.size() == 2);
}

void ParserTests::TestFunctionsBlockElement() const {
    TestFunctionsBlockElementFunctionBlock();
    TestFunctionsBlockElementProcedureBlock();
}

void ParserTests::TestFunctionsBlockElementFunctionBlock() const {
    const std::wstring inputString =
        L"Procedure ProcedureA()\n"
        "\t\n"
        "EndProcedure\n"
        "\n"
        "Function FunctionA()\n"
        "\t\n"
        "EndFunction";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionsBlock* functionsBlock = GetFunctionsBlock(ast);
    
    if (functionsBlock == nullptr) {
        return;
    }
    
    const FunctionsBlockElement* functionsBlockElement = GetFunctionsBlockElement(ast, 1);
    
    if (functionsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*functionsBlockElement, AstNodeType::functionsBlockElement, functionsBlock, 1, 39, 34, 11, 9);
    QVERIFY(functionsBlockElement->functionBlock.get() != nullptr);
    QVERIFY(functionsBlockElement->procedureBlock.get() == nullptr);
}

void ParserTests::TestFunctionsBlockElementProcedureBlock() const {
    const std::wstring inputString =
        L"Procedure ProcedureA()\n"
        "\t\n"
        "EndProcedure\n"
        "\n"
        "Procedure ProcedureB()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionsBlock* functionsBlock = GetFunctionsBlock(ast);
    
    if (functionsBlock == nullptr) {
        return;
    }
    
    const FunctionsBlockElement* functionsBlockElement = GetFunctionsBlockElement(ast, 1);
    
    if (functionsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*functionsBlockElement, AstNodeType::functionsBlockElement, functionsBlock, 1, 39, 37, 11, 9);
    QVERIFY(functionsBlockElement->functionBlock.get() == nullptr);
    QVERIFY(functionsBlockElement->procedureBlock.get() != nullptr);
}

void ParserTests::TestFunctionBlock() const {
    const std::wstring inputString =
        L"&AtServer\n"
        "Async Function FunctionA(ArgumentA) Export\n"
        "\t\n"
        "\tVariableA = 0;\n"
        "\t\n"
        "EndFunction";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionsBlockElement* functionsBlockElement = GetFunctionsBlockElement(ast, 0);
    
    if (functionsBlockElement == nullptr) {
        return;
    }
    
    const FunctionBlock* functionBlock = GetFunctionBlock(ast);
    
    if (functionBlock == nullptr) {
        return;
    }
    
    VerifyAstNode(*functionBlock, AstNodeType::functionBlock, functionsBlockElement, -1, 0, 84, 0, 27);
    QVERIFY(functionBlock->directiveOfPreprocessor.get() != nullptr);
    VerifyToken(functionBlock->tkAsync, TokenType::async, functionBlock, 10, 5, 3);
    VerifyToken(functionBlock->tkFunction, TokenType::function, functionBlock, 16, 8, 5);
    VerifyToken(functionBlock->tkIdentifier, TokenType::identifier, functionBlock, 25, 9, 7);
    VerifyToken(functionBlock->tkLeftParenthesis, TokenType::leftParenthesis, functionBlock, 34, 1, 8);
    QVERIFY(functionBlock->functionArgumentsBlock.get() != nullptr);
    VerifyToken(functionBlock->tkRightParenthesis, TokenType::rightParenthesis, functionBlock, 44, 1, 10);
    VerifyToken(functionBlock->tkExport, TokenType::export_, functionBlock, 46, 6, 12);
    QVERIFY(functionBlock->block.get() != nullptr);
    VerifyToken(functionBlock->tkEndFunction, TokenType::endFunction, functionBlock, 73, 11, 26);
}

void ParserTests::TestProcedureBlock() const {
    const std::wstring inputString =
        L"&AtServer\n"
        "Async Procedure ProcedureA(ArgumentA) Export\n"
        "\t\n"
        "\tVariableA = 0;\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionsBlockElement* functionsBlockElement = GetFunctionsBlockElement(ast, 0);
    
    if (functionsBlockElement == nullptr) {
        return;
    }
    
    const ProcedureBlock* procedureBlock = GetProcedureBlock(ast);
    
    if (procedureBlock == nullptr) {
        return;
    }
    
    VerifyAstNode(*procedureBlock, AstNodeType::procedureBlock, functionsBlockElement, -1, 0, 87, 0, 27);
    QVERIFY(procedureBlock->directiveOfPreprocessor.get() != nullptr);
    VerifyToken(procedureBlock->tkAsync, TokenType::async, procedureBlock, 10, 5, 3);
    VerifyToken(procedureBlock->tkProcedure, TokenType::procedure, procedureBlock, 16, 9, 5);
    VerifyToken(procedureBlock->tkIdentifier, TokenType::identifier, procedureBlock, 26, 10, 7);
    VerifyToken(procedureBlock->tkLeftParenthesis, TokenType::leftParenthesis, procedureBlock, 36, 1, 8);
    QVERIFY(procedureBlock->functionArgumentsBlock.get() != nullptr);
    VerifyToken(procedureBlock->tkRightParenthesis, TokenType::rightParenthesis, procedureBlock, 46, 1, 10);
    VerifyToken(procedureBlock->tkExport, TokenType::export_, procedureBlock, 48, 6, 12);
    QVERIFY(procedureBlock->block.get() != nullptr);
    VerifyToken(procedureBlock->tkEndProcedure, TokenType::endProcedure, procedureBlock, 75, 12, 26);
}

void ParserTests::TestDirectiveOfPreprocessor() const {
    TestDirectiveOfPreprocessorDirectiveAtClient();
    TestDirectiveOfPreprocessorDirectiveAtServer();
    TestDirectiveOfPreprocessorDirectiveAtServerNoContext();
    TestDirectiveOfPreprocessorDirectiveAtClientAtServerNoContext();
    TestDirectiveOfPreprocessorDirectiveAtClientAtServer();
    TestDirectiveOfPreprocessorAnnotation();
}

void ParserTests::TestDirectiveOfPreprocessorDirectiveAtClient() const {
    const std::wstring inputString =
        L"&AtClient\n"
        "Procedure ProcedureA()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const ProcedureBlock* procedureBlock = GetProcedureBlock(ast);
    
    if (procedureBlock == nullptr) {
        return;
    }
    
    const DirectiveOfPreprocessor* directiveOfPreprocessor = GetDirectiveOfPreprocessor(ast);
    
    if (directiveOfPreprocessor == nullptr) {
        return;
    }
    
    VerifyAstNode(*directiveOfPreprocessor, AstNodeType::directiveOfPreprocessor, procedureBlock, -1, 0, 9, 0, 2);
    QVERIFY(directiveOfPreprocessor->isDirectiveAtClient);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtServer);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtServerNoContext);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClientAtServerNoContext);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClientAtServer);
    
    VerifyToken(directiveOfPreprocessor->tkDirectiveAmpersand, TokenType::directiveAmpersand, directiveOfPreprocessor,
        0, 1, 0);
    VerifyToken(directiveOfPreprocessor->tkDirectiveAtClient, TokenType::directiveAtClient, directiveOfPreprocessor, 1,
        8, 1);
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtServer.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtServerNoContext.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClientAtServerNoContext.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClientAtServer.IsEmpty());
    QVERIFY(directiveOfPreprocessor->annotation.get() == nullptr);
}

void ParserTests::TestDirectiveOfPreprocessorDirectiveAtServer() const {
    const std::wstring inputString =
        L"&AtServer\n"
        "Procedure ProcedureA()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const ProcedureBlock* procedureBlock = GetProcedureBlock(ast);
    
    if (procedureBlock == nullptr) {
        return;
    }
    
    const DirectiveOfPreprocessor* directiveOfPreprocessor = GetDirectiveOfPreprocessor(ast);
    
    if (directiveOfPreprocessor == nullptr) {
        return;
    }
    
    VerifyAstNode(*directiveOfPreprocessor, AstNodeType::directiveOfPreprocessor, procedureBlock, -1, 0, 9, 0, 2);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClient);
    QVERIFY(directiveOfPreprocessor->isDirectiveAtServer);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtServerNoContext);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClientAtServerNoContext);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClientAtServer);
    
    VerifyToken(directiveOfPreprocessor->tkDirectiveAmpersand, TokenType::directiveAmpersand, directiveOfPreprocessor,
        0, 1, 0);
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClient.IsEmpty());
    VerifyToken(directiveOfPreprocessor->tkDirectiveAtServer, TokenType::directiveAtServer, directiveOfPreprocessor, 1,
        8, 1);
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtServerNoContext.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClientAtServerNoContext.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClientAtServer.IsEmpty());
    QVERIFY(directiveOfPreprocessor->annotation.get() == nullptr);
}

void ParserTests::TestDirectiveOfPreprocessorDirectiveAtServerNoContext() const {
    const std::wstring inputString =
        L"&AtServerNoContext\n"
        "Procedure ProcedureA()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const ProcedureBlock* procedureBlock = GetProcedureBlock(ast);
    
    if (procedureBlock == nullptr) {
        return;
    }
    
    const DirectiveOfPreprocessor* directiveOfPreprocessor = GetDirectiveOfPreprocessor(ast);
    
    if (directiveOfPreprocessor == nullptr) {
        return;
    }
    
    VerifyAstNode(*directiveOfPreprocessor, AstNodeType::directiveOfPreprocessor, procedureBlock, -1, 0, 18, 0, 2);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClient);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtServer);
    QVERIFY(directiveOfPreprocessor->isDirectiveAtServerNoContext);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClientAtServerNoContext);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClientAtServer);
    
    VerifyToken(directiveOfPreprocessor->tkDirectiveAmpersand, TokenType::directiveAmpersand, directiveOfPreprocessor,
        0, 1, 0);
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClient.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtServer.IsEmpty());
    VerifyToken(directiveOfPreprocessor->tkDirectiveAtServerNoContext, TokenType::directiveAtServerNoContext,
        directiveOfPreprocessor, 1, 17, 1);
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClientAtServerNoContext.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClientAtServer.IsEmpty());
    QVERIFY(directiveOfPreprocessor->annotation.get() == nullptr);
}

void ParserTests::TestDirectiveOfPreprocessorDirectiveAtClientAtServerNoContext() const {
    const std::wstring inputString =
        L"&AtClientAtServerNoContext\n"
        "Procedure ProcedureA()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const ProcedureBlock* procedureBlock = GetProcedureBlock(ast);
    
    if (procedureBlock == nullptr) {
        return;
    }
    
    const DirectiveOfPreprocessor* directiveOfPreprocessor = GetDirectiveOfPreprocessor(ast);
    
    if (directiveOfPreprocessor == nullptr) {
        return;
    }
    
    VerifyAstNode(*directiveOfPreprocessor, AstNodeType::directiveOfPreprocessor, procedureBlock, -1, 0, 26, 0, 2);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClient);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtServer);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtServerNoContext);
    QVERIFY(directiveOfPreprocessor->isDirectiveAtClientAtServerNoContext);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClientAtServer);
    
    VerifyToken(directiveOfPreprocessor->tkDirectiveAmpersand, TokenType::directiveAmpersand, directiveOfPreprocessor,
        0, 1, 0);
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClient.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtServer.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtServerNoContext.IsEmpty());
    VerifyToken(directiveOfPreprocessor->tkDirectiveAtClientAtServerNoContext,
        TokenType::directiveAtClientAtServerNoContext, directiveOfPreprocessor, 1, 25, 1);
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClientAtServer.IsEmpty());
    QVERIFY(directiveOfPreprocessor->annotation.get() == nullptr);
}

void ParserTests::TestDirectiveOfPreprocessorDirectiveAtClientAtServer() const {
    const std::wstring inputString =
        L"&AtClientAtServer\n"
        "Procedure ProcedureA()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const ProcedureBlock* procedureBlock = GetProcedureBlock(ast);
    
    if (procedureBlock == nullptr) {
        return;
    }
    
    const DirectiveOfPreprocessor* directiveOfPreprocessor = GetDirectiveOfPreprocessor(ast);
    
    if (directiveOfPreprocessor == nullptr) {
        return;
    }
    
    VerifyAstNode(*directiveOfPreprocessor, AstNodeType::directiveOfPreprocessor, procedureBlock, -1, 0, 17, 0, 2);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClient);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtServer);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtServerNoContext);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClientAtServerNoContext);
    QVERIFY(directiveOfPreprocessor->isDirectiveAtClientAtServer);
    
    VerifyToken(directiveOfPreprocessor->tkDirectiveAmpersand, TokenType::directiveAmpersand, directiveOfPreprocessor,
        0, 1, 0);
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClient.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtServer.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtServerNoContext.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClientAtServerNoContext.IsEmpty());
    VerifyToken(directiveOfPreprocessor->tkDirectiveAtClientAtServer, TokenType::directiveAtClientAtServer,
        directiveOfPreprocessor, 1, 16, 1);
    QVERIFY(directiveOfPreprocessor->annotation.get() == nullptr);
}

void ParserTests::TestDirectiveOfPreprocessorAnnotation() const {
    const std::wstring inputString =
        L"&Before(\"ProcedureA\")\n"
        "Procedure ProcedureB()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const ProcedureBlock* procedureBlock = GetProcedureBlock(ast);
    
    if (procedureBlock == nullptr) {
        return;
    }
    
    const DirectiveOfPreprocessor* directiveOfPreprocessor = GetDirectiveOfPreprocessor(ast);
    
    if (directiveOfPreprocessor == nullptr) {
        return;
    }
    
    VerifyAstNode(*directiveOfPreprocessor, AstNodeType::directiveOfPreprocessor, procedureBlock, -1, 0, 21, 0, 5);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClient);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtServer);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtServerNoContext);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClientAtServerNoContext);
    QVERIFY(!directiveOfPreprocessor->isDirectiveAtClientAtServer);
    
    QVERIFY(directiveOfPreprocessor->tkDirectiveAmpersand.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClient.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtServer.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtServerNoContext.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClientAtServerNoContext.IsEmpty());
    QVERIFY(directiveOfPreprocessor->tkDirectiveAtClientAtServer.IsEmpty());
    QVERIFY(directiveOfPreprocessor->annotation.get() != nullptr);
}

void ParserTests::TestAnnotation() const {
    TestAnnotationDirectiveBefore();
    TestAnnotationDirectiveAfter();
    TestAnnotationDirectiveInstead();
}

void ParserTests::TestAnnotationDirectiveBefore() const {
    const std::wstring inputString =
        L"&Before(\"ProcedureA\")\n"
        "Procedure ProcedureB()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const DirectiveOfPreprocessor* directiveOfPreprocessor = GetDirectiveOfPreprocessor(ast);
    
    if (directiveOfPreprocessor == nullptr) {
        return;
    }
    
    const Annotation* annotation = GetAnnotation(ast);
    
    if (annotation == nullptr) {
        return;
    }
    
    VerifyAstNode(*annotation, AstNodeType::annotation, directiveOfPreprocessor, -1, 0, 21, 0, 5);
    QVERIFY(annotation->isDirectiveBefore);
    QVERIFY(!annotation->isDirectiveAfter);
    QVERIFY(!annotation->isDirectiveInstead);
    
    VerifyToken(annotation->tkDirectiveAmpersand, TokenType::directiveAmpersand, annotation, 0, 1, 0);
    VerifyToken(annotation->tkDirectiveBefore, TokenType::directiveBefore, annotation, 1, 6, 1);
    QVERIFY(annotation->tkDirectiveAfter.IsEmpty());
    QVERIFY(annotation->tkDirectiveInstead.IsEmpty());
    VerifyToken(annotation->tkDirectiveLeftParenthesis, TokenType::directiveLeftParenthesis, annotation, 7, 1, 2);
    VerifyToken(annotation->tkDirectiveString, TokenType::directiveString, annotation, 8, 12, 3);
    VerifyToken(annotation->tkDirectiveRightParenthesis, TokenType::directiveRightParenthesis, annotation, 20, 1, 4);
}

void ParserTests::TestAnnotationDirectiveAfter() const {
    const std::wstring inputString =
        L"&After(\"ProcedureA\")\n"
        "Procedure ProcedureB()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const DirectiveOfPreprocessor* directiveOfPreprocessor = GetDirectiveOfPreprocessor(ast);
    
    if (directiveOfPreprocessor == nullptr) {
        return;
    }
    
    const Annotation* annotation = GetAnnotation(ast);
    
    if (annotation == nullptr) {
        return;
    }
    
    VerifyAstNode(*annotation, AstNodeType::annotation, directiveOfPreprocessor, -1, 0, 20, 0, 5);
    QVERIFY(!annotation->isDirectiveBefore);
    QVERIFY(annotation->isDirectiveAfter);
    QVERIFY(!annotation->isDirectiveInstead);
    
    VerifyToken(annotation->tkDirectiveAmpersand, TokenType::directiveAmpersand, annotation, 0, 1, 0);
    QVERIFY(annotation->tkDirectiveBefore.IsEmpty());
    VerifyToken(annotation->tkDirectiveAfter, TokenType::directiveAfter, annotation, 1, 5, 1);
    QVERIFY(annotation->tkDirectiveInstead.IsEmpty());
    VerifyToken(annotation->tkDirectiveLeftParenthesis, TokenType::directiveLeftParenthesis, annotation, 6, 1, 2);
    VerifyToken(annotation->tkDirectiveString, TokenType::directiveString, annotation, 7, 12, 3);
    VerifyToken(annotation->tkDirectiveRightParenthesis, TokenType::directiveRightParenthesis, annotation, 19, 1, 4);
}

void ParserTests::TestAnnotationDirectiveInstead() const {
    const std::wstring inputString =
        L"&Instead(\"ProcedureA\")\n"
        "Procedure ProcedureB()\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const DirectiveOfPreprocessor* directiveOfPreprocessor = GetDirectiveOfPreprocessor(ast);
    
    if (directiveOfPreprocessor == nullptr) {
        return;
    }
    
    const Annotation* annotation = GetAnnotation(ast);
    
    if (annotation == nullptr) {
        return;
    }
    
    VerifyAstNode(*annotation, AstNodeType::annotation, directiveOfPreprocessor, -1, 0, 22, 0, 5);
    QVERIFY(!annotation->isDirectiveBefore);
    QVERIFY(!annotation->isDirectiveAfter);
    QVERIFY(annotation->isDirectiveInstead);
    
    VerifyToken(annotation->tkDirectiveAmpersand, TokenType::directiveAmpersand, annotation, 0, 1, 0);
    QVERIFY(annotation->tkDirectiveBefore.IsEmpty());
    QVERIFY(annotation->tkDirectiveAfter.IsEmpty());
    VerifyToken(annotation->tkDirectiveInstead, TokenType::directiveInstead, annotation, 1, 7, 1);
    VerifyToken(annotation->tkDirectiveLeftParenthesis, TokenType::directiveLeftParenthesis, annotation, 8, 1, 2);
    VerifyToken(annotation->tkDirectiveString, TokenType::directiveString, annotation, 9, 12, 3);
    VerifyToken(annotation->tkDirectiveRightParenthesis, TokenType::directiveRightParenthesis, annotation, 21, 1, 4);
}

void ParserTests::TestFunctionArgumentsBlock() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA, ArgumentB, ArgumentC)\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const ProcedureBlock* procedureBlock = GetProcedureBlock(ast);
    
    if (procedureBlock == nullptr) {
        return;
    }
    
    const FunctionArgumentsBlock* functionArgumentsBlock = GetFunctionArgumentsBlock(ast);
    
    if (functionArgumentsBlock == nullptr) {
        return;
    }
    
    VerifyAstNode(*functionArgumentsBlock, AstNodeType::functionArgumentsBlock, procedureBlock, -1, 21, 31, 4, 7);
    QVERIFY(functionArgumentsBlock->functionArgument.get() != nullptr);
    QVERIFY(functionArgumentsBlock->functionArgumentsBlockElements.size() == 2);
}

void ParserTests::TestFunctionArgumentsBlockElement() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA, ArgumentB, ArgumentC)\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionArgumentsBlock* functionArgumentsBlock = GetFunctionArgumentsBlock(ast);
    
    if (functionArgumentsBlock == nullptr) {
        return;
    }
    
    const FunctionArgumentsBlockElement* functionArgumentsBlockElement = GetFunctionArgumentsBlockElement(ast, 1);
    
    if (functionArgumentsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*functionArgumentsBlockElement, AstNodeType::functionArgumentsBlockElement, functionArgumentsBlock, 1,
        41, 11, 8, 3);
    VerifyToken(functionArgumentsBlockElement->tkComma, TokenType::comma, functionArgumentsBlockElement, 41, 1, 8);
    QVERIFY(functionArgumentsBlockElement->functionArgument.get() != nullptr);
}

void ParserTests::TestFunctionArgument() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(Val ArgumentA = 0)\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionArgumentsBlock* functionArgumentsBlock = GetFunctionArgumentsBlock(ast);
    
    if (functionArgumentsBlock == nullptr) {
        return;
    }
    
    const FunctionArgument* functionArgument = GetFunctionArgument(ast);
    
    if (functionArgument == nullptr) {
        return;
    }
    
    VerifyAstNode(*functionArgument, AstNodeType::functionArgument, functionArgumentsBlock, -1, 21, 17, 4, 7);
    VerifyToken(functionArgument->tkVal, TokenType::val, functionArgument, 21, 3, 4);
    VerifyToken(functionArgument->tkIdentifier, TokenType::identifier, functionArgument, 25, 9, 6);
    VerifyToken(functionArgument->tkEquals, TokenType::equals, functionArgument, 35, 1, 8);
    QVERIFY(functionArgument->value.get() != nullptr);
}

void ParserTests::TestValue() const {
    TestValueSignedFloat();
    TestValueFloat();
    TestValueDate();
    TestValueNull();
    TestValueUndefined();
    TestValueFalse();
    TestValueTrue();
    TestValueString();
}

void ParserTests::TestValueSignedFloat() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = -1)\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionArgument* functionArgument = GetFunctionArgument(ast);
    
    if (functionArgument == nullptr) {
        return;
    }
    
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return;
    }
    
    VerifyAstNode(*value, AstNodeType::value, functionArgument, -1, 33, 2, 8, 1);
    QVERIFY(value->isSignedFloat);
    QVERIFY(!value->isFloat);
    QVERIFY(!value->isDate);
    QVERIFY(!value->isNull);
    QVERIFY(!value->isUndefined);
    QVERIFY(!value->isFalse);
    QVERIFY(!value->isTrue);
    
    VerifyToken(value->tkSignedFloat, TokenType::signedFloat, value, 33, 2, 8);
    QVERIFY(value->tkFloat.IsEmpty());
    QVERIFY(value->tkDate.IsEmpty());
    QVERIFY(value->tkNull.IsEmpty());
    QVERIFY(value->tkUndefined.IsEmpty());
    QVERIFY(value->tkFalse.IsEmpty());
    QVERIFY(value->tkTrue.IsEmpty());
    QVERIFY(value->string.get() == nullptr);
}

void ParserTests::TestValueFloat() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = 0)\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionArgument* functionArgument = GetFunctionArgument(ast);
    
    if (functionArgument == nullptr) {
        return;
    }
    
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return;
    }
    
    VerifyAstNode(*value, AstNodeType::value, functionArgument, -1, 33, 1, 8, 1);
    QVERIFY(!value->isSignedFloat);
    QVERIFY(value->isFloat);
    QVERIFY(!value->isDate);
    QVERIFY(!value->isNull);
    QVERIFY(!value->isUndefined);
    QVERIFY(!value->isFalse);
    QVERIFY(!value->isTrue);
    
    QVERIFY(value->tkSignedFloat.IsEmpty());
    VerifyToken(value->tkFloat, TokenType::float_, value, 33, 1, 8);
    QVERIFY(value->tkDate.IsEmpty());
    QVERIFY(value->tkNull.IsEmpty());
    QVERIFY(value->tkUndefined.IsEmpty());
    QVERIFY(value->tkFalse.IsEmpty());
    QVERIFY(value->tkTrue.IsEmpty());
    QVERIFY(value->string.get() == nullptr);
}

void ParserTests::TestValueDate() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = \'00010101\')\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionArgument* functionArgument = GetFunctionArgument(ast);
    
    if (functionArgument == nullptr) {
        return;
    }
    
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return;
    }
    
    VerifyAstNode(*value, AstNodeType::value, functionArgument, -1, 33, 10, 8, 1);
    QVERIFY(!value->isSignedFloat);
    QVERIFY(!value->isFloat);
    QVERIFY(value->isDate);
    QVERIFY(!value->isNull);
    QVERIFY(!value->isUndefined);
    QVERIFY(!value->isFalse);
    QVERIFY(!value->isTrue);
    
    QVERIFY(value->tkSignedFloat.IsEmpty());
    QVERIFY(value->tkFloat.IsEmpty());
    VerifyToken(value->tkDate, TokenType::date, value, 33, 10, 8);
    QVERIFY(value->tkNull.IsEmpty());
    QVERIFY(value->tkUndefined.IsEmpty());
    QVERIFY(value->tkFalse.IsEmpty());
    QVERIFY(value->tkTrue.IsEmpty());
    QVERIFY(value->string.get() == nullptr);
}

void ParserTests::TestValueNull() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = Null)\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionArgument* functionArgument = GetFunctionArgument(ast);
    
    if (functionArgument == nullptr) {
        return;
    }
    
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return;
    }
    
    VerifyAstNode(*value, AstNodeType::value, functionArgument, -1, 33, 4, 8, 1);
    QVERIFY(!value->isSignedFloat);
    QVERIFY(!value->isFloat);
    QVERIFY(!value->isDate);
    QVERIFY(value->isNull);
    QVERIFY(!value->isUndefined);
    QVERIFY(!value->isFalse);
    QVERIFY(!value->isTrue);
    
    QVERIFY(value->tkSignedFloat.IsEmpty());
    QVERIFY(value->tkFloat.IsEmpty());
    QVERIFY(value->tkDate.IsEmpty());
    VerifyToken(value->tkNull, TokenType::null, value, 33, 4, 8);
    QVERIFY(value->tkUndefined.IsEmpty());
    QVERIFY(value->tkFalse.IsEmpty());
    QVERIFY(value->tkTrue.IsEmpty());
    QVERIFY(value->string.get() == nullptr);
}

void ParserTests::TestValueUndefined() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = Undefined)\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionArgument* functionArgument = GetFunctionArgument(ast);
    
    if (functionArgument == nullptr) {
        return;
    }
    
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return;
    }
    
    VerifyAstNode(*value, AstNodeType::value, functionArgument, -1, 33, 9, 8, 1);
    QVERIFY(!value->isSignedFloat);
    QVERIFY(!value->isFloat);
    QVERIFY(!value->isDate);
    QVERIFY(!value->isNull);
    QVERIFY(value->isUndefined);
    QVERIFY(!value->isFalse);
    QVERIFY(!value->isTrue);
    
    QVERIFY(value->tkSignedFloat.IsEmpty());
    QVERIFY(value->tkFloat.IsEmpty());
    QVERIFY(value->tkDate.IsEmpty());
    QVERIFY(value->tkNull.IsEmpty());
    VerifyToken(value->tkUndefined, TokenType::undefined, value, 33, 9, 8);
    QVERIFY(value->tkFalse.IsEmpty());
    QVERIFY(value->tkTrue.IsEmpty());
    QVERIFY(value->string.get() == nullptr);
}

void ParserTests::TestValueFalse() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = False)\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionArgument* functionArgument = GetFunctionArgument(ast);
    
    if (functionArgument == nullptr) {
        return;
    }
    
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return;
    }
    
    VerifyAstNode(*value, AstNodeType::value, functionArgument, -1, 33, 5, 8, 1);
    QVERIFY(!value->isSignedFloat);
    QVERIFY(!value->isFloat);
    QVERIFY(!value->isDate);
    QVERIFY(!value->isNull);
    QVERIFY(!value->isUndefined);
    QVERIFY(value->isFalse);
    QVERIFY(!value->isTrue);
    
    QVERIFY(value->tkSignedFloat.IsEmpty());
    QVERIFY(value->tkFloat.IsEmpty());
    QVERIFY(value->tkDate.IsEmpty());
    QVERIFY(value->tkNull.IsEmpty());
    QVERIFY(value->tkUndefined.IsEmpty());
    VerifyToken(value->tkFalse, TokenType::false_, value, 33, 5, 8);
    QVERIFY(value->tkTrue.IsEmpty());
    QVERIFY(value->string.get() == nullptr);
}

void ParserTests::TestValueTrue() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = True)\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionArgument* functionArgument = GetFunctionArgument(ast);
    
    if (functionArgument == nullptr) {
        return;
    }
    
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return;
    }
    
    VerifyAstNode(*value, AstNodeType::value, functionArgument, -1, 33, 4, 8, 1);
    QVERIFY(!value->isSignedFloat);
    QVERIFY(!value->isFloat);
    QVERIFY(!value->isDate);
    QVERIFY(!value->isNull);
    QVERIFY(!value->isUndefined);
    QVERIFY(!value->isFalse);
    QVERIFY(value->isTrue);
    
    QVERIFY(value->tkSignedFloat.IsEmpty());
    QVERIFY(value->tkFloat.IsEmpty());
    QVERIFY(value->tkDate.IsEmpty());
    QVERIFY(value->tkNull.IsEmpty());
    QVERIFY(value->tkUndefined.IsEmpty());
    QVERIFY(value->tkFalse.IsEmpty());
    VerifyToken(value->tkTrue, TokenType::true_, value, 33, 4, 8);
    QVERIFY(value->string.get() == nullptr);
}

void ParserTests::TestValueString() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = \"String\")\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const FunctionArgument* functionArgument = GetFunctionArgument(ast);
    
    if (functionArgument == nullptr) {
        return;
    }
    
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return;
    }
    
    VerifyAstNode(*value, AstNodeType::value, functionArgument, -1, 33, 8, 8, 1);
    QVERIFY(!value->isSignedFloat);
    QVERIFY(!value->isFloat);
    QVERIFY(!value->isDate);
    QVERIFY(!value->isNull);
    QVERIFY(!value->isUndefined);
    QVERIFY(!value->isFalse);
    QVERIFY(!value->isTrue);
    
    QVERIFY(value->tkSignedFloat.IsEmpty());
    QVERIFY(value->tkFloat.IsEmpty());
    QVERIFY(value->tkDate.IsEmpty());
    QVERIFY(value->tkNull.IsEmpty());
    QVERIFY(value->tkUndefined.IsEmpty());
    QVERIFY(value->tkFalse.IsEmpty());
    QVERIFY(value->tkTrue.IsEmpty());
    QVERIFY(value->string.get() != nullptr);
}

void ParserTests::TestString() const {
    TestStringOneLine();
    TestStringSeveralLines();
}

void ParserTests::TestStringOneLine() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = \"String\")\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return;
    }
    
    const String* string = GetString(ast);
    
    if (string == nullptr) {
        return;
    }
    
    VerifyAstNode(*string, AstNodeType::string, value, -1, 33, 8, 8, 1);
    VerifyToken(string->tkString, TokenType::string, string, 33, 8, 8);
    QVERIFY(string->tkStringBeginning.IsEmpty());
    QVERIFY(string->stringElements.empty());
    QVERIFY(string->tkStringEnding.IsEmpty());
}

void ParserTests::TestStringSeveralLines() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = \"Beginning of string\n"
        "\t|Continue of string A\n"
        "\t|Continue of string B\n"
        "\t|End of string\")\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return;
    }
    
    const String* string = GetString(ast);
    
    if (string == nullptr) {
        return;
    }
    
    VerifyAstNode(*string, AstNodeType::string, value, -1, 33, 83, 8, 10);
    QVERIFY(string->tkString.IsEmpty());
    VerifyToken(string->tkStringBeginning, TokenType::stringBeginning, string, 33, 20, 8);
    QVERIFY(string->stringElements.size() == 2);
    VerifyToken(string->tkStringEnding, TokenType::stringEnding, string, 101, 15, 17);
}

void ParserTests::TestStringElement() const {
    const std::wstring inputString =
        L"Procedure ProcedureA(ArgumentA = \"Beginning of string\n"
        "\t|Continue of string A\n"
        "\t|Continue of string B\n"
        "\t|End of string\")\n"
        "\t\n"
        "EndProcedure";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const String* string = GetString(ast);
    
    if (string == nullptr) {
        return;
    }
    
    const StringElement* stringElement = GetStringElement(ast, 1);
    
    if (stringElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*stringElement, AstNodeType::stringElement, string, 1, 78, 21, 14, 1);
    VerifyToken(stringElement->tkStringContinue, TokenType::stringContinue, stringElement, 78, 21, 14);
}

void ParserTests::TestOperationsBlock() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "VariableB = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const BlockElement* blockElement = GetBlockElement(ast, 0);
    
    if (blockElement == nullptr) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlock, AstNodeType::operationsBlock, blockElement, -1, 0, 29, 0, 13);
    QVERIFY(operationsBlock->operationsBlockElements.size() == 2);
}

void ParserTests::TestOperationsBlockElement() const {
    TestOperationsBlockElementSettingStatement();
    TestOperationsBlockElementMethodStatement();
    TestOperationsBlockElementExecuteStatement();
    TestOperationsBlockElementReturnStatement();
    TestOperationsBlockElementAwaitStatement();
    TestOperationsBlockElementAddHandlerStatement();
    TestOperationsBlockElementRemoveHandlerStatement();
    TestOperationsBlockElementIfStatement();
    TestOperationsBlockElementForToStatement();
    TestOperationsBlockElementForEachStatement();
    TestOperationsBlockElementWhileStatement();
    TestOperationsBlockElementTryStatement();
    TestOperationsBlockElementRaiseStatement();
    TestOperationsBlockElementLabelStatement();
    TestOperationsBlockElementGotoStatement();
    TestOperationsBlockElementContinueStatement();
    TestOperationsBlockElementBreakStatement();
    TestOperationsBlockElementSemicolonStatement();
}

void ParserTests::TestOperationsBlockElementSettingStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "VariableB = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 14, 7, 6);
    QVERIFY(operationsBlockElement->settingStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementMethodStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "ProcedureA();";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 13, 7, 4);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementExecuteStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "Execute(\"String\");";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 18, 7, 5);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementReturnStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "Return 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 9, 7, 4);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementAwaitStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "Await VariableB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 16, 7, 4);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementAddHandlerStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "AddHandler VariableB.EventA, ProcedureA;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 40, 7, 9);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementRemoveHandlerStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "RemoveHandler VariableB.EventA, ProcedureA;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 43, 7, 9);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementIfStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "\n"
        "If VariableB Then\n"
        "\t\n"
        "EndIf;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 16, 26, 8, 10);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementForToStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "\n"
        "For VariableB = 0 To VariableC Do\n"
        "\t\n"
        "EndDo;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 16, 42, 8, 18);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementForEachStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "\n"
        "For each VariableB In VariableC Do\n"
        "\t\n"
        "EndDo;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 16, 43, 8, 16);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementWhileStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "\n"
        "While VariableB Do\n"
        "\t\n"
        "EndDo;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 16, 27, 8, 10);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementTryStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "\n"
        "Try\n"
        "\t\n"
        "Except\n"
        "\t\n"
        "EndTry;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 16, 22, 8, 10);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementRaiseStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "Raise 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 8, 7, 4);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementLabelStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "~LabelA:";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 8, 7, 3);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementGotoStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "Goto ~LabelA;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 13, 7, 5);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementContinueStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "Continue;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 9, 7, 2);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementBreakStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        "Break;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 6, 7, 2);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() != nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() == nullptr);
}

void ParserTests::TestOperationsBlockElementSemicolonStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;\n"
        ";";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 1);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*operationsBlockElement, AstNodeType::operationsBlockElement, operationsBlock, 1, 15, 1, 7, 1);
    QVERIFY(operationsBlockElement->settingStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->methodStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->executeStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->returnStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->awaitStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->addHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->removeHandlerStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->ifStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forToStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->forEachStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->whileStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->tryStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->raiseStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->labelStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->gotoStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->continueStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->breakStatement.get() == nullptr);
    QVERIFY(operationsBlockElement->semicolonStatement.get() != nullptr);
}

void ParserTests::TestSettingStatement() const {
    const std::wstring inputString =
        L"VariableA = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const SettingStatement* settingStatement = GetSettingStatement(ast);
    
    if (settingStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*settingStatement, AstNodeType::settingStatement, operationsBlockElement, -1, 0, 14, 0, 6);
    QVERIFY(settingStatement->memberExpression.get() != nullptr);
    VerifyToken(settingStatement->tkEquals, TokenType::equals, settingStatement, 10, 1, 2);
    QVERIFY(settingStatement->initialExpression.get() != nullptr);
    VerifyToken(settingStatement->tkSemicolon, TokenType::semicolon, settingStatement, 13, 1, 5);
}

void ParserTests::TestMemberExpression() const {
    const std::wstring inputString =
        L"VariableA.FieldA.FieldB[0][0] = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const SettingStatement* settingStatement = GetSettingStatement(ast);
    
    if (settingStatement == nullptr) {
        return;
    }
    
    const MemberExpression* memberExpression = GetMemberExpression(ast);
    
    if (memberExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*memberExpression, AstNodeType::memberExpression, settingStatement, -1, 0, 29, 0, 11);
    QVERIFY(memberExpression->memberMethodElements.size() == 2);
    VerifyToken(memberExpression->tkIdentifier, TokenType::identifier, memberExpression, 17, 6, 4);
    QVERIFY(memberExpression->arrayElements.size() == 2);
}

void ParserTests::TestMemberMethodElement() const {
    const std::wstring inputString =
        L"VariableA.FieldA.FieldB = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const MemberExpression* memberExpression = GetMemberExpression(ast);
    
    if (memberExpression == nullptr) {
        return;
    }
    
    const MemberMethodElement* memberMethodElement = GetMemberMethodElement(ast, 1);
    
    if (memberMethodElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*memberMethodElement, AstNodeType::memberMethodElement, memberExpression, 1, 10, 7, 2, 2);
    QVERIFY(memberMethodElement->memberMethodElementElement.get() != nullptr);
    VerifyToken(memberMethodElement->tkFullStop, TokenType::fullStop, memberMethodElement, 16, 1, 3);
}

void ParserTests::TestMemberMethodElementElement() const {
    const std::wstring inputString =
        L"ProcedureA()[0][0].FieldA = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const MemberMethodElement* memberMethodElement = GetMemberMethodElement(ast, 0);
    
    if (memberMethodElement == nullptr) {
        return;
    }
    
    const MemberMethodElementElement* memberMethodElementElement = GetMemberMethodElementElement(ast);
    
    if (memberMethodElementElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*memberMethodElementElement, AstNodeType::memberMethodElementElement, memberMethodElement, -1, 0, 18,
        0, 9);
    VerifyToken(memberMethodElementElement->tkIdentifier, TokenType::identifier, memberMethodElementElement, 0, 10, 0);
    QVERIFY(memberMethodElementElement->argumentsBlock.get() != nullptr);
    QVERIFY(memberMethodElementElement->arrayElements.size() == 2);
}

void ParserTests::TestArgumentsBlock() const {
    const std::wstring inputString =
        L"ProcedureA(0, 0, 0).FieldA = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const MemberMethodElementElement* memberMethodElementElement = GetMemberMethodElementElement(ast);
    
    if (memberMethodElementElement == nullptr) {
        return;
    }
    
    const ArgumentsBlock* argumentsBlock = GetArgumentsBlock(ast);
    
    if (argumentsBlock == nullptr) {
        return;
    }
    
    VerifyAstNode(*argumentsBlock, AstNodeType::argumentsBlock, memberMethodElementElement, -1, 10, 9, 1, 9);
    VerifyToken(argumentsBlock->tkLeftParenthesis, TokenType::leftParenthesis, argumentsBlock, 10, 1, 1);
    QVERIFY(argumentsBlock->initialExpression.get() != nullptr);
    QVERIFY(argumentsBlock->argumentsBlockElements.size() == 2);
    VerifyToken(argumentsBlock->tkRightParenthesis, TokenType::rightParenthesis, argumentsBlock, 18, 1, 9);
}

void ParserTests::TestArgumentsBlockElement() const {
    const std::wstring inputString =
        L"ProcedureA( , , 0).FieldA = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const ArgumentsBlock* argumentsBlock = GetArgumentsBlock(ast);
    
    if (argumentsBlock == nullptr) {
        return;
    }
    
    const ArgumentsBlockElement* argumentsBlockElement = GetArgumentsBlockElement(ast, 1);
    
    if (argumentsBlockElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*argumentsBlockElement, AstNodeType::argumentsBlockElement, argumentsBlock, 1, 14, 3, 5, 3);
    VerifyToken(argumentsBlockElement->tkComma, TokenType::comma, argumentsBlockElement, 14, 1, 5);
    QVERIFY(argumentsBlockElement->initialExpression.get() != nullptr);
}

void ParserTests::TestArrayElement() const {
    const std::wstring inputString =
        L"VariableA[0][0] = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const MemberExpression* memberExpression = GetMemberExpression(ast);
    
    if (memberExpression == nullptr) {
        return;
    }
    
    const ArrayElement* arrayElement = GetArrayElement(ast, 1);
    
    if (arrayElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*arrayElement, AstNodeType::arrayElement, memberExpression, 1, 12, 3, 4, 3);
    VerifyToken(arrayElement->tkLeftSquareBracket, TokenType::leftSquareBracket, arrayElement, 12, 1, 4);
    QVERIFY(arrayElement->initialExpression.get() != nullptr);
    VerifyToken(arrayElement->tkRightSquareBracket, TokenType::rightSquareBracket, arrayElement, 14, 1, 6);
}

void ParserTests::TestMethodStatement() const {
    const std::wstring inputString =
        L"ProcedureA();";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const MethodStatement* methodStatement = GetMethodStatement(ast);
    
    if (methodStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*methodStatement, AstNodeType::methodStatement, operationsBlockElement, -1, 0, 13, 0, 4);
    QVERIFY(methodStatement->methodExpression.get() != nullptr);
    VerifyToken(methodStatement->tkSemicolon, TokenType::semicolon, methodStatement, 12, 1, 3);
}

void ParserTests::TestMethodExpression() const {
    const std::wstring inputString =
        L"VariableA.FieldA.MethodA();";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const MethodStatement* methodStatement = GetMethodStatement(ast);
    
    if (methodStatement == nullptr) {
        return;
    }
    
    const MethodExpression* methodExpression = GetMethodExpression(ast);
    
    if (methodExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*methodExpression, AstNodeType::methodExpression, methodStatement, -1, 0, 26, 0, 7);
    QVERIFY(methodExpression->memberMethodElements.size() == 2);
    VerifyToken(methodExpression->tkIdentifier, TokenType::identifier, methodExpression, 17, 7, 4);
    QVERIFY(methodExpression->argumentsBlock.get() != nullptr);
}

void ParserTests::TestExecuteStatement() const {
    const std::wstring inputString =
        L"Execute(\"String\");";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const ExecuteStatement* executeStatement = GetExecuteStatement(ast);
    
    if (executeStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*executeStatement, AstNodeType::executeStatement, operationsBlockElement, -1, 0, 18, 0, 5);
    VerifyToken(executeStatement->tkExecute, TokenType::execute, executeStatement, 0, 7, 0);
    VerifyToken(executeStatement->tkLeftParenthesis, TokenType::leftParenthesis, executeStatement, 7, 1, 1);
    QVERIFY(executeStatement->initialExpression.get() != nullptr);
    VerifyToken(executeStatement->tkRightParenthesis, TokenType::rightParenthesis, executeStatement, 16, 1, 3);
    VerifyToken(executeStatement->tkSemicolon, TokenType::semicolon, executeStatement, 17, 1, 4);
}

void ParserTests::TestReturnStatement() const {
    const std::wstring inputString =
        L"Return 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const ReturnStatement* returnStatement = GetReturnStatement(ast);
    
    if (returnStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*returnStatement, AstNodeType::returnStatement, operationsBlockElement, -1, 0, 9, 0, 4);
    VerifyToken(returnStatement->tkReturn, TokenType::return_, returnStatement, 0, 6, 0);
    QVERIFY(returnStatement->initialExpression.get() != nullptr);
    VerifyToken(returnStatement->tkSemicolon, TokenType::semicolon, returnStatement, 8, 1, 3);
}

void ParserTests::TestAwaitStatement() const {
    const std::wstring inputString =
        L"Await VariableA;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const AwaitStatement* awaitStatement = GetAwaitStatement(ast);
    
    if (awaitStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*awaitStatement, AstNodeType::awaitStatement, operationsBlockElement, -1, 0, 16, 0, 4);
    VerifyToken(awaitStatement->tkAwait, TokenType::await, awaitStatement, 0, 5, 0);
    QVERIFY(awaitStatement->initialExpression.get() != nullptr);
    VerifyToken(awaitStatement->tkSemicolon, TokenType::semicolon, awaitStatement, 15, 1, 3);
}

void ParserTests::TestAddHandlerStatement() const {
    const std::wstring inputString =
        L"AddHandler VariableA.EventA, VariableB.HandlerA;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const AddHandlerStatement* addHandlerStatement = GetAddHandlerStatement(ast);
    
    if (addHandlerStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*addHandlerStatement, AstNodeType::addHandlerStatement, operationsBlockElement, -1, 0, 48, 0, 11);
    VerifyToken(addHandlerStatement->tkAddHandler, TokenType::addHandler, addHandlerStatement, 0, 10, 0);
    QVERIFY(addHandlerStatement->memberMethodEvent.get() != nullptr);
    VerifyToken(addHandlerStatement->tkFullStopEvent, TokenType::fullStop, addHandlerStatement, 20, 1, 3);
    VerifyToken(addHandlerStatement->tkIdentifierEvent, TokenType::identifier, addHandlerStatement, 21, 6, 4);
    VerifyToken(addHandlerStatement->tkComma, TokenType::comma, addHandlerStatement, 27, 1, 5);
    QVERIFY(addHandlerStatement->memberMethodHandler.get() != nullptr);
    VerifyToken(addHandlerStatement->tkFullStopHandler, TokenType::fullStop, addHandlerStatement, 38, 1, 8);
    VerifyToken(addHandlerStatement->tkIdentifierHandler, TokenType::identifier, addHandlerStatement, 39, 8, 9);
    VerifyToken(addHandlerStatement->tkSemicolon, TokenType::semicolon, addHandlerStatement, 47, 1, 10);
}

void ParserTests::TestRemoveHandlerStatement() const {
   const std::wstring inputString =
        L"RemoveHandler VariableA.EventA, VariableB.HandlerA;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const RemoveHandlerStatement* removeHandlerStatement = GetRemoveHandlerStatement(ast);
    
    if (removeHandlerStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*removeHandlerStatement, AstNodeType::removeHandlerStatement, operationsBlockElement, -1, 0, 51, 0,
        11);
    VerifyToken(removeHandlerStatement->tkRemoveHandler, TokenType::removeHandler, removeHandlerStatement, 0, 13, 0);
    QVERIFY(removeHandlerStatement->memberMethodEvent.get() != nullptr);
    VerifyToken(removeHandlerStatement->tkFullStopEvent, TokenType::fullStop, removeHandlerStatement, 23, 1, 3);
    VerifyToken(removeHandlerStatement->tkIdentifierEvent, TokenType::identifier, removeHandlerStatement, 24, 6, 4);
    VerifyToken(removeHandlerStatement->tkComma, TokenType::comma, removeHandlerStatement, 30, 1, 5);
    QVERIFY(removeHandlerStatement->memberMethodHandler.get() != nullptr);
    VerifyToken(removeHandlerStatement->tkFullStopHandler, TokenType::fullStop, removeHandlerStatement, 41, 1, 8);
    VerifyToken(removeHandlerStatement->tkIdentifierHandler, TokenType::identifier, removeHandlerStatement, 42, 8, 9);
    VerifyToken(removeHandlerStatement->tkSemicolon, TokenType::semicolon, removeHandlerStatement, 50, 1, 10);
}

void ParserTests::TestIfStatement() const {
    const std::wstring inputString =
        L"If VariableA Then\n"
        "\tVariableA = 0;\n"
        "\t\n"
        "ElsIf VariableB Then\n"
        "\t\n"
        "ElsIf VariableC Then\n"
        "\t\n"
        "Else\n"
        "\tVariableB = 0;\n"
        "EndIf;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const IfStatement* ifStatement = GetIfStatement(ast);
    
    if (ifStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*ifStatement, AstNodeType::ifStatement, operationsBlockElement, -1, 0, 109, 0, 44);
    VerifyToken(ifStatement->tkIf, TokenType::if_, ifStatement, 0, 2, 0);
    QVERIFY(ifStatement->initialExpression.get() != nullptr);
    VerifyToken(ifStatement->tkThen, TokenType::then, ifStatement, 13, 4, 4);
    QVERIFY(ifStatement->blockIf.get() != nullptr);
    QVERIFY(ifStatement->ifStatementElements.size() == 2);
    VerifyToken(ifStatement->tkElse, TokenType::else_, ifStatement, 82, 4, 32);
    QVERIFY(ifStatement->blockElse.get() != nullptr);
    VerifyToken(ifStatement->tkEndIf, TokenType::endIf, ifStatement, 103, 5, 42);
    VerifyToken(ifStatement->tkSemicolon, TokenType::semicolon, ifStatement, 108, 1, 43);
}

void ParserTests::TestIfStatementElement() const {
    const std::wstring inputString =
        L"If VariableA Then\n"
        "\t\n"
        "ElsIf VariableB Then\n"
        "\tVariableA = 0;\n"
        "\t\n"
        "ElsIf VariableC Then\n"
        "\tVariableB = 0;\n"
        "\t\n"
        "EndIf;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const IfStatement* ifStatement = GetIfStatement(ast);
    
    if (ifStatement == nullptr) {
        return;
    }
    
    const IfStatementElement* ifStatementElement = GetIfStatementElement(ast, 1);
    
    if (ifStatementElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*ifStatementElement, AstNodeType::ifStatementElement, ifStatement, 1, 59, 36, 24, 13);
    VerifyToken(ifStatementElement->tkElsIf, TokenType::elsIf, ifStatementElement, 59, 5, 24);
    QVERIFY(ifStatementElement->initialExpression.get() != nullptr);
    VerifyToken(ifStatementElement->tkThen, TokenType::then, ifStatementElement, 75, 4, 28);
    QVERIFY(ifStatementElement->block.get() != nullptr);
}

void ParserTests::TestForToStatement() const {
    const std::wstring inputString =
        L"For VariableA = 0 To VariableB Do\n"
        "\tVariableC = 0;\n"
        "EndDo;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const ForToStatement* forToStatement = GetForToStatement(ast);
    
    if (forToStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*forToStatement, AstNodeType::forToStatement, operationsBlockElement, -1, 0, 56, 0, 24);
    VerifyToken(forToStatement->tkFor, TokenType::for_, forToStatement, 0, 3, 0);
    VerifyToken(forToStatement->tkIdentifier, TokenType::identifier, forToStatement, 4, 9, 2);
    VerifyToken(forToStatement->tkEquals, TokenType::equals, forToStatement, 14, 1, 4);
    QVERIFY(forToStatement->initialExpressionA.get() != nullptr);
    VerifyToken(forToStatement->tkTo, TokenType::to, forToStatement, 18, 2, 8);
    QVERIFY(forToStatement->initialExpressionB.get() != nullptr);
    VerifyToken(forToStatement->tkDo, TokenType::do_, forToStatement, 31, 2, 12);
    QVERIFY(forToStatement->block.get() != nullptr);
    VerifyToken(forToStatement->tkEndDo, TokenType::endDo, forToStatement, 50, 5, 22);
    VerifyToken(forToStatement->tkSemicolon, TokenType::semicolon, forToStatement, 55, 1, 23);
}

void ParserTests::TestForEachStatement() const {
    const std::wstring inputString =
        L"For each VariableA In VariableB Do\n"
        "\tVariableC = 0;\n"
        "EndDo;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const ForEachStatement* forEachStatement = GetForEachStatement(ast);
    
    if (forEachStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*forEachStatement, AstNodeType::forEachStatement, operationsBlockElement, -1, 0, 57, 0, 22);
    VerifyToken(forEachStatement->tkFor, TokenType::for_, forEachStatement, 0, 3, 0);
    VerifyToken(forEachStatement->tkEach, TokenType::each, forEachStatement, 4, 4, 2);
    VerifyToken(forEachStatement->tkIdentifier, TokenType::identifier, forEachStatement, 9, 9, 4);
    VerifyToken(forEachStatement->tkIn, TokenType::in, forEachStatement, 19, 2, 6);
    QVERIFY(forEachStatement->initialExpression.get() != nullptr);
    VerifyToken(forEachStatement->tkDo, TokenType::do_, forEachStatement, 32, 2, 10);
    QVERIFY(forEachStatement->block.get() != nullptr);
    VerifyToken(forEachStatement->tkEndDo, TokenType::endDo, forEachStatement, 51, 5, 20);
    VerifyToken(forEachStatement->tkSemicolon, TokenType::semicolon, forEachStatement, 56, 1, 21);
}

void ParserTests::TestWhileStatement() const {
    const std::wstring inputString =
        L"While VariableA Do\n"
        "\tVariableB = 0;\n"
        "EndDo;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const WhileStatement* whileStatement = GetWhileStatement(ast);
    
    if (whileStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*whileStatement, AstNodeType::whileStatement, operationsBlockElement, -1, 0, 41, 0, 16);
    VerifyToken(whileStatement->tkWhile, TokenType::while_, whileStatement, 0, 5, 0);
    QVERIFY(whileStatement->initialExpression.get() != nullptr);
    VerifyToken(whileStatement->tkDo, TokenType::do_, whileStatement, 16, 2, 4);
    QVERIFY(whileStatement->block.get() != nullptr);
    VerifyToken(whileStatement->tkEndDo, TokenType::endDo, whileStatement, 35, 5, 14);
    VerifyToken(whileStatement->tkSemicolon, TokenType::semicolon, whileStatement, 40, 1, 15);
}

void ParserTests::TestTryStatement() const {
    const std::wstring inputString =
        L"Try\n"
        "\tVariableA = 0;\n"
        "\t\n"
        "Except\n"
        "\tVariableB = 0;\n"
        "EndTry;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const TryStatement* tryStatement = GetTryStatement(ast);
    
    if (tryStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*tryStatement, AstNodeType::tryStatement, operationsBlockElement, -1, 0, 52, 0, 24);
    VerifyToken(tryStatement->tkTry, TokenType::try_, tryStatement, 0, 3, 0);
    QVERIFY(tryStatement->blockTry.get() != nullptr);
    VerifyToken(tryStatement->tkExcept, TokenType::except, tryStatement, 22, 6, 12);
    QVERIFY(tryStatement->blockExcept.get() != nullptr);
    VerifyToken(tryStatement->tkEndTry, TokenType::endTry, tryStatement, 45, 6, 22);
    VerifyToken(tryStatement->tkSemicolon, TokenType::semicolon, tryStatement, 51, 1, 23);
}

void ParserTests::TestRaiseStatement() const {
    const std::wstring inputString =
        L"Raise 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const RaiseStatement* raiseStatement = GetRaiseStatement(ast);
    
    if (raiseStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*raiseStatement, AstNodeType::raiseStatement, operationsBlockElement, -1, 0, 8, 0, 4);
    VerifyToken(raiseStatement->tkRaise, TokenType::raise, raiseStatement, 0, 5, 0);
    QVERIFY(raiseStatement->initialExpression.get() != nullptr);
    VerifyToken(raiseStatement->tkSemicolon, TokenType::semicolon, raiseStatement, 7, 1, 3);
}

void ParserTests::TestLabelStatement() const {
    const std::wstring inputString =
        L"~LabelA:";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const LabelStatement* labelStatement = GetLabelStatement(ast);
    
    if (labelStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*labelStatement, AstNodeType::labelStatement, operationsBlockElement, -1, 0, 8, 0, 3);
    VerifyToken(labelStatement->tkTilde, TokenType::tilde, labelStatement, 0, 1, 0);
    VerifyToken(labelStatement->tkIdentifier, TokenType::identifier, labelStatement, 1, 6, 1);
    VerifyToken(labelStatement->tkColon, TokenType::colon, labelStatement, 7, 1, 2);
}

void ParserTests::TestGotoStatement() const {
    const std::wstring inputString =
        L"Goto ~LabelA;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const GotoStatement* gotoStatement = GetGotoStatement(ast);
    
    if (gotoStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*gotoStatement, AstNodeType::gotoStatement, operationsBlockElement, -1, 0, 13, 0, 5);
    VerifyToken(gotoStatement->tkGoto, TokenType::goto_, gotoStatement, 0, 4, 0);
    VerifyToken(gotoStatement->tkTilde, TokenType::tilde, gotoStatement, 5, 1, 2);
    VerifyToken(gotoStatement->tkIdentifier, TokenType::identifier, gotoStatement, 6, 6, 3);
    VerifyToken(gotoStatement->tkSemicolon, TokenType::semicolon, gotoStatement, 12, 1, 4);
}

void ParserTests::TestContinueStatement() const {
    const std::wstring inputString =
        L"Continue;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const ContinueStatement* continueStatement = GetContinueStatement(ast);
    
    if (continueStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*continueStatement, AstNodeType::continueStatement, operationsBlockElement, -1, 0, 9, 0, 2);
    VerifyToken(continueStatement->tkContinue, TokenType::continue_, continueStatement, 0, 8, 0);
    VerifyToken(continueStatement->tkSemicolon, TokenType::semicolon, continueStatement, 8, 1, 1);
}

void ParserTests::TestBreakStatement() const {
    const std::wstring inputString =
        L"Break;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const BreakStatement* breakStatement = GetBreakStatement(ast);
    
    if (breakStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*breakStatement, AstNodeType::breakStatement, operationsBlockElement, -1, 0, 6, 0, 2);
    VerifyToken(breakStatement->tkBreak, TokenType::break_, breakStatement, 0, 5, 0);
    VerifyToken(breakStatement->tkSemicolon, TokenType::semicolon, breakStatement, 5, 1, 1);
}

void ParserTests::TestSemicolonStatement() const {
    const std::wstring inputString =
        L";";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return;
    }
    
    const SemicolonStatement* semicolonStatement = GetSemicolonStatement(ast);
    
    if (semicolonStatement == nullptr) {
        return;
    }
    
    VerifyAstNode(*semicolonStatement, AstNodeType::semicolonStatement, operationsBlockElement, -1, 0, 1, 0, 1);
    VerifyToken(semicolonStatement->tkSemicolon, TokenType::semicolon, semicolonStatement, 0, 1, 0);
}

void ParserTests::TestInitialExpression() const {
    const std::wstring inputString =
        L"VariableA = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const SettingStatement* settingStatement = GetSettingStatement(ast);
    
    if (settingStatement == nullptr) {
        return;
    }
    
    const InitialExpression* initialExpression = GetInitialExpression(ast);
    
    if (initialExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*initialExpression, AstNodeType::initialExpression, settingStatement, -1, 12, 1, 4, 1);
    QVERIFY(initialExpression->expression.get() != nullptr);
}

void ParserTests::TestExpression() const {
    const std::wstring inputString =
        L"VariableA = VariableB\n"
        "\tOr VariableC\n"
        "\tOr VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const InitialExpression* initialExpression = GetInitialExpression(ast);
    
    if (initialExpression == nullptr) {
        return;
    }
    
    const Expression* expression = GetExpression(ast);
    
    if (expression == nullptr) {
        return;
    }
    
    VerifyAstNode(*expression, AstNodeType::expression, initialExpression, -1, 12, 37, 4, 11);
    QVERIFY(expression->andExpression.get() != nullptr);
    QVERIFY(expression->expressionElements.size() == 2);
}

void ParserTests::TestExpressionElement() const {
    const std::wstring inputString =
        L"VariableA = VariableB\n"
        "\tOr VariableC\n"
        "\tOr VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const Expression* expression = GetExpression(ast);
    
    if (expression == nullptr) {
        return;
    }
    
    const ExpressionElement* expressionElement = GetExpressionElement(ast, 1);
    
    if (expressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*expressionElement, AstNodeType::expressionElement, expression, 1, 37, 12, 12, 3);
    VerifyToken(expressionElement->tkOr, TokenType::or_, expressionElement, 37, 2, 12);
    QVERIFY(expressionElement->andExpression.get() != nullptr);
}

void ParserTests::TestPrimeExpression() const {
    TestPrimeExpressionValue();
    TestPrimeExpressionExpressionInParenthesis();
    TestPrimeExpressionMemberMethod();
    TestPrimeExpressionNewElement();
    TestPrimeExpressionTernaryOperationElement();
    TestPrimeExpressionAwaitElement();
}

void ParserTests::TestPrimeExpressionValue() const {
    const std::wstring inputString =
        L"VariableA = 0;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*primeExpression, AstNodeType::primeExpression, signExpression, -1, 12, 1, 4, 1);
    QVERIFY(primeExpression->value.get() != nullptr);
    QVERIFY(primeExpression->expressionInParenthesis.get() == nullptr);
    QVERIFY(primeExpression->memberMethod.get() == nullptr);
    QVERIFY(primeExpression->newElement.get() == nullptr);
    QVERIFY(primeExpression->ternaryOperationElement.get() == nullptr);
    QVERIFY(primeExpression->awaitElement.get() == nullptr);
}

void ParserTests::TestPrimeExpressionExpressionInParenthesis() const {
    const std::wstring inputString =
        L"VariableA = (0);";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*primeExpression, AstNodeType::primeExpression, signExpression, -1, 12, 3, 4, 3);
    QVERIFY(primeExpression->value.get() == nullptr);
    QVERIFY(primeExpression->expressionInParenthesis.get() != nullptr);
    QVERIFY(primeExpression->memberMethod.get() == nullptr);
    QVERIFY(primeExpression->newElement.get() == nullptr);
    QVERIFY(primeExpression->ternaryOperationElement.get() == nullptr);
    QVERIFY(primeExpression->awaitElement.get() == nullptr);
}

void ParserTests::TestPrimeExpressionMemberMethod() const {
    const std::wstring inputString =
        L"VariableA = VariableB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*primeExpression, AstNodeType::primeExpression, signExpression, -1, 12, 9, 4, 1);
    QVERIFY(primeExpression->value.get() == nullptr);
    QVERIFY(primeExpression->expressionInParenthesis.get() == nullptr);
    QVERIFY(primeExpression->memberMethod.get() != nullptr);
    QVERIFY(primeExpression->newElement.get() == nullptr);
    QVERIFY(primeExpression->ternaryOperationElement.get() == nullptr);
    QVERIFY(primeExpression->awaitElement.get() == nullptr);
}

void ParserTests::TestPrimeExpressionNewElement() const {
    const std::wstring inputString =
        L"VariableA = New ClassA();";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*primeExpression, AstNodeType::primeExpression, signExpression, -1, 12, 12, 4, 5);
    QVERIFY(primeExpression->value.get() == nullptr);
    QVERIFY(primeExpression->expressionInParenthesis.get() == nullptr);
    QVERIFY(primeExpression->memberMethod.get() == nullptr);
    QVERIFY(primeExpression->newElement.get() != nullptr);
    QVERIFY(primeExpression->ternaryOperationElement.get() == nullptr);
    QVERIFY(primeExpression->awaitElement.get() == nullptr);
}

void ParserTests::TestPrimeExpressionTernaryOperationElement() const {
    const std::wstring inputString =
        L"VariableA = ? (VariableB, VariableC, VariableD);";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*primeExpression, AstNodeType::primeExpression, signExpression, -1, 12, 35, 4, 11);
    QVERIFY(primeExpression->value.get() == nullptr);
    QVERIFY(primeExpression->expressionInParenthesis.get() == nullptr);
    QVERIFY(primeExpression->memberMethod.get() == nullptr);
    QVERIFY(primeExpression->newElement.get() == nullptr);
    QVERIFY(primeExpression->ternaryOperationElement.get() != nullptr);
    QVERIFY(primeExpression->awaitElement.get() == nullptr);
}

void ParserTests::TestPrimeExpressionAwaitElement() const {
    const std::wstring inputString =
        L"VariableA = Await VariableB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*primeExpression, AstNodeType::primeExpression, signExpression, -1, 12, 15, 4, 3);
    QVERIFY(primeExpression->value.get() == nullptr);
    QVERIFY(primeExpression->expressionInParenthesis.get() == nullptr);
    QVERIFY(primeExpression->memberMethod.get() == nullptr);
    QVERIFY(primeExpression->newElement.get() == nullptr);
    QVERIFY(primeExpression->ternaryOperationElement.get() == nullptr);
    QVERIFY(primeExpression->awaitElement.get() != nullptr);
}

void ParserTests::TestExpressionInParenthesis() const {
    const std::wstring inputString =
        L"VariableA = (0);";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    const ExpressionInParenthesis* expressionInParenthesis = GetExpressionInParenthesis(ast);
    
    if (expressionInParenthesis == nullptr) {
        return;
    }
    
    VerifyAstNode(*expressionInParenthesis, AstNodeType::expressionInParenthesis, primeExpression, -1, 12, 3, 4, 3);
    VerifyToken(expressionInParenthesis->tkLeftParenthesis, TokenType::leftParenthesis, expressionInParenthesis, 12, 1,
        4);
    QVERIFY(expressionInParenthesis->expression.get() != nullptr);
    VerifyToken(expressionInParenthesis->tkRightParenthesis, TokenType::rightParenthesis, expressionInParenthesis, 14,
        1, 6);
}

void ParserTests::TestMemberMethod() const {
    const std::wstring inputString =
        L"VariableA = VariableB.FieldA.FieldB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    const MemberMethod* memberMethod = GetMemberMethod(ast);
    
    if (memberMethod == nullptr) {
        return;
    }
    
    VerifyAstNode(*memberMethod, AstNodeType::memberMethod, primeExpression, -1, 12, 23, 4, 5);
    QVERIFY(memberMethod->memberMethodElements.size() == 2);
    QVERIFY(memberMethod->memberMethodElementElement.get() != nullptr);
}

void ParserTests::TestNewElement() const {
    TestNewElementWithIdentifier();
    TestNewElementWithoutIdentifier();
}

void ParserTests::TestNewElementWithIdentifier() const {
    const std::wstring inputString =
        L"VariableA = New ClassA();";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    const NewElement* newElement = GetNewElement(ast);
    
    if (newElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*newElement, AstNodeType::newElement, primeExpression, -1, 12, 12, 4, 5);
    VerifyToken(newElement->tkNew, TokenType::new_, newElement, 12, 3, 4);
    VerifyToken(newElement->tkIdentifier, TokenType::identifier, newElement, 16, 6, 6);
    QVERIFY(newElement->argumentsBlock.get() != nullptr);
    QVERIFY(newElement->newArgumentsBlock.get() == nullptr);
}

void ParserTests::TestNewElementWithoutIdentifier() const {
    const std::wstring inputString =
        L"VariableA = New (VariableB);";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    const NewElement* newElement = GetNewElement(ast);
    
    if (newElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*newElement, AstNodeType::newElement, primeExpression, -1, 12, 15, 4, 5);
    VerifyToken(newElement->tkNew, TokenType::new_, newElement, 12, 3, 4);
    QVERIFY(newElement->tkIdentifier.IsEmpty());
    QVERIFY(newElement->argumentsBlock.get() == nullptr);
    QVERIFY(newElement->newArgumentsBlock.get() != nullptr);
}

void ParserTests::TestNewArgumentsBlock() const {
    const std::wstring inputString =
        L"VariableA = New (VariableB, , );";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const NewElement* newElement = GetNewElement(ast);
    
    if (newElement == nullptr) {
        return;
    }
    
    const NewArgumentsBlock* newArgumentsBlock = GetNewArgumentsBlock(ast);
    
    if (newArgumentsBlock == nullptr) {
        return;
    }
    
    VerifyAstNode(*newArgumentsBlock, AstNodeType::newArgumentsBlock, newElement, -1, 16, 15, 6, 7);
    VerifyToken(newArgumentsBlock->tkLeftParenthesis, TokenType::leftParenthesis, newArgumentsBlock, 16, 1, 6);
    QVERIFY(newArgumentsBlock->initialExpression.get() != nullptr);
    QVERIFY(newArgumentsBlock->argumentsBlockElements.size() == 2);
    VerifyToken(newArgumentsBlock->tkRightParenthesis, TokenType::rightParenthesis, newArgumentsBlock, 30, 1, 12);
}

void ParserTests::TestTernaryOperationElement() const {
    const std::wstring inputString =
        L"VariableA = ? (VariableB, VariableC, VariableD);";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    const TernaryOperationElement* ternaryOperationElement = GetTernaryOperationElement(ast);
    
    if (ternaryOperationElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*ternaryOperationElement, AstNodeType::ternaryOperationElement, primeExpression, -1, 12, 35, 4, 11);
    VerifyToken(ternaryOperationElement->tkQuestionMark, TokenType::questionMark, ternaryOperationElement, 12, 1, 4);
    VerifyToken(ternaryOperationElement->tkLeftParenthesis, TokenType::leftParenthesis, ternaryOperationElement, 14, 1,
        6);
    QVERIFY(ternaryOperationElement->initialExpression.get() != nullptr);
    VerifyToken(ternaryOperationElement->tkCommaA, TokenType::comma, ternaryOperationElement, 24, 1, 8);
    QVERIFY(ternaryOperationElement->initialExpressionTrue.get() != nullptr);
    VerifyToken(ternaryOperationElement->tkCommaB, TokenType::comma, ternaryOperationElement, 35, 1, 11);
    QVERIFY(ternaryOperationElement->initialExpressionFalse.get() != nullptr);
    VerifyToken(ternaryOperationElement->tkRightParenthesis, TokenType::rightParenthesis, ternaryOperationElement, 46,
        1, 14);
}

void ParserTests::TestAwaitElement() const {
    const std::wstring inputString =
        L"VariableA = Await VariableB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return;
    }
    
    const AwaitElement* awaitElement = GetAwaitElement(ast);
    
    if (awaitElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*awaitElement, AstNodeType::awaitElement, primeExpression, -1, 12, 15, 4, 3);
    VerifyToken(awaitElement->tkAwait, TokenType::await, awaitElement, 12, 5, 4);
    QVERIFY(awaitElement->initialExpression.get() != nullptr);
}

void ParserTests::TestAndExpression() const {
    const std::wstring inputString =
        L"VariableA = VariableB\n"
        "\tAnd VariableC\n"
        "\tAnd VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const Expression* expression = GetExpression(ast);
    
    if (expression == nullptr) {
        return;
    }
    
    const AndExpression* andExpression = GetAndExpression(ast);
    
    if (andExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*andExpression, AstNodeType::andExpression, expression, -1, 12, 39, 4, 11);
    QVERIFY(andExpression->notExpression.get() != nullptr);
    QVERIFY(andExpression->andExpressionElements.size() == 2);
}

void ParserTests::TestAndExpressionElement() const {
    const std::wstring inputString =
        L"VariableA = VariableB\n"
        "\tAnd VariableC\n"
        "\tAnd VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const AndExpression* andExpression = GetAndExpression(ast);
    
    if (andExpression == nullptr) {
        return;
    }
    
    const AndExpressionElement* andExpressionElement = GetAndExpressionElement(ast, 1);
    
    if (andExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*andExpressionElement, AstNodeType::andExpressionElement, andExpression, 1, 38, 13, 12, 3);
    VerifyToken(andExpressionElement->tkAnd, TokenType::and_, andExpressionElement, 38, 3, 12);
    QVERIFY(andExpressionElement->notExpression.get() != nullptr);
}

void ParserTests::TestNotExpression() const {
    const std::wstring inputString =
        L"VariableA = Not Not VariableB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const AndExpression* andExpression = GetAndExpression(ast);
    
    if (andExpression == nullptr) {
        return;
    }
    
    const NotExpression* notExpression = GetNotExpression(ast);
    
    if (notExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*notExpression, AstNodeType::notExpression, andExpression, -1, 12, 17, 4, 5);
    QVERIFY(notExpression->notExpressionElements.size() == 2);
    QVERIFY(notExpression->relationalExpression.get() != nullptr);
}

void ParserTests::TestNotExpressionElement() const {
    const std::wstring inputString =
        L"VariableA = Not Not VariableB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const NotExpression* notExpression = GetNotExpression(ast);
    
    if (notExpression == nullptr) {
        return;
    }
    
    const NotExpressionElement* notExpressionElement = GetNotExpressionElement(ast, 1);
    
    if (notExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*notExpressionElement, AstNodeType::notExpressionElement, notExpression, 1, 16, 3, 6, 1);
    VerifyToken(notExpressionElement->tkNot, TokenType::not_, notExpressionElement, 16, 3, 6);
}

void ParserTests::TestRelationalExpression() const {
    const std::wstring inputString =
        L"VariableA = VariableB = VariableC = VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const NotExpression* notExpression = GetNotExpression(ast);
    
    if (notExpression == nullptr) {
        return;
    }
    
    const RelationalExpression* relationalExpression = GetRelationalExpression(ast);
    
    if (relationalExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*relationalExpression, AstNodeType::relationalExpression, notExpression, -1, 12, 33, 4, 9);
    QVERIFY(relationalExpression->addingExpression.get() != nullptr);
    QVERIFY(relationalExpression->relationalExpressionElements.size() == 2);
}

void ParserTests::TestRelationalExpressionElement() const {
    TestRelationalExpressionElementEquals();
    TestRelationalExpressionElementNotEquals();
    TestRelationalExpressionElementLess();
    TestRelationalExpressionElementLessOrEquals();
    TestRelationalExpressionElementGreater();
    TestRelationalExpressionElementGreaterOrEquals();
}

void ParserTests::TestRelationalExpressionElementEquals() const {
    const std::wstring inputString =
        L"VariableA = VariableB = VariableC = VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const RelationalExpression* relationalExpression = GetRelationalExpression(ast);
    
    if (relationalExpression == nullptr) {
        return;
    }
    
    const RelationalExpressionElement* relationalExpressionElement = GetRelationalExpressionElement(ast, 1);
    
    if (relationalExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*relationalExpressionElement, AstNodeType::relationalExpressionElement, relationalExpression, 1, 34,
        11, 10, 3);
    QVERIFY(relationalExpressionElement->isEquals);
    QVERIFY(!relationalExpressionElement->isNotEquals);
    QVERIFY(!relationalExpressionElement->isLess);
    QVERIFY(!relationalExpressionElement->isLessOrEquals);
    QVERIFY(!relationalExpressionElement->isGreater);
    QVERIFY(!relationalExpressionElement->isGreaterOrEquals);
    
    VerifyToken(relationalExpressionElement->tkEquals, TokenType::equals, relationalExpressionElement, 34, 1, 10);
    QVERIFY(relationalExpressionElement->tkNotEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkLess.IsEmpty());
    QVERIFY(relationalExpressionElement->tkLessOrEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkGreater.IsEmpty());
    QVERIFY(relationalExpressionElement->tkGreaterOrEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->addingExpression.get() != nullptr);
}

void ParserTests::TestRelationalExpressionElementNotEquals() const {
    const std::wstring inputString =
        L"VariableA = VariableB = VariableC <> VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const RelationalExpression* relationalExpression = GetRelationalExpression(ast);
    
    if (relationalExpression == nullptr) {
        return;
    }
    
    const RelationalExpressionElement* relationalExpressionElement = GetRelationalExpressionElement(ast, 1);
    
    if (relationalExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*relationalExpressionElement, AstNodeType::relationalExpressionElement, relationalExpression, 1, 34,
        12, 10, 3);
    QVERIFY(!relationalExpressionElement->isEquals);
    QVERIFY(relationalExpressionElement->isNotEquals);
    QVERIFY(!relationalExpressionElement->isLess);
    QVERIFY(!relationalExpressionElement->isLessOrEquals);
    QVERIFY(!relationalExpressionElement->isGreater);
    QVERIFY(!relationalExpressionElement->isGreaterOrEquals);
    
    QVERIFY(relationalExpressionElement->tkEquals.IsEmpty());
    VerifyToken(relationalExpressionElement->tkNotEquals, TokenType::notEquals, relationalExpressionElement, 34, 2, 10);
    QVERIFY(relationalExpressionElement->tkLess.IsEmpty());
    QVERIFY(relationalExpressionElement->tkLessOrEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkGreater.IsEmpty());
    QVERIFY(relationalExpressionElement->tkGreaterOrEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->addingExpression.get() != nullptr);
}

void ParserTests::TestRelationalExpressionElementLess() const {
    const std::wstring inputString =
        L"VariableA = VariableB = VariableC < VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const RelationalExpression* relationalExpression = GetRelationalExpression(ast);
    
    if (relationalExpression == nullptr) {
        return;
    }
    
    const RelationalExpressionElement* relationalExpressionElement = GetRelationalExpressionElement(ast, 1);
    
    if (relationalExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*relationalExpressionElement, AstNodeType::relationalExpressionElement, relationalExpression, 1, 34,
        11, 10, 3);
    QVERIFY(!relationalExpressionElement->isEquals);
    QVERIFY(!relationalExpressionElement->isNotEquals);
    QVERIFY(relationalExpressionElement->isLess);
    QVERIFY(!relationalExpressionElement->isLessOrEquals);
    QVERIFY(!relationalExpressionElement->isGreater);
    QVERIFY(!relationalExpressionElement->isGreaterOrEquals);
    
    QVERIFY(relationalExpressionElement->tkEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkNotEquals.IsEmpty());
    VerifyToken(relationalExpressionElement->tkLess, TokenType::less, relationalExpressionElement, 34, 1, 10);
    QVERIFY(relationalExpressionElement->tkLessOrEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkGreater.IsEmpty());
    QVERIFY(relationalExpressionElement->tkGreaterOrEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->addingExpression.get() != nullptr);
}

void ParserTests::TestRelationalExpressionElementLessOrEquals() const {
    const std::wstring inputString =
        L"VariableA = VariableB = VariableC <= VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const RelationalExpression* relationalExpression = GetRelationalExpression(ast);
    
    if (relationalExpression == nullptr) {
        return;
    }
    
    const RelationalExpressionElement* relationalExpressionElement = GetRelationalExpressionElement(ast, 1);
    
    if (relationalExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*relationalExpressionElement, AstNodeType::relationalExpressionElement, relationalExpression, 1, 34,
        12, 10, 3);
    QVERIFY(!relationalExpressionElement->isEquals);
    QVERIFY(!relationalExpressionElement->isNotEquals);
    QVERIFY(!relationalExpressionElement->isLess);
    QVERIFY(relationalExpressionElement->isLessOrEquals);
    QVERIFY(!relationalExpressionElement->isGreater);
    QVERIFY(!relationalExpressionElement->isGreaterOrEquals);
    
    QVERIFY(relationalExpressionElement->tkEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkNotEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkLess.IsEmpty());
    VerifyToken(relationalExpressionElement->tkLessOrEquals, TokenType::lessOrEquals, relationalExpressionElement, 34,
        2, 10);
    QVERIFY(relationalExpressionElement->tkGreater.IsEmpty());
    QVERIFY(relationalExpressionElement->tkGreaterOrEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->addingExpression.get() != nullptr);
}

void ParserTests::TestRelationalExpressionElementGreater() const {
    const std::wstring inputString =
        L"VariableA = VariableB = VariableC > VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const RelationalExpression* relationalExpression = GetRelationalExpression(ast);
    
    if (relationalExpression == nullptr) {
        return;
    }
    
    const RelationalExpressionElement* relationalExpressionElement = GetRelationalExpressionElement(ast, 1);
    
    if (relationalExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*relationalExpressionElement, AstNodeType::relationalExpressionElement, relationalExpression, 1, 34,
        11, 10, 3);
    QVERIFY(!relationalExpressionElement->isEquals);
    QVERIFY(!relationalExpressionElement->isNotEquals);
    QVERIFY(!relationalExpressionElement->isLess);
    QVERIFY(!relationalExpressionElement->isLessOrEquals);
    QVERIFY(relationalExpressionElement->isGreater);
    QVERIFY(!relationalExpressionElement->isGreaterOrEquals);
    
    QVERIFY(relationalExpressionElement->tkEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkNotEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkLess.IsEmpty());
    QVERIFY(relationalExpressionElement->tkLessOrEquals.IsEmpty());
    VerifyToken(relationalExpressionElement->tkGreater, TokenType::greater, relationalExpressionElement, 34, 1, 10);
    QVERIFY(relationalExpressionElement->tkGreaterOrEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->addingExpression.get() != nullptr);
}

void ParserTests::TestRelationalExpressionElementGreaterOrEquals() const {
    const std::wstring inputString =
        L"VariableA = VariableB = VariableC >= VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const RelationalExpression* relationalExpression = GetRelationalExpression(ast);
    
    if (relationalExpression == nullptr) {
        return;
    }
    
    const RelationalExpressionElement* relationalExpressionElement = GetRelationalExpressionElement(ast, 1);
    
    if (relationalExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*relationalExpressionElement, AstNodeType::relationalExpressionElement, relationalExpression, 1, 34,
        12, 10, 3);
    QVERIFY(!relationalExpressionElement->isEquals);
    QVERIFY(!relationalExpressionElement->isNotEquals);
    QVERIFY(!relationalExpressionElement->isLess);
    QVERIFY(!relationalExpressionElement->isLessOrEquals);
    QVERIFY(!relationalExpressionElement->isGreater);
    QVERIFY(relationalExpressionElement->isGreaterOrEquals);
    
    QVERIFY(relationalExpressionElement->tkEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkNotEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkLess.IsEmpty());
    QVERIFY(relationalExpressionElement->tkLessOrEquals.IsEmpty());
    QVERIFY(relationalExpressionElement->tkGreater.IsEmpty());
    VerifyToken(relationalExpressionElement->tkGreaterOrEquals, TokenType::greaterOrEquals, relationalExpressionElement,
        34, 2, 10);
    QVERIFY(relationalExpressionElement->addingExpression.get() != nullptr);
}

void ParserTests::TestAddingExpression() const {
    const std::wstring inputString =
        L"VariableA = VariableB + VariableC + VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const RelationalExpression* relationalExpression = GetRelationalExpression(ast);
    
    if (relationalExpression == nullptr) {
        return;
    }
    
    const AddingExpression* addingExpression = GetAddingExpression(ast);
    
    if (addingExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*addingExpression, AstNodeType::addingExpression, relationalExpression, -1, 12, 33, 4, 9);
    QVERIFY(addingExpression->multiplyingExpression.get() != nullptr);
    QVERIFY(addingExpression->addingExpressionElements.size() == 2);
}

void ParserTests::TestAddingExpressionElement() const {
    TestAddingExpressionElementMinus();
    TestAddingExpressionElementPlus();
}

void ParserTests::TestAddingExpressionElementMinus() const {
    const std::wstring inputString =
        L"VariableA = VariableB + VariableC - VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const AddingExpression* addingExpression = GetAddingExpression(ast);
    
    if (addingExpression == nullptr) {
        return;
    }
    
    const AddingExpressionElement* addingExpressionElement = GetAddingExpressionElement(ast, 1);
    
    if (addingExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*addingExpressionElement, AstNodeType::addingExpressionElement, addingExpression, 1, 34, 11, 10, 3);
    QVERIFY(addingExpressionElement->isMinus);
    QVERIFY(!addingExpressionElement->isPlus);
    VerifyToken(addingExpressionElement->tkMinus, TokenType::minus, addingExpressionElement, 34, 1, 10);
    QVERIFY(addingExpressionElement->tkPlus.IsEmpty());
    QVERIFY(addingExpressionElement->multiplyingExpression.get() != nullptr);
}

void ParserTests::TestAddingExpressionElementPlus() const {
    const std::wstring inputString =
        L"VariableA = VariableB + VariableC + VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const AddingExpression* addingExpression = GetAddingExpression(ast);
    
    if (addingExpression == nullptr) {
        return;
    }
    
    const AddingExpressionElement* addingExpressionElement = GetAddingExpressionElement(ast, 1);
    
    if (addingExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*addingExpressionElement, AstNodeType::addingExpressionElement, addingExpression, 1, 34, 11, 10, 3);
    QVERIFY(!addingExpressionElement->isMinus);
    QVERIFY(addingExpressionElement->isPlus);
    QVERIFY(addingExpressionElement->tkMinus.IsEmpty());
    VerifyToken(addingExpressionElement->tkPlus, TokenType::plus, addingExpressionElement, 34, 1, 10);
    QVERIFY(addingExpressionElement->multiplyingExpression.get() != nullptr);
}

void ParserTests::TestMultiplyingExpression() const {
    const std::wstring inputString =
        L"VariableA = VariableB * VariableC * VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const AddingExpression* addingExpression = GetAddingExpression(ast);
    
    if (addingExpression == nullptr) {
        return;
    }
    
    const MultiplyingExpression* multiplyingExpression = GetMultiplyingExpression(ast);
    
    if (multiplyingExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*multiplyingExpression, AstNodeType::multiplyingExpression, addingExpression, -1, 12, 33, 4, 9);
    QVERIFY(multiplyingExpression->signExpression.get() != nullptr);
    QVERIFY(multiplyingExpression->multiplyingExpressionElements.size() == 2);
}

void ParserTests::TestMultiplyingExpressionElement() const {
    TestMultiplyingExpressionElementAsterisk();
    TestMultiplyingExpressionElementSolidus();
    TestMultiplyingExpressionElementPercent();
}

void ParserTests::TestMultiplyingExpressionElementAsterisk() const {
    const std::wstring inputString =
        L"VariableA = VariableB * VariableC * VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const MultiplyingExpression* multiplyingExpression = GetMultiplyingExpression(ast);
    
    if (multiplyingExpression == nullptr) {
        return;
    }
    
    const MultiplyingExpressionElement* multiplyingExpressionElement = GetMultiplyingExpressionElement(ast, 1);
    
    if (multiplyingExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*multiplyingExpressionElement, AstNodeType::multiplyingExpressionElement, multiplyingExpression, 1,
        34, 11, 10, 3);
    QVERIFY(multiplyingExpressionElement->isAsterisk);
    QVERIFY(!multiplyingExpressionElement->isSolidus);
    QVERIFY(!multiplyingExpressionElement->isPercent);
    
    VerifyToken(multiplyingExpressionElement->tkAsterisk, TokenType::asterisk, multiplyingExpressionElement, 34, 1, 10);
    QVERIFY(multiplyingExpressionElement->tkSolidus.IsEmpty());
    QVERIFY(multiplyingExpressionElement->tkPercent.IsEmpty());
    QVERIFY(multiplyingExpressionElement->signExpression.get() != nullptr);
}

void ParserTests::TestMultiplyingExpressionElementSolidus() const {
    const std::wstring inputString =
        L"VariableA = VariableB * VariableC / VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const MultiplyingExpression* multiplyingExpression = GetMultiplyingExpression(ast);
    
    if (multiplyingExpression == nullptr) {
        return;
    }
    
    const MultiplyingExpressionElement* multiplyingExpressionElement = GetMultiplyingExpressionElement(ast, 1);
    
    if (multiplyingExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*multiplyingExpressionElement, AstNodeType::multiplyingExpressionElement, multiplyingExpression, 1,
        34, 11, 10, 3);
    QVERIFY(!multiplyingExpressionElement->isAsterisk);
    QVERIFY(multiplyingExpressionElement->isSolidus);
    QVERIFY(!multiplyingExpressionElement->isPercent);
    
    QVERIFY(multiplyingExpressionElement->tkAsterisk.IsEmpty());
    VerifyToken(multiplyingExpressionElement->tkSolidus, TokenType::solidus, multiplyingExpressionElement, 34, 1, 10);
    QVERIFY(multiplyingExpressionElement->tkPercent.IsEmpty());
    QVERIFY(multiplyingExpressionElement->signExpression.get() != nullptr);
}

void ParserTests::TestMultiplyingExpressionElementPercent() const {
    const std::wstring inputString =
        L"VariableA = VariableB * VariableC % VariableD;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const MultiplyingExpression* multiplyingExpression = GetMultiplyingExpression(ast);
    
    if (multiplyingExpression == nullptr) {
        return;
    }
    
    const MultiplyingExpressionElement* multiplyingExpressionElement = GetMultiplyingExpressionElement(ast, 1);
    
    if (multiplyingExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*multiplyingExpressionElement, AstNodeType::multiplyingExpressionElement, multiplyingExpression, 1,
        34, 11, 10, 3);
    QVERIFY(!multiplyingExpressionElement->isAsterisk);
    QVERIFY(!multiplyingExpressionElement->isSolidus);
    QVERIFY(multiplyingExpressionElement->isPercent);
    
    QVERIFY(multiplyingExpressionElement->tkAsterisk.IsEmpty());
    QVERIFY(multiplyingExpressionElement->tkSolidus.IsEmpty());
    VerifyToken(multiplyingExpressionElement->tkPercent, TokenType::percent, multiplyingExpressionElement, 34, 1, 10);
    QVERIFY(multiplyingExpressionElement->signExpression.get() != nullptr);
}

void ParserTests::TestSignExpression() const {
    const std::wstring inputString =
        L"VariableA = ++VariableB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const MultiplyingExpression* multiplyingExpression = GetMultiplyingExpression(ast);
    
    if (multiplyingExpression == nullptr) {
        return;
    }
    
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return;
    }
    
    VerifyAstNode(*signExpression, AstNodeType::signExpression, multiplyingExpression, -1, 12, 11, 4, 3);
    QVERIFY(signExpression->signExpressionElements.size() == 2);
    QVERIFY(signExpression->primeExpression.get() != nullptr);
}

void ParserTests::TestSignExpressionElement() const {
    TestSignExpressionElementMinus();
    TestSignExpressionElementPlus();
}

void ParserTests::TestSignExpressionElementMinus() const {
    const std::wstring inputString =
        L"VariableA = +-VariableB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return;
    }
    
    const SignExpressionElement* signExpressionElement = GetSignExpressionElement(ast, 1);
    
    if (signExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*signExpressionElement, AstNodeType::signExpressionElement, signExpression, 1, 13, 1, 5, 1);
    QVERIFY(signExpressionElement->isMinus);
    QVERIFY(!signExpressionElement->isPlus);
    
    VerifyToken(signExpressionElement->tkMinus, TokenType::minus, signExpressionElement, 13, 1, 5);
    QVERIFY(signExpressionElement->tkPlus.IsEmpty());
}

void ParserTests::TestSignExpressionElementPlus() const {
    const std::wstring inputString =
        L"VariableA = ++VariableB;";
    
    Ast ast;
    
    if (!FillAst(inputString, ast)) {
        return;
    }
    
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return;
    }
    
    const SignExpressionElement* signExpressionElement = GetSignExpressionElement(ast, 1);
    
    if (signExpressionElement == nullptr) {
        return;
    }
    
    VerifyAstNode(*signExpressionElement, AstNodeType::signExpressionElement, signExpression, 1, 13, 1, 5, 1);
    QVERIFY(!signExpressionElement->isMinus);
    QVERIFY(signExpressionElement->isPlus);
    
    QVERIFY(signExpressionElement->tkMinus.IsEmpty());
    VerifyToken(signExpressionElement->tkPlus, TokenType::plus, signExpressionElement, 13, 1, 5);
}

bool ParserTests::FillAst(const std::wstring& string, Ast& ast) const {
    Lexer lexer;
    TokenStream tokenStream;
    
    if (!lexer.FillTokenStream(string, tokenStream)) {
        QWARN("Can't fill tokens");
        return false;
    }
    
    Parser parser;
    
    if (!parser.FillAst(tokenStream, ast)) {
        QWARN("Can't fill ast nodes");
        return false;
    }
    
    return true;
}

void ParserTests::VerifyAstNode(const AstNode& astNode, const AstNodeType type, const void* prnt,
    const int index, const int chrPos, const int numOfChrs, const int tknPos, const int numOfTkns) const {
    QVERIFY(astNode.type == type);
    QVERIFY(astNode.prnt == prnt);
    QVERIFY(astNode.index == index);
    QVERIFY(astNode.chrPos == chrPos);
    QVERIFY(astNode.numOfChrs == numOfChrs);
    QVERIFY(astNode.tknPos == tknPos);
    QVERIFY(astNode.numOfTkns == numOfTkns);
}

void ParserTests::VerifyToken(const AstToken& token, const TokenType type, const void* prnt, const int chrPos,
    const int numOfChrs, const int tknPos) const {
    QVERIFY(token.type == type);
    QVERIFY(token.prnt == prnt);
    QVERIFY(token.chrPos == chrPos);
    QVERIFY(token.numOfChrs == numOfChrs);
    QVERIFY(token.tknPos == tknPos);
    QVERIFY(token.numOfTkns == 1);
}

const Block* ParserTests::GetBlock(const Ast& ast) const {
    const Block* block = ast.block.get();
    
    if (block == nullptr) {
        QWARN("block == nullptr");
        return nullptr;
    }
    
    return block;
}

const BlockElement* ParserTests::GetBlockElement(const Ast& ast, const int index) const {
    const Block* block = GetBlock(ast);
    
    if (block == nullptr) {
        return nullptr;
    }
    
    if (index >= block->blockElements.size()) {
        std::string string = std::to_string(index) + " >= block->blockElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &block->blockElements[index];
}

const PreprocessorRegionBlock* ParserTests::GetPreprocessorRegionBlock(const Ast& ast) const {
    const BlockElement* blockElement = GetBlockElement(ast, 0);
    
    if (blockElement == nullptr) {
        return nullptr;
    }
    
    const PreprocessorRegionBlock* preprocessorRegionBlock = blockElement->preprocessorRegionBlock.get();
    
    if (preprocessorRegionBlock == nullptr) {
        QWARN("preprocessorRegionBlock == nullptr");
        return nullptr;
    }
    
    return preprocessorRegionBlock;
}

const PreprocessorIfBlock* ParserTests::GetPreprocessorIfBlock(const Ast& ast) const {
    const BlockElement* blockElement = GetBlockElement(ast, 0);
    
    if (blockElement == nullptr) {
        return nullptr;
    }
    
    const PreprocessorIfBlock* preprocessorIfBlock = blockElement->preprocessorIfBlock.get();
    
    if (preprocessorIfBlock == nullptr) {
        QWARN("preprocessorIfBlock == nullptr");
        return nullptr;
    }
    
    return preprocessorIfBlock;
}

const PreprocessorIfBlockElement* ParserTests::GetPreprocessorIfBlockElement(const Ast& ast, const int index) const {
    const PreprocessorIfBlock* preprocessorIfBlock = GetPreprocessorIfBlock(ast);
    
    if (preprocessorIfBlock == nullptr) {
        return nullptr;
    }
    
    if (index >= preprocessorIfBlock->preprocessorIfBlockElements.size()) {
        std::string string = std::to_string(index) + " >= preprocessorIfBlock->preprocessorIfBlockElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &preprocessorIfBlock->preprocessorIfBlockElements[index];
}

const PreprocessorExpression* ParserTests::GetPreprocessorExpression(const Ast& ast) const {
    const PreprocessorIfBlock* preprocessorIfBlock = GetPreprocessorIfBlock(ast);
    
    if (preprocessorIfBlock == nullptr) {
        return nullptr;
    }
    
    const PreprocessorExpression* preprocessorExpression = preprocessorIfBlock->preprocessorExpression.get();
    
    if (preprocessorExpression == nullptr) {
        QWARN("preprocessorExpression == nullptr");
        return nullptr;
    }
    
    return preprocessorExpression;
}

const PreprocessorExpressionElement* ParserTests::GetPreprocessorExpressionElement(const Ast& ast,
    const int index) const {
    const PreprocessorExpression* preprocessorExpression = GetPreprocessorExpression(ast);
    
    if (preprocessorExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= preprocessorExpression->preprocessorExpressionElements.size()) {
        std::string string = std::to_string(index)
            + " >= preprocessorExpression->preprocessorExpressionElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &preprocessorExpression->preprocessorExpressionElements[index];
}

const PreprocessorPrimeExpression* ParserTests::GetPreprocessorPrimeExpression(const Ast& ast) const {
    const PreprocessorNotExpression* preprocessorNotExpression = GetPreprocessorNotExpression(ast);
    
    if (preprocessorNotExpression == nullptr) {
        return nullptr;
    }
    
    const PreprocessorPrimeExpression* preprocessorPrimeExpression =
        preprocessorNotExpression->preprocessorPrimeExpression.get();
    
    if (preprocessorPrimeExpression == nullptr) {
        QWARN("preprocessorPrimeExpression == nullptr");
        return nullptr;
    }
    
    return preprocessorPrimeExpression;
}

const PreprocessorValue* ParserTests::GetPreprocessorValue(const Ast& ast) const {
    const PreprocessorPrimeExpression* preprocessorPrimeExpression = GetPreprocessorPrimeExpression(ast);
    
    if (preprocessorPrimeExpression == nullptr) {
        return nullptr;
    }
    
    const PreprocessorValue* preprocessorValue = preprocessorPrimeExpression->preprocessorValue.get();
    
    if (preprocessorValue == nullptr) {
        QWARN("preprocessorValue == nullptr");
        return nullptr;
    }
    
    return preprocessorValue;
}

const PreprocessorAndExpression* ParserTests::GetPreprocessorAndExpression(const Ast& ast) const {
    const PreprocessorExpression* preprocessorExpression = GetPreprocessorExpression(ast);
    
    if (preprocessorExpression == nullptr) {
        return nullptr;
    }
    
    const PreprocessorAndExpression* preprocessorAndExpression =
        preprocessorExpression->preprocessorAndExpression.get();
    
    if (preprocessorAndExpression == nullptr) {
        QWARN("preprocessorAndExpression == nullptr");
        return nullptr;
    }
    
    return preprocessorAndExpression;
}

const PreprocessorAndExpressionElement* ParserTests::GetPreprocessorAndExpressionElement(const Ast& ast,
    const int index) const {
    const PreprocessorAndExpression* preprocessorAndExpression = GetPreprocessorAndExpression(ast);
    
    if (preprocessorAndExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= preprocessorAndExpression->preprocessorAndExpressionElements.size()) {
        std::string string = std::to_string(index)
            + " >= preprocessorAndExpression->preprocessorAndExpressionElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &preprocessorAndExpression->preprocessorAndExpressionElements[index];
}

const PreprocessorNotExpression* ParserTests::GetPreprocessorNotExpression(const Ast& ast) const {
    const PreprocessorAndExpression* preprocessorAndExpression = GetPreprocessorAndExpression(ast);
    
    if (preprocessorAndExpression == nullptr) {
        return nullptr;
    }
    
    const PreprocessorNotExpression* preprocessorNotExpression =
        preprocessorAndExpression->preprocessorNotExpression.get();
    
    if (preprocessorNotExpression == nullptr) {
        QWARN("preprocessorNotExpression == nullptr");
        return nullptr;
    }
    
    return preprocessorNotExpression;
}

const PreprocessorNotExpressionElement* ParserTests::GetPreprocessorNotExpressionElement(const Ast& ast,
    const int index) const {
    const PreprocessorNotExpression* preprocessorNotExpression = GetPreprocessorNotExpression(ast);
    
    if (preprocessorNotExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= preprocessorNotExpression->preprocessorNotExpressionElements.size()) {
        std::string string = std::to_string(index)
            + " >= preprocessorNotExpression->preprocessorNotExpressionElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &preprocessorNotExpression->preprocessorNotExpressionElements[index];
}

const VariablesBlock* ParserTests::GetVariablesBlock(const Ast& ast) const {
    const BlockElement* blockElement = GetBlockElement(ast, 0);
    
    if (blockElement == nullptr) {
        return nullptr;
    }
    
    const VariablesBlock* variablesBlock = blockElement->variablesBlock.get();
    
    if (variablesBlock == nullptr) {
        QWARN("variablesBlock == nullptr");
        return nullptr;
    }
    
    return variablesBlock;
}

const VariablesBlockElement* ParserTests::GetVariablesBlockElement(const Ast& ast, const int index) const {
    const VariablesBlock* variablesBlock = GetVariablesBlock(ast);
    
    if (variablesBlock == nullptr) {
        return nullptr;
    }
    
    if (index >= variablesBlock->variablesBlockElements.size()) {
        std::string string = std::to_string(index) + " >= variablesBlock->variablesBlockElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &variablesBlock->variablesBlockElements[index];
}

const VariablesBlockElementElement* ParserTests::GetVariablesBlockElementElement(const Ast& ast,
    const int index) const {
    const VariablesBlockElement* variablesBlockElement = GetVariablesBlockElement(ast, 0);
    
    if (variablesBlockElement == nullptr) {
        return nullptr;
    }
    
    if (index >= variablesBlockElement->variablesBlockElementElements.size()) {
        std::string string = std::to_string(index) + " >= variablesBlockElement->variablesBlockElementElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &variablesBlockElement->variablesBlockElementElements[index];
}

const Variable* ParserTests::GetVariable(const Ast& ast) const {
    const VariablesBlockElement* variablesBlockElement = GetVariablesBlockElement(ast, 0);
    
    if (variablesBlockElement == nullptr) {
        return nullptr;
    }
    
    const Variable* variable = variablesBlockElement->variable.get();
    
    if (variable == nullptr) {
        QWARN("variable == nullptr");
        return nullptr;
    }
    
    return variable;
}

const FunctionsBlock* ParserTests::GetFunctionsBlock(const Ast& ast) const {
    const BlockElement* blockElement = GetBlockElement(ast, 0);
    
    if (blockElement == nullptr) {
        return nullptr;
    }
    
    const FunctionsBlock* functionsBlock = blockElement->functionsBlock.get();
    
    if (functionsBlock == nullptr) {
        QWARN("functionsBlock == nullptr");
        return nullptr;
    }
    
    return functionsBlock;
}

const FunctionsBlockElement* ParserTests::GetFunctionsBlockElement(const Ast& ast, const int index) const {
    const FunctionsBlock* functionsBlock = GetFunctionsBlock(ast);
    
    if (functionsBlock == nullptr) {
        return nullptr;
    }
    
    if (index >= functionsBlock->functionsBlockElements.size()) {
        std::string string = std::to_string(index) + " >= functionsBlock->functionsBlockElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &functionsBlock->functionsBlockElements[index];
}

const FunctionBlock* ParserTests::GetFunctionBlock(const Ast& ast) const {
    const FunctionsBlockElement* functionsBlockElement = GetFunctionsBlockElement(ast, 0);
    
    if (functionsBlockElement == nullptr) {
        return nullptr;
    }
    
    const FunctionBlock* functionBlock = functionsBlockElement->functionBlock.get();
    
    if (functionBlock == nullptr) {
        QWARN("functionBlock == nullptr");
        return nullptr;
    }
    
    return functionBlock;
}

const ProcedureBlock* ParserTests::GetProcedureBlock(const Ast& ast) const {
    const FunctionsBlockElement* functionsBlockElement = GetFunctionsBlockElement(ast, 0);
    
    if (functionsBlockElement == nullptr) {
        return nullptr;
    }
    
    const ProcedureBlock* procedureBlock = functionsBlockElement->procedureBlock.get();
    
    if (procedureBlock == nullptr) {
        QWARN("procedureBlock == nullptr");
        return nullptr;
    }
    
    return procedureBlock;
}

const DirectiveOfPreprocessor* ParserTests::GetDirectiveOfPreprocessor(const Ast& ast) const {
    const ProcedureBlock* procedureBlock = GetProcedureBlock(ast);
    
    if (procedureBlock == nullptr) {
        return nullptr;
    }
    
    const DirectiveOfPreprocessor* directiveOfPreprocessor = procedureBlock->directiveOfPreprocessor.get();
    
    if (directiveOfPreprocessor == nullptr) {
        QWARN("directiveOfPreprocessor == nullptr");
        return nullptr;
    }
    
    return directiveOfPreprocessor;
}

const Annotation* ParserTests::GetAnnotation(const Ast& ast) const {
    const DirectiveOfPreprocessor* directiveOfPreprocessor = GetDirectiveOfPreprocessor(ast);
    
    if (directiveOfPreprocessor == nullptr) {
        return nullptr;
    }
    
    const Annotation* annotation = directiveOfPreprocessor->annotation.get();
    
    if (annotation == nullptr) {
        QWARN("annotation == nullptr");
        return nullptr;
    }
    
    return annotation;
}

const FunctionArgumentsBlock* ParserTests::GetFunctionArgumentsBlock(const Ast& ast) const {
    const ProcedureBlock* procedureBlock = GetProcedureBlock(ast);
    
    if (procedureBlock == nullptr) {
        return nullptr;
    }
    
    const FunctionArgumentsBlock* functionArgumentsBlock = procedureBlock->functionArgumentsBlock.get();
    
    if (functionArgumentsBlock == nullptr) {
        QWARN("functionArgumentsBlock == nullptr");
        return nullptr;
    }
    
    return functionArgumentsBlock;
}

const FunctionArgumentsBlockElement* ParserTests::GetFunctionArgumentsBlockElement(const Ast& ast,
    const int index) const {
    const FunctionArgumentsBlock* functionArgumentsBlock = GetFunctionArgumentsBlock(ast);
    
    if (functionArgumentsBlock == nullptr) {
        return nullptr;
    }
    
    if (index >= functionArgumentsBlock->functionArgumentsBlockElements.size()) {
        std::string string = std::to_string(index)
            + " >= functionArgumentsBlock->functionArgumentsBlockElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &functionArgumentsBlock->functionArgumentsBlockElements[index];
}

const FunctionArgument* ParserTests::GetFunctionArgument(const Ast& ast) const {
    const FunctionArgumentsBlock* functionArgumentsBlock = GetFunctionArgumentsBlock(ast);
    
    if (functionArgumentsBlock == nullptr) {
        return nullptr;
    }
    
    const FunctionArgument* functionArgument = functionArgumentsBlock->functionArgument.get();
    
    if (functionArgument == nullptr) {
        QWARN("functionArgument == nullptr");
        return nullptr;
    }
    
    return functionArgument;
}

const Value* ParserTests::GetValue(const Ast& ast) const {
    const FunctionArgument* functionArgument = GetFunctionArgument(ast);
    
    if (functionArgument == nullptr) {
        return nullptr;
    }
    
    const Value* value = functionArgument->value.get();
    
    if (value == nullptr) {
        QWARN("value == nullptr");
        return nullptr;
    }
    
    return value;
}

const String* ParserTests::GetString(const Ast& ast) const {
    const Value* value = GetValue(ast);
    
    if (value == nullptr) {
        return nullptr;
    }
    
    const String* string = value->string.get();
    
    if (string == nullptr) {
        QWARN("string == nullptr");
        return nullptr;
    }
    
    return string;
}

const StringElement* ParserTests::GetStringElement(const Ast& ast, const int index) const {
    const String* string = GetString(ast);
    
    if (string == nullptr) {
        return nullptr;
    }
    
    if (index >= string->stringElements.size()) {
        std::string string = std::to_string(index) + " >= string->stringElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &string->stringElements[index];
}

const OperationsBlock* ParserTests::GetOperationsBlock(const Ast& ast) const {
    const BlockElement* blockElement = GetBlockElement(ast, 0);
    
    if (blockElement == nullptr) {
        return nullptr;
    }
    
    const OperationsBlock* operationsBlock = blockElement->operationsBlock.get();
    
    if (operationsBlock == nullptr) {
        QWARN("operationsBlock == nullptr");
        return nullptr;
    }
    
    return operationsBlock;
}

const OperationsBlockElement* ParserTests::GetOperationsBlockElement(const Ast& ast, const int index) const {
    const OperationsBlock* operationsBlock = GetOperationsBlock(ast);
    
    if (operationsBlock == nullptr) {
        return nullptr;
    }
    
    if (index >= operationsBlock->operationsBlockElements.size()) {
        std::string string = std::to_string(index) + " >= operationsBlock->operationsBlockElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &operationsBlock->operationsBlockElements[index];
}

const SettingStatement* ParserTests::GetSettingStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const SettingStatement* settingStatement = operationsBlockElement->settingStatement.get();
    
    if (settingStatement == nullptr) {
        QWARN("settingStatement == nullptr");
        return nullptr;
    }
    
    return settingStatement;
}

const MemberExpression* ParserTests::GetMemberExpression(const Ast& ast) const {
    const SettingStatement* settingStatement = GetSettingStatement(ast);
    
    if (settingStatement == nullptr) {
        return nullptr;
    }
    
    const MemberExpression* memberExpression = settingStatement->memberExpression.get();
    
    if (memberExpression == nullptr) {
        QWARN("memberExpression == nullptr");
        return nullptr;
    }
    
    return memberExpression;
}

const MemberMethodElement* ParserTests::GetMemberMethodElement(const Ast& ast, const int index) const {
    const MemberExpression* memberExpression = GetMemberExpression(ast);
    
    if (memberExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= memberExpression->memberMethodElements.size()) {
        std::string string = std::to_string(index) + " >= memberExpression->memberMethodElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &memberExpression->memberMethodElements[index];
}

const MemberMethodElementElement* ParserTests::GetMemberMethodElementElement(const Ast& ast) const {
    const MemberMethodElement* memberMethodElement = GetMemberMethodElement(ast, 0);
    
    if (memberMethodElement == nullptr) {
        return nullptr;
    }
    
    const MemberMethodElementElement* memberMethodElementElement =
        memberMethodElement->memberMethodElementElement.get();
    
    if (memberMethodElementElement == nullptr) {
        QWARN("memberMethodElementElement == nullptr");
        return nullptr;
    }
    
    return memberMethodElementElement;
}

const ArgumentsBlock* ParserTests::GetArgumentsBlock(const Ast& ast) const {
    const MemberMethodElementElement* memberMethodElementElement = GetMemberMethodElementElement(ast);
    
    if (memberMethodElementElement == nullptr) {
        return nullptr;
    }
    
    const ArgumentsBlock* argumentsBlock = memberMethodElementElement->argumentsBlock.get();
    
    if (argumentsBlock == nullptr) {
        QWARN("argumentsBlock == nullptr");
        return nullptr;
    }
    
    return argumentsBlock;
}

const ArgumentsBlockElement* ParserTests::GetArgumentsBlockElement(const Ast& ast, const int index) const {
    const ArgumentsBlock* argumentsBlock = GetArgumentsBlock(ast);
    
    if (argumentsBlock == nullptr) {
        return nullptr;
    }
    
    if (index >= argumentsBlock->argumentsBlockElements.size()) {
        std::string string = std::to_string(index) + " >= argumentsBlock->argumentsBlockElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &argumentsBlock->argumentsBlockElements[index];
}

const ArrayElement* ParserTests::GetArrayElement(const Ast& ast, const int index) const {
    const MemberExpression* memberExpression = GetMemberExpression(ast);
    
    if (memberExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= memberExpression->arrayElements.size()) {
        std::string string = std::to_string(index) + " >= memberExpression->arrayElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &memberExpression->arrayElements[index];
}

const MethodStatement* ParserTests::GetMethodStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const MethodStatement* methodStatement = operationsBlockElement->methodStatement.get();
    
    if (methodStatement == nullptr) {
        QWARN("methodStatement == nullptr");
        return nullptr;
    }
    
    return methodStatement;
}

const MethodExpression* ParserTests::GetMethodExpression(const Ast& ast) const {
    const MethodStatement* methodStatement = GetMethodStatement(ast);
    
    if (methodStatement == nullptr) {
        return nullptr;
    }
    
    const MethodExpression* methodExpression = methodStatement->methodExpression.get();
    
    if (methodExpression == nullptr) {
        QWARN("methodExpression == nullptr");
        return nullptr;
    }
    
    return methodExpression;
}

const ExecuteStatement* ParserTests::GetExecuteStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const ExecuteStatement* executeStatement = operationsBlockElement->executeStatement.get();
    
    if (executeStatement == nullptr) {
        QWARN("executeStatement == nullptr");
        return nullptr;
    }
    
    return executeStatement;
}

const ReturnStatement* ParserTests::GetReturnStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const ReturnStatement* returnStatement = operationsBlockElement->returnStatement.get();
    
    if (returnStatement == nullptr) {
        QWARN("returnStatement == nullptr");
        return nullptr;
    }
    
    return returnStatement;
}

const AwaitStatement* ParserTests::GetAwaitStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const AwaitStatement* awaitStatement = operationsBlockElement->awaitStatement.get();
    
    if (awaitStatement == nullptr) {
        QWARN("awaitStatement == nullptr");
        return nullptr;
    }
    
    return awaitStatement;
}

const AddHandlerStatement* ParserTests::GetAddHandlerStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const AddHandlerStatement* addHandlerStatement = operationsBlockElement->addHandlerStatement.get();
    
    if (addHandlerStatement == nullptr) {
        QWARN("addHandlerStatement == nullptr");
        return nullptr;
    }
    
    return addHandlerStatement;
}

const RemoveHandlerStatement* ParserTests::GetRemoveHandlerStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const RemoveHandlerStatement* removeHandlerStatement = operationsBlockElement->removeHandlerStatement.get();
    
    if (removeHandlerStatement == nullptr) {
        QWARN("removeHandlerStatement == nullptr");
        return nullptr;
    }
    
    return removeHandlerStatement;
}

const IfStatement* ParserTests::GetIfStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const IfStatement* ifStatement = operationsBlockElement->ifStatement.get();
    
    if (ifStatement == nullptr) {
        QWARN("ifStatement == nullptr");
        return nullptr;
    }
    
    return ifStatement;
}

const IfStatementElement* ParserTests::GetIfStatementElement(const Ast& ast, const int index) const {
    const IfStatement* ifStatement = GetIfStatement(ast);
    
    if (ifStatement == nullptr) {
        return nullptr;
    }
    
    if (index >= ifStatement->ifStatementElements.size()) {
        std::string string = std::to_string(index) + " >= ifStatement->ifStatementElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &ifStatement->ifStatementElements[index];
}

const ForToStatement* ParserTests::GetForToStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const ForToStatement* forToStatement = operationsBlockElement->forToStatement.get();
    
    if (forToStatement == nullptr) {
        QWARN("forToStatement == nullptr");
        return nullptr;
    }
    
    return forToStatement;
}

const ForEachStatement* ParserTests::GetForEachStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const ForEachStatement* forEachStatement = operationsBlockElement->forEachStatement.get();
    
    if (forEachStatement == nullptr) {
        QWARN("forEachStatement == nullptr");
        return nullptr;
    }
    
    return forEachStatement;
}

const WhileStatement* ParserTests::GetWhileStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const WhileStatement* whileStatement = operationsBlockElement->whileStatement.get();
    
    if (whileStatement == nullptr) {
        QWARN("whileStatement == nullptr");
        return nullptr;
    }
    
    return whileStatement;
}

const TryStatement* ParserTests::GetTryStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const TryStatement* tryStatement = operationsBlockElement->tryStatement.get();
    
    if (tryStatement == nullptr) {
        QWARN("tryStatement == nullptr");
        return nullptr;
    }
    
    return tryStatement;
}

const RaiseStatement* ParserTests::GetRaiseStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const RaiseStatement* raiseStatement = operationsBlockElement->raiseStatement.get();
    
    if (raiseStatement == nullptr) {
        QWARN("raiseStatement == nullptr");
        return nullptr;
    }
    
    return raiseStatement;
}

const LabelStatement* ParserTests::GetLabelStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const LabelStatement* labelStatement = operationsBlockElement->labelStatement.get();
    
    if (labelStatement == nullptr) {
        QWARN("labelStatement == nullptr");
        return nullptr;
    }
    
    return labelStatement;
}

const GotoStatement* ParserTests::GetGotoStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const GotoStatement* gotoStatement = operationsBlockElement->gotoStatement.get();
    
    if (gotoStatement == nullptr) {
        QWARN("gotoStatement == nullptr");
        return nullptr;
    }
    
    return gotoStatement;
}

const ContinueStatement* ParserTests::GetContinueStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const ContinueStatement* continueStatement = operationsBlockElement->continueStatement.get();
    
    if (continueStatement == nullptr) {
        QWARN("continueStatement == nullptr");
        return nullptr;
    }
    
    return continueStatement;
}

const BreakStatement* ParserTests::GetBreakStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const BreakStatement* breakStatement = operationsBlockElement->breakStatement.get();
    
    if (breakStatement == nullptr) {
        QWARN("breakStatement == nullptr");
        return nullptr;
    }
    
    return breakStatement;
}

const SemicolonStatement* ParserTests::GetSemicolonStatement(const Ast& ast) const {
    const OperationsBlockElement* operationsBlockElement = GetOperationsBlockElement(ast, 0);
    
    if (operationsBlockElement == nullptr) {
        return nullptr;
    }
    
    const SemicolonStatement* semicolonStatement = operationsBlockElement->semicolonStatement.get();
    
    if (semicolonStatement == nullptr) {
        QWARN("semicolonStatement == nullptr");
        return nullptr;
    }
    
    return semicolonStatement;
}

const InitialExpression* ParserTests::GetInitialExpression(const Ast& ast) const {
    const SettingStatement* settingStatement = GetSettingStatement(ast);
    
    if (settingStatement == nullptr) {
        return nullptr;
    }
    
    const InitialExpression* initialExpression = settingStatement->initialExpression.get();
    
    if (initialExpression == nullptr) {
        QWARN("initialExpression == nullptr");
        return nullptr;
    }
    
    return initialExpression;
}

const Expression* ParserTests::GetExpression(const Ast& ast) const {
    const InitialExpression* initialExpression = GetInitialExpression(ast);
    
    if (initialExpression == nullptr) {
        return nullptr;
    }
    
    const Expression* expression = initialExpression->expression.get();
    
    if (expression == nullptr) {
        QWARN("expression == nullptr");
        return nullptr;
    }
    
    return expression;
}

const ExpressionElement* ParserTests::GetExpressionElement(const Ast& ast, const int index) const {
    const Expression* expression = GetExpression(ast);
    
    if (expression == nullptr) {
        return nullptr;
    }
    
    if (index >= expression->expressionElements.size()) {
        std::string string = std::to_string(index) + " >= expression->expressionElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &expression->expressionElements[index];
}

const PrimeExpression* ParserTests::GetPrimeExpression(const Ast& ast) const {
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return nullptr;
    }
    
    const PrimeExpression* primeExpression = signExpression->primeExpression.get();
    
    if (primeExpression == nullptr) {
        QWARN("primeExpression == nullptr");
        return nullptr;
    }
    
    return primeExpression;
}

const ExpressionInParenthesis* ParserTests::GetExpressionInParenthesis(const Ast& ast) const {
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return nullptr;
    }
    
    const ExpressionInParenthesis* expressionInParenthesis = primeExpression->expressionInParenthesis.get();
    
    if (expressionInParenthesis == nullptr) {
        QWARN("expressionInParenthesis == nullptr");
        return nullptr;
    }
    
    return expressionInParenthesis;
}

const MemberMethod* ParserTests::GetMemberMethod(const Ast& ast) const {
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return nullptr;
    }
    
    const MemberMethod* memberMethod = primeExpression->memberMethod.get();
    
    if (memberMethod == nullptr) {
        QWARN("memberMethod == nullptr");
        return nullptr;
    }
    
    return memberMethod;
}

const NewElement* ParserTests::GetNewElement(const Ast& ast) const {
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return nullptr;
    }
    
    const NewElement* newElement = primeExpression->newElement.get();
    
    if (newElement == nullptr) {
        QWARN("newElement == nullptr");
        return nullptr;
    }
    
    return newElement;
}

const NewArgumentsBlock* ParserTests::GetNewArgumentsBlock(const Ast& ast) const {
    const NewElement* newElement = GetNewElement(ast);
    
    if (newElement == nullptr) {
        return nullptr;
    }
    
    const NewArgumentsBlock* newArgumentsBlock = newElement->newArgumentsBlock.get();
    
    if (newArgumentsBlock == nullptr) {
        QWARN("newArgumentsBlock == nullptr");
        return nullptr;
    }
    
    return newArgumentsBlock;
}

const TernaryOperationElement* ParserTests::GetTernaryOperationElement(const Ast& ast) const {
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return nullptr;
    }
    
    const TernaryOperationElement* ternaryOperationElement = primeExpression->ternaryOperationElement.get();
    
    if (ternaryOperationElement == nullptr) {
        QWARN("ternaryOperationElement == nullptr");
        return nullptr;
    }
    
    return ternaryOperationElement;
}

const AwaitElement* ParserTests::GetAwaitElement(const Ast& ast) const {
    const PrimeExpression* primeExpression = GetPrimeExpression(ast);
    
    if (primeExpression == nullptr) {
        return nullptr;
    }
    
    const AwaitElement* awaitElement = primeExpression->awaitElement.get();
    
    if (awaitElement == nullptr) {
        QWARN("awaitElement == nullptr");
        return nullptr;
    }
    
    return awaitElement;
}

const AndExpression* ParserTests::GetAndExpression(const Ast& ast) const {
    const Expression* expression = GetExpression(ast);
    
    if (expression == nullptr) {
        return nullptr;
    }
    
    const AndExpression* andExpression = expression->andExpression.get();
    
    if (andExpression == nullptr) {
        QWARN("andExpression == nullptr");
        return nullptr;
    }
    
    return andExpression;
}

const AndExpressionElement* ParserTests::GetAndExpressionElement(const Ast& ast, const int index) const {
    const AndExpression* andExpression = GetAndExpression(ast);
    
    if (andExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= andExpression->andExpressionElements.size()) {
        std::string string = std::to_string(index) + " >= andExpression->andExpressionElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &andExpression->andExpressionElements[index];
}

const NotExpression* ParserTests::GetNotExpression(const Ast& ast) const {
    const AndExpression* andExpression = GetAndExpression(ast);
    
    if (andExpression == nullptr) {
        return nullptr;
    }
    
    const NotExpression* notExpression = andExpression->notExpression.get();
    
    if (notExpression == nullptr) {
        QWARN("notExpression == nullptr");
        return nullptr;
    }
    
    return notExpression;
}

const NotExpressionElement* ParserTests::GetNotExpressionElement(const Ast& ast, const int index) const {
    const NotExpression* notExpression = GetNotExpression(ast);
    
    if (notExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= notExpression->notExpressionElements.size()) {
        std::string string = std::to_string(index) + " >= notExpression->notExpressionElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &notExpression->notExpressionElements[index];
}

const RelationalExpression* ParserTests::GetRelationalExpression(const Ast& ast) const {
    const NotExpression* notExpression = GetNotExpression(ast);
    
    if (notExpression == nullptr) {
        return nullptr;
    }
    
    const RelationalExpression* relationalExpression = notExpression->relationalExpression.get();
    
    if (relationalExpression == nullptr) {
        QWARN("relationalExpression == nullptr");
        return nullptr;
    }
    
    return relationalExpression;
}

const RelationalExpressionElement* ParserTests::GetRelationalExpressionElement(const Ast& ast, const int index) const {
    const RelationalExpression* relationalExpression = GetRelationalExpression(ast);
    
    if (relationalExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= relationalExpression->relationalExpressionElements.size()) {
        std::string string = std::to_string(index) + " >= relationalExpression->relationalExpressionElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &relationalExpression->relationalExpressionElements[index];
}

const AddingExpression* ParserTests::GetAddingExpression(const Ast& ast) const {
    const RelationalExpression* relationalExpression = GetRelationalExpression(ast);
    
    if (relationalExpression == nullptr) {
        return nullptr;
    }
    
    const AddingExpression* addingExpression = relationalExpression->addingExpression.get();
    
    if (addingExpression == nullptr) {
        QWARN("addingExpression == nullptr");
        return nullptr;
    }
    
    return addingExpression;
}

const AddingExpressionElement* ParserTests::GetAddingExpressionElement(const Ast& ast, const int index) const {
    const AddingExpression* addingExpression = GetAddingExpression(ast);
    
    if (addingExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= addingExpression->addingExpressionElements.size()) {
        std::string string = std::to_string(index) + " >= addingExpression->addingExpressionElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &addingExpression->addingExpressionElements[index];
}

const MultiplyingExpression* ParserTests::GetMultiplyingExpression(const Ast& ast) const {
    const AddingExpression* addingExpression = GetAddingExpression(ast);
    
    if (addingExpression == nullptr) {
        return nullptr;
    }
    
    const MultiplyingExpression* multiplyingExpression = addingExpression->multiplyingExpression.get();
    
    if (multiplyingExpression == nullptr) {
        QWARN("multiplyingExpression == nullptr");
        return nullptr;
    }
    
    return multiplyingExpression;
}

const MultiplyingExpressionElement* ParserTests::GetMultiplyingExpressionElement(const Ast& ast,
    const int index) const {
    const MultiplyingExpression* multiplyingExpression = GetMultiplyingExpression(ast);
    
    if (multiplyingExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= multiplyingExpression->multiplyingExpressionElements.size()) {
        std::string string = std::to_string(index) + " >= multiplyingExpression->multiplyingExpressionElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &multiplyingExpression->multiplyingExpressionElements[index];
}

const SignExpression* ParserTests::GetSignExpression(const Ast& ast) const {
    const MultiplyingExpression* multiplyingExpression = GetMultiplyingExpression(ast);
    
    if (multiplyingExpression == nullptr) {
        return nullptr;
    }
    
    const SignExpression* signExpression = multiplyingExpression->signExpression.get();
    
    if (signExpression == nullptr) {
        QWARN("signExpression == nullptr");
        return nullptr;
    }
    
    return signExpression;
}

const SignExpressionElement* ParserTests::GetSignExpressionElement(const Ast& ast, const int index) const {
    const SignExpression* signExpression = GetSignExpression(ast);
    
    if (signExpression == nullptr) {
        return nullptr;
    }
    
    if (index >= signExpression->signExpressionElements.size()) {
        std::string string = std::to_string(index) + " >= signExpression->signExpressionElements.size()";
        QWARN(string.c_str());
        return nullptr;
    }
    
    return &signExpression->signExpressionElements[index];
}
