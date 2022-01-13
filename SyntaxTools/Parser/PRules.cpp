#include "PRules.h"

const PhEndHelper endHelper;

PRule::~PRule() {
}

bool PRule::Check(PStream& stream) {
    PStream newStream;
    newStream.Set(stream);
    
    if (!CheckAstNode(newStream)) {
        return false;
    }
    
    stream.Set(newStream);
    SetChecked();
    return true;
}

bool PrBlock::CheckAstNode(PStream& stream) {
    bool readyForBlockElement = stream.readyForBlockElement;
    stream.readyForBlockElement = true;
    
    PhOnceOrMore<PrBlockElement> onceOrMore;
    
    if (!onceOrMore.Check(stream)) {
        stream.readyForBlockElement = readyForBlockElement;
        return false;
    }
    
    stream.readyForBlockElement = readyForBlockElement;
    
    block = std::make_unique<Block>();
    
    std::vector<std::unique_ptr<PrBlockElement>>& helpers = onceOrMore.GetHelpers();
    block->blockElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        block->blockElements.push_back(*helpers[i]->GetBlockElement(block.get(), i));
        block->blockElements.back().UpdateChildren();
    }
    
    block->SetEntity(block->blockElements.front(), block->blockElements.back());
    return true;
}

std::unique_ptr<Block> PrBlock::GetBlock(void* prnt) {
    block->prnt = prnt;
    return std::move(block);
}

void PrBlock::Reset() {
    PHelper::Reset();
    block.reset();
}

bool PrBlockElement::CheckAstNode(PStream& stream) {
    PrPreprocessorRegionBlock preprocessorRegionBlock;
    PrPreprocessorIfBlock preprocessorIfBlock;
    PrVariablesBlock variablesBlock;
    PrFunctionsBlock functionsBlock;
    PrOperationsBlock operationsBlock;
    
    if (stream.state == PState::global) {
        PhAnyOf anyOf(&preprocessorRegionBlock, &preprocessorIfBlock, &variablesBlock, &functionsBlock,
            &operationsBlock, &endHelper);
        
        if (!anyOf.Check(stream)) {
            return false;
        }
    }
    else if (stream.state == PState::local) {
        PhAnyOf anyOf(&preprocessorRegionBlock, &preprocessorIfBlock, &variablesBlock, &operationsBlock, &endHelper);
        
        if (!anyOf.Check(stream)) {
            return false;
        }
    }
    
    blockElement = std::make_unique<BlockElement>();
    
    if (preprocessorRegionBlock.GetChecked()) {
        blockElement->preprocessorRegionBlock = preprocessorRegionBlock.GetPreprocessorRegionBlock(
            blockElement.get());
    }
    else if (preprocessorIfBlock.GetChecked()) {
        blockElement->preprocessorIfBlock = preprocessorIfBlock.GetPreprocessorIfBlock(blockElement.get());
    }
    else if (variablesBlock.GetChecked()) {
        blockElement->variablesBlock = variablesBlock.GetVariablesBlock(blockElement.get());
    }
    else if (functionsBlock.GetChecked()) {
        blockElement->functionsBlock = functionsBlock.GetFunctionsBlock(blockElement.get());
    }
    else if (operationsBlock.GetChecked()) {
        blockElement->operationsBlock = operationsBlock.GetOperationsBlock(blockElement.get());
    }
    
    if (blockElement->preprocessorRegionBlock.get() != nullptr) {
        blockElement->SetEntity(*blockElement->preprocessorRegionBlock);
    }
    else if (blockElement->preprocessorIfBlock.get() != nullptr) {
        blockElement->SetEntity(*blockElement->preprocessorIfBlock);
    }
    else if (blockElement->variablesBlock.get() != nullptr) {
        blockElement->SetEntity(*blockElement->variablesBlock);
    }
    else if (blockElement->functionsBlock.get() != nullptr) {
        blockElement->SetEntity(*blockElement->functionsBlock);
    }
    else if (blockElement->operationsBlock.get() != nullptr) {
        blockElement->SetEntity(*blockElement->operationsBlock);
    }
    
    return true;
}

std::unique_ptr<BlockElement> PrBlockElement::GetBlockElement(void* prnt, int index) {
    blockElement->prnt = prnt;
    blockElement->index = index;
    return std::move(blockElement);
}

void PrBlockElement::Reset() {
    PHelper::Reset();
    blockElement.reset();
}

bool PrPreprocessorRegionBlock::CheckAstNode(PStream& stream) {
    if (!stream.readyForBlockElement) {
        return false;
    }
    
    PrBlock block;
    PhOnceOrNot onceOrNot(&block);
    
    PhFromToken fromTokenTermNumberSignRegion(TokenType::termNumberSign);
    PhFromToken fromTokenTermRegion(TokenType::termRegion);
    PhFromToken fromTokenTermIdentifier(TokenType::termIdentifier);
    PhFromToken fromTokenTermNumberSignEndRegion(TokenType::termNumberSign);
    PhFromToken fromTokenTermEndRegion(TokenType::termEndRegion);
    PhAddition addition(&fromTokenTermNumberSignRegion, &fromTokenTermRegion, &fromTokenTermIdentifier, &onceOrNot,
        &fromTokenTermNumberSignEndRegion, &fromTokenTermEndRegion, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    preprocessorRegionBlock = std::make_unique<PreprocessorRegionBlock>();
    preprocessorRegionBlock->tkTermNumberSignRegion = fromTokenTermNumberSignRegion.GetToken(
        preprocessorRegionBlock.get());
    preprocessorRegionBlock->tkTermRegion = fromTokenTermRegion.GetToken(preprocessorRegionBlock.get());
    preprocessorRegionBlock->tkTermIdentifier = fromTokenTermIdentifier.GetToken(preprocessorRegionBlock.get());
    
    if (block.GetChecked()) {
        preprocessorRegionBlock->block = block.GetBlock(preprocessorRegionBlock.get());
    }
    
    preprocessorRegionBlock->tkTermNumberSignEndRegion = fromTokenTermNumberSignEndRegion.GetToken(
        preprocessorRegionBlock.get());
    preprocessorRegionBlock->tkTermEndRegion = fromTokenTermEndRegion.GetToken(preprocessorRegionBlock.get());
    
    preprocessorRegionBlock->SetEntity(preprocessorRegionBlock->tkTermNumberSignRegion,
        preprocessorRegionBlock->tkTermEndRegion);
    return true;
}

std::unique_ptr<PreprocessorRegionBlock> PrPreprocessorRegionBlock::GetPreprocessorRegionBlock(void* prnt) {
    preprocessorRegionBlock->prnt = prnt;
    return std::move(preprocessorRegionBlock);
}

void PrPreprocessorRegionBlock::Reset() {
    PHelper::Reset();
    preprocessorRegionBlock.reset();
}

bool PrPreprocessorIfBlock::CheckAstNode(PStream& stream) {
    if (!stream.readyForBlockElement) {
        return false;
    }
    
    PrBlock blockIf;
    PhOnceOrNot onceOrNotBlock(&blockIf);
    
    PrBlock blockElse;
    PhOnceOrNot onceOrNotBlockElse(&blockElse);
    
    PhFromToken fromTokenTermNumberSignElse(TokenType::termNumberSign);
    PhFromToken fromTokenTermElse(TokenType::termElse);
    PhAddition additionElse(&fromTokenTermNumberSignElse, &fromTokenTermElse, &onceOrNotBlockElse, &endHelper);
    
    PhFromToken fromTokenTermNumberSignIf(TokenType::termNumberSign);
    PhFromToken fromTokenTermIf(TokenType::termIf);
    PrPreprocessorExpression preprocessorExpression;
    PhFromToken fromTokenTermThen(TokenType::termThen);
    PhSeveral<PrPreprocessorIfBlockElement> several;
    PhOnceOrNot onceOrNotElse(&additionElse);
    PhFromToken fromTokenTermNumberSignEndIf(TokenType::termNumberSign);
    PhFromToken fromTokenTermEndIf(TokenType::termEndIf);
    PhAddition addition(&fromTokenTermNumberSignIf, &fromTokenTermIf, &preprocessorExpression, &fromTokenTermThen,
        &onceOrNotBlock, &several, &onceOrNotElse, &fromTokenTermNumberSignEndIf, &fromTokenTermEndIf, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    preprocessorIfBlock = std::make_unique<PreprocessorIfBlock>();
    preprocessorIfBlock->tkTermNumberSignIf = fromTokenTermNumberSignIf.GetToken(preprocessorIfBlock.get());
    preprocessorIfBlock->tkTermIf = fromTokenTermIf.GetToken(preprocessorIfBlock.get());
    preprocessorIfBlock->preprocessorExpression = preprocessorExpression.GetPreprocessorExpression(
        preprocessorIfBlock.get());
    preprocessorIfBlock->tkTermThen = fromTokenTermThen.GetToken(preprocessorIfBlock.get());
    
    if (blockIf.GetChecked()) {
        preprocessorIfBlock->blockIf = blockIf.GetBlock(preprocessorIfBlock.get());
    }
    
    std::vector<std::unique_ptr<PrPreprocessorIfBlockElement>>& helpers = several.GetHelpers();
    preprocessorIfBlock->preprocessorIfBlockElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        preprocessorIfBlock->preprocessorIfBlockElements.push_back(*helpers[i]->GetPreprocessorIfBlockElement(
            preprocessorIfBlock.get(), i));
        preprocessorIfBlock->preprocessorIfBlockElements.back().UpdateChildren();
    }
    
    if (fromTokenTermElse.GetChecked()) {
        preprocessorIfBlock->isTermElse = true;
        preprocessorIfBlock->tkTermNumberSignElse = fromTokenTermNumberSignElse.GetToken(
            preprocessorIfBlock.get());
        preprocessorIfBlock->tkTermElse = fromTokenTermElse.GetToken(preprocessorIfBlock.get());
        
        if (blockElse.GetChecked()) {
            preprocessorIfBlock->blockElse = blockElse.GetBlock(preprocessorIfBlock.get());
        }
    }
    
    preprocessorIfBlock->tkTermNumberSignEndIf = fromTokenTermNumberSignEndIf.GetToken(
        preprocessorIfBlock.get());
    preprocessorIfBlock->tkTermEndIf = fromTokenTermEndIf.GetToken(preprocessorIfBlock.get());
    
    preprocessorIfBlock->SetEntity(preprocessorIfBlock->tkTermNumberSignIf, preprocessorIfBlock->tkTermEndIf);
    return true;
}

std::unique_ptr<PreprocessorIfBlock> PrPreprocessorIfBlock::GetPreprocessorIfBlock(void* prnt) {
    preprocessorIfBlock->prnt = prnt;
    return std::move(preprocessorIfBlock);
}

void PrPreprocessorIfBlock::Reset() {
    PHelper::Reset();
    preprocessorIfBlock.reset();
}

bool PrPreprocessorIfBlockElement::CheckAstNode(PStream& stream) {
    PrBlock block;
    PhOnceOrNot onceOrNot(&block);
    
    PhFromToken fromTokenTermNumberSign(TokenType::termNumberSign);
    PhFromToken fromTokenTermElsIf(TokenType::termElsIf);
    PrPreprocessorExpression preprocessorExpression;
    PhFromToken fromTokenTermThen(TokenType::termThen);
    PhAddition addition(&fromTokenTermNumberSign, &fromTokenTermElsIf, &preprocessorExpression, &fromTokenTermThen,
        &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    preprocessorIfBlockElement = std::make_unique<PreprocessorIfBlockElement>();
    preprocessorIfBlockElement->tkTermNumberSign = fromTokenTermNumberSign.GetToken(
        preprocessorIfBlockElement.get());
    preprocessorIfBlockElement->tkTermElsIf = fromTokenTermElsIf.GetToken(preprocessorIfBlockElement.get());
    preprocessorIfBlockElement->preprocessorExpression =
        preprocessorExpression.GetPreprocessorExpression(preprocessorIfBlockElement.get());
    preprocessorIfBlockElement->tkTermThen = fromTokenTermThen.GetToken(preprocessorIfBlockElement.get());
    
    if (block.GetChecked()) {
        preprocessorIfBlockElement->block = block.GetBlock(preprocessorIfBlockElement.get());
    }
    
    if (preprocessorIfBlockElement->block.get() != nullptr) {
        preprocessorIfBlockElement->SetEntity(preprocessorIfBlockElement->tkTermNumberSign,
            *preprocessorIfBlockElement->block);
    }
    else {
        preprocessorIfBlockElement->SetEntity(preprocessorIfBlockElement->tkTermNumberSign,
            preprocessorIfBlockElement->tkTermThen);
    }
    
    return true;
}

std::unique_ptr<PreprocessorIfBlockElement> PrPreprocessorIfBlockElement::GetPreprocessorIfBlockElement(
    void* prnt, int index) {
    preprocessorIfBlockElement->prnt = prnt;
    preprocessorIfBlockElement->index = index;
    return std::move(preprocessorIfBlockElement);
}

void PrPreprocessorIfBlockElement::Reset() {
    PHelper::Reset();
    preprocessorIfBlockElement.reset();
}

bool PrPreprocessorExpression::CheckAstNode(PStream& stream) {
    PrPreprocessorAndExpression preprocessorAndExpression;
    PhSeveral<PrPreprocessorExpressionElement> several;
    PhAddition addition(&preprocessorAndExpression, &several, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    preprocessorExpression = std::make_unique<PreprocessorExpression>();
    preprocessorExpression->preprocessorAndExpression = preprocessorAndExpression.GetPreprocessorAndExpression(
        preprocessorExpression.get());
    
    std::vector<std::unique_ptr<PrPreprocessorExpressionElement>>& helpers = several.GetHelpers();
    preprocessorExpression->preprocessorExpressionElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        preprocessorExpression->preprocessorExpressionElements.push_back(
            *helpers[i]->GetPreprocessorExpressionElement(preprocessorExpression.get(), i));
        preprocessorExpression->preprocessorExpressionElements.back().UpdateChildren();
    }
    
    if (!preprocessorExpression->preprocessorExpressionElements.empty()) {
        preprocessorExpression->SetEntity(*preprocessorExpression->preprocessorAndExpression,
            preprocessorExpression->preprocessorExpressionElements.back());
    }
    else {
        preprocessorExpression->SetEntity(*preprocessorExpression->preprocessorAndExpression);
    }
    
    return true;
}

std::unique_ptr<PreprocessorExpression> PrPreprocessorExpression::GetPreprocessorExpression(void* prnt) {
    preprocessorExpression->prnt = prnt;
    return std::move(preprocessorExpression);
}

void PrPreprocessorExpression::Reset() {
    PHelper::Reset();
    preprocessorExpression.reset();
}

bool PrPreprocessorExpressionElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenTermOr(TokenType::termOr);
    PrPreprocessorAndExpression preprocessorAndExpression;
    PhAddition addition(&fromTokenTermOr, &preprocessorAndExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    preprocessorExpressionElement = std::make_unique<PreprocessorExpressionElement>();
    preprocessorExpressionElement->tkTermOr = fromTokenTermOr.GetToken(preprocessorExpressionElement.get());
    preprocessorExpressionElement->preprocessorAndExpression =
        preprocessorAndExpression.GetPreprocessorAndExpression(preprocessorExpressionElement.get());
    
    preprocessorExpressionElement->SetEntity(preprocessorExpressionElement->tkTermOr,
        *preprocessorExpressionElement->preprocessorAndExpression);
    return true;
}

std::unique_ptr<PreprocessorExpressionElement> PrPreprocessorExpressionElement::GetPreprocessorExpressionElement(
    void* prnt, int index) {
    preprocessorExpressionElement->prnt = prnt;
    preprocessorExpressionElement->index = index;
    return std::move(preprocessorExpressionElement);
}

void PrPreprocessorExpressionElement::Reset() {
    PHelper::Reset();
    preprocessorExpressionElement.reset();
}

bool PrPreprocessorPrimeExpression::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenTermLeftParenthesis(TokenType::termLeftParenthesis);
    PrPreprocessorExpression preprocessorExpression;
    PhFromToken fromTokenTermRightParenthesis(TokenType::termRightParenthesis);
    PhAddition additionParenthesis(&fromTokenTermLeftParenthesis, &preprocessorExpression,
        &fromTokenTermRightParenthesis, &endHelper);
    
    PrPreprocessorValue preprocessorValue;
    PhAnyOf anyOf(&preprocessorValue, &additionParenthesis, &endHelper);
    
    if (!anyOf.Check(stream)) {
        return false;
    }
    
    preprocessorPrimeExpression = std::make_unique<PreprocessorPrimeExpression>();
    
    if (preprocessorValue.GetChecked()) {
        preprocessorPrimeExpression->preprocessorValue = preprocessorValue.GetPreprocessorValue(
            preprocessorPrimeExpression.get());
    }
    else if (preprocessorExpression.GetChecked()) {
        preprocessorPrimeExpression->tkTermLeftParenthesis = fromTokenTermLeftParenthesis.GetToken(
            preprocessorPrimeExpression.get());
        preprocessorPrimeExpression->preprocessorExpression = preprocessorExpression.GetPreprocessorExpression(
            preprocessorPrimeExpression.get());
        preprocessorPrimeExpression->tkTermRightParenthesis = fromTokenTermRightParenthesis.GetToken(
            preprocessorPrimeExpression.get());
    }
    
    if (preprocessorPrimeExpression->preprocessorValue.get() != nullptr) {
        preprocessorPrimeExpression->SetEntity(*preprocessorPrimeExpression->preprocessorValue);
    }
    else if (preprocessorPrimeExpression->preprocessorExpression.get() != nullptr) {
        preprocessorPrimeExpression->SetEntity(preprocessorPrimeExpression->tkTermLeftParenthesis,
            preprocessorPrimeExpression->tkTermRightParenthesis);
    }
    
    return true;
}

std::unique_ptr<PreprocessorPrimeExpression> PrPreprocessorPrimeExpression::GetPreprocessorPrimeExpression(
    void* prnt) {
    preprocessorPrimeExpression->prnt = prnt;
    return std::move(preprocessorPrimeExpression);
}

void PrPreprocessorPrimeExpression::Reset() {
    PHelper::Reset();
    preprocessorPrimeExpression.reset();
}

bool PrPreprocessorValue::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenTermClient(TokenType::termClient);
    PhFromToken fromTokenTermAtClient(TokenType::termAtClient);
    PhFromToken fromTokenTermAtServer(TokenType::termAtServer);
    PhFromToken fromTokenTermMobileAppClient(TokenType::termMobileAppClient);
    PhFromToken fromTokenTermMobileAppServer(TokenType::termMobileAppServer);
    PhFromToken fromTokenTermThickClientOrdinaryApplication(TokenType::termThickClientOrdinaryApplication);
    PhFromToken fromTokenTermThickClientManagedApplication(TokenType::termThickClientManagedApplication);
    PhFromToken fromTokenTermServer(TokenType::termServer);
    PhFromToken fromTokenTermExternalConnection(TokenType::termExternalConnection);
    PhFromToken fromTokenTermThinClient(TokenType::termThinClient);
    PhFromToken fromTokenTermWebClient(TokenType::termWebClient);
    PhAnyOf anyOf(&fromTokenTermClient, &fromTokenTermAtClient, &fromTokenTermAtServer, &fromTokenTermMobileAppClient,
        &fromTokenTermMobileAppServer, &fromTokenTermThickClientOrdinaryApplication,
        &fromTokenTermThickClientManagedApplication, &fromTokenTermServer, &fromTokenTermExternalConnection,
        &fromTokenTermThinClient, &fromTokenTermWebClient, &endHelper);
    
    if (!anyOf.Check(stream)) {
        return false;
    }
    
    preprocessorValue = std::make_unique<PreprocessorValue>();
    
    if (fromTokenTermClient.GetChecked()) {
        preprocessorValue->isTermClient = true;
    }
    else if (fromTokenTermAtClient.GetChecked()) {
        preprocessorValue->isTermAtClient = true;
    }
    else if (fromTokenTermAtServer.GetChecked()) {
        preprocessorValue->isTermAtServer = true;
    }
    else if (fromTokenTermMobileAppClient.GetChecked()) {
        preprocessorValue->isTermMobileAppClient = true;
    }
    else if (fromTokenTermMobileAppServer.GetChecked()) {
        preprocessorValue->isTermMobileAppServer = true;
    }
    else if (fromTokenTermThickClientOrdinaryApplication.GetChecked()) {
        preprocessorValue->isTermThickClientOrdinaryApplication = true;
    }
    else if (fromTokenTermThickClientManagedApplication.GetChecked()) {
        preprocessorValue->isTermThickClientManagedApplication = true;
    }
    else if (fromTokenTermServer.GetChecked()) {
        preprocessorValue->isTermServer = true;
    }
    else if (fromTokenTermExternalConnection.GetChecked()) {
        preprocessorValue->isTermExternalConnection = true;
    }
    else if (fromTokenTermThinClient.GetChecked()) {
        preprocessorValue->isTermThinClient = true;
    }
    else if (fromTokenTermWebClient.GetChecked()) {
        preprocessorValue->isTermWebClient = true;
    }
    
    if (fromTokenTermClient.GetChecked()) {
        preprocessorValue->tkTermClient = fromTokenTermClient.GetToken(preprocessorValue.get());
    }
    else if (fromTokenTermAtClient.GetChecked()) {
        preprocessorValue->tkTermAtClient = fromTokenTermAtClient.GetToken(preprocessorValue.get());
    }
    else if (fromTokenTermAtServer.GetChecked()) {
        preprocessorValue->tkTermAtServer = fromTokenTermAtServer.GetToken(preprocessorValue.get());
    }
    else if (fromTokenTermMobileAppClient.GetChecked()) {
        preprocessorValue->tkTermMobileAppClient = fromTokenTermMobileAppClient.GetToken(
            preprocessorValue.get());
    }
    else if (fromTokenTermMobileAppServer.GetChecked()) {
        preprocessorValue->tkTermMobileAppServer = fromTokenTermMobileAppServer.GetToken(
            preprocessorValue.get());
    }
    else if (fromTokenTermThickClientOrdinaryApplication.GetChecked()) {
        preprocessorValue->tkTermThickClientOrdinaryApplication =
            fromTokenTermThickClientOrdinaryApplication.GetToken(preprocessorValue.get());
    }
    else if (fromTokenTermThickClientManagedApplication.GetChecked()) {
        preprocessorValue->tkTermThickClientManagedApplication =
            fromTokenTermThickClientManagedApplication.GetToken(preprocessorValue.get());
    }
    else if (fromTokenTermServer.GetChecked()) {
        preprocessorValue->tkTermServer = fromTokenTermServer.GetToken(preprocessorValue.get());
    }
    else if (fromTokenTermExternalConnection.GetChecked()) {
        preprocessorValue->tkTermExternalConnection = fromTokenTermExternalConnection.GetToken(
            preprocessorValue.get());
    }
    else if (fromTokenTermThinClient.GetChecked()) {
        preprocessorValue->tkTermThinClient = fromTokenTermThinClient.GetToken(preprocessorValue.get());
    }
    else if (fromTokenTermWebClient.GetChecked()) {
        preprocessorValue->tkTermWebClient = fromTokenTermWebClient.GetToken(preprocessorValue.get());
    }
    
    if (!preprocessorValue->tkTermClient.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermClient);
    }
    else if (!preprocessorValue->tkTermAtClient.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermAtClient);
    }
    else if (!preprocessorValue->tkTermAtServer.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermAtServer);
    }
    else if (!preprocessorValue->tkTermMobileAppClient.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermMobileAppClient);
    }
    else if (!preprocessorValue->tkTermMobileAppServer.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermMobileAppServer);
    }
    else if (!preprocessorValue->tkTermThickClientOrdinaryApplication.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermThickClientOrdinaryApplication);
    }
    else if (!preprocessorValue->tkTermThickClientManagedApplication.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermThickClientManagedApplication);
    }
    else if (!preprocessorValue->tkTermServer.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermServer);
    }
    else if (!preprocessorValue->tkTermExternalConnection.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermExternalConnection);
    }
    else if (!preprocessorValue->tkTermThinClient.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermThinClient);
    }
    else if (!preprocessorValue->tkTermWebClient.IsEmpty()) {
        preprocessorValue->SetEntity(preprocessorValue->tkTermWebClient);
    }
    
    return true;
}

