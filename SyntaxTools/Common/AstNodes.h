#ifndef SYNTAX_TOOLS_COMMON_AST_NODES_H
#define SYNTAX_TOOLS_COMMON_AST_NODES_H

#include <memory>
#include <vector>

#include "Tokens.h"

namespace syntax_tools {

enum class AstNodeType {
    none,
    root,
    block,
    blockElement,
    preprocessorRegionBlock,
    preprocessorIfBlock,
    preprocessorIfBlockElement,
    preprocessorExpression,
    preprocessorExpressionElement,
    preprocessorPrimeExpression,
    preprocessorValue,
    preprocessorAndExpression,
    preprocessorAndExpressionElement,
    preprocessorNotExpression,
    preprocessorNotExpressionElement,
    variablesBlock,
    variablesBlockElement,
    variablesBlockElementElement,
    variable,
    functionsBlock,
    functionsBlockElement,
    functionBlock,
    procedureBlock,
    directiveOfPreprocessor,
    annotation,
    functionArgumentsBlock,
    functionArgumentsBlockElement,
    functionArgument,
    value,
    string,
    stringElement,
    operationsBlock,
    operationsBlockElement,
    settingStatement,
    memberExpression,
    memberMethodElement,
    memberMethodElementElement,
    argumentsBlock,
    argumentsBlockElement,
    arrayElement,
    methodStatement,
    methodExpression,
    executeStatement,
    returnStatement,
    awaitStatement,
    addHandlerStatement,
    removeHandlerStatement,
    ifStatement,
    ifStatementElement,
    forToStatement,
    forEachStatement,
    whileStatement,
    tryStatement,
    raiseStatement,
    labelStatement,
    gotoStatement,
    continueStatement,
    breakStatement,
    semicolonStatement,
    initialExpression,
    expression,
    expressionElement,
    primeExpression,
    expressionInParenthesis,
    memberMethod,
    newElement,
    newArgumentsBlock,
    ternaryOperationElement,
    awaitElement,
    andExpression,
    andExpressionElement,
    notExpression,
    notExpressionElement,
    relationalExpression,
    relationalExpressionElement,
    addingExpression,
    addingExpressionElement,
    multiplyingExpression,
    multiplyingExpressionElement,
    signExpression,
    signExpressionElement
};

struct AstToken: public Token {
    virtual ~AstToken();
    void SetFromToken(const Token& token);
    
    void* prnt = nullptr;
};

struct AstNode: public Entity {
    virtual ~AstNode();
    void SetAstNode(const AstNode& astNode);
    virtual void UpdateChildren();
    
    AstNodeType type = AstNodeType::none;
    void* prnt = nullptr;
    int index = -1;
};

struct Ast;
struct Block;
struct BlockElement;
struct PreprocessorRegionBlock;
struct PreprocessorIfBlock;
struct PreprocessorIfBlockElement;
struct PreprocessorExpression;
struct PreprocessorExpressionElement;
struct PreprocessorPrimeExpression;
struct PreprocessorValue;
struct PreprocessorAndExpression;
struct PreprocessorAndExpressionElement;
struct PreprocessorNotExpression;
struct PreprocessorNotExpressionElement;
struct VariablesBlock;
struct VariablesBlockElement;
struct VariablesBlockElementElement;
struct Variable;
struct FunctionsBlock;
struct FunctionsBlockElement;
struct FunctionBlock;
struct ProcedureBlock;
struct DirectiveOfPreprocessor;
struct Annotation;
struct FunctionArgumentsBlock;
struct FunctionArgumentsBlockElement;
struct FunctionArgument;
struct Value;
struct String;
struct StringElement;
struct OperationsBlock;
struct OperationsBlockElement;
struct SettingStatement;
struct MemberExpression;
struct MemberMethodElement;
struct MemberMethodElementElement;
struct ArgumentsBlock;
struct ArgumentsBlockElement;
struct ArrayElement;
struct MethodStatement;
struct MethodExpression;
struct ExecuteStatement;
struct ReturnStatement;
struct AwaitStatement;
struct AddHandlerStatement;
struct RemoveHandlerStatement;
struct IfStatement;
struct IfStatementElement;
struct ForToStatement;
struct ForEachStatement;
struct WhileStatement;
struct TryStatement;
struct RaiseStatement;
struct LabelStatement;
struct GotoStatement;
struct ContinueStatement;
struct BreakStatement;
struct SemicolonStatement;
struct InitialExpression;
struct Expression;
struct ExpressionElement;
struct PrimeExpression;
struct ExpressionInParenthesis;
struct MemberMethod;
struct NewElement;
struct NewArgumentsBlock;
struct TernaryOperationElement;
struct AwaitElement;
struct AndExpression;
struct AndExpressionElement;
struct NotExpression;
struct NotExpressionElement;
struct RelationalExpression;
struct RelationalExpressionElement;
struct AddingExpression;
struct AddingExpressionElement;
struct MultiplyingExpression;
struct MultiplyingExpressionElement;
struct SignExpression;
struct SignExpressionElement;

struct Ast: public AstNode {
    Ast();
    virtual ~Ast();
    
