#include "AstNodes.h"

using namespace syntax_tools;

AstToken::~AstToken() {
}

void AstToken::SetFromToken(const Token& token) {
    type = token.type;
    prnt = nullptr;
    SetEntity(token);
}

AstNode::~AstNode() {
}

void AstNode::SetAstNode(const AstNode& astNode) {
    type = astNode.type;
    prnt = astNode.prnt;
    index = astNode.index;
    SetEntity(astNode);
}

void AstNode::UpdateChildren() {
}

Ast::Ast() {
    type = AstNodeType::root;
}

Ast::~Ast() {
}

Block::Block() {
    type = AstNodeType::block;
}

Block::~Block() {
}

BlockElement::BlockElement() {
    type = AstNodeType::blockElement;
}

BlockElement::BlockElement(const BlockElement& blockElement) {
    SetAstNode(blockElement);
    
    preprocessorRegionBlock = std::move(const_cast<BlockElement&>(blockElement).preprocessorRegionBlock);
    preprocessorIfBlock = std::move(const_cast<BlockElement&>(blockElement).preprocessorIfBlock);
    variablesBlock = std::move(const_cast<BlockElement&>(blockElement).variablesBlock);
    functionsBlock = std::move(const_cast<BlockElement&>(blockElement).functionsBlock);
    operationsBlock = std::move(const_cast<BlockElement&>(blockElement).operationsBlock);
}

BlockElement::~BlockElement() {
}

void BlockElement::UpdateChildren() {
    if (preprocessorRegionBlock.get() != nullptr) {
        preprocessorRegionBlock->prnt = this;
    }
    else if (preprocessorIfBlock.get() != nullptr) {
        preprocessorIfBlock->prnt = this;
    }
    else if (variablesBlock.get() != nullptr) {
        variablesBlock->prnt = this;
    }
    else if (functionsBlock.get() != nullptr) {
        functionsBlock->prnt = this;
    }
    else if (operationsBlock.get() != nullptr) {
        operationsBlock->prnt = this;
    }
}

PreprocessorRegionBlock::PreprocessorRegionBlock() {
    type = AstNodeType::preprocessorRegionBlock;
}

PreprocessorRegionBlock::~PreprocessorRegionBlock() {
}

PreprocessorIfBlock::PreprocessorIfBlock() {
    type = AstNodeType::preprocessorIfBlock;
}

PreprocessorIfBlock::~PreprocessorIfBlock() {
}

PreprocessorIfBlockElement::PreprocessorIfBlockElement() {
    type = AstNodeType::preprocessorIfBlockElement;
}

PreprocessorIfBlockElement::PreprocessorIfBlockElement(
    const PreprocessorIfBlockElement& preprocessorIfBlockElement) {
    SetAstNode(preprocessorIfBlockElement);
    
    tkTermNumberSign = preprocessorIfBlockElement.tkTermNumberSign;
    tkTermElsIf = preprocessorIfBlockElement.tkTermElsIf;
    preprocessorExpression = std::move(
        const_cast<PreprocessorIfBlockElement&>(preprocessorIfBlockElement).preprocessorExpression);
    tkTermThen = preprocessorIfBlockElement.tkTermThen;
    block = std::move(const_cast<PreprocessorIfBlockElement&>(preprocessorIfBlockElement).block);
}

PreprocessorIfBlockElement::~PreprocessorIfBlockElement() {
}

void PreprocessorIfBlockElement::UpdateChildren() {
    tkTermNumberSign.prnt = this;
    tkTermElsIf.prnt = this;
    preprocessorExpression->prnt = this;
    tkTermThen.prnt = this;
    
    if (block.get() != nullptr) {
        block->prnt = this;
    }
}

PreprocessorExpression::PreprocessorExpression() {
    type = AstNodeType::preprocessorExpression;
}

PreprocessorExpression::~PreprocessorExpression() {
}

PreprocessorExpressionElement::PreprocessorExpressionElement() {
    type = AstNodeType::preprocessorExpressionElement;
}

PreprocessorExpressionElement::PreprocessorExpressionElement(
    const PreprocessorExpressionElement& preprocessorExpressionElement) {
    SetAstNode(preprocessorExpressionElement);
    
    tkTermOr = preprocessorExpressionElement.tkTermOr;
    preprocessorAndExpression = std::move(
        const_cast<PreprocessorExpressionElement&>(preprocessorExpressionElement).preprocessorAndExpression);
}