std::unique_ptr<PreprocessorValue> PrPreprocessorValue::GetPreprocessorValue(void* prnt) {
    preprocessorValue->prnt = prnt;
    return std::move(preprocessorValue);
}

void PrPreprocessorValue::Reset() {
    PHelper::Reset();
    preprocessorValue.reset();
}

bool PrPreprocessorAndExpression::CheckAstNode(PStream& stream) {
    PrPreprocessorNotExpression preprocessorNotExpression;
    PhSeveral<PrPreprocessorAndExpressionElement> several;
    PhAddition addition(&preprocessorNotExpression, &several, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    preprocessorAndExpression = std::make_unique<PreprocessorAndExpression>();
    preprocessorAndExpression->preprocessorNotExpression =
        preprocessorNotExpression.GetPreprocessorNotExpression(preprocessorAndExpression.get());
    
    std::vector<std::unique_ptr<PrPreprocessorAndExpressionElement>>& helpers = several.GetHelpers();
    preprocessorAndExpression->preprocessorAndExpressionElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        preprocessorAndExpression->preprocessorAndExpressionElements.push_back(
            *helpers[i]->GetPreprocessorAndExpressionElement(preprocessorAndExpression.get(), i));
        preprocessorAndExpression->preprocessorAndExpressionElements.back().UpdateChildren();
    }
    
    
    if (!preprocessorAndExpression->preprocessorAndExpressionElements.empty()) {
        preprocessorAndExpression->SetEntity(*preprocessorAndExpression->preprocessorNotExpression,
            preprocessorAndExpression->preprocessorAndExpressionElements.back());
    }
    else {
        preprocessorAndExpression->SetEntity(*preprocessorAndExpression->preprocessorNotExpression);
    }
    
    return true;
}

std::unique_ptr<PreprocessorAndExpression> PrPreprocessorAndExpression::GetPreprocessorAndExpression(
    void* prnt) {
    preprocessorAndExpression->prnt = prnt;
    return std::move(preprocessorAndExpression);
}

void PrPreprocessorAndExpression::Reset() {
    PHelper::Reset();
    preprocessorAndExpression.reset();
}

bool PrPreprocessorAndExpressionElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenTermAnd(TokenType::termAnd);
    PrPreprocessorNotExpression preprocessorNotExpression;
    PhAddition addition(&fromTokenTermAnd, &preprocessorNotExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    preprocessorAndExpressionElement = std::make_unique<PreprocessorAndExpressionElement>();
    preprocessorAndExpressionElement->tkTermAnd = fromTokenTermAnd.GetToken(
        preprocessorAndExpressionElement.get());
    preprocessorAndExpressionElement->preprocessorNotExpression =
        preprocessorNotExpression.GetPreprocessorNotExpression(preprocessorAndExpressionElement.get());
    
    preprocessorAndExpressionElement->SetEntity(preprocessorAndExpressionElement->tkTermAnd,
        *preprocessorAndExpressionElement->preprocessorNotExpression);
    return true;
}

std::unique_ptr<PreprocessorAndExpressionElement> PrPreprocessorAndExpressionElement::GetPreprocessorAndExpressionElement(
    void* prnt, int index) {
    preprocessorAndExpressionElement->prnt = prnt;
    preprocessorAndExpressionElement->index = index;
    return std::move(preprocessorAndExpressionElement);
}

void PrPreprocessorAndExpressionElement::Reset() {
    PHelper::Reset();
    preprocessorAndExpressionElement.reset();
}

bool PrPreprocessorNotExpression::CheckAstNode(PStream& stream) {
    PhSeveral<PrPreprocessorNotExpressionElement> several;
    PrPreprocessorPrimeExpression preprocessorPrimeExpression;
    PhAddition addition(&several, &preprocessorPrimeExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    preprocessorNotExpression = std::make_unique<PreprocessorNotExpression>();
    
    std::vector<std::unique_ptr<PrPreprocessorNotExpressionElement>>& helpers = several.GetHelpers();
    preprocessorNotExpression->preprocessorNotExpressionElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        preprocessorNotExpression->preprocessorNotExpressionElements.push_back(
            *helpers[i]->GetPreprocessorNotExpressionElement(preprocessorNotExpression.get(), i));
        preprocessorNotExpression->preprocessorNotExpressionElements.back().UpdateChildren();
    }
    
    preprocessorNotExpression->preprocessorPrimeExpression =
        preprocessorPrimeExpression.GetPreprocessorPrimeExpression(preprocessorNotExpression.get());
    
    if (!preprocessorNotExpression->preprocessorNotExpressionElements.empty()) {
        preprocessorNotExpression->SetEntity(
            preprocessorNotExpression->preprocessorNotExpressionElements.front(),
            *preprocessorNotExpression->preprocessorPrimeExpression);
    }
    else {
        preprocessorNotExpression->SetEntity(*preprocessorNotExpression->preprocessorPrimeExpression);
    }
    
    return true;
}

std::unique_ptr<PreprocessorNotExpression> PrPreprocessorNotExpression::GetPreprocessorNotExpression(
    void* prnt) {
    preprocessorNotExpression->prnt = prnt;
    return std::move(preprocessorNotExpression);
}

void PrPreprocessorNotExpression::Reset() {
    PHelper::Reset();
    preprocessorNotExpression.reset();
}

bool PrPreprocessorNotExpressionElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenTermNot(TokenType::termNot);
    
    if (!fromTokenTermNot.Check(stream)) {
        return false;
    }
    
    preprocessorNotExpressionElement = std::make_unique<PreprocessorNotExpressionElement>();
    preprocessorNotExpressionElement->tkTermNot = fromTokenTermNot.GetToken(
        preprocessorNotExpressionElement.get());
    
    preprocessorNotExpressionElement->SetEntity(preprocessorNotExpressionElement->tkTermNot);
    return true;
}

std::unique_ptr<PreprocessorNotExpressionElement> PrPreprocessorNotExpressionElement::GetPreprocessorNotExpressionElement(
    void* prnt, int index) {
    preprocessorNotExpressionElement->prnt = prnt;
    preprocessorNotExpressionElement->index = index;
    return std::move(preprocessorNotExpressionElement);
}

void PrPreprocessorNotExpressionElement::Reset() {
    PHelper::Reset();
    preprocessorNotExpressionElement.reset();
}

bool PrVariablesBlock::CheckAstNode(PStream& stream) {
    if (!stream.readyForBlockElement) {
        return false;
    }
    
    PhOnceOrMore<PrVariablesBlockElement> onceOrMore;
    
    if (!onceOrMore.Check(stream)) {
        return false;
    }
    
    variablesBlock = std::make_unique<VariablesBlock>();
    
    std::vector<std::unique_ptr<PrVariablesBlockElement>>& helpers = onceOrMore.GetHelpers();
    variablesBlock->variablesBlockElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        variablesBlock->variablesBlockElements.push_back(*helpers[i]->GetVariablesBlockElement(
            variablesBlock.get(), i));
        variablesBlock->variablesBlockElements.back().UpdateChildren();
    }
    
    variablesBlock->SetEntity(variablesBlock->variablesBlockElements.front(),
        variablesBlock->variablesBlockElements.back());
    return true;
}

std::unique_ptr<VariablesBlock> PrVariablesBlock::GetVariablesBlock(void* prnt) {
    variablesBlock->prnt = prnt;
    return std::move(variablesBlock);
}

void PrVariablesBlock::Reset() {
    PHelper::Reset();
    variablesBlock.reset();
}

bool PrVariablesBlockElement::CheckAstNode(PStream& stream) {
    if (!stream.readyForBlockElement) {
        return false;
    }
    
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PhFromToken fromTokenVar(TokenType::var);
    PrVariable variable;
    PhSeveral<PrVariablesBlockElementElement> several;
    PhAddition addition(&fromTokenVar, &variable, &several, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    variablesBlockElement = std::make_unique<VariablesBlockElement>();
    variablesBlockElement->tkVar = fromTokenVar.GetToken(variablesBlockElement.get());
    variablesBlockElement->variable = variable.GetVariable(variablesBlockElement.get());
    
    std::vector<std::unique_ptr<PrVariablesBlockElementElement>>& helpers = several.GetHelpers();
    variablesBlockElement->variablesBlockElementElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        variablesBlockElement->variablesBlockElementElements.push_back(
            *helpers[i]->GetVariablesBlockElementElement(variablesBlockElement.get(), i));
        variablesBlockElement->variablesBlockElementElements.back().UpdateChildren();
    }
    
    if (fromTokenSemicolon.GetChecked()) {
        variablesBlockElement->tkSemicolon = fromTokenSemicolon.GetToken(variablesBlockElement.get());
    }
    
    if (!variablesBlockElement->tkSemicolon.IsEmpty()) {
        variablesBlockElement->SetEntity(variablesBlockElement->tkVar, variablesBlockElement->tkSemicolon);
    }
    else {
        if (!variablesBlockElement->variablesBlockElementElements.empty()) {
            variablesBlockElement->SetEntity(variablesBlockElement->tkVar,
                variablesBlockElement->variablesBlockElementElements.back());
        }
        else {
            variablesBlockElement->SetEntity(variablesBlockElement->tkVar, *variablesBlockElement->variable);
        }
    }
    
    return true;
}

std::unique_ptr<VariablesBlockElement> PrVariablesBlockElement::GetVariablesBlockElement(void* prnt,
    int index) {
    variablesBlockElement->prnt = prnt;
    variablesBlockElement->index = index;
    return std::move(variablesBlockElement);
}

void PrVariablesBlockElement::Reset() {
    PHelper::Reset();
    variablesBlockElement.reset();
}

bool PrVariablesBlockElementElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenComma(TokenType::comma);
    PrVariable variable;
    PhAddition addition(&fromTokenComma, &variable, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    variablesBlockElementElement = std::make_unique<VariablesBlockElementElement>();
    variablesBlockElementElement->tkComma = fromTokenComma.GetToken(variablesBlockElementElement.get());
    variablesBlockElementElement->variable = variable.GetVariable(variablesBlockElementElement.get());
    
    variablesBlockElementElement->SetEntity(variablesBlockElementElement->tkComma,
        *variablesBlockElementElement->variable);
    return true;
}

std::unique_ptr<VariablesBlockElementElement> PrVariablesBlockElementElement::GetVariablesBlockElementElement(
    void* prnt, int index) {
    variablesBlockElementElement->prnt = prnt;
    variablesBlockElementElement->index = index;
    return std::move(variablesBlockElementElement);
}

void PrVariablesBlockElementElement::Reset() {
    PHelper::Reset();
    variablesBlockElementElement.reset();
}

bool PrVariable::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenExport(TokenType::export_);
    PhOnceOrNot onceOrNot(&fromTokenExport);
    
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    
    if (stream.state == PState::global) {
        PhAddition addition(&fromTokenIdentifier, &onceOrNot, &endHelper);
        
        if (!addition.Check(stream)) {
            return false;
        }
    }
    else if (stream.state == PState::local) {
        if (!fromTokenIdentifier.Check(stream)) {
            return false;
        }
    }
    
    variable = std::make_unique<Variable>();
    variable->tkIdentifier = fromTokenIdentifier.GetToken(variable.get());
    
    if (fromTokenExport.GetChecked()) {
        variable->isExport = true;
    }
    
    if (fromTokenExport.GetChecked()) {
        variable->tkExport = fromTokenExport.GetToken(variable.get());
    }
    
    if (!variable->tkExport.IsEmpty()) {
        variable->SetEntity(variable->tkIdentifier, variable->tkExport);
    }
    else {
        variable->SetEntity(variable->tkIdentifier);
    }
    
    return true;
}

std::unique_ptr<Variable> PrVariable::GetVariable(void* prnt) {
    variable->prnt = prnt;
    return std::move(variable);
}

void PrVariable::Reset() {
    PHelper::Reset();
    variable.reset();
}

bool PrFunctionsBlock::CheckAstNode(PStream& stream) {
    if (!stream.readyForBlockElement) {
        return false;
    }
    
    PState state = stream.state;
    stream.state = PState::local;
    
    PhOnceOrMore<PrFunctionsBlockElement> onceOrMore;
    
    if (!onceOrMore.Check(stream)) {
        stream.state = state;
        return false;
    }
    
    stream.state = state;
    
    functionsBlock = std::make_unique<FunctionsBlock>();
    
    std::vector<std::unique_ptr<PrFunctionsBlockElement>>& helpers = onceOrMore.GetHelpers();
    functionsBlock->functionsBlockElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        functionsBlock->functionsBlockElements.push_back(*helpers[i]->GetFunctionsBlockElement(
            functionsBlock.get(), i));
        functionsBlock->functionsBlockElements.back().UpdateChildren();
    }
    
    functionsBlock->SetEntity(functionsBlock->functionsBlockElements.front(),
        functionsBlock->functionsBlockElements.back());
    return true;
}

std::unique_ptr<FunctionsBlock> PrFunctionsBlock::GetFunctionsBlock(void* prnt) {
    functionsBlock->prnt = prnt;
    return std::move(functionsBlock);
}

void PrFunctionsBlock::Reset() {
    PHelper::Reset();
    functionsBlock.reset();
}