    std::unique_ptr<Block> block;
};

struct Block: public AstNode {
    Block();
    virtual ~Block();
    
    std::vector<BlockElement> blockElements;
};

struct BlockElement: public AstNode {
    BlockElement();
    BlockElement(const BlockElement& blockElement);
    virtual ~BlockElement();
    virtual void UpdateChildren() override;
    
    std::unique_ptr<PreprocessorRegionBlock> preprocessorRegionBlock;
    std::unique_ptr<PreprocessorIfBlock> preprocessorIfBlock;
    std::unique_ptr<VariablesBlock> variablesBlock;
    std::unique_ptr<FunctionsBlock> functionsBlock;
    std::unique_ptr<OperationsBlock> operationsBlock;
};

struct PreprocessorRegionBlock: public AstNode {
    PreprocessorRegionBlock();
    virtual ~PreprocessorRegionBlock();
    
    AstToken tkTermNumberSignRegion;
    AstToken tkTermRegion;
    AstToken tkTermIdentifier;
    std::unique_ptr<Block> block;
    AstToken tkTermNumberSignEndRegion;
    AstToken tkTermEndRegion;
};

struct PreprocessorIfBlock: public AstNode {
    PreprocessorIfBlock();
    virtual ~PreprocessorIfBlock();
    
    bool isTermElse = false;
    
    AstToken tkTermNumberSignIf;
    AstToken tkTermIf;
    std::unique_ptr<PreprocessorExpression> preprocessorExpression;
    AstToken tkTermThen;
    std::unique_ptr<Block> blockIf;
    std::vector<PreprocessorIfBlockElement> preprocessorIfBlockElements;
    AstToken tkTermNumberSignElse;
    AstToken tkTermElse;
    std::unique_ptr<Block> blockElse;
    AstToken tkTermNumberSignEndIf;
    AstToken tkTermEndIf;
};

struct PreprocessorIfBlockElement: public AstNode {
    PreprocessorIfBlockElement();
    PreprocessorIfBlockElement(const PreprocessorIfBlockElement& preprocessorIfBlockElement);
    virtual ~PreprocessorIfBlockElement();
    virtual void UpdateChildren() override;
    
    AstToken tkTermNumberSign;
    AstToken tkTermElsIf;
    std::unique_ptr<PreprocessorExpression> preprocessorExpression;
    AstToken tkTermThen;
    std::unique_ptr<Block> block;
};

struct PreprocessorExpression: public AstNode {
    PreprocessorExpression();
    virtual ~PreprocessorExpression();
    
    std::unique_ptr<PreprocessorAndExpression> preprocessorAndExpression;
    std::vector<PreprocessorExpressionElement> preprocessorExpressionElements;
};

struct PreprocessorExpressionElement: public AstNode {
    PreprocessorExpressionElement();
    PreprocessorExpressionElement(const PreprocessorExpressionElement& preprocessorExpressionElement);
    virtual ~PreprocessorExpressionElement();
    virtual void UpdateChildren() override;
    
    AstToken tkTermOr;
    std::unique_ptr<PreprocessorAndExpression> preprocessorAndExpression;
};

struct PreprocessorPrimeExpression: public AstNode {
    PreprocessorPrimeExpression();
    virtual ~PreprocessorPrimeExpression();
    
