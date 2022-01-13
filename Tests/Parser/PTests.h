#ifndef SYNTAX_TOOLS_PARSER_P_TESTS_H
#define SYNTAX_TOOLS_PARSER_P_TESTS_H

#include <string>

#include <QObject>
#include <QtTest/QtTest>

#include "../../SyntaxTools/Lexer/Lexer.h"
#include "../../SyntaxTools/Parser/Parser.h"

using namespace syntax_tools;

class ParserTests: public QObject {
    Q_OBJECT

public:
    ~ParserTests();
    
    void TestAst() const;
    void TestBlock() const;
    
    void TestBlockElement() const;
    void TestBlockElementPreprocessorRegionBlock() const;
    void TestBlockElementPreprocessorIfBlock() const;
    void TestBlockElementVariablesBlock() const;
    void TestBlockElementFunctionsBlock() const;
    void TestBlockElementOperationsBlock() const;
    
    void TestPreprocessorRegionBlock() const;
    void TestPreprocessorIfBlock() const;
    void TestPreprocessorIfBlockElement() const;
    void TestPreprocessorExpression() const;
    void TestPreprocessorExpressionElement() const;
    
    void TestPreprocessorPrimeExpression() const;
    void TestPreprocessorPrimeExpressionValue() const;
    void TestPreprocessorPrimeExpressionExpressionInParenthesis() const;
    
    void TestPreprocessorValue() const;
    void TestPreprocessorValueClient() const;
    void TestPreprocessorValueAtClient() const;
    void TestPreprocessorValueAtServer() const;
    void TestPreprocessorValueMobileAppClient() const;
    void TestPreprocessorValueMobileAppServer() const;
    void TestPreprocessorValueThickClientOrdinaryApplication() const;
    void TestPreprocessorValueThickClientManagedApplication() const;
    void TestPreprocessorValueServer() const;
    void TestPreprocessorValueExternalConnection() const;
    void TestPreprocessorValueThinClient() const;
    void TestPreprocessorValueWebClient() const;
    
    void TestPreprocessorAndExpression() const;
    void TestPreprocessorAndExpressionElement() const;
    void TestPreprocessorNotExpression() const;
    void TestPreprocessorNotExpressionElement() const;
    void TestVariablesBlock() const;
    void TestVariablesBlockElement() const;
    void TestVariablesBlockElementElement() const;
    void TestVariable() const;
    void TestFunctionsBlock() const;
    
    void TestFunctionsBlockElement() const;
    void TestFunctionsBlockElementFunctionBlock() const;
    void TestFunctionsBlockElementProcedureBlock() const;
    
    void TestFunctionBlock() const;
    void TestProcedureBlock() const;
    
    void TestDirectiveOfPreprocessor() const;
    void TestDirectiveOfPreprocessorDirectiveAtClient() const;
    void TestDirectiveOfPreprocessorDirectiveAtServer() const;
    void TestDirectiveOfPreprocessorDirectiveAtServerNoContext() const;
    void TestDirectiveOfPreprocessorDirectiveAtClientAtServerNoContext() const;
    void TestDirectiveOfPreprocessorDirectiveAtClientAtServer() const;
    void TestDirectiveOfPreprocessorAnnotation() const;
    
    void TestAnnotation() const;
    void TestAnnotationDirectiveBefore() const;
    void TestAnnotationDirectiveAfter() const;
    void TestAnnotationDirectiveInstead() const;
    
    void TestFunctionArgumentsBlock() const;
    void TestFunctionArgumentsBlockElement() const;
    void TestFunctionArgument() const;
    
    void TestValue() const;
    void TestValueSignedFloat() const;
    void TestValueFloat() const;
    void TestValueDate() const;
    void TestValueNull() const;
    void TestValueUndefined() const;
    void TestValueFalse() const;
    void TestValueTrue() const;
    void TestValueString() const;
    
    void TestString() const;
    void TestStringOneLine() const;
    void TestStringSeveralLines() const;
    
    void TestStringElement() const;
    void TestOperationsBlock() const;
    
    void TestOperationsBlockElement() const;
    void TestOperationsBlockElementSettingStatement() const;
    void TestOperationsBlockElementMethodStatement() const;
    void TestOperationsBlockElementExecuteStatement() const;
    void TestOperationsBlockElementReturnStatement() const;
    void TestOperationsBlockElementAwaitStatement() const;
    void TestOperationsBlockElementAddHandlerStatement() const;
    void TestOperationsBlockElementRemoveHandlerStatement() const;
    void TestOperationsBlockElementIfStatement() const;
    void TestOperationsBlockElementForToStatement() const;
    void TestOperationsBlockElementForEachStatement() const;
    void TestOperationsBlockElementWhileStatement() const;
    void TestOperationsBlockElementTryStatement() const;
    void TestOperationsBlockElementRaiseStatement() const;
    void TestOperationsBlockElementLabelStatement() const;
    void TestOperationsBlockElementGotoStatement() const;
    void TestOperationsBlockElementContinueStatement() const;
    void TestOperationsBlockElementBreakStatement() const;
    void TestOperationsBlockElementSemicolonStatement() const;
    