bool PrFunctionsBlockElement::CheckAstNode(PStream& stream) {
    PrFunctionBlock functionBlock;
    PrProcedureBlock procedureBlock;
    PhAnyOf anyOf(&functionBlock, &procedureBlock, &endHelper);
    
    if (!anyOf.Check(stream)) {
        return false;
    }
    
    functionsBlockElement = std::make_unique<FunctionsBlockElement>();
    
    if (functionBlock.GetChecked()) {
        functionsBlockElement->functionBlock = functionBlock.GetFunctionBlock(functionsBlockElement.get());
        functionsBlockElement->procedureBlock = nullptr;
    }
    else if (procedureBlock.GetChecked()) {
        functionsBlockElement->functionBlock = nullptr;
        functionsBlockElement->procedureBlock = procedureBlock.GetProcedureBlock(functionsBlockElement.get());
    }
    
    if (functionsBlockElement->functionBlock.get() != nullptr) {
        functionsBlockElement->SetEntity(*functionsBlockElement->functionBlock);
    }
    else if (functionsBlockElement->procedureBlock.get() != nullptr) {
        functionsBlockElement->SetEntity(*functionsBlockElement->procedureBlock);
    }
    
    return true;
}

std::unique_ptr<FunctionsBlockElement> PrFunctionsBlockElement::GetFunctionsBlockElement(void* prnt,
    int index) {
    functionsBlockElement->prnt = prnt;
    functionsBlockElement->index = index;
    return std::move(functionsBlockElement);
}

void PrFunctionsBlockElement::Reset() {
    PHelper::Reset();
    functionsBlockElement.reset();
}

bool PrFunctionBlock::CheckAstNode(PStream& stream) {
    PrDirectiveOfPreprocessor directiveOfPreprocessor;
    PhOnceOrNot onceOrNotDirectiveOfPreprocessor(&directiveOfPreprocessor);
    
    PhFromToken fromTokenAsync(TokenType::async);
    PhOnceOrNot onceOrNotAsync(&fromTokenAsync);
    
    PrFunctionArgumentsBlock functionArgumentsBlock;
    PhOnceOrNot onceOrNotArguments(&functionArgumentsBlock);
    
    PhFromToken fromTokenExport(TokenType::export_);
    PhOnceOrNot onceOrNotExport(&fromTokenExport);
    
    PrBlock block;
    PhOnceOrNot onceOrNotBlock(&block);
    
    PhFromToken fromTokenFunction(TokenType::function);
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PhFromToken fromTokenLeftParenthesis(TokenType::leftParenthesis);
    PhFromToken fromTokenRightParenthesis(TokenType::rightParenthesis);
    PhFromToken fromTokenEndFunction(TokenType::endFunction);
    PhAddition addition(&onceOrNotDirectiveOfPreprocessor, &onceOrNotAsync, &fromTokenFunction, &fromTokenIdentifier,
        &fromTokenLeftParenthesis, &onceOrNotArguments, &fromTokenRightParenthesis, &onceOrNotExport, &onceOrNotBlock,
        &fromTokenEndFunction, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    functionBlock = std::make_unique<FunctionBlock>();
    
    if (directiveOfPreprocessor.GetChecked()) {
        functionBlock->directiveOfPreprocessor = directiveOfPreprocessor.GetDirectiveOfPreprocessor(
            functionBlock.get());
    }
    
    if (fromTokenAsync.GetChecked()) {
        functionBlock->isAsync = true;
        functionBlock->tkAsync = fromTokenAsync.GetToken(functionBlock.get());
    }
    
    functionBlock->tkFunction = fromTokenFunction.GetToken(functionBlock.get());
    functionBlock->tkIdentifier = fromTokenIdentifier.GetToken(functionBlock.get());
    functionBlock->tkLeftParenthesis = fromTokenLeftParenthesis.GetToken(functionBlock.get());
    
    if (functionArgumentsBlock.GetChecked()) {
        functionBlock->functionArgumentsBlock = functionArgumentsBlock.GetFunctionArgumentsBlock(
            functionBlock.get());
    }
    
    functionBlock->tkRightParenthesis = fromTokenRightParenthesis.GetToken(functionBlock.get());
    
    if (fromTokenExport.GetChecked()) {
        functionBlock->isExport = true;
        functionBlock->tkExport = fromTokenExport.GetToken(functionBlock.get());
    }
    
    if (block.GetChecked()) {
        functionBlock->block = block.GetBlock(functionBlock.get());
    }
    
    functionBlock->tkEndFunction = fromTokenEndFunction.GetToken(functionBlock.get());
    
    if (functionBlock->directiveOfPreprocessor.get() != nullptr) {
        functionBlock->SetEntity(*functionBlock->directiveOfPreprocessor, functionBlock->tkEndFunction);
    }
    else {
        if (!functionBlock->tkAsync.IsEmpty()) {
            functionBlock->SetEntity(functionBlock->tkAsync, functionBlock->tkEndFunction);
        }
        else {
            functionBlock->SetEntity(functionBlock->tkFunction, functionBlock->tkEndFunction);
        }
    }
    
    return true;
}

std::unique_ptr<FunctionBlock> PrFunctionBlock::GetFunctionBlock(void* prnt) {
    functionBlock->prnt = prnt;
    return std::move(functionBlock);
}

void PrFunctionBlock::Reset() {
    PHelper::Reset();
    functionBlock.reset();
}

bool PrProcedureBlock::CheckAstNode(PStream& stream) {
    PrDirectiveOfPreprocessor directiveOfPreprocessor;
    PhOnceOrNot onceOrNotDirectiveOfPreprocessor(&directiveOfPreprocessor);
    
    PhFromToken fromTokenAsync(TokenType::async);
    PhOnceOrNot onceOrNotAsync(&fromTokenAsync);
    
    PrFunctionArgumentsBlock functionArgumentsBlock;
    PhOnceOrNot onceOrNotArguments(&functionArgumentsBlock);
    
    PhFromToken fromTokenExport(TokenType::export_);
    PhOnceOrNot onceOrNotExport(&fromTokenExport);
    
    PrBlock block;
    PhOnceOrNot onceOrNotBlock(&block);
    
    PhFromToken fromTokenProcedure(TokenType::procedure);
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PhFromToken fromTokenLeftParenthesis(TokenType::leftParenthesis);
    PhFromToken fromTokenRightParenthesis(TokenType::rightParenthesis);
    PhFromToken fromTokenEndProcedure(TokenType::endProcedure);
    PhAddition addition(&onceOrNotDirectiveOfPreprocessor, &onceOrNotAsync, &fromTokenProcedure, &fromTokenIdentifier,
        &fromTokenLeftParenthesis, &onceOrNotArguments, &fromTokenRightParenthesis, &onceOrNotExport, &onceOrNotBlock,
        &fromTokenEndProcedure, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    procedureBlock = std::make_unique<ProcedureBlock>();
    
    if (directiveOfPreprocessor.GetChecked()) {
        procedureBlock->directiveOfPreprocessor = directiveOfPreprocessor.GetDirectiveOfPreprocessor(
            procedureBlock.get());
    }
    
    if (fromTokenAsync.GetChecked()) {
        procedureBlock->isAsync = true;
        procedureBlock->tkAsync = fromTokenAsync.GetToken(procedureBlock.get());
    }
    
    procedureBlock->tkProcedure = fromTokenProcedure.GetToken(procedureBlock.get());
    procedureBlock->tkIdentifier = fromTokenIdentifier.GetToken(procedureBlock.get());
    procedureBlock->tkLeftParenthesis = fromTokenLeftParenthesis.GetToken(procedureBlock.get());
    
    if (functionArgumentsBlock.GetChecked()) {
        procedureBlock->functionArgumentsBlock = functionArgumentsBlock.GetFunctionArgumentsBlock(
            procedureBlock.get());
    }
    
    procedureBlock->tkRightParenthesis = fromTokenRightParenthesis.GetToken(procedureBlock.get());
    
    if (fromTokenExport.GetChecked()) {
        procedureBlock->isExport = true;
        procedureBlock->tkExport = fromTokenExport.GetToken(procedureBlock.get());
    }
    
    if (block.GetChecked()) {
        procedureBlock->block = block.GetBlock(procedureBlock.get());
    }
    
    procedureBlock->tkEndProcedure = fromTokenEndProcedure.GetToken(procedureBlock.get());
    
    if (procedureBlock->directiveOfPreprocessor.get() != nullptr) {
        procedureBlock->SetEntity(*procedureBlock->directiveOfPreprocessor, procedureBlock->tkEndProcedure);
    }
    else {
        if (!procedureBlock->tkAsync.IsEmpty()) {
            procedureBlock->SetEntity(procedureBlock->tkAsync, procedureBlock->tkEndProcedure);
        }
        else {
            procedureBlock->SetEntity(procedureBlock->tkProcedure, procedureBlock->tkEndProcedure);
        }
    }
    
    return true;
}

std::unique_ptr<ProcedureBlock> PrProcedureBlock::GetProcedureBlock(void* prnt) {
    procedureBlock->prnt = prnt;
    return std::move(procedureBlock);
}

void PrProcedureBlock::Reset() {
    PHelper::Reset();
    procedureBlock.reset();
}

bool PrDirectiveOfPreprocessor::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenDirectiveAtClient(TokenType::directiveAtClient);
    PhFromToken fromTokenDirectiveAtServer(TokenType::directiveAtServer);
    PhFromToken fromTokenDirectiveAtServerNoContext(TokenType::directiveAtServerNoContext);
    PhFromToken fromTokenDirectiveAtClientAtServerNoContext(TokenType::directiveAtClientAtServerNoContext);
    PhFromToken fromTokenDirectiveAtClientAtServer(TokenType::directiveAtClientAtServer);
    PhAnyOf anyOfDirective(&fromTokenDirectiveAtClient, &fromTokenDirectiveAtServer,
        &fromTokenDirectiveAtServerNoContext, &fromTokenDirectiveAtClientAtServerNoContext,
        &fromTokenDirectiveAtClientAtServer, &endHelper);
    
    PhFromToken fromTokenDirectiveAmpersand(TokenType::directiveAmpersand);
    PhAddition addition(&fromTokenDirectiveAmpersand, &anyOfDirective, &endHelper);
    
    PrAnnotation annotation;
    PhAnyOf anyOf(&addition, &annotation, &endHelper);
    
    if (!anyOf.Check(stream)) {
        return false;
    }
    
    directiveOfPreprocessor = std::make_unique<DirectiveOfPreprocessor>();
    
    if (addition.GetChecked()) {
        directiveOfPreprocessor->tkDirectiveAmpersand = fromTokenDirectiveAmpersand.GetToken(
            directiveOfPreprocessor.get());
        
        if (fromTokenDirectiveAtClient.GetChecked()) {
            directiveOfPreprocessor->tkDirectiveAtClient = fromTokenDirectiveAtClient.GetToken(
                directiveOfPreprocessor.get());
            directiveOfPreprocessor->isDirectiveAtClient = true;
        }
        else if (fromTokenDirectiveAtServer.GetChecked()) {
            directiveOfPreprocessor->tkDirectiveAtServer = fromTokenDirectiveAtServer.GetToken(
                directiveOfPreprocessor.get());
            directiveOfPreprocessor->isDirectiveAtServer = true;
        }
        else if (fromTokenDirectiveAtServerNoContext.GetChecked()) {
            directiveOfPreprocessor->tkDirectiveAtServerNoContext =
                fromTokenDirectiveAtServerNoContext.GetToken(directiveOfPreprocessor.get());
            directiveOfPreprocessor->isDirectiveAtServerNoContext = true;
        }
        else if (fromTokenDirectiveAtClientAtServerNoContext.GetChecked()) {
            directiveOfPreprocessor->tkDirectiveAtClientAtServerNoContext =
                fromTokenDirectiveAtClientAtServerNoContext.GetToken(directiveOfPreprocessor.get());
            directiveOfPreprocessor->isDirectiveAtClientAtServerNoContext = true;
        }
        else if (fromTokenDirectiveAtClientAtServer.GetChecked()) {
            directiveOfPreprocessor->tkDirectiveAtClientAtServer = fromTokenDirectiveAtClientAtServer.GetToken(
                directiveOfPreprocessor.get());
            directiveOfPreprocessor->isDirectiveAtClientAtServer = true;
        }
    }
    else if (annotation.GetChecked()) {
        directiveOfPreprocessor->annotation = annotation.GetAnnotation(directiveOfPreprocessor.get());
    }
    
    if (!directiveOfPreprocessor->tkDirectiveAmpersand.IsEmpty()) {
        if (directiveOfPreprocessor->isDirectiveAtClient) {
            directiveOfPreprocessor->SetEntity(directiveOfPreprocessor->tkDirectiveAmpersand,
                directiveOfPreprocessor->tkDirectiveAtClient);
        }
        else if (directiveOfPreprocessor->isDirectiveAtServer) {
            directiveOfPreprocessor->SetEntity(directiveOfPreprocessor->tkDirectiveAmpersand,
                directiveOfPreprocessor->tkDirectiveAtServer);
        }
        else if (directiveOfPreprocessor->isDirectiveAtServerNoContext) {
            directiveOfPreprocessor->SetEntity(directiveOfPreprocessor->tkDirectiveAmpersand,
                directiveOfPreprocessor->tkDirectiveAtServerNoContext);
        }
        else if (directiveOfPreprocessor->isDirectiveAtClientAtServerNoContext) {
            directiveOfPreprocessor->SetEntity(directiveOfPreprocessor->tkDirectiveAmpersand,
                directiveOfPreprocessor->tkDirectiveAtClientAtServerNoContext);
        }
        else if (directiveOfPreprocessor->isDirectiveAtClientAtServer) {
            directiveOfPreprocessor->SetEntity(directiveOfPreprocessor->tkDirectiveAmpersand,
                directiveOfPreprocessor->tkDirectiveAtClientAtServer);
        }
    }
    else if (directiveOfPreprocessor->annotation.get() != nullptr) {
        directiveOfPreprocessor->SetEntity(*directiveOfPreprocessor->annotation);
    }
    
    return true;
}

std::unique_ptr<DirectiveOfPreprocessor> PrDirectiveOfPreprocessor::GetDirectiveOfPreprocessor(void* prnt) {
    directiveOfPreprocessor->prnt = prnt;
    return std::move(directiveOfPreprocessor);
}

void PrDirectiveOfPreprocessor::Reset() {
    PHelper::Reset();
    directiveOfPreprocessor.reset();
}

bool PrAnnotation::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenDirectiveBefore(TokenType::directiveBefore);
    PhFromToken fromTokenDirectiveAfter(TokenType::directiveAfter);
    PhFromToken fromTokenDirectiveInstead(TokenType::directiveInstead);
    PhAnyOf anyOf(&fromTokenDirectiveBefore, &fromTokenDirectiveAfter, &fromTokenDirectiveInstead, &endHelper);
    
    PhFromToken fromTokenDirectiveAmpersand(TokenType::directiveAmpersand);
    PhFromToken fromTokenDirectiveLeftParenthesis(TokenType::directiveLeftParenthesis);
    PhFromToken fromTokenDirectiveString(TokenType::directiveString);
    PhFromToken fromTokenDirectiveRightParenthesis(TokenType::directiveRightParenthesis);
    PhAddition addition(&fromTokenDirectiveAmpersand, &anyOf, &fromTokenDirectiveLeftParenthesis,
        &fromTokenDirectiveString, &fromTokenDirectiveRightParenthesis, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    annotation = std::make_unique<Annotation>();
    annotation->tkDirectiveAmpersand = fromTokenDirectiveAmpersand.GetToken(annotation.get());
    
    if (fromTokenDirectiveBefore.GetChecked()) {
        annotation->tkDirectiveBefore = fromTokenDirectiveBefore.GetToken(annotation.get());
        annotation->isDirectiveBefore = true;
    }
    else if (fromTokenDirectiveAfter.GetChecked()) {
        annotation->tkDirectiveAfter = fromTokenDirectiveAfter.GetToken(annotation.get());
        annotation->isDirectiveAfter = true;
    }
    else if (fromTokenDirectiveInstead.GetChecked()) {
        annotation->tkDirectiveInstead = fromTokenDirectiveInstead.GetToken(annotation.get());
        annotation->isDirectiveInstead = true;
    }
    
    annotation->tkDirectiveLeftParenthesis = fromTokenDirectiveLeftParenthesis.GetToken(annotation.get());
    annotation->tkDirectiveString = fromTokenDirectiveString.GetToken(annotation.get());
    annotation->tkDirectiveRightParenthesis = fromTokenDirectiveRightParenthesis.GetToken(annotation.get());
    
    annotation->SetEntity(annotation->tkDirectiveAmpersand, annotation->tkDirectiveRightParenthesis);
    return true;
}

std::unique_ptr<Annotation> PrAnnotation::GetAnnotation(void* prnt) {
    annotation->prnt = prnt;
    return std::move(annotation);
}

void PrAnnotation::Reset() {
    PHelper::Reset();
    annotation.reset();
}

bool PrFunctionArgumentsBlock::CheckAstNode(PStream& stream) {
    PrFunctionArgument functionArgument;
    PhSeveral<PrFunctionArgumentsBlockElement> several;
    PhAddition addition(&functionArgument, &several, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    functionArgumentsBlock = std::make_unique<FunctionArgumentsBlock>();
    functionArgumentsBlock->functionArgument = functionArgument.GetFunctionArgument(
        functionArgumentsBlock.get());
    
    std::vector<std::unique_ptr<PrFunctionArgumentsBlockElement>>& helpers = several.GetHelpers();
    functionArgumentsBlock->functionArgumentsBlockElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        functionArgumentsBlock->functionArgumentsBlockElements.push_back(
            *helpers[i]->GetFunctionArgumentsBlockElement(functionArgumentsBlock.get(), i));
        functionArgumentsBlock->functionArgumentsBlockElements.back().UpdateChildren();
    }
    
    if (!functionArgumentsBlock->functionArgumentsBlockElements.empty()) {
        functionArgumentsBlock->SetEntity(*functionArgumentsBlock->functionArgument,
            functionArgumentsBlock->functionArgumentsBlockElements.back());
    }
    else {
        functionArgumentsBlock->SetEntity(*functionArgumentsBlock->functionArgument,
            *functionArgumentsBlock->functionArgument);
    }
    
    return true;
}

std::unique_ptr<FunctionArgumentsBlock> PrFunctionArgumentsBlock::GetFunctionArgumentsBlock(void* prnt) {
    functionArgumentsBlock->prnt = prnt;
    return std::move(functionArgumentsBlock);
}

void PrFunctionArgumentsBlock::Reset() {
    PHelper::Reset();
    functionArgumentsBlock.reset();
}

bool PrFunctionArgumentsBlockElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenComma(TokenType::comma);
    PrFunctionArgument functionArgument;
    PhAddition addition(&fromTokenComma, &functionArgument, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    functionArgumentsBlockElement = std::make_unique<FunctionArgumentsBlockElement>();
    functionArgumentsBlockElement->tkComma = fromTokenComma.GetToken(functionArgumentsBlockElement.get());
    functionArgumentsBlockElement->functionArgument = functionArgument.GetFunctionArgument(
        functionArgumentsBlockElement.get());
    
    functionArgumentsBlockElement->SetEntity(functionArgumentsBlockElement->tkComma,
        *functionArgumentsBlockElement->functionArgument);
    return true;
}

std::unique_ptr<FunctionArgumentsBlockElement> PrFunctionArgumentsBlockElement::GetFunctionArgumentsBlockElement(
    void* prnt, int index) {
    functionArgumentsBlockElement->prnt = prnt;
    functionArgumentsBlockElement->index = index;
    return std::move(functionArgumentsBlockElement);
}

void PrFunctionArgumentsBlockElement::Reset() {
    PHelper::Reset();
    functionArgumentsBlockElement.reset();
}

bool PrFunctionArgument::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenVal(TokenType::val);
    PhOnceOrNot onceOrNotVal(&fromTokenVal);
    
    PhFromToken fromTokenEquals(TokenType::equals);
    PrValue value;
    PhAddition additionEquals(&fromTokenEquals, &value, &endHelper);
    
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PhOnceOrNot onceOrNotEquals(&additionEquals);
    PhAddition addition(&onceOrNotVal, &fromTokenIdentifier, &onceOrNotEquals, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    functionArgument = std::make_unique<FunctionArgument>();
    
    if (fromTokenVal.GetChecked()) {
        functionArgument->isVal = true;
        functionArgument->tkVal = fromTokenVal.GetToken(functionArgument.get());
    }
    
    functionArgument->tkIdentifier = fromTokenIdentifier.GetToken(functionArgument.get());
    
    if (value.GetChecked()) {
        functionArgument->value = value.GetValue(functionArgument.get());
    }
    
    if (onceOrNotEquals.GetChecked()) {
        functionArgument->tkEquals = fromTokenEquals.GetToken(functionArgument.get());
    }
    
    if (fromTokenVal.GetChecked()) {
        if (functionArgument->value.get() != nullptr) {
            functionArgument->SetEntity(functionArgument->tkVal, *functionArgument->value);
        }
        else {
            functionArgument->SetEntity(functionArgument->tkVal, functionArgument->tkIdentifier);
        }
    }
    else {
        if (functionArgument->value.get() != nullptr) {
            functionArgument->SetEntity(functionArgument->tkIdentifier, *functionArgument->value);
        }
        else {
            functionArgument->SetEntity(functionArgument->tkIdentifier);
        }
    }
    
    return true;
}

std::unique_ptr<FunctionArgument> PrFunctionArgument::GetFunctionArgument(void* prnt) {
    functionArgument->prnt = prnt;
    return std::move(functionArgument);
}

void PrFunctionArgument::Reset() {
    PHelper::Reset();
    functionArgument.reset();
}

bool PrValue::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSignedFloat(TokenType::signedFloat);
    PhFromToken fromTokenFloat(TokenType::float_);
    PhFromToken fromTokenDate(TokenType::date);
    PhFromToken fromTokenNull(TokenType::null);
    PhFromToken fromTokenUndefined(TokenType::undefined);
    PhFromToken fromTokenFalse(TokenType::false_);
    PhFromToken fromTokenTrue(TokenType::true_);
    PrString string;
    PhAnyOf anyOf(&fromTokenSignedFloat, &fromTokenFloat, &fromTokenDate, &fromTokenNull,
        &fromTokenUndefined, &fromTokenFalse, &fromTokenTrue, &string, &endHelper);
    
    if (!anyOf.Check(stream)) {
        return false;
    }
    
    value = std::make_unique<Value>();
    
    if (fromTokenSignedFloat.GetChecked()) {
        value->isSignedFloat = true;
        value->tkSignedFloat = fromTokenSignedFloat.GetToken(value.get());
    }
    else if (fromTokenFloat.GetChecked()) {
        value->isFloat = true;
        value->tkFloat = fromTokenFloat.GetToken(value.get());
    }
    else if (fromTokenDate.GetChecked()) {
        value->isDate = true;
        value->tkDate = fromTokenDate.GetToken(value.get());
    }
    else if (fromTokenNull.GetChecked()) {
        value->isNull = true;
        value->tkNull = fromTokenNull.GetToken(value.get());
    }
    else if (fromTokenUndefined.GetChecked()) {
        value->isUndefined = true;
        value->tkUndefined = fromTokenUndefined.GetToken(value.get());
    }
    else if (fromTokenFalse.GetChecked()) {
        value->isFalse = true;
        value->tkFalse = fromTokenFalse.GetToken(value.get());
    }
    else if (fromTokenTrue.GetChecked()) {
        value->isTrue = true;
        value->tkTrue = fromTokenTrue.GetToken(value.get());
    }
    else if (string.GetChecked()) {
        value->string = string.GetString(value.get());
    }
    
    if (value->isSignedFloat) {
        value->SetEntity(value->tkSignedFloat);
    }
    else if (value->isFloat) {
        value->SetEntity(value->tkFloat);
    }
    else if (value->isDate) {
        value->SetEntity(value->tkDate);
    }
    else if (value->isNull) {
        value->SetEntity(value->tkNull);
    }
    else if (value->isUndefined) {
        value->SetEntity(value->tkUndefined);
    }
    else if (value->isFalse) {
        value->SetEntity(value->tkFalse);
    }
    else if (value->isTrue) {
        value->SetEntity(value->tkTrue);
    }
    else if (value->string.get() != nullptr) {
        value->SetEntity(*value->string);
    }
    
    return true;
}