PreprocessorExpressionElement::~PreprocessorExpressionElement() {
}

void PreprocessorExpressionElement::UpdateChildren() {
    tkTermOr.prnt = this;
    preprocessorAndExpression->prnt = this;
}

PreprocessorPrimeExpression::PreprocessorPrimeExpression() {
    type = AstNodeType::preprocessorPrimeExpression;
}

PreprocessorPrimeExpression::~PreprocessorPrimeExpression() {
}

PreprocessorValue::PreprocessorValue() {
    type = AstNodeType::preprocessorValue;
}

PreprocessorValue::~PreprocessorValue() {
}

PreprocessorAndExpression::PreprocessorAndExpression() {
    type = AstNodeType::preprocessorAndExpression;
}

PreprocessorAndExpression::~PreprocessorAndExpression() {
}

PreprocessorAndExpressionElement::PreprocessorAndExpressionElement() {
    type = AstNodeType::preprocessorAndExpressionElement;
}

PreprocessorAndExpressionElement::PreprocessorAndExpressionElement(
    const PreprocessorAndExpressionElement& preprocessorAndExpressionElement) {
    SetAstNode(preprocessorAndExpressionElement);
    
    tkTermAnd = preprocessorAndExpressionElement.tkTermAnd;
    preprocessorNotExpression = std::move(
        const_cast<PreprocessorAndExpressionElement&>(preprocessorAndExpressionElement).preprocessorNotExpression);
}

PreprocessorAndExpressionElement::~PreprocessorAndExpressionElement() {
}

void PreprocessorAndExpressionElement::UpdateChildren() {
    tkTermAnd.prnt = this;
    preprocessorNotExpression->prnt = this;
}

PreprocessorNotExpression::PreprocessorNotExpression() {
    type = AstNodeType::preprocessorNotExpression;
}

PreprocessorNotExpression::~PreprocessorNotExpression() {
}

PreprocessorNotExpressionElement::PreprocessorNotExpressionElement() {
    type = AstNodeType::preprocessorNotExpressionElement;
}

PreprocessorNotExpressionElement::~PreprocessorNotExpressionElement() {
}

void PreprocessorNotExpressionElement::UpdateChildren() {
    tkTermNot.prnt = this;
}

VariablesBlock::VariablesBlock() {
    type = AstNodeType::variablesBlock;
}

VariablesBlock::~VariablesBlock() {
}

VariablesBlockElement::VariablesBlockElement() {
    type = AstNodeType::variablesBlockElement;
}

VariablesBlockElement::VariablesBlockElement(const VariablesBlockElement& variablesBlockElement) {
    SetAstNode(variablesBlockElement);
    
    tkVar = variablesBlockElement.tkVar;
    variable = std::move(const_cast<VariablesBlockElement&>(variablesBlockElement).variable);
    variablesBlockElementElements = std::move(
        const_cast<VariablesBlockElement&>(variablesBlockElement).variablesBlockElementElements);
    tkSemicolon = variablesBlockElement.tkSemicolon;
}

VariablesBlockElement::~VariablesBlockElement() {
}

void VariablesBlockElement::UpdateChildren() {
    tkVar.prnt = this;
    variable->prnt = this;
    
    for (VariablesBlockElementElement& variablesBlockElementElement : variablesBlockElementElements) {
        variablesBlockElementElement.prnt = this;
    }
    
    if (!tkSemicolon.IsEmpty()) {
        tkSemicolon.prnt = this;
    }
}

VariablesBlockElementElement::VariablesBlockElementElement() {
    type = AstNodeType::variablesBlockElementElement;
}

VariablesBlockElementElement::VariablesBlockElementElement(
    const VariablesBlockElementElement& variablesBlockElementElement) {
    SetAstNode(variablesBlockElementElement);
    
    tkComma = variablesBlockElementElement.tkComma;
    variable = std::move(const_cast<VariablesBlockElementElement&>(variablesBlockElementElement).variable);
}

VariablesBlockElementElement::~VariablesBlockElementElement() {
}

void VariablesBlockElementElement::UpdateChildren() {
    tkComma.prnt = this;
    variable->prnt = this;
}