    std::unique_ptr<PreprocessorValue> preprocessorValue;
    AstToken tkTermLeftParenthesis;
    std::unique_ptr<PreprocessorExpression> preprocessorExpression;
    AstToken tkTermRightParenthesis;
};

struct PreprocessorValue: public AstNode {
    PreprocessorValue();
    virtual ~PreprocessorValue();
    
    bool isTermClient = false;
    bool isTermAtClient = false;
    bool isTermAtServer = false;
    bool isTermMobileAppClient = false;
    bool isTermMobileAppServer = false;
    bool isTermThickClientOrdinaryApplication = false;
    bool isTermThickClientManagedApplication = false;
    bool isTermServer = false;
    bool isTermExternalConnection = false;
    bool isTermThinClient = false;
    bool isTermWebClient = false;
    
    AstToken tkTermClient;
    AstToken tkTermAtClient;
    AstToken tkTermAtServer;
    AstToken tkTermMobileAppClient;
    AstToken tkTermMobileAppServer;
    AstToken tkTermThickClientOrdinaryApplication;
    AstToken tkTermThickClientManagedApplication;
    AstToken tkTermServer;
    AstToken tkTermExternalConnection;
    AstToken tkTermThinClient;
    AstToken tkTermWebClient;
};

struct PreprocessorAndExpression: public AstNode {
    PreprocessorAndExpression();
    virtual ~PreprocessorAndExpression();
    
    std::unique_ptr<PreprocessorNotExpression> preprocessorNotExpression;
    std::vector<PreprocessorAndExpressionElement> preprocessorAndExpressionElements;
};

struct PreprocessorAndExpressionElement: public AstNode {
    PreprocessorAndExpressionElement();
    PreprocessorAndExpressionElement(const PreprocessorAndExpressionElement& preprocessorAndExpressionElement);
    virtual ~PreprocessorAndExpressionElement();
    virtual void UpdateChildren() override;
    
    AstToken tkTermAnd;
    std::unique_ptr<PreprocessorNotExpression> preprocessorNotExpression;
};

struct PreprocessorNotExpression: public AstNode {
    PreprocessorNotExpression();
    virtual ~PreprocessorNotExpression();
    
    std::vector<PreprocessorNotExpressionElement> preprocessorNotExpressionElements;
    std::unique_ptr<PreprocessorPrimeExpression> preprocessorPrimeExpression;
};

struct PreprocessorNotExpressionElement: public AstNode {
    PreprocessorNotExpressionElement();
    virtual ~PreprocessorNotExpressionElement();
    virtual void UpdateChildren() override;
    
    AstToken tkTermNot;
};

struct VariablesBlock: public AstNode {
    VariablesBlock();
    virtual ~VariablesBlock();
    
    std::vector<VariablesBlockElement> variablesBlockElements;
};

struct VariablesBlockElement: public AstNode {
    VariablesBlockElement();
    VariablesBlockElement(const VariablesBlockElement& variablesBlockElement);
    virtual ~VariablesBlockElement();
    virtual void UpdateChildren() override;
    
    AstToken tkVar;
    std::unique_ptr<Variable> variable;
    std::vector<VariablesBlockElementElement> variablesBlockElementElements;
    AstToken tkSemicolon;
};

struct VariablesBlockElementElement: public AstNode {
    VariablesBlockElementElement();
    VariablesBlockElementElement(const VariablesBlockElementElement& variablesBlockElementElement);
    virtual ~VariablesBlockElementElement();
    virtual void UpdateChildren() override;
    
    AstToken tkComma;
    std::unique_ptr<Variable> variable;
};

struct Variable: public AstNode {
    Variable();
    virtual ~Variable();
    
    bool isExport = false;
    
    AstToken tkIdentifier;
    AstToken tkExport;
};

struct FunctionsBlock: public AstNode {
    FunctionsBlock();
    virtual ~FunctionsBlock();
    
    std::vector<FunctionsBlockElement> functionsBlockElements;
};

struct FunctionsBlockElement: public AstNode {
    FunctionsBlockElement();
    FunctionsBlockElement(const FunctionsBlockElement& functionsBlockElement);
    virtual ~FunctionsBlockElement();
    virtual void UpdateChildren() override;
    
