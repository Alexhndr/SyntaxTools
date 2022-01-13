#ifndef SYNTAX_TOOLS_PARSER_P_RULES_H
#define SYNTAX_TOOLS_PARSER_P_RULES_H

#include <memory>
#include <utility>
#include <vector>

#include "../Common/AstNodes.h"
#include "PHelpers.h"

using namespace syntax_tools;

class PRule: public PHelper {
public:
    ~PRule();
    bool Check(PStream& stream) override;
    virtual bool CheckAstNode(PStream& stream) = 0;
};

class PrBlock;
class PrBlockElement;
class PrPreprocessorRegionBlock;
class PrPreprocessorIfBlock;
class PrPreprocessorIfBlockElement;
class PrPreprocessorExpression;
class PrPreprocessorExpressionElement;
class PrPreprocessorPrimeExpression;
class PrPreprocessorValue;
class PrPreprocessorAndExpression;
class PrPreprocessorAndExpressionElement;
class PrPreprocessorNotExpression;
class PrPreprocessorNotExpressionElement;
class PrVariablesBlock;
class PrVariablesBlockElement;
class PrVariablesBlockElementElement;
class PrVariable;
class PrFunctionsBlock;
class PrFunctionsBlockElement;
class PrFunctionBlock;
class PrProcedureBlock;
class PrDirectiveOfPreprocessor;
class PrAnnotation;
class PrFunctionArgumentsBlock;
class PrFunctionArgumentsBlockElement;
class PrFunctionArgument;
class PrValue;
class PrString;
class PrStringElement;
class PrOperationsBlock;
class PrOperationsBlockElement;
class PrSettingStatement;
class PrMemberExpression;
class PrMemberMethodElement;
class PrMemberMethodElementElement;
class PrArgumentsBlock;
class PrArgumentsBlockElement;
class PrArrayElement;
class PrMethodStatement;
class PrMethodExpression;
class PrExecuteStatement;
class PrReturnStatement;
class PrAwaitStatement;
class PrAddHandlerStatement;
class PrRemoveHandlerStatement;
class PrIfStatement;
class PrIfStatementElement;
class PrForToStatement;
class PrForEachStatement;
class PrWhileStatement;
class PrTryStatement;
class PrRaiseStatement;
class PrLabelStatement;
class PrGotoStatement;
class PrContinueStatement;
class PrBreakStatement;
class PrSemicolonStatement;
class PrInitialExpression;
class PrExpression;
class PrExpressionElement;
class PrPrimeExpression;
class PrExpressionInParenthesis;
class PrMemberMethod;
class PrNewElement;
class PrNewArgumentsBlock;
class PrTernaryOperationElement;
class PrAwaitElement;
class PrAndExpression;
class PrAndExpressionElement;
class PrNotExpression;
class PrNotExpressionElement;
class PrRelationalExpression;
class PrRelationalExpressionElement;
class PrAddingExpression;
class PrAddingExpressionElement;
class PrMultiplyingExpression;
class PrMultiplyingExpressionElement;
class PrSignExpression;
class PrSignExpressionElement;

class PrBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<Block> GetBlock(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<Block> block;
};

class PrBlockElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<BlockElement> GetBlockElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<BlockElement> blockElement;
};

class PrPreprocessorRegionBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorRegionBlock> GetPreprocessorRegionBlock(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorRegionBlock> preprocessorRegionBlock;
};

class PrPreprocessorIfBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorIfBlock> GetPreprocessorIfBlock(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorIfBlock> preprocessorIfBlock;
};

class PrPreprocessorIfBlockElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorIfBlockElement> GetPreprocessorIfBlockElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorIfBlockElement> preprocessorIfBlockElement;
};

class PrPreprocessorExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorExpression> GetPreprocessorExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorExpression> preprocessorExpression;
};

class PrPreprocessorExpressionElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorExpressionElement> GetPreprocessorExpressionElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorExpressionElement> preprocessorExpressionElement;
};

class PrPreprocessorPrimeExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorPrimeExpression> GetPreprocessorPrimeExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorPrimeExpression> preprocessorPrimeExpression;
};

class PrPreprocessorValue final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorValue> GetPreprocessorValue(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorValue> preprocessorValue;
};

class PrPreprocessorAndExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorAndExpression> GetPreprocessorAndExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorAndExpression> preprocessorAndExpression;
};

class PrPreprocessorAndExpressionElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorAndExpressionElement> GetPreprocessorAndExpressionElement(void* prnt,
        int index);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorAndExpressionElement> preprocessorAndExpressionElement;
};

class PrPreprocessorNotExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorNotExpression> GetPreprocessorNotExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorNotExpression> preprocessorNotExpression;
};

class PrPreprocessorNotExpressionElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PreprocessorNotExpressionElement> GetPreprocessorNotExpressionElement(void* prnt,
        int index);
    void Reset() override;

private:
    std::unique_ptr<PreprocessorNotExpressionElement> preprocessorNotExpressionElement;
};

class PrVariablesBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<VariablesBlock> GetVariablesBlock(void* prnt);
    void Reset() override;
    
private:
    std::unique_ptr<VariablesBlock> variablesBlock;
};

class PrVariablesBlockElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<VariablesBlockElement> GetVariablesBlockElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<VariablesBlockElement> variablesBlockElement;
};

class PrVariablesBlockElementElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<VariablesBlockElementElement> GetVariablesBlockElementElement(void* prnt, int index);
    void Reset() override;
    
private:
    std::unique_ptr<VariablesBlockElementElement> variablesBlockElementElement;
};

class PrVariable final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<Variable> GetVariable(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<Variable> variable;
};

class PrFunctionsBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<FunctionsBlock> GetFunctionsBlock(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<FunctionsBlock> functionsBlock;
};

class PrFunctionsBlockElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<FunctionsBlockElement> GetFunctionsBlockElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<FunctionsBlockElement> functionsBlockElement;
};

class PrFunctionBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<FunctionBlock> GetFunctionBlock(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<FunctionBlock> functionBlock;
};

class PrProcedureBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ProcedureBlock> GetProcedureBlock(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<ProcedureBlock> procedureBlock;
};

class PrDirectiveOfPreprocessor final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<DirectiveOfPreprocessor> GetDirectiveOfPreprocessor(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<DirectiveOfPreprocessor> directiveOfPreprocessor;
};

class PrAnnotation final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<Annotation> GetAnnotation(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<Annotation> annotation;
};

class PrFunctionArgumentsBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<FunctionArgumentsBlock> GetFunctionArgumentsBlock(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<FunctionArgumentsBlock> functionArgumentsBlock;
};

class PrFunctionArgumentsBlockElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<FunctionArgumentsBlockElement> GetFunctionArgumentsBlockElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<FunctionArgumentsBlockElement> functionArgumentsBlockElement;
};

class PrFunctionArgument final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<FunctionArgument> GetFunctionArgument(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<FunctionArgument> functionArgument;
};

class PrValue final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<Value> GetValue(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<Value> value;
};

class PrString final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<String> GetString(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<String> string;
};

class PrStringElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<StringElement> GetStringElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<StringElement> stringElement;
};

class PrOperationsBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<OperationsBlock> GetOperationsBlock(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<OperationsBlock> operationsBlock;
};

class PrOperationsBlockElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<OperationsBlockElement> GetOperationsBlockElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<OperationsBlockElement> operationsBlockElement;
};

class PrSettingStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<SettingStatement> GetSettingStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<SettingStatement> settingStatement;
};

class PrMemberExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<MemberExpression> GetMemberExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<MemberExpression> memberExpression;
};

class PrMemberMethodElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<MemberMethodElement> GetMemberMethodElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<MemberMethodElement> memberMethodElement;
};

class PrMemberMethodElementElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<MemberMethodElementElement> GetMemberMethodElementElement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<MemberMethodElementElement> memberMethodElementElement;
};

class PrArgumentsBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ArgumentsBlock> GetArgumentsBlock(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<ArgumentsBlock> argumentsBlock;
};

class PrArgumentsBlockElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ArgumentsBlockElement> GetArgumentsBlockElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<ArgumentsBlockElement> argumentsBlockElement;
};

class PrArrayElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ArrayElement> GetArrayElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<ArrayElement> arrayElement;
};

class PrMethodStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<MethodStatement> GetMethodStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<MethodStatement> methodStatement;
};

class PrMethodExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<MethodExpression> GetMethodExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<MethodExpression> methodExpression;
};

class PrExecuteStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ExecuteStatement> GetExecuteStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<ExecuteStatement> executeStatement;
};

class PrReturnStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ReturnStatement> GetReturnStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<ReturnStatement> returnStatement;
};

class PrAwaitStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<AwaitStatement> GetAwaitStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<AwaitStatement> awaitStatement;
};

class PrHandlerStatementHelper {
public:
    using MemberMethodPair = std::pair<std::unique_ptr<MemberMethod>, AstToken>;
    
    static MemberMethodPair GetMemberMethodPair(void* prnt,
        std::vector<std::unique_ptr<PrMemberMethodElement>>& helpers);
};

class PrAddHandlerStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<AddHandlerStatement> GetAddHandlerStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<AddHandlerStatement> addHandlerStatement;
};

class PrRemoveHandlerStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<RemoveHandlerStatement> GetRemoveHandlerStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<RemoveHandlerStatement> removeHandlerStatement;
};

class PrIfStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<IfStatement> GetIfStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<IfStatement> ifStatement;
};

class PrIfStatementElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<IfStatementElement> GetIfStatementElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<IfStatementElement> ifStatementElement;
};

class PrForToStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ForToStatement> GetForToStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<ForToStatement> forToStatement;
};

class PrForEachStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ForEachStatement> GetForEachStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<ForEachStatement> forEachStatement;
};

class PrWhileStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<WhileStatement> GetWhileStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<WhileStatement> whileStatement;
};

class PrTryStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<TryStatement> GetTryStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<TryStatement> tryStatement;
};

class PrRaiseStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<RaiseStatement> GetRaiseStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<RaiseStatement> raiseStatement;
};

class PrLabelStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<LabelStatement> GetLabelStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<LabelStatement> labelStatement;
};

class PrGotoStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<GotoStatement> GetGotoStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<GotoStatement> gotoStatement;
};

class PrContinueStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ContinueStatement> GetContinueStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<ContinueStatement> continueStatement;
};

class PrBreakStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<BreakStatement> GetBreakStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<BreakStatement> breakStatement;
};

class PrSemicolonStatement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<SemicolonStatement> GetSemicolonStatement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<SemicolonStatement> semicolonStatement;
};

class PrInitialExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<InitialExpression> GetInitialExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<InitialExpression> initialExpression;
};

class PrExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<Expression> GetExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<Expression> expression;
};

class PrExpressionElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ExpressionElement> GetExpressionElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<ExpressionElement> expressionElement;
};

class PrPrimeExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<PrimeExpression> GetPrimeExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<PrimeExpression> primeExpression;
};

class PrExpressionInParenthesis final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<ExpressionInParenthesis> GetExpressionInParenthesis(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<ExpressionInParenthesis> expressionInParenthesis;
};

class PrMemberMethod final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<MemberMethod> GetMemberMethod(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<MemberMethod> memberMethod;
};

class PrNewElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<NewElement> GetNewElement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<NewElement> newElement;
};

class PrNewArgumentsBlock final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<NewArgumentsBlock> GetNewArgumentsBlock(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<NewArgumentsBlock> newArgumentsBlock;
};

class PrTernaryOperationElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<TernaryOperationElement> GetTernaryOperationElement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<TernaryOperationElement> ternaryOperationElement;
};

class PrAwaitElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<AwaitElement> GetAwaitElement(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<AwaitElement> awaitElement;
};

class PrAndExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<AndExpression> GetAndExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<AndExpression> andExpression;
};

class PrAndExpressionElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<AndExpressionElement> GetAndExpressionElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<AndExpressionElement> andExpressionElement;
};

class PrNotExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<NotExpression> GetNotExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<NotExpression> notExpression;
};

class PrNotExpressionElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<NotExpressionElement> GetNotExpressionElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<NotExpressionElement> notExpressionElement;
};

class PrRelationalExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<RelationalExpression> GetRelationalExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<RelationalExpression> relationalExpression;
};

class PrRelationalExpressionElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<RelationalExpressionElement> GetRelationalExpressionElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<RelationalExpressionElement> relationalExpressionElement;
};

class PrAddingExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<AddingExpression> GetAddingExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<AddingExpression> addingExpression;
};

class PrAddingExpressionElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<AddingExpressionElement> GetAddingExpressionElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<AddingExpressionElement> addingExpressionElement;
};

class PrMultiplyingExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<MultiplyingExpression> GetMultiplyingExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<MultiplyingExpression> multiplyingExpression;
};

class PrMultiplyingExpressionElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<MultiplyingExpressionElement> GetMultiplyingExpressionElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<MultiplyingExpressionElement> multiplyingExpressionElement;
};

class PrSignExpression final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<SignExpression> GetSignExpression(void* prnt);
    void Reset() override;

private:
    std::unique_ptr<SignExpression> signExpression;
};

class PrSignExpressionElement final: public PRule {
public:
    bool CheckAstNode(PStream& stream) override;
    std::unique_ptr<SignExpressionElement> GetSignExpressionElement(void* prnt, int index);
    void Reset() override;

private:
    std::unique_ptr<SignExpressionElement> signExpressionElement;
};

#endif