Variable::Variable() {
    type = AstNodeType::variable;
}

Variable::~Variable() {
}

FunctionsBlock::FunctionsBlock() {
    type = AstNodeType::functionsBlock;
}

FunctionsBlock::~FunctionsBlock() {
}

FunctionsBlockElement::FunctionsBlockElement() {
    type = AstNodeType::functionsBlockElement;
}

FunctionsBlockElement::FunctionsBlockElement(const FunctionsBlockElement& functionsBlockElement) {
    SetAstNode(functionsBlockElement);
    
    functionBlock = std::move(const_cast<FunctionsBlockElement&>(functionsBlockElement).functionBlock);
    procedureBlock = std::move(const_cast<FunctionsBlockElement&>(functionsBlockElement).procedureBlock);
}

FunctionsBlockElement::~FunctionsBlockElement() {
}

void FunctionsBlockElement::UpdateChildren() {
    if (functionBlock.get() != nullptr) {
        functionBlock->prnt = this;
    }
    else if (procedureBlock.get() != nullptr) {
        procedureBlock->prnt = this;
    }
}

FunctionBlock::FunctionBlock() {
    type = AstNodeType::functionBlock;
}

FunctionBlock::~FunctionBlock() {
}

ProcedureBlock::ProcedureBlock() {
    type = AstNodeType::procedureBlock;
}

ProcedureBlock::~ProcedureBlock() {
}

DirectiveOfPreprocessor::DirectiveOfPreprocessor() {
    type = AstNodeType::directiveOfPreprocessor;
}

DirectiveOfPreprocessor::~DirectiveOfPreprocessor() {
}

Annotation::Annotation() {
    type = AstNodeType::annotation;
}

Annotation::~Annotation() {
}

FunctionArgumentsBlock::FunctionArgumentsBlock() {
    type = AstNodeType::functionArgumentsBlock;
}

FunctionArgumentsBlock::~FunctionArgumentsBlock() {
}

FunctionArgumentsBlockElement::FunctionArgumentsBlockElement() {
    type = AstNodeType::functionArgumentsBlockElement;
}

FunctionArgumentsBlockElement::FunctionArgumentsBlockElement(
    const FunctionArgumentsBlockElement& functionArgumentsBlockElement) {
    SetAstNode(functionArgumentsBlockElement);
    
    tkComma = functionArgumentsBlockElement.tkComma;
    functionArgument = std::move(
        const_cast<FunctionArgumentsBlockElement&>(functionArgumentsBlockElement).functionArgument);
}

FunctionArgumentsBlockElement::~FunctionArgumentsBlockElement() {
}

void FunctionArgumentsBlockElement::UpdateChildren() {
    tkComma.prnt = this;
    functionArgument->prnt = this;
}

FunctionArgument::FunctionArgument() {
    type = AstNodeType::functionArgument;
}

FunctionArgument::~FunctionArgument() {
}

Value::Value() {
    type = AstNodeType::value;
}

Value::~Value() {
}

String::String() {
    type = AstNodeType::string;
}

String::~String() {
}

StringElement::StringElement() {
    type = AstNodeType::stringElement;
}

StringElement::~StringElement() {
}

void StringElement::UpdateChildren() {
    tkStringContinue.prnt = this;
}

OperationsBlock::OperationsBlock() {
    type = AstNodeType::operationsBlock;
}

OperationsBlock::~OperationsBlock() {
}

OperationsBlockElement::OperationsBlockElement() {
    type = AstNodeType::operationsBlockElement;
}

OperationsBlockElement::OperationsBlockElement(const OperationsBlockElement& operationsBlockElement) {
    SetAstNode(operationsBlockElement);
    
    settingStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).settingStatement);
    methodStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).methodStatement);
    executeStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).executeStatement);
    returnStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).returnStatement);
    awaitStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).awaitStatement);
    addHandlerStatement = std::move(
        const_cast<OperationsBlockElement&>(operationsBlockElement).addHandlerStatement);
    removeHandlerStatement = std::move(
        const_cast<OperationsBlockElement&>(operationsBlockElement).removeHandlerStatement);
    ifStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).ifStatement);
    forToStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).forToStatement);
    forEachStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).forEachStatement);
    whileStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).whileStatement);
    tryStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).tryStatement);
    raiseStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).raiseStatement);
    labelStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).labelStatement);
    gotoStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).gotoStatement);
    continueStatement = std::move(
        const_cast<OperationsBlockElement&>(operationsBlockElement).continueStatement);
    breakStatement = std::move(const_cast<OperationsBlockElement&>(operationsBlockElement).breakStatement);
    semicolonStatement = std::move(
        const_cast<OperationsBlockElement&>(operationsBlockElement).semicolonStatement);
}