    std::unique_ptr<FunctionBlock> functionBlock;
    std::unique_ptr<ProcedureBlock> procedureBlock;
};

struct FunctionBlock: public AstNode {
    FunctionBlock();
    virtual ~FunctionBlock();
    
    bool isAsync = false;
    bool isExport = false;
    
    std::unique_ptr<DirectiveOfPreprocessor> directiveOfPreprocessor;
    AstToken tkAsync;
    AstToken tkFunction;
    AstToken tkIdentifier;
    AstToken tkLeftParenthesis;
    std::unique_ptr<FunctionArgumentsBlock> functionArgumentsBlock;
    AstToken tkRightParenthesis;
    AstToken tkExport;
    std::unique_ptr<Block> block;
    AstToken tkEndFunction;
};

struct ProcedureBlock: public AstNode {
    ProcedureBlock();
    virtual ~ProcedureBlock();
    
    bool isAsync = false;
    bool isExport = false;
    
    std::unique_ptr<DirectiveOfPreprocessor> directiveOfPreprocessor;
    AstToken tkAsync;
    AstToken tkProcedure;
    AstToken tkIdentifier;
    AstToken tkLeftParenthesis;
    std::unique_ptr<FunctionArgumentsBlock> functionArgumentsBlock;
    AstToken tkRightParenthesis;
    AstToken tkExport;
    std::unique_ptr<Block> block;
    AstToken tkEndProcedure;
};

struct DirectiveOfPreprocessor: public AstNode {
    DirectiveOfPreprocessor();
    virtual ~DirectiveOfPreprocessor();
    
    bool isDirectiveAtClient = false;
    bool isDirectiveAtServer = false;
    bool isDirectiveAtServerNoContext = false;
    bool isDirectiveAtClientAtServerNoContext = false;
    bool isDirectiveAtClientAtServer = false;
    
    AstToken tkDirectiveAmpersand;
    AstToken tkDirectiveAtClient;
    AstToken tkDirectiveAtServer;
    AstToken tkDirectiveAtServerNoContext;
    AstToken tkDirectiveAtClientAtServerNoContext;
    AstToken tkDirectiveAtClientAtServer;
    std::unique_ptr<Annotation> annotation;
};

struct Annotation: public AstNode {
    Annotation();
    virtual ~Annotation();
    
    bool isDirectiveBefore = false;
    bool isDirectiveAfter = false;
    bool isDirectiveInstead = false;
    
    AstToken tkDirectiveAmpersand;
    AstToken tkDirectiveBefore;
    AstToken tkDirectiveAfter;
    AstToken tkDirectiveInstead;
    AstToken tkDirectiveLeftParenthesis;
    AstToken tkDirectiveString;
    AstToken tkDirectiveRightParenthesis;
};

struct FunctionArgumentsBlock: public AstNode {
    FunctionArgumentsBlock();
    virtual ~FunctionArgumentsBlock();
    
    std::unique_ptr<FunctionArgument> functionArgument;
    std::vector<FunctionArgumentsBlockElement> functionArgumentsBlockElements;
};

struct FunctionArgumentsBlockElement: public AstNode {
    FunctionArgumentsBlockElement();
    FunctionArgumentsBlockElement(const FunctionArgumentsBlockElement& functionArgumentsBlockElement);
    virtual ~FunctionArgumentsBlockElement();
    virtual void UpdateChildren() override;
    
    AstToken tkComma;
    std::unique_ptr<FunctionArgument> functionArgument;
};

struct FunctionArgument: public AstNode {
    FunctionArgument();
    virtual ~FunctionArgument();
    
    bool isVal = false;
    
    AstToken tkVal;
    AstToken tkIdentifier;
    AstToken tkEquals;
    std::unique_ptr<Value> value;
};

struct Value: public AstNode {
    Value();
    virtual ~Value();
    
    bool isSignedFloat = false;
    bool isFloat = false;
    bool isDate = false;
    bool isNull = false;
    bool isUndefined = false;
    bool isFalse = false;
    bool isTrue = false;
    
