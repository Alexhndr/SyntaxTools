#include "Tests.h"

void Tests::TestLexer() const {
    LexerTests lexerTests;
    lexerTests.Test();
}

void Tests::TestParser() const {
    ParserTests parserTests;
    
    parserTests.TestAst();
    parserTests.TestBlock();
    parserTests.TestBlockElement();
    parserTests.TestPreprocessorRegionBlock();
    parserTests.TestPreprocessorIfBlock();
    parserTests.TestPreprocessorIfBlockElement();
    parserTests.TestPreprocessorExpression();
    parserTests.TestPreprocessorExpressionElement();
    parserTests.TestPreprocessorPrimeExpression();
    parserTests.TestPreprocessorValue();
    parserTests.TestPreprocessorAndExpression();
    parserTests.TestPreprocessorAndExpressionElement();
    parserTests.TestPreprocessorNotExpression();
    parserTests.TestPreprocessorNotExpressionElement();
    parserTests.TestVariablesBlock();
    parserTests.TestVariablesBlockElement();
    parserTests.TestVariablesBlockElementElement();
    parserTests.TestVariable();
    parserTests.TestFunctionsBlock();
    parserTests.TestFunctionsBlockElement();
    parserTests.TestFunctionBlock();
    parserTests.TestProcedureBlock();
    parserTests.TestDirectiveOfPreprocessor();
    parserTests.TestAnnotation();
    parserTests.TestFunctionArgumentsBlock();
    parserTests.TestFunctionArgumentsBlockElement();
    parserTests.TestFunctionArgument();
    parserTests.TestValue();
    parserTests.TestString();
    parserTests.TestStringElement();
    parserTests.TestOperationsBlock();
    parserTests.TestOperationsBlockElement();
    parserTests.TestSettingStatement();
    parserTests.TestMemberExpression();
    parserTests.TestMemberMethodElement();
    parserTests.TestMemberMethodElementElement();
    parserTests.TestArgumentsBlock();
    parserTests.TestArgumentsBlockElement();
    parserTests.TestArrayElement();
    parserTests.TestMethodStatement();
    parserTests.TestMethodExpression();
    parserTests.TestExecuteStatement();
    parserTests.TestReturnStatement();
    parserTests.TestAwaitStatement();
    parserTests.TestAddHandlerStatement();
    parserTests.TestRemoveHandlerStatement();
    parserTests.TestIfStatement();
    parserTests.TestIfStatementElement();
    parserTests.TestForToStatement();
    parserTests.TestForEachStatement();
    parserTests.TestWhileStatement();
    parserTests.TestTryStatement();
    parserTests.TestRaiseStatement();
    parserTests.TestLabelStatement();
    parserTests.TestGotoStatement();
    parserTests.TestContinueStatement();
    parserTests.TestBreakStatement();
    parserTests.TestSemicolonStatement();
    parserTests.TestInitialExpression();
    parserTests.TestExpression();
    parserTests.TestExpressionElement();
    parserTests.TestPrimeExpression();
    parserTests.TestExpressionInParenthesis();
    parserTests.TestMemberMethod();
    parserTests.TestNewElement();
    parserTests.TestNewArgumentsBlock();
    parserTests.TestTernaryOperationElement();
    parserTests.TestAwaitElement();
    parserTests.TestAndExpression();
    parserTests.TestAndExpressionElement();
    parserTests.TestNotExpression();
    parserTests.TestNotExpressionElement();
    parserTests.TestRelationalExpression();
    parserTests.TestRelationalExpressionElement();
    parserTests.TestAddingExpression();
    parserTests.TestAddingExpressionElement();
    parserTests.TestMultiplyingExpression();
    parserTests.TestMultiplyingExpressionElement();
    parserTests.TestSignExpression();
    parserTests.TestSignExpressionElement();
}

QTEST_APPLESS_MAIN(Tests)