OperationsBlockElement::~OperationsBlockElement() {
}

void OperationsBlockElement::UpdateChildren() {
    if (settingStatement.get() != nullptr) {
        settingStatement->prnt = this;
    }
    else if (methodStatement.get() != nullptr) {
        methodStatement->prnt = this;
    }
    else if (executeStatement.get() != nullptr) {
        executeStatement->prnt = this;
    }
    else if (returnStatement.get() != nullptr) {
        returnStatement->prnt = this;
    }
    else if (awaitStatement.get() != nullptr) {
        awaitStatement->prnt = this;
    }
    else if (addHandlerStatement.get() != nullptr) {
        addHandlerStatement->prnt = this;
    }
    else if (removeHandlerStatement.get() != nullptr) {
        removeHandlerStatement->prnt = this;
    }
    else if (ifStatement.get() != nullptr) {
        ifStatement->prnt = this;
    }
    else if (forToStatement.get() != nullptr) {
        forToStatement->prnt = this;
    }
    else if (forEachStatement.get() != nullptr) {
        forEachStatement->prnt = this;
    }
    else if (whileStatement.get() != nullptr) {
        whileStatement->prnt = this;
    }
    else if (tryStatement.get() != nullptr) {
        tryStatement->prnt = this;
    }
    else if (raiseStatement.get() != nullptr) {
        raiseStatement->prnt = this;
    }
    else if (labelStatement.get() != nullptr) {
        labelStatement->prnt = this;
    }
    else if (gotoStatement.get() != nullptr) {
        gotoStatement->prnt = this;
    }
    else if (continueStatement.get() != nullptr) {
        continueStatement->prnt = this;
    }
    else if (breakStatement.get() != nullptr) {
        breakStatement->prnt = this;
    }
    else if (semicolonStatement.get() != nullptr) {
        semicolonStatement->prnt = this;
    }
}

SettingStatement::SettingStatement() {
    type = AstNodeType::settingStatement;
}

SettingStatement::~SettingStatement() {
}

MemberExpression::MemberExpression() {
    type = AstNodeType::memberExpression;
}

MemberExpression::~MemberExpression() {
}

MemberMethodElement::MemberMethodElement() {
    type = AstNodeType::memberMethodElement;
}

MemberMethodElement::MemberMethodElement(const MemberMethodElement& memberMethodElement) {
    SetAstNode(memberMethodElement);
    
    memberMethodElementElement = std::move(
        const_cast<MemberMethodElement&>(memberMethodElement).memberMethodElementElement);
    tkFullStop = memberMethodElement.tkFullStop;
}

MemberMethodElement::~MemberMethodElement() {
}

void MemberMethodElement::UpdateChildren() {
    memberMethodElementElement->prnt = this;
    tkFullStop.prnt = this;
}

MemberMethodElementElement::MemberMethodElementElement() {
    type = AstNodeType::memberMethodElementElement;
}

MemberMethodElementElement::~MemberMethodElementElement() {
}

ArgumentsBlock::ArgumentsBlock() {
    type = AstNodeType::argumentsBlock;
}

ArgumentsBlock::~ArgumentsBlock() {
}

ArgumentsBlockElement::ArgumentsBlockElement() {
    type = AstNodeType::argumentsBlockElement;
}

ArgumentsBlockElement::ArgumentsBlockElement(const ArgumentsBlockElement& argumentsBlockElement) {
    SetAstNode(argumentsBlockElement);
    
    tkComma = argumentsBlockElement.tkComma;
    initialExpression = std::move(const_cast<ArgumentsBlockElement&>(argumentsBlockElement).initialExpression);
}

ArgumentsBlockElement::~ArgumentsBlockElement() {
}

void ArgumentsBlockElement::UpdateChildren() {
    tkComma.prnt = this;
    
    if (initialExpression.get() != nullptr) {
        initialExpression->prnt = this;
    }
}