    AstToken tkSignedFloat;
    AstToken tkFloat;
    AstToken tkDate;
    AstToken tkNull;
    AstToken tkUndefined;
    AstToken tkFalse;
    AstToken tkTrue;
    std::unique_ptr<String> string;
};

struct String: public AstNode {
    String();
    virtual ~String();
    
    AstToken tkString;
    AstToken tkStringBeginning;
    std::vector<StringElement> stringElements;
    AstToken tkStringEnding;
};

struct StringElement: public AstNode {
    StringElement();
    virtual ~StringElement();
    virtual void UpdateChildren() override;
    
    AstToken tkStringContinue;
};

struct OperationsBlock: public AstNode {
    OperationsBlock();
    virtual ~OperationsBlock();
    
    std::vector<OperationsBlockElement> operationsBlockElements;
};

struct OperationsBlockElement: public AstNode {
    OperationsBlockElement();
    OperationsBlockElement(const OperationsBlockElement& operationsBlockElement);
    virtual ~OperationsBlockElement();
    virtual void UpdateChildren() override;
    
    std::unique_ptr<SettingStatement> settingStatement;
    std::unique_ptr<MethodStatement> methodStatement;
    std::unique_ptr<ExecuteStatement> executeStatement;
    std::unique_ptr<ReturnStatement> returnStatement;
    std::unique_ptr<AwaitStatement> awaitStatement;
    std::unique_ptr<AddHandlerStatement> addHandlerStatement;
    std::unique_ptr<RemoveHandlerStatement> removeHandlerStatement;
    std::unique_ptr<IfStatement> ifStatement;
    std::unique_ptr<ForToStatement> forToStatement;
    std::unique_ptr<ForEachStatement> forEachStatement;
    std::unique_ptr<WhileStatement> whileStatement;
    std::unique_ptr<TryStatement> tryStatement;
    std::unique_ptr<RaiseStatement> raiseStatement;
    std::unique_ptr<LabelStatement> labelStatement;
    std::unique_ptr<GotoStatement> gotoStatement;
    std::unique_ptr<ContinueStatement> continueStatement;
    std::unique_ptr<BreakStatement> breakStatement;
    std::unique_ptr<SemicolonStatement> semicolonStatement;
};

struct SettingStatement: public AstNode {
    SettingStatement();
    virtual ~SettingStatement();
    
    std::unique_ptr<MemberExpression> memberExpression;
    AstToken tkEquals;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkSemicolon;
};

struct MemberExpression: public AstNode {
    MemberExpression();
    virtual ~MemberExpression();
    
    std::vector<MemberMethodElement> memberMethodElements;
    AstToken tkIdentifier;
    std::vector<ArrayElement> arrayElements;
};

struct MemberMethodElement: public AstNode {
    MemberMethodElement();
    MemberMethodElement(const MemberMethodElement& memberMethodElement);
    virtual ~MemberMethodElement();
    virtual void UpdateChildren() override;
    
    std::unique_ptr<MemberMethodElementElement> memberMethodElementElement;
    AstToken tkFullStop;
};

struct MemberMethodElementElement: public AstNode {
    MemberMethodElementElement();
    virtual ~MemberMethodElementElement();
    
    AstToken tkIdentifier;
    std::unique_ptr<ArgumentsBlock> argumentsBlock;
    std::vector<ArrayElement> arrayElements;
};

struct ArgumentsBlock: public AstNode {
    ArgumentsBlock();
    virtual ~ArgumentsBlock();
    
    AstToken tkLeftParenthesis;
    std::unique_ptr<InitialExpression> initialExpression;
    std::vector<ArgumentsBlockElement> argumentsBlockElements;
    AstToken tkRightParenthesis;
};

struct ArgumentsBlockElement: public AstNode {
    ArgumentsBlockElement();
    ArgumentsBlockElement(const ArgumentsBlockElement& argumentsBlockElement);
    virtual ~ArgumentsBlockElement();
    virtual void UpdateChildren() override;
    
    AstToken tkComma;
    std::unique_ptr<InitialExpression> initialExpression;
};

struct ArrayElement: public AstNode {
    ArrayElement();
    ArrayElement(const ArrayElement& arrayElement);
    virtual ~ArrayElement();
    virtual void UpdateChildren() override;
    