std::unique_ptr<Value> PrValue::GetValue(void* prnt) {
    value->prnt = prnt;
    return std::move(value);
}

void PrValue::Reset() {
    PHelper::Reset();
    value.reset();
}

bool PrString::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenStringBeginning(TokenType::stringBeginning);
    PhSeveral<PrStringElement> several;
    PhFromToken fromTokenStringEnding(TokenType::stringEnding);
    PhAddition addition(&fromTokenStringBeginning, &several, &fromTokenStringEnding, &endHelper);
    
    PhFromToken fromTokenString(TokenType::string);
    PhAnyOf anyOf(&fromTokenString, &addition, &endHelper);
    
    if (!anyOf.Check(stream)) {
        return false;
    }
    
    string = std::make_unique<String>();
    
    if (fromTokenString.GetChecked()) {
        string->tkString = fromTokenString.GetToken(string.get());
    }
    else if (fromTokenStringBeginning.GetChecked()) {
        string->tkStringBeginning = fromTokenStringBeginning.GetToken(string.get());
        
        std::vector<std::unique_ptr<PrStringElement>>& helpers = several.GetHelpers();
        string->stringElements.reserve(helpers.size());
        
        for (int i = 0; i < helpers.size(); i++) {
            string->stringElements.push_back(*helpers[i]->GetStringElement(string.get(), i));
            string->stringElements.back().UpdateChildren();
        }
        
        string->tkStringEnding = fromTokenStringEnding.GetToken(string.get());
    }
    
    if (!string->tkString.IsEmpty()) {
        string->SetEntity(string->tkString);
    }
    else {
        string->SetEntity(string->tkStringBeginning, string->tkStringEnding);
    }
    
    return true;
}

std::unique_ptr<String> PrString::GetString(void* prnt) {
    string->prnt = prnt;
    return std::move(string);
}

void PrString::Reset() {
    PHelper::Reset();
    string.reset();
}

bool PrStringElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenStringContinue(TokenType::stringContinue);
    
    if (!fromTokenStringContinue.Check(stream)) {
        return false;
    }
    
    stringElement = std::make_unique<StringElement>();
    stringElement->tkStringContinue = fromTokenStringContinue.GetToken(stringElement.get());
    
    stringElement->SetEntity(stringElement->tkStringContinue);
    return true;
}

std::unique_ptr<StringElement> PrStringElement::GetStringElement(void* prnt, int index) {
    stringElement->prnt = prnt;
    stringElement->index = index;
    return std::move(stringElement);
}

void PrStringElement::Reset() {
    PHelper::Reset();
    stringElement.reset();
}

bool PrOperationsBlock::CheckAstNode(PStream& stream) {
    if (!stream.readyForBlockElement) {
        return false;
    }
    
    PState state = stream.state;
    stream.state = PState::local;
    
    PhOnceOrMore<PrOperationsBlockElement> onceOrMore;
    
    if (!onceOrMore.Check(stream)) {
        stream.state = state;
        return false;
    }
    
    stream.state = state;
    
    operationsBlock = std::make_unique<OperationsBlock>();
    
    std::vector<std::unique_ptr<PrOperationsBlockElement>>& helpers = onceOrMore.GetHelpers();
    operationsBlock->operationsBlockElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        operationsBlock->operationsBlockElements.push_back(*helpers[i]->GetOperationsBlockElement(
            operationsBlock.get(), i));
        operationsBlock->operationsBlockElements.back().UpdateChildren();
    }
    
    operationsBlock->SetEntity(operationsBlock->operationsBlockElements.front(),
        operationsBlock->operationsBlockElements.back());
    return true;
}

std::unique_ptr<OperationsBlock> PrOperationsBlock::GetOperationsBlock(void* prnt) {
    operationsBlock->prnt = prnt;
    return std::move(operationsBlock);
}

void PrOperationsBlock::Reset() {
    PHelper::Reset();
    operationsBlock.reset();
}

bool PrOperationsBlockElement::CheckAstNode(PStream& stream) {
    if (!stream.readyForBlockElement) {
        return false;
    }
    
    PrSettingStatement settingStatement;
    PrMethodStatement methodStatement;
    PrExecuteStatement executeStatement;
    PrReturnStatement returnStatement;
    PrAwaitStatement awaitStatement;
    PrAddHandlerStatement addHandlerStatement;
    PrRemoveHandlerStatement removeHandlerStatement;
    PrIfStatement ifStatement;
    PrForToStatement forToStatement;
    PrForEachStatement forEachStatement;
    PrWhileStatement whileStatement;
    PrTryStatement tryStatement;
    PrRaiseStatement raiseStatement;
    PrLabelStatement labelStatement;
    PrGotoStatement gotoStatement;
    PrContinueStatement continueStatement;
    PrBreakStatement breakStatement;
    PrSemicolonStatement semicolonStatement;
    PhAnyOf anyOf(&settingStatement, &methodStatement, &executeStatement, &returnStatement, &awaitStatement,
        &addHandlerStatement, &removeHandlerStatement, &ifStatement, &forToStatement, &forEachStatement,
        &whileStatement, &tryStatement, &raiseStatement, &labelStatement, &gotoStatement, &continueStatement,
        &breakStatement, &semicolonStatement, &endHelper);
    
    if (!anyOf.Check(stream)) {
        return false;
    }
    
    operationsBlockElement = std::make_unique<OperationsBlockElement>();
    
    if (settingStatement.GetChecked()) {
        operationsBlockElement->settingStatement = settingStatement.GetSettingStatement(
            operationsBlockElement.get());
    }
    else if (methodStatement.GetChecked()) {
        operationsBlockElement->methodStatement = methodStatement.GetMethodStatement(
            operationsBlockElement.get());
    }
    else if (executeStatement.GetChecked()) {
        operationsBlockElement->executeStatement = executeStatement.GetExecuteStatement(
            operationsBlockElement.get());
    }
    else if (returnStatement.GetChecked()) {
        operationsBlockElement->returnStatement = returnStatement.GetReturnStatement(
            operationsBlockElement.get());
    }
    else if (awaitStatement.GetChecked()) {
        operationsBlockElement->awaitStatement = awaitStatement.GetAwaitStatement(operationsBlockElement.get());
    }
    else if (addHandlerStatement.GetChecked()) {
        operationsBlockElement->addHandlerStatement = addHandlerStatement.GetAddHandlerStatement(
            operationsBlockElement.get());
    }
    else if (removeHandlerStatement.GetChecked()) {
        operationsBlockElement->removeHandlerStatement = removeHandlerStatement.GetRemoveHandlerStatement(
            operationsBlockElement.get());
    }
    else if (ifStatement.GetChecked()) {
        operationsBlockElement->ifStatement = ifStatement.GetIfStatement(operationsBlockElement.get());
    }
    else if (forToStatement.GetChecked()) {
        operationsBlockElement->forToStatement = forToStatement.GetForToStatement(operationsBlockElement.get());
    }
    else if (forEachStatement.GetChecked()) {
        operationsBlockElement->forEachStatement = forEachStatement.GetForEachStatement(
            operationsBlockElement.get());
    }
    else if (whileStatement.GetChecked()) {
        operationsBlockElement->whileStatement = whileStatement.GetWhileStatement(operationsBlockElement.get());
    }
    else if (tryStatement.GetChecked()) {
        operationsBlockElement->tryStatement = tryStatement.GetTryStatement(operationsBlockElement.get());
    }
    else if (raiseStatement.GetChecked()) {
        operationsBlockElement->raiseStatement = raiseStatement.GetRaiseStatement(operationsBlockElement.get());
    }
    else if (labelStatement.GetChecked()) {
        operationsBlockElement->labelStatement = labelStatement.GetLabelStatement(operationsBlockElement.get());
    }
    else if (gotoStatement.GetChecked()) {
        operationsBlockElement->gotoStatement = gotoStatement.GetGotoStatement(operationsBlockElement.get());
    }
    else if (continueStatement.GetChecked()) {
        operationsBlockElement->continueStatement = continueStatement.GetContinueStatement(
            operationsBlockElement.get());
    }
    else if (breakStatement.GetChecked()) {
        operationsBlockElement->breakStatement = breakStatement.GetBreakStatement(operationsBlockElement.get());
    }
    else if (semicolonStatement.GetChecked()) {
        operationsBlockElement->semicolonStatement = semicolonStatement.GetSemicolonStatement(
            operationsBlockElement.get());
    }
    
    if (operationsBlockElement->settingStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->settingStatement);
    }
    else if (operationsBlockElement->methodStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->methodStatement);
    }
    else if (operationsBlockElement->executeStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->executeStatement);
    }
    else if (operationsBlockElement->returnStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->returnStatement);
    }
    else if (operationsBlockElement->awaitStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->awaitStatement);
    }
    else if (operationsBlockElement->addHandlerStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->addHandlerStatement);
    }
    else if (operationsBlockElement->removeHandlerStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->removeHandlerStatement);
    }
    else if (operationsBlockElement->ifStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->ifStatement);
    }
    else if (operationsBlockElement->forToStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->forToStatement);
    }
    else if (operationsBlockElement->forEachStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->forEachStatement);
    }
    else if (operationsBlockElement->whileStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->whileStatement);
    }
    else if (operationsBlockElement->tryStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->tryStatement);
    }
    else if (operationsBlockElement->raiseStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->raiseStatement);
    }
    else if (operationsBlockElement->labelStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->labelStatement);
    }
    else if (operationsBlockElement->gotoStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->gotoStatement);
    }
    else if (operationsBlockElement->continueStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->continueStatement);
    }
    else if (operationsBlockElement->breakStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->breakStatement);
    }
    else if (operationsBlockElement->semicolonStatement.get() != nullptr) {
        operationsBlockElement->SetEntity(*operationsBlockElement->semicolonStatement);
    }
    
    return true;
}

std::unique_ptr<OperationsBlockElement> PrOperationsBlockElement::GetOperationsBlockElement(void* prnt,
    int index) {
    operationsBlockElement->prnt = prnt;
    operationsBlockElement->index = index;
    return std::move(operationsBlockElement);
}

void PrOperationsBlockElement::Reset() {
    PHelper::Reset();
    operationsBlockElement.reset();
}

bool PrSettingStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PrMemberExpression memberExpression;
    PhFromToken fromTokenEquals(TokenType::equals);
    PrInitialExpression initialExpression;
    PhAddition addition(&memberExpression, &fromTokenEquals, &initialExpression, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    settingStatement = std::make_unique<SettingStatement>();
    settingStatement->memberExpression = memberExpression.GetMemberExpression(settingStatement.get());
    settingStatement->tkEquals = fromTokenEquals.GetToken(settingStatement.get());
    settingStatement->initialExpression = initialExpression.GetInitialExpression(settingStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        settingStatement->tkSemicolon = fromTokenSemicolon.GetToken(settingStatement.get());
    }
    
    if (!settingStatement->tkSemicolon.IsEmpty()) {
        settingStatement->SetEntity(*settingStatement->memberExpression, settingStatement->tkSemicolon);
    }
    else {
        settingStatement->SetEntity(*settingStatement->memberExpression,
            *settingStatement->initialExpression);
    }
    
    return true;
}

std::unique_ptr<SettingStatement> PrSettingStatement::GetSettingStatement(void* prnt) {
    settingStatement->prnt = prnt;
    return std::move(settingStatement);
}

void PrSettingStatement::Reset() {
    PHelper::Reset();
    settingStatement.reset();
}