ArrayElement::ArrayElement() {
    type = AstNodeType::arrayElement;
}

ArrayElement::ArrayElement(const ArrayElement& arrayElement) {
    SetAstNode(arrayElement);
    
    tkLeftSquareBracket = arrayElement.tkLeftSquareBracket;
    initialExpression = std::move(const_cast<ArrayElement&>(arrayElement).initialExpression);
    tkRightSquareBracket = arrayElement.tkRightSquareBracket;
}

ArrayElement::~ArrayElement() {
}

void ArrayElement::UpdateChildren() {
    tkLeftSquareBracket.prnt = this;
    initialExpression->prnt = this;
    tkRightSquareBracket.prnt = this;
}

MethodStatement::MethodStatement() {
    type = AstNodeType::methodStatement;
}

MethodStatement::~MethodStatement() {
}

MethodExpression::MethodExpression() {
    type = AstNodeType::methodExpression;
}

MethodExpression::~MethodExpression() {
}

ExecuteStatement::ExecuteStatement() {
    type = AstNodeType::executeStatement;
}

ExecuteStatement::~ExecuteStatement() {
}

ReturnStatement::ReturnStatement() {
    type = AstNodeType::returnStatement;
}

ReturnStatement::~ReturnStatement() {
}

AwaitStatement::AwaitStatement() {
    type = AstNodeType::awaitStatement;
}

AwaitStatement::~AwaitStatement() {
}

AddHandlerStatement::AddHandlerStatement() {
    type = AstNodeType::addHandlerStatement;
}

AddHandlerStatement::~AddHandlerStatement() {
}

RemoveHandlerStatement::RemoveHandlerStatement() {
    type = AstNodeType::removeHandlerStatement;
}

RemoveHandlerStatement::~RemoveHandlerStatement() {
}

IfStatement::IfStatement() {
    type = AstNodeType::ifStatement;
}

IfStatement::~IfStatement() {
}

IfStatementElement::IfStatementElement() {
    type = AstNodeType::ifStatementElement;
}

IfStatementElement::IfStatementElement(const IfStatementElement& ifStatementElement) {
    SetAstNode(ifStatementElement);
    
    tkElsIf = ifStatementElement.tkElsIf;
    initialExpression = std::move(const_cast<IfStatementElement&>(ifStatementElement).initialExpression);
    tkThen = ifStatementElement.tkThen;
    block = std::move(const_cast<IfStatementElement&>(ifStatementElement).block);
}

IfStatementElement::~IfStatementElement() {
}

void IfStatementElement::UpdateChildren() {
    tkElsIf.prnt = this;
    initialExpression->prnt = this;
    tkThen.prnt = this;
    
    if (block.get() != nullptr) {
        block->prnt = this;
    }
}

ForToStatement::ForToStatement() {
    type = AstNodeType::forToStatement;
}

ForToStatement::~ForToStatement() {
}

ForEachStatement::ForEachStatement() {
    type = AstNodeType::forEachStatement;
}

ForEachStatement::~ForEachStatement() {
}

WhileStatement::WhileStatement() {
    type = AstNodeType::whileStatement;
}

WhileStatement::~WhileStatement() {
}

TryStatement::TryStatement() {
    type = AstNodeType::tryStatement;
}

TryStatement::~TryStatement() {
}

RaiseStatement::RaiseStatement() {
    type = AstNodeType::raiseStatement;
}

RaiseStatement::~RaiseStatement() {
}

LabelStatement::LabelStatement() {
    type = AstNodeType::labelStatement;
}

LabelStatement::~LabelStatement() {
}

GotoStatement::GotoStatement() {
    type = AstNodeType::gotoStatement;
}

GotoStatement::~GotoStatement() {
}

ContinueStatement::ContinueStatement() {
    type = AstNodeType::continueStatement;
}

ContinueStatement::~ContinueStatement() {
}

BreakStatement::BreakStatement() {
    type = AstNodeType::breakStatement;
}

BreakStatement::~BreakStatement() {
}

SemicolonStatement::SemicolonStatement() {
    type = AstNodeType::semicolonStatement;
}

SemicolonStatement::~SemicolonStatement() {
}

InitialExpression::InitialExpression() {
    type = AstNodeType::initialExpression;
}