    AstToken tkLeftSquareBracket;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkRightSquareBracket;
};

struct MethodStatement: public AstNode {
    MethodStatement();
    virtual ~MethodStatement();
    
    std::unique_ptr<MethodExpression> methodExpression;
    AstToken tkSemicolon;
};

struct MethodExpression: public AstNode {
    MethodExpression();
    virtual ~MethodExpression();
    
    std::vector<MemberMethodElement> memberMethodElements;
    AstToken tkIdentifier;
    std::unique_ptr<ArgumentsBlock> argumentsBlock;
};

struct ExecuteStatement: public AstNode {
    ExecuteStatement();
    virtual ~ExecuteStatement();
    
    AstToken tkExecute;
    AstToken tkLeftParenthesis;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkRightParenthesis;
    AstToken tkSemicolon;
};

struct ReturnStatement: public AstNode {
    ReturnStatement();
    virtual ~ReturnStatement();
    
    AstToken tkReturn;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkSemicolon;
};

struct AwaitStatement: public AstNode {
    AwaitStatement();
    virtual ~AwaitStatement();
    
    AstToken tkAwait;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkSemicolon;
};

struct AddHandlerStatement: public AstNode {
    AddHandlerStatement();
    virtual ~AddHandlerStatement();
    
    AstToken tkAddHandler;
    std::unique_ptr<MemberMethod> memberMethodEvent;
    AstToken tkFullStopEvent;
    AstToken tkIdentifierEvent;
    AstToken tkComma;
    std::unique_ptr<MemberMethod> memberMethodHandler;
    AstToken tkFullStopHandler;
    AstToken tkIdentifierHandler;
    AstToken tkSemicolon;
    AstToken tkIdentifierFunctionName;
};

struct RemoveHandlerStatement: public AstNode {
    RemoveHandlerStatement();
    virtual ~RemoveHandlerStatement();
    
    AstToken tkRemoveHandler;
    std::unique_ptr<MemberMethod> memberMethodEvent;
    AstToken tkFullStopEvent;
    AstToken tkIdentifierEvent;
    AstToken tkComma;
    std::unique_ptr<MemberMethod> memberMethodHandler;
    AstToken tkFullStopHandler;
    AstToken tkIdentifierHandler;
    AstToken tkSemicolon;
    AstToken tkIdentifierFunctionName;
};

struct IfStatement: public AstNode {
    IfStatement();
    virtual ~IfStatement();
    
    bool isElse = false;
    
    AstToken tkIf;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkThen;
    std::unique_ptr<Block> blockIf;
    std::vector<IfStatementElement> ifStatementElements;
    AstToken tkElse;
    std::unique_ptr<Block> blockElse;
    AstToken tkEndIf;
    AstToken tkSemicolon;
};

struct IfStatementElement: public AstNode {
    IfStatementElement();
    IfStatementElement(const IfStatementElement& ifStatementElement);
    virtual ~IfStatementElement();
    virtual void UpdateChildren() override;
    
    AstToken tkElsIf;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkThen;
    std::unique_ptr<Block> block;
};

struct ForToStatement: public AstNode {
    ForToStatement();
    virtual ~ForToStatement();
    
    AstToken tkFor;
    AstToken tkIdentifier;
    AstToken tkEquals;
    std::unique_ptr<InitialExpression> initialExpressionA;
    AstToken tkTo;
    std::unique_ptr<InitialExpression> initialExpressionB;
    AstToken tkDo;
    std::unique_ptr<Block> block;
    AstToken tkEndDo;
    AstToken tkSemicolon;
};

struct ForEachStatement: public AstNode {
    ForEachStatement();
    virtual ~ForEachStatement();
    
    AstToken tkFor;
    AstToken tkEach;
    AstToken tkIdentifier;
    AstToken tkIn;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkDo;
    std::unique_ptr<Block> block;
    AstToken tkEndDo;
    AstToken tkSemicolon;
};

struct WhileStatement: public AstNode {
    WhileStatement();
    virtual ~WhileStatement();
    
    AstToken tkWhile;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkDo;
    std::unique_ptr<Block> block;
    AstToken tkEndDo;
    AstToken tkSemicolon;
};

struct TryStatement: public AstNode {
    TryStatement();
    virtual ~TryStatement();
    