    void TestSettingStatement() const;
    void TestMemberExpression() const;
    void TestMemberMethodElement() const;
    void TestMemberMethodElementElement() const;
    void TestArgumentsBlock() const;
    void TestArgumentsBlockElement() const;
    void TestArrayElement() const;
    void TestMethodStatement() const;
    void TestMethodExpression() const;
    void TestExecuteStatement() const;
    void TestReturnStatement() const;
    void TestAwaitStatement() const;
    void TestAddHandlerStatement() const;
    void TestRemoveHandlerStatement() const;
    void TestIfStatement() const;
    void TestIfStatementElement() const;
    void TestForToStatement() const;
    void TestForEachStatement() const;
    void TestWhileStatement() const;
    void TestTryStatement() const;
    void TestRaiseStatement() const;
    void TestLabelStatement() const;
    void TestGotoStatement() const;
    void TestContinueStatement() const;
    void TestBreakStatement() const;
    void TestSemicolonStatement() const;
    void TestInitialExpression() const;
    void TestExpression() const;
    void TestExpressionElement() const;
    
    void TestPrimeExpression() const;
    void TestPrimeExpressionValue() const;
    void TestPrimeExpressionExpressionInParenthesis() const;
    void TestPrimeExpressionMemberMethod() const;
    void TestPrimeExpressionNewElement() const;
    void TestPrimeExpressionTernaryOperationElement() const;
    void TestPrimeExpressionAwaitElement() const;
    
    void TestExpressionInParenthesis() const;
    void TestMemberMethod() const;
    
    void TestNewElement() const;
    void TestNewElementWithIdentifier() const;
    void TestNewElementWithoutIdentifier() const;
    
    void TestNewArgumentsBlock() const;
    void TestTernaryOperationElement() const;
    void TestAwaitElement() const;
    void TestAndExpression() const;
    void TestAndExpressionElement() const;
    void TestNotExpression() const;
    void TestNotExpressionElement() const;
    void TestRelationalExpression() const;
    
    void TestRelationalExpressionElement() const;
    void TestRelationalExpressionElementEquals() const;
    void TestRelationalExpressionElementNotEquals() const;
    void TestRelationalExpressionElementLess() const;
    void TestRelationalExpressionElementLessOrEquals() const;
    void TestRelationalExpressionElementGreater() const;
    void TestRelationalExpressionElementGreaterOrEquals() const;
    
    void TestAddingExpression() const;
    
    void TestAddingExpressionElement() const;
    void TestAddingExpressionElementMinus() const;
    void TestAddingExpressionElementPlus() const;
    
    void TestMultiplyingExpression() const;
    
    void TestMultiplyingExpressionElement() const;
    void TestMultiplyingExpressionElementAsterisk() const;
    void TestMultiplyingExpressionElementSolidus() const;
    void TestMultiplyingExpressionElementPercent() const;
    
    void TestSignExpression() const;
    
    void TestSignExpressionElement() const;
    void TestSignExpressionElementMinus() const;
    void TestSignExpressionElementPlus() const;

private:
    bool FillAst(const std::wstring& string, Ast& ast) const;
    void VerifyAstNode(const AstNode& astNode, const AstNodeType type, const void* prnt, const int index,
        const int chrPos, const int numOfChrs, const int tknPos, const int numOfTkns) const;
    void VerifyToken(const AstToken& token, const TokenType type, const void* prnt, const int chrPos,
        const int numOfChrs, const int tknPos) const;
    