bool PrMemberExpression::CheckAstNode(PStream& stream) {
    PhSeveral<PrMemberMethodElement> severalMemberMethodElement;
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PhSeveral<PrArrayElement> severalArrayElement;
    PhAddition addition(&severalMemberMethodElement, &fromTokenIdentifier, &severalArrayElement, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    memberExpression = std::make_unique<MemberExpression>();
    
    std::vector<std::unique_ptr<PrMemberMethodElement>>& helpersMemberMethodElement =
        severalMemberMethodElement.GetHelpers();
    memberExpression->memberMethodElements.reserve(helpersMemberMethodElement.size());
    
    for (int i = 0; i < helpersMemberMethodElement.size(); i++) {
        memberExpression->memberMethodElements.push_back(
            *helpersMemberMethodElement[i]->GetMemberMethodElement(memberExpression.get(), i));
        memberExpression->memberMethodElements.back().UpdateChildren();
    }
    
    memberExpression->tkIdentifier = fromTokenIdentifier.GetToken(memberExpression.get());
    
    std::vector<std::unique_ptr<PrArrayElement>>& helpersArrayElement = severalArrayElement.GetHelpers();
    memberExpression->arrayElements.reserve(helpersArrayElement.size());
    
    for (int i = 0; i < helpersArrayElement.size(); i++) {
        memberExpression->arrayElements.push_back(*helpersArrayElement[i]->GetArrayElement(
            memberExpression.get(), i));
        memberExpression->arrayElements.back().UpdateChildren();
    }
    
    if (!memberExpression->memberMethodElements.empty()) {
        if (!memberExpression->arrayElements.empty()) {
            memberExpression->SetEntity(memberExpression->memberMethodElements.front(),
                memberExpression->arrayElements.back());
        }
        else {
            memberExpression->SetEntity(memberExpression->memberMethodElements.front(),
                memberExpression->tkIdentifier);
        }
    }
    else {
        if (!memberExpression->arrayElements.empty()) {
            memberExpression->SetEntity(memberExpression->tkIdentifier,
                memberExpression->arrayElements.back());
        }
        else {
            memberExpression->SetEntity(memberExpression->tkIdentifier);
        }
    }
    
    return true;
}

std::unique_ptr<MemberExpression> PrMemberExpression::GetMemberExpression(void* prnt) {
    memberExpression->prnt = prnt;
    return std::move(memberExpression);
}

void PrMemberExpression::Reset() {
    PHelper::Reset();
    memberExpression.reset();
}

bool PrMemberMethodElement::CheckAstNode(PStream& stream) {
    PrMemberMethodElementElement memberMethodElementElement;
    PhFromToken fromTokenFullStop(TokenType::fullStop);
    PhAddition addition(&memberMethodElementElement, &fromTokenFullStop, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    memberMethodElement = std::make_unique<MemberMethodElement>();
    memberMethodElement->memberMethodElementElement = memberMethodElementElement.GetMemberMethodElementElement(
        memberMethodElement.get());
    memberMethodElement->tkFullStop = fromTokenFullStop.GetToken(memberMethodElement.get());
    
    memberMethodElement->SetEntity(*memberMethodElement->memberMethodElementElement,
        memberMethodElement->tkFullStop);
    return true;
}

std::unique_ptr<MemberMethodElement> PrMemberMethodElement::GetMemberMethodElement(void* prnt, int index) {
    memberMethodElement->prnt = prnt;
    memberMethodElement->index = index;
    return std::move(memberMethodElement);
}

void PrMemberMethodElement::Reset() {
    PHelper::Reset();
    memberMethodElement.reset();
}

bool PrMemberMethodElementElement::CheckAstNode(PStream& stream) {
    PrArgumentsBlock argumentsBlock;
    PhOnceOrNot onceOrNot(&argumentsBlock);
    
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PhSeveral<PrArrayElement> several;
    PhAddition addition(&fromTokenIdentifier, &onceOrNot, &several, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    memberMethodElementElement = std::make_unique<MemberMethodElementElement>();
    memberMethodElementElement->tkIdentifier = fromTokenIdentifier.GetToken(memberMethodElementElement.get());
    
    if (argumentsBlock.GetChecked()) {
        memberMethodElementElement->argumentsBlock = argumentsBlock.GetArgumentsBlock(
            memberMethodElementElement.get());
    }
    
    std::vector<std::unique_ptr<PrArrayElement>>& helpers = several.GetHelpers();
    memberMethodElementElement->arrayElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        memberMethodElementElement->arrayElements.push_back(*helpers[i]->GetArrayElement(
            memberMethodElementElement.get(), i));
        memberMethodElementElement->arrayElements.back().UpdateChildren();
    }
    
    if (!memberMethodElementElement->arrayElements.empty()) {
        memberMethodElementElement->SetEntity(memberMethodElementElement->tkIdentifier,
            memberMethodElementElement->arrayElements.back());
    }
    else if (memberMethodElementElement->argumentsBlock.get() != nullptr) {
        memberMethodElementElement->SetEntity(memberMethodElementElement->tkIdentifier,
            *memberMethodElementElement->argumentsBlock);
    }
    else {
        memberMethodElementElement->SetEntity(memberMethodElementElement->tkIdentifier);
    }
    
    return true;
}

std::unique_ptr<MemberMethodElementElement> PrMemberMethodElementElement::GetMemberMethodElementElement(
    void* prnt) {
    memberMethodElementElement->prnt = prnt;
    return std::move(memberMethodElementElement);
}

void PrMemberMethodElementElement::Reset() {
    PHelper::Reset();
    memberMethodElementElement.reset();
}

bool PrArgumentsBlock::CheckAstNode(PStream& stream) {
    PrInitialExpression initialExpression;
    PhOnceOrNot onceOrNot(&initialExpression);
    
    PhFromToken fromTokenLeftParenthesis(TokenType::leftParenthesis);
    PhSeveral<PrArgumentsBlockElement> several;
    PhFromToken fromTokenRightParenthesis(TokenType::rightParenthesis);
    PhAddition addition(&fromTokenLeftParenthesis, &onceOrNot, &several, &fromTokenRightParenthesis, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    argumentsBlock = std::make_unique<ArgumentsBlock>();
    argumentsBlock->tkLeftParenthesis = fromTokenLeftParenthesis.GetToken(argumentsBlock.get());
    
    if (initialExpression.GetChecked()) {
        argumentsBlock->initialExpression = initialExpression.GetInitialExpression(argumentsBlock.get());
    }
    
    std::vector<std::unique_ptr<PrArgumentsBlockElement>>& helpers = several.GetHelpers();
    argumentsBlock->argumentsBlockElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        argumentsBlock->argumentsBlockElements.push_back(*helpers[i]->GetArgumentsBlockElement(
            argumentsBlock.get(), i));
        argumentsBlock->argumentsBlockElements.back().UpdateChildren();
    }
    
    argumentsBlock->tkRightParenthesis = fromTokenRightParenthesis.GetToken(argumentsBlock.get());
    
    argumentsBlock->SetEntity(argumentsBlock->tkLeftParenthesis, argumentsBlock->tkRightParenthesis);
    return true;
}

std::unique_ptr<ArgumentsBlock> PrArgumentsBlock::GetArgumentsBlock(void* prnt) {
    argumentsBlock->prnt = prnt;
    return std::move(argumentsBlock);
}

void PrArgumentsBlock::Reset() {
    PHelper::Reset();
    argumentsBlock.reset();
}

bool PrArgumentsBlockElement::CheckAstNode(PStream& stream) {
    PrInitialExpression initialExpression;
    PhOnceOrNot onceOrNot(&initialExpression);
    
    PhFromToken fromTokenComma(TokenType::comma);
    PhAddition addition(&fromTokenComma, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    argumentsBlockElement = std::make_unique<ArgumentsBlockElement>();
    argumentsBlockElement->tkComma = fromTokenComma.GetToken(argumentsBlockElement.get());
    
    if (initialExpression.GetChecked()) {
        argumentsBlockElement->initialExpression = initialExpression.GetInitialExpression(
            argumentsBlockElement.get());
    }
    
    if (argumentsBlockElement->initialExpression.get() != nullptr) {
        argumentsBlockElement->SetEntity(argumentsBlockElement->tkComma,
            *argumentsBlockElement->initialExpression);
    }
    else {
        argumentsBlockElement->SetEntity(argumentsBlockElement->tkComma);
    }
    
    return true;
}

std::unique_ptr<ArgumentsBlockElement> PrArgumentsBlockElement::GetArgumentsBlockElement(void* prnt,
    int index) {
    argumentsBlockElement->prnt = prnt;
    argumentsBlockElement->index = index;
    return std::move(argumentsBlockElement);
}

void PrArgumentsBlockElement::Reset() {
    PHelper::Reset();
    argumentsBlockElement.reset();
}

bool PrArrayElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenLeftSquareBracket(TokenType::leftSquareBracket);
    PrInitialExpression initialExpression;
    PhFromToken fromTokenRightSquareBracket(TokenType::rightSquareBracket);
    PhAddition addition(&fromTokenLeftSquareBracket, &initialExpression, &fromTokenRightSquareBracket, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    arrayElement = std::make_unique<ArrayElement>();
    arrayElement->tkLeftSquareBracket = fromTokenLeftSquareBracket.GetToken(arrayElement.get());
    arrayElement->initialExpression = initialExpression.GetInitialExpression(arrayElement.get());
    arrayElement->tkRightSquareBracket = fromTokenRightSquareBracket.GetToken(arrayElement.get());
    
    arrayElement->SetEntity(arrayElement->tkLeftSquareBracket, arrayElement->tkRightSquareBracket);
    return true;
}

std::unique_ptr<ArrayElement> PrArrayElement::GetArrayElement(void* prnt, int index) {
    arrayElement->prnt = prnt;
    arrayElement->index = index;
    return std::move(arrayElement);
}

void PrArrayElement::Reset() {
    PHelper::Reset();
    arrayElement.reset();
}

bool PrMethodStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PrMethodExpression methodExpression;
    PhAddition addition(&methodExpression, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    methodStatement = std::make_unique<MethodStatement>();
    methodStatement->methodExpression = methodExpression.GetMethodExpression(methodStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        methodStatement->tkSemicolon = fromTokenSemicolon.GetToken(methodStatement.get());
    }
    
    if (!methodStatement->tkSemicolon.IsEmpty()) {
        methodStatement->SetEntity(*methodStatement->methodExpression, methodStatement->tkSemicolon);
    }
    else {
        methodStatement->SetEntity(*methodStatement->methodExpression);
    }
    
    return true;
}

std::unique_ptr<MethodStatement> PrMethodStatement::GetMethodStatement(void* prnt) {
    methodStatement->prnt = prnt;
    return std::move(methodStatement);
}

void PrMethodStatement::Reset() {
    PHelper::Reset();
    methodStatement.reset();
}

bool PrMethodExpression::CheckAstNode(PStream& stream) {
    PhSeveral<PrMemberMethodElement> several;
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PrArgumentsBlock argumentsBlock;
    PhAddition addition(&several, &fromTokenIdentifier, &argumentsBlock, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    methodExpression = std::make_unique<MethodExpression>();
    
    std::vector<std::unique_ptr<PrMemberMethodElement>>& helpers = several.GetHelpers();
    methodExpression->memberMethodElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        methodExpression->memberMethodElements.push_back(*helpers[i]->GetMemberMethodElement(
            methodExpression.get(), i));
        methodExpression->memberMethodElements.back().UpdateChildren();
    }
    
    methodExpression->tkIdentifier = fromTokenIdentifier.GetToken(methodExpression.get());
    methodExpression->argumentsBlock = argumentsBlock.GetArgumentsBlock(methodExpression.get());
    
    if (!methodExpression->memberMethodElements.empty()) {
        methodExpression->SetEntity(methodExpression->memberMethodElements.front(),
            *methodExpression->argumentsBlock);
    }
    else {
        methodExpression->SetEntity(methodExpression->tkIdentifier, *methodExpression->argumentsBlock);
    }
    
    return true;
}

std::unique_ptr<MethodExpression> PrMethodExpression::GetMethodExpression(void* prnt) {
    methodExpression->prnt = prnt;
    return std::move(methodExpression);
}

void PrMethodExpression::Reset() {
    PHelper::Reset();
    methodExpression.reset();
}

bool PrExecuteStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PhFromToken fromTokenExecute(TokenType::execute);
    PhFromToken fromTokenLeftParenthesis(TokenType::leftParenthesis);
    PrInitialExpression initialExpression;
    PhFromToken fromTokenRightParenthesis(TokenType::rightParenthesis);
    PhAddition addition(&fromTokenExecute, &fromTokenLeftParenthesis, &initialExpression, &fromTokenRightParenthesis,
        &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    executeStatement = std::make_unique<ExecuteStatement>();
    executeStatement->tkExecute = fromTokenExecute.GetToken(executeStatement.get());
    executeStatement->tkLeftParenthesis = fromTokenLeftParenthesis.GetToken(executeStatement.get());
    executeStatement->initialExpression = initialExpression.GetInitialExpression(executeStatement.get());
    executeStatement->tkRightParenthesis = fromTokenRightParenthesis.GetToken(executeStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        executeStatement->tkSemicolon = fromTokenSemicolon.GetToken(executeStatement.get());
    }
    
    if (!executeStatement->tkSemicolon.IsEmpty()) {
        executeStatement->SetEntity(executeStatement->tkExecute, executeStatement->tkSemicolon);
    }
    else {
        executeStatement->SetEntity(executeStatement->tkExecute, executeStatement->tkRightParenthesis);
    }
    
    return true;
}

std::unique_ptr<ExecuteStatement> PrExecuteStatement::GetExecuteStatement(void* prnt) {
    executeStatement->prnt = prnt;
    return std::move(executeStatement);
}

void PrExecuteStatement::Reset() {
    PHelper::Reset();
    executeStatement.reset();
}

bool PrReturnStatement::CheckAstNode(PStream& stream) {
    PrInitialExpression initialExpression;
    PhOnceOrNot onceOrNot(&initialExpression);
    
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNotSemicolon(&fromTokenSemicolon);
    
    PhFromToken fromTokenReturn(TokenType::return_);
    PhAddition addition(&fromTokenReturn, &onceOrNot, &onceOrNotSemicolon, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    returnStatement = std::make_unique<ReturnStatement>();
    returnStatement->tkReturn = fromTokenReturn.GetToken(returnStatement.get());
    
    if (initialExpression.GetChecked()) {
        returnStatement->initialExpression = initialExpression.GetInitialExpression(returnStatement.get());
    }
    
    if (fromTokenSemicolon.GetChecked()) {
        returnStatement->tkSemicolon = fromTokenSemicolon.GetToken(returnStatement.get());
    }
    
    if (!returnStatement->tkSemicolon.IsEmpty()) {
        returnStatement->SetEntity(returnStatement->tkReturn, returnStatement->tkSemicolon);
    }
    else if (returnStatement->initialExpression.get() != nullptr) {
        returnStatement->SetEntity(returnStatement->tkReturn, *returnStatement->initialExpression);
    }
    else {
        returnStatement->SetEntity(returnStatement->tkReturn);
    }
    
    return true;
}

std::unique_ptr<ReturnStatement> PrReturnStatement::GetReturnStatement(void* prnt) {
    returnStatement->prnt = prnt;
    return std::move(returnStatement);
}

void PrReturnStatement::Reset() {
    PHelper::Reset();
    returnStatement.reset();
}

bool PrAwaitStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNotSemicolon(&fromTokenSemicolon);
    
    PhFromToken fromTokenAwait(TokenType::await);
    PrInitialExpression initialExpression;
    PhAddition addition(&fromTokenAwait, &initialExpression, &onceOrNotSemicolon, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    awaitStatement = std::make_unique<AwaitStatement>();
    awaitStatement->tkAwait = fromTokenAwait.GetToken(awaitStatement.get());
    awaitStatement->initialExpression = initialExpression.GetInitialExpression(awaitStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        awaitStatement->tkSemicolon = fromTokenSemicolon.GetToken(awaitStatement.get());
    }
    
    if (!awaitStatement->tkSemicolon.IsEmpty()) {
        awaitStatement->SetEntity(awaitStatement->tkAwait, awaitStatement->tkSemicolon);
    }
    else {
        awaitStatement->SetEntity(awaitStatement->tkAwait, *awaitStatement->initialExpression);
    }
    
    return true;
}

std::unique_ptr<AwaitStatement> PrAwaitStatement::GetAwaitStatement(void* prnt) {
    awaitStatement->prnt = prnt;
    return std::move(awaitStatement);
}

void PrAwaitStatement::Reset() {
    PHelper::Reset();
    awaitStatement.reset();
}

PrHandlerStatementHelper::MemberMethodPair PrHandlerStatementHelper::GetMemberMethodPair(void* prnt,
    std::vector<std::unique_ptr<PrMemberMethodElement>>& helpers) {
    std::unique_ptr<MemberMethod> memberMethod = std::make_unique<MemberMethod>();
    memberMethod->prnt = prnt;
    
    int numOfElements = helpers.size();
    memberMethod->memberMethodElements.reserve(numOfElements - 1);
    
    for (int i = 0; i < numOfElements - 1; i++) {
        memberMethod->memberMethodElements.push_back(*helpers[i]->GetMemberMethodElement(memberMethod.get(), i));
        memberMethod->memberMethodElements.back().UpdateChildren();
    }
    
    std::unique_ptr<MemberMethodElement> memberMethodElement = std::move(helpers.back()->GetMemberMethodElement(
        memberMethod.get(), numOfElements - 1));
    memberMethod->memberMethodElementElement = std::move(memberMethodElement->memberMethodElementElement);
    memberMethod->memberMethodElementElement->prnt = memberMethod.get();
    
    if (!memberMethod->memberMethodElements.empty()) {
        memberMethod->SetEntity(memberMethod->memberMethodElements.front(), *memberMethod->memberMethodElementElement);
    }
    else {
        memberMethod->SetEntity(*memberMethod->memberMethodElementElement);
    }
    
    AstToken tkFullStop = memberMethodElement->tkFullStop;
    tkFullStop.prnt = prnt;
    return MemberMethodPair{std::move(memberMethod), tkFullStop};
}

bool PrAddHandlerStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PhFromToken fromTokenAddHandler(TokenType::addHandler);
    PhOnceOrMore<PrMemberMethodElement> onceOrMore;
    PhFromToken fromTokenIdentifierEvent(TokenType::identifier);
    PhFromToken fromTokenComma(TokenType::comma);
    PhSeveral<PrMemberMethodElement> several;
    PhFromToken fromTokenIdentifierHandler(TokenType::identifier);
    
    PhAddition addition(&fromTokenAddHandler, &onceOrMore, &fromTokenIdentifierEvent, &fromTokenComma, &several,
        &fromTokenIdentifierHandler, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    addHandlerStatement = std::make_unique<AddHandlerStatement>();
    addHandlerStatement->tkAddHandler = fromTokenAddHandler.GetToken(addHandlerStatement.get());
    
    std::vector<std::unique_ptr<PrMemberMethodElement>>& helpersEvent = onceOrMore.GetHelpers();
    PrHandlerStatementHelper::MemberMethodPair memberMethodPairEvent = PrHandlerStatementHelper::GetMemberMethodPair(
        addHandlerStatement.get(), helpersEvent);
    addHandlerStatement->memberMethodEvent = std::move(std::get<0>(memberMethodPairEvent));
    addHandlerStatement->tkFullStopEvent = std::get<1>(memberMethodPairEvent);
    
    addHandlerStatement->tkIdentifierEvent = fromTokenIdentifierEvent.GetToken(addHandlerStatement.get());
    addHandlerStatement->tkComma = fromTokenComma.GetToken(addHandlerStatement.get());
    
    std::vector<std::unique_ptr<PrMemberMethodElement>>& helpersHandler = several.GetHelpers();
    
    if (!helpersHandler.empty()) {
        PrHandlerStatementHelper::MemberMethodPair memberMethodPairHandler =
            PrHandlerStatementHelper::GetMemberMethodPair(addHandlerStatement.get(), helpersHandler);
        addHandlerStatement->memberMethodHandler = std::move(std::get<0>(memberMethodPairHandler));
        addHandlerStatement->tkFullStopHandler = std::get<1>(memberMethodPairHandler);
        
        addHandlerStatement->tkIdentifierHandler = fromTokenIdentifierHandler.GetToken(addHandlerStatement.get());
    }
    else {
        addHandlerStatement->tkIdentifierFunctionName = fromTokenIdentifierHandler.GetToken(addHandlerStatement.get());
    }
    
    if (fromTokenSemicolon.GetChecked()) {
        addHandlerStatement->tkSemicolon = fromTokenSemicolon.GetToken(addHandlerStatement.get());
    }
    
    if (!addHandlerStatement->tkSemicolon.IsEmpty()) {
        addHandlerStatement->SetEntity(addHandlerStatement->tkAddHandler, addHandlerStatement->tkSemicolon);
    }
    else {
        if (!addHandlerStatement->tkIdentifierHandler.IsEmpty()) {
            addHandlerStatement->SetEntity(addHandlerStatement->tkAddHandler, addHandlerStatement->tkIdentifierHandler);
        }
        else {
            addHandlerStatement->SetEntity(addHandlerStatement->tkAddHandler,
                addHandlerStatement->tkIdentifierFunctionName);
        }
    }
    
    return true;
}

std::unique_ptr<AddHandlerStatement> PrAddHandlerStatement::GetAddHandlerStatement(void* prnt) {
    addHandlerStatement->prnt = prnt;
    return std::move(addHandlerStatement);
}

void PrAddHandlerStatement::Reset() {
    PHelper::Reset();
    addHandlerStatement.reset();
}

bool PrRemoveHandlerStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PhFromToken fromTokenRemoveHandler(TokenType::removeHandler);
    PhOnceOrMore<PrMemberMethodElement> onceOrMore;
    PhFromToken fromTokenIdentifierEvent(TokenType::identifier);
    PhFromToken fromTokenComma(TokenType::comma);
    PhSeveral<PrMemberMethodElement> several;
    PhFromToken fromTokenIdentifierHandler(TokenType::identifier);
    
    PhAddition addition(&fromTokenRemoveHandler, &onceOrMore, &fromTokenIdentifierEvent, &fromTokenComma, &several,
        &fromTokenIdentifierHandler, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    removeHandlerStatement = std::make_unique<RemoveHandlerStatement>();
    removeHandlerStatement->tkRemoveHandler = fromTokenRemoveHandler.GetToken(removeHandlerStatement.get());
    
    std::vector<std::unique_ptr<PrMemberMethodElement>>& helpersEvent = onceOrMore.GetHelpers();
    PrHandlerStatementHelper::MemberMethodPair memberMethodPairEvent = PrHandlerStatementHelper::GetMemberMethodPair(
        removeHandlerStatement.get(), helpersEvent);
    removeHandlerStatement->memberMethodEvent = std::move(std::get<0>(memberMethodPairEvent));
    removeHandlerStatement->tkFullStopEvent = std::get<1>(memberMethodPairEvent);
    
    removeHandlerStatement->tkIdentifierEvent = fromTokenIdentifierEvent.GetToken(removeHandlerStatement.get());
    removeHandlerStatement->tkComma = fromTokenComma.GetToken(removeHandlerStatement.get());
    
    std::vector<std::unique_ptr<PrMemberMethodElement>>& helpersHandler = several.GetHelpers();
    
    if (!helpersHandler.empty()) {
        PrHandlerStatementHelper::MemberMethodPair memberMethodPairHandler =
            PrHandlerStatementHelper::GetMemberMethodPair(removeHandlerStatement.get(), helpersHandler);
        removeHandlerStatement->memberMethodHandler = std::move(std::get<0>(memberMethodPairHandler));
        removeHandlerStatement->tkFullStopHandler = std::get<1>(memberMethodPairHandler);
        
        removeHandlerStatement->tkIdentifierHandler = fromTokenIdentifierHandler.GetToken(removeHandlerStatement.get());
    }
    else {
        removeHandlerStatement->tkIdentifierFunctionName =
            fromTokenIdentifierHandler.GetToken(removeHandlerStatement.get());
    }
    
    if (fromTokenSemicolon.GetChecked()) {
        removeHandlerStatement->tkSemicolon = fromTokenSemicolon.GetToken(removeHandlerStatement.get());
    }
    
    if (!removeHandlerStatement->tkSemicolon.IsEmpty()) {
        removeHandlerStatement->SetEntity(removeHandlerStatement->tkRemoveHandler,
            removeHandlerStatement->tkSemicolon);
    }
    else {
        if (!removeHandlerStatement->tkIdentifierHandler.IsEmpty()) {
            removeHandlerStatement->SetEntity(removeHandlerStatement->tkRemoveHandler,
                removeHandlerStatement->tkIdentifierHandler);
        }
        else {
            removeHandlerStatement->SetEntity(removeHandlerStatement->tkRemoveHandler,
                removeHandlerStatement->tkIdentifierFunctionName);
        }
    }
    
    return true;
}

std::unique_ptr<RemoveHandlerStatement> PrRemoveHandlerStatement::GetRemoveHandlerStatement(void* prnt) {
    removeHandlerStatement->prnt = prnt;
    return std::move(removeHandlerStatement);
}

void PrRemoveHandlerStatement::Reset() {
    PHelper::Reset();
    removeHandlerStatement.reset();
}

bool PrIfStatement::CheckAstNode(PStream& stream) {
    PrBlock blockIf;
    PhOnceOrNot onceOrNotIf(&blockIf);
    
    PrBlock blockElse;
    PhOnceOrNot onceOrNotElseB(&blockElse);
    
    PhFromToken fromTokenElse(TokenType::else_);
    PhAddition additionElse(&fromTokenElse, &onceOrNotElseB, &endHelper);
    
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNotSemicolon(&fromTokenSemicolon);
    
    PhFromToken fromTokenIf(TokenType::if_);
    PrInitialExpression initialExpression;
    PhFromToken fromTokenThen(TokenType::then);
    PhSeveral<PrIfStatementElement> several;
    PhOnceOrNot onceOrNotElseA(&additionElse);
    PhFromToken fromTokenEndIf(TokenType::endIf);
    PhAddition addition(&fromTokenIf, &initialExpression, &fromTokenThen, &onceOrNotIf, &several, &onceOrNotElseA,
        &fromTokenEndIf, &onceOrNotSemicolon, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    ifStatement = std::make_unique<IfStatement>();
    ifStatement->tkIf = fromTokenIf.GetToken(ifStatement.get());
    ifStatement->initialExpression = initialExpression.GetInitialExpression(ifStatement.get());
    ifStatement->tkThen = fromTokenThen.GetToken(ifStatement.get());
    
    if (blockIf.GetChecked()) {
        ifStatement->blockIf = blockIf.GetBlock(ifStatement.get());
    }
    
    std::vector<std::unique_ptr<PrIfStatementElement>>& helpers = several.GetHelpers();
    ifStatement->ifStatementElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        ifStatement->ifStatementElements.push_back(*helpers[i]->GetIfStatementElement(ifStatement.get(), i));
        ifStatement->ifStatementElements.back().UpdateChildren();
    }
    
    if (fromTokenElse.GetChecked()) {
        ifStatement->isElse = true;
        ifStatement->tkElse = fromTokenElse.GetToken(ifStatement.get());
        
        if (blockElse.GetChecked()) {
            ifStatement->blockElse = blockElse.GetBlock(ifStatement.get());
        }
    }
    
    ifStatement->tkEndIf = fromTokenEndIf.GetToken(ifStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        ifStatement->tkSemicolon = fromTokenSemicolon.GetToken(ifStatement.get());
    }
    
    if (!ifStatement->tkSemicolon.IsEmpty()) {
        ifStatement->SetEntity(ifStatement->tkIf, ifStatement->tkSemicolon);
    }
    else {
        ifStatement->SetEntity(ifStatement->tkIf, ifStatement->tkEndIf);
    }
    
    return true;
}

std::unique_ptr<IfStatement> PrIfStatement::GetIfStatement(void* prnt) {
    ifStatement->prnt = prnt;
    return std::move(ifStatement);
}

void PrIfStatement::Reset() {
    PHelper::Reset();
    ifStatement.reset();
}

bool PrIfStatementElement::CheckAstNode(PStream& stream) {
    PrBlock block;
    PhOnceOrNot onceOrNot(&block);
    
    PhFromToken fromTokenElsIf(TokenType::elsIf);
    PrInitialExpression initialExpression;
    PhFromToken fromTokenThen(TokenType::then);
    PhAddition addition(&fromTokenElsIf, &initialExpression, &fromTokenThen, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    ifStatementElement = std::make_unique<IfStatementElement>();
    ifStatementElement->tkElsIf = fromTokenElsIf.GetToken(ifStatementElement.get());
    ifStatementElement->initialExpression = initialExpression.GetInitialExpression(ifStatementElement.get());
    ifStatementElement->tkThen = fromTokenThen.GetToken(ifStatementElement.get());
    
    if (block.GetChecked()) {
        ifStatementElement->block = block.GetBlock(ifStatementElement.get());
    }
    
    if (ifStatementElement->block.get() != nullptr) {
        ifStatementElement->SetEntity(ifStatementElement->tkElsIf, *ifStatementElement->block);
    }
    else {
        ifStatementElement->SetEntity(ifStatementElement->tkElsIf, ifStatementElement->tkThen);
    }
    
    return true;
}

std::unique_ptr<IfStatementElement> PrIfStatementElement::GetIfStatementElement(void* prnt, int index) {
    ifStatementElement->prnt = prnt;
    ifStatementElement->index = index;
    return std::move(ifStatementElement);
}

void PrIfStatementElement::Reset() {
    PHelper::Reset();
    ifStatementElement.reset();
}

bool PrForToStatement::CheckAstNode(PStream& stream) {
    PrBlock block;
    PhOnceOrNot onceOrNot(&block);
    
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNotSemicolon(&fromTokenSemicolon);
    
    PhFromToken fromTokenFor(TokenType::for_);
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PhFromToken fromTokenEquals(TokenType::equals);
    PrInitialExpression initialExpressionA;
    PhFromToken fromTokenTo(TokenType::to);
    PrInitialExpression initialExpressionB;
    PhFromToken fromTokenDo(TokenType::do_);
    PhFromToken fromTokenEndDo(TokenType::endDo);
    PhAddition addition(&fromTokenFor, &fromTokenIdentifier, &fromTokenEquals, &initialExpressionA, &fromTokenTo,
        &initialExpressionB, &fromTokenDo, &onceOrNot, &fromTokenEndDo, &onceOrNotSemicolon, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    forToStatement = std::make_unique<ForToStatement>();
    forToStatement->tkFor = fromTokenFor.GetToken(forToStatement.get());
    forToStatement->tkIdentifier = fromTokenIdentifier.GetToken(forToStatement.get());
    forToStatement->tkEquals = fromTokenEquals.GetToken(forToStatement.get());
    forToStatement->initialExpressionA = initialExpressionA.GetInitialExpression(forToStatement.get());
    forToStatement->tkTo = fromTokenTo.GetToken(forToStatement.get());
    forToStatement->initialExpressionB = initialExpressionB.GetInitialExpression(forToStatement.get());
    forToStatement->tkDo = fromTokenDo.GetToken(forToStatement.get());
    
    if (block.GetChecked()) {
        forToStatement->block = block.GetBlock(forToStatement.get());
    }
    
    forToStatement->tkEndDo = fromTokenEndDo.GetToken(forToStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        forToStatement->tkSemicolon = fromTokenSemicolon.GetToken(forToStatement.get());
    }
    
    if (!forToStatement->tkSemicolon.IsEmpty()) {
        forToStatement->SetEntity(forToStatement->tkFor, forToStatement->tkSemicolon);
    }
    else {
        forToStatement->SetEntity(forToStatement->tkFor, forToStatement->tkEndDo);
    }
    
    return true;
}

std::unique_ptr<ForToStatement> PrForToStatement::GetForToStatement(void* prnt) {
    forToStatement->prnt = prnt;
    return std::move(forToStatement);
}

void PrForToStatement::Reset() {
    PHelper::Reset();
    forToStatement.reset();
}

bool PrForEachStatement::CheckAstNode(PStream& stream) {
    PrBlock block;
    PhOnceOrNot onceOrNot(&block);
    
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNotSemicolon(&fromTokenSemicolon);
    
    PhFromToken fromTokenFor(TokenType::for_);
    PhFromToken fromTokenEach(TokenType::each);
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PhFromToken fromTokenIn(TokenType::in);
    PrInitialExpression initialExpression;
    PhFromToken fromTokenDo(TokenType::do_);
    PhFromToken fromTokenEndDo(TokenType::endDo);
    PhAddition addition(&fromTokenFor, &fromTokenEach, &fromTokenIdentifier, &fromTokenIn, &initialExpression,
        &fromTokenDo, &onceOrNot, &fromTokenEndDo, &onceOrNotSemicolon, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    forEachStatement = std::make_unique<ForEachStatement>();
    forEachStatement->tkFor = fromTokenFor.GetToken(forEachStatement.get());
    forEachStatement->tkEach = fromTokenEach.GetToken(forEachStatement.get());
    forEachStatement->tkIdentifier = fromTokenIdentifier.GetToken(forEachStatement.get());
    forEachStatement->tkIn = fromTokenIn.GetToken(forEachStatement.get());
    forEachStatement->initialExpression = initialExpression.GetInitialExpression(forEachStatement.get());
    forEachStatement->tkDo = fromTokenDo.GetToken(forEachStatement.get());
    
    if (block.GetChecked()) {
        forEachStatement->block = block.GetBlock(forEachStatement.get());
    }
    
    forEachStatement->tkEndDo = fromTokenEndDo.GetToken(forEachStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        forEachStatement->tkSemicolon = fromTokenSemicolon.GetToken(forEachStatement.get());
    }
    
    if (!forEachStatement->tkSemicolon.IsEmpty()) {
        forEachStatement->SetEntity(forEachStatement->tkFor, forEachStatement->tkSemicolon);
    }
    else {
        forEachStatement->SetEntity(forEachStatement->tkFor, forEachStatement->tkEndDo);
    }
    
    return true;
}

std::unique_ptr<ForEachStatement> PrForEachStatement::GetForEachStatement(void* prnt) {
    forEachStatement->prnt = prnt;
    return std::move(forEachStatement);
}

void PrForEachStatement::Reset() {
    PHelper::Reset();
    forEachStatement.reset();
}

bool PrWhileStatement::CheckAstNode(PStream& stream) {
    PrBlock block;
    PhOnceOrNot onceOrNot(&block);
    
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNotSemicolon(&fromTokenSemicolon);
    
    PhFromToken fromTokenWhile(TokenType::while_);
    PrInitialExpression initialExpression;
    PhFromToken fromTokenDo(TokenType::do_);
    PhFromToken fromTokenEndDo(TokenType::endDo);
    PhAddition addition(&fromTokenWhile, &initialExpression, &fromTokenDo, &onceOrNot, &fromTokenEndDo,
        &onceOrNotSemicolon, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    whileStatement = std::make_unique<WhileStatement>();
    whileStatement->tkWhile = fromTokenWhile.GetToken(whileStatement.get());
    whileStatement->initialExpression = initialExpression.GetInitialExpression(whileStatement.get());
    whileStatement->tkDo = fromTokenDo.GetToken(whileStatement.get());
    
    if (block.GetChecked()) {
        whileStatement->block = block.GetBlock(whileStatement.get());
    }
    
    whileStatement->tkEndDo = fromTokenEndDo.GetToken(whileStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        whileStatement->tkSemicolon = fromTokenSemicolon.GetToken(whileStatement.get());
    }
    
    if (!whileStatement->tkSemicolon.IsEmpty()) {
        whileStatement->SetEntity(whileStatement->tkWhile, whileStatement->tkSemicolon);
    }
    else {
        whileStatement->SetEntity(whileStatement->tkWhile, whileStatement->tkEndDo);
    }
    
    return true;
}

std::unique_ptr<WhileStatement> PrWhileStatement::GetWhileStatement(void* prnt) {
    whileStatement->prnt = prnt;
    return std::move(whileStatement);
}

void PrWhileStatement::Reset() {
    PHelper::Reset();
    whileStatement.reset();
}

bool PrTryStatement::CheckAstNode(PStream& stream) {
    PrBlock blockTry;
    PhOnceOrNot onceOrNotTry(&blockTry);
    
    PrBlock blockExcept;
    PhOnceOrNot onceOrNotExcept(&blockExcept);
    
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PhFromToken fromTokenTry(TokenType::try_);
    PhFromToken fromTokenExcept(TokenType::except);
    PhFromToken fromTokenEndTry(TokenType::endTry);
    PhAddition addition(&fromTokenTry, &onceOrNotTry, &fromTokenExcept, &onceOrNotExcept, &fromTokenEndTry, &onceOrNot,
        &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    tryStatement = std::make_unique<TryStatement>();
    tryStatement->tkTry = fromTokenTry.GetToken(tryStatement.get());
    
    if (blockTry.GetChecked()) {
        tryStatement->blockTry = blockTry.GetBlock(tryStatement.get());
    }
    
    tryStatement->tkExcept = fromTokenExcept.GetToken(tryStatement.get());
    
    if (blockExcept.GetChecked()) {
        tryStatement->blockExcept = blockExcept.GetBlock(tryStatement.get());
    }
    
    tryStatement->tkEndTry = fromTokenEndTry.GetToken(tryStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        tryStatement->tkSemicolon = fromTokenSemicolon.GetToken(tryStatement.get());
    }
    
    if (!tryStatement->tkSemicolon.IsEmpty()) {
        tryStatement->SetEntity(tryStatement->tkTry, tryStatement->tkSemicolon);
    }
    else {
        tryStatement->SetEntity(tryStatement->tkTry, tryStatement->tkEndTry);
    }
    
    return true;
}

std::unique_ptr<TryStatement> PrTryStatement::GetTryStatement(void* prnt) {
    tryStatement->prnt = prnt;
    return std::move(tryStatement);
}

void PrTryStatement::Reset() {
    PHelper::Reset();
    tryStatement.reset();
}

bool PrRaiseStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PhFromToken fromTokenRaise(TokenType::raise);
    PrInitialExpression initialExpression;
    PhAddition addition(&fromTokenRaise, &initialExpression, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    raiseStatement = std::make_unique<RaiseStatement>();
    raiseStatement->tkRaise = fromTokenRaise.GetToken(raiseStatement.get());
    raiseStatement->initialExpression = initialExpression.GetInitialExpression(raiseStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        raiseStatement->tkSemicolon = fromTokenSemicolon.GetToken(raiseStatement.get());
    }
    
    if (!raiseStatement->tkSemicolon.IsEmpty()) {
        raiseStatement->SetEntity(raiseStatement->tkRaise, raiseStatement->tkSemicolon);
    }
    else {
        raiseStatement->SetEntity(raiseStatement->tkRaise, *raiseStatement->initialExpression);
    }
    
    return true;
}

std::unique_ptr<RaiseStatement> PrRaiseStatement::GetRaiseStatement(void* prnt) {
    raiseStatement->prnt = prnt;
    return std::move(raiseStatement);
}

void PrRaiseStatement::Reset() {
    PHelper::Reset();
    raiseStatement.reset();
}

bool PrLabelStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenTilde(TokenType::tilde);
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PhFromToken fromTokenColon(TokenType::colon);
    PhAddition addition(&fromTokenTilde, &fromTokenIdentifier, &fromTokenColon, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    labelStatement = std::make_unique<LabelStatement>();
    labelStatement->tkTilde = fromTokenTilde.GetToken(labelStatement.get());
    labelStatement->tkIdentifier = fromTokenIdentifier.GetToken(labelStatement.get());
    labelStatement->tkColon = fromTokenColon.GetToken(labelStatement.get());
    
    labelStatement->SetEntity(labelStatement->tkTilde, labelStatement->tkColon);
    return true;
}

std::unique_ptr<LabelStatement> PrLabelStatement::GetLabelStatement(void* prnt) {
    labelStatement->prnt = prnt;
    return std::move(labelStatement);
}

void PrLabelStatement::Reset() {
    PHelper::Reset();
    labelStatement.reset();
}

bool PrGotoStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PhFromToken fromTokenGoto(TokenType::goto_);
    PhFromToken fromTokenTilde(TokenType::tilde);
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PhAddition addition(&fromTokenGoto, &fromTokenTilde, &fromTokenIdentifier, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    gotoStatement = std::make_unique<GotoStatement>();
    gotoStatement->tkGoto = fromTokenGoto.GetToken(gotoStatement.get());
    gotoStatement->tkTilde = fromTokenTilde.GetToken(gotoStatement.get());
    gotoStatement->tkIdentifier = fromTokenIdentifier.GetToken(gotoStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        gotoStatement->tkSemicolon = fromTokenSemicolon.GetToken(gotoStatement.get());
    }
    
    if (!gotoStatement->tkSemicolon.IsEmpty()) {
        gotoStatement->SetEntity(gotoStatement->tkGoto, gotoStatement->tkSemicolon);
    }
    else {
        gotoStatement->SetEntity(gotoStatement->tkGoto, gotoStatement->tkIdentifier);
    }
    
    return true;
}

std::unique_ptr<GotoStatement> PrGotoStatement::GetGotoStatement(void* prnt) {
    gotoStatement->prnt = prnt;
    return std::move(gotoStatement);
}

void PrGotoStatement::Reset() {
    PHelper::Reset();
    gotoStatement.reset();
}

bool PrContinueStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PhFromToken fromTokenContinue(TokenType::continue_);
    PhAddition addition(&fromTokenContinue, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    continueStatement = std::make_unique<ContinueStatement>();
    continueStatement->tkContinue = fromTokenContinue.GetToken(continueStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        continueStatement->tkSemicolon = fromTokenSemicolon.GetToken(continueStatement.get());
    }
    
    if (!continueStatement->tkSemicolon.IsEmpty()) {
        continueStatement->SetEntity(continueStatement->tkContinue, continueStatement->tkSemicolon);
    }
    else {
        continueStatement->SetEntity(continueStatement->tkContinue);
    }
    
    return true;
}

std::unique_ptr<ContinueStatement> PrContinueStatement::GetContinueStatement(void* prnt) {
    continueStatement->prnt = prnt;
    return std::move(continueStatement);
}

void PrContinueStatement::Reset() {
    PHelper::Reset();
    continueStatement.reset();
}

bool PrBreakStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    PhOnceOrNot onceOrNot(&fromTokenSemicolon);
    
    PhFromToken fromTokenBreak(TokenType::break_);
    PhAddition addition(&fromTokenBreak, &onceOrNot, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    if (!fromTokenSemicolon.GetChecked()) {
        stream.readyForBlockElement = false;
    }
    
    breakStatement = std::make_unique<BreakStatement>();
    breakStatement->tkBreak = fromTokenBreak.GetToken(breakStatement.get());
    
    if (fromTokenSemicolon.GetChecked()) {
        breakStatement->tkSemicolon = fromTokenSemicolon.GetToken(breakStatement.get());
    }
    
    if (!breakStatement->tkSemicolon.IsEmpty()) {
        breakStatement->SetEntity(breakStatement->tkBreak, breakStatement->tkSemicolon);
    }
    else {
        breakStatement->SetEntity(breakStatement->tkBreak);
    }
    
    return true;
}

std::unique_ptr<BreakStatement> PrBreakStatement::GetBreakStatement(void* prnt) {
    breakStatement->prnt = prnt;
    return std::move(breakStatement);
}

void PrBreakStatement::Reset() {
    PHelper::Reset();
    breakStatement.reset();
}

bool PrSemicolonStatement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenSemicolon(TokenType::semicolon);
    
    if (!fromTokenSemicolon.Check(stream)) {
        return false;
    }
    
    semicolonStatement = std::make_unique<SemicolonStatement>();
    semicolonStatement->tkSemicolon = fromTokenSemicolon.GetToken(semicolonStatement.get());
    
    semicolonStatement->SetEntity(semicolonStatement->tkSemicolon);
    return true;
}

std::unique_ptr<SemicolonStatement> PrSemicolonStatement::GetSemicolonStatement(void* prnt) {
    semicolonStatement->prnt = prnt;
    return std::move(semicolonStatement);
}

void PrSemicolonStatement::Reset() {
    PHelper::Reset();
    semicolonStatement.reset();
}

bool PrInitialExpression::CheckAstNode(PStream& stream) {
    PrExpression prExpression;
    
    if (!prExpression.Check(stream)) {
        return false;
    }
    
    initialExpression = std::make_unique<InitialExpression>();
    initialExpression->expression = prExpression.GetExpression(initialExpression.get());
    
    initialExpression->SetEntity(*initialExpression->expression);
    return true;
}

std::unique_ptr<InitialExpression> PrInitialExpression::GetInitialExpression(void* prnt) {
    initialExpression->prnt = prnt;
    return std::move(initialExpression);
}

void PrInitialExpression::Reset() {
    PHelper::Reset();
    initialExpression.reset();
}

bool PrExpression::CheckAstNode(PStream& stream) {
    PrAndExpression andExpression;
    PhSeveral<PrExpressionElement> several;
    PhAddition addition(&andExpression, &several, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    expression = std::make_unique<Expression>();
    expression->andExpression = andExpression.GetAndExpression(expression.get());
    
    std::vector<std::unique_ptr<PrExpressionElement>>& helpers = several.GetHelpers();
    expression->expressionElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        expression->expressionElements.push_back(*helpers[i]->GetExpressionElement(expression.get(), i));
        expression->expressionElements.back().UpdateChildren();
    }
    
    if (!expression->expressionElements.empty()) {
        expression->SetEntity(*expression->andExpression, expression->expressionElements.back());
    }
    else {
        expression->SetEntity(*expression->andExpression);
    }
    
    return true;
}

std::unique_ptr<Expression> PrExpression::GetExpression(void* prnt) {
    expression->prnt = prnt;
    return std::move(expression);
}

void PrExpression::Reset() {
    PHelper::Reset();
    expression.reset();
}

bool PrExpressionElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenOr(TokenType::or_);
    PrAndExpression andExpression;
    PhAddition addition(&fromTokenOr, &andExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    expressionElement = std::make_unique<ExpressionElement>();
    expressionElement->tkOr = fromTokenOr.GetToken(expressionElement.get());
    expressionElement->andExpression = andExpression.GetAndExpression(expressionElement.get());
    
    expressionElement->SetEntity(expressionElement->tkOr, *expressionElement->andExpression);
    return true;
}

std::unique_ptr<ExpressionElement> PrExpressionElement::GetExpressionElement(void* prnt, int index) {
    expressionElement->prnt = prnt;
    expressionElement->index = index;
    return std::move(expressionElement);
}

void PrExpressionElement::Reset() {
    PHelper::Reset();
    expressionElement.reset();
}

bool PrPrimeExpression::CheckAstNode(PStream& stream) {
    PrValue value;
    PrExpressionInParenthesis expressionInParenthesis;
    PrMemberMethod memberMethod;
    PrNewElement newElement;
    PrTernaryOperationElement ternaryOperationElement;
    PrAwaitElement awaitElement;
    PhAnyOf anyOf(&value, &expressionInParenthesis, &memberMethod, &newElement, &ternaryOperationElement, &awaitElement,
        &endHelper);
    
    if (!anyOf.Check(stream)) {
        return false;
    }
    
    primeExpression = std::make_unique<PrimeExpression>();
    
    if (value.GetChecked()) {
        primeExpression->value = value.GetValue(primeExpression.get());
    }
    else if (expressionInParenthesis.GetChecked()) {
        primeExpression->expressionInParenthesis = expressionInParenthesis.GetExpressionInParenthesis(
            primeExpression.get());
    }
    else if (memberMethod.GetChecked()) {
        primeExpression->memberMethod = memberMethod.GetMemberMethod(primeExpression.get());
    }
    else if (newElement.GetChecked()) {
        primeExpression->newElement = newElement.GetNewElement(primeExpression.get());
    }
    else if (ternaryOperationElement.GetChecked()) {
        primeExpression->ternaryOperationElement = ternaryOperationElement.GetTernaryOperationElement(
            primeExpression.get());
    }
    else if (awaitElement.GetChecked()) {
        primeExpression->awaitElement = awaitElement.GetAwaitElement(primeExpression.get());
    }
    
    if (primeExpression->value.get() != nullptr) {
        primeExpression->SetEntity(*primeExpression->value);
    }
    else if (primeExpression->expressionInParenthesis.get() != nullptr) {
        primeExpression->SetEntity(*primeExpression->expressionInParenthesis);
    }
    else if (primeExpression->memberMethod.get() != nullptr) {
        primeExpression->SetEntity(*primeExpression->memberMethod);
    }
    else if (primeExpression->newElement.get() != nullptr) {
        primeExpression->SetEntity(*primeExpression->newElement);
    }
    else if (primeExpression->ternaryOperationElement.get() != nullptr) {
        primeExpression->SetEntity(*primeExpression->ternaryOperationElement);
    }
    else if (primeExpression->awaitElement.get() != nullptr) {
        primeExpression->SetEntity(*primeExpression->awaitElement);
    }
    
    return true;
}

std::unique_ptr<PrimeExpression> PrPrimeExpression::GetPrimeExpression(void* prnt) {
    primeExpression->prnt = prnt;
    return std::move(primeExpression);
}

void PrPrimeExpression::Reset() {
    PHelper::Reset();
    primeExpression.reset();
}

bool PrExpressionInParenthesis::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenLeftParenthesis(TokenType::leftParenthesis);
    PrExpression expression;
    PhFromToken fromTokenRightParenthesis(TokenType::rightParenthesis);
    PhAddition addition(&fromTokenLeftParenthesis, &expression, &fromTokenRightParenthesis, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    expressionInParenthesis = std::make_unique<ExpressionInParenthesis>();
    expressionInParenthesis->tkLeftParenthesis = fromTokenLeftParenthesis.GetToken(
        expressionInParenthesis.get());
    expressionInParenthesis->expression = expression.GetExpression(expressionInParenthesis.get());
    expressionInParenthesis->tkRightParenthesis = fromTokenRightParenthesis.GetToken(
        expressionInParenthesis.get());
    
    expressionInParenthesis->SetEntity(expressionInParenthesis->tkLeftParenthesis,
        expressionInParenthesis->tkRightParenthesis);
    return true;
}

std::unique_ptr<ExpressionInParenthesis> PrExpressionInParenthesis::GetExpressionInParenthesis(void* prnt) {
    expressionInParenthesis->prnt = prnt;
    return std::move(expressionInParenthesis);
}

void PrExpressionInParenthesis::Reset() {
    PHelper::Reset();
    expressionInParenthesis.reset();
}

bool PrMemberMethod::CheckAstNode(PStream& stream) {
    PhSeveral<PrMemberMethodElement> several;
    PrMemberMethodElementElement memberMethodElementElement;
    PhAddition addition(&several, &memberMethodElementElement, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    memberMethod = std::make_unique<MemberMethod>();
    
    std::vector<std::unique_ptr<PrMemberMethodElement>>& helpers = several.GetHelpers();
    memberMethod->memberMethodElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        memberMethod->memberMethodElements.push_back(*helpers[i]->GetMemberMethodElement(memberMethod.get(),
            i));
        memberMethod->memberMethodElements.back().UpdateChildren();
    }
    
    memberMethod->memberMethodElementElement = memberMethodElementElement.GetMemberMethodElementElement(
        memberMethod.get());
    
    if (!memberMethod->memberMethodElements.empty()) {
        memberMethod->SetEntity(memberMethod->memberMethodElements.front(),
            *memberMethod->memberMethodElementElement);
    }
    else {
        memberMethod->SetEntity(*memberMethod->memberMethodElementElement);
    }
    
    return true;
}

std::unique_ptr<MemberMethod> PrMemberMethod::GetMemberMethod(void* prnt) {
    memberMethod->prnt = prnt;
    return std::move(memberMethod);
}

void PrMemberMethod::Reset() {
    PHelper::Reset();
    memberMethod.reset();
}

bool PrNewElement::CheckAstNode(PStream& stream) {
    PrArgumentsBlock argumentsBlock;
    PhOnceOrNot onceOrNot(&argumentsBlock);
    
    PhFromToken fromTokenIdentifier(TokenType::identifier);
    PhAddition additionIdentifier(&fromTokenIdentifier, &onceOrNot, &endHelper);
    
    PrNewArgumentsBlock newArgumentsBlock;
    PhAnyOf anyOf(&additionIdentifier, &newArgumentsBlock, &endHelper);
    
    PhFromToken fromTokenNew(TokenType::new_);
    PhAddition addition(&fromTokenNew, &anyOf, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    newElement = std::make_unique<NewElement>();
    newElement->tkNew = fromTokenNew.GetToken(newElement.get());
    
    if (fromTokenIdentifier.GetChecked()) {
        newElement->tkIdentifier = fromTokenIdentifier.GetToken(newElement.get());
        
        if (argumentsBlock.GetChecked()) {
            newElement->argumentsBlock = argumentsBlock.GetArgumentsBlock(newElement.get());
        }
    }
    else if (newArgumentsBlock.GetChecked()) {
        newElement->newArgumentsBlock = newArgumentsBlock.GetNewArgumentsBlock(newElement.get());
    }
    
    if (!newElement->tkIdentifier.IsEmpty()) {
        if (newElement->argumentsBlock.get() != nullptr) {
            newElement->SetEntity(newElement->tkNew, *newElement->argumentsBlock);
        }
        else {
            newElement->SetEntity(newElement->tkNew, newElement->tkIdentifier);
        }
    }
    else {
        newElement->SetEntity(newElement->tkNew, *newElement->newArgumentsBlock);
    }
    
    return true;
}

std::unique_ptr<NewElement> PrNewElement::GetNewElement(void* prnt) {
    newElement->prnt = prnt;
    return std::move(newElement);
}

void PrNewElement::Reset() {
    PHelper::Reset();
    newElement.reset();
}

bool PrNewArgumentsBlock::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenLeftParenthesis(TokenType::leftParenthesis);
    PrInitialExpression initialExpression;
    PhSeveral<PrArgumentsBlockElement> several;
    PhFromToken fromTokenRightParenthesis(TokenType::rightParenthesis);
    PhAddition addition(&fromTokenLeftParenthesis, &initialExpression, &several, &fromTokenRightParenthesis,
        &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    newArgumentsBlock = std::make_unique<NewArgumentsBlock>();
    newArgumentsBlock->tkLeftParenthesis = fromTokenLeftParenthesis.GetToken(newArgumentsBlock.get());
    newArgumentsBlock->initialExpression = initialExpression.GetInitialExpression(newArgumentsBlock.get());
    
    std::vector<std::unique_ptr<PrArgumentsBlockElement>>& helpers = several.GetHelpers();
    newArgumentsBlock->argumentsBlockElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        newArgumentsBlock->argumentsBlockElements.push_back(*helpers[i]->GetArgumentsBlockElement(
            newArgumentsBlock.get(), i));
        newArgumentsBlock->argumentsBlockElements.back().UpdateChildren();
    }
    
    newArgumentsBlock->tkRightParenthesis = fromTokenRightParenthesis.GetToken(newArgumentsBlock.get());
    
    newArgumentsBlock->SetEntity(newArgumentsBlock->tkLeftParenthesis, newArgumentsBlock->tkRightParenthesis);
    return true;
}

std::unique_ptr<NewArgumentsBlock> PrNewArgumentsBlock::GetNewArgumentsBlock(void* prnt) {
    newArgumentsBlock->prnt = prnt;
    return std::move(newArgumentsBlock);
}

void PrNewArgumentsBlock::Reset() {
    PHelper::Reset();
    newArgumentsBlock.reset();
}

bool PrTernaryOperationElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenQuestionMark(TokenType::questionMark);
    PhFromToken fromTokenLeftParenthesis(TokenType::leftParenthesis);
    PrInitialExpression initialExpression;
    PhFromToken fromTokenCommaA(TokenType::comma);
    PrInitialExpression initialExpressionTrue;
    PhFromToken fromTokenCommaB(TokenType::comma);
    PrInitialExpression initialExpressionFalse;
    PhFromToken fromTokenRightParenthesis(TokenType::rightParenthesis);
    PhAddition addition(&fromTokenQuestionMark, &fromTokenLeftParenthesis, &initialExpression, &fromTokenCommaA,
        &initialExpressionTrue, &fromTokenCommaB, &initialExpressionFalse, &fromTokenRightParenthesis, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    ternaryOperationElement = std::make_unique<TernaryOperationElement>();
    ternaryOperationElement->tkQuestionMark = fromTokenQuestionMark.GetToken(ternaryOperationElement.get());
    ternaryOperationElement->tkLeftParenthesis = fromTokenLeftParenthesis.GetToken(
        ternaryOperationElement.get());
    ternaryOperationElement->initialExpression = initialExpression.GetInitialExpression(
        ternaryOperationElement.get());
    ternaryOperationElement->tkCommaA = fromTokenCommaA.GetToken(ternaryOperationElement.get());
    ternaryOperationElement->initialExpressionTrue = initialExpressionTrue.GetInitialExpression(
        ternaryOperationElement.get());
    ternaryOperationElement->tkCommaB = fromTokenCommaB.GetToken(ternaryOperationElement.get());
    ternaryOperationElement->initialExpressionFalse = initialExpressionFalse.GetInitialExpression(
        ternaryOperationElement.get());
    ternaryOperationElement->tkRightParenthesis = fromTokenRightParenthesis.GetToken(
        ternaryOperationElement.get());
    
    ternaryOperationElement->SetEntity(ternaryOperationElement->tkQuestionMark,
        ternaryOperationElement->tkRightParenthesis);
    return true;
}

std::unique_ptr<TernaryOperationElement> PrTernaryOperationElement::GetTernaryOperationElement(void* prnt) {
    ternaryOperationElement->prnt = prnt;
    return std::move(ternaryOperationElement);
}

void PrTernaryOperationElement::Reset() {
    PHelper::Reset();
    ternaryOperationElement.reset();
}

bool PrAwaitElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenAwait(TokenType::await);
    PrInitialExpression initialExpression;
    PhAddition addition(&fromTokenAwait, &initialExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    awaitElement = std::make_unique<AwaitElement>();
    awaitElement->tkAwait = fromTokenAwait.GetToken(awaitElement.get());
    awaitElement->initialExpression = initialExpression.GetInitialExpression(awaitElement.get());
    
    awaitElement->SetEntity(awaitElement->tkAwait, *awaitElement->initialExpression);
    return true;
}

std::unique_ptr<AwaitElement> PrAwaitElement::GetAwaitElement(void* prnt) {
    awaitElement->prnt = prnt;
    return std::move(awaitElement);
}

void PrAwaitElement::Reset() {
    PHelper::Reset();
    awaitElement.reset();
}

bool PrAndExpression::CheckAstNode(PStream& stream) {
    PrNotExpression notExpression;
    PhSeveral<PrAndExpressionElement> several;
    PhAddition addition(&notExpression, &several, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    andExpression = std::make_unique<AndExpression>();
    andExpression->notExpression = notExpression.GetNotExpression(andExpression.get());
    
    std::vector<std::unique_ptr<PrAndExpressionElement>>& helpers = several.GetHelpers();
    andExpression->andExpressionElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        andExpression->andExpressionElements.push_back(*helpers[i]->GetAndExpressionElement(andExpression.get(),
            i));
        andExpression->andExpressionElements.back().UpdateChildren();
    }
    
    if (!andExpression->andExpressionElements.empty() != 0) {
        andExpression->SetEntity(*andExpression->notExpression, andExpression->andExpressionElements.back());
    }
    else {
        andExpression->SetEntity(*andExpression->notExpression);
    }
    
    return true;
}

std::unique_ptr<AndExpression> PrAndExpression::GetAndExpression(void* prnt) {
    andExpression->prnt = prnt;
    return std::move(andExpression);
}

void PrAndExpression::Reset() {
    PHelper::Reset();
    andExpression.reset();
}

bool PrAndExpressionElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenAnd(TokenType::and_);
    PrNotExpression notExpression;
    PhAddition addition(&fromTokenAnd, &notExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    andExpressionElement = std::make_unique<AndExpressionElement>();
    andExpressionElement->tkAnd = fromTokenAnd.GetToken(andExpressionElement.get());
    andExpressionElement->notExpression = notExpression.GetNotExpression(andExpressionElement.get());
    
    andExpressionElement->SetEntity(andExpressionElement->tkAnd, *andExpressionElement->notExpression);
    return true;
}

std::unique_ptr<AndExpressionElement> PrAndExpressionElement::GetAndExpressionElement(void* prnt, int index) {
    andExpressionElement->prnt = prnt;
    andExpressionElement->index = index;
    return std::move(andExpressionElement);
}

void PrAndExpressionElement::Reset() {
    PHelper::Reset();
    andExpressionElement.reset();
}

bool PrNotExpression::CheckAstNode(PStream& stream) {
    PhSeveral<PrNotExpressionElement> several;
    PrRelationalExpression relationalExpression;
    PhAddition addition(&several, &relationalExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    notExpression = std::make_unique<NotExpression>();
    
    std::vector<std::unique_ptr<PrNotExpressionElement>>& helpers = several.GetHelpers();
    notExpression->notExpressionElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        notExpression->notExpressionElements.push_back(*helpers[i]->GetNotExpressionElement(notExpression.get(),
            i));
        notExpression->notExpressionElements.back().UpdateChildren();
    }
    
    notExpression->relationalExpression = relationalExpression.GetRelationalExpression(notExpression.get());
    
    if (!notExpression->notExpressionElements.empty()) {
        notExpression->SetEntity(notExpression->notExpressionElements.front(),
            *notExpression->relationalExpression);
    }
    else {
        notExpression->SetEntity(*notExpression->relationalExpression);
    }
    
    return true;
}

std::unique_ptr<NotExpression> PrNotExpression::GetNotExpression(void* prnt) {
    notExpression->prnt = prnt;
    return std::move(notExpression);
}

void PrNotExpression::Reset() {
    PHelper::Reset();
    notExpression.reset();
}

bool PrNotExpressionElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenNot(TokenType::not_);
    
    if (!fromTokenNot.Check(stream)) {
        return false;
    }
    
    notExpressionElement = std::make_unique<NotExpressionElement>();
    notExpressionElement->tkNot = fromTokenNot.GetToken(notExpressionElement.get());
    
    notExpressionElement->SetEntity(notExpressionElement->tkNot);
    return true;
}

std::unique_ptr<NotExpressionElement> PrNotExpressionElement::GetNotExpressionElement(void* prnt, int index) {
    notExpressionElement->prnt = prnt;
    notExpressionElement->index = index;
    return std::move(notExpressionElement);
}

void PrNotExpressionElement::Reset() {
    PHelper::Reset();
    notExpressionElement.reset();
}

bool PrRelationalExpression::CheckAstNode(PStream& stream) {
    PrAddingExpression addingExpression;
    PhSeveral<PrRelationalExpressionElement> several;
    PhAddition addition(&addingExpression, &several, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    relationalExpression = std::make_unique<RelationalExpression>();
    relationalExpression->addingExpression = addingExpression.GetAddingExpression(relationalExpression.get());
    
    std::vector<std::unique_ptr<PrRelationalExpressionElement>>& helpers = several.GetHelpers();
    relationalExpression->relationalExpressionElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        relationalExpression->relationalExpressionElements.push_back(
            *helpers[i]->GetRelationalExpressionElement(relationalExpression.get(), i));
        relationalExpression->relationalExpressionElements.back().UpdateChildren();
    }
    
    if (!relationalExpression->relationalExpressionElements.empty()) {
        relationalExpression->SetEntity(*relationalExpression->addingExpression,
            relationalExpression->relationalExpressionElements.back());
    }
    else {
        relationalExpression->SetEntity(*relationalExpression->addingExpression);
    }
    
    return true;
}

std::unique_ptr<RelationalExpression> PrRelationalExpression::GetRelationalExpression(void* prnt) {
    relationalExpression->prnt = prnt;
    return std::move(relationalExpression);
}

void PrRelationalExpression::Reset() {
    PHelper::Reset();
    relationalExpression.reset();
}

bool PrRelationalExpressionElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenEquals(TokenType::equals);
    PhFromToken fromTokenNotEquals(TokenType::notEquals);
    PhFromToken fromTokenLess(TokenType::less);
    PhFromToken fromTokenLessOrEquals(TokenType::lessOrEquals);
    PhFromToken fromTokenGreater(TokenType::greater);
    PhFromToken fromTokenGreaterOrEquals(TokenType::greaterOrEquals);
    PhAnyOf anyOf(&fromTokenEquals, &fromTokenNotEquals, &fromTokenLess, &fromTokenLessOrEquals, &fromTokenGreater,
        &fromTokenGreaterOrEquals, &endHelper);
    
    PrAddingExpression addingExpression;
    PhAddition addition(&anyOf, &addingExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    relationalExpressionElement = std::make_unique<RelationalExpressionElement>();
    
    if (fromTokenEquals.GetChecked()) {
        relationalExpressionElement->isEquals = true;
        relationalExpressionElement->tkEquals = fromTokenEquals.GetToken(relationalExpressionElement.get());
    }
    else if (fromTokenNotEquals.GetChecked()) {
        relationalExpressionElement->isNotEquals = true;
        relationalExpressionElement->tkNotEquals = fromTokenNotEquals.GetToken(
            relationalExpressionElement.get());
    }
    else if (fromTokenLess.GetChecked()) {
        relationalExpressionElement->isLess = true;
        relationalExpressionElement->tkLess = fromTokenLess.GetToken(relationalExpressionElement.get());
    }
    else if (fromTokenLessOrEquals.GetChecked()) {
        relationalExpressionElement->isLessOrEquals = true;
        relationalExpressionElement->tkLessOrEquals = fromTokenLessOrEquals.GetToken(
            relationalExpressionElement.get());
    }
    else if (fromTokenGreater.GetChecked()) {
        relationalExpressionElement->isGreater = true;
        relationalExpressionElement->tkGreater = fromTokenGreater.GetToken(relationalExpressionElement.get());
    }
    else if (fromTokenGreaterOrEquals.GetChecked()) {
        relationalExpressionElement->isGreaterOrEquals = true;
        relationalExpressionElement->tkGreaterOrEquals = fromTokenGreaterOrEquals.GetToken(
            relationalExpressionElement.get());
    }
    
    relationalExpressionElement->addingExpression = addingExpression.GetAddingExpression(
        relationalExpressionElement.get());
    
    if (relationalExpressionElement->isEquals) {
        relationalExpressionElement->SetEntity(relationalExpressionElement->tkEquals,
            *relationalExpressionElement->addingExpression);
    }
    else if (relationalExpressionElement->isNotEquals) {
        relationalExpressionElement->SetEntity(relationalExpressionElement->tkNotEquals,
            *relationalExpressionElement->addingExpression);
    }
    else if (relationalExpressionElement->isLess) {
        relationalExpressionElement->SetEntity(relationalExpressionElement->tkLess,
            *relationalExpressionElement->addingExpression);
    }
    else if (relationalExpressionElement->isLessOrEquals) {
        relationalExpressionElement->SetEntity(relationalExpressionElement->tkLessOrEquals,
            *relationalExpressionElement->addingExpression);
    }
    else if (relationalExpressionElement->isGreater) {
        relationalExpressionElement->SetEntity(relationalExpressionElement->tkGreater,
            *relationalExpressionElement->addingExpression);
    }
    else if (relationalExpressionElement->isGreaterOrEquals) {
        relationalExpressionElement->SetEntity(relationalExpressionElement->tkGreaterOrEquals,
            *relationalExpressionElement->addingExpression);
    }
    
    return true;
}

std::unique_ptr<RelationalExpressionElement> PrRelationalExpressionElement::GetRelationalExpressionElement(
    void* prnt, int index) {
    relationalExpressionElement->prnt = prnt;
    relationalExpressionElement->index = index;
    return std::move(relationalExpressionElement);
}

void PrRelationalExpressionElement::Reset() {
    PHelper::Reset();
    relationalExpressionElement.reset();
}

bool PrAddingExpression::CheckAstNode(PStream& stream) {
    PrMultiplyingExpression multiplyingExpression;
    PhSeveral<PrAddingExpressionElement> several;
    PhAddition addition(&multiplyingExpression, &several, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    addingExpression = std::make_unique<AddingExpression>();
    addingExpression->multiplyingExpression = multiplyingExpression.GetMultiplyingExpression(
        addingExpression.get());
    
    std::vector<std::unique_ptr<PrAddingExpressionElement>>& helpers = several.GetHelpers();
    addingExpression->addingExpressionElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        addingExpression->addingExpressionElements.push_back(*helpers[i]->GetAddingExpressionElement(
            addingExpression.get(), i));
        addingExpression->addingExpressionElements.back().UpdateChildren();
    }
    
    if (!addingExpression->addingExpressionElements.empty()) {
        addingExpression->SetEntity(*addingExpression->multiplyingExpression,
            addingExpression->addingExpressionElements.back());
    }
    else {
        addingExpression->SetEntity(*addingExpression->multiplyingExpression);
    }
    
    return true;
}

std::unique_ptr<AddingExpression> PrAddingExpression::GetAddingExpression(void* prnt) {
    addingExpression->prnt = prnt;
    return std::move(addingExpression);
}

void PrAddingExpression::Reset() {
    PHelper::Reset();
    addingExpression.reset();
}

bool PrAddingExpressionElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenMinus(TokenType::minus);
    PhFromToken fromTokenPlus(TokenType::plus);
    PhAnyOf anyOf(&fromTokenMinus, &fromTokenPlus, &endHelper);
    
    PrMultiplyingExpression multiplyingExpression;
    PhAddition addition(&anyOf, &multiplyingExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    addingExpressionElement = std::make_unique<AddingExpressionElement>();
    
    if (fromTokenMinus.GetChecked()) {
        addingExpressionElement->isMinus = true;
        addingExpressionElement->tkMinus = fromTokenMinus.GetToken(addingExpressionElement.get());
    }
    else if (fromTokenPlus.GetChecked()) {
        addingExpressionElement->isPlus = true;
        addingExpressionElement->tkPlus = fromTokenPlus.GetToken(addingExpressionElement.get());
    }
    
    addingExpressionElement->multiplyingExpression = multiplyingExpression.GetMultiplyingExpression(
        addingExpressionElement.get());
    
    if (addingExpressionElement->isMinus) {
        addingExpressionElement->SetEntity(addingExpressionElement->tkMinus,
            *addingExpressionElement->multiplyingExpression);
    }
    else if (addingExpressionElement->isPlus) {
        addingExpressionElement->SetEntity(addingExpressionElement->tkPlus,
            *addingExpressionElement->multiplyingExpression);
    }
    
    return true;
}

std::unique_ptr<AddingExpressionElement> PrAddingExpressionElement::GetAddingExpressionElement(
    void* prnt, int index) {
    addingExpressionElement->prnt = prnt;
    addingExpressionElement->index = index;
    return std::move(addingExpressionElement);
}

void PrAddingExpressionElement::Reset() {
    PHelper::Reset();
    addingExpressionElement.reset();
}

bool PrMultiplyingExpression::CheckAstNode(PStream& stream) {
    PrSignExpression signExpression;
    PhSeveral<PrMultiplyingExpressionElement> several;
    PhAddition addition(&signExpression, &several, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    multiplyingExpression = std::make_unique<MultiplyingExpression>();
    multiplyingExpression->signExpression = signExpression.GetSignExpression(multiplyingExpression.get());
    
    std::vector<std::unique_ptr<PrMultiplyingExpressionElement>>& helpers = several.GetHelpers();
    multiplyingExpression->multiplyingExpressionElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        multiplyingExpression->multiplyingExpressionElements.push_back(
            *helpers[i]->GetMultiplyingExpressionElement(multiplyingExpression.get(), i));
        multiplyingExpression->multiplyingExpressionElements.back().UpdateChildren();
    }
    
    if (!multiplyingExpression->multiplyingExpressionElements.empty()) {
        multiplyingExpression->SetEntity(*multiplyingExpression->signExpression,
            multiplyingExpression->multiplyingExpressionElements.back());
    }
    else {
        multiplyingExpression->SetEntity(*multiplyingExpression->signExpression);
    }
    
    return true;
}

std::unique_ptr<MultiplyingExpression> PrMultiplyingExpression::GetMultiplyingExpression(void* prnt) {
    multiplyingExpression->prnt = prnt;
    return std::move(multiplyingExpression);
}

void PrMultiplyingExpression::Reset() {
    PHelper::Reset();
    multiplyingExpression.reset();
}

bool PrMultiplyingExpressionElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenAsterisk(TokenType::asterisk);
    PhFromToken fromTokenSolidus(TokenType::solidus);
    PhFromToken fromTokenPercent(TokenType::percent);
    PhAnyOf anyOf(&fromTokenAsterisk, &fromTokenSolidus, &fromTokenPercent, &endHelper);
    
    PrSignExpression signExpression;
    PhAddition addition(&anyOf, &signExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    multiplyingExpressionElement = std::make_unique<MultiplyingExpressionElement>();
    
    if (fromTokenAsterisk.GetChecked()) {
        multiplyingExpressionElement->isAsterisk = true;
        multiplyingExpressionElement->tkAsterisk = fromTokenAsterisk.GetToken(
            multiplyingExpressionElement.get());
    }
    else if (fromTokenSolidus.GetChecked()) {
        multiplyingExpressionElement->isSolidus = true;
        multiplyingExpressionElement->tkSolidus = fromTokenSolidus.GetToken(multiplyingExpressionElement.get());
    }
    else if (fromTokenPercent.GetChecked()) {
        multiplyingExpressionElement->isPercent = true;
        multiplyingExpressionElement->tkPercent = fromTokenPercent.GetToken(multiplyingExpressionElement.get());
    }
    
    multiplyingExpressionElement->signExpression = signExpression.GetSignExpression(
        multiplyingExpressionElement.get());
    
    if (multiplyingExpressionElement->isAsterisk) {
        multiplyingExpressionElement->SetEntity(multiplyingExpressionElement->tkAsterisk,
            *multiplyingExpressionElement->signExpression);
    }
    else if (multiplyingExpressionElement->isSolidus) {
        multiplyingExpressionElement->SetEntity(multiplyingExpressionElement->tkSolidus,
            *multiplyingExpressionElement->signExpression);
    }
    else if (multiplyingExpressionElement->isPercent) {
        multiplyingExpressionElement->SetEntity(multiplyingExpressionElement->tkPercent,
            *multiplyingExpressionElement->signExpression);
    }
    
    return true;
}

std::unique_ptr<MultiplyingExpressionElement> PrMultiplyingExpressionElement::GetMultiplyingExpressionElement(
    void* prnt, int index) {
    multiplyingExpressionElement->prnt = prnt;
    multiplyingExpressionElement->index = index;
    return std::move(multiplyingExpressionElement);
}

void PrMultiplyingExpressionElement::Reset() {
    PHelper::Reset();
    multiplyingExpressionElement.reset();
}

bool PrSignExpression::CheckAstNode(PStream& stream) {
    PhSeveral<PrSignExpressionElement> several;
    PrPrimeExpression primeExpression;
    PhAddition addition(&several, &primeExpression, &endHelper);
    
    if (!addition.Check(stream)) {
        return false;
    }
    
    signExpression = std::make_unique<SignExpression>();
    
    std::vector<std::unique_ptr<PrSignExpressionElement>>& helpers = several.GetHelpers();
    signExpression->signExpressionElements.reserve(helpers.size());
    
    for (int i = 0; i < helpers.size(); i++) {
        signExpression->signExpressionElements.push_back(*helpers[i]->GetSignExpressionElement(signExpression.get(),
            i));
        signExpression->signExpressionElements.back().UpdateChildren();
    }
    
    signExpression->primeExpression = primeExpression.GetPrimeExpression(signExpression.get());
    
    if (!signExpression->signExpressionElements.empty()) {
        signExpression->SetEntity(signExpression->signExpressionElements[0], *signExpression->primeExpression);
    }
    else {
        signExpression->SetEntity(*signExpression->primeExpression);
    }
    
    return true;
}

std::unique_ptr<SignExpression> PrSignExpression::GetSignExpression(void* prnt) {
    signExpression->prnt = prnt;
    return std::move(signExpression);
}

void PrSignExpression::Reset() {
    PHelper::Reset();
    signExpression.reset();
}

bool PrSignExpressionElement::CheckAstNode(PStream& stream) {
    PhFromToken fromTokenMinus(TokenType::minus);
    PhFromToken fromTokenPlus(TokenType::plus);
    PhAnyOf anyOf(&fromTokenMinus, &fromTokenPlus, &endHelper);
    
    if (!anyOf.Check(stream)) {
        return false;
    }
    
    signExpressionElement = std::make_unique<SignExpressionElement>();
    
    if (fromTokenMinus.GetChecked()) {
        signExpressionElement->isMinus = true;
        signExpressionElement->tkMinus = fromTokenMinus.GetToken(signExpressionElement.get());
    }
    else if (fromTokenPlus.GetChecked()) {
        signExpressionElement->isPlus = true;
        signExpressionElement->tkPlus = fromTokenPlus.GetToken(signExpressionElement.get());
    }
    
    if (signExpressionElement->isMinus) {
        signExpressionElement->SetEntity(signExpressionElement->tkMinus);
    }
    else if (signExpressionElement->isPlus) {
        signExpressionElement->SetEntity(signExpressionElement->tkPlus);
    }
    
    return true;
}

std::unique_ptr<SignExpressionElement> PrSignExpressionElement::GetSignExpressionElement(void* prnt,
    int index) {
    signExpressionElement->prnt = prnt;
    signExpressionElement->index = index;
    return std::move(signExpressionElement);
}

void PrSignExpressionElement::Reset() {
    PHelper::Reset();
    signExpressionElement.reset();
}