    AstToken tkTry;
    std::unique_ptr<Block> blockTry;
    AstToken tkExcept;
    std::unique_ptr<Block> blockExcept;
    AstToken tkEndTry;
    AstToken tkSemicolon;
};

struct RaiseStatement: public AstNode {
    RaiseStatement();
    virtual ~RaiseStatement();
    
    AstToken tkRaise;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkSemicolon;
};

struct LabelStatement: public AstNode {
    LabelStatement();
    virtual ~LabelStatement();
    
    AstToken tkTilde;
    AstToken tkIdentifier;
    AstToken tkColon;
};

struct GotoStatement: public AstNode {
    GotoStatement();
    virtual ~GotoStatement();
    
    AstToken tkGoto;
    AstToken tkTilde;
    AstToken tkIdentifier;
    AstToken tkSemicolon;
};

struct ContinueStatement: public AstNode {
    ContinueStatement();
    virtual ~ContinueStatement();
    
    AstToken tkContinue;
    AstToken tkSemicolon;
};

struct BreakStatement: public AstNode {
    BreakStatement();
    virtual ~BreakStatement();
    
    AstToken tkBreak;
    AstToken tkSemicolon;
};

struct SemicolonStatement: public AstNode {
    SemicolonStatement();
    virtual ~SemicolonStatement();
    
    AstToken tkSemicolon;
};

struct InitialExpression: public AstNode {
    InitialExpression();
    virtual ~InitialExpression();
    
    std::unique_ptr<Expression> expression;
};

struct Expression: public AstNode {
    Expression();
    virtual ~Expression();
    
    std::unique_ptr<AndExpression> andExpression;
    std::vector<ExpressionElement> expressionElements;
};

struct ExpressionElement: public AstNode {
    ExpressionElement();
    ExpressionElement(const ExpressionElement& expressionElement);
    virtual ~ExpressionElement();
    virtual void UpdateChildren() override;
    
    AstToken tkOr;
    std::unique_ptr<AndExpression> andExpression;
};

struct PrimeExpression: public AstNode {
    PrimeExpression();
    virtual ~PrimeExpression();
    
    std::unique_ptr<Value> value;
    std::unique_ptr<ExpressionInParenthesis> expressionInParenthesis;
    std::unique_ptr<MemberMethod> memberMethod;
    std::unique_ptr<NewElement> newElement;
    std::unique_ptr<TernaryOperationElement> ternaryOperationElement;
    std::unique_ptr<AwaitElement> awaitElement;
};

struct ExpressionInParenthesis: public AstNode {
    ExpressionInParenthesis();
    virtual ~ExpressionInParenthesis();
    
    AstToken tkLeftParenthesis;
    std::unique_ptr<Expression> expression;
    AstToken tkRightParenthesis;
};

struct MemberMethod: public AstNode {
    MemberMethod();
    MemberMethod(const MemberMethod& memberMethod);
    virtual ~MemberMethod();
    
    std::vector<MemberMethodElement> memberMethodElements;
    std::unique_ptr<MemberMethodElementElement> memberMethodElementElement;
};

struct NewElement: public AstNode {
    NewElement();
    virtual ~NewElement();
    
    AstToken tkNew;
    AstToken tkIdentifier;
    std::unique_ptr<ArgumentsBlock> argumentsBlock;
    std::unique_ptr<NewArgumentsBlock> newArgumentsBlock;
};

struct NewArgumentsBlock: public AstNode {
    NewArgumentsBlock();
    virtual ~NewArgumentsBlock();
    
    AstToken tkLeftParenthesis;
    std::unique_ptr<InitialExpression> initialExpression;
    std::vector<ArgumentsBlockElement> argumentsBlockElements;
    AstToken tkRightParenthesis;
};

struct TernaryOperationElement: public AstNode {
    TernaryOperationElement();
    virtual ~TernaryOperationElement();
    
    AstToken tkQuestionMark;
    AstToken tkLeftParenthesis;
    std::unique_ptr<InitialExpression> initialExpression;
    AstToken tkCommaA;
    std::unique_ptr<InitialExpression> initialExpressionTrue;
    AstToken tkCommaB;
    std::unique_ptr<InitialExpression> initialExpressionFalse;
    AstToken tkRightParenthesis;
};

struct AwaitElement: public AstNode {
    AwaitElement();
    virtual ~AwaitElement();
    