    const Block* GetBlock(const Ast& ast) const;
    const BlockElement* GetBlockElement(const Ast& ast, const int index) const;
    const PreprocessorRegionBlock* GetPreprocessorRegionBlock(const Ast& ast) const;
    const PreprocessorIfBlock* GetPreprocessorIfBlock(const Ast& ast) const;
    const PreprocessorIfBlockElement* GetPreprocessorIfBlockElement(const Ast& ast, const int index) const;
    const PreprocessorExpression* GetPreprocessorExpression(const Ast& ast) const;
    const PreprocessorExpressionElement* GetPreprocessorExpressionElement(const Ast& ast, const int index) const;
    const PreprocessorPrimeExpression* GetPreprocessorPrimeExpression(const Ast& ast) const;
    const PreprocessorValue* GetPreprocessorValue(const Ast& ast) const;
    const PreprocessorAndExpression* GetPreprocessorAndExpression(const Ast& ast) const;
    const PreprocessorAndExpressionElement* GetPreprocessorAndExpressionElement(const Ast& ast, const int index) const;
    const PreprocessorNotExpression* GetPreprocessorNotExpression(const Ast& ast) const;
    const PreprocessorNotExpressionElement* GetPreprocessorNotExpressionElement(const Ast& ast, const int index) const;
    const VariablesBlock* GetVariablesBlock(const Ast& ast) const;
    const VariablesBlockElement* GetVariablesBlockElement(const Ast& ast, const int index) const;
    const VariablesBlockElementElement* GetVariablesBlockElementElement(const Ast& ast, const int index) const;
    const Variable* GetVariable(const Ast& ast) const;
    const FunctionsBlock* GetFunctionsBlock(const Ast& ast) const;
    const FunctionsBlockElement* GetFunctionsBlockElement(const Ast& ast, const int index) const;
    const FunctionBlock* GetFunctionBlock(const Ast& ast) const;
    const ProcedureBlock* GetProcedureBlock(const Ast& ast) const;
    const DirectiveOfPreprocessor* GetDirectiveOfPreprocessor(const Ast& ast) const;
    const Annotation* GetAnnotation(const Ast& ast) const;
    const FunctionArgumentsBlock* GetFunctionArgumentsBlock(const Ast& ast) const;
    const FunctionArgumentsBlockElement* GetFunctionArgumentsBlockElement(const Ast& ast, const int index) const;
    const FunctionArgument* GetFunctionArgument(const Ast& ast) const;
    const Value* GetValue(const Ast& ast) const;
    const String* GetString(const Ast& ast) const;
    const StringElement* GetStringElement(const Ast& ast, const int index) const;
    const OperationsBlock* GetOperationsBlock(const Ast& ast) const;
    const OperationsBlockElement* GetOperationsBlockElement(const Ast& ast, const int index) const;
    const SettingStatement* GetSettingStatement(const Ast& ast) const;
    const MemberExpression* GetMemberExpression(const Ast& ast) const;
    const MemberMethodElement* GetMemberMethodElement(const Ast& ast, const int index) const;
    const MemberMethodElementElement* GetMemberMethodElementElement(const Ast& ast) const;
    const ArgumentsBlock* GetArgumentsBlock(const Ast& ast) const;
    const ArgumentsBlockElement* GetArgumentsBlockElement(const Ast& ast, const int index) const;
    const ArrayElement* GetArrayElement(const Ast& ast, const int index) const;
    const MethodStatement* GetMethodStatement(const Ast& ast) const;
    const MethodExpression* GetMethodExpression(const Ast& ast) const;
    const ExecuteStatement* GetExecuteStatement(const Ast& ast) const;
    const ReturnStatement* GetReturnStatement(const Ast& ast) const;
    const AwaitStatement* GetAwaitStatement(const Ast& ast) const;
    const AddHandlerStatement* GetAddHandlerStatement(const Ast& ast) const;
    const RemoveHandlerStatement* GetRemoveHandlerStatement(const Ast& ast) const;
    const IfStatement* GetIfStatement(const Ast& ast) const;
    const IfStatementElement* GetIfStatementElement(const Ast& ast, const int index) const;
    const ForToStatement* GetForToStatement(const Ast& ast) const;
    const ForEachStatement* GetForEachStatement(const Ast& ast) const;
    const WhileStatement* GetWhileStatement(const Ast& ast) const;
    const TryStatement* GetTryStatement(const Ast& ast) const;
    const RaiseStatement* GetRaiseStatement(const Ast& ast) const;
    const LabelStatement* GetLabelStatement(const Ast& ast) const;
    const GotoStatement* GetGotoStatement(const Ast& ast) const;
    const ContinueStatement* GetContinueStatement(const Ast& ast) const;
    const BreakStatement* GetBreakStatement(const Ast& ast) const;
    const SemicolonStatement* GetSemicolonStatement(const Ast& ast) const;
    const InitialExpression* GetInitialExpression(const Ast& ast) const;
    const Expression* GetExpression(const Ast& ast) const;
    const ExpressionElement* GetExpressionElement(const Ast& ast, const int index) const;
    const PrimeExpression* GetPrimeExpression(const Ast& ast) const;
    const ExpressionInParenthesis* GetExpressionInParenthesis(const Ast& ast) const;
    const MemberMethod* GetMemberMethod(const Ast& ast) const;
    const NewElement* GetNewElement(const Ast& ast) const;
    const NewArgumentsBlock* GetNewArgumentsBlock(const Ast& ast) const;
    const TernaryOperationElement* GetTernaryOperationElement(const Ast& ast) const;
    const AwaitElement* GetAwaitElement(const Ast& ast) const;
    const AndExpression* GetAndExpression(const Ast& ast) const;
    const AndExpressionElement* GetAndExpressionElement(const Ast& ast, const int index) const;
    const NotExpression* GetNotExpression(const Ast& ast) const;
    const NotExpressionElement* GetNotExpressionElement(const Ast& ast, const int index) const;
    const RelationalExpression* GetRelationalExpression(const Ast& ast) const;
    const RelationalExpressionElement* GetRelationalExpressionElement(const Ast& ast, const int index) const;
    const AddingExpression* GetAddingExpression(const Ast& ast) const;
    const AddingExpressionElement* GetAddingExpressionElement(const Ast& ast, const int index) const;
    const MultiplyingExpression* GetMultiplyingExpression(const Ast& ast) const;
    const MultiplyingExpressionElement* GetMultiplyingExpressionElement(const Ast& ast, const int index) const;
    const SignExpression* GetSignExpression(const Ast& ast) const;
    const SignExpressionElement* GetSignExpressionElement(const Ast& ast, const int index) const;
};

#endif