InitialExpression::~InitialExpression() {
}

Expression::Expression() {
    type = AstNodeType::expression;
}

Expression::~Expression() {
}

ExpressionElement::ExpressionElement() {
    type = AstNodeType::expressionElement;
}

ExpressionElement::ExpressionElement(const ExpressionElement& expressionElement) {
    SetAstNode(expressionElement);
    
    tkOr = expressionElement.tkOr;
    andExpression = std::move(const_cast<ExpressionElement&>(expressionElement).andExpression);
}

ExpressionElement::~ExpressionElement() {
}

void ExpressionElement::UpdateChildren() {
    tkOr.prnt = this;
    andExpression->prnt = this;
}

PrimeExpression::PrimeExpression() {
    type = AstNodeType::primeExpression;
}

PrimeExpression::~PrimeExpression() {
}

ExpressionInParenthesis::ExpressionInParenthesis() {
    type = AstNodeType::expressionInParenthesis;
}

ExpressionInParenthesis::~ExpressionInParenthesis() {
}

MemberMethod::MemberMethod() {
    type = AstNodeType::memberMethod;
}

MemberMethod::MemberMethod(const MemberMethod& memberMethod) {
    SetAstNode(memberMethod);
    
    memberMethodElements = std::move(const_cast<MemberMethod&>(memberMethod).memberMethodElements);
    memberMethodElementElement = std::move(const_cast<MemberMethod&>(memberMethod).memberMethodElementElement);
}

MemberMethod::~MemberMethod() {
}

NewElement::NewElement() {
    type = AstNodeType::newElement;
}

NewElement::~NewElement() {
}

NewArgumentsBlock::NewArgumentsBlock() {
    type = AstNodeType::newArgumentsBlock;
}

NewArgumentsBlock::~NewArgumentsBlock() {
}

TernaryOperationElement::TernaryOperationElement() {
    type = AstNodeType::ternaryOperationElement;
}

TernaryOperationElement::~TernaryOperationElement() {
}

AwaitElement::AwaitElement() {
    type = AstNodeType::awaitElement;
}

AwaitElement::~AwaitElement() {
}

AndExpression::AndExpression() {
    type = AstNodeType::andExpression;
}

AndExpression::~AndExpression() {
}

AndExpressionElement::AndExpressionElement() {
    type = AstNodeType::andExpressionElement;
}

AndExpressionElement::AndExpressionElement(const AndExpressionElement& andExpressionElement) {
    SetAstNode(andExpressionElement);
    
    tkAnd = andExpressionElement.tkAnd;
    notExpression = std::move(const_cast<AndExpressionElement&>(andExpressionElement).notExpression);
}

AndExpressionElement::~AndExpressionElement() {
}

void AndExpressionElement::UpdateChildren() {
    tkAnd.prnt = this;
    notExpression->prnt = this;
}

NotExpression::NotExpression() {
    type = AstNodeType::notExpression;
}

NotExpression::~NotExpression() {
}

NotExpressionElement::NotExpressionElement() {
    type = AstNodeType::notExpressionElement;
}

NotExpressionElement::~NotExpressionElement() {
}

void NotExpressionElement::UpdateChildren() {
    tkNot.prnt = this;
}

RelationalExpression::RelationalExpression() {
    type = AstNodeType::relationalExpression;
}

RelationalExpression::~RelationalExpression() {
}

RelationalExpressionElement::RelationalExpressionElement() {
    type = AstNodeType::relationalExpressionElement;
}

RelationalExpressionElement::RelationalExpressionElement(
    const RelationalExpressionElement& relationalExpressionElement) {
    SetAstNode(relationalExpressionElement);
    
    isEquals = relationalExpressionElement.isEquals;
    isNotEquals = relationalExpressionElement.isNotEquals;
    isLess = relationalExpressionElement.isLess;
    isLessOrEquals = relationalExpressionElement.isLessOrEquals;
    isGreater = relationalExpressionElement.isGreater;
    isGreaterOrEquals = relationalExpressionElement.isGreaterOrEquals;
    
    tkEquals = relationalExpressionElement.tkEquals;
    tkNotEquals = relationalExpressionElement.tkNotEquals;
    tkLess = relationalExpressionElement.tkLess;
    tkLessOrEquals = relationalExpressionElement.tkLessOrEquals;
    tkGreater = relationalExpressionElement.tkGreater;
    tkGreaterOrEquals = relationalExpressionElement.tkGreaterOrEquals;
    addingExpression = std::move(
        const_cast<RelationalExpressionElement&>(relationalExpressionElement).addingExpression);
}