    AstToken tkAwait;
    std::unique_ptr<InitialExpression> initialExpression;
};

struct AndExpression: public AstNode {
    AndExpression();
    virtual ~AndExpression();
    
    std::unique_ptr<NotExpression> notExpression;
    std::vector<AndExpressionElement> andExpressionElements;
};

struct AndExpressionElement: public AstNode {
    AndExpressionElement();
    AndExpressionElement(const AndExpressionElement& andExpressionElement);
    virtual ~AndExpressionElement();
    virtual void UpdateChildren() override;
    
    AstToken tkAnd;
    std::unique_ptr<NotExpression> notExpression;
};

struct NotExpression: public AstNode {
    NotExpression();
    virtual ~NotExpression();
    
    std::vector<NotExpressionElement> notExpressionElements;
    std::unique_ptr<RelationalExpression> relationalExpression;
};

struct NotExpressionElement: public AstNode {
    NotExpressionElement();
    virtual ~NotExpressionElement();
    virtual void UpdateChildren() override;
    
    AstToken tkNot;
};

struct RelationalExpression: public AstNode {
    RelationalExpression();
    virtual ~RelationalExpression();
    
    std::unique_ptr<AddingExpression> addingExpression;
    std::vector<RelationalExpressionElement> relationalExpressionElements;
};

struct RelationalExpressionElement: public AstNode {
    RelationalExpressionElement();
    RelationalExpressionElement(const RelationalExpressionElement& relationalExpressionElement);
    virtual ~RelationalExpressionElement();
    virtual void UpdateChildren() override;
    
    bool isEquals = false;
    bool isNotEquals = false;
    bool isLess = false;
    bool isLessOrEquals = false;
    bool isGreater = false;
    bool isGreaterOrEquals = false;

    AstToken tkEquals;
    AstToken tkNotEquals;
    AstToken tkLess;
    AstToken tkLessOrEquals;
    AstToken tkGreater;
    AstToken tkGreaterOrEquals;
    std::unique_ptr<AddingExpression> addingExpression;
};

struct AddingExpression: public AstNode {
    AddingExpression();
    virtual ~AddingExpression();
    
    std::unique_ptr<MultiplyingExpression> multiplyingExpression;
    std::vector<AddingExpressionElement> addingExpressionElements;
};

struct AddingExpressionElement: public AstNode {
    AddingExpressionElement();
    AddingExpressionElement(const AddingExpressionElement& addingExpressionElement);
    virtual ~AddingExpressionElement();
    virtual void UpdateChildren() override;
    
    bool isMinus = false;
    bool isPlus = false;
    
    AstToken tkMinus;
    AstToken tkPlus;
    std::unique_ptr<MultiplyingExpression> multiplyingExpression;
};

struct MultiplyingExpression: public AstNode {
    MultiplyingExpression();
    virtual ~MultiplyingExpression();
    
    std::vector<MultiplyingExpressionElement> multiplyingExpressionElements;
    std::unique_ptr<SignExpression> signExpression;
};

struct MultiplyingExpressionElement: public AstNode {
    MultiplyingExpressionElement();
    MultiplyingExpressionElement(const MultiplyingExpressionElement& multiplyingExpressionElement);
    virtual ~MultiplyingExpressionElement();
    virtual void UpdateChildren() override;
    
    bool isAsterisk = false;
    bool isSolidus = false;
    bool isPercent = false;
    
    AstToken tkAsterisk;
    AstToken tkSolidus;
    AstToken tkPercent;
    std::unique_ptr<SignExpression> signExpression;
};

struct SignExpression: public AstNode {
    SignExpression();
    virtual ~SignExpression();
    
    std::unique_ptr<PrimeExpression> primeExpression;
    std::vector<SignExpressionElement> signExpressionElements;
};

struct SignExpressionElement: public AstNode {
    SignExpressionElement();
    virtual ~SignExpressionElement();
    virtual void UpdateChildren() override;
    
    bool isMinus = false;
    bool isPlus = false;
    
    AstToken tkMinus;
    AstToken tkPlus;
};

}

#endif
