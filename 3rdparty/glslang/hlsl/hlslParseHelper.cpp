//
// Copyright (C) 2016 Google, Inc.
// Copyright (C) 2016 LunarG, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#include "hlslParseHelper.h"
#include "hlslScanContext.h"
#include "hlslGrammar.h"
#include "hlslAttributes.h"

#include "../glslang/MachineIndependent/Scan.h"
#include "../glslang/MachineIndependent/preprocessor/PpContext.h"

#include "../glslang/OSDependent/osinclude.h"

#include <algorithm>
#include <functional>
#include <cctype>
#include <array>

namespace glslang {

HlslParseContext::HlslParseContext(TSymbolTable& symbolTable, TIntermediate& interm, bool parsingBuiltins,
                                   int version, EProfile profile, const SpvVersion& spvVersion, EShLanguage language, TInfoSink& infoSink,
                                   const TString sourceEntryPointName,
                                   bool forwardCompatible, EShMessages messages) :
    TParseContextBase(symbolTable, interm, parsingBuiltins, version, profile, spvVersion, language, infoSink, forwardCompatible, messages),
    contextPragma(true, false),
    loopNestingLevel(0), annotationNestingLevel(0), structNestingLevel(0), controlFlowNestingLevel(0),
    inEntryPoint(false),
    postEntryPointReturn(false),
    limits(resources.limits),
    entryPointOutput(nullptr),
    builtInIoIndex(nullptr),
    builtInIoBase(nullptr),
    nextInLocation(0), nextOutLocation(0),
    sourceEntryPointName(sourceEntryPointName)
{
    globalUniformDefaults.clear();
    globalUniformDefaults.layoutMatrix = ElmRowMajor;
    globalUniformDefaults.layoutPacking = ElpStd140;

    globalBufferDefaults.clear();
    globalBufferDefaults.layoutMatrix = ElmRowMajor;
    globalBufferDefaults.layoutPacking = ElpStd430;

    globalInputDefaults.clear();
    globalOutputDefaults.clear();

    // "Shaders in the transform
    // feedback capturing mode have an initial global default of
    //     layout(xfb_buffer = 0) out;"
    if (language == EShLangVertex ||
        language == EShLangTessControl ||
        language == EShLangTessEvaluation ||
        language == EShLangGeometry)
        globalOutputDefaults.layoutXfbBuffer = 0;

    if (language == EShLangGeometry)
        globalOutputDefaults.layoutStream = 0;

    if (spvVersion.spv == 0 || spvVersion.vulkan == 0)
        infoSink.info << "ERROR: HLSL currently only supported when requesting SPIR-V for Vulkan.\n";
}

HlslParseContext::~HlslParseContext()
{
}

void HlslParseContext::initializeExtensionBehavior()
{
    TParseContextBase::initializeExtensionBehavior();

    // HLSL allows #line by default.
    extensionBehavior[E_GL_GOOGLE_cpp_style_line_directive] = EBhEnable;
}

void HlslParseContext::setLimits(const TBuiltInResource& r)
{
    resources = r;
    intermediate.setLimits(resources);
}

//
// Parse an array of strings using the parser in HlslRules.
//
// Returns true for successful acceptance of the shader, false if any errors.
//
bool HlslParseContext::parseShaderStrings(TPpContext& ppContext, TInputScanner& input, bool versionWillBeError)
{
    currentScanner = &input;
    ppContext.setInput(input, versionWillBeError);

    HlslScanContext scanContext(*this, ppContext);
    HlslGrammar grammar(scanContext, *this);
    if (!grammar.parse()) {
        // Print a message formated such that if you click on the message it will take you right to
        // the line through most UIs.
        const glslang::TSourceLoc& sourceLoc = input.getSourceLoc();
        infoSink.info << sourceLoc.name << "(" << sourceLoc.line << "): error at column " << sourceLoc.column << ", HLSL parsing failed.\n";
        ++numErrors;
        return false;
    }

    finish();

    return numErrors == 0;
}

//
// Return true if this l-value node should be converted in some manner.
// For instance: turning a load aggregate into a store in an l-value.
//
bool HlslParseContext::shouldConvertLValue(const TIntermNode* node) const
{
    if (node == nullptr)
        return false;

    const TIntermAggregate* lhsAsAggregate = node->getAsAggregate();
    const TIntermBinary* lhsAsBinary = node->getAsBinaryNode();

    // If it's a swizzled/indexed aggregate, look at the left node instead.
    if (lhsAsBinary != nullptr &&
        (lhsAsBinary->getOp() == EOpVectorSwizzle || lhsAsBinary->getOp() == EOpIndexDirect))
        lhsAsAggregate = lhsAsBinary->getLeft()->getAsAggregate();

    if (lhsAsAggregate != nullptr && lhsAsAggregate->getOp() == EOpImageLoad)
        return true;

    return false;
}

//
// Return a TLayoutFormat corresponding to the given texture type.
//
TLayoutFormat HlslParseContext::getLayoutFromTxType(const TSourceLoc& loc, const TType& txType)
{
    const int components = txType.getVectorSize();

    const auto selectFormat = [this,&components](TLayoutFormat v1, TLayoutFormat v2, TLayoutFormat v4) -> TLayoutFormat {
        if (intermediate.getNoStorageFormat())
            return ElfNone;

        return components == 1 ? v1 :
               components == 2 ? v2 : v4;
    };

    switch (txType.getBasicType()) {
    case EbtFloat: return selectFormat(ElfR32f,  ElfRg32f,  ElfRgba32f);
    case EbtInt:   return selectFormat(ElfR32i,  ElfRg32i,  ElfRgba32i);
    case EbtUint:  return selectFormat(ElfR32ui, ElfRg32ui, ElfRgba32ui);
    default:
        error(loc, "unknown basic type in image format", "", "");
        return ElfNone;
    }
}

//
// Both test and if necessary, spit out an error, to see if the node is really
// an l-value that can be operated on this way.
//
// Returns true if there was an error.
//
bool HlslParseContext::lValueErrorCheck(const TSourceLoc& loc, const char* op, TIntermTyped* node)
{
    if (shouldConvertLValue(node)) {
        // if we're writing to a texture, it must be an RW form.

        TIntermAggregate* lhsAsAggregate = node->getAsAggregate();
        TIntermTyped* object = lhsAsAggregate->getSequence()[0]->getAsTyped();

        if (!object->getType().getSampler().isImage()) {
            error(loc, "operator[] on a non-RW texture must be an r-value", "", "");
            return true;
        }
    }

    // Let the base class check errors
    return TParseContextBase::lValueErrorCheck(loc, op, node);
}

//
// This function handles l-value conversions and verifications.  It uses, but is not synonymous
// with lValueErrorCheck.  That function accepts an l-value directly, while this one must be
// given the surrounding tree - e.g, with an assignment, so we can convert the assign into a
// series of other image operations.
//
// Most things are passed through unmodified, except for error checking.
//
TIntermTyped* HlslParseContext::handleLvalue(const TSourceLoc& loc, const char* op, TIntermTyped* node)
{
    if (node == nullptr)
        return nullptr;

    TIntermBinary* nodeAsBinary = node->getAsBinaryNode();
    TIntermUnary* nodeAsUnary = node->getAsUnaryNode();
    TIntermAggregate* sequence = nullptr;

    TIntermTyped* lhs = nodeAsUnary  ? nodeAsUnary->getOperand() :
                        nodeAsBinary ? nodeAsBinary->getLeft() :
                        nullptr;

    // Early bail out if there is no conversion to apply
    if (!shouldConvertLValue(lhs)) {
        if (lhs != nullptr)
            if (lValueErrorCheck(loc, op, lhs))
                return nullptr;
        return node;
    }

    // *** If we get here, we're going to apply some conversion to an l-value.

    // Helper to create a load.
    const auto makeLoad = [&](TIntermSymbol* rhsTmp, TIntermTyped* object, TIntermTyped* coord, const TType& derefType) {
        TIntermAggregate* loadOp = new TIntermAggregate(EOpImageLoad);
        loadOp->setLoc(loc);
        loadOp->getSequence().push_back(object);
        loadOp->getSequence().push_back(intermediate.addSymbol(*coord->getAsSymbolNode()));
        loadOp->setType(derefType);

        sequence = intermediate.growAggregate(sequence,
                                              intermediate.addAssign(EOpAssign, rhsTmp, loadOp, loc),
                                              loc);
    };

    // Helper to create a store.
    const auto makeStore = [&](TIntermTyped* object, TIntermTyped* coord, TIntermSymbol* rhsTmp) {
        TIntermAggregate* storeOp = new TIntermAggregate(EOpImageStore);
        storeOp->getSequence().push_back(object);
        storeOp->getSequence().push_back(coord);
        storeOp->getSequence().push_back(intermediate.addSymbol(*rhsTmp));
        storeOp->setLoc(loc);
        storeOp->setType(TType(EbtVoid));

        sequence = intermediate.growAggregate(sequence, storeOp);
    };

    // Helper to create an assign.
    const auto makeBinary = [&](TOperator op, TIntermTyped* lhs, TIntermTyped* rhs) {
        sequence = intermediate.growAggregate(sequence,
                                              intermediate.addBinaryNode(op, lhs, rhs, loc, lhs->getType()),
                                              loc);
    };

    // Helper to complete sequence by adding trailing variable, so we evaluate to the right value.
    const auto finishSequence = [&](TIntermSymbol* rhsTmp, const TType& derefType) -> TIntermAggregate* {
        // Add a trailing use of the temp, so the sequence returns the proper value.
        sequence = intermediate.growAggregate(sequence, intermediate.addSymbol(*rhsTmp));
        sequence->setOperator(EOpSequence);
        sequence->setLoc(loc);
        sequence->setType(derefType);

        return sequence;
    };

    // Helper to add unary op
    const auto makeUnary = [&](TOperator op, TIntermSymbol* rhsTmp) {
        sequence = intermediate.growAggregate(sequence,
                                              intermediate.addUnaryNode(op, intermediate.addSymbol(*rhsTmp), loc,
                                                                        rhsTmp->getType()),
                                              loc);
    };

    // Return true if swizzle or index writes all components of the given variable.
    const auto writesAllComponents = [&](TIntermSymbol* var, TIntermBinary* swizzle) -> bool {
        if (swizzle == nullptr)  // not a swizzle or index
            return true;

        // Track which components are being set.
        std::array<bool, 4> compIsSet;
        compIsSet.fill(false);

        const TIntermConstantUnion* asConst     = swizzle->getRight()->getAsConstantUnion();
        const TIntermAggregate*     asAggregate = swizzle->getRight()->getAsAggregate();

        // This could be either a direct index, or a swizzle.
        if (asConst) {
            compIsSet[asConst->getConstArray()[0].getIConst()] = true;
        } else if (asAggregate) {
            const TIntermSequence& seq = asAggregate->getSequence();
            for (int comp=0; comp<int(seq.size()); ++comp)
                compIsSet[seq[comp]->getAsConstantUnion()->getConstArray()[0].getIConst()] = true;
        } else {
            assert(0);
        }

        // Return true if all components are being set by the index or swizzle
        return std::all_of(compIsSet.begin(), compIsSet.begin() + var->getType().getVectorSize(),
                           [](bool isSet) { return isSet; } );
    };

    // helper to create a temporary variable
    const auto addTmpVar = [&](const char* name, const TType& derefType) -> TIntermSymbol* {
        TVariable* tmpVar = makeInternalVariable(name, derefType);
        tmpVar->getWritableType().getQualifier().makeTemporary();
        return intermediate.addSymbol(*tmpVar, loc);
    };

    // Create swizzle matching input swizzle
    const auto addSwizzle = [&](TIntermSymbol* var, TIntermBinary* swizzle) -> TIntermTyped* {
        if (swizzle)
            return intermediate.addBinaryNode(swizzle->getOp(), var, swizzle->getRight(), loc, swizzle->getType());
        else
            return var;
    };

    TIntermBinary*    lhsAsBinary    = lhs->getAsBinaryNode();
    TIntermAggregate* lhsAsAggregate = lhs->getAsAggregate();
    bool lhsIsSwizzle = false;

    // If it's a swizzled L-value, remember the swizzle, and use the LHS.
    if (lhsAsBinary != nullptr && (lhsAsBinary->getOp() == EOpVectorSwizzle || lhsAsBinary->getOp() == EOpIndexDirect)) {
        lhsAsAggregate = lhsAsBinary->getLeft()->getAsAggregate();
        lhsIsSwizzle = true;
    }

    TIntermTyped* object = lhsAsAggregate->getSequence()[0]->getAsTyped();
    TIntermTyped* coord  = lhsAsAggregate->getSequence()[1]->getAsTyped();

    const TSampler& texSampler = object->getType().getSampler();

    const TType objDerefType(texSampler.type, EvqTemporary, texSampler.vectorSize);

    if (nodeAsBinary) {
        TIntermTyped* rhs = nodeAsBinary->getRight();
        const TOperator assignOp = nodeAsBinary->getOp();

        bool isModifyOp = false;

        switch (assignOp) {
        case EOpAddAssign:
        case EOpSubAssign:
        case EOpMulAssign:
        case EOpVectorTimesMatrixAssign:
        case EOpVectorTimesScalarAssign:
        case EOpMatrixTimesScalarAssign:
        case EOpMatrixTimesMatrixAssign:
        case EOpDivAssign:
        case EOpModAssign:
        case EOpAndAssign:
        case EOpInclusiveOrAssign:
        case EOpExclusiveOrAssign:
        case EOpLeftShiftAssign:
        case EOpRightShiftAssign:
            isModifyOp = true;
            // fall through...
        case EOpAssign:
            {
                // Since this is an lvalue, we'll convert an image load to a sequence like this (to still provide the value):
                //   OpSequence
                //      OpImageStore(object, lhs, rhs)
                //      rhs
                // But if it's not a simple symbol RHS (say, a fn call), we don't want to duplicate the RHS, so we'll convert
                // instead to this:
                //   OpSequence
                //      rhsTmp = rhs
                //      OpImageStore(object, coord, rhsTmp)
                //      rhsTmp
                // If this is a read-modify-write op, like +=, we issue:
                //   OpSequence
                //      coordtmp = load's param1
                //      rhsTmp = OpImageLoad(object, coordTmp)
                //      rhsTmp op= rhs
                //      OpImageStore(object, coordTmp, rhsTmp)
                //      rhsTmp
                //
                // If the lvalue is swizzled, we apply that when writing the temp variable, like so:
                //    ...
                //    rhsTmp.some_swizzle = ...
                // For partial writes, an error is generated.

                TIntermSymbol* rhsTmp = rhs->getAsSymbolNode();
                TIntermTyped* coordTmp = coord;

                if (rhsTmp == nullptr || isModifyOp || lhsIsSwizzle) {
                    rhsTmp = addTmpVar("storeTemp", objDerefType);

                    // Partial updates not yet supported
                    if (!writesAllComponents(rhsTmp, lhsAsBinary)) {
                        error(loc, "unimplemented: partial image updates", "", "");
                    }

                    // Assign storeTemp = rhs
                    if (isModifyOp) {
                        // We have to make a temp var for the coordinate, to avoid evaluating it twice.
                        coordTmp = addTmpVar("coordTemp", coord->getType());
                        makeBinary(EOpAssign, coordTmp, coord); // coordtmp = load[param1]
                        makeLoad(rhsTmp, object, coordTmp, objDerefType); // rhsTmp = OpImageLoad(object, coordTmp)
                    }

                    // rhsTmp op= rhs.
                    makeBinary(assignOp, addSwizzle(intermediate.addSymbol(*rhsTmp), lhsAsBinary), rhs);
                }

                makeStore(object, coordTmp, rhsTmp);         // add a store
                return finishSequence(rhsTmp, objDerefType); // return rhsTmp from sequence
            }

        default:
            break;
        }
    }

    if (nodeAsUnary) {
        const TOperator assignOp = nodeAsUnary->getOp();

        switch (assignOp) {
        case EOpPreIncrement:
        case EOpPreDecrement:
            {
                // We turn this into:
                //   OpSequence
                //      coordtmp = load's param1
                //      rhsTmp = OpImageLoad(object, coordTmp)
                //      rhsTmp op
                //      OpImageStore(object, coordTmp, rhsTmp)
                //      rhsTmp

                TIntermSymbol* rhsTmp = addTmpVar("storeTemp", objDerefType);
                TIntermTyped* coordTmp = addTmpVar("coordTemp", coord->getType());

                makeBinary(EOpAssign, coordTmp, coord);           // coordtmp = load[param1]
                makeLoad(rhsTmp, object, coordTmp, objDerefType); // rhsTmp = OpImageLoad(object, coordTmp)
                makeUnary(assignOp, rhsTmp);                      // op rhsTmp
                makeStore(object, coordTmp, rhsTmp);              // OpImageStore(object, coordTmp, rhsTmp)
                return finishSequence(rhsTmp, objDerefType);      // return rhsTmp from sequence
            }

        case EOpPostIncrement:
        case EOpPostDecrement:
            {
                // We turn this into:
                //   OpSequence
                //      coordtmp = load's param1
                //      rhsTmp1 = OpImageLoad(object, coordTmp)
                //      rhsTmp2 = rhsTmp1
                //      rhsTmp2 op
                //      OpImageStore(object, coordTmp, rhsTmp2)
                //      rhsTmp1 (pre-op value)
                TIntermSymbol* rhsTmp1 = addTmpVar("storeTempPre",  objDerefType);
                TIntermSymbol* rhsTmp2 = addTmpVar("storeTempPost", objDerefType);
                TIntermTyped* coordTmp = addTmpVar("coordTemp", coord->getType());

                makeBinary(EOpAssign, coordTmp, coord);            // coordtmp = load[param1]
                makeLoad(rhsTmp1, object, coordTmp, objDerefType); // rhsTmp1 = OpImageLoad(object, coordTmp)
                makeBinary(EOpAssign, rhsTmp2, rhsTmp1);           // rhsTmp2 = rhsTmp1
                makeUnary(assignOp, rhsTmp2);                      // rhsTmp op
                makeStore(object, coordTmp, rhsTmp2);              // OpImageStore(object, coordTmp, rhsTmp2)
                return finishSequence(rhsTmp1, objDerefType);      // return rhsTmp from sequence
            }

        default:
            break;
        }
    }

    if (lhs)
        if (lValueErrorCheck(loc, op, lhs))
            return nullptr;

    return node;
}

void HlslParseContext::handlePragma(const TSourceLoc& loc, const TVector<TString>& tokens)
{
    if (pragmaCallback)
        pragmaCallback(loc.line, tokens);

    if (tokens.size() == 0)
        return;
}

//
// Look at a '.' matrix selector string and change it into components
// for a matrix. There are two types:
//
//   _21    second row, first column (one based)
//   _m21   third row, second column (zero based)
//
// Returns true if there is no error.
//
bool HlslParseContext::parseMatrixSwizzleSelector(const TSourceLoc& loc, const TString& fields, int cols, int rows,
                                                  TSwizzleSelectors<TMatrixSelector>& components)
{
    int startPos[MaxSwizzleSelectors];
    int numComps = 0;
    TString compString = fields;

    // Find where each component starts,
    // recording the first character position after the '_'.
    for (size_t c = 0; c < compString.size(); ++c) {
        if (compString[c] == '_') {
            if (numComps >= MaxSwizzleSelectors) {
                error(loc, "matrix component swizzle has too many components", compString.c_str(), "");
                return false;
            }
            if (c > compString.size() - 3 ||
                    ((compString[c+1] == 'm' || compString[c+1] == 'M') && c > compString.size() - 4)) {
                error(loc, "matrix component swizzle missing", compString.c_str(), "");
                return false;
            }
            startPos[numComps++] = c + 1;
        }
    }

    // Process each component
    for (int i = 0; i < numComps; ++i) {
        int pos = startPos[i];
        int bias = -1;
        if (compString[pos] == 'm' || compString[pos] == 'M') {
            bias = 0;
            ++pos;
        }
        TMatrixSelector comp;
        comp.coord1 = compString[pos+0] - '0' + bias;
        comp.coord2 = compString[pos+1] - '0' + bias;
        if (comp.coord1 < 0 || comp.coord1 >= cols) {
            error(loc, "matrix row component out of range", compString.c_str(), "");
            return false;
        }
        if (comp.coord2 < 0 || comp.coord2 >= rows) {
            error(loc, "matrix column component out of range", compString.c_str(), "");
            return false;
        }
        components.push_back(comp);
    }

    return true;
}

// If the 'comps' express a column of a matrix,
// return the column.  Column means the first coords all match.
//
// Otherwise, return -1.
//
int HlslParseContext::getMatrixComponentsColumn(int rows, const TSwizzleSelectors<TMatrixSelector>& selector)
{
    int col = -1;

    // right number of comps?
    if (selector.size() != rows)
        return -1;

    // all comps in the same column?
    // rows in order?
    col = selector[0].coord1;
    for (int i = 0; i < rows; ++i) {
        if (col != selector[i].coord1)
            return -1;
        if (i != selector[i].coord2)
            return -1;
    }

    return col;
}

//
// Handle seeing a variable identifier in the grammar.
//
TIntermTyped* HlslParseContext::handleVariable(const TSourceLoc& loc, TSymbol* symbol, const TString* string)
{
    if (symbol == nullptr)
        symbol = symbolTable.find(*string);
    if (symbol && symbol->getAsVariable() && symbol->getAsVariable()->isUserType()) {
        error(loc, "expected symbol, not user-defined type", string->c_str(), "");
        return nullptr;
    }

    // Error check for requiring specific extensions present.
    if (symbol && symbol->getNumExtensions())
        requireExtensions(loc, symbol->getNumExtensions(), symbol->getExtensions(), symbol->getName().c_str());

    const TVariable* variable;
    const TAnonMember* anon = symbol ? symbol->getAsAnonMember() : nullptr;
    TIntermTyped* node = nullptr;
    if (anon) {
        // It was a member of an anonymous container.

        // Create a subtree for its dereference.
        variable = anon->getAnonContainer().getAsVariable();
        TIntermTyped* container = intermediate.addSymbol(*variable, loc);
        TIntermTyped* constNode = intermediate.addConstantUnion(anon->getMemberNumber(), loc);
        node = intermediate.addIndex(EOpIndexDirectStruct, container, constNode, loc);

        node->setType(*(*variable->getType().getStruct())[anon->getMemberNumber()].type);
        if (node->getType().hiddenMember())
            error(loc, "member of nameless block was not redeclared", string->c_str(), "");
    } else {
        // Not a member of an anonymous container.

        // The symbol table search was done in the lexical phase.
        // See if it was a variable.
        variable = symbol ? symbol->getAsVariable() : nullptr;
        if (variable) {
            if ((variable->getType().getBasicType() == EbtBlock ||
                variable->getType().getBasicType() == EbtStruct) && variable->getType().getStruct() == nullptr) {
                error(loc, "cannot be used (maybe an instance name is needed)", string->c_str(), "");
                variable = nullptr;
            }
        } else {
            if (symbol)
                error(loc, "variable name expected", string->c_str(), "");
        }

        // Recovery, if it wasn't found or was not a variable.
        if (! variable) {
            error(loc, "unknown variable", string->c_str(), "");
            variable = new TVariable(string, TType(EbtVoid));
        }

        if (variable->getType().getQualifier().isFrontEndConstant())
            node = intermediate.addConstantUnion(variable->getConstArray(), variable->getType(), loc);
        else
            node = intermediate.addSymbol(*variable, loc);
    }

    if (variable->getType().getQualifier().isIo())
        intermediate.addIoAccessed(*string);

    return node;
}

//
// Handle operator[] on any objects it applies to.  Currently:
//    Textures
//    Buffers
//
TIntermTyped* HlslParseContext::handleBracketOperator(const TSourceLoc& loc, TIntermTyped* base, TIntermTyped* index)
{
    // handle r-value operator[] on textures and images.  l-values will be processed later.
    if (base->getType().getBasicType() == EbtSampler && !base->isArray()) {
        const TSampler& sampler = base->getType().getSampler();
        if (sampler.isImage() || sampler.isTexture()) {
            TIntermAggregate* load = new TIntermAggregate(sampler.isImage() ? EOpImageLoad : EOpTextureFetch);

            load->setType(TType(sampler.type, EvqTemporary, sampler.vectorSize));
            load->setLoc(loc);
            load->getSequence().push_back(base);
            load->getSequence().push_back(index);

            // Textures need a MIP.  First indirection is always to mip 0.  If there's another, we'll add it
            // later.
            if (sampler.isTexture())
                load->getSequence().push_back(intermediate.addConstantUnion(0, loc, true));

            return load;
        }
    }

    return nullptr;
}

//
// Handle seeing a base[index] dereference in the grammar.
//
TIntermTyped* HlslParseContext::handleBracketDereference(const TSourceLoc& loc, TIntermTyped* base, TIntermTyped* index)
{
    TIntermTyped* result = handleBracketOperator(loc, base, index);

    if (result != nullptr)
        return result;  // it was handled as an operator[]

    bool flattened = false;
    int indexValue = 0;
    if (index->getQualifier().storage == EvqConst) {
        indexValue = index->getAsConstantUnion()->getConstArray()[0].getIConst();
        checkIndex(loc, base->getType(), indexValue);
    }

    variableCheck(base);
    if (! base->isArray() && ! base->isMatrix() && ! base->isVector()) {
        if (base->getAsSymbolNode())
            error(loc, " left of '[' is not of type array, matrix, or vector ", base->getAsSymbolNode()->getName().c_str(), "");
        else
            error(loc, " left of '[' is not of type array, matrix, or vector ", "expression", "");
    } else if (base->getType().getQualifier().storage == EvqConst && index->getQualifier().storage == EvqConst)
        return intermediate.foldDereference(base, indexValue, loc);
    else {
        // at least one of base and index is variable...

        if (base->getAsSymbolNode() && (wasFlattened(base) || shouldFlatten(base->getType()))) {
            if (index->getQualifier().storage != EvqConst)
                error(loc, "Invalid variable index to flattened array", base->getAsSymbolNode()->getName().c_str(), "");

            result = flattenAccess(base, indexValue);
            flattened = (result != base);
        } else {
            splitAccessArray(loc, base, index);

            if (index->getQualifier().storage == EvqConst) {
                if (base->getType().isImplicitlySizedArray())
                    updateImplicitArraySize(loc, base, indexValue);
                result = intermediate.addIndex(EOpIndexDirect, base, index, loc);
            } else {
                result = intermediate.addIndex(EOpIndexIndirect, base, index, loc);
            }
        }
    }

    if (result == nullptr) {
        // Insert dummy error-recovery result
        result = intermediate.addConstantUnion(0.0, EbtFloat, loc);
    } else {
        // If the array reference was flattened, it has the correct type.  E.g, if it was
        // a uniform array, it was flattened INTO a set of scalar uniforms, not scalar temps.
        // In that case, we preserve the qualifiers.
        if (!flattened) {
            // Insert valid dereferenced result
            TType newType(base->getType(), 0);  // dereferenced type
            if (base->getType().getQualifier().storage == EvqConst && index->getQualifier().storage == EvqConst)
                newType.getQualifier().storage = EvqConst;
            else
                newType.getQualifier().storage = EvqTemporary;
            result->setType(newType);
        }
    }

    return result;
}

void HlslParseContext::checkIndex(const TSourceLoc& /*loc*/, const TType& /*type*/, int& /*index*/)
{
    // HLSL todo: any rules for index fixups?
}

// Handle seeing a binary node with a math operation.
TIntermTyped* HlslParseContext::handleBinaryMath(const TSourceLoc& loc, const char* str, TOperator op, TIntermTyped* left, TIntermTyped* right)
{
    TIntermTyped* result = intermediate.addBinaryMath(op, left, right, loc);
    if (! result)
        binaryOpError(loc, str, left->getCompleteString(), right->getCompleteString());

    return result;
}

// Handle seeing a unary node with a math operation.
TIntermTyped* HlslParseContext::handleUnaryMath(const TSourceLoc& loc, const char* str, TOperator op, TIntermTyped* childNode)
{
    TIntermTyped* result = intermediate.addUnaryMath(op, childNode, loc);

    if (result)
        return result;
    else
        unaryOpError(loc, str, childNode->getCompleteString());

    return childNode;
}

//
// Handle seeing a base.field dereference in the grammar.
//
TIntermTyped* HlslParseContext::handleDotDereference(const TSourceLoc& loc, TIntermTyped* base, const TString& field)
{
    variableCheck(base);

    //
    // methods can't be resolved until we later see the function-calling syntax.
    // Save away the name in the AST for now.  Processing is completed in
    // handleLengthMethod(), etc.
    //
    if (field == "length") {
        return intermediate.addMethod(base, TType(EbtInt), &field, loc);
    } else if (field == "CalculateLevelOfDetail"          ||
               field == "CalculateLevelOfDetailUnclamped" ||
               field == "Gather"                          ||
               field == "GatherRed"                       ||
               field == "GatherGreen"                     ||
               field == "GatherBlue"                      ||
               field == "GatherAlpha"                     ||
               field == "GatherCmp"                       ||
               field == "GatherCmpRed"                    ||
               field == "GatherCmpGreen"                  ||
               field == "GatherCmpBlue"                   ||
               field == "GatherCmpAlpha"                  ||
               field == "GetDimensions"                   ||
               field == "GetSamplePosition"               ||
               field == "Load"                            ||
               field == "Sample"                          ||
               field == "SampleBias"                      ||
               field == "SampleCmp"                       ||
               field == "SampleCmpLevelZero"              ||
               field == "SampleGrad"                      ||
               field == "SampleLevel") {
        // If it's not a method on a sampler object, we fall through in case it is a struct member.
        if (base->getType().getBasicType() == EbtSampler) {
            const TSampler& sampler = base->getType().getSampler();
            if (! sampler.isPureSampler()) {
                const int vecSize = sampler.isShadow() ? 1 : 4; // TODO: handle arbitrary sample return sizes
                return intermediate.addMethod(base, TType(sampler.type, EvqTemporary, vecSize), &field, loc);
            }
        }
    } else if (field == "Append" ||
               field == "RestartStrip") {
        // We cannot check the type here: it may be sanitized if we're not compiling a geometry shader, but
        // the code is around in the shader source.
        return intermediate.addMethod(base, TType(EbtVoid), &field, loc);
    }

    // It's not .length() if we get to here.

    if (base->isArray()) {
        error(loc, "cannot apply to an array:", ".", field.c_str());

        return base;
    }

    // It's neither an array nor .length() if we get here,
    // leaving swizzles and struct/block dereferences.

    TIntermTyped* result = base;
    if (base->isVector() || base->isScalar()) {
        TSwizzleSelectors<TVectorSelector> selectors;
        parseSwizzleSelector(loc, field, base->getVectorSize(), selectors);

        if (base->isScalar()) {
            if (selectors.size() == 1)
                return result;
            else {
                TType type(base->getBasicType(), EvqTemporary, selectors.size());
                return addConstructor(loc, base, type);
            }
        }
        if (base->getVectorSize() == 1) {
            TType scalarType(base->getBasicType(), EvqTemporary, 1);
            if (selectors.size() == 1)
                return addConstructor(loc, base, scalarType);
            else {
                TType vectorType(base->getBasicType(), EvqTemporary, selectors.size());
                return addConstructor(loc, addConstructor(loc, base, scalarType), vectorType);
            }
        }

        if (base->getType().getQualifier().isFrontEndConstant())
            result = intermediate.foldSwizzle(base, selectors, loc);
        else {
            if (selectors.size() == 1) {
                TIntermTyped* index = intermediate.addConstantUnion(selectors[0], loc);
                result = intermediate.addIndex(EOpIndexDirect, base, index, loc);
                result->setType(TType(base->getBasicType(), EvqTemporary));
            } else {
                TIntermTyped* index = intermediate.addSwizzle(selectors, loc);
                result = intermediate.addIndex(EOpVectorSwizzle, base, index, loc);
                result->setType(TType(base->getBasicType(), EvqTemporary, base->getType().getQualifier().precision, selectors.size()));
            }
        }
    } else if (base->isMatrix()) {
        TSwizzleSelectors<TMatrixSelector> selectors;
        if (! parseMatrixSwizzleSelector(loc, field, base->getMatrixCols(), base->getMatrixRows(), selectors))
            return result;

        if (selectors.size() == 1) {
            // Representable by m[c][r]
            if (base->getType().getQualifier().isFrontEndConstant()) {
                result = intermediate.foldDereference(base, selectors[0].coord1, loc);
                result = intermediate.foldDereference(result, selectors[0].coord2, loc);
            } else {
                result = intermediate.addIndex(EOpIndexDirect, base, intermediate.addConstantUnion(selectors[0].coord1, loc), loc);
                TType dereferencedCol(base->getType(), 0);
                result->setType(dereferencedCol);
                result = intermediate.addIndex(EOpIndexDirect, result, intermediate.addConstantUnion(selectors[0].coord2, loc), loc);
                TType dereferenced(dereferencedCol, 0);
                result->setType(dereferenced);
            }
        } else {
            int column = getMatrixComponentsColumn(base->getMatrixRows(), selectors);
            if (column >= 0) {
                // Representable by m[c]
                if (base->getType().getQualifier().isFrontEndConstant())
                    result = intermediate.foldDereference(base, column, loc);
                else {
                    result = intermediate.addIndex(EOpIndexDirect, base, intermediate.addConstantUnion(column, loc), loc);
                    TType dereferenced(base->getType(), 0);
                    result->setType(dereferenced);
                }
            } else {
                // general case, not a column, not a single component
                TIntermTyped* index = intermediate.addSwizzle(selectors, loc);
                result = intermediate.addIndex(EOpMatrixSwizzle, base, index, loc);
                result->setType(TType(base->getBasicType(), EvqTemporary, base->getType().getQualifier().precision, selectors.size()));
           }
        }
    } else if (base->getBasicType() == EbtStruct || base->getBasicType() == EbtBlock) {
        const TTypeList* fields = base->getType().getStruct();
        bool fieldFound = false;
        int member;
        for (member = 0; member < (int)fields->size(); ++member) {
            if ((*fields)[member].type->getFieldName() == field) {
                fieldFound = true;
                break;
            }
        }
        if (fieldFound) {
            if (base->getAsSymbolNode() && (wasFlattened(base) || shouldFlatten(base->getType()))) {
                result = flattenAccess(base, member);
            } else {
                // Update the base and member to access if this was a split structure.
                result = splitAccessStruct(loc, base, member);
                fields = base->getType().getStruct();

                if (result == nullptr) {
                    if (base->getType().getQualifier().storage == EvqConst)
                        result = intermediate.foldDereference(base, member, loc);
                    else {
                        TIntermTyped* index = intermediate.addConstantUnion(member, loc);
                        result = intermediate.addIndex(EOpIndexDirectStruct, base, index, loc);
                        result->setType(*(*fields)[member].type);
                    }
                }
            }
        } else
            error(loc, "no such field in structure", field.c_str(), "");
    } else
        error(loc, "does not apply to this type:", field.c_str(), base->getType().getCompleteString().c_str());

    return result;
}

// Determine whether we should split this type
bool HlslParseContext::shouldSplit(const TType& type)
{
    if (! inEntryPoint)
        return false;

    const TStorageQualifier qualifier = type.getQualifier().storage;

    // If it contains interstage IO, but not ONLY interstage IO, split the struct.
    return type.isStruct() && type.containsBuiltInInterstageIO(language) &&
        (qualifier == EvqVaryingIn || qualifier == EvqVaryingOut);
}

// Split the type of the given node into two structs:
//   1. interstage IO
//   2. everything else
// IO members are put into the ioStruct.  The type is modified to remove them.
void HlslParseContext::split(TIntermTyped* node)
{
    if (node == nullptr)
        return;

    TIntermSymbol* symNode = node->getAsSymbolNode();

    if (symNode == nullptr)
        return;

    // Create a new variable:
    TType& splitType = split(*symNode->getType().clone(), symNode->getName());

    splitIoVars[symNode->getId()] = makeInternalVariable(symNode->getName(), splitType);
}

// Split the type of the given variable into two structs:
void HlslParseContext::split(const TVariable& variable)
{
    const TType& type = variable.getType();

    TString name = (&variable == entryPointOutput) ? "" : variable.getName();

    // Create a new variable:
    TType& splitType = split(*type.clone(), name);

    splitIoVars[variable.getUniqueId()] = makeInternalVariable(variable.getName(), splitType);
}

// Recursive implementation of split(const TVariable& variable).
// Returns reference to the modified type.
TType& HlslParseContext::split(TType& type, TString name, const TType* outerStructType)
{
    const TArraySizes* arraySizes = nullptr;

    // At the outer-most scope, remember the struct type so we can examine its storage class
    // at deeper levels.
    if (outerStructType == nullptr)
        outerStructType = &type;

    if (type.isArray())
        arraySizes = &type.getArraySizes();

    // We can ignore arrayness: it's uninvolved.
    if (type.isStruct()) {
        TTypeList* userStructure = type.getWritableStruct();

        // Get iterator to (now at end) set of builtin iterstage IO members
        const auto firstIo = std::stable_partition(userStructure->begin(), userStructure->end(),
                                                   [this](const TTypeLoc& t) {return !t.type->isBuiltInInterstageIO(language);});

        // Move those to the builtin IO.  However, we also propagate arrayness (just one level is handled
        // now) to this variable.
        for (auto ioType = firstIo; ioType != userStructure->end(); ++ioType) {
            const TType& memberType = *ioType->type;
            TVariable* ioVar = makeInternalVariable(name + (name.empty() ? "" : "_") + memberType.getFieldName(), memberType);

            if (arraySizes)
                ioVar->getWritableType().newArraySizes(*arraySizes);

            interstageBuiltInIo[tInterstageIoData(memberType, *outerStructType)] = ioVar;

            // Merge qualifier from the user structure
            mergeQualifiers(ioVar->getWritableType().getQualifier(), outerStructType->getQualifier());
        }

        // Erase the IO vars from the user structure.
        userStructure->erase(firstIo, userStructure->end());

        // Recurse further into the members.
        for (unsigned int i = 0; i < userStructure->size(); ++i)
            split(*(*userStructure)[i].type,
                  name + (name.empty() ? "" : "_") + (*userStructure)[i].type->getFieldName(),
                  outerStructType);
    }

    return type;
}

// Determine whether we should flatten an arbitrary type.
bool HlslParseContext::shouldFlatten(const TType& type) const
{
    return shouldFlattenIO(type) || shouldFlattenUniform(type);
}

// Is this an IO variable that can't be passed down the stack?
// E.g., pipeline inputs to the vertex stage and outputs from the fragment stage.
bool HlslParseContext::shouldFlattenIO(const TType& type) const
{
    if (! inEntryPoint)
        return false;

    const TStorageQualifier qualifier = type.getQualifier().storage;

    if (!type.isStruct())
        return false;

    return ((language == EShLangVertex   && qualifier == EvqVaryingIn) ||
            (language == EShLangFragment && qualifier == EvqVaryingOut));
}

// Is this a uniform array which should be flattened?
bool HlslParseContext::shouldFlattenUniform(const TType& type) const
{
    const TStorageQualifier qualifier = type.getQualifier().storage;

    return ((type.isArray() && intermediate.getFlattenUniformArrays()) || type.isStruct()) &&
        qualifier == EvqUniform &&
        type.containsOpaque();
}

// Top level variable flattening: construct data
void HlslParseContext::flatten(const TSourceLoc& loc, const TVariable& variable)
{
    const TType& type = variable.getType();

    // emplace gives back a pair whose .first is an iterator to the item...
    auto entry = flattenMap.emplace(variable.getUniqueId(),
                                    TFlattenData(type.getQualifier().layoutBinding));

    // ... and the item is a map pair, so first->second is the TFlattenData itself.
    flatten(loc, variable, type, entry.first->second, "");
}

// Recursively flatten the given variable at the provided type, building the flattenData as we go.
//
// This is mutually recursive with flattenStruct and flattenArray.
// We are going to flatten an arbitrarily nested composite structure into a linear sequence of
// members, and later on, we want to turn a path through the tree structure into a final
// location in this linear sequence.
//
// If the tree was N-ary, that can be directly calculated.  However, we are dealing with
// arbitrary numbers - perhaps a struct of 7 members containing an array of 3.  Thus, we must
// build a data structure to allow the sequence of bracket and dot operators on arrays and
// structs to arrive at the proper member.
//
// To avoid storing a tree with pointers, we are going to flatten the tree into a vector of integers.
// The leaves are the indexes into the flattened member array.
// Each level will have the next location for the Nth item stored sequentially, so for instance:
//
// struct { float2 a[2]; int b; float4 c[3] };
//
// This will produce the following flattened tree:
// Pos: 0  1   2    3  4    5  6   7     8   9  10   11  12 13
//     (3, 7,  8,   5, 6,   0, 1,  2,   11, 12, 13,   3,  4, 5}
//
// Given a reference to mystruct.c[1], the access chain is (2,1), so we traverse:
//   (0+2) = 8  -->  (8+1) = 12 -->   12 = 4
//
// so the 4th flattened member in traversal order is ours.
//
int HlslParseContext::flatten(const TSourceLoc& loc, const TVariable& variable, const TType& type,
                              TFlattenData& flattenData, TString name)
{
    // If something is an arrayed struct, the array flattener will recursively call flatten()
    // to then flatten the struct, so this is an "if else": we don't do both.
    if (type.isArray())
        return flattenArray(loc, variable, type, flattenData, name);
    else if (type.isStruct())
        return flattenStruct(loc, variable, type, flattenData, name);
    else {
        assert(0); // should never happen
        return -1;
    }
}

// Add a single flattened member to the flattened data being tracked for the composite
// Returns true for the final flattening level.
int HlslParseContext::addFlattenedMember(const TSourceLoc& loc,
                                          const TVariable& variable, const TType& type, TFlattenData& flattenData,
                                          const TString& memberName, bool track)
{
    if (isFinalFlattening(type)) {
        // This is as far as we flatten.  Insert the variable.
        TVariable* memberVariable = makeInternalVariable(memberName, type);
        mergeQualifiers(memberVariable->getWritableType().getQualifier(), variable.getType().getQualifier());

        if (flattenData.nextBinding != TQualifier::layoutBindingEnd)
            memberVariable->getWritableType().getQualifier().layoutBinding = flattenData.nextBinding++;

        flattenData.offsets.push_back(static_cast<int>(flattenData.members.size()));
        flattenData.members.push_back(memberVariable);

        if (track)
            trackLinkageDeferred(*memberVariable);

        return static_cast<int>(flattenData.offsets.size())-1; // location of the member reference
    } else {
        // Further recursion required
        return flatten(loc, variable, type, flattenData, memberName);
    }
}

// Figure out the mapping between an aggregate's top members and an
// equivalent set of individual variables.
//
// N.B. Erases memory of I/O-related annotations in the original type's member,
//      effecting a transfer of this information to the flattened variable form.
//
// Assumes shouldFlatten() or equivalent was called first.
int HlslParseContext::flattenStruct(const TSourceLoc& loc, const TVariable& variable, const TType& type,
                                     TFlattenData& flattenData, TString name)
{
    assert(type.isStruct());

    auto members = *type.getStruct();

    // Reserve space for this tree level.
    int start = static_cast<int>(flattenData.offsets.size());
    int pos   = start;
    flattenData.offsets.resize(int(pos + members.size()), -1);

    for (int member = 0; member < (int)members.size(); ++member) {
        TType& dereferencedType = *members[member].type;
        const TString memberName = name + (name.empty() ? "" : ".") + dereferencedType.getFieldName();

        const int mpos = addFlattenedMember(loc, variable, dereferencedType, flattenData, memberName, false);
        flattenData.offsets[pos++] = mpos;

        // N.B. Erase I/O-related annotations from the source-type member.
        dereferencedType.getQualifier().makeTemporary();
    }

    return start;
}

// Figure out mapping between an array's members and an
// equivalent set of individual variables.
//
// Assumes shouldFlatten() or equivalent was called first.
int HlslParseContext::flattenArray(const TSourceLoc& loc, const TVariable& variable, const TType& type,
                                   TFlattenData& flattenData, TString name)
{
    assert(type.isArray());

    if (type.isImplicitlySizedArray())
        error(loc, "cannot flatten implicitly sized array", variable.getName().c_str(), "");

    const int size = type.getOuterArraySize();
    const TType dereferencedType(type, 0);

    if (name.empty())
        name = variable.getName();

    // Reserve space for this tree level.
    int start = static_cast<int>(flattenData.offsets.size());
    int pos   = start;
    flattenData.offsets.resize(int(pos + size), -1);

    for (int element=0; element < size; ++element) {
        char elementNumBuf[20];  // sufficient for MAXINT
        snprintf(elementNumBuf, sizeof(elementNumBuf)-1, "[%d]", element);
        const int mpos = addFlattenedMember(loc, variable, dereferencedType, flattenData,
                                            name + elementNumBuf, true);

        flattenData.offsets[pos++] = mpos;
    }

    return start;
}

// Return true if we have flattened this node.
bool HlslParseContext::wasFlattened(const TIntermTyped* node) const
{
    return node != nullptr && node->getAsSymbolNode() != nullptr &&
        wasFlattened(node->getAsSymbolNode()->getId());
}

// Return true if we have split this structure
bool HlslParseContext::wasSplit(const TIntermTyped* node) const
{
    return node != nullptr && node->getAsSymbolNode() != nullptr &&
        wasSplit(node->getAsSymbolNode()->getId());
}

// Turn an access into an aggregate that was flattened to instead be
// an access to the individual variable the member was flattened to.
// Assumes shouldFlatten() or equivalent was called first.
TIntermTyped* HlslParseContext::flattenAccess(TIntermTyped* base, int member)
{
    const TType dereferencedType(base->getType(), member);  // dereferenced type

    const TIntermSymbol& symbolNode = *base->getAsSymbolNode();

    const auto flattenData = flattenMap.find(symbolNode.getId());

    if (flattenData == flattenMap.end())
        return base;

    // Calculate new cumulative offset from the packed tree
    flattenOffset.back() = flattenData->second.offsets[flattenOffset.back() + member];

    if (isFinalFlattening(dereferencedType)) {
        // Finished flattening: create symbol for variable
        member = flattenData->second.offsets[flattenOffset.back()];
        const TVariable* memberVariable = flattenData->second.members[member];
        return intermediate.addSymbol(*memberVariable);
    } else {
        // If this is not the final flattening, accumulate the position and return
        // an object of the partially dereferenced type.
        return new TIntermSymbol(symbolNode.getId(), "flattenShadow", dereferencedType);
    }
}

// Find and return the split IO TVariable for id, or nullptr if none.
TVariable* HlslParseContext::getSplitIoVar(int id) const
{
    const auto splitIoVar = splitIoVars.find(id);

    if (splitIoVar == splitIoVars.end())
        return nullptr;

    return splitIoVar->second;
}

// Find and return the split IO TVariable for variable, or nullptr if none.
TVariable* HlslParseContext::getSplitIoVar(const TVariable* var) const
{
    if (var == nullptr)
        return nullptr;

    return getSplitIoVar(var->getUniqueId());
}

// Find and return the split IO TVariable for symbol in this node, or nullptr if none.
TVariable* HlslParseContext::getSplitIoVar(const TIntermTyped* node) const
{
    if (node == nullptr)
        return nullptr;

    const TIntermSymbol* symbolNode = node->getAsSymbolNode();

    if (symbolNode == nullptr)
        return nullptr;

    return getSplitIoVar(symbolNode->getId());
}

// Remember the index used to dereference into this structure, in case it has to be moved to a
// split-off builtin IO member.
void HlslParseContext::splitAccessArray(const TSourceLoc& loc, TIntermTyped* base, TIntermTyped* index)
{
    const TVariable* splitIoVar = getSplitIoVar(base);

    // Not a split structure
    if (splitIoVar == nullptr)
        return;

    if (builtInIoBase) {
        error(loc, "only one array dimension supported for builtIn IO variable", "", "");
        return;
    }

    builtInIoBase  = base;
    builtInIoIndex = index;
}

// Turn an access into an struct that was split to instead be an
// access to either the modified structure, or a direct reference to
// one of the split member variables.
TIntermTyped* HlslParseContext::splitAccessStruct(const TSourceLoc& loc, TIntermTyped*& base, int& member)
{
    // nothing to do
    if (base == nullptr)
        return nullptr;

    // We have a pending bracket reference to an outer struct that we may want to move to an inner member.
    if (builtInIoBase)
        base = builtInIoBase;

    const TVariable* splitIoVar = getSplitIoVar(base);

    if (splitIoVar == nullptr)
        return nullptr;

    const TTypeList& members = *base->getType().getStruct();

    const TType& memberType = *members[member].type;

    if (memberType.isBuiltInInterstageIO(language)) {
        // It's one of the interstage IO variables we split off.
        TIntermTyped* builtIn = intermediate.addSymbol(*interstageBuiltInIo[tInterstageIoData(memberType, base->getType())], loc);

        // If there's an array reference to an outer split struct, we re-apply it here.
        if (builtInIoIndex != nullptr) {
            if (builtInIoIndex->getQualifier().storage == EvqConst)
                builtIn = intermediate.addIndex(EOpIndexDirect, builtIn, builtInIoIndex, loc);
            else
                builtIn = intermediate.addIndex(EOpIndexIndirect, builtIn, builtInIoIndex, loc);

            builtIn->setType(memberType);

            builtInIoIndex = nullptr;
            builtInIoBase  = nullptr;
        }

        return builtIn;
    } else {
        // It's not an IO variable.  Find the equivalent index into the new variable.
        base = intermediate.addSymbol(*splitIoVar, loc);

        int newMember = 0;
        for (int m=0; m<member; ++m)
            if (!members[m].type->isBuiltInInterstageIO(language))
                ++newMember;

        member = newMember;

        return nullptr;
    }
}

// Variables that correspond to the user-interface in and out of a stage
// (not the built-in interface) are assigned locations and
// registered as a linkage node (part of the stage's external interface).
//
// Assumes it is called in the order in which locations should be assigned.
void HlslParseContext::assignLocations(TVariable& variable)
{
    const auto assignLocation = [&](TVariable& variable) {
        const TQualifier& qualifier = variable.getType().getQualifier();
        if (qualifier.storage == EvqVaryingIn || qualifier.storage == EvqVaryingOut) {
            if (qualifier.builtIn == EbvNone) {
                if (qualifier.storage == EvqVaryingIn) {
                    variable.getWritableType().getQualifier().layoutLocation = nextInLocation;
                    nextInLocation += intermediate.computeTypeLocationSize(variable.getType());
                } else {
                    variable.getWritableType().getQualifier().layoutLocation = nextOutLocation;
                    nextOutLocation += intermediate.computeTypeLocationSize(variable.getType());
                }
            }
            trackLinkage(variable);
        }
    };

    if (wasFlattened(variable.getUniqueId())) {
        auto& memberList = flattenMap[variable.getUniqueId()].members;
        for (auto member = memberList.begin(); member != memberList.end(); ++member)
            assignLocation(**member);
    } else if (wasSplit(variable.getUniqueId())) {
        TVariable* splitIoVar = getSplitIoVar(&variable);
        const TTypeList* structure = splitIoVar->getType().getStruct();
        // Struct splitting can produce empty structures if the only members of the
        // struct were builtin interstage IO types.  Only assign locations if it
        // isn't a struct, or is a non-empty struct.
        if (structure == nullptr || !structure->empty())
            assignLocation(*splitIoVar);
    } else {
        assignLocation(variable);
    }
}

//
// Handle seeing a function declarator in the grammar.  This is the precursor
// to recognizing a function prototype or function definition.
//
TFunction& HlslParseContext::handleFunctionDeclarator(const TSourceLoc& loc, TFunction& function, bool prototype)
{
    //
    // Multiple declarations of the same function name are allowed.
    //
    // If this is a definition, the definition production code will check for redefinitions
    // (we don't know at this point if it's a definition or not).
    //
    bool builtIn;
    TSymbol* symbol = symbolTable.find(function.getMangledName(), &builtIn);
    const TFunction* prevDec = symbol ? symbol->getAsFunction() : 0;

    if (prototype) {
        // All built-in functions are defined, even though they don't have a body.
        // Count their prototype as a definition instead.
        if (symbolTable.atBuiltInLevel())
            function.setDefined();
        else {
            if (prevDec && ! builtIn)
                symbol->getAsFunction()->setPrototyped();  // need a writable one, but like having prevDec as a const
            function.setPrototyped();
        }
    }

    // This insert won't actually insert it if it's a duplicate signature, but it will still check for
    // other forms of name collisions.
    if (! symbolTable.insert(function))
        error(loc, "function name is redeclaration of existing name", function.getName().c_str(), "");

    //
    // If this is a redeclaration, it could also be a definition,
    // in which case, we need to use the parameter names from this one, and not the one that's
    // being redeclared.  So, pass back this declaration, not the one in the symbol table.
    //
    return function;
}

// Add interstage IO variables to the linkage in canonical order.
void HlslParseContext::addInterstageIoToLinkage()
{
    TSourceLoc loc;
    loc.init();

    std::vector<tInterstageIoData> io;
    io.reserve(interstageBuiltInIo.size());

    for (auto ioVar = interstageBuiltInIo.begin(); ioVar != interstageBuiltInIo.end(); ++ioVar)
        io.push_back(ioVar->first);

    // Our canonical order is the TBuiltInVariable numeric order.
    std::sort(io.begin(), io.end());

    // We have to (potentially) track two IO blocks, one in, one out.  E.g, a GS may have a
    // PerVertex block in both directions, possibly with different members.
    static const TStorageQualifier ioType[2] = { EvqVaryingIn, EvqVaryingOut };
    static const char* blockName[2] = { "PerVertex_in", "PerVertex_out" };

    TTypeList*   ioBlockTypes[2] = { nullptr, nullptr };
    TArraySizes* ioBlockArray[2] = { nullptr, nullptr };

    for (int idx = 0; idx < int(io.size()); ++idx) {
        TVariable* var = interstageBuiltInIo[io[idx]];

        // Add the loose interstage IO to the linkage
        if (var->getType().isLooseAndBuiltIn(language))
            trackLinkageDeferred(*var);

        // Add the PerVertex interstage IO to the IO block
        if (var->getType().isPerVertexAndBuiltIn(language)) {
            int blockId = 0;
            switch (var->getType().getQualifier().storage) {
            case EvqVaryingIn:  blockId = 0; break;
            case EvqVaryingOut: blockId = 1; break;
            default: assert(0 && "Invalid storage qualifier");
            }

            // Lazy creation of type list only if we end up needing it.
            if (ioBlockTypes[blockId] == nullptr)
                ioBlockTypes[blockId] = new TTypeList();

            TTypeLoc member = { new TType(EbtVoid), loc };
            member.type->shallowCopy(var->getType());
            member.type->setFieldName(var->getName());

            // We may have collected these from different parts of different structures.  If their
            // array dimensions are not the same, we don't know what to do, so issue an error.
            if (member.type->isArray()) {
                if (ioBlockArray[blockId] == nullptr) {
                    ioBlockArray[blockId] = &member.type->getArraySizes();
                } else  {
                    if (*ioBlockArray[blockId] != member.type->getArraySizes())
                        error(loc, "PerVertex block array dimension mismatch", "", "");
                }
                member.type->clearArraySizes();
            }

            ioBlockTypes[blockId]->push_back(member);
        }
    }

    // If there were PerVertex items, add the block to the linkage.  Handle in and out separately.
    for (int blockId = 0; blockId <= 1; ++blockId) {
        if (ioBlockTypes[blockId] != nullptr) {
            const TString* instanceName = NewPoolTString(blockName[blockId]);
            TQualifier     blockQualifier;

            blockQualifier.clear();
            blockQualifier.storage = ioType[blockId];

            TType blockType(ioBlockTypes[blockId], *instanceName, blockQualifier);

            if (ioBlockArray[blockId] != nullptr)
                blockType.newArraySizes(*ioBlockArray[blockId]);

            TVariable* ioBlock = new TVariable(instanceName, blockType);
            if (!symbolTable.insert(*ioBlock))
                error(loc, "block instance name redefinition", ioBlock->getName().c_str(), "");
            else
                trackLinkageDeferred(*ioBlock);
        }
    }
}

//
// Handle seeing the function prototype in front of a function definition in the grammar.
// The body is handled after this function returns.
//
TIntermAggregate* HlslParseContext::handleFunctionDefinition(const TSourceLoc& loc, TFunction& function,
                                                             const TAttributeMap& attributes)
{
    currentCaller = function.getMangledName();
    TSymbol* symbol = symbolTable.find(function.getMangledName());
    TFunction* prevDec = symbol ? symbol->getAsFunction() : nullptr;

    if (! prevDec)
        error(loc, "can't find function", function.getName().c_str(), "");
    // Note:  'prevDec' could be 'function' if this is the first time we've seen function
    // as it would have just been put in the symbol table.  Otherwise, we're looking up
    // an earlier occurrence.

    if (prevDec && prevDec->isDefined()) {
        // Then this function already has a body.
        error(loc, "function already has a body", function.getName().c_str(), "");
    }
    if (prevDec && ! prevDec->isDefined()) {
        prevDec->setDefined();

        // Remember the return type for later checking for RETURN statements.
        currentFunctionType = &(prevDec->getType());
    } else
        currentFunctionType = new TType(EbtVoid);
    functionReturnsValue = false;

    // Entry points need different I/O and other handling, transform it so the
    // rest of this function doesn't care.
    transformEntryPoint(loc, function, attributes);

    // Insert the $Global constant buffer.
    // TODO: this design fails if new members are declared between function definitions.
    if (! insertGlobalUniformBlock())
        error(loc, "failed to insert the global constant buffer", "uniform", "");

    //
    // New symbol table scope for body of function plus its arguments
    //
    pushScope();

    //
    // Insert parameters into the symbol table.
    // If the parameter has no name, it's not an error, just don't insert it
    // (could be used for unused args).
    //
    // Also, accumulate the list of parameters into the AST, so lower level code
    // knows where to find parameters.
    //
    TIntermAggregate* paramNodes = new TIntermAggregate;
    for (int i = 0; i < function.getParamCount(); i++) {
        TParameter& param = function[i];
        if (param.name != nullptr) {
            TType* sanitizedType;

            // If we're not in the entry point, parameters are sanitized types.
            if (inEntryPoint)
                sanitizedType = param.type;
            else
                sanitizedType = sanitizeType(param.type);

            TVariable *variable = new TVariable(param.name, *sanitizedType);

            // Insert the parameters with name in the symbol table.
            if (! symbolTable.insert(*variable))
                error(loc, "redefinition", variable->getName().c_str(), "");
            else {
                // get IO straightened out
                if (inEntryPoint) {
                    if (shouldFlatten(*param.type))
                        flatten(loc, *variable);
                    if (shouldSplit(*param.type))
                        split(*variable);
                    assignLocations(*variable);
                }

                // Transfer ownership of name pointer to symbol table.
                param.name = nullptr;

                // Add the parameter to the AST
                paramNodes = intermediate.growAggregate(paramNodes,
                                                        intermediate.addSymbol(*variable, loc),
                                                        loc);
            }
        } else
            paramNodes = intermediate.growAggregate(paramNodes, intermediate.addSymbol(*param.type, loc), loc);
    }

    intermediate.setAggregateOperator(paramNodes, EOpParameters, TType(EbtVoid), loc);
    loopNestingLevel = 0;
    controlFlowNestingLevel = 0;
    postEntryPointReturn = false;

    return paramNodes;
}

//
// Do all special handling for the entry point.
//
void HlslParseContext::transformEntryPoint(const TSourceLoc& loc, TFunction& function, const TAttributeMap& attributes)
{
    inEntryPoint = function.getName().compare(intermediate.getEntryPointName().c_str()) == 0;

    if (!inEntryPoint) {
        remapNonEntryPointIO(function);
        return;
    }

    // entry point logic...

    intermediate.setEntryPointMangledName(function.getMangledName().c_str());
    intermediate.incrementEntryPointCount();

    // Handle parameters and return value
    remapEntryPointIO(function);
    if (entryPointOutput) {
        if (shouldFlatten(entryPointOutput->getType()))
            flatten(loc, *entryPointOutput);
        if (shouldSplit(entryPointOutput->getType()))
            split(*entryPointOutput);
        assignLocations(*entryPointOutput);
    }

    // Handle function attributes
    const TIntermAggregate* numThreads = attributes[EatNumThreads];
    if (numThreads != nullptr) {
        const TIntermSequence& sequence = numThreads->getSequence();

        for (int lid = 0; lid < int(sequence.size()); ++lid)
            intermediate.setLocalSize(lid, sequence[lid]->getAsConstantUnion()->getConstArray()[0].getIConst());
    }
    const TIntermAggregate* maxVertexCount = attributes[EatMaxVertexCount];
    if (maxVertexCount != nullptr)
        intermediate.setVertices(maxVertexCount->getSequence()[0]->getAsConstantUnion()->getConstArray()[0].getIConst());
}

void HlslParseContext::handleFunctionBody(const TSourceLoc& loc, TFunction& function, TIntermNode* functionBody, TIntermNode*& node)
{
    node = intermediate.growAggregate(node, functionBody);
    intermediate.setAggregateOperator(node, EOpFunction, function.getType(), loc);
    node->getAsAggregate()->setName(function.getMangledName().c_str());

    popScope();

    if (function.getType().getBasicType() != EbtVoid && ! functionReturnsValue)
        error(loc, "function does not return a value:", "", function.getName().c_str());
}

// AST I/O is done through shader globals declared in the 'in' or 'out'
// storage class.  An HLSL entry point has a return value, input parameters
// and output parameters.  These need to get remapped to the AST I/O.
void HlslParseContext::remapEntryPointIO(TFunction& function)
{
    // Will auto-assign locations here to the inputs/outputs defined by the entry point

    const auto remapType = [&](TType& type) {
        const auto remapBuiltInType = [&](TType& type) {
            switch (type.getQualifier().builtIn) {
            case EbvFragDepthGreater:
                intermediate.setDepth(EldGreater);
                type.getQualifier().builtIn = EbvFragDepth;
                break;
            case EbvFragDepthLesser:
                intermediate.setDepth(EldLess);
                type.getQualifier().builtIn = EbvFragDepth;
                break;
            default:
                break;
            }
        };
        remapBuiltInType(type);
        if (type.isStruct()) {
            auto members = *type.getStruct();
            for (auto member = members.begin(); member != members.end(); ++member)
                remapBuiltInType(*member->type);
        }
    };

    // return value is actually a shader-scoped output (out)
    if (function.getType().getBasicType() != EbtVoid) {
        entryPointOutput = makeInternalVariable("@entryPointOutput", function.getType());
        entryPointOutput->getWritableType().getQualifier().storage = EvqVaryingOut;
        remapType(function.getWritableType());
    }

    // parameters are actually shader-scoped inputs and outputs (in or out)
    for (int i = 0; i < function.getParamCount(); i++) {
        TType& paramType = *function[i].type;
        paramType.getQualifier().storage = paramType.getQualifier().isParamInput() ? EvqVaryingIn : EvqVaryingOut;
        remapType(paramType);
    }
}

// An HLSL function that looks like an entry point, but is not,
// declares entry point IO built-ins, but these have to be undone.
void HlslParseContext::remapNonEntryPointIO(TFunction& function)
{
    const auto remapBuiltInType = [&](TType& type) { type.getQualifier().builtIn = EbvNone; };

    // return value
    if (function.getType().getBasicType() != EbtVoid)
        remapBuiltInType(function.getWritableType());

    // parameters
    for (int i = 0; i < function.getParamCount(); i++)
        remapBuiltInType(*function[i].type);
}

// Handle function returns, including type conversions to the function return type
// if necessary.
TIntermNode* HlslParseContext::handleReturnValue(const TSourceLoc& loc, TIntermTyped* value)
{
    functionReturnsValue = true;

    if (currentFunctionType->getBasicType() == EbtVoid) {
        error(loc, "void function cannot return a value", "return", "");
        return intermediate.addBranch(EOpReturn, loc);
    } else if (*currentFunctionType != value->getType()) {
        value = intermediate.addConversion(EOpReturn, *currentFunctionType, value);
        if (value && *currentFunctionType != value->getType())
            value = intermediate.addShapeConversion(EOpReturn, *currentFunctionType, value);
        if (value == nullptr) {
            error(loc, "type does not match, or is not convertible to, the function's return type", "return", "");
            return value;
        }
    }

    // The entry point needs to send any return value to the entry-point output instead.
    // So, a subtree is built up, as a two-part sequence, with the first part being an
    // assignment subtree, and the second part being a return with no value.
    //
    // Otherwise, for a non entry point, just return a return statement.
    if (inEntryPoint) {
        assert(entryPointOutput != nullptr); // should have been error tested at the beginning
        TIntermSymbol* left = new TIntermSymbol(entryPointOutput->getUniqueId(), entryPointOutput->getName(),
                                                entryPointOutput->getType());
        TIntermNode* returnSequence = handleAssign(loc, EOpAssign, left, value);
        returnSequence = intermediate.makeAggregate(returnSequence);
        returnSequence = intermediate.growAggregate(returnSequence, intermediate.addBranch(EOpReturn, loc), loc);
        returnSequence->getAsAggregate()->setOperator(EOpSequence);

        return returnSequence;
    } else
        return intermediate.addBranch(EOpReturn, value, loc);
}

void HlslParseContext::handleFunctionArgument(TFunction* function,
                                              TIntermTyped*& arguments, TIntermTyped* newArg)
{
    TParameter param = { 0, new TType, nullptr };
    param.type->shallowCopy(newArg->getType());

    function->addParameter(param);
    if (arguments)
        arguments = intermediate.growAggregate(arguments, newArg);
    else
        arguments = newArg;
}

// Some simple source assignments need to be flattened to a sequence
// of AST assignments. Catch these and flatten, otherwise, pass through
// to intermediate.addAssign().
//
// Also, assignment to matrix swizzles requires multiple component assignments,
// intercept those as well.
TIntermTyped* HlslParseContext::handleAssign(const TSourceLoc& loc, TOperator op, TIntermTyped* left, TIntermTyped* right)
{
    if (left == nullptr || right == nullptr)
        return nullptr;

    if (left->getAsOperator() && left->getAsOperator()->getOp() == EOpMatrixSwizzle)
        return handleAssignToMatrixSwizzle(loc, op, left, right);

    const bool isSplitLeft    = wasSplit(left);
    const bool isSplitRight   = wasSplit(right);

    const bool isFlattenLeft  = wasFlattened(left);
    const bool isFlattenRight = wasFlattened(right);

    // OK to do a single assign if both are split, or both are unsplit.  But if one is and the other
    // isn't, we fall back to a member-wise copy.
    if (! isFlattenLeft && ! isFlattenRight && !isSplitLeft && !isSplitRight)
        return intermediate.addAssign(op, left, right, loc);

    TIntermAggregate* assignList = nullptr;
    const TVector<TVariable*>* leftVariables = nullptr;
    const TVector<TVariable*>* rightVariables = nullptr;

    // A temporary to store the right node's value, so we don't keep indirecting into it
    // if it's not a simple symbol.
    TVariable*     rhsTempVar   = nullptr;

    // If the RHS is a simple symbol node, we'll copy it for each member.
    TIntermSymbol* cloneSymNode = nullptr;

    int memberCount = 0;

    // Track how many items there are to copy.
    if (left->getType().isStruct())
        memberCount = (int)left->getType().getStruct()->size();
    if (left->getType().isArray())
        memberCount = left->getType().getCumulativeArraySize();

    if (isFlattenLeft)
        leftVariables = &flattenMap.find(left->getAsSymbolNode()->getId())->second.members;

    if (isFlattenRight) {
        rightVariables = &flattenMap.find(right->getAsSymbolNode()->getId())->second.members;
    } else {
        // The RHS is not flattened.  There are several cases:
        // 1. 1 item to copy:  Use the RHS directly.
        // 2. >1 item, simple symbol RHS: we'll create a new TIntermSymbol node for each, but no assign to temp.
        // 3. >1 item, complex RHS: assign it to a new temp variable, and create a TIntermSymbol for each member.

        if (memberCount <= 1) {
            // case 1: we'll use the symbol directly below.  Nothing to do.
        } else {
            if (right->getAsSymbolNode() != nullptr) {
                // case 2: we'll copy the symbol per iteration below.
                cloneSymNode = right->getAsSymbolNode();
            } else {
                // case 3: assign to a temp, and indirect into that.
                rhsTempVar = makeInternalVariable("flattenTemp", right->getType());
                rhsTempVar->getWritableType().getQualifier().makeTemporary();
                TIntermTyped* noFlattenRHS = intermediate.addSymbol(*rhsTempVar, loc);

                // Add this to the aggregate being built.
                assignList = intermediate.growAggregate(assignList, intermediate.addAssign(op, noFlattenRHS, right, loc), loc);
            }
        }
    }

    int memberIdx = 0;

    // We track the outer-most aggregate, so that we can use its storage class later.
    const TIntermTyped* outerLeft  = left;
    const TIntermTyped* outerRight = right;

    const auto getMember = [&](bool isLeft, TIntermTyped* node, int member, TIntermTyped* splitNode, int splitMember) -> TIntermTyped * {
        TIntermTyped* subTree;

        const bool flattened      = isLeft ? isFlattenLeft : isFlattenRight;
        const bool split          = isLeft ? isSplitLeft : isSplitRight;
        const TIntermTyped* outer = isLeft ? outerLeft   : outerRight;
        const TVector<TVariable*>& flatVariables      = isLeft ? *leftVariables : *rightVariables;
        const TOperator op = node->getType().isArray() ? EOpIndexDirect : EOpIndexDirectStruct;
        const TType derefType(node->getType(), member);

        if (split && derefType.isBuiltInInterstageIO(language)) {
            // copy from interstage IO builtin if needed
            subTree = intermediate.addSymbol(*interstageBuiltInIo.find(tInterstageIoData(derefType, outer->getType()))->second);
        } else if (flattened && isFinalFlattening(derefType)) {
            subTree = intermediate.addSymbol(*flatVariables[memberIdx++]);
        } else {
            const TType splitDerefType(splitNode->getType(), splitMember);

            subTree = intermediate.addIndex(op, splitNode, intermediate.addConstantUnion(splitMember, loc), loc);
            subTree->setType(splitDerefType);
        }

        return subTree;
    };

    // Use the proper RHS node: a new symbol from a TVariable, copy
    // of an TIntermSymbol node, or sometimes the right node directly.
    right = rhsTempVar   ? intermediate.addSymbol(*rhsTempVar, loc) :
            cloneSymNode ? intermediate.addSymbol(*cloneSymNode) :
            right;

    // Cannot use auto here, because this is recursive, and auto can't work out the type without seeing the
    // whole thing.  So, we'll resort to an explicit type via std::function.
    const std::function<void(TIntermTyped* left, TIntermTyped* right, TIntermTyped* splitLeft, TIntermTyped* splitRight)>
    traverse = [&](TIntermTyped* left, TIntermTyped* right, TIntermTyped* splitLeft, TIntermTyped* splitRight) -> void {
        // If we get here, we are assigning to or from a whole array or struct that must be
        // flattened, so have to do member-by-member assignment:

        if (left->getType().isArray()) {
            const TType dereferencedType(left->getType(), 0);

            // array case
            for (int element=0; element < left->getType().getOuterArraySize(); ++element) {
                    // Add a new AST symbol node if we have a temp variable holding a complex RHS.
                TIntermTyped* subLeft  = getMember(true,  left,  element, left, element);
                TIntermTyped* subRight = getMember(false, right, element, right, element);

                TIntermTyped* subSplitLeft =  isSplitLeft  ? getMember(true,  left,  element, splitLeft, element) : subLeft;
                TIntermTyped* subSplitRight = isSplitRight ? getMember(false, right, element, splitRight, element) : subRight; 

                if (isFinalFlattening(dereferencedType))
                    assignList = intermediate.growAggregate(assignList, intermediate.addAssign(op, subLeft, subRight, loc), loc);
                else
                    traverse(subLeft, subRight, subSplitLeft, subSplitRight);
            }
        } else if (left->getType().isStruct()) {
            // struct case
            const auto& membersL = *left->getType().getStruct();
            const auto& membersR = *right->getType().getStruct();

            // These track the members in the split structures corresponding to the same in the unsplit structures,
            // which we traverse in parallel.
            int memberL = 0;
            int memberR = 0;

            for (int member = 0; member < int(membersL.size()); ++member) {
                const TType& typeL = *membersL[member].type;
                const TType& typeR = *membersR[member].type;

                TIntermTyped* subLeft  = getMember(true,  left, member, left, member);
                TIntermTyped* subRight = getMember(false, right, member, right, member);

                // If there is no splitting, use the same values to avoid inefficiency.
                TIntermTyped* subSplitLeft =  isSplitLeft  ? getMember(true,  left,  member, splitLeft, memberL) : subLeft;
                TIntermTyped* subSplitRight = isSplitRight ? getMember(false, right, member, splitRight, memberR) : subRight;

                // If this is the final flattening (no nested types below to flatten) we'll copy the member, else
                // recurse into the type hierarchy.  However, if splitting the struct, that means we can copy a whole
                // subtree here IFF it does not itself contain any interstage built-in IO variables, so we only have to
                // recurse into it if there's something for splitting to do.  That can save a lot of AST verbosity for
                // a bunch of memberwise copies.
                if (isFinalFlattening(typeL) || (!isFlattenLeft && !isFlattenRight &&
                                                 !typeL.containsBuiltInInterstageIO(language) && !typeR.containsBuiltInInterstageIO(language))) {
                    assignList = intermediate.growAggregate(assignList, intermediate.addAssign(op, subSplitLeft, subSplitRight, loc), loc);
                } else {
                    traverse(subLeft, subRight, subSplitLeft, subSplitRight);
                }

                memberL += (typeL.isBuiltInInterstageIO(language) ? 0 : 1);
                memberR += (typeR.isBuiltInInterstageIO(language) ? 0 : 1);
            }
        } else {
            assert(0);  // we should never be called on a non-flattenable thing, because
                        // that case bails out above to a simple copy.
        }

    };

    TIntermTyped* splitLeft  = left;
    TIntermTyped* splitRight = right;

    // If either left or right was a split structure, we must read or write it, but still have to
    // parallel-recurse through the unsplit structure to identify the builtin IO vars.
    if (isSplitLeft)
        splitLeft = intermediate.addSymbol(*getSplitIoVar(left), loc);

    if (isSplitRight)
        splitRight = intermediate.addSymbol(*getSplitIoVar(right), loc);

    // This makes the whole assignment, recursing through subtypes as needed.
    traverse(left, right, splitLeft, splitRight);

    assert(assignList != nullptr);
    assignList->setOperator(EOpSequence);

    return assignList;
}

// An assignment to matrix swizzle must be decomposed into individual assignments.
// These must be selected component-wise from the RHS and stored component-wise
// into the LHS.
TIntermTyped* HlslParseContext::handleAssignToMatrixSwizzle(const TSourceLoc& loc, TOperator op, TIntermTyped* left, TIntermTyped* right)
{
    assert(left->getAsOperator() && left->getAsOperator()->getOp() == EOpMatrixSwizzle);

    if (op != EOpAssign)
        error(loc, "only simple assignment to non-simple matrix swizzle is supported", "assign", "");

    // isolate the matrix and swizzle nodes
    TIntermTyped* matrix = left->getAsBinaryNode()->getLeft()->getAsTyped();
    const TIntermSequence& swizzle = left->getAsBinaryNode()->getRight()->getAsAggregate()->getSequence();

    // if the RHS isn't already a simple vector, let's store into one
    TIntermSymbol* vector = right->getAsSymbolNode();
    TIntermTyped* vectorAssign = nullptr;
    if (vector == nullptr) {
        // create a new intermediate vector variable to assign to
        TType vectorType(matrix->getBasicType(), EvqTemporary, matrix->getQualifier().precision, swizzle.size()/2);
        vector = intermediate.addSymbol(*makeInternalVariable("intermVec", vectorType), loc);

        // assign the right to the new vector
        vectorAssign = handleAssign(loc, op, vector, right);
    }

    // Assign the vector components to the matrix components.
    // Store this as a sequence, so a single aggregate node represents this
    // entire operation.
    TIntermAggregate* result = intermediate.makeAggregate(vectorAssign);
    TType columnType(matrix->getType(), 0);
    TType componentType(columnType, 0);
    TType indexType(EbtInt);
    for (int i = 0; i < (int)swizzle.size(); i += 2) {
        // the right component, single index into the RHS vector
        TIntermTyped* rightComp = intermediate.addIndex(EOpIndexDirect, vector,
                                    intermediate.addConstantUnion(i/2, loc), loc);

        // the left component, double index into the LHS matrix
        TIntermTyped* leftComp = intermediate.addIndex(EOpIndexDirect, matrix,
                                    intermediate.addConstantUnion(swizzle[i]->getAsConstantUnion()->getConstArray(),
                                                                  indexType, loc),
                                    loc);
        leftComp->setType(columnType);
        leftComp = intermediate.addIndex(EOpIndexDirect, leftComp,
                                    intermediate.addConstantUnion(swizzle[i+1]->getAsConstantUnion()->getConstArray(),
                                                                  indexType, loc),
                                    loc);
        leftComp->setType(componentType);

        // Add the assignment to the aggregate
        result = intermediate.growAggregate(result, intermediate.addAssign(op, leftComp, rightComp, loc));
    }

    result->setOp(EOpSequence);

    return result;
}

//
// HLSL atomic operations have slightly different arguments than
// GLSL/AST/SPIRV.  The semantics are converted below in decomposeIntrinsic.
// This provides the post-decomposition equivalent opcode.
//
TOperator HlslParseContext::mapAtomicOp(const TSourceLoc& loc, TOperator op, bool isImage)
{
    switch (op) {
    case EOpInterlockedAdd:             return isImage ? EOpImageAtomicAdd      : EOpAtomicAdd;
    case EOpInterlockedAnd:             return isImage ? EOpImageAtomicAnd      : EOpAtomicAnd;
    case EOpInterlockedCompareExchange: return isImage ? EOpImageAtomicCompSwap : EOpAtomicCompSwap;
    case EOpInterlockedMax:             return isImage ? EOpImageAtomicMax      : EOpAtomicMax;
    case EOpInterlockedMin:             return isImage ? EOpImageAtomicMin      : EOpAtomicMin;
    case EOpInterlockedOr:              return isImage ? EOpImageAtomicOr       : EOpAtomicOr;
    case EOpInterlockedXor:             return isImage ? EOpImageAtomicXor      : EOpAtomicXor;
    case EOpInterlockedExchange:        return isImage ? EOpImageAtomicExchange : EOpAtomicExchange;
    case EOpInterlockedCompareStore:  // TODO: ...
    default:
        error(loc, "unknown atomic operation", "unknown op", "");
        return EOpNull;
    }
}

//
// Create a combined sampler/texture from separate sampler and texture.
//
TIntermAggregate* HlslParseContext::handleSamplerTextureCombine(const TSourceLoc& loc, TIntermTyped* argTex, TIntermTyped* argSampler)
{
    TIntermAggregate* txcombine = new TIntermAggregate(EOpConstructTextureSampler);

    txcombine->getSequence().push_back(argTex);
    txcombine->getSequence().push_back(argSampler);

    TSampler samplerType = argTex->getType().getSampler();
    samplerType.combined = true;
    samplerType.shadow   = argSampler->getType().getSampler().shadow;

    txcombine->setType(TType(samplerType, EvqTemporary));
    txcombine->setLoc(loc);

    return txcombine;
}

//
// Decompose DX9 and DX10 sample intrinsics & object methods into AST
//
void HlslParseContext::decomposeSampleMethods(const TSourceLoc& loc, TIntermTyped*& node, TIntermNode* arguments)
{
    if (!node || !node->getAsOperator())
        return;

    const auto clampReturn = [&loc, &node, this](TIntermTyped* result, const TSampler& sampler) -> TIntermTyped* {
        // Sampler return must always be a vec4, but we can construct a shorter vector
        result->setType(TType(node->getType().getBasicType(), EvqTemporary, node->getVectorSize()));

        if (sampler.vectorSize < (unsigned)node->getVectorSize()) {
            // Too many components.  Construct shorter vector from it.
            const TType clampedType(result->getType().getBasicType(), EvqTemporary, sampler.vectorSize);

            const TOperator op = intermediate.mapTypeToConstructorOp(clampedType);

            result = constructBuiltIn(clampedType, op, result, loc, false);
        }

        result->setLoc(loc);
        return result;
    };

    const TOperator op  = node->getAsOperator()->getOp();
    const TIntermAggregate* argAggregate = arguments ? arguments->getAsAggregate() : nullptr;

    switch (op) {
    // **** DX9 intrinsics: ****
    case EOpTexture:
        {
            // Texture with ddx & ddy is really gradient form in HLSL
            if (argAggregate->getSequence().size() == 4)
                node->getAsAggregate()->setOperator(EOpTextureGrad);

            break;
        }

    case EOpTextureBias:
        {
            TIntermTyped* arg0 = argAggregate->getSequence()[0]->getAsTyped();  // sampler
            TIntermTyped* arg1 = argAggregate->getSequence()[1]->getAsTyped();  // coord

            // HLSL puts bias in W component of coordinate.  We extract it and add it to
            // the argument list, instead
            TIntermTyped* w = intermediate.addConstantUnion(3, loc, true);
            TIntermTyped* bias = intermediate.addIndex(EOpIndexDirect, arg1, w, loc);

            TOperator constructOp = EOpNull;
            const TSampler& sampler = arg0->getType().getSampler();

            switch (sampler.dim) {
            case Esd1D:   constructOp = EOpConstructFloat; break; // 1D
            case Esd2D:   constructOp = EOpConstructVec2;  break; // 2D
            case Esd3D:   constructOp = EOpConstructVec3;  break; // 3D
            case EsdCube: constructOp = EOpConstructVec3;  break; // also 3D
            default: break;
            }

            TIntermAggregate* constructCoord = new TIntermAggregate(constructOp);
            constructCoord->getSequence().push_back(arg1);
            constructCoord->setLoc(loc);

            // The input vector should never be less than 2, since there's always a bias.
            // The max is for safety, and should be a no-op.
            constructCoord->setType(TType(arg1->getBasicType(), EvqTemporary, std::max(arg1->getVectorSize() - 1, 0)));

            TIntermAggregate* tex = new TIntermAggregate(EOpTexture);
            tex->getSequence().push_back(arg0);           // sampler
            tex->getSequence().push_back(constructCoord); // coordinate
            tex->getSequence().push_back(bias);           // bias

            node = clampReturn(tex, sampler);

            break;
        }

    // **** DX10 methods: ****
    case EOpMethodSample:     // fall through
    case EOpMethodSampleBias: // ...
        {
            TIntermTyped* argTex    = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* argSamp   = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* argCoord  = argAggregate->getSequence()[2]->getAsTyped();
            TIntermTyped* argBias   = nullptr;
            TIntermTyped* argOffset = nullptr;
            const TSampler& sampler = argTex->getType().getSampler();

            int nextArg = 3;

            if (op == EOpMethodSampleBias)  // SampleBias has a bias arg
                argBias = argAggregate->getSequence()[nextArg++]->getAsTyped();

            TOperator textureOp = EOpTexture;

            if ((int)argAggregate->getSequence().size() == (nextArg+1)) { // last parameter is offset form
                textureOp = EOpTextureOffset;
                argOffset = argAggregate->getSequence()[nextArg++]->getAsTyped();
            }

            TIntermAggregate* txcombine = handleSamplerTextureCombine(loc, argTex, argSamp);

            TIntermAggregate* txsample = new TIntermAggregate(textureOp);
            txsample->getSequence().push_back(txcombine);
            txsample->getSequence().push_back(argCoord);

            if (argBias != nullptr)
                txsample->getSequence().push_back(argBias);

            if (argOffset != nullptr)
                txsample->getSequence().push_back(argOffset);

            node = clampReturn(txsample, sampler);

            break;
        }

    case EOpMethodSampleGrad: // ...
        {
            TIntermTyped* argTex    = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* argSamp   = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* argCoord  = argAggregate->getSequence()[2]->getAsTyped();
            TIntermTyped* argDDX    = argAggregate->getSequence()[3]->getAsTyped();
            TIntermTyped* argDDY    = argAggregate->getSequence()[4]->getAsTyped();
            TIntermTyped* argOffset = nullptr;
            const TSampler& sampler = argTex->getType().getSampler();

            TOperator textureOp = EOpTextureGrad;

            if (argAggregate->getSequence().size() == 6) { // last parameter is offset form
                textureOp = EOpTextureGradOffset;
                argOffset = argAggregate->getSequence()[5]->getAsTyped();
            }

            TIntermAggregate* txcombine = handleSamplerTextureCombine(loc, argTex, argSamp);

            TIntermAggregate* txsample = new TIntermAggregate(textureOp);
            txsample->getSequence().push_back(txcombine);
            txsample->getSequence().push_back(argCoord);
            txsample->getSequence().push_back(argDDX);
            txsample->getSequence().push_back(argDDY);

            if (argOffset != nullptr)
                txsample->getSequence().push_back(argOffset);

            node = clampReturn(txsample, sampler);

            break;
        }

    case EOpMethodGetDimensions:
        {
            // AST returns a vector of results, which we break apart component-wise into
            // separate values to assign to the HLSL method's outputs, ala:
            //  tx . GetDimensions(width, height);
            //      float2 sizeQueryTemp = EOpTextureQuerySize
            //      width = sizeQueryTemp.X;
            //      height = sizeQueryTemp.Y;

            TIntermTyped* argTex = argAggregate->getSequence()[0]->getAsTyped();
            const TType& texType = argTex->getType();

            assert(texType.getBasicType() == EbtSampler);

            const TSampler& sampler = texType.getSampler();
            const TSamplerDim dim = sampler.dim;
            const bool isImage = sampler.isImage();
            const int numArgs = (int)argAggregate->getSequence().size();

            int numDims = 0;

            switch (dim) {
            case Esd1D:     numDims = 1; break; // W
            case Esd2D:     numDims = 2; break; // W, H
            case Esd3D:     numDims = 3; break; // W, H, D
            case EsdCube:   numDims = 2; break; // W, H (cube)
            case EsdBuffer: numDims = 1; break; // W (buffers)
            default:
                assert(0 && "unhandled texture dimension");
            }

            // Arrayed adds another dimension for the number of array elements
            if (sampler.isArrayed())
                ++numDims;

            // Establish whether we're querying mip levels
            const bool mipQuery = (numArgs > (numDims + 1)) && (!sampler.isMultiSample());

            // AST assumes integer return.  Will be converted to float if required.
            TIntermAggregate* sizeQuery = new TIntermAggregate(isImage ? EOpImageQuerySize : EOpTextureQuerySize);
            sizeQuery->getSequence().push_back(argTex);
            // If we're querying an explicit LOD, add the LOD, which is always arg #1
            if (mipQuery) {
                TIntermTyped* queryLod = argAggregate->getSequence()[1]->getAsTyped();
                sizeQuery->getSequence().push_back(queryLod);
            }
            sizeQuery->setType(TType(EbtUint, EvqTemporary, numDims));
            sizeQuery->setLoc(loc);

            // Return value from size query
            TVariable* tempArg = makeInternalVariable("sizeQueryTemp", sizeQuery->getType());
            tempArg->getWritableType().getQualifier().makeTemporary();
            TIntermTyped* sizeQueryAssign = intermediate.addAssign(EOpAssign,
                                                                   intermediate.addSymbol(*tempArg, loc),
                                                                   sizeQuery, loc);

            // Compound statement for assigning outputs
            TIntermAggregate* compoundStatement = intermediate.makeAggregate(sizeQueryAssign, loc);
            // Index of first output parameter
            const int outParamBase = mipQuery ? 2 : 1;

            for (int compNum = 0; compNum < numDims; ++compNum) {
                TIntermTyped* indexedOut = nullptr;
                TIntermSymbol* sizeQueryReturn = intermediate.addSymbol(*tempArg, loc);

                if (numDims > 1) {
                    TIntermTyped* component = intermediate.addConstantUnion(compNum, loc, true);
                    indexedOut = intermediate.addIndex(EOpIndexDirect, sizeQueryReturn, component, loc);
                    indexedOut->setType(TType(EbtUint, EvqTemporary, 1));
                    indexedOut->setLoc(loc);
                } else {
                    indexedOut = sizeQueryReturn;
                }

                TIntermTyped* outParam = argAggregate->getSequence()[outParamBase + compNum]->getAsTyped();
                TIntermTyped* compAssign = intermediate.addAssign(EOpAssign, outParam, indexedOut, loc);

                compoundStatement = intermediate.growAggregate(compoundStatement, compAssign);
            }

            // handle mip level parameter
            if (mipQuery) {
                TIntermTyped* outParam = argAggregate->getSequence()[outParamBase + numDims]->getAsTyped();

                TIntermAggregate* levelsQuery = new TIntermAggregate(EOpTextureQueryLevels);
                levelsQuery->getSequence().push_back(argTex);
                levelsQuery->setType(TType(EbtUint, EvqTemporary, 1));
                levelsQuery->setLoc(loc);

                TIntermTyped* compAssign = intermediate.addAssign(EOpAssign, outParam, levelsQuery, loc);
                compoundStatement = intermediate.growAggregate(compoundStatement, compAssign);
            }

            // 2DMS formats query # samples, which needs a different query op
            if (sampler.isMultiSample()) {
                TIntermTyped* outParam = argAggregate->getSequence()[outParamBase + numDims]->getAsTyped();

                TIntermAggregate* samplesQuery = new TIntermAggregate(EOpImageQuerySamples);
                samplesQuery->getSequence().push_back(argTex);
                samplesQuery->setType(TType(EbtUint, EvqTemporary, 1));
                samplesQuery->setLoc(loc);

                TIntermTyped* compAssign = intermediate.addAssign(EOpAssign, outParam, samplesQuery, loc);
                compoundStatement = intermediate.growAggregate(compoundStatement, compAssign);
            }

            compoundStatement->setOperator(EOpSequence);
            compoundStatement->setLoc(loc);
            compoundStatement->setType(TType(EbtVoid));

            node = compoundStatement;

            break;
        }

    case EOpMethodSampleCmp:  // fall through...
    case EOpMethodSampleCmpLevelZero:
        {
            TIntermTyped* argTex    = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* argSamp   = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* argCoord  = argAggregate->getSequence()[2]->getAsTyped();
            TIntermTyped* argCmpVal = argAggregate->getSequence()[3]->getAsTyped();
            TIntermTyped* argOffset = nullptr;

            // optional offset value
            if (argAggregate->getSequence().size() > 4)
                argOffset = argAggregate->getSequence()[4]->getAsTyped();

            const int coordDimWithCmpVal = argCoord->getType().getVectorSize() + 1; // +1 for cmp

            // AST wants comparison value as one of the texture coordinates
            TOperator constructOp = EOpNull;
            switch (coordDimWithCmpVal) {
            // 1D can't happen: there's always at least 1 coordinate dimension + 1 cmp val
            case 2: constructOp = EOpConstructVec2;  break;
            case 3: constructOp = EOpConstructVec3;  break;
            case 4: constructOp = EOpConstructVec4;  break;
            case 5: constructOp = EOpConstructVec4;  break; // cubeArrayShadow, cmp value is separate arg.
            default: assert(0); break;
            }

            TIntermAggregate* coordWithCmp = new TIntermAggregate(constructOp);
            coordWithCmp->getSequence().push_back(argCoord);
            if (coordDimWithCmpVal != 5) // cube array shadow is special.
                coordWithCmp->getSequence().push_back(argCmpVal);
            coordWithCmp->setLoc(loc);
            coordWithCmp->setType(TType(argCoord->getBasicType(), EvqTemporary, std::min(coordDimWithCmpVal, 4)));

            TOperator textureOp = (op == EOpMethodSampleCmpLevelZero ? EOpTextureLod : EOpTexture);
            if (argOffset != nullptr)
                textureOp = (op == EOpMethodSampleCmpLevelZero ? EOpTextureLodOffset : EOpTextureOffset);

            // Create combined sampler & texture op
            TIntermAggregate* txcombine = handleSamplerTextureCombine(loc, argTex, argSamp);
            TIntermAggregate* txsample = new TIntermAggregate(textureOp);
            txsample->getSequence().push_back(txcombine);
            txsample->getSequence().push_back(coordWithCmp);

            if (coordDimWithCmpVal == 5) // cube array shadow is special: cmp val follows coord.
                txsample->getSequence().push_back(argCmpVal);

            // the LevelZero form uses 0 as an explicit LOD
            if (op == EOpMethodSampleCmpLevelZero)
                txsample->getSequence().push_back(intermediate.addConstantUnion(0.0, EbtFloat, loc, true));

            // Add offset if present
            if (argOffset != nullptr)
                txsample->getSequence().push_back(argOffset);

            txsample->setType(node->getType());
            txsample->setLoc(loc);
            node = txsample;

            break;
        }

    case EOpMethodLoad:
        {
            TIntermTyped* argTex    = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* argCoord  = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* argOffset = nullptr;
            TIntermTyped* lodComponent = nullptr;
            TIntermTyped* coordSwizzle = nullptr;

            const TSampler& sampler = argTex->getType().getSampler();
            const bool isMS = sampler.isMultiSample();
            const bool isBuffer = sampler.dim == EsdBuffer;
            const bool isImage = sampler.isImage();
            const TBasicType coordBaseType = argCoord->getType().getBasicType();

            // Last component of coordinate is the mip level, for non-MS.  we separate them here:
            if (isMS || isBuffer || isImage) {
                // MS, Buffer, and Image have no LOD
                coordSwizzle = argCoord;
            } else {
                // Extract coordinate
                int swizzleSize = argCoord->getType().getVectorSize() - (isMS ? 0 : 1);
                TSwizzleSelectors<TVectorSelector> coordFields;
                for (int i = 0; i < swizzleSize; ++i)
                    coordFields.push_back(i);
                TIntermTyped* coordIdx = intermediate.addSwizzle(coordFields, loc);
                coordSwizzle = intermediate.addIndex(EOpVectorSwizzle, argCoord, coordIdx, loc);
                coordSwizzle->setType(TType(coordBaseType, EvqTemporary, coordFields.size()));

                // Extract LOD
                TIntermTyped* lodIdx = intermediate.addConstantUnion(coordFields.size(), loc, true);
                lodComponent = intermediate.addIndex(EOpIndexDirect, argCoord, lodIdx, loc);
                lodComponent->setType(TType(coordBaseType, EvqTemporary, 1));
            }

            const int numArgs    = (int)argAggregate->getSequence().size();
            const bool hasOffset = ((!isMS && numArgs == 3) || (isMS && numArgs == 4));

            // Create texel fetch
            const TOperator fetchOp = (isImage   ? EOpImageLoad :
                                       hasOffset ? EOpTextureFetchOffset :
                                       EOpTextureFetch);
            TIntermAggregate* txfetch = new TIntermAggregate(fetchOp);

            // Build up the fetch
            txfetch->getSequence().push_back(argTex);
            txfetch->getSequence().push_back(coordSwizzle);

            if (isMS) {
                // add 2DMS sample index
                TIntermTyped* argSampleIdx  = argAggregate->getSequence()[2]->getAsTyped();
                txfetch->getSequence().push_back(argSampleIdx);
            } else if (isBuffer) {
                // Nothing else to do for buffers.
            } else if (isImage) {
                // Nothing else to do for images.
            } else {
                // 2DMS and buffer have no LOD, but everything else does.
                txfetch->getSequence().push_back(lodComponent);
            }

            // Obtain offset arg, if there is one.
            if (hasOffset) {
                const int offsetPos  = (isMS ? 3 : 2);
                argOffset = argAggregate->getSequence()[offsetPos]->getAsTyped();
                txfetch->getSequence().push_back(argOffset);
            }

            node = clampReturn(txfetch, sampler);

            break;
        }

    case EOpMethodSampleLevel:
        {
            TIntermTyped* argTex    = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* argSamp   = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* argCoord  = argAggregate->getSequence()[2]->getAsTyped();
            TIntermTyped* argLod    = argAggregate->getSequence()[3]->getAsTyped();
            TIntermTyped* argOffset = nullptr;
            const TSampler& sampler = argTex->getType().getSampler();

            const int  numArgs = (int)argAggregate->getSequence().size();

            if (numArgs == 5) // offset, if present
                argOffset = argAggregate->getSequence()[4]->getAsTyped();

            const TOperator textureOp = (argOffset == nullptr ? EOpTextureLod : EOpTextureLodOffset);
            TIntermAggregate* txsample = new TIntermAggregate(textureOp);

            TIntermAggregate* txcombine = handleSamplerTextureCombine(loc, argTex, argSamp);

            txsample->getSequence().push_back(txcombine);
            txsample->getSequence().push_back(argCoord);
            txsample->getSequence().push_back(argLod);

            if (argOffset != nullptr)
                txsample->getSequence().push_back(argOffset);

            node = clampReturn(txsample, sampler);

            break;
        }

    case EOpMethodGather:
        {
            TIntermTyped* argTex    = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* argSamp   = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* argCoord  = argAggregate->getSequence()[2]->getAsTyped();
            TIntermTyped* argOffset = nullptr;

            // Offset is optional
            if (argAggregate->getSequence().size() > 3)
                argOffset = argAggregate->getSequence()[3]->getAsTyped();

            const TOperator textureOp = (argOffset == nullptr ? EOpTextureGather : EOpTextureGatherOffset);
            TIntermAggregate* txgather = new TIntermAggregate(textureOp);

            TIntermAggregate* txcombine = handleSamplerTextureCombine(loc, argTex, argSamp);

            txgather->getSequence().push_back(txcombine);
            txgather->getSequence().push_back(argCoord);
            // Offset if not given is implicitly channel 0 (red)

            if (argOffset != nullptr)
                txgather->getSequence().push_back(argOffset);

            txgather->setType(node->getType());
            txgather->setLoc(loc);
            node = txgather;

            break;
        }

    case EOpMethodGatherRed:      // fall through...
    case EOpMethodGatherGreen:    // ...
    case EOpMethodGatherBlue:     // ...
    case EOpMethodGatherAlpha:    // ...
    case EOpMethodGatherCmpRed:   // ...
    case EOpMethodGatherCmpGreen: // ...
    case EOpMethodGatherCmpBlue:  // ...
    case EOpMethodGatherCmpAlpha: // ...
        {
            int channel = 0;    // the channel we are gathering
            int cmpValues = 0;  // 1 if there is a compare value (handier than a bool below)

            switch (op) {
            case EOpMethodGatherCmpRed:   cmpValues = 1;  // fall through
            case EOpMethodGatherRed:      channel = 0; break;
            case EOpMethodGatherCmpGreen: cmpValues = 1;  // fall through
            case EOpMethodGatherGreen:    channel = 1; break;
            case EOpMethodGatherCmpBlue:  cmpValues = 1;  // fall through
            case EOpMethodGatherBlue:     channel = 2; break;
            case EOpMethodGatherCmpAlpha: cmpValues = 1;  // fall through
            case EOpMethodGatherAlpha:    channel = 3; break;
            default:                      assert(0);   break;
            }

            // For now, we have nothing to map the component-wise comparison forms
            // to, because neither GLSL nor SPIR-V has such an opcode.  Issue an
            // unimplemented error instead.  Most of the machinery is here if that
            // should ever become available.
            if (cmpValues) {
                error(loc, "unimplemented: component-level gather compare", "", "");
                return;
            }

            int arg = 0;

            TIntermTyped* argTex        = argAggregate->getSequence()[arg++]->getAsTyped();
            TIntermTyped* argSamp       = argAggregate->getSequence()[arg++]->getAsTyped();
            TIntermTyped* argCoord      = argAggregate->getSequence()[arg++]->getAsTyped();
            TIntermTyped* argOffset     = nullptr;
            TIntermTyped* argOffsets[4] = { nullptr, nullptr, nullptr, nullptr };
            // TIntermTyped* argStatus     = nullptr; // TODO: residency
            TIntermTyped* argCmp        = nullptr;

            const TSamplerDim dim = argTex->getType().getSampler().dim;

            const int  argSize = (int)argAggregate->getSequence().size();
            bool hasStatus     = (argSize == (5+cmpValues) || argSize == (8+cmpValues));
            bool hasOffset1    = false;
            bool hasOffset4    = false;

            // Only 2D forms can have offsets.  Discover if we have 0, 1 or 4 offsets.
            if (dim == Esd2D) {
                hasOffset1 = (argSize == (4+cmpValues) || argSize == (5+cmpValues));
                hasOffset4 = (argSize == (7+cmpValues) || argSize == (8+cmpValues));
            }

            assert(!(hasOffset1 && hasOffset4));

            TOperator textureOp = EOpTextureGather;

            // Compare forms have compare value
            if (cmpValues != 0)
                argCmp = argOffset = argAggregate->getSequence()[arg++]->getAsTyped();

            // Some forms have single offset
            if (hasOffset1) {
                textureOp = EOpTextureGatherOffset;   // single offset form
                argOffset = argAggregate->getSequence()[arg++]->getAsTyped();
            }

            // Some forms have 4 gather offsets
            if (hasOffset4) {
                textureOp = EOpTextureGatherOffsets;  // note plural, for 4 offset form
                for (int offsetNum = 0; offsetNum < 4; ++offsetNum)
                    argOffsets[offsetNum] = argAggregate->getSequence()[arg++]->getAsTyped();
            }

            // Residency status
            if (hasStatus) {
                // argStatus = argAggregate->getSequence()[arg++]->getAsTyped();
                error(loc, "unimplemented: residency status", "", "");
                return;
            }

            TIntermAggregate* txgather = new TIntermAggregate(textureOp);
            TIntermAggregate* txcombine = handleSamplerTextureCombine(loc, argTex, argSamp);

            TIntermTyped* argChannel = intermediate.addConstantUnion(channel, loc, true);

            txgather->getSequence().push_back(txcombine);
            txgather->getSequence().push_back(argCoord);

            // AST wants an array of 4 offsets, where HLSL has separate args.  Here
            // we construct an array from the separate args.
            if (hasOffset4) {
                TType arrayType(EbtInt, EvqTemporary, 2);
                TArraySizes arraySizes;
                arraySizes.addInnerSize(4);
                arrayType.newArraySizes(arraySizes);

                TIntermAggregate* initList = new TIntermAggregate(EOpNull);

                for (int offsetNum = 0; offsetNum < 4; ++offsetNum)
                    initList->getSequence().push_back(argOffsets[offsetNum]);

                argOffset = addConstructor(loc, initList, arrayType);
            }

            // Add comparison value if we have one
            if (argTex->getType().getSampler().isShadow())
                txgather->getSequence().push_back(argCmp);

            // Add offset (either 1, or an array of 4) if we have one
            if (argOffset != nullptr)
                txgather->getSequence().push_back(argOffset);

            txgather->getSequence().push_back(argChannel);

            txgather->setType(node->getType());
            txgather->setLoc(loc);
            node = txgather;

            break;
        }

    case EOpMethodCalculateLevelOfDetail:
    case EOpMethodCalculateLevelOfDetailUnclamped:
        {
            TIntermTyped* argTex    = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* argSamp   = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* argCoord  = argAggregate->getSequence()[2]->getAsTyped();

            TIntermAggregate* txquerylod = new TIntermAggregate(EOpTextureQueryLod);

            TIntermAggregate* txcombine = handleSamplerTextureCombine(loc, argTex, argSamp);
            txquerylod->getSequence().push_back(txcombine);
            txquerylod->getSequence().push_back(argCoord);

            TIntermTyped* lodComponent = intermediate.addConstantUnion(0, loc, true);
            TIntermTyped* lodComponentIdx = intermediate.addIndex(EOpIndexDirect, txquerylod, lodComponent, loc);
            lodComponentIdx->setType(TType(EbtFloat, EvqTemporary, 1));

            node = lodComponentIdx;

            // We cannot currently obtain the unclamped LOD
            if (op == EOpMethodCalculateLevelOfDetailUnclamped)
                error(loc, "unimplemented: CalculateLevelOfDetailUnclamped", "", "");

            break;
        }

    case EOpMethodGetSamplePosition:
        {
            error(loc, "unimplemented: GetSamplePosition", "", "");
            break;
        }

    default:
        break; // most pass through unchanged
    }
}

//
// Decompose geometry shader methods
//
void HlslParseContext::decomposeGeometryMethods(const TSourceLoc& loc, TIntermTyped*& node, TIntermNode* arguments)
{
    if (!node || !node->getAsOperator())
        return;

    const TOperator op  = node->getAsOperator()->getOp();
    const TIntermAggregate* argAggregate = arguments ? arguments->getAsAggregate() : nullptr;

    switch (op) {
    case EOpMethodAppend:
        if (argAggregate) {
            TIntermAggregate* sequence = nullptr;
            TIntermAggregate* emit = new TIntermAggregate(EOpEmitVertex);

            emit->setLoc(loc);
            emit->setType(TType(EbtVoid));

            sequence = intermediate.growAggregate(sequence,
                                                  handleAssign(loc, EOpAssign,
                                                               argAggregate->getSequence()[0]->getAsTyped(),
                                                               argAggregate->getSequence()[1]->getAsTyped()),
                                                  loc);

            sequence = intermediate.growAggregate(sequence, emit);

            sequence->setOperator(EOpSequence);
            sequence->setLoc(loc);
            sequence->setType(TType(EbtVoid));
            node = sequence;
        }
        break;

    case EOpMethodRestartStrip:
        {
            TIntermAggregate* cut = new TIntermAggregate(EOpEndPrimitive);
            cut->setLoc(loc);
            cut->setType(TType(EbtVoid));
            node = cut;
        }
        break;

    default:
        break; // most pass through unchanged
    }
}

//
// Optionally decompose intrinsics to AST opcodes.
//
void HlslParseContext::decomposeIntrinsic(const TSourceLoc& loc, TIntermTyped*& node, TIntermNode* arguments)
{
    // Helper to find image data for image atomics:
    // OpImageLoad(image[idx])
    // We take the image load apart and add its params to the atomic op aggregate node
    const auto imageAtomicParams = [this, &loc, &node](TIntermAggregate* atomic, TIntermTyped* load) {
        TIntermAggregate* loadOp = load->getAsAggregate();
        if (loadOp == nullptr) {
            error(loc, "unknown image type in atomic operation", "", "");
            node = nullptr;
            return;
        }

        atomic->getSequence().push_back(loadOp->getSequence()[0]);
        atomic->getSequence().push_back(loadOp->getSequence()[1]);
    };

    // Return true if this is an imageLoad, which we will change to an image atomic.
    const auto isImageParam = [](TIntermTyped* image) -> bool {
        TIntermAggregate* imageAggregate = image->getAsAggregate();
        return imageAggregate != nullptr && imageAggregate->getOp() == EOpImageLoad;
    };

    // HLSL intrinsics can be pass through to native AST opcodes, or decomposed here to existing AST
    // opcodes for compatibility with existing software stacks.
    static const bool decomposeHlslIntrinsics = true;

    if (!decomposeHlslIntrinsics || !node || !node->getAsOperator())
        return;

    const TIntermAggregate* argAggregate = arguments ? arguments->getAsAggregate() : nullptr;
    TIntermUnary* fnUnary = node->getAsUnaryNode();
    const TOperator op  = node->getAsOperator()->getOp();

    switch (op) {
    case EOpGenMul:
        {
            // mul(a,b) -> MatrixTimesMatrix, MatrixTimesVector, MatrixTimesScalar, VectorTimesScalar, Dot, Mul
            // Since we are treating HLSL rows like GLSL columns (the first matrix indirection),
            // we must reverse the operand order here.  Hence, arg0 gets sequence[1], etc.
            TIntermTyped* arg0 = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* arg1 = argAggregate->getSequence()[0]->getAsTyped();

            if (arg0->isVector() && arg1->isVector()) {  // vec * vec
                node->getAsAggregate()->setOperator(EOpDot);
            } else {
                node = handleBinaryMath(loc, "mul", EOpMul, arg0, arg1);
            }

            break;
        }

    case EOpRcp:
        {
            // rcp(a) -> 1 / a
            TIntermTyped* arg0 = fnUnary->getOperand();
            TBasicType   type0 = arg0->getBasicType();
            TIntermTyped* one  = intermediate.addConstantUnion(1, type0, loc, true);
            node  = handleBinaryMath(loc, "rcp", EOpDiv, one, arg0);

            break;
        }

    case EOpSaturate:
        {
            // saturate(a) -> clamp(a,0,1)
            TIntermTyped* arg0 = fnUnary->getOperand();
            TBasicType   type0 = arg0->getBasicType();
            TIntermAggregate* clamp = new TIntermAggregate(EOpClamp);

            clamp->getSequence().push_back(arg0);
            clamp->getSequence().push_back(intermediate.addConstantUnion(0, type0, loc, true));
            clamp->getSequence().push_back(intermediate.addConstantUnion(1, type0, loc, true));
            clamp->setLoc(loc);
            clamp->setType(node->getType());
            clamp->getWritableType().getQualifier().makeTemporary();
            node = clamp;

            break;
        }

    case EOpSinCos:
        {
            // sincos(a,b,c) -> b = sin(a), c = cos(a)
            TIntermTyped* arg0 = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* arg1 = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* arg2 = argAggregate->getSequence()[2]->getAsTyped();

            TIntermTyped* sinStatement = handleUnaryMath(loc, "sin", EOpSin, arg0);
            TIntermTyped* cosStatement = handleUnaryMath(loc, "cos", EOpCos, arg0);
            TIntermTyped* sinAssign    = intermediate.addAssign(EOpAssign, arg1, sinStatement, loc);
            TIntermTyped* cosAssign    = intermediate.addAssign(EOpAssign, arg2, cosStatement, loc);

            TIntermAggregate* compoundStatement = intermediate.makeAggregate(sinAssign, loc);
            compoundStatement = intermediate.growAggregate(compoundStatement, cosAssign);
            compoundStatement->setOperator(EOpSequence);
            compoundStatement->setLoc(loc);
            compoundStatement->setType(TType(EbtVoid));

            node = compoundStatement;

            break;
        }

    case EOpClip:
        {
            // clip(a) -> if (any(a<0)) discard;
            TIntermTyped*  arg0 = fnUnary->getOperand();
            TBasicType     type0 = arg0->getBasicType();
            TIntermTyped*  compareNode = nullptr;

            // For non-scalars: per experiment with FXC compiler, discard if any component < 0.
            if (!arg0->isScalar()) {
                // component-wise compare: a < 0
                TIntermAggregate* less = new TIntermAggregate(EOpLessThan);
                less->getSequence().push_back(arg0);
                less->setLoc(loc);

                // make vec or mat of bool matching dimensions of input
                less->setType(TType(EbtBool, EvqTemporary,
                                    arg0->getType().getVectorSize(),
                                    arg0->getType().getMatrixCols(),
                                    arg0->getType().getMatrixRows(),
                                    arg0->getType().isVector()));

                // calculate # of components for comparison const
                const int constComponentCount =
                    std::max(arg0->getType().getVectorSize(), 1) *
                    std::max(arg0->getType().getMatrixCols(), 1) *
                    std::max(arg0->getType().getMatrixRows(), 1);

                TConstUnion zero;
                zero.setDConst(0.0);
                TConstUnionArray zeros(constComponentCount, zero);

                less->getSequence().push_back(intermediate.addConstantUnion(zeros, arg0->getType(), loc, true));

                compareNode = intermediate.addBuiltInFunctionCall(loc, EOpAny, true, less, TType(EbtBool));
            } else {
                TIntermTyped* zero = intermediate.addConstantUnion(0, type0, loc, true);
                compareNode = handleBinaryMath(loc, "clip", EOpLessThan, arg0, zero);
            }

            TIntermBranch* killNode = intermediate.addBranch(EOpKill, loc);

            node = new TIntermSelection(compareNode, killNode, nullptr);
            node->setLoc(loc);

            break;
        }

    case EOpLog10:
        {
            // log10(a) -> log2(a) * 0.301029995663981  (== 1/log2(10))
            TIntermTyped* arg0 = fnUnary->getOperand();
            TIntermTyped* log2 = handleUnaryMath(loc, "log2", EOpLog2, arg0);
            TIntermTyped* base = intermediate.addConstantUnion(0.301029995663981f, EbtFloat, loc, true);

            node  = handleBinaryMath(loc, "mul", EOpMul, log2, base);

            break;
        }

    case EOpDst:
        {
            // dest.x = 1;
            // dest.y = src0.y * src1.y;
            // dest.z = src0.z;
            // dest.w = src1.w;

            TIntermTyped* arg0 = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* arg1 = argAggregate->getSequence()[1]->getAsTyped();

            TIntermTyped* y = intermediate.addConstantUnion(1, loc, true);
            TIntermTyped* z = intermediate.addConstantUnion(2, loc, true);
            TIntermTyped* w = intermediate.addConstantUnion(3, loc, true);

            TIntermTyped* src0y = intermediate.addIndex(EOpIndexDirect, arg0, y, loc);
            TIntermTyped* src1y = intermediate.addIndex(EOpIndexDirect, arg1, y, loc);
            TIntermTyped* src0z = intermediate.addIndex(EOpIndexDirect, arg0, z, loc);
            TIntermTyped* src1w = intermediate.addIndex(EOpIndexDirect, arg1, w, loc);

            TIntermAggregate* dst = new TIntermAggregate(EOpConstructVec4);

            dst->getSequence().push_back(intermediate.addConstantUnion(1.0, EbtFloat, loc, true));
            dst->getSequence().push_back(handleBinaryMath(loc, "mul", EOpMul, src0y, src1y));
            dst->getSequence().push_back(src0z);
            dst->getSequence().push_back(src1w);
            dst->setType(TType(EbtFloat, EvqTemporary, 4));
            dst->setLoc(loc);
            node = dst;

            break;
        }

    case EOpInterlockedAdd: // optional last argument (if present) is assigned from return value
    case EOpInterlockedMin: // ...
    case EOpInterlockedMax: // ...
    case EOpInterlockedAnd: // ...
    case EOpInterlockedOr:  // ...
    case EOpInterlockedXor: // ...
    case EOpInterlockedExchange: // always has output arg
        {
            TIntermTyped* arg0 = argAggregate->getSequence()[0]->getAsTyped();  // dest
            TIntermTyped* arg1 = argAggregate->getSequence()[1]->getAsTyped();  // value
            TIntermTyped* arg2 = nullptr;

            if (argAggregate->getSequence().size() > 2)
                arg2 = argAggregate->getSequence()[2]->getAsTyped();

            const bool isImage = isImageParam(arg0);
            const TOperator atomicOp = mapAtomicOp(loc, op, isImage);
            TIntermAggregate* atomic = new TIntermAggregate(atomicOp);
            atomic->setType(arg0->getType());
            atomic->getWritableType().getQualifier().makeTemporary();
            atomic->setLoc(loc);

            if (isImage) {
                // orig_value = imageAtomicOp(image, loc, data)
                imageAtomicParams(atomic, arg0);
                atomic->getSequence().push_back(arg1);

                if (argAggregate->getSequence().size() > 2) {
                    node = intermediate.addAssign(EOpAssign, arg2, atomic, loc);
                } else {
                    node = atomic; // no assignment needed, as there was no out var.
                }
            } else {
                // Normal memory variable:
                // arg0 = mem, arg1 = data, arg2(optional,out) = orig_value
                if (argAggregate->getSequence().size() > 2) {
                    // optional output param is present.  return value goes to arg2.
                    atomic->getSequence().push_back(arg0);
                    atomic->getSequence().push_back(arg1);

                    node = intermediate.addAssign(EOpAssign, arg2, atomic, loc);
                } else {
                    // Set the matching operator.  Since output is absent, this is all we need to do.
                    node->getAsAggregate()->setOperator(atomicOp);
                }
            }

            break;
        }

    case EOpInterlockedCompareExchange:
        {
            TIntermTyped* arg0 = argAggregate->getSequence()[0]->getAsTyped();  // dest
            TIntermTyped* arg1 = argAggregate->getSequence()[1]->getAsTyped();  // cmp
            TIntermTyped* arg2 = argAggregate->getSequence()[2]->getAsTyped();  // value
            TIntermTyped* arg3 = argAggregate->getSequence()[3]->getAsTyped();  // orig

            const bool isImage = isImageParam(arg0);
            TIntermAggregate* atomic = new TIntermAggregate(mapAtomicOp(loc, op, isImage));
            atomic->setLoc(loc);
            atomic->setType(arg2->getType());
            atomic->getWritableType().getQualifier().makeTemporary();

            if (isImage) {
                imageAtomicParams(atomic, arg0);
            } else {
                atomic->getSequence().push_back(arg0);
            }

            atomic->getSequence().push_back(arg1);
            atomic->getSequence().push_back(arg2);
            node = intermediate.addAssign(EOpAssign, arg3, atomic, loc);

            break;
        }

    case EOpEvaluateAttributeSnapped:
        {
            // SPIR-V InterpolateAtOffset uses float vec2 offset in pixels
            // HLSL uses int2 offset on a 16x16 grid in [-8..7] on x & y:
            //   iU = (iU<<28)>>28
            //   fU = ((float)iU)/16
            // Targets might handle this natively, in which case they can disable
            // decompositions.

            TIntermTyped* arg0 = argAggregate->getSequence()[0]->getAsTyped();  // value
            TIntermTyped* arg1 = argAggregate->getSequence()[1]->getAsTyped();  // offset

            TIntermTyped* i28 = intermediate.addConstantUnion(28, loc, true);
            TIntermTyped* iU = handleBinaryMath(loc, ">>", EOpRightShift,
                                                handleBinaryMath(loc, "<<", EOpLeftShift, arg1, i28),
                                                i28);

            TIntermTyped* recip16 = intermediate.addConstantUnion((1.0/16.0), EbtFloat, loc, true);
            TIntermTyped* floatOffset = handleBinaryMath(loc, "mul", EOpMul,
                                                         intermediate.addConversion(EOpConstructFloat,
                                                                                    TType(EbtFloat, EvqTemporary, 2), iU),
                                                         recip16);

            TIntermAggregate* interp = new TIntermAggregate(EOpInterpolateAtOffset);
            interp->getSequence().push_back(arg0);
            interp->getSequence().push_back(floatOffset);
            interp->setLoc(loc);
            interp->setType(arg0->getType());
            interp->getWritableType().getQualifier().makeTemporary();

            node = interp;

            break;
        }

    case EOpLit:
        {
            TIntermTyped* n_dot_l = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* n_dot_h = argAggregate->getSequence()[1]->getAsTyped();
            TIntermTyped* m = argAggregate->getSequence()[2]->getAsTyped();

            TIntermAggregate* dst = new TIntermAggregate(EOpConstructVec4);

            // Ambient
            dst->getSequence().push_back(intermediate.addConstantUnion(1.0, EbtFloat, loc, true));

            // Diffuse:
            TIntermTyped* zero = intermediate.addConstantUnion(0.0, EbtFloat, loc, true);
            TIntermAggregate* diffuse = new TIntermAggregate(EOpMax);
            diffuse->getSequence().push_back(n_dot_l);
            diffuse->getSequence().push_back(zero);
            diffuse->setLoc(loc);
            diffuse->setType(TType(EbtFloat));
            dst->getSequence().push_back(diffuse);

            // Specular:
            TIntermAggregate* min_ndot = new TIntermAggregate(EOpMin);
            min_ndot->getSequence().push_back(n_dot_l);
            min_ndot->getSequence().push_back(n_dot_h);
            min_ndot->setLoc(loc);
            min_ndot->setType(TType(EbtFloat));

            TIntermTyped* compare = handleBinaryMath(loc, "<", EOpLessThan, min_ndot, zero);
            TIntermTyped* n_dot_h_m = handleBinaryMath(loc, "mul", EOpMul, n_dot_h, m);  // n_dot_h * m

            dst->getSequence().push_back(intermediate.addSelection(compare, zero, n_dot_h_m, loc));

            // One:
            dst->getSequence().push_back(intermediate.addConstantUnion(1.0, EbtFloat, loc, true));

            dst->setLoc(loc);
            dst->setType(TType(EbtFloat, EvqTemporary, 4));
            node = dst;
            break;
        }

    case EOpAsDouble:
        {
            // asdouble accepts two 32 bit ints.  we can use EOpUint64BitsToDouble, but must
            // first construct a uint64.
            TIntermTyped* arg0 = argAggregate->getSequence()[0]->getAsTyped();
            TIntermTyped* arg1 = argAggregate->getSequence()[1]->getAsTyped();

            if (arg0->getType().isVector()) { // TODO: ...
                error(loc, "double2 conversion not implemented", "asdouble", "");
                break;
            }

            TIntermAggregate* uint64 = new TIntermAggregate(EOpConstructUVec2);

            uint64->getSequence().push_back(arg0);
            uint64->getSequence().push_back(arg1);
            uint64->setType(TType(EbtUint, EvqTemporary, 2));  // convert 2 uints to a uint2
            uint64->setLoc(loc);

            // bitcast uint2 to a double
            TIntermTyped* convert = new TIntermUnary(EOpUint64BitsToDouble);
            convert->getAsUnaryNode()->setOperand(uint64);
            convert->setLoc(loc);
            convert->setType(TType(EbtDouble, EvqTemporary));
            node = convert;

            break;
        }

    case EOpF16tof32:
    case EOpF32tof16:
        {
            // Temporary until decomposition is available.
            error(loc, "unimplemented intrinsic: handle natively", "f32tof16", "");
            break;
        }

    case EOpD3DCOLORtoUBYTE4:
        {
            // ivec4 ( x.zyxw * 255.001953 );
            TIntermTyped* arg0 = node->getAsUnaryNode()->getOperand();
            TSwizzleSelectors<TVectorSelector> selectors;
            selectors.push_back(2);
            selectors.push_back(1);
            selectors.push_back(0);
            selectors.push_back(3);
            TIntermTyped* swizzleIdx = intermediate.addSwizzle(selectors, loc);
            TIntermTyped* swizzled = intermediate.addIndex(EOpVectorSwizzle, arg0, swizzleIdx, loc);
            swizzled->setType(arg0->getType());
            swizzled->getWritableType().getQualifier().makeTemporary();

            TIntermTyped* conversion = intermediate.addConstantUnion(255.001953f, EbtFloat, loc, true);
            TIntermTyped* rangeConverted = handleBinaryMath(loc, "mul", EOpMul, conversion, swizzled);
            rangeConverted->setType(arg0->getType());
            rangeConverted->getWritableType().getQualifier().makeTemporary();

            node = intermediate.addConversion(EOpConstructInt, TType(EbtInt, EvqTemporary, 4), rangeConverted);
            node->setLoc(loc);
            node->setType(TType(EbtInt, EvqTemporary, 4));
            break;
        }

    default:
        break; // most pass through unchanged
    }
}

//
// Handle seeing function call syntax in the grammar, which could be any of
//  - .length() method
//  - constructor
//  - a call to a built-in function mapped to an operator
//  - a call to a built-in function that will remain a function call (e.g., texturing)
//  - user function
//  - subroutine call (not implemented yet)
//
TIntermTyped* HlslParseContext::handleFunctionCall(const TSourceLoc& loc, TFunction* function, TIntermTyped* arguments)
{
    TIntermTyped* result = nullptr;

    TOperator op = function->getBuiltInOp();
    if (op == EOpArrayLength)
        result = handleLengthMethod(loc, function, arguments);
    else if (op != EOpNull) {
        //
        // Then this should be a constructor.
        // Don't go through the symbol table for constructors.
        // Their parameters will be verified algorithmically.
        //
        TType type(EbtVoid);  // use this to get the type back
        if (! constructorError(loc, arguments, *function, op, type)) {
            //
            // It's a constructor, of type 'type'.
            //
            result = addConstructor(loc, arguments, type);
            if (result == nullptr)
                error(loc, "cannot construct with these arguments", type.getCompleteString().c_str(), "");
        }
    } else {
        //
        // Find it in the symbol table.
        //
        const TFunction* fnCandidate;
        bool builtIn;
        fnCandidate = findFunction(loc, *function, builtIn, arguments);
        if (fnCandidate) {
            // This is a declared function that might map to
            //  - a built-in operator,
            //  - a built-in function not mapped to an operator, or
            //  - a user function.

            // Error check for a function requiring specific extensions present.
            if (builtIn && fnCandidate->getNumExtensions())
                requireExtensions(loc, fnCandidate->getNumExtensions(), fnCandidate->getExtensions(), fnCandidate->getName().c_str());

            // Convert 'in' arguments
            if (arguments)
                addInputArgumentConversions(*fnCandidate, arguments);

            op = fnCandidate->getBuiltInOp();
            if (builtIn && op != EOpNull) {
                // A function call mapped to a built-in operation.
                result = intermediate.addBuiltInFunctionCall(loc, op, fnCandidate->getParamCount() == 1, arguments, fnCandidate->getType());
                if (result == nullptr)  {
                    error(arguments->getLoc(), " wrong operand type", "Internal Error",
                        "built in unary operator function.  Type: %s",
                        static_cast<TIntermTyped*>(arguments)->getCompleteString().c_str());
                } else if (result->getAsOperator()) {
                    builtInOpCheck(loc, *fnCandidate, *result->getAsOperator());
                }
            } else {
                // This is a function call not mapped to built-in operator.
                // It could still be a built-in function, but only if PureOperatorBuiltins == false.
                result = intermediate.setAggregateOperator(arguments, EOpFunctionCall, fnCandidate->getType(), loc);
                TIntermAggregate* call = result->getAsAggregate();
                call->setName(fnCandidate->getMangledName());

                // this is how we know whether the given function is a built-in function or a user-defined function
                // if builtIn == false, it's a userDefined -> could be an overloaded built-in function also
                // if builtIn == true, it's definitely a built-in function with EOpNull
                if (! builtIn) {
                    call->setUserDefined();
                    intermediate.addToCallGraph(infoSink, currentCaller, fnCandidate->getMangledName());
                }
            }

            // for decompositions, since we want to operate on the function node, not the aggregate holding
            // output conversions.
            const TIntermTyped* fnNode = result;

            decomposeIntrinsic(loc, result, arguments);       // HLSL->AST intrinsic decompositions
            decomposeSampleMethods(loc, result, arguments);   // HLSL->AST sample method decompositions
            decomposeGeometryMethods(loc, result, arguments); // HLSL->AST geometry method decompositions

            // Convert 'out' arguments.  If it was a constant folded built-in, it won't be an aggregate anymore.
            // Built-ins with a single argument aren't called with an aggregate, but they also don't have an output.
            // Also, build the qualifier list for user function calls, which are always called with an aggregate.
            // We don't do this is if there has been a decomposition, which will have added its own conversions
            // for output parameters.
            if (result == fnNode && result->getAsAggregate()) {
                TQualifierList& qualifierList = result->getAsAggregate()->getQualifierList();
                for (int i = 0; i < fnCandidate->getParamCount(); ++i) {
                    TStorageQualifier qual = (*fnCandidate)[i].type->getQualifier().storage;
                    qualifierList.push_back(qual);
                }
                result = addOutputArgumentConversions(*fnCandidate, *result->getAsOperator());
            }
        }
    }

    // generic error recovery
    // TODO: simplification: localize all the error recoveries that look like this, and taking type into account to reduce cascades
    if (result == nullptr)
        result = intermediate.addConstantUnion(0.0, EbtFloat, loc);

    return result;
}

// Finish processing object.length(). This started earlier in handleDotDereference(), where
// the ".length" part was recognized and semantically checked, and finished here where the
// function syntax "()" is recognized.
//
// Return resulting tree node.
TIntermTyped* HlslParseContext::handleLengthMethod(const TSourceLoc& loc, TFunction* function, TIntermNode* intermNode)
{
    int length = 0;

    if (function->getParamCount() > 0)
        error(loc, "method does not accept any arguments", function->getName().c_str(), "");
    else {
        const TType& type = intermNode->getAsTyped()->getType();
        if (type.isArray()) {
            if (type.isRuntimeSizedArray()) {
                // Create a unary op and let the back end handle it
                return intermediate.addBuiltInFunctionCall(loc, EOpArrayLength, true, intermNode, TType(EbtInt));
            } else
                length = type.getOuterArraySize();
        } else if (type.isMatrix())
            length = type.getMatrixCols();
        else if (type.isVector())
            length = type.getVectorSize();
        else {
            // we should not get here, because earlier semantic checking should have prevented this path
            error(loc, ".length()", "unexpected use of .length()", "");
        }
    }

    if (length == 0)
        length = 1;

    return intermediate.addConstantUnion(length, loc);
}

//
// Add any needed implicit conversions for function-call arguments to input parameters.
//
void HlslParseContext::addInputArgumentConversions(const TFunction& function, TIntermTyped*& arguments)
{
    TIntermAggregate* aggregate = arguments->getAsAggregate();
    const auto setArg = [&](int argNum, TIntermTyped* arg) {
        if (function.getParamCount() == 1)
            arguments = arg;
        else {
            if (aggregate)
                aggregate->getSequence()[argNum] = arg;
            else
                arguments = arg;
        }
    };

    // Process each argument's conversion
    for (int i = 0; i < function.getParamCount(); ++i) {
        if (! function[i].type->getQualifier().isParamInput())
            continue;

        // At this early point there is a slight ambiguity between whether an aggregate 'arguments'
        // is the single argument itself or its children are the arguments.  Only one argument
        // means take 'arguments' itself as the one argument.
        TIntermTyped* arg = function.getParamCount() == 1
                                   ? arguments->getAsTyped()
                                   : (aggregate ? aggregate->getSequence()[i]->getAsTyped() : arguments->getAsTyped());
        if (*function[i].type != arg->getType()) {
            // In-qualified arguments just need an extra node added above the argument to
            // convert to the correct type.
            TIntermTyped* convArg = intermediate.addConversion(EOpFunctionCall, *function[i].type, arg);
            if (convArg != nullptr)
                convArg = intermediate.addShapeConversion(EOpFunctionCall, *function[i].type, convArg);
            if (convArg != nullptr)
                setArg(i, convArg);
            else
                error(arg->getLoc(), "cannot convert input argument, argument", "", "%d", i);
        } else {
            if (wasFlattened(arg) || wasSplit(arg)) {
                // Will make a two-level subtree.
                // The deepest will copy member-by-member to build the structure to pass.
                // The level above that will be a two-operand EOpComma sequence that follows the copy by the
                // object itself.
                TVariable* internalAggregate = makeInternalVariable("aggShadow", *function[i].type);
                internalAggregate->getWritableType().getQualifier().makeTemporary();
                TIntermSymbol* internalSymbolNode = new TIntermSymbol(internalAggregate->getUniqueId(),
                                                                      internalAggregate->getName(),
                                                                      internalAggregate->getType());
                internalSymbolNode->setLoc(arg->getLoc());
                // This makes the deepest level, the member-wise copy
                TIntermAggregate* assignAgg = handleAssign(arg->getLoc(), EOpAssign, internalSymbolNode, arg)->getAsAggregate();

                // Now, pair that with the resulting aggregate.
                assignAgg = intermediate.growAggregate(assignAgg, internalSymbolNode, arg->getLoc());
                assignAgg->setOperator(EOpComma);
                assignAgg->setType(internalAggregate->getType());
                setArg(i, assignAgg);
            }
        }
    }
}

//
// Add any needed implicit output conversions for function-call arguments.  This
// can require a new tree topology, complicated further by whether the function
// has a return value.
//
// Returns a node of a subtree that evaluates to the return value of the function.
//
TIntermTyped* HlslParseContext::addOutputArgumentConversions(const TFunction& function, TIntermOperator& intermNode)
{
    assert (intermNode.getAsAggregate() != nullptr || intermNode.getAsUnaryNode() != nullptr);

    const TSourceLoc& loc = intermNode.getLoc();

    TIntermSequence argSequence; // temp sequence for unary node args

    if (intermNode.getAsUnaryNode())
        argSequence.push_back(intermNode.getAsUnaryNode()->getOperand());

    TIntermSequence& arguments = argSequence.empty() ? intermNode.getAsAggregate()->getSequence() : argSequence;

    const auto needsConversion = [&](int argNum) {
        return function[argNum].type->getQualifier().isParamOutput() &&
               (*function[argNum].type != arguments[argNum]->getAsTyped()->getType() ||
                shouldConvertLValue(arguments[argNum]) ||
                wasFlattened(arguments[argNum]->getAsTyped()));
    };

    // Will there be any output conversions?
    bool outputConversions = false;
    for (int i = 0; i < function.getParamCount(); ++i) {
        if (needsConversion(i)) {
            outputConversions = true;
            break;
        }
    }

    if (! outputConversions)
        return &intermNode;

    // Setup for the new tree, if needed:
    //
    // Output conversions need a different tree topology.
    // Out-qualified arguments need a temporary of the correct type, with the call
    // followed by an assignment of the temporary to the original argument:
    //     void: function(arg, ...)  ->        (          function(tempArg, ...), arg = tempArg, ...)
    //     ret = function(arg, ...)  ->  ret = (tempRet = function(tempArg, ...), arg = tempArg, ..., tempRet)
    // Where the "tempArg" type needs no conversion as an argument, but will convert on assignment.
    TIntermTyped* conversionTree = nullptr;
    TVariable* tempRet = nullptr;
    if (intermNode.getBasicType() != EbtVoid) {
        // do the "tempRet = function(...), " bit from above
        tempRet = makeInternalVariable("tempReturn", intermNode.getType());
        TIntermSymbol* tempRetNode = intermediate.addSymbol(*tempRet, loc);
        conversionTree = intermediate.addAssign(EOpAssign, tempRetNode, &intermNode, loc);
    } else
        conversionTree = &intermNode;

    conversionTree = intermediate.makeAggregate(conversionTree);

    // Process each argument's conversion
    for (int i = 0; i < function.getParamCount(); ++i) {
        if (needsConversion(i)) {
            // Out-qualified arguments needing conversion need to use the topology setup above.
            // Do the " ...(tempArg, ...), arg = tempArg" bit from above.

            // Make a temporary for what the function expects the argument to look like.
            TVariable* tempArg = makeInternalVariable("tempArg", *function[i].type);
            tempArg->getWritableType().getQualifier().makeTemporary();
            TIntermSymbol* tempArgNode = intermediate.addSymbol(*tempArg, loc);

            // This makes the deepest level, the member-wise copy
            TIntermTyped* tempAssign = handleAssign(arguments[i]->getLoc(), EOpAssign, arguments[i]->getAsTyped(), tempArgNode);
            tempAssign = handleLvalue(arguments[i]->getLoc(), "assign", tempAssign);
            conversionTree = intermediate.growAggregate(conversionTree, tempAssign, arguments[i]->getLoc());

            // replace the argument with another node for the same tempArg variable
            arguments[i] = intermediate.addSymbol(*tempArg, loc);
        }
    }

    // Finalize the tree topology (see bigger comment above).
    if (tempRet) {
        // do the "..., tempRet" bit from above
        TIntermSymbol* tempRetNode = intermediate.addSymbol(*tempRet, loc);
        conversionTree = intermediate.growAggregate(conversionTree, tempRetNode, loc);
    }

    conversionTree = intermediate.setAggregateOperator(conversionTree, EOpComma, intermNode.getType(), loc);

    return conversionTree;
}

//
// Do additional checking of built-in function calls that is not caught
// by normal semantic checks on argument type, extension tagging, etc.
//
// Assumes there has been a semantically correct match to a built-in function prototype.
//
void HlslParseContext::builtInOpCheck(const TSourceLoc& loc, const TFunction& fnCandidate, TIntermOperator& callNode)
{
    // Set up convenience accessors to the argument(s).  There is almost always
    // multiple arguments for the cases below, but when there might be one,
    // check the unaryArg first.
    const TIntermSequence* argp = nullptr;   // confusing to use [] syntax on a pointer, so this is to help get a reference
    const TIntermTyped* unaryArg = nullptr;
    const TIntermTyped* arg0 = nullptr;
    if (callNode.getAsAggregate()) {
        argp = &callNode.getAsAggregate()->getSequence();
        if (argp->size() > 0)
            arg0 = (*argp)[0]->getAsTyped();
    } else {
        assert(callNode.getAsUnaryNode());
        unaryArg = callNode.getAsUnaryNode()->getOperand();
        arg0 = unaryArg;
    }
    const TIntermSequence& aggArgs = *argp;  // only valid when unaryArg is nullptr

    switch (callNode.getOp()) {
    case EOpTextureGather:
    case EOpTextureGatherOffset:
    case EOpTextureGatherOffsets:
    {
        // Figure out which variants are allowed by what extensions,
        // and what arguments must be constant for which situations.

        TString featureString = fnCandidate.getName() + "(...)";
        const char* feature = featureString.c_str();
        int compArg = -1;  // track which argument, if any, is the constant component argument
        switch (callNode.getOp()) {
        case EOpTextureGather:
            // More than two arguments needs gpu_shader5, and rectangular or shadow needs gpu_shader5,
            // otherwise, need GL_ARB_texture_gather.
            if (fnCandidate.getParamCount() > 2 || fnCandidate[0].type->getSampler().dim == EsdRect || fnCandidate[0].type->getSampler().shadow) {
                if (! fnCandidate[0].type->getSampler().shadow)
                    compArg = 2;
            }
            break;
        case EOpTextureGatherOffset:
            // GL_ARB_texture_gather is good enough for 2D non-shadow textures with no component argument
            if (! fnCandidate[0].type->getSampler().shadow)
                compArg = 3;
            break;
        case EOpTextureGatherOffsets:
            if (! fnCandidate[0].type->getSampler().shadow)
                compArg = 3;
            break;
        default:
            break;
        }

        if (compArg > 0 && compArg < fnCandidate.getParamCount()) {
            if (aggArgs[compArg]->getAsConstantUnion()) {
                int value = aggArgs[compArg]->getAsConstantUnion()->getConstArray()[0].getIConst();
                if (value < 0 || value > 3)
                    error(loc, "must be 0, 1, 2, or 3:", feature, "component argument");
            } else
                error(loc, "must be a compile-time constant:", feature, "component argument");
        }

        break;
    }

    case EOpTextureOffset:
    case EOpTextureFetchOffset:
    case EOpTextureProjOffset:
    case EOpTextureLodOffset:
    case EOpTextureProjLodOffset:
    case EOpTextureGradOffset:
    case EOpTextureProjGradOffset:
    {
        // Handle texture-offset limits checking
        // Pick which argument has to hold constant offsets
        int arg = -1;
        switch (callNode.getOp()) {
        case EOpTextureOffset:          arg = 2;  break;
        case EOpTextureFetchOffset:     arg = (arg0->getType().getSampler().dim != EsdRect) ? 3 : 2; break;
        case EOpTextureProjOffset:      arg = 2;  break;
        case EOpTextureLodOffset:       arg = 3;  break;
        case EOpTextureProjLodOffset:   arg = 3;  break;
        case EOpTextureGradOffset:      arg = 4;  break;
        case EOpTextureProjGradOffset:  arg = 4;  break;
        default:
            assert(0);
            break;
        }

        if (arg > 0) {
            if (! aggArgs[arg]->getAsConstantUnion())
                error(loc, "argument must be compile-time constant", "texel offset", "");
            else {
                const TType& type = aggArgs[arg]->getAsTyped()->getType();
                for (int c = 0; c < type.getVectorSize(); ++c) {
                    int offset = aggArgs[arg]->getAsConstantUnion()->getConstArray()[c].getIConst();
                    if (offset > resources.maxProgramTexelOffset || offset < resources.minProgramTexelOffset)
                        error(loc, "value is out of range:", "texel offset", "[gl_MinProgramTexelOffset, gl_MaxProgramTexelOffset]");
                }
            }
        }

        break;
    }

    case EOpTextureQuerySamples:
    case EOpImageQuerySamples:
        break;

    case EOpImageAtomicAdd:
    case EOpImageAtomicMin:
    case EOpImageAtomicMax:
    case EOpImageAtomicAnd:
    case EOpImageAtomicOr:
    case EOpImageAtomicXor:
    case EOpImageAtomicExchange:
    case EOpImageAtomicCompSwap:
        break;

    case EOpInterpolateAtCentroid:
    case EOpInterpolateAtSample:
    case EOpInterpolateAtOffset:
        // Make sure the first argument is an interpolant, or an array element of an interpolant
        if (arg0->getType().getQualifier().storage != EvqVaryingIn) {
            // It might still be an array element.
            //
            // We could check more, but the semantics of the first argument are already met; the
            // only way to turn an array into a float/vec* is array dereference and swizzle.
            //
            // ES and desktop 4.3 and earlier:  swizzles may not be used
            // desktop 4.4 and later: swizzles may be used
            const TIntermTyped* base = TIntermediate::findLValueBase(arg0, true);
            if (base == nullptr || base->getType().getQualifier().storage != EvqVaryingIn)
                error(loc, "first argument must be an interpolant, or interpolant-array element", fnCandidate.getName().c_str(), "");
        }
        break;

    default:
        break;
    }
}

//
// Handle seeing a built-in constructor in a grammar production.
//
TFunction* HlslParseContext::handleConstructorCall(const TSourceLoc& loc, const TType& type)
{
    TOperator op = intermediate.mapTypeToConstructorOp(type);

    if (op == EOpNull) {
        error(loc, "cannot construct this type", type.getBasicString(), "");
        return nullptr;
    }

    TString empty("");

    return new TFunction(&empty, type, op);
}

//
// Handle seeing a "COLON semantic" at the end of a type declaration,
// by updating the type according to the semantic.
//
void HlslParseContext::handleSemantic(TSourceLoc loc, TQualifier& qualifier, const TString& semantic)
{
    // TODO: need to know if it's an input or an output
    // The following sketches what needs to be done, but can't be right
    // without taking into account stage and input/output.

    TString semanticUpperCase = semantic;
    std::transform(semanticUpperCase.begin(), semanticUpperCase.end(), semanticUpperCase.begin(), ::toupper);
    // in DX9, all outputs had to have a semantic associated with them, that was either consumed
    // by the system or was a specific register assignment
    // in DX10+, only semantics with the SV_ prefix have any meaning beyond decoration
    // Fxc will only accept DX9 style semantics in compat mode
    // Also, in DX10 if a SV value is present as the input of a stage, but isn't appropriate for that
    // stage, it would just be ignored as it is likely there as part of an output struct from one stage
    // to the next

    bool bParseDX9 = false;
    if (bParseDX9) {
        if (semanticUpperCase == "PSIZE")
            qualifier.builtIn = EbvPointSize;
        else if (semantic == "FOG")
            qualifier.builtIn = EbvFogFragCoord;
        else if (semanticUpperCase == "DEPTH")
            qualifier.builtIn = EbvFragDepth;
        else if (semanticUpperCase == "VFACE")
            qualifier.builtIn = EbvFace;
        else if (semanticUpperCase == "VPOS")
            qualifier.builtIn = EbvFragCoord;
    }

    // SV Position has a different meaning in vertex vs fragment
    if (semanticUpperCase == "SV_POSITION" && language != EShLangFragment)
        qualifier.builtIn = EbvPosition;
    else if (semanticUpperCase == "SV_POSITION" && language == EShLangFragment)
        qualifier.builtIn = EbvFragCoord;
    else if (semanticUpperCase == "SV_CLIPDISTANCE")
        qualifier.builtIn = EbvClipDistance;
    else if (semanticUpperCase == "SV_CULLDISTANCE")
        qualifier.builtIn = EbvCullDistance;
    else if (semanticUpperCase == "SV_VERTEXID")
        qualifier.builtIn = EbvVertexIndex;
    else if (semanticUpperCase == "SV_VIEWPORTARRAYINDEX")
        qualifier.builtIn = EbvViewportIndex;
    else if (semanticUpperCase == "SV_TESSFACTOR")
        qualifier.builtIn = EbvTessLevelOuter;

    // Targets are defined 0-7
    else if (semanticUpperCase == "SV_TARGET") {
        qualifier.builtIn = EbvNone;
        // qualifier.layoutLocation = 0;
    } else if (semanticUpperCase == "SV_TARGET0") {
        qualifier.builtIn = EbvNone;
        // qualifier.layoutLocation = 0;
    } else if (semanticUpperCase == "SV_TARGET1") {
        qualifier.builtIn = EbvNone;
        // qualifier.layoutLocation = 1;
    } else if (semanticUpperCase == "SV_TARGET2") {
        qualifier.builtIn = EbvNone;
        // qualifier.layoutLocation = 2;
    } else if (semanticUpperCase == "SV_TARGET3") {
        qualifier.builtIn = EbvNone;
        // qualifier.layoutLocation = 3;
    } else if (semanticUpperCase == "SV_TARGET4") {
        qualifier.builtIn = EbvNone;
        // qualifier.layoutLocation = 4;
    } else if (semanticUpperCase == "SV_TARGET5") {
        qualifier.builtIn = EbvNone;
        // qualifier.layoutLocation = 5;
    } else if (semanticUpperCase == "SV_TARGET6") {
        qualifier.builtIn = EbvNone;
        // qualifier.layoutLocation = 6;
    } else if (semanticUpperCase == "SV_TARGET7") {
        qualifier.builtIn = EbvNone;
        // qualifier.layoutLocation = 7;
    } else if (semanticUpperCase == "SV_SAMPLEINDEX")
        qualifier.builtIn = EbvSampleId;
    else if (semanticUpperCase == "SV_RENDERTARGETARRAYINDEX")
        qualifier.builtIn = EbvLayer;
    else if (semanticUpperCase == "SV_PRIMITIVEID")
        qualifier.builtIn = EbvPrimitiveId;
    else if (semanticUpperCase == "SV_OUTPUTCONTROLPOINTID")
        qualifier.builtIn = EbvInvocationId;
    else if (semanticUpperCase == "SV_ISFRONTFACE")
        qualifier.builtIn = EbvFace;
    else if (semanticUpperCase == "SV_INSTANCEID")
        qualifier.builtIn = EbvInstanceIndex;
    else if (semanticUpperCase == "SV_INSIDETESSFACTOR")
        qualifier.builtIn = EbvTessLevelInner;
    else if (semanticUpperCase == "SV_GSINSTANCEID")
        qualifier.builtIn = EbvInvocationId;
    else if (semanticUpperCase == "SV_DISPATCHTHREADID")
        qualifier.builtIn = EbvGlobalInvocationId;
    else if (semanticUpperCase == "SV_GROUPTHREADID")
        qualifier.builtIn = EbvLocalInvocationId;
    else if (semanticUpperCase == "SV_GROUPID")
        qualifier.builtIn = EbvWorkGroupId;
    else if (semanticUpperCase == "SV_DOMAINLOCATION")
        qualifier.builtIn = EbvTessCoord;
    else if (semanticUpperCase == "SV_DEPTH")
        qualifier.builtIn = EbvFragDepth;
    else if( semanticUpperCase == "SV_COVERAGE")
        qualifier.builtIn = EbvSampleMask;

    // TODO, these need to get refined to be more specific
    else if( semanticUpperCase == "SV_DEPTHGREATEREQUAL")
        qualifier.builtIn = EbvFragDepthGreater;
    else if( semanticUpperCase == "SV_DEPTHLESSEQUAL")
        qualifier.builtIn = EbvFragDepthLesser;
    else if( semanticUpperCase == "SV_STENCILREF")
        error(loc, "unimplemented; need ARB_shader_stencil_export", "SV_STENCILREF", "");
    else if( semanticUpperCase == "SV_GROUPINDEX")
        error(loc, "unimplemented", "SV_GROUPINDEX", "");
}

//
// Handle seeing something like "PACKOFFSET LEFT_PAREN c[Subcomponent][.component] RIGHT_PAREN"
//
// 'location' has the "c[Subcomponent]" part.
// 'component' points to the "component" part, or nullptr if not present.
//
void HlslParseContext::handlePackOffset(const TSourceLoc& loc, TQualifier& qualifier, const glslang::TString& location,
                                        const glslang::TString* component)
{
    if (location.size() == 0 || location[0] != 'c') {
        error(loc, "expected 'c'", "packoffset", "");
        return;
    }
    if (location.size() == 1)
        return;
    if (! isdigit(location[1])) {
        error(loc, "expected number after 'c'", "packoffset", "");
        return;
    }

    qualifier.layoutOffset = 16 * atoi(location.substr(1, location.size()).c_str());
    if (component != nullptr) {
        int componentOffset = 0;
        switch ((*component)[0]) {
        case 'x': componentOffset =  0; break;
        case 'y': componentOffset =  4; break;
        case 'z': componentOffset =  8; break;
        case 'w': componentOffset = 12; break;
        default:
            componentOffset = -1;
            break;
        }
        if (componentOffset < 0 || component->size() > 1) {
            error(loc, "expected {x, y, z, w} for component", "packoffset", "");
            return;
        }
        qualifier.layoutOffset += componentOffset;
    }
}

//
// Handle seeing something like "REGISTER LEFT_PAREN [shader_profile,] Type# RIGHT_PAREN"
//
// 'profile' points to the shader_profile part, or nullptr if not present.
// 'desc' is the type# part.
//
void HlslParseContext::handleRegister(const TSourceLoc& loc, TQualifier& qualifier, const glslang::TString* profile,
                                      const glslang::TString& desc, int subComponent, const glslang::TString* spaceDesc)
{
    if (profile != nullptr)
        warn(loc, "ignoring shader_profile", "register", "");

    if (desc.size() < 1) {
        error(loc, "expected register type", "register", "");
        return;
    }

    int regNumber = 0;
    if (desc.size() > 1) {
        if (isdigit(desc[1]))
            regNumber = atoi(desc.substr(1, desc.size()).c_str());
        else {
            error(loc, "expected register number after register type", "register", "");
            return;
        }
    }

    // TODO: learn what all these really mean and how they interact with regNumber and subComponent
    switch (std::tolower(desc[0])) {
    case 'b':
    case 't':
    case 'c':
    case 's':
    case 'u':
        qualifier.layoutBinding = regNumber + subComponent;
        break;
    default:
        warn(loc, "ignoring unrecognized register type", "register", "%c", desc[0]);
        break;
    }

    // space
    unsigned int setNumber;
    const auto crackSpace = [&]() -> bool {
        const int spaceLen = 5;
        if (spaceDesc->size() < spaceLen + 1)
            return false;
        if (spaceDesc->compare(0, spaceLen, "space") != 0)
            return false;
        if (! isdigit((*spaceDesc)[spaceLen]))
            return false;
        setNumber = atoi(spaceDesc->substr(spaceLen, spaceDesc->size()).c_str());
        return true;
    };

    if (spaceDesc) {
        if (! crackSpace()) {
            error(loc, "expected spaceN", "register", "");
            return;
        }
        qualifier.layoutSet = setNumber;
    }
}

//
// Same error message for all places assignments don't work.
//
void HlslParseContext::assignError(const TSourceLoc& loc, const char* op, TString left, TString right)
{
    error(loc, "", op, "cannot convert from '%s' to '%s'",
        right.c_str(), left.c_str());
}

//
// Same error message for all places unary operations don't work.
//
void HlslParseContext::unaryOpError(const TSourceLoc& loc, const char* op, TString operand)
{
    error(loc, " wrong operand type", op,
        "no operation '%s' exists that takes an operand of type %s (or there is no acceptable conversion)",
        op, operand.c_str());
}

//
// Same error message for all binary operations don't work.
//
void HlslParseContext::binaryOpError(const TSourceLoc& loc, const char* op, TString left, TString right)
{
    error(loc, " wrong operand types:", op,
        "no operation '%s' exists that takes a left-hand operand of type '%s' and "
        "a right operand of type '%s' (or there is no acceptable conversion)",
        op, left.c_str(), right.c_str());
}

//
// A basic type of EbtVoid is a key that the name string was seen in the source, but
// it was not found as a variable in the symbol table.  If so, give the error
// message and insert a dummy variable in the symbol table to prevent future errors.
//
void HlslParseContext::variableCheck(TIntermTyped*& nodePtr)
{
    TIntermSymbol* symbol = nodePtr->getAsSymbolNode();
    if (! symbol)
        return;

    if (symbol->getType().getBasicType() == EbtVoid) {
        error(symbol->getLoc(), "undeclared identifier", symbol->getName().c_str(), "");

        // Add to symbol table to prevent future error messages on the same name
        if (symbol->getName().size() > 0) {
            TVariable* fakeVariable = new TVariable(&symbol->getName(), TType(EbtFloat));
            symbolTable.insert(*fakeVariable);

            // substitute a symbol node for this new variable
            nodePtr = intermediate.addSymbol(*fakeVariable, symbol->getLoc());
        }
    }
}

//
// Both test, and if necessary spit out an error, to see if the node is really
// a constant.
//
void HlslParseContext::constantValueCheck(TIntermTyped* node, const char* token)
{
    if (node->getQualifier().storage != EvqConst)
        error(node->getLoc(), "constant expression required", token, "");
}

//
// Both test, and if necessary spit out an error, to see if the node is really
// an integer.
//
void HlslParseContext::integerCheck(const TIntermTyped* node, const char* token)
{
    if ((node->getBasicType() == EbtInt || node->getBasicType() == EbtUint) && node->isScalar())
        return;

    error(node->getLoc(), "scalar integer expression required", token, "");
}

//
// Both test, and if necessary spit out an error, to see if we are currently
// globally scoped.
//
void HlslParseContext::globalCheck(const TSourceLoc& loc, const char* token)
{
    if (! symbolTable.atGlobalLevel())
        error(loc, "not allowed in nested scope", token, "");
}

bool HlslParseContext::builtInName(const TString& /*identifier*/)
{
    return false;
}

//
// Make sure there is enough data and not too many arguments provided to the
// constructor to build something of the type of the constructor.  Also returns
// the type of the constructor.
//
// Returns true if there was an error in construction.
//
bool HlslParseContext::constructorError(const TSourceLoc& loc, TIntermNode* node, TFunction& function,
                                        TOperator op, TType& type)
{
    type.shallowCopy(function.getType());

    bool constructingMatrix = false;
    switch (op) {
    case EOpConstructTextureSampler:
        return constructorTextureSamplerError(loc, function);
    case EOpConstructMat2x2:
    case EOpConstructMat2x3:
    case EOpConstructMat2x4:
    case EOpConstructMat3x2:
    case EOpConstructMat3x3:
    case EOpConstructMat3x4:
    case EOpConstructMat4x2:
    case EOpConstructMat4x3:
    case EOpConstructMat4x4:
    case EOpConstructDMat2x2:
    case EOpConstructDMat2x3:
    case EOpConstructDMat2x4:
    case EOpConstructDMat3x2:
    case EOpConstructDMat3x3:
    case EOpConstructDMat3x4:
    case EOpConstructDMat4x2:
    case EOpConstructDMat4x3:
    case EOpConstructDMat4x4:
        constructingMatrix = true;
        break;
    default:
        break;
    }

    //
    // Walk the arguments for first-pass checks and collection of information.
    //

    int size = 0;
    bool constType = true;
    bool full = false;
    bool overFull = false;
    bool matrixInMatrix = false;
    bool arrayArg = false;
    for (int arg = 0; arg < function.getParamCount(); ++arg) {
        if (function[arg].type->isArray()) {
            if (! function[arg].type->isExplicitlySizedArray()) {
                // Can't construct from an unsized array.
                error(loc, "array argument must be sized", "constructor", "");
                return true;
            }
            arrayArg = true;
        }
        if (constructingMatrix && function[arg].type->isMatrix())
            matrixInMatrix = true;

        // 'full' will go to true when enough args have been seen.  If we loop
        // again, there is an extra argument.
        if (full) {
            // For vectors and matrices, it's okay to have too many components
            // available, but not okay to have unused arguments.
            overFull = true;
        }

        size += function[arg].type->computeNumComponents();
        if (op != EOpConstructStruct && ! type.isArray() && size >= type.computeNumComponents())
            full = true;

        if (function[arg].type->getQualifier().storage != EvqConst)
            constType = false;
    }

    if (constType)
        type.getQualifier().storage = EvqConst;

    if (type.isArray()) {
        if (function.getParamCount() == 0) {
            error(loc, "array constructor must have at least one argument", "constructor", "");
            return true;
        }

        if (type.isImplicitlySizedArray()) {
            // auto adapt the constructor type to the number of arguments
            type.changeOuterArraySize(function.getParamCount());
        } else if (type.getOuterArraySize() != function.getParamCount()) {
            error(loc, "array constructor needs one argument per array element", "constructor", "");
            return true;
        }

        if (type.isArrayOfArrays()) {
            // Types have to match, but we're still making the type.
            // Finish making the type, and the comparison is done later
            // when checking for conversion.
            TArraySizes& arraySizes = type.getArraySizes();

            // At least the dimensionalities have to match.
            if (! function[0].type->isArray() || arraySizes.getNumDims() != function[0].type->getArraySizes().getNumDims() + 1) {
                error(loc, "array constructor argument not correct type to construct array element", "constructor", "");
                return true;
            }

            if (arraySizes.isInnerImplicit()) {
                // "Arrays of arrays ..., and the size for any dimension is optional"
                // That means we need to adopt (from the first argument) the other array sizes into the type.
                for (int d = 1; d < arraySizes.getNumDims(); ++d) {
                    if (arraySizes.getDimSize(d) == UnsizedArraySize) {
                        arraySizes.setDimSize(d, function[0].type->getArraySizes().getDimSize(d - 1));
                    }
                }
            }
        }
    }

    if (arrayArg && op != EOpConstructStruct && ! type.isArrayOfArrays()) {
        error(loc, "constructing non-array constituent from array argument", "constructor", "");
        return true;
    }

    if (matrixInMatrix && ! type.isArray()) {
        return false;
    }

    if (overFull) {
        error(loc, "too many arguments", "constructor", "");
        return true;
    }

    if (op == EOpConstructStruct && ! type.isArray() && isZeroConstructor(node))
        return false;

    if (op == EOpConstructStruct && ! type.isArray() && (int)type.getStruct()->size() != function.getParamCount()) {
        error(loc, "Number of constructor parameters does not match the number of structure fields", "constructor", "");
        return true;
    }

    if ((op != EOpConstructStruct && size != 1 && size < type.computeNumComponents()) ||
        (op == EOpConstructStruct && size < type.computeNumComponents())) {
        error(loc, "not enough data provided for construction", "constructor", "");
        return true;
    }

    return false;
}

bool HlslParseContext::isZeroConstructor(const TIntermNode* node)
{
    return node->getAsTyped()->isScalar() && node->getAsConstantUnion() &&
           node->getAsConstantUnion()->getConstArray()[0].getIConst() == 0;
}

// Verify all the correct semantics for constructing a combined texture/sampler.
// Return true if the semantics are incorrect.
bool HlslParseContext::constructorTextureSamplerError(const TSourceLoc& loc, const TFunction& function)
{
    TString constructorName = function.getType().getBasicTypeString();  // TODO: performance: should not be making copy; interface needs to change
    const char* token = constructorName.c_str();

    // exactly two arguments needed
    if (function.getParamCount() != 2) {
        error(loc, "sampler-constructor requires two arguments", token, "");
        return true;
    }

    // For now, not allowing arrayed constructors, the rest of this function
    // is set up to allow them, if this test is removed:
    if (function.getType().isArray()) {
        error(loc, "sampler-constructor cannot make an array of samplers", token, "");
        return true;
    }

    // first argument
    //  * the constructor's first argument must be a texture type
    //  * the dimensionality (1D, 2D, 3D, Cube, Rect, Buffer, MS, and Array)
    //    of the texture type must match that of the constructed sampler type
    //    (that is, the suffixes of the type of the first argument and the
    //    type of the constructor will be spelled the same way)
    if (function[0].type->getBasicType() != EbtSampler ||
        ! function[0].type->getSampler().isTexture() ||
        function[0].type->isArray()) {
        error(loc, "sampler-constructor first argument must be a scalar textureXXX type", token, "");
        return true;
    }
    // simulate the first argument's impact on the result type, so it can be compared with the encapsulated operator!=()
    TSampler texture = function.getType().getSampler();
    texture.combined = false;
    texture.shadow = false;
    if (texture != function[0].type->getSampler()) {
        error(loc, "sampler-constructor first argument must match type and dimensionality of constructor type", token, "");
        return true;
    }

    // second argument
    //   * the constructor's second argument must be a scalar of type
    //     *sampler* or *samplerShadow*
    //   * the presence or absence of depth comparison (Shadow) must match
    //     between the constructed sampler type and the type of the second argument
    if (function[1].type->getBasicType() != EbtSampler ||
        ! function[1].type->getSampler().isPureSampler() ||
        function[1].type->isArray()) {
        error(loc, "sampler-constructor second argument must be a scalar type 'sampler'", token, "");
        return true;
    }
    if (function.getType().getSampler().shadow != function[1].type->getSampler().shadow) {
        error(loc, "sampler-constructor second argument presence of shadow must match constructor presence of shadow", token, "");
        return true;
    }

    return false;
}

// Checks to see if a void variable has been declared and raise an error message for such a case
//
// returns true in case of an error
//
bool HlslParseContext::voidErrorCheck(const TSourceLoc& loc, const TString& identifier, const TBasicType basicType)
{
    if (basicType == EbtVoid) {
        error(loc, "illegal use of type 'void'", identifier.c_str(), "");
        return true;
    }

    return false;
}

// Checks to see if the node (for the expression) contains a scalar boolean expression or not
void HlslParseContext::boolCheck(const TSourceLoc& loc, const TIntermTyped* type)
{
    if (type->getBasicType() != EbtBool || type->isArray() || type->isMatrix() || type->isVector())
        error(loc, "boolean expression expected", "", "");
}

//
// Fix just a full qualifier (no variables or types yet, but qualifier is complete) at global level.
//
void HlslParseContext::globalQualifierFix(const TSourceLoc&, TQualifier& qualifier)
{
    // move from parameter/unknown qualifiers to pipeline in/out qualifiers
    switch (qualifier.storage) {
    case EvqIn:
        qualifier.storage = EvqVaryingIn;
        break;
    case EvqOut:
        qualifier.storage = EvqVaryingOut;
        break;
    default:
        break;
    }
}

//
// Merge characteristics of the 'src' qualifier into the 'dst'.
// If there is duplication, issue error messages, unless 'force'
// is specified, which means to just override default settings.
//
// Also, when force is false, it will be assumed that 'src' follows
// 'dst', for the purpose of error checking order for versions
// that require specific orderings of qualifiers.
//
void HlslParseContext::mergeQualifiers(TQualifier& dst, const TQualifier& src)
{
    // Storage qualification
    if (dst.storage == EvqTemporary || dst.storage == EvqGlobal)
        dst.storage = src.storage;
    else if ((dst.storage == EvqIn  && src.storage == EvqOut) ||
             (dst.storage == EvqOut && src.storage == EvqIn))
        dst.storage = EvqInOut;
    else if ((dst.storage == EvqIn    && src.storage == EvqConst) ||
             (dst.storage == EvqConst && src.storage == EvqIn))
        dst.storage = EvqConstReadOnly;

    // Layout qualifiers
    mergeObjectLayoutQualifiers(dst, src, false);

    // individual qualifiers
    bool repeated = false;
#define MERGE_SINGLETON(field) repeated |= dst.field && src.field; dst.field |= src.field;
    MERGE_SINGLETON(invariant);
    MERGE_SINGLETON(noContraction);
    MERGE_SINGLETON(centroid);
    MERGE_SINGLETON(smooth);
    MERGE_SINGLETON(flat);
    MERGE_SINGLETON(nopersp);
    MERGE_SINGLETON(patch);
    MERGE_SINGLETON(sample);
    MERGE_SINGLETON(coherent);
    MERGE_SINGLETON(volatil);
    MERGE_SINGLETON(restrict);
    MERGE_SINGLETON(readonly);
    MERGE_SINGLETON(writeonly);
    MERGE_SINGLETON(specConstant);
}

// used to flatten the sampler type space into a single dimension
// correlates with the declaration of defaultSamplerPrecision[]
int HlslParseContext::computeSamplerTypeIndex(TSampler& sampler)
{
    int arrayIndex = sampler.arrayed ? 1 : 0;
    int shadowIndex = sampler.shadow ? 1 : 0;
    int externalIndex = sampler.external ? 1 : 0;

    return EsdNumDims * (EbtNumTypes * (2 * (2 * arrayIndex + shadowIndex) + externalIndex) + sampler.type) + sampler.dim;
}

//
// Do size checking for an array type's size.
//
void HlslParseContext::arraySizeCheck(const TSourceLoc& loc, TIntermTyped* expr, TArraySize& sizePair)
{
    bool isConst = false;
    sizePair.size = 1;
    sizePair.node = nullptr;

    TIntermConstantUnion* constant = expr->getAsConstantUnion();
    if (constant) {
        // handle true (non-specialization) constant
        sizePair.size = constant->getConstArray()[0].getIConst();
        isConst = true;
    } else {
        // see if it's a specialization constant instead
        if (expr->getQualifier().isSpecConstant()) {
            isConst = true;
            sizePair.node = expr;
            TIntermSymbol* symbol = expr->getAsSymbolNode();
            if (symbol && symbol->getConstArray().size() > 0)
                sizePair.size = symbol->getConstArray()[0].getIConst();
        }
    }

    if (! isConst || (expr->getBasicType() != EbtInt && expr->getBasicType() != EbtUint)) {
        error(loc, "array size must be a constant integer expression", "", "");
        return;
    }

    if (sizePair.size <= 0) {
        error(loc, "array size must be a positive integer", "", "");
        return;
    }
}

//
// Require array to be completely sized
//
void HlslParseContext::arraySizeRequiredCheck(const TSourceLoc& loc, const TArraySizes& arraySizes)
{
    if (arraySizes.isImplicit())
        error(loc, "array size required", "", "");
}

void HlslParseContext::structArrayCheck(const TSourceLoc& /*loc*/, const TType& type)
{
    const TTypeList& structure = *type.getStruct();
    for (int m = 0; m < (int)structure.size(); ++m) {
        const TType& member = *structure[m].type;
        if (member.isArray())
            arraySizeRequiredCheck(structure[m].loc, *member.getArraySizes());
    }
}

// Merge array dimensions listed in 'sizes' onto the type's array dimensions.
//
// From the spec: "vec4[2] a[3]; // size-3 array of size-2 array of vec4"
//
// That means, the 'sizes' go in front of the 'type' as outermost sizes.
// 'type' is the type part of the declaration (to the left)
// 'sizes' is the arrayness tagged on the identifier (to the right)
//
void HlslParseContext::arrayDimMerge(TType& type, const TArraySizes* sizes)
{
    if (sizes)
        type.addArrayOuterSizes(*sizes);
}

//
// Do all the semantic checking for declaring or redeclaring an array, with and
// without a size, and make the right changes to the symbol table.
//
void HlslParseContext::declareArray(const TSourceLoc& loc, TString& identifier, const TType& type, TSymbol*& symbol, bool track)
{
    if (! symbol) {
        bool currentScope;
        symbol = symbolTable.find(identifier, nullptr, &currentScope);

        if (symbol && builtInName(identifier) && ! symbolTable.atBuiltInLevel()) {
            // bad shader (errors already reported) trying to redeclare a built-in name as an array
            return;
        }
        if (symbol == nullptr || ! currentScope) {
            //
            // Successfully process a new definition.
            // (Redeclarations have to take place at the same scope; otherwise they are hiding declarations)
            //
            symbol = new TVariable(&identifier, type);
            symbolTable.insert(*symbol);
            if (track && symbolTable.atGlobalLevel())
                trackLinkageDeferred(*symbol);

            return;
        }
        if (symbol->getAsAnonMember()) {
            error(loc, "cannot redeclare a user-block member array", identifier.c_str(), "");
            symbol = nullptr;
            return;
        }
    }

    //
    // Process a redeclaration.
    //

    if (! symbol) {
        error(loc, "array variable name expected", identifier.c_str(), "");
        return;
    }

    // redeclareBuiltinVariable() should have already done the copyUp()
    TType& existingType = symbol->getWritableType();

    if (existingType.isExplicitlySizedArray()) {
        // be more lenient for input arrays to geometry shaders and tessellation control outputs, where the redeclaration is the same size
        return;
    }

    existingType.updateArraySizes(type);
}

void HlslParseContext::updateImplicitArraySize(const TSourceLoc& loc, TIntermNode *node, int index)
{
    // maybe there is nothing to do...
    TIntermTyped* typedNode = node->getAsTyped();
    if (typedNode->getType().getImplicitArraySize() > index)
        return;

    // something to do...

    // Figure out what symbol to lookup, as we will use its type to edit for the size change,
    // as that type will be shared through shallow copies for future references.
    TSymbol* symbol = nullptr;
    int blockIndex = -1;
    const TString* lookupName = nullptr;
    if (node->getAsSymbolNode())
        lookupName = &node->getAsSymbolNode()->getName();
    else if (node->getAsBinaryNode()) {
        const TIntermBinary* deref = node->getAsBinaryNode();
        // This has to be the result of a block dereference, unless it's bad shader code
        // If it's a uniform block, then an error will be issued elsewhere, but
        // return early now to avoid crashing later in this function.
        if (! deref->getLeft()->getAsSymbolNode() || deref->getLeft()->getBasicType() != EbtBlock ||
            deref->getLeft()->getType().getQualifier().storage == EvqUniform ||
            deref->getRight()->getAsConstantUnion() == nullptr)
            return;

        blockIndex = deref->getRight()->getAsConstantUnion()->getConstArray()[0].getIConst();

        lookupName = &deref->getLeft()->getAsSymbolNode()->getName();
        if (IsAnonymous(*lookupName))
            lookupName = &(*deref->getLeft()->getType().getStruct())[blockIndex].type->getFieldName();
    }

    // Lookup the symbol, should only fail if shader code is incorrect
    symbol = symbolTable.find(*lookupName);
    if (symbol == nullptr)
        return;

    if (symbol->getAsFunction()) {
        error(loc, "array variable name expected", symbol->getName().c_str(), "");
        return;
    }

    symbol->getWritableType().setImplicitArraySize(index + 1);
}

//
// Enforce non-initializer type/qualifier rules.
//
void HlslParseContext::fixConstInit(const TSourceLoc& loc, TString& identifier, TType& type, TIntermTyped*& initializer)
{
    //
    // Make the qualifier make sense, given that there is an initializer.
    //
    if (initializer == nullptr) {
        if (type.getQualifier().storage == EvqConst ||
            type.getQualifier().storage == EvqConstReadOnly) {
            initializer = intermediate.makeAggregate(loc);
            warn(loc, "variable with qualifier 'const' not initialized; zero initializing", identifier.c_str(), "");
        }
    }
}

//
// See if the identifier is a built-in symbol that can be redeclared, and if so,
// copy the symbol table's read-only built-in variable to the current
// global level, where it can be modified based on the passed in type.
//
// Returns nullptr if no redeclaration took place; meaning a normal declaration still
// needs to occur for it, not necessarily an error.
//
// Returns a redeclared and type-modified variable if a redeclared occurred.
//
TSymbol* HlslParseContext::redeclareBuiltinVariable(const TSourceLoc& /*loc*/, const TString& identifier,
                                                    const TQualifier& /*qualifier*/,
                                                    const TShaderQualifiers& /*publicType*/)
{
    if (! builtInName(identifier) || symbolTable.atBuiltInLevel() || ! symbolTable.atGlobalLevel())
        return nullptr;

    return nullptr;
}

//
// Either redeclare the requested block, or give an error message why it can't be done.
//
// TODO: functionality: explicitly sizing members of redeclared blocks is not giving them an explicit size
void HlslParseContext::redeclareBuiltinBlock(const TSourceLoc& loc, TTypeList& newTypeList, const TString& blockName, const TString* instanceName, TArraySizes* arraySizes)
{
    // Redeclaring a built-in block...

    // Blocks with instance names are easy to find, lookup the instance name,
    // Anonymous blocks need to be found via a member.
    bool builtIn;
    TSymbol* block;
    if (instanceName)
        block = symbolTable.find(*instanceName, &builtIn);
    else
        block = symbolTable.find(newTypeList.front().type->getFieldName(), &builtIn);

    // If the block was not found, this must be a version/profile/stage
    // that doesn't have it, or the instance name is wrong.
    const char* errorName = instanceName ? instanceName->c_str() : newTypeList.front().type->getFieldName().c_str();
    if (! block) {
        error(loc, "no declaration found for redeclaration", errorName, "");
        return;
    }
    // Built-in blocks cannot be redeclared more than once, which if happened,
    // we'd be finding the already redeclared one here, rather than the built in.
    if (! builtIn) {
        error(loc, "can only redeclare a built-in block once, and before any use", blockName.c_str(), "");
        return;
    }

    // Copy the block to make a writable version, to insert into the block table after editing.
    block = symbolTable.copyUpDeferredInsert(block);

    if (block->getType().getBasicType() != EbtBlock) {
        error(loc, "cannot redeclare a non block as a block", errorName, "");
        return;
    }

    // Edit and error check the container against the redeclaration
    //  - remove unused members
    //  - ensure remaining qualifiers/types match
    TType& type = block->getWritableType();
    TTypeList::iterator member = type.getWritableStruct()->begin();
    size_t numOriginalMembersFound = 0;
    while (member != type.getStruct()->end()) {
        // look for match
        bool found = false;
        TTypeList::const_iterator newMember;
        TSourceLoc memberLoc;
        memberLoc.init();
        for (newMember = newTypeList.begin(); newMember != newTypeList.end(); ++newMember) {
            if (member->type->getFieldName() == newMember->type->getFieldName()) {
                found = true;
                memberLoc = newMember->loc;
                break;
            }
        }

        if (found) {
            ++numOriginalMembersFound;
            // - ensure match between redeclared members' types
            // - check for things that can't be changed
            // - update things that can be changed
            TType& oldType = *member->type;
            const TType& newType = *newMember->type;
            if (! newType.sameElementType(oldType))
                error(memberLoc, "cannot redeclare block member with a different type", member->type->getFieldName().c_str(), "");
            if (oldType.isArray() != newType.isArray())
                error(memberLoc, "cannot change arrayness of redeclared block member", member->type->getFieldName().c_str(), "");
            else if (! oldType.sameArrayness(newType) && oldType.isExplicitlySizedArray())
                error(memberLoc, "cannot change array size of redeclared block member", member->type->getFieldName().c_str(), "");
            if (newType.getQualifier().isMemory())
                error(memberLoc, "cannot add memory qualifier to redeclared block member", member->type->getFieldName().c_str(), "");
            if (newType.getQualifier().hasLayout())
                error(memberLoc, "cannot add layout to redeclared block member", member->type->getFieldName().c_str(), "");
            if (newType.getQualifier().patch)
                error(memberLoc, "cannot add patch to redeclared block member", member->type->getFieldName().c_str(), "");
            oldType.getQualifier().centroid = newType.getQualifier().centroid;
            oldType.getQualifier().sample = newType.getQualifier().sample;
            oldType.getQualifier().invariant = newType.getQualifier().invariant;
            oldType.getQualifier().noContraction = newType.getQualifier().noContraction;
            oldType.getQualifier().smooth = newType.getQualifier().smooth;
            oldType.getQualifier().flat = newType.getQualifier().flat;
            oldType.getQualifier().nopersp = newType.getQualifier().nopersp;

            // go to next member
            ++member;
        } else {
            // For missing members of anonymous blocks that have been redeclared,
            // hide the original (shared) declaration.
            // Instance-named blocks can just have the member removed.
            if (instanceName)
                member = type.getWritableStruct()->erase(member);
            else {
                member->type->hideMember();
                ++member;
            }
        }
    }

    if (numOriginalMembersFound < newTypeList.size())
        error(loc, "block redeclaration has extra members", blockName.c_str(), "");
    if (type.isArray() != (arraySizes != nullptr))
        error(loc, "cannot change arrayness of redeclared block", blockName.c_str(), "");
    else if (type.isArray()) {
        if (type.isExplicitlySizedArray() && arraySizes->getOuterSize() == UnsizedArraySize)
            error(loc, "block already declared with size, can't redeclare as implicitly-sized", blockName.c_str(), "");
        else if (type.isExplicitlySizedArray() && type.getArraySizes() != *arraySizes)
            error(loc, "cannot change array size of redeclared block", blockName.c_str(), "");
        else if (type.isImplicitlySizedArray() && arraySizes->getOuterSize() != UnsizedArraySize)
            type.changeOuterArraySize(arraySizes->getOuterSize());
    }

    symbolTable.insert(*block);

    // Save it in the AST for linker use.
    trackLinkageDeferred(*block);
}

void HlslParseContext::paramFix(TType& type)
{
    switch (type.getQualifier().storage) {
    case EvqConst:
        type.getQualifier().storage = EvqConstReadOnly;
        break;
    case EvqGlobal:
    case EvqTemporary:
        type.getQualifier().storage = EvqIn;
        break;
    default:
        break;
    }
}

void HlslParseContext::specializationCheck(const TSourceLoc& loc, const TType& type, const char* op)
{
    if (type.containsSpecializationSize())
        error(loc, "can't use with types containing arrays sized with a specialization constant", op, "");
}

//
// Layout qualifier stuff.
//

// Put the id's layout qualification into the public type, for qualifiers not having a number set.
// This is before we know any type information for error checking.
void HlslParseContext::setLayoutQualifier(const TSourceLoc& loc, TQualifier& qualifier, TString& id)
{
    std::transform(id.begin(), id.end(), id.begin(), ::tolower);

    if (id == TQualifier::getLayoutMatrixString(ElmColumnMajor)) {
        qualifier.layoutMatrix = ElmRowMajor;
        return;
    }
    if (id == TQualifier::getLayoutMatrixString(ElmRowMajor)) {
        qualifier.layoutMatrix = ElmColumnMajor;
        return;
    }
    if (id == "push_constant") {
        requireVulkan(loc, "push_constant");
        qualifier.layoutPushConstant = true;
        return;
    }
    if (language == EShLangGeometry || language == EShLangTessEvaluation) {
        if (id == TQualifier::getGeometryString(ElgTriangles)) {
            // publicType.shaderQualifiers.geometry = ElgTriangles;
            warn(loc, "ignored", id.c_str(), "");
            return;
        }
        if (language == EShLangGeometry) {
            if (id == TQualifier::getGeometryString(ElgPoints)) {
                // publicType.shaderQualifiers.geometry = ElgPoints;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == TQualifier::getGeometryString(ElgLineStrip)) {
                // publicType.shaderQualifiers.geometry = ElgLineStrip;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == TQualifier::getGeometryString(ElgLines)) {
                // publicType.shaderQualifiers.geometry = ElgLines;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == TQualifier::getGeometryString(ElgLinesAdjacency)) {
                // publicType.shaderQualifiers.geometry = ElgLinesAdjacency;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == TQualifier::getGeometryString(ElgTrianglesAdjacency)) {
                // publicType.shaderQualifiers.geometry = ElgTrianglesAdjacency;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == TQualifier::getGeometryString(ElgTriangleStrip)) {
                // publicType.shaderQualifiers.geometry = ElgTriangleStrip;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
        } else {
            assert(language == EShLangTessEvaluation);

            // input primitive
            if (id == TQualifier::getGeometryString(ElgTriangles)) {
                // publicType.shaderQualifiers.geometry = ElgTriangles;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == TQualifier::getGeometryString(ElgQuads)) {
                // publicType.shaderQualifiers.geometry = ElgQuads;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == TQualifier::getGeometryString(ElgIsolines)) {
                // publicType.shaderQualifiers.geometry = ElgIsolines;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }

            // vertex spacing
            if (id == TQualifier::getVertexSpacingString(EvsEqual)) {
                // publicType.shaderQualifiers.spacing = EvsEqual;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == TQualifier::getVertexSpacingString(EvsFractionalEven)) {
                // publicType.shaderQualifiers.spacing = EvsFractionalEven;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == TQualifier::getVertexSpacingString(EvsFractionalOdd)) {
                // publicType.shaderQualifiers.spacing = EvsFractionalOdd;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }

            // triangle order
            if (id == TQualifier::getVertexOrderString(EvoCw)) {
                // publicType.shaderQualifiers.order = EvoCw;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == TQualifier::getVertexOrderString(EvoCcw)) {
                // publicType.shaderQualifiers.order = EvoCcw;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }

            // point mode
            if (id == "point_mode") {
                // publicType.shaderQualifiers.pointMode = true;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
        }
    }
    if (language == EShLangFragment) {
        if (id == "origin_upper_left") {
            // publicType.shaderQualifiers.originUpperLeft = true;
            warn(loc, "ignored", id.c_str(), "");
            return;
        }
        if (id == "pixel_center_integer") {
            // publicType.shaderQualifiers.pixelCenterInteger = true;
            warn(loc, "ignored", id.c_str(), "");
            return;
        }
        if (id == "early_fragment_tests") {
            // publicType.shaderQualifiers.earlyFragmentTests = true;
            warn(loc, "ignored", id.c_str(), "");
            return;
        }
        for (TLayoutDepth depth = (TLayoutDepth)(EldNone + 1); depth < EldCount; depth = (TLayoutDepth)(depth + 1)) {
            if (id == TQualifier::getLayoutDepthString(depth)) {
                // publicType.shaderQualifiers.layoutDepth = depth;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
        }
        if (id.compare(0, 13, "blend_support") == 0) {
            bool found = false;
            for (TBlendEquationShift be = (TBlendEquationShift)0; be < EBlendCount; be = (TBlendEquationShift)(be + 1)) {
                if (id == TQualifier::getBlendEquationString(be)) {
                    requireExtensions(loc, 1, &E_GL_KHR_blend_equation_advanced, "blend equation");
                    intermediate.addBlendEquation(be);
                    // publicType.shaderQualifiers.blendEquation = true;
                    warn(loc, "ignored", id.c_str(), "");
                    found = true;
                    break;
                }
            }
            if (! found)
                error(loc, "unknown blend equation", "blend_support", "");
            return;
        }
    }
    error(loc, "unrecognized layout identifier, or qualifier requires assignment (e.g., binding = 4)", id.c_str(), "");
}

// Put the id's layout qualifier value into the public type, for qualifiers having a number set.
// This is before we know any type information for error checking.
void HlslParseContext::setLayoutQualifier(const TSourceLoc& loc, TQualifier& qualifier, TString& id, const TIntermTyped* node)
{
    const char* feature = "layout-id value";
    // const char* nonLiteralFeature = "non-literal layout-id value";

    integerCheck(node, feature);
    const TIntermConstantUnion* constUnion = node->getAsConstantUnion();
    int value = 0;
    if (constUnion) {
        value = constUnion->getConstArray()[0].getIConst();
    }

    std::transform(id.begin(), id.end(), id.begin(), ::tolower);

    if (id == "offset") {
        qualifier.layoutOffset = value;
        return;
    } else if (id == "align") {
        // "The specified alignment must be a power of 2, or a compile-time error results."
        if (! IsPow2(value))
            error(loc, "must be a power of 2", "align", "");
        else
            qualifier.layoutAlign = value;
        return;
    } else if (id == "location") {
        if ((unsigned int)value >= TQualifier::layoutLocationEnd)
            error(loc, "location is too large", id.c_str(), "");
        else
            qualifier.layoutLocation = value;
        return;
    } else if (id == "set") {
        if ((unsigned int)value >= TQualifier::layoutSetEnd)
            error(loc, "set is too large", id.c_str(), "");
        else
            qualifier.layoutSet = value;
        return;
    } else if (id == "binding") {
        if ((unsigned int)value >= TQualifier::layoutBindingEnd)
            error(loc, "binding is too large", id.c_str(), "");
        else
            qualifier.layoutBinding = value;
        return;
    } else if (id == "component") {
        if ((unsigned)value >= TQualifier::layoutComponentEnd)
            error(loc, "component is too large", id.c_str(), "");
        else
            qualifier.layoutComponent = value;
        return;
    } else if (id.compare(0, 4, "xfb_") == 0) {
        // "Any shader making any static use (after preprocessing) of any of these
        // *xfb_* qualifiers will cause the shader to be in a transform feedback
        // capturing mode and hence responsible for describing the transform feedback
        // setup."
        intermediate.setXfbMode();
        if (id == "xfb_buffer") {
            // "It is a compile-time error to specify an *xfb_buffer* that is greater than
            // the implementation-dependent constant gl_MaxTransformFeedbackBuffers."
            if (value >= resources.maxTransformFeedbackBuffers)
                error(loc, "buffer is too large:", id.c_str(), "gl_MaxTransformFeedbackBuffers is %d", resources.maxTransformFeedbackBuffers);
            if (value >= (int)TQualifier::layoutXfbBufferEnd)
                error(loc, "buffer is too large:", id.c_str(), "internal max is %d", TQualifier::layoutXfbBufferEnd - 1);
            else
                qualifier.layoutXfbBuffer = value;
            return;
        } else if (id == "xfb_offset") {
            if (value >= (int)TQualifier::layoutXfbOffsetEnd)
                error(loc, "offset is too large:", id.c_str(), "internal max is %d", TQualifier::layoutXfbOffsetEnd - 1);
            else
                qualifier.layoutXfbOffset = value;
            return;
        } else if (id == "xfb_stride") {
            // "The resulting stride (implicit or explicit), when divided by 4, must be less than or equal to the
            // implementation-dependent constant gl_MaxTransformFeedbackInterleavedComponents."
            if (value > 4 * resources.maxTransformFeedbackInterleavedComponents)
                error(loc, "1/4 stride is too large:", id.c_str(), "gl_MaxTransformFeedbackInterleavedComponents is %d", resources.maxTransformFeedbackInterleavedComponents);
            else if (value >= (int)TQualifier::layoutXfbStrideEnd)
                error(loc, "stride is too large:", id.c_str(), "internal max is %d", TQualifier::layoutXfbStrideEnd - 1);
            if (value < (int)TQualifier::layoutXfbStrideEnd)
                qualifier.layoutXfbStride = value;
            return;
        }
    }

    if (id == "input_attachment_index") {
        requireVulkan(loc, "input_attachment_index");
        if (value >= (int)TQualifier::layoutAttachmentEnd)
            error(loc, "attachment index is too large", id.c_str(), "");
        else
            qualifier.layoutAttachment = value;
        return;
    }
    if (id == "constant_id") {
        requireSpv(loc, "constant_id");
        if (value >= (int)TQualifier::layoutSpecConstantIdEnd) {
            error(loc, "specialization-constant id is too large", id.c_str(), "");
        } else {
            qualifier.layoutSpecConstantId = value;
            qualifier.specConstant = true;
            if (! intermediate.addUsedConstantId(value))
                error(loc, "specialization-constant id already used", id.c_str(), "");
        }
        return;
    }

    switch (language) {
    case EShLangVertex:
        break;

    case EShLangTessControl:
        if (id == "vertices") {
            if (value == 0)
                error(loc, "must be greater than 0", "vertices", "");
            else
                // publicType.shaderQualifiers.vertices = value;
                warn(loc, "ignored", id.c_str(), "");
            return;
        }
        break;

    case EShLangTessEvaluation:
        break;

    case EShLangGeometry:
        if (id == "invocations") {
            if (value == 0)
                error(loc, "must be at least 1", "invocations", "");
            else
                // publicType.shaderQualifiers.invocations = value;
                warn(loc, "ignored", id.c_str(), "");
            return;
        }
        if (id == "max_vertices") {
            // publicType.shaderQualifiers.vertices = value;
            warn(loc, "ignored", id.c_str(), "");
            if (value > resources.maxGeometryOutputVertices)
                error(loc, "too large, must be less than gl_MaxGeometryOutputVertices", "max_vertices", "");
            return;
        }
        if (id == "stream") {
            qualifier.layoutStream = value;
            return;
        }
        break;

    case EShLangFragment:
        if (id == "index") {
            qualifier.layoutIndex = value;
            return;
        }
        break;

    case EShLangCompute:
        if (id.compare(0, 11, "local_size_") == 0) {
            if (id == "local_size_x") {
                // publicType.shaderQualifiers.localSize[0] = value;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == "local_size_y") {
                // publicType.shaderQualifiers.localSize[1] = value;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (id == "local_size_z") {
                // publicType.shaderQualifiers.localSize[2] = value;
                warn(loc, "ignored", id.c_str(), "");
                return;
            }
            if (spvVersion.spv != 0) {
                if (id == "local_size_x_id") {
                    // publicType.shaderQualifiers.localSizeSpecId[0] = value;
                    warn(loc, "ignored", id.c_str(), "");
                    return;
                }
                if (id == "local_size_y_id") {
                    // publicType.shaderQualifiers.localSizeSpecId[1] = value;
                    warn(loc, "ignored", id.c_str(), "");
                    return;
                }
                if (id == "local_size_z_id") {
                    // publicType.shaderQualifiers.localSizeSpecId[2] = value;
                    warn(loc, "ignored", id.c_str(), "");
                    return;
                }
            }
        }
        break;

    default:
        break;
    }

    error(loc, "there is no such layout identifier for this stage taking an assigned value", id.c_str(), "");
}

// Merge any layout qualifier information from src into dst, leaving everything else in dst alone
//
// "More than one layout qualifier may appear in a single declaration.
// Additionally, the same layout-qualifier-name can occur multiple times
// within a layout qualifier or across multiple layout qualifiers in the
// same declaration. When the same layout-qualifier-name occurs
// multiple times, in a single declaration, the last occurrence overrides
// the former occurrence(s).  Further, if such a layout-qualifier-name
// will effect subsequent declarations or other observable behavior, it
// is only the last occurrence that will have any effect, behaving as if
// the earlier occurrence(s) within the declaration are not present.
// This is also true for overriding layout-qualifier-names, where one
// overrides the other (e.g., row_major vs. column_major); only the last
// occurrence has any effect."
//
void HlslParseContext::mergeObjectLayoutQualifiers(TQualifier& dst, const TQualifier& src, bool inheritOnly)
{
    if (src.hasMatrix())
        dst.layoutMatrix = src.layoutMatrix;
    if (src.hasPacking())
        dst.layoutPacking = src.layoutPacking;

    if (src.hasStream())
        dst.layoutStream = src.layoutStream;

    if (src.hasFormat())
        dst.layoutFormat = src.layoutFormat;

    if (src.hasXfbBuffer())
        dst.layoutXfbBuffer = src.layoutXfbBuffer;

    if (src.hasAlign())
        dst.layoutAlign = src.layoutAlign;

    if (! inheritOnly) {
        if (src.hasLocation())
            dst.layoutLocation = src.layoutLocation;
        if (src.hasComponent())
            dst.layoutComponent = src.layoutComponent;
        if (src.hasIndex())
            dst.layoutIndex = src.layoutIndex;

        if (src.hasOffset())
            dst.layoutOffset = src.layoutOffset;

        if (src.hasSet())
            dst.layoutSet = src.layoutSet;
        if (src.layoutBinding != TQualifier::layoutBindingEnd)
            dst.layoutBinding = src.layoutBinding;

        if (src.hasXfbStride())
            dst.layoutXfbStride = src.layoutXfbStride;
        if (src.hasXfbOffset())
            dst.layoutXfbOffset = src.layoutXfbOffset;
        if (src.hasAttachment())
            dst.layoutAttachment = src.layoutAttachment;
        if (src.hasSpecConstantId())
            dst.layoutSpecConstantId = src.layoutSpecConstantId;

        if (src.layoutPushConstant)
            dst.layoutPushConstant = true;
    }
}

//
// Look up a function name in the symbol table, and make sure it is a function.
//
// First, look for an exact match.  If there is none, use the generic selector
// TParseContextBase::selectFunction() to find one, parameterized by the
// convertible() and better() predicates defined below.
//
// Return the function symbol if found, otherwise nullptr.
//
const TFunction* HlslParseContext::findFunction(const TSourceLoc& loc, TFunction& call, bool& builtIn,
                                                TIntermTyped*& args)
{
    // const TFunction* function = nullptr;

    if (symbolTable.isFunctionNameVariable(call.getName())) {
        error(loc, "can't use function syntax on variable", call.getName().c_str(), "");
        return nullptr;
    }

    // first, look for an exact match
    TSymbol* symbol = symbolTable.find(call.getMangledName(), &builtIn);
    if (symbol)
        return symbol->getAsFunction();

    // no exact match, use the generic selector, parameterized by the GLSL rules

    // create list of candidates to send
    TVector<const TFunction*> candidateList;
    symbolTable.findFunctionNameList(call.getMangledName(), candidateList, builtIn);

    // These builtin ops can accept any type, so we bypass the argument selection
    if (candidateList.size() == 1 && builtIn &&
        (candidateList[0]->getBuiltInOp() == EOpMethodAppend ||
         candidateList[0]->getBuiltInOp() == EOpMethodRestartStrip)) {

        return candidateList[0];
    }

    bool allowOnlyUpConversions = true;

    // can 'from' convert to 'to'?
    const auto convertible = [&](const TType& from, const TType& to, TOperator op, int arg) -> bool {
        if (from == to)
            return true;

        // no aggregate conversions
        if (from.isArray()  || to.isArray() ||
            from.isStruct() || to.isStruct())
            return false;

        switch (op) {
        case EOpInterlockedAdd:
        case EOpInterlockedAnd:
        case EOpInterlockedCompareExchange:
        case EOpInterlockedCompareStore:
        case EOpInterlockedExchange:
        case EOpInterlockedMax:
        case EOpInterlockedMin:
        case EOpInterlockedOr:
        case EOpInterlockedXor:
            // We do not promote the texture or image type for these ocodes.  Normally that would not
            // be an issue because it's a buffer, but we haven't decomposed the opcode yet, and at this
            // stage it's merely e.g, a basic integer type.
            //
            // Instead, we want to promote other arguments, but stay within the same family.  In other
            // words, InterlockedAdd(RWBuffer<int>, ...) will always use the int flavor, never the uint flavor,
            // but it is allowed to promote its other arguments.
            if (arg == 0)
                return false;
            break;
        case EOpMethodSample:
        case EOpMethodSampleBias:
        case EOpMethodSampleCmp:
        case EOpMethodSampleCmpLevelZero:
        case EOpMethodSampleGrad:
        case EOpMethodSampleLevel:
        case EOpMethodLoad:
        case EOpMethodGetDimensions:
        case EOpMethodGetSamplePosition:
        case EOpMethodGather:
        case EOpMethodCalculateLevelOfDetail:
        case EOpMethodCalculateLevelOfDetailUnclamped:
        case EOpMethodGatherRed:
        case EOpMethodGatherGreen:
        case EOpMethodGatherBlue:
        case EOpMethodGatherAlpha:
        case EOpMethodGatherCmp:
        case EOpMethodGatherCmpRed:
        case EOpMethodGatherCmpGreen:
        case EOpMethodGatherCmpBlue:
        case EOpMethodGatherCmpAlpha:
        case EOpMethodAppend:
        case EOpMethodRestartStrip:
            // those are method calls, the object type can not be changed
            // they are equal if the dim and type match (is dim sufficient?)
            if (arg == 0)
                return from.getSampler().type == to.getSampler().type &&
                       from.getSampler().arrayed == to.getSampler().arrayed &&
                       from.getSampler().shadow == to.getSampler().shadow &&
                       from.getSampler().ms == to.getSampler().ms &&
                       from.getSampler().dim == to.getSampler().dim;
            break;
        default:
            break;
        }

        // basic types have to be convertible
        if (allowOnlyUpConversions)
            if (! intermediate.canImplicitlyPromote(from.getBasicType(), to.getBasicType(), EOpFunctionCall))
                return false;

        // shapes have to be convertible
        if ((from.isScalarOrVec1() && to.isScalarOrVec1()) ||
            (from.isScalarOrVec1() && to.isVector())    ||
            (from.isVector() && to.isVector() && from.getVectorSize() >= to.getVectorSize()))
            return true;

        // TODO: what are the matrix rules? they go here

        return false;
    };

    // Is 'to2' a better conversion than 'to1'?
    // Ties should not be considered as better.
    // Assumes 'convertible' already said true.
    const auto better = [](const TType& from, const TType& to1, const TType& to2) -> bool {
        // exact match is always better than mismatch
        if (from == to2)
            return from != to1;
        if (from == to1)
            return false;

        // shape changes are always worse
        if (from.isScalar() || from.isVector()) {
            if (from.getVectorSize() == to2.getVectorSize() &&
                from.getVectorSize() != to1.getVectorSize())
                return true;
            if (from.getVectorSize() == to1.getVectorSize() &&
                from.getVectorSize() != to2.getVectorSize())
                return false;
        }

        // Handle sampler betterness: An exact sampler match beats a non-exact match.
        // (If we just looked at basic type, all EbtSamplers would look the same).
        // If any type is not a sampler, just use the linearize function below.
        if (from.getBasicType() == EbtSampler && to1.getBasicType() == EbtSampler && to2.getBasicType() == EbtSampler) {
            // We can ignore the vector size in the comparison.
            TSampler to1Sampler = to1.getSampler();
            TSampler to2Sampler = to2.getSampler();

            to1Sampler.vectorSize = to2Sampler.vectorSize = from.getSampler().vectorSize;

            if (from.getSampler() == to2Sampler)
                return from.getSampler() != to1Sampler;
            if (from.getSampler() == to1Sampler)
                return false;
        }

        // Might or might not be changing shape, which means basic type might
        // or might not match, so within that, the question is how big a
        // basic-type conversion is being done.
        //
        // Use a hierarchy of domains, translated to order of magnitude
        // in a linearized view:
        //   - floating-point vs. integer
        //     - 32 vs. 64 bit (or width in general)
        //       - bool vs. non bool
        //         - signed vs. not signed
        const auto linearize = [](const TBasicType& basicType) -> int {
            switch (basicType) {
            case EbtBool:     return 1;
            case EbtInt:      return 10;
            case EbtUint:     return 11;
            case EbtInt64:    return 20;
            case EbtUint64:   return 21;
            case EbtFloat:    return 100;
            case EbtDouble:   return 110;
            default:          return 0;
            }
        };

        return std::abs(linearize(to2.getBasicType()) - linearize(from.getBasicType())) <
               std::abs(linearize(to1.getBasicType()) - linearize(from.getBasicType()));
    };

    // for ambiguity reporting
    bool tie = false;

    // send to the generic selector
    const TFunction* bestMatch = selectFunction(candidateList, call, convertible, better, tie);

    if (bestMatch == nullptr) {
        // If there is nothing selected by allowing only up-conversions (to a larger linearize() value),
        // we instead try down-conversions, which are valid in HLSL, but not preferred if there are any
        // upconversions possible.
        allowOnlyUpConversions = false;
        bestMatch = selectFunction(candidateList, call, convertible, better, tie);
    }

    if (bestMatch == nullptr) {
        error(loc, "no matching overloaded function found", call.getName().c_str(), "");
        return nullptr;
    }

    // For builtins, we can convert across the arguments.  This will happen in several steps:
    // Step 1:  If there's an exact match, use it.
    // Step 2a: Otherwise, get the operator from the best match and promote arguments:
    // Step 2b: reconstruct the TFunction based on the new arg types
    // Step 3:  Re-select after type promotion is applied, to find proper candidate.
    if (builtIn) {
        // Step 1: If there's an exact match, use it.
        if (call.getMangledName() == bestMatch->getMangledName())
            return bestMatch;

        // Step 2a: Otherwise, get the operator from the best match and promote arguments as if we
        // are that kind of operator.
        if (args != nullptr) {
            // The arg list can be a unary node, or an aggregate.  We have to handle both.
            // We will use the normal promote() facilities, which require an interm node.
            TIntermOperator* promote = nullptr;

            if (call.getParamCount() == 1) {
                promote = new TIntermUnary(bestMatch->getBuiltInOp());
                promote->getAsUnaryNode()->setOperand(args->getAsTyped());
            } else {
                promote = new TIntermAggregate(bestMatch->getBuiltInOp());
                promote->getAsAggregate()->getSequence().swap(args->getAsAggregate()->getSequence());
            }

            if (! intermediate.promote(promote))
                return nullptr;

            // Obtain the promoted arg list.
            if (call.getParamCount() == 1) {
                args = promote->getAsUnaryNode()->getOperand();
            } else {
                promote->getAsAggregate()->getSequence().swap(args->getAsAggregate()->getSequence());
            }
        }

        // Step 2b: reconstruct the TFunction based on the new arg types
        TFunction convertedCall(&call.getName(), call.getType(), call.getBuiltInOp());

        if (args->getAsAggregate()) {
            // Handle aggregates: put all args into the new function call
            for (int arg=0; arg<int(args->getAsAggregate()->getSequence().size()); ++arg) {
                // TODO: But for constness, we could avoid the new & shallowCopy, and use the pointer directly.
                TParameter param = { 0, new TType, nullptr };
                param.type->shallowCopy(args->getAsAggregate()->getSequence()[arg]->getAsTyped()->getType());
                convertedCall.addParameter(param);
            }
        } else if (args->getAsUnaryNode()) {
            // Handle unaries: put all args into the new function call
            TParameter param = { 0, new TType, nullptr };
            param.type->shallowCopy(args->getAsUnaryNode()->getOperand()->getAsTyped()->getType());
            convertedCall.addParameter(param);
        } else if (args->getAsTyped()) {
            // Handle bare e.g, floats, not in an aggregate.
            TParameter param = { 0, new TType, nullptr };
            param.type->shallowCopy(args->getAsTyped()->getType());
            convertedCall.addParameter(param);
        } else {
            assert(0); // unknown argument list.
            return nullptr;
        }

        // Step 3: Re-select after type promotion, to find proper candidate
        // send to the generic selector
        bestMatch = selectFunction(candidateList, convertedCall, convertible, better, tie);

        // At this point, there should be no tie.
    }

    if (tie)
        error(loc, "ambiguous best function under implicit type conversion", call.getName().c_str(), "");

    // Append default parameter values if needed
    if (!tie && bestMatch != nullptr) {
        for (int defParam = call.getParamCount(); defParam < bestMatch->getParamCount(); ++defParam) {
            handleFunctionArgument(&call, args, (*bestMatch)[defParam].defaultValue);
        }
    }

    return bestMatch;
}

//
// Do everything necessary to handle a typedef declaration, for a single symbol.
//
// 'parseType' is the type part of the declaration (to the left)
// 'arraySizes' is the arrayness tagged on the identifier (to the right)
//
void HlslParseContext::declareTypedef(const TSourceLoc& loc, TString& identifier, const TType& parseType, TArraySizes* /*arraySizes*/)
{
    TType type;
    type.deepCopy(parseType);

    TVariable* typeSymbol = new TVariable(&identifier, type, true);
    if (! symbolTable.insert(*typeSymbol))
        error(loc, "name already defined", "typedef", identifier.c_str());
}

// Type sanitization: return existing sanitized (temporary) type if there is one, else make new one.
TType* HlslParseContext::sanitizeType(TType* type)
{
    // We only do this for structs.
    if (!type->isStruct())
        return type;

    // Type sanitization: if this is declaring a variable of a type that contains
    // interstage IO, we want to make it a temporary.
    const auto sanitizedTypeIter = sanitizedTypeMap.find(type->getStruct());

    if (sanitizedTypeIter != sanitizedTypeMap.end()) {
        // We've sanitized this before.  Use that one.
        TType* sanitizedType = new TType();
        sanitizedType->shallowCopy(*sanitizedTypeIter->second);

        // Arrayness is not part of the sanitized type.  Use the input type's arrayness.
        if (type->isArray())
            sanitizedType->newArraySizes(type->getArraySizes());
        else
            sanitizedType->clearArraySizes();
        return sanitizedType;
    } else {
        if (type->containsBuiltInInterstageIO(language)) {
            // This means the type contains interstage IO, but we've never encountered it before.
            // Copy it, sanitize it, and remember it in the sanitizedTypeMap
            TType* sanitizedType = type->clone();
            sanitizedType->makeTemporary();
            sanitizedTypeMap[type->getStruct()] = sanitizedType;
            return sanitizedType;
        } else {
            // This means the type has no interstage IO, so we can use it as is.
            return type;
        }
    }
}

//
// Do everything necessary to handle a variable (non-block) declaration.
// Either redeclaring a variable, or making a new one, updating the symbol
// table, and all error checking.
//
// Returns a subtree node that computes an initializer, if needed.
// Returns nullptr if there is no code to execute for initialization.
//
// 'parseType' is the type part of the declaration (to the left)
// 'arraySizes' is the arrayness tagged on the identifier (to the right)
//
TIntermNode* HlslParseContext::declareVariable(const TSourceLoc& loc, TString& identifier, TType& type, TIntermTyped* initializer)
{
    if (voidErrorCheck(loc, identifier, type.getBasicType()))
        return nullptr;

    // make const and initialization consistent
    fixConstInit(loc, identifier, type, initializer);

    // Check for redeclaration of built-ins and/or attempting to declare a reserved name
    TSymbol* symbol = nullptr;

    inheritGlobalDefaults(type.getQualifier());

    const bool flattenVar = shouldFlatten(type);
    const bool splitVar   = shouldSplit(type);

    // Type sanitization: if this is declaring a variable of a type that contains
    // interstage IO, we want to make it a temporary.
    TType* sanitizedType = sanitizeType(&type);

    // Declare the variable
    if (type.isArray()) {
        // array case
        declareArray(loc, identifier, *sanitizedType, symbol, !flattenVar);
    } else {
        // non-array case
        if (! symbol)
            symbol = declareNonArray(loc, identifier, *sanitizedType, !flattenVar);
        else if (type != symbol->getType())
            error(loc, "cannot change the type of", "redeclaration", symbol->getName().c_str());
    }

    if (flattenVar)
        flatten(loc, *symbol->getAsVariable());

    if (splitVar)
        split(*symbol->getAsVariable());

    if (! symbol)
        return nullptr;

    // Deal with initializer
    TIntermNode* initNode = nullptr;
    if (symbol && initializer) {
        if (flattenVar)
            error(loc, "flattened array with initializer list unsupported", identifier.c_str(), "");

        TVariable* variable = symbol->getAsVariable();
        if (! variable) {
            error(loc, "initializer requires a variable, not a member", identifier.c_str(), "");
            return nullptr;
        }
        initNode = executeInitializer(loc, initializer, variable);
    }

    return initNode;
}

// Pick up global defaults from the provide global defaults into dst.
void HlslParseContext::inheritGlobalDefaults(TQualifier& dst) const
{
    if (dst.storage == EvqVaryingOut) {
        if (! dst.hasStream() && language == EShLangGeometry)
            dst.layoutStream = globalOutputDefaults.layoutStream;
        if (! dst.hasXfbBuffer())
            dst.layoutXfbBuffer = globalOutputDefaults.layoutXfbBuffer;
    }
}

//
// Make an internal-only variable whose name is for debug purposes only
// and won't be searched for.  Callers will only use the return value to use
// the variable, not the name to look it up.  It is okay if the name
// is the same as other names; there won't be any conflict.
//
TVariable* HlslParseContext::makeInternalVariable(const char* name, const TType& type) const
{
    TString* nameString = NewPoolTString(name);
    TVariable* variable = new TVariable(nameString, type);
    symbolTable.makeInternalVariable(*variable);

    return variable;
}

//
// Declare a non-array variable, the main point being there is no redeclaration
// for resizing allowed.
//
// Return the successfully declared variable.
//
TVariable* HlslParseContext::declareNonArray(const TSourceLoc& loc, TString& identifier, TType& type, bool track)
{
    // make a new variable
    TVariable* variable = new TVariable(&identifier, type);

    // add variable to symbol table
    if (symbolTable.insert(*variable)) {
        if (track && symbolTable.atGlobalLevel())
            trackLinkageDeferred(*variable);
        return variable;
    }

    error(loc, "redefinition", variable->getName().c_str(), "");
    return nullptr;
}

//
// Handle all types of initializers from the grammar.
//
// Returning nullptr just means there is no code to execute to handle the
// initializer, which will, for example, be the case for constant initializers.
//
TIntermNode* HlslParseContext::executeInitializer(const TSourceLoc& loc, TIntermTyped* initializer, TVariable* variable)
{
    //
    // Identifier must be of type constant, a global, or a temporary, and
    // starting at version 120, desktop allows uniforms to have initializers.
    //
    TStorageQualifier qualifier = variable->getType().getQualifier().storage;

    //
    // If the initializer was from braces { ... }, we convert the whole subtree to a
    // constructor-style subtree, allowing the rest of the code to operate
    // identically for both kinds of initializers.
    //
    //
    // Type can't be deduced from the initializer list, so a skeletal type to
    // follow has to be passed in.  Constness and specialization-constness
    // should be deduced bottom up, not dictated by the skeletal type.
    //
    TType skeletalType;
    skeletalType.shallowCopy(variable->getType());
    skeletalType.getQualifier().makeTemporary();
    if (initializer->getAsAggregate() && initializer->getAsAggregate()->getOp() == EOpNull)
        initializer = convertInitializerList(loc, skeletalType, initializer);
    if (! initializer) {
        // error recovery; don't leave const without constant values
        if (qualifier == EvqConst)
            variable->getWritableType().getQualifier().storage = EvqTemporary;
        return nullptr;
    }

    // Fix outer arrayness if variable is unsized, getting size from the initializer
    if (initializer->getType().isExplicitlySizedArray() &&
        variable->getType().isImplicitlySizedArray())
        variable->getWritableType().changeOuterArraySize(initializer->getType().getOuterArraySize());

    // Inner arrayness can also get set by an initializer
    if (initializer->getType().isArrayOfArrays() && variable->getType().isArrayOfArrays() &&
        initializer->getType().getArraySizes()->getNumDims() ==
        variable->getType().getArraySizes()->getNumDims()) {
        // adopt unsized sizes from the initializer's sizes
        for (int d = 1; d < variable->getType().getArraySizes()->getNumDims(); ++d) {
            if (variable->getType().getArraySizes()->getDimSize(d) == UnsizedArraySize)
                variable->getWritableType().getArraySizes().setDimSize(d, initializer->getType().getArraySizes()->getDimSize(d));
        }
    }

    // Uniform and global consts require a constant initializer
    if (qualifier == EvqUniform && initializer->getType().getQualifier().storage != EvqConst) {
        error(loc, "uniform initializers must be constant", "=", "'%s'", variable->getType().getCompleteString().c_str());
        variable->getWritableType().getQualifier().storage = EvqTemporary;
        return nullptr;
    }
    if (qualifier == EvqConst && symbolTable.atGlobalLevel() && initializer->getType().getQualifier().storage != EvqConst) {
        error(loc, "global const initializers must be constant", "=", "'%s'", variable->getType().getCompleteString().c_str());
        variable->getWritableType().getQualifier().storage = EvqTemporary;
        return nullptr;
    }

    // Const variables require a constant initializer, depending on version
    if (qualifier == EvqConst) {
        if (initializer->getType().getQualifier().storage != EvqConst) {
            variable->getWritableType().getQualifier().storage = EvqConstReadOnly;
            qualifier = EvqConstReadOnly;
        }
    }

    if (qualifier == EvqConst || qualifier == EvqUniform) {
        // Compile-time tagging of the variable with its constant value...

        initializer = intermediate.addConversion(EOpAssign, variable->getType(), initializer);
        if (! initializer || ! initializer->getAsConstantUnion() || variable->getType() != initializer->getType()) {
            error(loc, "non-matching or non-convertible constant type for const initializer",
                variable->getType().getStorageQualifierString(), "");
            variable->getWritableType().getQualifier().storage = EvqTemporary;
            return nullptr;
        }

        variable->setConstArray(initializer->getAsConstantUnion()->getConstArray());
    } else {
        // normal assigning of a value to a variable...
        specializationCheck(loc, initializer->getType(), "initializer");
        TIntermSymbol* intermSymbol = intermediate.addSymbol(*variable, loc);
        TIntermNode* initNode = handleAssign(loc, EOpAssign, intermSymbol, initializer);
        if (! initNode)
            assignError(loc, "=", intermSymbol->getCompleteString(), initializer->getCompleteString());

        return initNode;
    }

    return nullptr;
}

//
// Reprocess any initializer-list { ... } parts of the initializer.
// Need to hierarchically assign correct types and implicit
// conversions. Will do this mimicking the same process used for
// creating a constructor-style initializer, ensuring we get the
// same form.
//
// Returns a node representing an expression for the initializer list expressed
// as the correct type.
//
// Returns nullptr if there is an error.
//
TIntermTyped* HlslParseContext::convertInitializerList(const TSourceLoc& loc, const TType& type, TIntermTyped* initializer)
{
    // Will operate recursively.  Once a subtree is found that is constructor style,
    // everything below it is already good: Only the "top part" of the initializer
    // can be an initializer list, where "top part" can extend for several (or all) levels.

    // see if we have bottomed out in the tree within the initializer-list part
    TIntermAggregate* initList = initializer->getAsAggregate();
    if (! initList || initList->getOp() != EOpNull) {
        // We don't have a list, but if it's a scalar and the 'type' is a
        // composite, we need to lengthen below to make it useful.
        // Otherwise, this is an already formed object to initialize with.
        if (type.isScalar() || !initializer->getType().isScalar())
            return initializer;
        else
            initList = intermediate.makeAggregate(initializer);
    }

    // Of the initializer-list set of nodes, need to process bottom up,
    // so recurse deep, then process on the way up.

    // Go down the tree here...
    if (type.isArray()) {
        // The type's array might be unsized, which could be okay, so base sizes on the size of the aggregate.
        // Later on, initializer execution code will deal with array size logic.
        TType arrayType;
        arrayType.shallowCopy(type);                     // sharing struct stuff is fine
        arrayType.newArraySizes(*type.getArraySizes());  // but get a fresh copy of the array information, to edit below

        // edit array sizes to fill in unsized dimensions
        if (type.isImplicitlySizedArray())
            arrayType.changeOuterArraySize((int)initList->getSequence().size());

        // set unsized array dimensions that can be derived from the initializer's first element
        if (arrayType.isArrayOfArrays() && initList->getSequence().size() > 0) {
            TIntermTyped* firstInit = initList->getSequence()[0]->getAsTyped();
            if (firstInit->getType().isArray() &&
                arrayType.getArraySizes().getNumDims() == firstInit->getType().getArraySizes()->getNumDims() + 1) {
                for (int d = 1; d < arrayType.getArraySizes().getNumDims(); ++d) {
                    if (arrayType.getArraySizes().getDimSize(d) == UnsizedArraySize)
                        arrayType.getArraySizes().setDimSize(d, firstInit->getType().getArraySizes()->getDimSize(d - 1));
                }
            }
        }

        // lengthen list to be long enough
        lengthenList(loc, initList->getSequence(), arrayType.getOuterArraySize());

        // recursively process each element
        TType elementType(arrayType, 0); // dereferenced type
        for (int i = 0; i < arrayType.getOuterArraySize(); ++i) {
            initList->getSequence()[i] = convertInitializerList(loc, elementType, initList->getSequence()[i]->getAsTyped());
            if (initList->getSequence()[i] == nullptr)
                return nullptr;
        }

        return addConstructor(loc, initList, arrayType);
    } else if (type.isStruct()) {
        // lengthen list to be long enough
        lengthenList(loc, initList->getSequence(), static_cast<int>(type.getStruct()->size()));

        if (type.getStruct()->size() != initList->getSequence().size()) {
            error(loc, "wrong number of structure members", "initializer list", "");
            return nullptr;
        }
        for (size_t i = 0; i < type.getStruct()->size(); ++i) {
            initList->getSequence()[i] = convertInitializerList(loc, *(*type.getStruct())[i].type, initList->getSequence()[i]->getAsTyped());
            if (initList->getSequence()[i] == nullptr)
                return nullptr;
        }
    } else if (type.isMatrix()) {
        if (type.computeNumComponents() == (int)initList->getSequence().size()) {
            // This means the matrix is initialized component-wise, rather than as
            // a series of rows and columns.  We can just use the list directly as
            // a constructor; no further processing needed.
        } else {
            // lengthen list to be long enough
            lengthenList(loc, initList->getSequence(), type.getMatrixCols());

            if (type.getMatrixCols() != (int)initList->getSequence().size()) {
                error(loc, "wrong number of matrix columns:", "initializer list", type.getCompleteString().c_str());
                return nullptr;
            }
            TType vectorType(type, 0); // dereferenced type
            for (int i = 0; i < type.getMatrixCols(); ++i) {
                initList->getSequence()[i] = convertInitializerList(loc, vectorType, initList->getSequence()[i]->getAsTyped());
                if (initList->getSequence()[i] == nullptr)
                    return nullptr;
            }
        }
    } else if (type.isVector()) {
        // lengthen list to be long enough
        lengthenList(loc, initList->getSequence(), type.getVectorSize());

        // error check; we're at bottom, so work is finished below
        if (type.getVectorSize() != (int)initList->getSequence().size()) {
            error(loc, "wrong vector size (or rows in a matrix column):", "initializer list", type.getCompleteString().c_str());
            return nullptr;
        }
    } else if (type.isScalar()) {
        // lengthen list to be long enough
        lengthenList(loc, initList->getSequence(), 1);

        if ((int)initList->getSequence().size() != 1) {
            error(loc, "scalar expected one element:", "initializer list", type.getCompleteString().c_str());
            return nullptr;
        }
    } else {
        error(loc, "unexpected initializer-list type:", "initializer list", type.getCompleteString().c_str());
        return nullptr;
    }

    // Now that the subtree is processed, process this node as if the
    // initializer list is a set of arguments to a constructor.
    TIntermNode* emulatedConstructorArguments;
    if (initList->getSequence().size() == 1)
        emulatedConstructorArguments = initList->getSequence()[0];
    else
        emulatedConstructorArguments = initList;

    return addConstructor(loc, emulatedConstructorArguments, type);
}

// Lengthen list to be long enough to cover any gap from the current list size
// to 'size'. If the list is longer, do nothing.
// The value to lengthen with is the default for short lists.
void HlslParseContext::lengthenList(const TSourceLoc& loc, TIntermSequence& list, int size)
{
    for (int c = (int)list.size(); c < size; ++c)
        list.push_back(intermediate.addConstantUnion(0, loc));
}

//
// Test for the correctness of the parameters passed to various constructor functions
// and also convert them to the right data type, if allowed and required.
//
// Returns nullptr for an error or the constructed node (aggregate or typed) for no error.
//
TIntermTyped* HlslParseContext::addConstructor(const TSourceLoc& loc, TIntermNode* node, const TType& type)
{
    if (node == nullptr || node->getAsTyped() == nullptr)
        return nullptr;

    // Handle the idiom "(struct type)0"
    if (type.isStruct() && isZeroConstructor(node))
        return convertInitializerList(loc, type, intermediate.makeAggregate(loc));

    TIntermAggregate* aggrNode = node->getAsAggregate();
    TOperator op = intermediate.mapTypeToConstructorOp(type);

    // Combined texture-sampler constructors are completely semantic checked
    // in constructorTextureSamplerError()
    if (op == EOpConstructTextureSampler)
        return intermediate.setAggregateOperator(aggrNode, op, type, loc);

    TTypeList::const_iterator memberTypes;
    if (op == EOpConstructStruct)
        memberTypes = type.getStruct()->begin();

    TType elementType;
    if (type.isArray()) {
        TType dereferenced(type, 0);
        elementType.shallowCopy(dereferenced);
    } else
        elementType.shallowCopy(type);

    bool singleArg;
    if (aggrNode) {
        if (aggrNode->getOp() != EOpNull || aggrNode->getSequence().size() == 1)
            singleArg = true;
        else
            singleArg = false;
    } else
        singleArg = true;

    TIntermTyped *newNode;
    if (singleArg) {
        // If structure constructor or array constructor is being called
        // for only one parameter inside the structure, we need to call constructAggregate function once.
        if (type.isArray())
            newNode = constructAggregate(node, elementType, 1, node->getLoc());
        else if (op == EOpConstructStruct)
            newNode = constructAggregate(node, *(*memberTypes).type, 1, node->getLoc());
        else
            newNode = constructBuiltIn(type, op, node->getAsTyped(), node->getLoc(), false);

        if (newNode && (type.isArray() || op == EOpConstructStruct))
            newNode = intermediate.setAggregateOperator(newNode, EOpConstructStruct, type, loc);

        return newNode;
    }

    //
    // Handle list of arguments.
    //
    TIntermSequence &sequenceVector = aggrNode->getSequence();    // Stores the information about the parameter to the constructor
    // if the structure constructor contains more than one parameter, then construct
    // each parameter

    int paramCount = 0;  // keeps a track of the constructor parameter number being checked

    // for each parameter to the constructor call, check to see if the right type is passed or convert them
    // to the right type if possible (and allowed).
    // for structure constructors, just check if the right type is passed, no conversion is allowed.

    for (TIntermSequence::iterator p = sequenceVector.begin();
        p != sequenceVector.end(); p++, paramCount++) {
        if (type.isArray())
            newNode = constructAggregate(*p, elementType, paramCount + 1, node->getLoc());
        else if (op == EOpConstructStruct)
            newNode = constructAggregate(*p, *(memberTypes[paramCount]).type, paramCount + 1, node->getLoc());
        else
            newNode = constructBuiltIn(type, op, (*p)->getAsTyped(), node->getLoc(), true);

        if (newNode)
            *p = newNode;
        else
            return nullptr;
    }

    TIntermTyped* constructor = intermediate.setAggregateOperator(aggrNode, op, type, loc);

    return constructor;
}

// Function for constructor implementation. Calls addUnaryMath with appropriate EOp value
// for the parameter to the constructor (passed to this function). Essentially, it converts
// the parameter types correctly. If a constructor expects an int (like ivec2) and is passed a
// float, then float is converted to int.
//
// Returns nullptr for an error or the constructed node.
//
TIntermTyped* HlslParseContext::constructBuiltIn(const TType& type, TOperator op, TIntermTyped* node, const TSourceLoc& loc, bool subset)
{
    TIntermTyped* newNode;
    TOperator basicOp;

    //
    // First, convert types as needed.
    //
    switch (op) {
    case EOpConstructVec2:
    case EOpConstructVec3:
    case EOpConstructVec4:
    case EOpConstructMat2x2:
    case EOpConstructMat2x3:
    case EOpConstructMat2x4:
    case EOpConstructMat3x2:
    case EOpConstructMat3x3:
    case EOpConstructMat3x4:
    case EOpConstructMat4x2:
    case EOpConstructMat4x3:
    case EOpConstructMat4x4:
    case EOpConstructFloat:
        basicOp = EOpConstructFloat;
        break;

    case EOpConstructDVec2:
    case EOpConstructDVec3:
    case EOpConstructDVec4:
    case EOpConstructDMat2x2:
    case EOpConstructDMat2x3:
    case EOpConstructDMat2x4:
    case EOpConstructDMat3x2:
    case EOpConstructDMat3x3:
    case EOpConstructDMat3x4:
    case EOpConstructDMat4x2:
    case EOpConstructDMat4x3:
    case EOpConstructDMat4x4:
    case EOpConstructDouble:
        basicOp = EOpConstructDouble;
        break;

    case EOpConstructIVec2:
    case EOpConstructIVec3:
    case EOpConstructIVec4:
    case EOpConstructInt:
        basicOp = EOpConstructInt;
        break;

    case EOpConstructUVec2:
    case EOpConstructUVec3:
    case EOpConstructUVec4:
    case EOpConstructUint:
        basicOp = EOpConstructUint;
        break;

    case EOpConstructBVec2:
    case EOpConstructBVec3:
    case EOpConstructBVec4:
    case EOpConstructBool:
        basicOp = EOpConstructBool;
        break;

    default:
        error(loc, "unsupported construction", "", "");

        return nullptr;
    }
    newNode = intermediate.addUnaryMath(basicOp, node, node->getLoc());
    if (newNode == nullptr) {
        error(loc, "can't convert", "constructor", "");
        return nullptr;
    }

    //
    // Now, if there still isn't an operation to do the construction, and we need one, add one.
    //

    // Otherwise, skip out early.
    if (subset || (newNode != node && newNode->getType() == type))
        return newNode;

    // setAggregateOperator will insert a new node for the constructor, as needed.
    return intermediate.setAggregateOperator(newNode, op, type, loc);
}

// This function tests for the type of the parameters to the structure or array constructor. Raises
// an error message if the expected type does not match the parameter passed to the constructor.
//
// Returns nullptr for an error or the input node itself if the expected and the given parameter types match.
//
TIntermTyped* HlslParseContext::constructAggregate(TIntermNode* node, const TType& type, int paramCount, const TSourceLoc& loc)
{
    TIntermTyped* converted = intermediate.addConversion(EOpConstructStruct, type, node->getAsTyped());
    if (! converted || converted->getType() != type) {
        error(loc, "", "constructor", "cannot convert parameter %d from '%s' to '%s'", paramCount,
            node->getAsTyped()->getType().getCompleteString().c_str(), type.getCompleteString().c_str());

        return nullptr;
    }

    return converted;
}

//
// Do everything needed to add an interface block.
//
void HlslParseContext::declareBlock(const TSourceLoc& loc, TType& type, const TString* instanceName, TArraySizes* arraySizes)
{
    assert(type.getWritableStruct() != nullptr);

    TTypeList& typeList = *type.getWritableStruct();
    // fix and check for member storage qualifiers and types that don't belong within a block
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TType& memberType = *typeList[member].type;
        TQualifier& memberQualifier = memberType.getQualifier();
        const TSourceLoc& memberLoc = typeList[member].loc;
        globalQualifierFix(memberLoc, memberQualifier);
        memberQualifier.storage = type.getQualifier().storage;
    }

    // This might be a redeclaration of a built-in block.  If so, redeclareBuiltinBlock() will
    // do all the rest.
    // if (! symbolTable.atBuiltInLevel() && builtInName(*blockName)) {
    //    redeclareBuiltinBlock(loc, typeList, *blockName, instanceName, arraySizes);
    //    return;
    //}

    // Make default block qualification, and adjust the member qualifications

    TQualifier defaultQualification;
    switch (type.getQualifier().storage) {
    case EvqUniform:    defaultQualification = globalUniformDefaults;    break;
    case EvqBuffer:     defaultQualification = globalBufferDefaults;     break;
    case EvqVaryingIn:  defaultQualification = globalInputDefaults;      break;
    case EvqVaryingOut: defaultQualification = globalOutputDefaults;     break;
    default:            defaultQualification.clear();                    break;
    }

    // Special case for "push_constant uniform", which has a default of std430,
    // contrary to normal uniform defaults, and can't have a default tracked for it.
    if (type.getQualifier().layoutPushConstant && ! type.getQualifier().hasPacking())
        type.getQualifier().layoutPacking = ElpStd430;

    // fix and check for member layout qualifiers

    mergeObjectLayoutQualifiers(defaultQualification, type.getQualifier(), true);

    bool memberWithLocation = false;
    bool memberWithoutLocation = false;
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier& memberQualifier = typeList[member].type->getQualifier();
        const TSourceLoc& memberLoc = typeList[member].loc;
        if (memberQualifier.hasStream()) {
            if (defaultQualification.layoutStream != memberQualifier.layoutStream)
                error(memberLoc, "member cannot contradict block", "stream", "");
        }

        // "This includes a block's inheritance of the
        // current global default buffer, a block member's inheritance of the block's
        // buffer, and the requirement that any *xfb_buffer* declared on a block
        // member must match the buffer inherited from the block."
        if (memberQualifier.hasXfbBuffer()) {
            if (defaultQualification.layoutXfbBuffer != memberQualifier.layoutXfbBuffer)
                error(memberLoc, "member cannot contradict block (or what block inherited from global)", "xfb_buffer", "");
        }

        if (memberQualifier.hasPacking())
            error(memberLoc, "member of block cannot have a packing layout qualifier", typeList[member].type->getFieldName().c_str(), "");
        if (memberQualifier.hasLocation()) {
            switch (type.getQualifier().storage) {
            case EvqVaryingIn:
            case EvqVaryingOut:
                memberWithLocation = true;
                break;
            default:
                break;
            }
        } else
            memberWithoutLocation = true;
        if (memberQualifier.hasAlign()) {
            if (defaultQualification.layoutPacking != ElpStd140 && defaultQualification.layoutPacking != ElpStd430)
                error(memberLoc, "can only be used with std140 or std430 layout packing", "align", "");
        }

        TQualifier newMemberQualification = defaultQualification;
        mergeQualifiers(newMemberQualification, memberQualifier);
        memberQualifier = newMemberQualification;
    }

    // Process the members
    fixBlockLocations(loc, type.getQualifier(), typeList, memberWithLocation, memberWithoutLocation);
    fixBlockXfbOffsets(type.getQualifier(), typeList);
    fixBlockUniformOffsets(type.getQualifier(), typeList);

    // reverse merge, so that currentBlockQualifier now has all layout information
    // (can't use defaultQualification directly, it's missing other non-layout-default-class qualifiers)
    mergeObjectLayoutQualifiers(type.getQualifier(), defaultQualification, true);

    //
    // Build and add the interface block as a new type named 'blockName'
    //

    // Use the instance name as the interface name if one exists, else the block name.
    const TString& interfaceName = (instanceName && !instanceName->empty()) ? *instanceName : type.getTypeName();

    TType blockType(&typeList, interfaceName, type.getQualifier());
    if (arraySizes)
        blockType.newArraySizes(*arraySizes);

    // Add the variable, as anonymous or named instanceName.
    // Make an anonymous variable if no name was provided.
    if (! instanceName)
        instanceName = NewPoolTString("");

    TVariable& variable = *new TVariable(instanceName, blockType);
    if (! symbolTable.insert(variable)) {
        if (*instanceName == "")
            error(loc, "nameless block contains a member that already has a name at global scope", "" /* blockName->c_str() */, "");
        else
            error(loc, "block instance name redefinition", variable.getName().c_str(), "");

        return;
    }

    // Save it in the AST for linker use.
    trackLinkageDeferred(variable);
}

void HlslParseContext::finalizeGlobalUniformBlockLayout(TVariable& block)
{
    block.getWritableType().getQualifier().layoutPacking = ElpStd140;
    block.getWritableType().getQualifier().layoutMatrix = ElmRowMajor;
    fixBlockUniformOffsets(block.getType().getQualifier(), *block.getWritableType().getWritableStruct());
}

//
// "For a block, this process applies to the entire block, or until the first member
// is reached that has a location layout qualifier. When a block member is declared with a location
// qualifier, its location comes from that qualifier: The member's location qualifier overrides the block-level
// declaration. Subsequent members are again assigned consecutive locations, based on the newest location,
// until the next member declared with a location qualifier. The values used for locations do not have to be
// declared in increasing order."
void HlslParseContext::fixBlockLocations(const TSourceLoc& loc, TQualifier& qualifier, TTypeList& typeList, bool memberWithLocation, bool memberWithoutLocation)
{
    // "If a block has no block-level location layout qualifier, it is required that either all or none of its members
    // have a location layout qualifier, or a compile-time error results."
    if (! qualifier.hasLocation() && memberWithLocation && memberWithoutLocation)
        error(loc, "either the block needs a location, or all members need a location, or no members have a location", "location", "");
    else {
        if (memberWithLocation) {
            // remove any block-level location and make it per *every* member
            int nextLocation = 0;  // by the rule above, initial value is not relevant
            if (qualifier.hasAnyLocation()) {
                nextLocation = qualifier.layoutLocation;
                qualifier.layoutLocation = TQualifier::layoutLocationEnd;
                if (qualifier.hasComponent()) {
                    // "It is a compile-time error to apply the *component* qualifier to a ... block"
                    error(loc, "cannot apply to a block", "component", "");
                }
                if (qualifier.hasIndex()) {
                    error(loc, "cannot apply to a block", "index", "");
                }
            }
            for (unsigned int member = 0; member < typeList.size(); ++member) {
                TQualifier& memberQualifier = typeList[member].type->getQualifier();
                const TSourceLoc& memberLoc = typeList[member].loc;
                if (! memberQualifier.hasLocation()) {
                    if (nextLocation >= (int)TQualifier::layoutLocationEnd)
                        error(memberLoc, "location is too large", "location", "");
                    memberQualifier.layoutLocation = nextLocation;
                    memberQualifier.layoutComponent = 0;
                }
                nextLocation = memberQualifier.layoutLocation + intermediate.computeTypeLocationSize(*typeList[member].type);
            }
        }
    }
}

void HlslParseContext::fixBlockXfbOffsets(TQualifier& qualifier, TTypeList& typeList)
{
    // "If a block is qualified with xfb_offset, all its
    // members are assigned transform feedback buffer offsets. If a block is not qualified with xfb_offset, any
    // members of that block not qualified with an xfb_offset will not be assigned transform feedback buffer
    // offsets."

    if (! qualifier.hasXfbBuffer() || ! qualifier.hasXfbOffset())
        return;

    int nextOffset = qualifier.layoutXfbOffset;
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier& memberQualifier = typeList[member].type->getQualifier();
        bool containsDouble = false;
        int memberSize = intermediate.computeTypeXfbSize(*typeList[member].type, containsDouble);
        // see if we need to auto-assign an offset to this member
        if (! memberQualifier.hasXfbOffset()) {
            // "if applied to an aggregate containing a double, the offset must also be a multiple of 8"
            if (containsDouble)
                RoundToPow2(nextOffset, 8);
            memberQualifier.layoutXfbOffset = nextOffset;
        } else
            nextOffset = memberQualifier.layoutXfbOffset;
        nextOffset += memberSize;
    }

    // The above gave all block members an offset, so we can take it off the block now,
    // which will avoid double counting the offset usage.
    qualifier.layoutXfbOffset = TQualifier::layoutXfbOffsetEnd;
}

// Calculate and save the offset of each block member, using the recursively
// defined block offset rules and the user-provided offset and align.
//
// Also, compute and save the total size of the block. For the block's size, arrayness
// is not taken into account, as each element is backed by a separate buffer.
//
void HlslParseContext::fixBlockUniformOffsets(const TQualifier& qualifier, TTypeList& typeList)
{
    if (! qualifier.isUniformOrBuffer())
        return;
    if (qualifier.layoutPacking != ElpStd140 && qualifier.layoutPacking != ElpStd430)
        return;

    int offset = 0;
    int memberSize;
    for (unsigned int member = 0; member < typeList.size(); ++member) {
        TQualifier& memberQualifier = typeList[member].type->getQualifier();
        const TSourceLoc& memberLoc = typeList[member].loc;

        // "When align is applied to an array, it effects only the start of the array, not the array's internal stride."

        // modify just the children's view of matrix layout, if there is one for this member
        TLayoutMatrix subMatrixLayout = typeList[member].type->getQualifier().layoutMatrix;
        int dummyStride;
        int memberAlignment = intermediate.getBaseAlignment(*typeList[member].type, memberSize, dummyStride,
                                                            qualifier.layoutPacking == ElpStd140,
                                                            subMatrixLayout != ElmNone ? subMatrixLayout == ElmRowMajor
                                                                                       : qualifier.layoutMatrix == ElmRowMajor);
        if (memberQualifier.hasOffset()) {
            // "The specified offset must be a multiple
            // of the base alignment of the type of the block member it qualifies, or a compile-time error results."
            if (! IsMultipleOfPow2(memberQualifier.layoutOffset, memberAlignment))
                error(memberLoc, "must be a multiple of the member's alignment", "offset", "");

            // "The offset qualifier forces the qualified member to start at or after the specified
            // integral-constant expression, which will be its byte offset from the beginning of the buffer.
            // "The actual offset of a member is computed as
            // follows: If offset was declared, start with that offset, otherwise start with the next available offset."
            offset = std::max(offset, memberQualifier.layoutOffset);
        }

        // "The actual alignment of a member will be the greater of the specified align alignment and the standard
        // (e.g., std140) base alignment for the member's type."
        if (memberQualifier.hasAlign())
            memberAlignment = std::max(memberAlignment, memberQualifier.layoutAlign);

        // "If the resulting offset is not a multiple of the actual alignment,
        // increase it to the first offset that is a multiple of
        // the actual alignment."
        RoundToPow2(offset, memberAlignment);
        typeList[member].type->getQualifier().layoutOffset = offset;
        offset += memberSize;
    }
}

// For an identifier that is already declared, add more qualification to it.
void HlslParseContext::addQualifierToExisting(const TSourceLoc& loc, TQualifier qualifier, const TString& identifier)
{
    TSymbol* symbol = symbolTable.find(identifier);
    if (! symbol) {
        error(loc, "identifier not previously declared", identifier.c_str(), "");
        return;
    }
    if (symbol->getAsFunction()) {
        error(loc, "cannot re-qualify a function name", identifier.c_str(), "");
        return;
    }

    if (qualifier.isAuxiliary() ||
        qualifier.isMemory() ||
        qualifier.isInterpolation() ||
        qualifier.hasLayout() ||
        qualifier.storage != EvqTemporary ||
        qualifier.precision != EpqNone) {
        error(loc, "cannot add storage, auxiliary, memory, interpolation, layout, or precision qualifier to an existing variable", identifier.c_str(), "");
        return;
    }

    // For read-only built-ins, add a new symbol for holding the modified qualifier.
    // This will bring up an entire block, if a block type has to be modified (e.g., gl_Position inside a block)
    if (symbol->isReadOnly())
        symbol = symbolTable.copyUp(symbol);

    if (qualifier.invariant) {
        if (intermediate.inIoAccessed(identifier))
            error(loc, "cannot change qualification after use", "invariant", "");
        symbol->getWritableType().getQualifier().invariant = true;
    } else if (qualifier.noContraction) {
        if (intermediate.inIoAccessed(identifier))
            error(loc, "cannot change qualification after use", "precise", "");
        symbol->getWritableType().getQualifier().noContraction = true;
    } else if (qualifier.specConstant) {
        symbol->getWritableType().getQualifier().makeSpecConstant();
        if (qualifier.hasSpecConstantId())
            symbol->getWritableType().getQualifier().layoutSpecConstantId = qualifier.layoutSpecConstantId;
    } else
        warn(loc, "unknown requalification", "", "");
}

void HlslParseContext::addQualifierToExisting(const TSourceLoc& loc, TQualifier qualifier, TIdentifierList& identifiers)
{
    for (unsigned int i = 0; i < identifiers.size(); ++i)
        addQualifierToExisting(loc, qualifier, *identifiers[i]);
}

//
// Update the intermediate for the given input geometry
//
bool HlslParseContext::handleInputGeometry(const TSourceLoc& loc, const TLayoutGeometry& geometry)
{
    switch (geometry) {
    case ElgPoints:             // fall through
    case ElgLines:              // ...
    case ElgTriangles:          // ...
    case ElgLinesAdjacency:     // ...
    case ElgTrianglesAdjacency: // ...
        if (! intermediate.setInputPrimitive(geometry)) {
            error(loc, "input primitive geometry redefinition", TQualifier::getGeometryString(geometry), "");
            return false;
        }
        break;

    default:
        error(loc, "cannot apply to 'in'", TQualifier::getGeometryString(geometry), "");
        return false;
    }

    return true;
}

//
// Update the intermediate for the given output geometry
//
bool HlslParseContext::handleOutputGeometry(const TSourceLoc& loc, const TLayoutGeometry& geometry)
{
    switch (geometry) {
    case ElgPoints:
    case ElgLineStrip:
    case ElgTriangleStrip:
        if (! intermediate.setOutputPrimitive(geometry)) {
            error(loc, "output primitive geometry redefinition", TQualifier::getGeometryString(geometry), "");
            return false;
        }
        break;
    default:
        error(loc, "cannot apply to 'out'", TQualifier::getGeometryString(geometry), "");
        return false;
    }

    return true;
}

//
// Updating default qualifier for the case of a declaration with just a qualifier,
// no type, block, or identifier.
//
void HlslParseContext::updateStandaloneQualifierDefaults(const TSourceLoc& loc, const TPublicType& publicType)
{
    if (publicType.shaderQualifiers.vertices != TQualifier::layoutNotSet) {
        assert(language == EShLangTessControl || language == EShLangGeometry);
        // const char* id = (language == EShLangTessControl) ? "vertices" : "max_vertices";
    }
    if (publicType.shaderQualifiers.invocations != TQualifier::layoutNotSet) {
        if (! intermediate.setInvocations(publicType.shaderQualifiers.invocations))
            error(loc, "cannot change previously set layout value", "invocations", "");
    }
    if (publicType.shaderQualifiers.geometry != ElgNone) {
        if (publicType.qualifier.storage == EvqVaryingIn) {
            switch (publicType.shaderQualifiers.geometry) {
            case ElgPoints:
            case ElgLines:
            case ElgLinesAdjacency:
            case ElgTriangles:
            case ElgTrianglesAdjacency:
            case ElgQuads:
            case ElgIsolines:
                break;
            default:
                error(loc, "cannot apply to input", TQualifier::getGeometryString(publicType.shaderQualifiers.geometry), "");
            }
        } else if (publicType.qualifier.storage == EvqVaryingOut) {
            handleOutputGeometry(loc, publicType.shaderQualifiers.geometry);
        } else
            error(loc, "cannot apply to:", TQualifier::getGeometryString(publicType.shaderQualifiers.geometry), GetStorageQualifierString(publicType.qualifier.storage));
    }
    if (publicType.shaderQualifiers.spacing != EvsNone)
        intermediate.setVertexSpacing(publicType.shaderQualifiers.spacing);
    if (publicType.shaderQualifiers.order != EvoNone)
        intermediate.setVertexOrder(publicType.shaderQualifiers.order);
    if (publicType.shaderQualifiers.pointMode)
        intermediate.setPointMode();
    for (int i = 0; i < 3; ++i) {
        if (publicType.shaderQualifiers.localSize[i] > 1) {
            int max = 0;
            switch (i) {
            case 0: max = resources.maxComputeWorkGroupSizeX; break;
            case 1: max = resources.maxComputeWorkGroupSizeY; break;
            case 2: max = resources.maxComputeWorkGroupSizeZ; break;
            default: break;
            }
            if (intermediate.getLocalSize(i) > (unsigned int)max)
                error(loc, "too large; see gl_MaxComputeWorkGroupSize", "local_size", "");

            // Fix the existing constant gl_WorkGroupSize with this new information.
            TVariable* workGroupSize = getEditableVariable("gl_WorkGroupSize");
            workGroupSize->getWritableConstArray()[i].setUConst(intermediate.getLocalSize(i));
        }
        if (publicType.shaderQualifiers.localSizeSpecId[i] != TQualifier::layoutNotSet) {
            intermediate.setLocalSizeSpecId(i, publicType.shaderQualifiers.localSizeSpecId[i]);
            // Set the workgroup built-in variable as a specialization constant
            TVariable* workGroupSize = getEditableVariable("gl_WorkGroupSize");
            workGroupSize->getWritableType().getQualifier().specConstant = true;
        }
    }
    if (publicType.shaderQualifiers.earlyFragmentTests)
        intermediate.setEarlyFragmentTests();

    const TQualifier& qualifier = publicType.qualifier;

    switch (qualifier.storage) {
    case EvqUniform:
        if (qualifier.hasMatrix())
            globalUniformDefaults.layoutMatrix = qualifier.layoutMatrix;
        if (qualifier.hasPacking())
            globalUniformDefaults.layoutPacking = qualifier.layoutPacking;
        break;
    case EvqBuffer:
        if (qualifier.hasMatrix())
            globalBufferDefaults.layoutMatrix = qualifier.layoutMatrix;
        if (qualifier.hasPacking())
            globalBufferDefaults.layoutPacking = qualifier.layoutPacking;
        break;
    case EvqVaryingIn:
        break;
    case EvqVaryingOut:
        if (qualifier.hasStream())
            globalOutputDefaults.layoutStream = qualifier.layoutStream;
        if (qualifier.hasXfbBuffer())
            globalOutputDefaults.layoutXfbBuffer = qualifier.layoutXfbBuffer;
        if (globalOutputDefaults.hasXfbBuffer() && qualifier.hasXfbStride()) {
            if (! intermediate.setXfbBufferStride(globalOutputDefaults.layoutXfbBuffer, qualifier.layoutXfbStride))
                error(loc, "all stride settings must match for xfb buffer", "xfb_stride", "%d", qualifier.layoutXfbBuffer);
        }
        break;
    default:
        error(loc, "default qualifier requires 'uniform', 'buffer', 'in', or 'out' storage qualification", "", "");
        return;
    }
}

//
// Take the sequence of statements that has been built up since the last case/default,
// put it on the list of top-level nodes for the current (inner-most) switch statement,
// and follow that by the case/default we are on now.  (See switch topology comment on
// TIntermSwitch.)
//
void HlslParseContext::wrapupSwitchSubsequence(TIntermAggregate* statements, TIntermNode* branchNode)
{
    TIntermSequence* switchSequence = switchSequenceStack.back();

    if (statements) {
        statements->setOperator(EOpSequence);
        switchSequence->push_back(statements);
    }
    if (branchNode) {
        // check all previous cases for the same label (or both are 'default')
        for (unsigned int s = 0; s < switchSequence->size(); ++s) {
            TIntermBranch* prevBranch = (*switchSequence)[s]->getAsBranchNode();
            if (prevBranch) {
                TIntermTyped* prevExpression = prevBranch->getExpression();
                TIntermTyped* newExpression = branchNode->getAsBranchNode()->getExpression();
                if (prevExpression == nullptr && newExpression == nullptr)
                    error(branchNode->getLoc(), "duplicate label", "default", "");
                else if (prevExpression != nullptr &&
                    newExpression != nullptr &&
                    prevExpression->getAsConstantUnion() &&
                    newExpression->getAsConstantUnion() &&
                    prevExpression->getAsConstantUnion()->getConstArray()[0].getIConst() ==
                    newExpression->getAsConstantUnion()->getConstArray()[0].getIConst())
                    error(branchNode->getLoc(), "duplicated value", "case", "");
            }
        }
        switchSequence->push_back(branchNode);
    }
}

//
// Turn the top-level node sequence built up of wrapupSwitchSubsequence
// into a switch node.
//
TIntermNode* HlslParseContext::addSwitch(const TSourceLoc& loc, TIntermTyped* expression, TIntermAggregate* lastStatements)
{
    wrapupSwitchSubsequence(lastStatements, nullptr);

    if (expression == nullptr ||
        (expression->getBasicType() != EbtInt && expression->getBasicType() != EbtUint) ||
        expression->getType().isArray() || expression->getType().isMatrix() || expression->getType().isVector())
        error(loc, "condition must be a scalar integer expression", "switch", "");

    // If there is nothing to do, drop the switch but still execute the expression
    TIntermSequence* switchSequence = switchSequenceStack.back();
    if (switchSequence->size() == 0)
        return expression;

    if (lastStatements == nullptr) {
        // emulate a break for error recovery
        lastStatements = intermediate.makeAggregate(intermediate.addBranch(EOpBreak, loc));
        lastStatements->setOperator(EOpSequence);
        switchSequence->push_back(lastStatements);
    }

    TIntermAggregate* body = new TIntermAggregate(EOpSequence);
    body->getSequence() = *switchSequenceStack.back();
    body->setLoc(loc);

    TIntermSwitch* switchNode = new TIntermSwitch(expression, body);
    switchNode->setLoc(loc);

    return switchNode;
}

// Potentially rename shader entry point function
void HlslParseContext::renameShaderFunction(TString*& name) const
{
    // Replace the entry point name given in the shader with the real entry point name,
    // if there is a substitution.
    if (name != nullptr && *name == sourceEntryPointName)
        name = NewPoolTString(intermediate.getEntryPointName().c_str());
}

// post-processing
void HlslParseContext::finish()
{
    addInterstageIoToLinkage();

    TParseContextBase::finish();
}

} // end namespace glslang