RelationalExpressionElement::~RelationalExpressionElement() {
}

void RelationalExpressionElement::UpdateChildren() {
    if (!tkEquals.IsEmpty()) {
        tkEquals.prnt = this;
    }
    else if (!tkNotEquals.IsEmpty()) {
        tkNotEquals.prnt = this;
    }
    else if (!tkLess.IsEmpty()) {
        tkLess.prnt = this;
    }
    else if (!tkLessOrEquals.IsEmpty()) {
        tkLessOrEquals.prnt = this;
    }
    else if (!tkGreater.IsEmpty()) {
        tkGreater.prnt = this;
    }
    else if (!tkGreaterOrEquals.IsEmpty()) {
        tkGreaterOrEquals.prnt = this;
    }
    
    addingExpression->prnt = this;
}

AddingExpression::AddingExpression() {
    type = AstNodeType::addingExpression;
}

AddingExpression::~AddingExpression() {
}

AddingExpressionElement::AddingExpressionElement() {
    type = AstNodeType::addingExpressionElement;
}

AddingExpressionElement::AddingExpressionElement(const AddingExpressionElement& addingExpressionElement) {
    SetAstNode(addingExpressionElement);
    
    isMinus = addingExpressionElement.isMinus;
    isPlus = addingExpressionElement.isPlus;
    
    tkMinus = addingExpressionElement.tkMinus;
    tkPlus = addingExpressionElement.tkPlus;
    multiplyingExpression = std::move(
        const_cast<AddingExpressionElement&>(addingExpressionElement).multiplyingExpression);
}

AddingExpressionElement::~AddingExpressionElement() {
}

void AddingExpressionElement::UpdateChildren() {
    if (!tkMinus.IsEmpty()) {
        tkMinus.prnt = this;
    }
    else if (!tkPlus.IsEmpty()) {
        tkPlus.prnt = this;
    }
    
    multiplyingExpression->prnt = this;
}

MultiplyingExpression::MultiplyingExpression() {
    type = AstNodeType::multiplyingExpression;
}

MultiplyingExpression::~MultiplyingExpression() {
}

MultiplyingExpressionElement::MultiplyingExpressionElement() {
    type = AstNodeType::multiplyingExpressionElement;
}

MultiplyingExpressionElement::MultiplyingExpressionElement(
    const MultiplyingExpressionElement& multiplyingExpressionElement) {
    SetAstNode(multiplyingExpressionElement);
    
    isAsterisk = multiplyingExpressionElement.isAsterisk;
    isSolidus = multiplyingExpressionElement.isSolidus;
    isPercent = multiplyingExpressionElement.isPercent;
    
    tkAsterisk = multiplyingExpressionElement.tkAsterisk;
    tkSolidus = multiplyingExpressionElement.tkSolidus;
    tkPercent = multiplyingExpressionElement.tkPercent;
    signExpression = std::move(
        const_cast<MultiplyingExpressionElement&>(multiplyingExpressionElement).signExpression);
}

MultiplyingExpressionElement::~MultiplyingExpressionElement() {
}

void MultiplyingExpressionElement::UpdateChildren() {
    if (!tkAsterisk.IsEmpty()) {
        tkAsterisk.prnt = this;
    }
    else if (!tkSolidus.IsEmpty()) {
        tkSolidus.prnt = this;
    }
    else if (!tkPercent.IsEmpty()) {
        tkPercent.prnt = this;
    }
    
    signExpression->prnt = this;
}

SignExpression::SignExpression() {
    type = AstNodeType::signExpression;
}

SignExpression::~SignExpression() {
}

SignExpressionElement::SignExpressionElement() {
    type = AstNodeType::signExpressionElement;
}

SignExpressionElement::~SignExpressionElement() {
}

void SignExpressionElement::UpdateChildren() {
    if (!tkMinus.IsEmpty()) {
        tkMinus.prnt = this;
    }
    else if (!tkPlus.IsEmpty()) {
        tkPlus.prnt = this;
    }
}
