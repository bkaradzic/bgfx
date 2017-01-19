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
//    Neither the name of Google, Inc., nor the names of its
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

//
// This is a set of mutually recursive methods implementing the HLSL grammar.
// Generally, each returns
//  - through an argument: a type specifically appropriate to which rule it
//    recognized
//  - through the return value: true/false to indicate whether or not it
//    recognized its rule
//
// As much as possible, only grammar recognition should happen in this file,
// with all other work being farmed out to hlslParseHelper.cpp, which in turn
// will build the AST.
//
// The next token, yet to be "accepted" is always sitting in 'token'.
// When a method says it accepts a rule, that means all tokens involved
// in the rule will have been consumed, and none left in 'token'.
//

#include "hlslTokens.h"
#include "hlslGrammar.h"
#include "hlslAttributes.h"

namespace glslang {

// Root entry point to this recursive decent parser.
// Return true if compilation unit was successfully accepted.
bool HlslGrammar::parse()
{
    advanceToken();
    return acceptCompilationUnit();
}

void HlslGrammar::expected(const char* syntax)
{
    parseContext.error(token.loc, "Expected", syntax, "");
}

void HlslGrammar::unimplemented(const char* error)
{
    parseContext.error(token.loc, "Unimplemented", error, "");
}

// Only process the next token if it is an identifier.
// Return true if it was an identifier.
bool HlslGrammar::acceptIdentifier(HlslToken& idToken)
{
    if (peekTokenClass(EHTokIdentifier)) {
        idToken = token;
        advanceToken();
        return true;
    }

    // Even though "sample", "bool", "float", etc keywords (for types, interpolation modifiers),
    // they ARE still accepted as identifiers.  This is not a dense space: e.g, "void" is not a
    // valid identifier, nor is "linear".  This code special cases the known instances of this, so
    // e.g, "int sample;" or "float float;" is accepted.  Other cases can be added here if needed.

    TString* idString = nullptr;
    switch (peek()) {
    case EHTokSample:     idString = NewPoolTString("sample");     break;
    case EHTokHalf:       idString = NewPoolTString("half");       break;
    case EHTokBool:       idString = NewPoolTString("bool");       break;
    case EHTokFloat:      idString = NewPoolTString("float");      break;
    case EHTokDouble:     idString = NewPoolTString("double");     break;
    case EHTokInt:        idString = NewPoolTString("int");        break;
    case EHTokUint:       idString = NewPoolTString("uint");       break;
    case EHTokMin16float: idString = NewPoolTString("min16float"); break;
    case EHTokMin10float: idString = NewPoolTString("min10float"); break;
    case EHTokMin16int:   idString = NewPoolTString("min16int");   break;
    case EHTokMin12int:   idString = NewPoolTString("min12int");   break;
    default:
        return false;
    }

    token.string     = idString;
    token.tokenClass = EHTokIdentifier;
    token.symbol     = nullptr;
    idToken          = token;

    advanceToken();

    return true;
}

// compilationUnit
//      : list of externalDeclaration
//      |   SEMICOLONS
//
bool HlslGrammar::acceptCompilationUnit()
{
    TIntermNode* unitNode = nullptr;

    while (! peekTokenClass(EHTokNone)) {
        // HLSL allows semicolons between global declarations, e.g, between functions.
        if (acceptTokenClass(EHTokSemicolon))
            continue;

        // externalDeclaration
        TIntermNode* declarationNode;
        if (! acceptDeclaration(declarationNode))
            return false;

        // hook it up
        unitNode = intermediate.growAggregate(unitNode, declarationNode);
    }

    // set root of AST
    intermediate.setTreeRoot(unitNode);

    return true;
}

// sampler_state
//      : LEFT_BRACE [sampler_state_assignment ... ] RIGHT_BRACE
//
// sampler_state_assignment
//     : sampler_state_identifier EQUAL value SEMICOLON
//
// sampler_state_identifier
//     : ADDRESSU
//     | ADDRESSV
//     | ADDRESSW
//     | BORDERCOLOR
//     | FILTER
//     | MAXANISOTROPY
//     | MAXLOD
//     | MINLOD
//     | MIPLODBIAS
//
bool HlslGrammar::acceptSamplerState()
{
    // TODO: this should be genericized to accept a list of valid tokens and
    // return token/value pairs.  Presently it is specific to texture values.

    if (! acceptTokenClass(EHTokLeftBrace))
        return true;

    parseContext.warn(token.loc, "unimplemented", "immediate sampler state", "");

    do {
        // read state name
        HlslToken state;
        if (! acceptIdentifier(state))
            break;  // end of list

        // FXC accepts any case
        TString stateName = *state.string;
        std::transform(stateName.begin(), stateName.end(), stateName.begin(), ::tolower);

        if (! acceptTokenClass(EHTokAssign)) {
            expected("assign");
            return false;
        }

        if (stateName == "minlod" || stateName == "maxlod") {
            if (! peekTokenClass(EHTokIntConstant)) {
                expected("integer");
                return false;
            }

            TIntermTyped* lod = nullptr;
            if (! acceptLiteral(lod))  // should never fail, since we just looked for an integer
                return false;
        } else if (stateName == "maxanisotropy") {
            if (! peekTokenClass(EHTokIntConstant)) {
                expected("integer");
                return false;
            }

            TIntermTyped* maxAnisotropy = nullptr;
            if (! acceptLiteral(maxAnisotropy))  // should never fail, since we just looked for an integer
                return false;
        } else if (stateName == "filter") {
            HlslToken filterMode;
            if (! acceptIdentifier(filterMode)) {
                expected("filter mode");
                return false;
            }
        } else if (stateName == "addressu" || stateName == "addressv" || stateName == "addressw") {
            HlslToken addrMode;
            if (! acceptIdentifier(addrMode)) {
                expected("texture address mode");
                return false;
            }
        } else if (stateName == "miplodbias") {
            TIntermTyped* lodBias = nullptr;
            if (! acceptLiteral(lodBias)) {
                expected("lod bias");
                return false;
            }
        } else if (stateName == "bordercolor") {
            return false;
        } else {
            expected("texture state");
            return false;
        }

        // SEMICOLON
        if (! acceptTokenClass(EHTokSemicolon)) {
            expected("semicolon");
            return false;
        }
    } while (true);

    if (! acceptTokenClass(EHTokRightBrace))
        return false;

    return true;
}

// sampler_declaration_dx9
//    : SAMPLER identifier EQUAL sampler_type sampler_state
//
bool HlslGrammar::acceptSamplerDeclarationDX9(TType& /*type*/)
{
    if (! acceptTokenClass(EHTokSampler))
        return false;

    // TODO: remove this when DX9 style declarations are implemented.
    unimplemented("Direct3D 9 sampler declaration");

    // read sampler name
    HlslToken name;
    if (! acceptIdentifier(name)) {
        expected("sampler name");
        return false;
    }

    if (! acceptTokenClass(EHTokAssign)) {
        expected("=");
        return false;
    }

    return false;
}

// declaration
//      : sampler_declaration_dx9 post_decls SEMICOLON
//      | fully_specified_type declarator_list SEMICOLON
//      | fully_specified_type identifier function_parameters post_decls compound_statement  // function definition
//      | fully_specified_type identifier sampler_state post_decls compound_statement        // sampler definition
//      | typedef declaration
//
// declarator_list
//      : declarator COMMA declarator COMMA declarator...  // zero or more declarators
//
// declarator
//      : identifier array_specifier post_decls
//      | identifier array_specifier post_decls EQUAL assignment_expression
//      | identifier function_parameters post_decls                                          // function prototype
//
// Parsing has to go pretty far in to know whether it's a variable, prototype, or
// function definition, so the implementation below doesn't perfectly divide up the grammar
// as above.  (The 'identifier' in the first item in init_declarator list is the
// same as 'identifier' for function declarations.)
//
// 'node' could get populated if the declaration creates code, like an initializer
// or a function body.
//
bool HlslGrammar::acceptDeclaration(TIntermNode*& node)
{
    node = nullptr;
    bool list = false;

    // attributes
    TAttributeMap attributes;
    acceptAttributes(attributes);

    // typedef
    bool typedefDecl = acceptTokenClass(EHTokTypedef);

    TType declaredType;

    // DX9 sampler declaration use a different syntax
    // DX9 shaders need to run through HLSL compiler (fxc) via a back compat mode, it isn't going to
    // be possible to simultaneously compile D3D10+ style shaders and DX9 shaders. If we want to compile DX9
    // HLSL shaders, this will have to be a master level switch
    // As such, the sampler keyword in D3D10+ turns into an automatic sampler type, and is commonly used
    // For that reason, this line is commented out

   // if (acceptSamplerDeclarationDX9(declaredType))
   //     return true;

    // fully_specified_type
    if (! acceptFullySpecifiedType(declaredType))
        return false;

    // identifier
    HlslToken idToken;
    while (acceptIdentifier(idToken)) {
        TString* fnName = idToken.string;

        // Potentially rename shader entry point function.  No-op most of the time.
        parseContext.renameShaderFunction(fnName);

        // function_parameters
        TFunction& function = *new TFunction(fnName, declaredType);
        if (acceptFunctionParameters(function)) {
            // post_decls
            acceptPostDecls(function.getWritableType().getQualifier());

            // compound_statement (function body definition) or just a prototype?
            if (peekTokenClass(EHTokLeftBrace)) {
                if (list)
                    parseContext.error(idToken.loc, "function body can't be in a declarator list", "{", "");
                if (typedefDecl)
                    parseContext.error(idToken.loc, "function body can't be in a typedef", "{", "");
                return acceptFunctionDefinition(function, node, attributes);
            } else {
                if (typedefDecl)
                    parseContext.error(idToken.loc, "function typedefs not implemented", "{", "");
                parseContext.handleFunctionDeclarator(idToken.loc, function, true);
            }
        } else {
            // A variable declaration. Fix the storage qualifier if it's a global.
            if (declaredType.getQualifier().storage == EvqTemporary && parseContext.symbolTable.atGlobalLevel())
                declaredType.getQualifier().storage = EvqUniform;

            // We can handle multiple variables per type declaration, so
            // the number of types can expand when arrayness is different.
            TType variableType;
            variableType.shallowCopy(declaredType);

            // recognize array_specifier
            TArraySizes* arraySizes = nullptr;
            acceptArraySpecifier(arraySizes);

            // Fix arrayness in the variableType
            if (declaredType.isImplicitlySizedArray()) {
                // Because "int[] a = int[2](...), b = int[3](...)" makes two arrays a and b
                // of different sizes, for this case sharing the shallow copy of arrayness
                // with the parseType oversubscribes it, so get a deep copy of the arrayness.
                variableType.newArraySizes(declaredType.getArraySizes());
            }
            if (arraySizes || variableType.isArray()) {
                // In the most general case, arrayness is potentially coming both from the
                // declared type and from the variable: "int[] a[];" or just one or the other.
                // Merge it all to the variableType, so all arrayness is part of the variableType.
                parseContext.arrayDimMerge(variableType, arraySizes);
            }

            // samplers accept immediate sampler state
            if (variableType.getBasicType() == EbtSampler) {
                if (! acceptSamplerState())
                    return false;
            }

            // post_decls
            acceptPostDecls(variableType.getQualifier());

            // EQUAL assignment_expression
            TIntermTyped* expressionNode = nullptr;
            if (acceptTokenClass(EHTokAssign)) {
                if (typedefDecl)
                    parseContext.error(idToken.loc, "can't have an initializer", "typedef", "");
                if (! acceptAssignmentExpression(expressionNode)) {
                    expected("initializer");
                    return false;
                }
            }

            // Hand off the actual declaration

            // TODO: things scoped within an annotation need their own name space;
            // TODO: strings are not yet handled.
            if (variableType.getBasicType() != EbtString && parseContext.getAnnotationNestingLevel() == 0) {
                if (typedefDecl)
                    parseContext.declareTypedef(idToken.loc, *idToken.string, variableType);
                else if (variableType.getBasicType() == EbtBlock)
                    parseContext.declareBlock(idToken.loc, variableType, idToken.string);
                else {
                    if (variableType.getQualifier().storage == EvqUniform && ! variableType.containsOpaque()) {
                        // this isn't really an individual variable, but a member of the $Global buffer
                        parseContext.growGlobalUniformBlock(idToken.loc, variableType, *idToken.string);
                    } else {
                        // Declare the variable and add any initializer code to the AST.
                        // The top-level node is always made into an aggregate, as that's
                        // historically how the AST has been.
                        node = intermediate.growAggregate(node,
                                                          parseContext.declareVariable(idToken.loc, *idToken.string, variableType,
                                                                                       expressionNode),
                                                          idToken.loc);
                    }
                }
            }
        }

        if (acceptTokenClass(EHTokComma)) {
            list = true;
            continue;
        }
    };

    // The top-level node is a sequence.
    if (node != nullptr)
        node->getAsAggregate()->setOperator(EOpSequence);

    // SEMICOLON
    if (! acceptTokenClass(EHTokSemicolon)) {
        // This may have been a false detection of what appeared to be a declaration, but
        // was actually an assignment such as "float = 4", where "float" is an identifier.
        // We put the token back to let further parsing happen for cases where that may
        // happen.  This errors on the side of caution, and mostly triggers the error.

        if (peek() == EHTokAssign || peek() == EHTokLeftBracket || peek() == EHTokDot || peek() == EHTokComma)
            recedeToken();
        else
            expected(";");
        return false;
    }

    return true;
}

// control_declaration
//      : fully_specified_type identifier EQUAL expression
//
bool HlslGrammar::acceptControlDeclaration(TIntermNode*& node)
{
    node = nullptr;

    // fully_specified_type
    TType type;
    if (! acceptFullySpecifiedType(type))
        return false;

    // identifier
    HlslToken idToken;
    if (! acceptIdentifier(idToken)) {
        expected("identifier");
        return false;
    }

    // EQUAL
    TIntermTyped* expressionNode = nullptr;
    if (! acceptTokenClass(EHTokAssign)) {
        expected("=");
        return false;
    }

    // expression
    if (! acceptExpression(expressionNode)) {
        expected("initializer");
        return false;
    }

    node = parseContext.declareVariable(idToken.loc, *idToken.string, type, expressionNode);

    return true;
}

// fully_specified_type
//      : type_specifier
//      | type_qualifier type_specifier
//
bool HlslGrammar::acceptFullySpecifiedType(TType& type)
{
    // type_qualifier
    TQualifier qualifier;
    qualifier.clear();
    if (! acceptQualifier(qualifier))
        return false;
    TSourceLoc loc = token.loc;

    // type_specifier
    if (! acceptType(type)) {
        // If this is not a type, we may have inadvertently gone down a wrong path
        // by parsing "sample", which can be treated like either an identifier or a
        // qualifier.  Back it out, if we did.
        if (qualifier.sample)
            recedeToken();

        return false;
    }
    if (type.getBasicType() == EbtBlock) {
        // the type was a block, which set some parts of the qualifier
        parseContext.mergeQualifiers(type.getQualifier(), qualifier);
        // further, it can create an anonymous instance of the block
        if (peekTokenClass(EHTokSemicolon))
            parseContext.declareBlock(loc, type);
    } else {
        // Some qualifiers are set when parsing the type.  Merge those with
        // whatever comes from acceptQualifier.
        assert(qualifier.layoutFormat == ElfNone);

        qualifier.layoutFormat = type.getQualifier().layoutFormat;
        qualifier.precision    = type.getQualifier().precision;

        if (type.getQualifier().storage == EvqVaryingOut)
            qualifier.storage      = type.getQualifier().storage;

        type.getQualifier()    = qualifier;
    }

    return true;
}

// type_qualifier
//      : qualifier qualifier ...
//
// Zero or more of these, so this can't return false.
//
bool HlslGrammar::acceptQualifier(TQualifier& qualifier)
{
    do {
        switch (peek()) {
        case EHTokStatic:
            qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
            break;
        case EHTokExtern:
            // TODO: no meaning in glslang?
            break;
        case EHTokShared:
            // TODO: hint
            break;
        case EHTokGroupShared:
            qualifier.storage = EvqShared;
            break;
        case EHTokUniform:
            qualifier.storage = EvqUniform;
            break;
        case EHTokConst:
            qualifier.storage = EvqConst;
            break;
        case EHTokVolatile:
            qualifier.volatil = true;
            break;
        case EHTokLinear:
            qualifier.smooth = true;
            break;
        case EHTokCentroid:
            qualifier.centroid = true;
            break;
        case EHTokNointerpolation:
            qualifier.flat = true;
            break;
        case EHTokNoperspective:
            qualifier.nopersp = true;
            break;
        case EHTokSample:
            qualifier.sample = true;
            break;
        case EHTokRowMajor:
            qualifier.layoutMatrix = ElmColumnMajor;
            break;
        case EHTokColumnMajor:
            qualifier.layoutMatrix = ElmRowMajor;
            break;
        case EHTokPrecise:
            qualifier.noContraction = true;
            break;
        case EHTokIn:
            qualifier.storage = EvqIn;
            break;
        case EHTokOut:
            qualifier.storage = EvqOut;
            break;
        case EHTokInOut:
            qualifier.storage = EvqInOut;
            break;
        case EHTokLayout:
            if (! acceptLayoutQualifierList(qualifier))
                return false;
            continue;

        // GS geometries: these are specified on stage input variables, and are an error (not verified here)
        // for output variables.
        case EHTokPoint:
            qualifier.storage = EvqIn;
            if (!parseContext.handleInputGeometry(token.loc, ElgPoints))
                return false;
            break;
        case EHTokLine:
            qualifier.storage = EvqIn;
            if (!parseContext.handleInputGeometry(token.loc, ElgLines))
                return false;
            break;
        case EHTokTriangle:
            qualifier.storage = EvqIn;
            if (!parseContext.handleInputGeometry(token.loc, ElgTriangles))
                return false;
            break;
        case EHTokLineAdj:
            qualifier.storage = EvqIn;
            if (!parseContext.handleInputGeometry(token.loc, ElgLinesAdjacency))
                return false;
            break;
        case EHTokTriangleAdj:
            qualifier.storage = EvqIn;
            if (!parseContext.handleInputGeometry(token.loc, ElgTrianglesAdjacency))
                return false;
            break;

        default:
            return true;
        }
        advanceToken();
    } while (true);
}

// layout_qualifier_list
//      : LAYOUT LEFT_PAREN layout_qualifier COMMA layout_qualifier ... RIGHT_PAREN
//
// layout_qualifier
//      : identifier
//      | identifier EQUAL expression
//
// Zero or more of these, so this can't return false.
//
bool HlslGrammar::acceptLayoutQualifierList(TQualifier& qualifier)
{
    if (! acceptTokenClass(EHTokLayout))
        return false;

    // LEFT_PAREN
    if (! acceptTokenClass(EHTokLeftParen))
        return false;

    do {
        // identifier
        HlslToken idToken;
        if (! acceptIdentifier(idToken))
            break;

        // EQUAL expression
        if (acceptTokenClass(EHTokAssign)) {
            TIntermTyped* expr;
            if (! acceptConditionalExpression(expr)) {
                expected("expression");
                return false;
            }
            parseContext.setLayoutQualifier(idToken.loc, qualifier, *idToken.string, expr);
        } else
            parseContext.setLayoutQualifier(idToken.loc, qualifier, *idToken.string);

        // COMMA
        if (! acceptTokenClass(EHTokComma))
            break;
    } while (true);

    // RIGHT_PAREN
    if (! acceptTokenClass(EHTokRightParen)) {
        expected(")");
        return false;
    }

    return true;
}

// template_type
//      : FLOAT
//      | DOUBLE
//      | INT
//      | DWORD
//      | UINT
//      | BOOL
//
bool HlslGrammar::acceptTemplateVecMatBasicType(TBasicType& basicType)
{
    switch (peek()) {
    case EHTokFloat:
        basicType = EbtFloat;
        break;
    case EHTokDouble:
        basicType = EbtDouble;
        break;
    case EHTokInt:
    case EHTokDword:
        basicType = EbtInt;
        break;
    case EHTokUint:
        basicType = EbtUint;
        break;
    case EHTokBool:
        basicType = EbtBool;
        break;
    default:
        return false;
    }

    advanceToken();

    return true;
}

// vector_template_type
//      : VECTOR
//      | VECTOR LEFT_ANGLE template_type COMMA integer_literal RIGHT_ANGLE
//
bool HlslGrammar::acceptVectorTemplateType(TType& type)
{
    if (! acceptTokenClass(EHTokVector))
        return false;

    if (! acceptTokenClass(EHTokLeftAngle)) {
        // in HLSL, 'vector' alone means float4.
        new(&type) TType(EbtFloat, EvqTemporary, 4);
        return true;
    }

    TBasicType basicType;
    if (! acceptTemplateVecMatBasicType(basicType)) {
        expected("scalar type");
        return false;
    }

    // COMMA
    if (! acceptTokenClass(EHTokComma)) {
        expected(",");
        return false;
    }

    // integer
    if (! peekTokenClass(EHTokIntConstant)) {
        expected("literal integer");
        return false;
    }

    TIntermTyped* vecSize;
    if (! acceptLiteral(vecSize))
        return false;

    const int vecSizeI = vecSize->getAsConstantUnion()->getConstArray()[0].getIConst();

    new(&type) TType(basicType, EvqTemporary, vecSizeI);

    if (vecSizeI == 1)
        type.makeVector();

    if (!acceptTokenClass(EHTokRightAngle)) {
        expected("right angle bracket");
        return false;
    }

    return true;
}

// matrix_template_type
//      : MATRIX
//      | MATRIX LEFT_ANGLE template_type COMMA integer_literal COMMA integer_literal RIGHT_ANGLE
//
bool HlslGrammar::acceptMatrixTemplateType(TType& type)
{
    if (! acceptTokenClass(EHTokMatrix))
        return false;

    if (! acceptTokenClass(EHTokLeftAngle)) {
        // in HLSL, 'matrix' alone means float4x4.
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 4);
        return true;
    }

    TBasicType basicType;
    if (! acceptTemplateVecMatBasicType(basicType)) {
        expected("scalar type");
        return false;
    }

    // COMMA
    if (! acceptTokenClass(EHTokComma)) {
        expected(",");
        return false;
    }

    // integer rows
    if (! peekTokenClass(EHTokIntConstant)) {
        expected("literal integer");
        return false;
    }

    TIntermTyped* rows;
    if (! acceptLiteral(rows))
        return false;

    // COMMA
    if (! acceptTokenClass(EHTokComma)) {
        expected(",");
        return false;
    }

    // integer cols
    if (! peekTokenClass(EHTokIntConstant)) {
        expected("literal integer");
        return false;
    }

    TIntermTyped* cols;
    if (! acceptLiteral(cols))
        return false;

    new(&type) TType(basicType, EvqTemporary, 0,
                     rows->getAsConstantUnion()->getConstArray()[0].getIConst(),
                     cols->getAsConstantUnion()->getConstArray()[0].getIConst());

    if (!acceptTokenClass(EHTokRightAngle)) {
        expected("right angle bracket");
        return false;
    }

    return true;
}

// layout_geometry
//      : LINESTREAM
//      | POINTSTREAM
//      | TRIANGLESTREAM
//
bool HlslGrammar::acceptOutputPrimitiveGeometry(TLayoutGeometry& geometry)
{
    // read geometry type
    const EHlslTokenClass geometryType = peek();

    switch (geometryType) {
    case EHTokPointStream:    geometry = ElgPoints;        break;
    case EHTokLineStream:     geometry = ElgLineStrip;     break;
    case EHTokTriangleStream: geometry = ElgTriangleStrip; break;
    default:
        return false;  // not a layout geometry
    }

    advanceToken();  // consume the layout keyword
    return true;
}

// stream_out_template_type
//      : output_primitive_geometry_type LEFT_ANGLE type RIGHT_ANGLE
//
bool HlslGrammar::acceptStreamOutTemplateType(TType& type, TLayoutGeometry& geometry)
{
    geometry = ElgNone;

    if (! acceptOutputPrimitiveGeometry(geometry))
        return false;

    if (! acceptTokenClass(EHTokLeftAngle))
        return false;

    if (! acceptType(type)) {
        expected("stream output type");
        return false;
    }

    type.getQualifier().storage = EvqVaryingOut;

    if (! acceptTokenClass(EHTokRightAngle)) {
        expected("right angle bracket");
        return false;
    }

    return true;
}

// annotations
//      : LEFT_ANGLE declaration SEMI_COLON ... declaration SEMICOLON RIGHT_ANGLE
//
bool HlslGrammar::acceptAnnotations(TQualifier&)
{
    if (! acceptTokenClass(EHTokLeftAngle))
        return false;

    // note that we are nesting a name space
    parseContext.nestAnnotations();

    // declaration SEMI_COLON ... declaration SEMICOLON RIGHT_ANGLE
    do {
        // eat any extra SEMI_COLON; don't know if the grammar calls for this or not
        while (acceptTokenClass(EHTokSemicolon))
            ;

        if (acceptTokenClass(EHTokRightAngle))
            break;

        // declaration
        TIntermNode* node;
        if (! acceptDeclaration(node)) {
            expected("declaration in annotation");
            return false;
        }
    } while (true);

    parseContext.unnestAnnotations();
    return true;
}

// sampler_type
//      : SAMPLER
//      | SAMPLER1D
//      | SAMPLER2D
//      | SAMPLER3D
//      | SAMPLERCUBE
//      | SAMPLERSTATE
//      | SAMPLERCOMPARISONSTATE
bool HlslGrammar::acceptSamplerType(TType& type)
{
    // read sampler type
    const EHlslTokenClass samplerType = peek();

    // TODO: for DX9
    // TSamplerDim dim = EsdNone;

    bool isShadow = false;

    switch (samplerType) {
    case EHTokSampler:      break;
    case EHTokSampler1d:    /*dim = Esd1D*/; break;
    case EHTokSampler2d:    /*dim = Esd2D*/; break;
    case EHTokSampler3d:    /*dim = Esd3D*/; break;
    case EHTokSamplerCube:  /*dim = EsdCube*/; break;
    case EHTokSamplerState: break;
    case EHTokSamplerComparisonState: isShadow = true; break;
    default:
        return false;  // not a sampler declaration
    }

    advanceToken();  // consume the sampler type keyword

    TArraySizes* arraySizes = nullptr; // TODO: array

    TSampler sampler;
    sampler.setPureSampler(isShadow);

    type.shallowCopy(TType(sampler, EvqUniform, arraySizes));

    return true;
}

// texture_type
//      | BUFFER
//      | TEXTURE1D
//      | TEXTURE1DARRAY
//      | TEXTURE2D
//      | TEXTURE2DARRAY
//      | TEXTURE3D
//      | TEXTURECUBE
//      | TEXTURECUBEARRAY
//      | TEXTURE2DMS
//      | TEXTURE2DMSARRAY
//      | RWBUFFER
//      | RWTEXTURE1D
//      | RWTEXTURE1DARRAY
//      | RWTEXTURE2D
//      | RWTEXTURE2DARRAY
//      | RWTEXTURE3D

bool HlslGrammar::acceptTextureType(TType& type)
{
    const EHlslTokenClass textureType = peek();

    TSamplerDim dim = EsdNone;
    bool array = false;
    bool ms    = false;
    bool image = false;

    switch (textureType) {
    case EHTokBuffer:            dim = EsdBuffer;                      break;
    case EHTokTexture1d:         dim = Esd1D;                          break;
    case EHTokTexture1darray:    dim = Esd1D; array = true;            break;
    case EHTokTexture2d:         dim = Esd2D;                          break;
    case EHTokTexture2darray:    dim = Esd2D; array = true;            break;
    case EHTokTexture3d:         dim = Esd3D;                          break;
    case EHTokTextureCube:       dim = EsdCube;                        break;
    case EHTokTextureCubearray:  dim = EsdCube; array = true;          break;
    case EHTokTexture2DMS:       dim = Esd2D; ms = true;               break;
    case EHTokTexture2DMSarray:  dim = Esd2D; array = true; ms = true; break;
    case EHTokRWBuffer:          dim = EsdBuffer; image=true;          break;
    case EHTokRWTexture1d:       dim = Esd1D; array=false; image=true; break;
    case EHTokRWTexture1darray:  dim = Esd1D; array=true;  image=true; break;
    case EHTokRWTexture2d:       dim = Esd2D; array=false; image=true; break;
    case EHTokRWTexture2darray:  dim = Esd2D; array=true;  image=true; break;
    case EHTokRWTexture3d:       dim = Esd3D; array=false; image=true; break;
    default:
        return false;  // not a texture declaration
    }

    advanceToken();  // consume the texture object keyword

    TType txType(EbtFloat, EvqUniform, 4); // default type is float4

    TIntermTyped* msCount = nullptr;

    // texture type: required for multisample types and RWBuffer/RWTextures!
    if (acceptTokenClass(EHTokLeftAngle)) {
        if (! acceptType(txType)) {
            expected("scalar or vector type");
            return false;
        }

        const TBasicType basicRetType = txType.getBasicType() ;

        if (basicRetType != EbtFloat && basicRetType != EbtUint && basicRetType != EbtInt) {
            unimplemented("basic type in texture");
            return false;
        }

        // Buffers can handle small mats if they fit in 4 components
        if (dim == EsdBuffer && txType.isMatrix()) {
            if ((txType.getMatrixCols() * txType.getMatrixRows()) > 4) {
                expected("components < 4 in matrix buffer type");
                return false;
            }

            // TODO: except we don't handle it yet...
            unimplemented("matrix type in buffer");
            return false;
        }

        if (!txType.isScalar() && !txType.isVector()) {
            expected("scalar or vector type");
            return false;
        }

        if (ms && acceptTokenClass(EHTokComma)) {
            // read sample count for multisample types, if given
            if (! peekTokenClass(EHTokIntConstant)) {
                expected("multisample count");
                return false;
            }

            if (! acceptLiteral(msCount))  // should never fail, since we just found an integer
                return false;
        }

        if (! acceptTokenClass(EHTokRightAngle)) {
            expected("right angle bracket");
            return false;
        }
    } else if (ms) {
        expected("texture type for multisample");
        return false;
    } else if (image) {
        expected("type for RWTexture/RWBuffer");
        return false;
    }

    TArraySizes* arraySizes = nullptr;
    const bool shadow = false; // declared on the sampler

    TSampler sampler;
    TLayoutFormat format = ElfNone;

    // Buffer, RWBuffer and RWTexture (images) require a TLayoutFormat.  We handle only a limit set.
    if (image || dim == EsdBuffer)
        format = parseContext.getLayoutFromTxType(token.loc, txType);

    // Non-image Buffers are combined
    if (dim == EsdBuffer && !image) {
        sampler.set(txType.getBasicType(), dim, array);
    } else {
        // DX10 textures are separated.  TODO: DX9.
        if (image) {
            sampler.setImage(txType.getBasicType(), dim, array, shadow, ms);
        } else {
            sampler.setTexture(txType.getBasicType(), dim, array, shadow, ms);
        }
    }

    // Remember the declared vector size.
    sampler.vectorSize = txType.getVectorSize();

    type.shallowCopy(TType(sampler, EvqUniform, arraySizes));
    type.getQualifier().layoutFormat = format;

    return true;
}

// If token is for a type, update 'type' with the type information,
// and return true and advance.
// Otherwise, return false, and don't advance
bool HlslGrammar::acceptType(TType& type)
{
    // Basic types for min* types, broken out here in case of future
    // changes, e.g, to use native halfs.
    static const TBasicType min16float_bt = EbtFloat;
    static const TBasicType min10float_bt = EbtFloat;
    static const TBasicType half_bt       = EbtFloat;
    static const TBasicType min16int_bt   = EbtInt;
    static const TBasicType min12int_bt   = EbtInt;
    static const TBasicType min16uint_bt  = EbtUint;

    switch (peek()) {
    case EHTokVector:
        return acceptVectorTemplateType(type);
        break;

    case EHTokMatrix:
        return acceptMatrixTemplateType(type);
        break;

    case EHTokPointStream:            // fall through
    case EHTokLineStream:             // ...
    case EHTokTriangleStream:         // ...
        {
            TLayoutGeometry geometry;
            if (! acceptStreamOutTemplateType(type, geometry))
                return false;

            if (! parseContext.handleOutputGeometry(token.loc, geometry))
                return false;

            return true;
        }

    case EHTokSampler:                // fall through
    case EHTokSampler1d:              // ...
    case EHTokSampler2d:              // ...
    case EHTokSampler3d:              // ...
    case EHTokSamplerCube:            // ...
    case EHTokSamplerState:           // ...
    case EHTokSamplerComparisonState: // ...
        return acceptSamplerType(type);
        break;

    case EHTokBuffer:                 // fall through
    case EHTokTexture1d:              // ...
    case EHTokTexture1darray:         // ...
    case EHTokTexture2d:              // ...
    case EHTokTexture2darray:         // ...
    case EHTokTexture3d:              // ...
    case EHTokTextureCube:            // ...
    case EHTokTextureCubearray:       // ...
    case EHTokTexture2DMS:            // ...
    case EHTokTexture2DMSarray:       // ...
    case EHTokRWTexture1d:            // ...
    case EHTokRWTexture1darray:       // ...
    case EHTokRWTexture2d:            // ...
    case EHTokRWTexture2darray:       // ...
    case EHTokRWTexture3d:            // ...
    case EHTokRWBuffer:               // ...
        return acceptTextureType(type);
        break;

    case EHTokStruct:
    case EHTokCBuffer:
    case EHTokTBuffer:
        return acceptStruct(type);
        break;

    case EHTokIdentifier:
        // An identifier could be for a user-defined type.
        // Note we cache the symbol table lookup, to save for a later rule
        // when this is not a type.
        token.symbol = parseContext.symbolTable.find(*token.string);
        if (token.symbol && token.symbol->getAsVariable() && token.symbol->getAsVariable()->isUserType()) {
            type.shallowCopy(token.symbol->getType());
            advanceToken();
            return true;
        } else
            return false;

    case EHTokVoid:
        new(&type) TType(EbtVoid);
        break;

    case EHTokString:
        new(&type) TType(EbtString);
        break;

    case EHTokFloat:
        new(&type) TType(EbtFloat);
        break;
    case EHTokFloat1:
        new(&type) TType(EbtFloat);
        type.makeVector();
        break;
    case EHTokFloat2:
        new(&type) TType(EbtFloat, EvqTemporary, 2);
        break;
    case EHTokFloat3:
        new(&type) TType(EbtFloat, EvqTemporary, 3);
        break;
    case EHTokFloat4:
        new(&type) TType(EbtFloat, EvqTemporary, 4);
        break;

    case EHTokDouble:
        new(&type) TType(EbtDouble);
        break;
    case EHTokDouble1:
        new(&type) TType(EbtDouble);
        type.makeVector();
        break;
    case EHTokDouble2:
        new(&type) TType(EbtDouble, EvqTemporary, 2);
        break;
    case EHTokDouble3:
        new(&type) TType(EbtDouble, EvqTemporary, 3);
        break;
    case EHTokDouble4:
        new(&type) TType(EbtDouble, EvqTemporary, 4);
        break;

    case EHTokInt:
    case EHTokDword:
        new(&type) TType(EbtInt);
        break;
    case EHTokInt1:
        new(&type) TType(EbtInt);
        type.makeVector();
        break;
    case EHTokInt2:
        new(&type) TType(EbtInt, EvqTemporary, 2);
        break;
    case EHTokInt3:
        new(&type) TType(EbtInt, EvqTemporary, 3);
        break;
    case EHTokInt4:
        new(&type) TType(EbtInt, EvqTemporary, 4);
        break;

    case EHTokUint:
        new(&type) TType(EbtUint);
        break;
    case EHTokUint1:
        new(&type) TType(EbtUint);
        type.makeVector();
        break;
    case EHTokUint2:
        new(&type) TType(EbtUint, EvqTemporary, 2);
        break;
    case EHTokUint3:
        new(&type) TType(EbtUint, EvqTemporary, 3);
        break;
    case EHTokUint4:
        new(&type) TType(EbtUint, EvqTemporary, 4);
        break;

    case EHTokBool:
        new(&type) TType(EbtBool);
        break;
    case EHTokBool1:
        new(&type) TType(EbtBool);
        type.makeVector();
        break;
    case EHTokBool2:
        new(&type) TType(EbtBool, EvqTemporary, 2);
        break;
    case EHTokBool3:
        new(&type) TType(EbtBool, EvqTemporary, 3);
        break;
    case EHTokBool4:
        new(&type) TType(EbtBool, EvqTemporary, 4);
        break;

    case EHTokHalf:
        new(&type) TType(half_bt, EvqTemporary, EpqMedium);
        break;
    case EHTokHalf1:
        new(&type) TType(half_bt, EvqTemporary, EpqMedium);
        type.makeVector();
        break;
    case EHTokHalf2:
        new(&type) TType(half_bt, EvqTemporary, EpqMedium, 2);
        break;
    case EHTokHalf3:
        new(&type) TType(half_bt, EvqTemporary, EpqMedium, 3);
        break;
    case EHTokHalf4:
        new(&type) TType(half_bt, EvqTemporary, EpqMedium, 4);
        break;

    case EHTokMin16float:
        new(&type) TType(min16float_bt, EvqTemporary, EpqMedium);
        break;
    case EHTokMin16float1:
        new(&type) TType(min16float_bt, EvqTemporary, EpqMedium);
        type.makeVector();
        break;
    case EHTokMin16float2:
        new(&type) TType(min16float_bt, EvqTemporary, EpqMedium, 2);
        break;
    case EHTokMin16float3:
        new(&type) TType(min16float_bt, EvqTemporary, EpqMedium, 3);
        break;
    case EHTokMin16float4:
        new(&type) TType(min16float_bt, EvqTemporary, EpqMedium, 4);
        break;

    case EHTokMin10float:
        new(&type) TType(min10float_bt, EvqTemporary, EpqMedium);
        break;
    case EHTokMin10float1:
        new(&type) TType(min10float_bt, EvqTemporary, EpqMedium);
        type.makeVector();
        break;
    case EHTokMin10float2:
        new(&type) TType(min10float_bt, EvqTemporary, EpqMedium, 2);
        break;
    case EHTokMin10float3:
        new(&type) TType(min10float_bt, EvqTemporary, EpqMedium, 3);
        break;
    case EHTokMin10float4:
        new(&type) TType(min10float_bt, EvqTemporary, EpqMedium, 4);
        break;

    case EHTokMin16int:
        new(&type) TType(min16int_bt, EvqTemporary, EpqMedium);
        break;
    case EHTokMin16int1:
        new(&type) TType(min16int_bt, EvqTemporary, EpqMedium);
        type.makeVector();
        break;
    case EHTokMin16int2:
        new(&type) TType(min16int_bt, EvqTemporary, EpqMedium, 2);
        break;
    case EHTokMin16int3:
        new(&type) TType(min16int_bt, EvqTemporary, EpqMedium, 3);
        break;
    case EHTokMin16int4:
        new(&type) TType(min16int_bt, EvqTemporary, EpqMedium, 4);
        break;

    case EHTokMin12int:
        new(&type) TType(min12int_bt, EvqTemporary, EpqMedium);
        break;
    case EHTokMin12int1:
        new(&type) TType(min12int_bt, EvqTemporary, EpqMedium);
        type.makeVector();
        break;
    case EHTokMin12int2:
        new(&type) TType(min12int_bt, EvqTemporary, EpqMedium, 2);
        break;
    case EHTokMin12int3:
        new(&type) TType(min12int_bt, EvqTemporary, EpqMedium, 3);
        break;
    case EHTokMin12int4:
        new(&type) TType(min12int_bt, EvqTemporary, EpqMedium, 4);
        break;

    case EHTokMin16uint:
        new(&type) TType(min16uint_bt, EvqTemporary, EpqMedium);
        break;
    case EHTokMin16uint1:
        new(&type) TType(min16uint_bt, EvqTemporary, EpqMedium);
        type.makeVector();
        break;
    case EHTokMin16uint2:
        new(&type) TType(min16uint_bt, EvqTemporary, EpqMedium, 2);
        break;
    case EHTokMin16uint3:
        new(&type) TType(min16uint_bt, EvqTemporary, EpqMedium, 3);
        break;
    case EHTokMin16uint4:
        new(&type) TType(min16uint_bt, EvqTemporary, EpqMedium, 4);
        break;

    case EHTokInt1x1:
        new(&type) TType(EbtInt, EvqTemporary, 0, 1, 1);
        break;
    case EHTokInt1x2:
        new(&type) TType(EbtInt, EvqTemporary, 0, 1, 2);
        break;
    case EHTokInt1x3:
        new(&type) TType(EbtInt, EvqTemporary, 0, 1, 3);
        break;
    case EHTokInt1x4:
        new(&type) TType(EbtInt, EvqTemporary, 0, 1, 4);
        break;
    case EHTokInt2x1:
        new(&type) TType(EbtInt, EvqTemporary, 0, 2, 1);
        break;
    case EHTokInt2x2:
        new(&type) TType(EbtInt, EvqTemporary, 0, 2, 2);
        break;
    case EHTokInt2x3:
        new(&type) TType(EbtInt, EvqTemporary, 0, 2, 3);
        break;
    case EHTokInt2x4:
        new(&type) TType(EbtInt, EvqTemporary, 0, 2, 4);
        break;
    case EHTokInt3x1:
        new(&type) TType(EbtInt, EvqTemporary, 0, 3, 1);
        break;
    case EHTokInt3x2:
        new(&type) TType(EbtInt, EvqTemporary, 0, 3, 2);
        break;
    case EHTokInt3x3:
        new(&type) TType(EbtInt, EvqTemporary, 0, 3, 3);
        break;
    case EHTokInt3x4:
        new(&type) TType(EbtInt, EvqTemporary, 0, 3, 4);
        break;
    case EHTokInt4x1:
        new(&type) TType(EbtInt, EvqTemporary, 0, 4, 1);
        break;
    case EHTokInt4x2:
        new(&type) TType(EbtInt, EvqTemporary, 0, 4, 2);
        break;
    case EHTokInt4x3:
        new(&type) TType(EbtInt, EvqTemporary, 0, 4, 3);
        break;
    case EHTokInt4x4:
        new(&type) TType(EbtInt, EvqTemporary, 0, 4, 4);
        break;

    case EHTokUint1x1:
        new(&type) TType(EbtUint, EvqTemporary, 0, 1, 1);
        break;
    case EHTokUint1x2:
        new(&type) TType(EbtUint, EvqTemporary, 0, 1, 2);
        break;
    case EHTokUint1x3:
        new(&type) TType(EbtUint, EvqTemporary, 0, 1, 3);
        break;
    case EHTokUint1x4:
        new(&type) TType(EbtUint, EvqTemporary, 0, 1, 4);
        break;
    case EHTokUint2x1:
        new(&type) TType(EbtUint, EvqTemporary, 0, 2, 1);
        break;
    case EHTokUint2x2:
        new(&type) TType(EbtUint, EvqTemporary, 0, 2, 2);
        break;
    case EHTokUint2x3:
        new(&type) TType(EbtUint, EvqTemporary, 0, 2, 3);
        break;
    case EHTokUint2x4:
        new(&type) TType(EbtUint, EvqTemporary, 0, 2, 4);
        break;
    case EHTokUint3x1:
        new(&type) TType(EbtUint, EvqTemporary, 0, 3, 1);
        break;
    case EHTokUint3x2:
        new(&type) TType(EbtUint, EvqTemporary, 0, 3, 2);
        break;
    case EHTokUint3x3:
        new(&type) TType(EbtUint, EvqTemporary, 0, 3, 3);
        break;
    case EHTokUint3x4:
        new(&type) TType(EbtUint, EvqTemporary, 0, 3, 4);
        break;
    case EHTokUint4x1:
        new(&type) TType(EbtUint, EvqTemporary, 0, 4, 1);
        break;
    case EHTokUint4x2:
        new(&type) TType(EbtUint, EvqTemporary, 0, 4, 2);
        break;
    case EHTokUint4x3:
        new(&type) TType(EbtUint, EvqTemporary, 0, 4, 3);
        break;
    case EHTokUint4x4:
        new(&type) TType(EbtUint, EvqTemporary, 0, 4, 4);
        break;

    case EHTokBool1x1:
        new(&type) TType(EbtBool, EvqTemporary, 0, 1, 1);
        break;
    case EHTokBool1x2:
        new(&type) TType(EbtBool, EvqTemporary, 0, 1, 2);
        break;
    case EHTokBool1x3:
        new(&type) TType(EbtBool, EvqTemporary, 0, 1, 3);
        break;
    case EHTokBool1x4:
        new(&type) TType(EbtBool, EvqTemporary, 0, 1, 4);
        break;
    case EHTokBool2x1:
        new(&type) TType(EbtBool, EvqTemporary, 0, 2, 1);
        break;
    case EHTokBool2x2:
        new(&type) TType(EbtBool, EvqTemporary, 0, 2, 2);
        break;
    case EHTokBool2x3:
        new(&type) TType(EbtBool, EvqTemporary, 0, 2, 3);
        break;
    case EHTokBool2x4:
        new(&type) TType(EbtBool, EvqTemporary, 0, 2, 4);
        break;
    case EHTokBool3x1:
        new(&type) TType(EbtBool, EvqTemporary, 0, 3, 1);
        break;
    case EHTokBool3x2:
        new(&type) TType(EbtBool, EvqTemporary, 0, 3, 2);
        break;
    case EHTokBool3x3:
        new(&type) TType(EbtBool, EvqTemporary, 0, 3, 3);
        break;
    case EHTokBool3x4:
        new(&type) TType(EbtBool, EvqTemporary, 0, 3, 4);
        break;
    case EHTokBool4x1:
        new(&type) TType(EbtBool, EvqTemporary, 0, 4, 1);
        break;
    case EHTokBool4x2:
        new(&type) TType(EbtBool, EvqTemporary, 0, 4, 2);
        break;
    case EHTokBool4x3:
        new(&type) TType(EbtBool, EvqTemporary, 0, 4, 3);
        break;
    case EHTokBool4x4:
        new(&type) TType(EbtBool, EvqTemporary, 0, 4, 4);
        break;

    case EHTokFloat1x1:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 1, 1);
        break;
    case EHTokFloat1x2:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 1, 2);
        break;
    case EHTokFloat1x3:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 1, 3);
        break;
    case EHTokFloat1x4:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 1, 4);
        break;
    case EHTokFloat2x1:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 2, 1);
        break;
    case EHTokFloat2x2:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 2, 2);
        break;
    case EHTokFloat2x3:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 2, 3);
        break;
    case EHTokFloat2x4:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 2, 4);
        break;
    case EHTokFloat3x1:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 3, 1);
        break;
    case EHTokFloat3x2:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 3, 2);
        break;
    case EHTokFloat3x3:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 3, 3);
        break;
    case EHTokFloat3x4:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 3, 4);
        break;
    case EHTokFloat4x1:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 1);
        break;
    case EHTokFloat4x2:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 2);
        break;
    case EHTokFloat4x3:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 3);
        break;
    case EHTokFloat4x4:
        new(&type) TType(EbtFloat, EvqTemporary, 0, 4, 4);
        break;

    case EHTokDouble1x1:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 1, 1);
        break;
    case EHTokDouble1x2:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 1, 2);
        break;
    case EHTokDouble1x3:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 1, 3);
        break;
    case EHTokDouble1x4:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 1, 4);
        break;
    case EHTokDouble2x1:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 2, 1);
        break;
    case EHTokDouble2x2:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 2, 2);
        break;
    case EHTokDouble2x3:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 2, 3);
        break;
    case EHTokDouble2x4:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 2, 4);
        break;
    case EHTokDouble3x1:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 3, 1);
        break;
    case EHTokDouble3x2:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 3, 2);
        break;
    case EHTokDouble3x3:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 3, 3);
        break;
    case EHTokDouble3x4:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 3, 4);
        break;
    case EHTokDouble4x1:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 4, 1);
        break;
    case EHTokDouble4x2:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 4, 2);
        break;
    case EHTokDouble4x3:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 4, 3);
        break;
    case EHTokDouble4x4:
        new(&type) TType(EbtDouble, EvqTemporary, 0, 4, 4);
        break;

    default:
        return false;
    }

    advanceToken();

    return true;
}

// struct
//      : struct_type IDENTIFIER post_decls LEFT_BRACE struct_declaration_list RIGHT_BRACE
//      | struct_type            post_decls LEFT_BRACE struct_declaration_list RIGHT_BRACE
//
// struct_type
//      : STRUCT
//      | CBUFFER
//      | TBUFFER
//
bool HlslGrammar::acceptStruct(TType& type)
{
    // This storage qualifier will tell us whether it's an AST
    // block type or just a generic structure type.
    TStorageQualifier storageQualifier = EvqTemporary;

    // CBUFFER
    if (acceptTokenClass(EHTokCBuffer))
        storageQualifier = EvqUniform;
    // TBUFFER
    else if (acceptTokenClass(EHTokTBuffer))
        storageQualifier = EvqBuffer;
    // STRUCT
    else if (! acceptTokenClass(EHTokStruct))
        return false;

    // IDENTIFIER
    TString structName = "";
    if (peekTokenClass(EHTokIdentifier)) {
        structName = *token.string;
        advanceToken();
    }

    // post_decls
    TQualifier postDeclQualifier;
    postDeclQualifier.clear();
    acceptPostDecls(postDeclQualifier);

    // LEFT_BRACE
    if (! acceptTokenClass(EHTokLeftBrace)) {
        expected("{");
        return false;
    }

    // struct_declaration_list
    TTypeList* typeList;
    if (! acceptStructDeclarationList(typeList)) {
        expected("struct member declarations");
        return false;
    }

    // RIGHT_BRACE
    if (! acceptTokenClass(EHTokRightBrace)) {
        expected("}");
        return false;
    }

    // create the user-defined type
    if (storageQualifier == EvqTemporary)
        new(&type) TType(typeList, structName);
    else {
        postDeclQualifier.storage = storageQualifier;
        new(&type) TType(typeList, structName, postDeclQualifier); // sets EbtBlock
    }

    // If it was named, which means the type can be reused later, add
    // it to the symbol table.  (Unless it's a block, in which
    // case the name is not a type.)
    if (type.getBasicType() != EbtBlock && structName.size() > 0) {
        TVariable* userTypeDef = new TVariable(&structName, type, true);
        if (! parseContext.symbolTable.insert(*userTypeDef))
            parseContext.error(token.loc, "redefinition", structName.c_str(), "struct");
    }

    return true;
}

// struct_declaration_list
//      : struct_declaration SEMI_COLON struct_declaration SEMI_COLON ...
//
// struct_declaration
//      : fully_specified_type struct_declarator COMMA struct_declarator ...
//
// struct_declarator
//      : IDENTIFIER post_decls
//      | IDENTIFIER array_specifier post_decls
//
bool HlslGrammar::acceptStructDeclarationList(TTypeList*& typeList)
{
    typeList = new TTypeList();
    HlslToken idToken;

    do {
        // success on seeing the RIGHT_BRACE coming up
        if (peekTokenClass(EHTokRightBrace))
            return true;

        // struct_declaration

        // fully_specified_type
        TType memberType;
        if (! acceptFullySpecifiedType(memberType)) {
            expected("member type");
            return false;
        }

        // struct_declarator COMMA struct_declarator ...
        do {
            if (! acceptIdentifier(idToken)) {
                expected("member name");
                return false;
            }

            // add it to the list of members
            TTypeLoc member = { new TType(EbtVoid), token.loc };
            member.type->shallowCopy(memberType);
            member.type->setFieldName(*idToken.string);
            typeList->push_back(member);

            // array_specifier
            TArraySizes* arraySizes = nullptr;
            acceptArraySpecifier(arraySizes);
            if (arraySizes)
                typeList->back().type->newArraySizes(*arraySizes);

            acceptPostDecls(member.type->getQualifier());

            // success on seeing the SEMICOLON coming up
            if (peekTokenClass(EHTokSemicolon))
                break;

            // COMMA
            if (! acceptTokenClass(EHTokComma)) {
                expected(",");
                return false;
            }

        } while (true);

        // SEMI_COLON
        if (! acceptTokenClass(EHTokSemicolon)) {
            expected(";");
            return false;
        }

    } while (true);
}

// function_parameters
//      : LEFT_PAREN parameter_declaration COMMA parameter_declaration ... RIGHT_PAREN
//      | LEFT_PAREN VOID RIGHT_PAREN
//
bool HlslGrammar::acceptFunctionParameters(TFunction& function)
{
    // LEFT_PAREN
    if (! acceptTokenClass(EHTokLeftParen))
        return false;

    // VOID RIGHT_PAREN
    if (! acceptTokenClass(EHTokVoid)) {
        do {
            // parameter_declaration
            if (! acceptParameterDeclaration(function))
                break;

            // COMMA
            if (! acceptTokenClass(EHTokComma))
                break;
        } while (true);
    }

    // RIGHT_PAREN
    if (! acceptTokenClass(EHTokRightParen)) {
        expected(")");
        return false;
    }

    return true;
}

// default_parameter_declaration
//      : EQUAL conditional_expression
//      : EQUAL initializer
bool HlslGrammar::acceptDefaultParameterDeclaration(const TType& type, TIntermTyped*& node)
{
    node = nullptr;

    // Valid not to have a default_parameter_declaration
    if (!acceptTokenClass(EHTokAssign))
        return true;

    if (!acceptConditionalExpression(node)) {
        if (!acceptInitializer(node))
            return false;

        // For initializer lists, we have to const-fold into a constructor for the type, so build
        // that.
        TFunction* constructor = parseContext.handleConstructorCall(token.loc, type);
        if (constructor == nullptr)  // cannot construct
            return false;

        TIntermTyped* arguments = nullptr;
        for (int i = 0; i < int(node->getAsAggregate()->getSequence().size()); i++)
            parseContext.handleFunctionArgument(constructor, arguments, node->getAsAggregate()->getSequence()[i]->getAsTyped());

        node = parseContext.handleFunctionCall(token.loc, constructor, node);
    }

    // If this is simply a constant, we can use it directly.
    if (node->getAsConstantUnion())
        return true;

    // Otherwise, it has to be const-foldable.
    TIntermTyped* origNode = node;

    node = intermediate.fold(node->getAsAggregate());

    if (node != nullptr && origNode != node)
        return true;

    parseContext.error(token.loc, "invalid default parameter value", "", "");

    return false;
}

// parameter_declaration
//      : fully_specified_type post_decls [ = default_parameter_declaration ]
//      | fully_specified_type identifier array_specifier post_decls [ = default_parameter_declaration ]
//
bool HlslGrammar::acceptParameterDeclaration(TFunction& function)
{
    // fully_specified_type
    TType* type = new TType;
    if (! acceptFullySpecifiedType(*type))
        return false;

    // identifier
    HlslToken idToken;
    acceptIdentifier(idToken);

    // array_specifier
    TArraySizes* arraySizes = nullptr;
    acceptArraySpecifier(arraySizes);
    if (arraySizes) {
        if (arraySizes->isImplicit()) {
            parseContext.error(token.loc, "function parameter array cannot be implicitly sized", "", "");
            return false;
        }

        type->newArraySizes(*arraySizes);
    }

    // post_decls
    acceptPostDecls(type->getQualifier());

    TIntermTyped* defaultValue;
    if (!acceptDefaultParameterDeclaration(*type, defaultValue))
        return false;

    parseContext.paramFix(*type);

    // If any prior parameters have default values, all the parameters after that must as well.
    if (defaultValue == nullptr && function.getDefaultParamCount() > 0) {
        parseContext.error(idToken.loc, "invalid parameter after default value parameters", idToken.string->c_str(), "");
        return false;
    }

    TParameter param = { idToken.string, type, defaultValue };
    function.addParameter(param);

    return true;
}

// Do the work to create the function definition in addition to
// parsing the body (compound_statement).
bool HlslGrammar::acceptFunctionDefinition(TFunction& function, TIntermNode*& node, const TAttributeMap& attributes)
{
    TFunction& functionDeclarator = parseContext.handleFunctionDeclarator(token.loc, function, false /* not prototype */);
    TSourceLoc loc = token.loc;

    // This does a pushScope()
    node = parseContext.handleFunctionDefinition(loc, functionDeclarator, attributes);

    // compound_statement
    TIntermNode* functionBody = nullptr;
    if (acceptCompoundStatement(functionBody)) {
        parseContext.handleFunctionBody(loc, functionDeclarator, functionBody, node);
        return true;
    }

    return false;
}

// Accept an expression with parenthesis around it, where
// the parenthesis ARE NOT expression parenthesis, but the
// syntactically required ones like in "if ( expression )".
//
// Also accepts a declaration expression; "if (int a = expression)".
//
// Note this one is not set up to be speculative; as it gives
// errors if not found.
//
bool HlslGrammar::acceptParenExpression(TIntermTyped*& expression)
{
    // LEFT_PAREN
    if (! acceptTokenClass(EHTokLeftParen))
        expected("(");

    bool decl = false;
    TIntermNode* declNode = nullptr;
    decl = acceptControlDeclaration(declNode);
    if (decl) {
        if (declNode == nullptr || declNode->getAsTyped() == nullptr) {
            expected("initialized declaration");
            return false;
        } else
            expression = declNode->getAsTyped();
    } else {
        // no declaration
        if (! acceptExpression(expression)) {
            expected("expression");
            return false;
        }
    }

    // RIGHT_PAREN
    if (! acceptTokenClass(EHTokRightParen))
        expected(")");

    return true;
}

// The top-level full expression recognizer.
//
// expression
//      : assignment_expression COMMA assignment_expression COMMA assignment_expression ...
//
bool HlslGrammar::acceptExpression(TIntermTyped*& node)
{
    node = nullptr;

    // assignment_expression
    if (! acceptAssignmentExpression(node))
        return false;

    if (! peekTokenClass(EHTokComma))
        return true;

    do {
        // ... COMMA
        TSourceLoc loc = token.loc;
        advanceToken();

        // ... assignment_expression
        TIntermTyped* rightNode = nullptr;
        if (! acceptAssignmentExpression(rightNode)) {
            expected("assignment expression");
            return false;
        }

        node = intermediate.addComma(node, rightNode, loc);

        if (! peekTokenClass(EHTokComma))
            return true;
    } while (true);
}

// initializer
//      : LEFT_BRACE RIGHT_BRACE
//      | LEFT_BRACE initializer_list RIGHT_BRACE
//
// initializer_list
//      : assignment_expression COMMA assignment_expression COMMA ...
//
bool HlslGrammar::acceptInitializer(TIntermTyped*& node)
{
    // LEFT_BRACE
    if (! acceptTokenClass(EHTokLeftBrace))
        return false;

    // RIGHT_BRACE
    TSourceLoc loc = token.loc;
    if (acceptTokenClass(EHTokRightBrace)) {
        // a zero-length initializer list
        node = intermediate.makeAggregate(loc);
        return true;
    }

    // initializer_list
    node = nullptr;
    do {
        // assignment_expression
        TIntermTyped* expr;
        if (! acceptAssignmentExpression(expr)) {
            expected("assignment expression in initializer list");
            return false;
        }
        node = intermediate.growAggregate(node, expr, loc);

        // COMMA
        if (acceptTokenClass(EHTokComma)) {
            if (acceptTokenClass(EHTokRightBrace))  // allow trailing comma
                return true;
            continue;
        }

        // RIGHT_BRACE
        if (acceptTokenClass(EHTokRightBrace))
            return true;

        expected(", or }");
        return false;
    } while (true);
}

// Accept an assignment expression, where assignment operations
// associate right-to-left.  That is, it is implicit, for example
//
//    a op (b op (c op d))
//
// assigment_expression
//      : initializer
//      | conditional_expression
//      | conditional_expression assign_op conditional_expression assign_op conditional_expression ...
//
bool HlslGrammar::acceptAssignmentExpression(TIntermTyped*& node)
{
    // initializer
    if (peekTokenClass(EHTokLeftBrace)) {
        if (acceptInitializer(node))
            return true;

        expected("initializer");
        return false;
    }

    // conditional_expression
    if (! acceptConditionalExpression(node))
        return false;

    // assignment operation?
    TOperator assignOp = HlslOpMap::assignment(peek());
    if (assignOp == EOpNull)
        return true;

    // assign_op
    TSourceLoc loc = token.loc;
    advanceToken();

    // conditional_expression assign_op conditional_expression ...
    // Done by recursing this function, which automatically
    // gets the right-to-left associativity.
    TIntermTyped* rightNode = nullptr;
    if (! acceptAssignmentExpression(rightNode)) {
        expected("assignment expression");
        return false;
    }

    node = parseContext.handleAssign(loc, assignOp, node, rightNode);
    node = parseContext.handleLvalue(loc, "assign", node);

    if (node == nullptr) {
        parseContext.error(loc, "could not create assignment", "", "");
        return false;
    }

    if (! peekTokenClass(EHTokComma))
        return true;

    return true;
}

// Accept a conditional expression, which associates right-to-left,
// accomplished by the "true" expression calling down to lower
// precedence levels than this level.
//
// conditional_expression
//      : binary_expression
//      | binary_expression QUESTION expression COLON assignment_expression
//
bool HlslGrammar::acceptConditionalExpression(TIntermTyped*& node)
{
    // binary_expression
    if (! acceptBinaryExpression(node, PlLogicalOr))
        return false;

    if (! acceptTokenClass(EHTokQuestion))
        return true;

    TIntermTyped* trueNode = nullptr;
    if (! acceptExpression(trueNode)) {
        expected("expression after ?");
        return false;
    }
    TSourceLoc loc = token.loc;

    if (! acceptTokenClass(EHTokColon)) {
        expected(":");
        return false;
    }

    TIntermTyped* falseNode = nullptr;
    if (! acceptAssignmentExpression(falseNode)) {
        expected("expression after :");
        return false;
    }

    node = intermediate.addSelection(node, trueNode, falseNode, loc);

    return true;
}

// Accept a binary expression, for binary operations that
// associate left-to-right.  This is, it is implicit, for example
//
//    ((a op b) op c) op d
//
// binary_expression
//      : expression op expression op expression ...
//
// where 'expression' is the next higher level in precedence.
//
bool HlslGrammar::acceptBinaryExpression(TIntermTyped*& node, PrecedenceLevel precedenceLevel)
{
    if (precedenceLevel > PlMul)
        return acceptUnaryExpression(node);

    // assignment_expression
    if (! acceptBinaryExpression(node, (PrecedenceLevel)(precedenceLevel + 1)))
        return false;

    do {
        TOperator op = HlslOpMap::binary(peek());
        PrecedenceLevel tokenLevel = HlslOpMap::precedenceLevel(op);
        if (tokenLevel < precedenceLevel)
            return true;

        // ... op
        TSourceLoc loc = token.loc;
        advanceToken();

        // ... expression
        TIntermTyped* rightNode = nullptr;
        if (! acceptBinaryExpression(rightNode, (PrecedenceLevel)(precedenceLevel + 1))) {
            expected("expression");
            return false;
        }

        node = intermediate.addBinaryMath(op, node, rightNode, loc);
        if (node == nullptr) {
            parseContext.error(loc, "Could not perform requested binary operation", "", "");
            return false;
        }
    } while (true);
}

// unary_expression
//      : (type) unary_expression
//      | + unary_expression
//      | - unary_expression
//      | ! unary_expression
//      | ~ unary_expression
//      | ++ unary_expression
//      | -- unary_expression
//      | postfix_expression
//
bool HlslGrammar::acceptUnaryExpression(TIntermTyped*& node)
{
    // (type) unary_expression
    // Have to look two steps ahead, because this could be, e.g., a
    // postfix_expression instead, since that also starts with at "(".
    if (acceptTokenClass(EHTokLeftParen)) {
        TType castType;
        if (acceptType(castType)) {
            if (acceptTokenClass(EHTokRightParen)) {
                // We've matched "(type)" now, get the expression to cast
                TSourceLoc loc = token.loc;
                if (! acceptUnaryExpression(node))
                    return false;

                // Hook it up like a constructor
                TFunction* constructorFunction = parseContext.handleConstructorCall(loc, castType);
                if (constructorFunction == nullptr) {
                    expected("type that can be constructed");
                    return false;
                }
                TIntermTyped* arguments = nullptr;
                parseContext.handleFunctionArgument(constructorFunction, arguments, node);
                node = parseContext.handleFunctionCall(loc, constructorFunction, arguments);

                return true;
            } else {
                // This could be a parenthesized constructor, ala (int(3)), and we just accepted
                // the '(int' part.  We must back up twice.
                recedeToken();
                recedeToken();
            }
        } else {
            // This isn't a type cast, but it still started "(", so if it is a
            // unary expression, it can only be a postfix_expression, so try that.
            // Back it up first.
            recedeToken();
            return acceptPostfixExpression(node);
        }
    }

    // peek for "op unary_expression"
    TOperator unaryOp = HlslOpMap::preUnary(peek());

    // postfix_expression (if no unary operator)
    if (unaryOp == EOpNull)
        return acceptPostfixExpression(node);

    // op unary_expression
    TSourceLoc loc = token.loc;
    advanceToken();
    if (! acceptUnaryExpression(node))
        return false;

    // + is a no-op
    if (unaryOp == EOpAdd)
        return true;

    node = intermediate.addUnaryMath(unaryOp, node, loc);

    // These unary ops require lvalues
    if (unaryOp == EOpPreIncrement || unaryOp == EOpPreDecrement)
        node = parseContext.handleLvalue(loc, "unary operator", node);

    return node != nullptr;
}

// postfix_expression
//      : LEFT_PAREN expression RIGHT_PAREN
//      | literal
//      | constructor
//      | identifier
//      | function_call
//      | postfix_expression LEFT_BRACKET integer_expression RIGHT_BRACKET
//      | postfix_expression DOT IDENTIFIER
//      | postfix_expression INC_OP
//      | postfix_expression DEC_OP
//
bool HlslGrammar::acceptPostfixExpression(TIntermTyped*& node)
{
    // Not implemented as self-recursive:
    // The logical "right recursion" is done with an loop at the end

    // idToken will pick up either a variable or a function name in a function call
    HlslToken idToken;

    // Find something before the postfix operations, as they can't operate
    // on nothing.  So, no "return true", they fall through, only "return false".
    if (acceptTokenClass(EHTokLeftParen)) {
        // LEFT_PAREN expression RIGHT_PAREN
        if (! acceptExpression(node)) {
            expected("expression");
            return false;
        }
        if (! acceptTokenClass(EHTokRightParen)) {
            expected(")");
            return false;
        }
    } else if (acceptLiteral(node)) {
        // literal (nothing else to do yet), go on to the
    } else if (acceptConstructor(node)) {
        // constructor (nothing else to do yet)
    } else if (acceptIdentifier(idToken)) {
        // identifier or function_call name
        if (! peekTokenClass(EHTokLeftParen)) {
            node = parseContext.handleVariable(idToken.loc, idToken.symbol, idToken.string);
        } else if (acceptFunctionCall(idToken, node)) {
            // function_call (nothing else to do yet)
        } else {
            expected("function call arguments");
            return false;
        }
    } else {
        // nothing found, can't post operate
        return false;
    }

    // This is to guarantee we do this no matter how we get out of the stack frame.
    // This way there's no bug if an early return forgets to do it.
    struct tFinalize {
        tFinalize(HlslParseContext& p) : parseContext(p) { }
        ~tFinalize() { parseContext.finalizeFlattening(); }
       HlslParseContext& parseContext;
    } finalize(parseContext);

    // Initialize the flattening accumulation data, so we can track data across multiple bracket or
    // dot operators.  This can also be nested, e.g, for [], so we have to track each nesting
    // level: hence the init and finalize.  Even though in practice these must be
    // constants, they are parsed no matter what.
    parseContext.initFlattening();

    // Something was found, chain as many postfix operations as exist.
    do {
        TSourceLoc loc = token.loc;
        TOperator postOp = HlslOpMap::postUnary(peek());

        // Consume only a valid post-unary operator, otherwise we are done.
        switch (postOp) {
        case EOpIndexDirectStruct:
        case EOpIndexIndirect:
        case EOpPostIncrement:
        case EOpPostDecrement:
            advanceToken();
            break;
        default:
            return true;
        }

        // We have a valid post-unary operator, process it.
        switch (postOp) {
        case EOpIndexDirectStruct:
        {
            // DOT IDENTIFIER
            // includes swizzles and struct members
            HlslToken field;
            if (! acceptIdentifier(field)) {
                expected("swizzle or member");
                return false;
            }

            TIntermTyped* base = node; // preserve for method function calls
            node = parseContext.handleDotDereference(field.loc, node, *field.string);

            // In the event of a method node, we look for an open paren and accept the function call.
            if (node != nullptr && node->getAsMethodNode() != nullptr && peekTokenClass(EHTokLeftParen)) {
                if (! acceptFunctionCall(field, node, base)) {
                    expected("function parameters");
                    return false;
                }
            }

            break;
        }
        case EOpIndexIndirect:
        {
            // LEFT_BRACKET integer_expression RIGHT_BRACKET
            TIntermTyped* indexNode = nullptr;
            if (! acceptExpression(indexNode) ||
                ! peekTokenClass(EHTokRightBracket)) {
                expected("expression followed by ']'");
                return false;
            }
            advanceToken();
            node = parseContext.handleBracketDereference(indexNode->getLoc(), node, indexNode);
            break;
        }
        case EOpPostIncrement:
            // INC_OP
            // fall through
        case EOpPostDecrement:
            // DEC_OP
            node = intermediate.addUnaryMath(postOp, node, loc);
            node = parseContext.handleLvalue(loc, "unary operator", node);
            break;
        default:
            assert(0);
            break;
        }
    } while (true);
}

// constructor
//      : type argument_list
//
bool HlslGrammar::acceptConstructor(TIntermTyped*& node)
{
    // type
    TType type;
    if (acceptType(type)) {
        TFunction* constructorFunction = parseContext.handleConstructorCall(token.loc, type);
        if (constructorFunction == nullptr)
            return false;

        // arguments
        TIntermTyped* arguments = nullptr;
        if (! acceptArguments(constructorFunction, arguments)) {
            // It's possible this is a type keyword used as an identifier.  Put the token back
            // for later use.
            recedeToken();
            return false;
        }

        // hook it up
        node = parseContext.handleFunctionCall(arguments->getLoc(), constructorFunction, arguments);

        return true;
    }

    return false;
}

// The function_call identifier was already recognized, and passed in as idToken.
//
// function_call
//      : [idToken] arguments
//
bool HlslGrammar::acceptFunctionCall(HlslToken idToken, TIntermTyped*& node, TIntermTyped* base)
{
    // arguments
    TFunction* function = new TFunction(idToken.string, TType(EbtVoid));
    TIntermTyped* arguments = nullptr;

    // methods have an implicit first argument of the calling object.
    if (base != nullptr)
        parseContext.handleFunctionArgument(function, arguments, base);

    if (! acceptArguments(function, arguments))
        return false;

    node = parseContext.handleFunctionCall(idToken.loc, function, arguments);

    return true;
}

// arguments
//      : LEFT_PAREN expression COMMA expression COMMA ... RIGHT_PAREN
//
// The arguments are pushed onto the 'function' argument list and
// onto the 'arguments' aggregate.
//
bool HlslGrammar::acceptArguments(TFunction* function, TIntermTyped*& arguments)
{
    // LEFT_PAREN
    if (! acceptTokenClass(EHTokLeftParen))
        return false;

    do {
        // expression
        TIntermTyped* arg;
        if (! acceptAssignmentExpression(arg))
            break;

        // hook it up
        parseContext.handleFunctionArgument(function, arguments, arg);

        // COMMA
        if (! acceptTokenClass(EHTokComma))
            break;
    } while (true);

    // RIGHT_PAREN
    if (! acceptTokenClass(EHTokRightParen)) {
        expected(")");
        return false;
    }

    return true;
}

bool HlslGrammar::acceptLiteral(TIntermTyped*& node)
{
    switch (token.tokenClass) {
    case EHTokIntConstant:
        node = intermediate.addConstantUnion(token.i, token.loc, true);
        break;
    case EHTokUintConstant:
        node = intermediate.addConstantUnion(token.u, token.loc, true);
        break;
    case EHTokFloatConstant:
        node = intermediate.addConstantUnion(token.d, EbtFloat, token.loc, true);
        break;
    case EHTokDoubleConstant:
        node = intermediate.addConstantUnion(token.d, EbtDouble, token.loc, true);
        break;
    case EHTokBoolConstant:
        node = intermediate.addConstantUnion(token.b, token.loc, true);
        break;
    case EHTokStringConstant:
        node = nullptr;
        break;

    default:
        return false;
    }

    advanceToken();

    return true;
}

// compound_statement
//      : LEFT_CURLY statement statement ... RIGHT_CURLY
//
bool HlslGrammar::acceptCompoundStatement(TIntermNode*& retStatement)
{
    TIntermAggregate* compoundStatement = nullptr;

    // LEFT_CURLY
    if (! acceptTokenClass(EHTokLeftBrace))
        return false;

    // statement statement ...
    TIntermNode* statement = nullptr;
    while (acceptStatement(statement)) {
        TIntermBranch* branch = statement ? statement->getAsBranchNode() : nullptr;
        if (branch != nullptr && (branch->getFlowOp() == EOpCase ||
                                  branch->getFlowOp() == EOpDefault)) {
            // hook up individual subsequences within a switch statement
            parseContext.wrapupSwitchSubsequence(compoundStatement, statement);
            compoundStatement = nullptr;
        } else {
            // hook it up to the growing compound statement
            compoundStatement = intermediate.growAggregate(compoundStatement, statement);
        }
    }
    if (compoundStatement)
        compoundStatement->setOperator(EOpSequence);

    retStatement = compoundStatement;

    // RIGHT_CURLY
    return acceptTokenClass(EHTokRightBrace);
}

bool HlslGrammar::acceptScopedStatement(TIntermNode*& statement)
{
    parseContext.pushScope();
    bool result = acceptStatement(statement);
    parseContext.popScope();

    return result;
}

bool HlslGrammar::acceptScopedCompoundStatement(TIntermNode*& statement)
{
    parseContext.pushScope();
    bool result = acceptCompoundStatement(statement);
    parseContext.popScope();

    return result;
}

// statement
//      : attributes attributed_statement
//
// attributed_statement
//      : compound_statement
//      | SEMICOLON
//      | expression SEMICOLON
//      | declaration_statement
//      | selection_statement
//      | switch_statement
//      | case_label
//      | iteration_statement
//      | jump_statement
//
bool HlslGrammar::acceptStatement(TIntermNode*& statement)
{
    statement = nullptr;

    // attributes
    TAttributeMap attributes;
    acceptAttributes(attributes);

    // attributed_statement
    switch (peek()) {
    case EHTokLeftBrace:
        return acceptScopedCompoundStatement(statement);

    case EHTokIf:
        return acceptSelectionStatement(statement);

    case EHTokSwitch:
        return acceptSwitchStatement(statement);

    case EHTokFor:
    case EHTokDo:
    case EHTokWhile:
        return acceptIterationStatement(statement);

    case EHTokContinue:
    case EHTokBreak:
    case EHTokDiscard:
    case EHTokReturn:
        return acceptJumpStatement(statement);

    case EHTokCase:
        return acceptCaseLabel(statement);
    case EHTokDefault:
        return acceptDefaultLabel(statement);

    case EHTokSemicolon:
        return acceptTokenClass(EHTokSemicolon);

    case EHTokRightBrace:
        // Performance: not strictly necessary, but stops a bunch of hunting early,
        // and is how sequences of statements end.
        return false;

    default:
        {
            // declaration
            if (acceptDeclaration(statement))
                return true;

            // expression
            TIntermTyped* node;
            if (acceptExpression(node))
                statement = node;
            else
                return false;

            // SEMICOLON (following an expression)
            if (! acceptTokenClass(EHTokSemicolon)) {
                expected(";");
                return false;
            }
        }
    }

    return true;
}

// attributes
//      : list of zero or more of:  LEFT_BRACKET attribute RIGHT_BRACKET
//
// attribute:
//      : UNROLL
//      | UNROLL LEFT_PAREN literal RIGHT_PAREN
//      | FASTOPT
//      | ALLOW_UAV_CONDITION
//      | BRANCH
//      | FLATTEN
//      | FORCECASE
//      | CALL
//      | DOMAIN
//      | EARLYDEPTHSTENCIL
//      | INSTANCE
//      | MAXTESSFACTOR
//      | OUTPUTCONTROLPOINTS
//      | OUTPUTTOPOLOGY
//      | PARTITIONING
//      | PATCHCONSTANTFUNC
//      | NUMTHREADS LEFT_PAREN x_size, y_size,z z_size RIGHT_PAREN
//
void HlslGrammar::acceptAttributes(TAttributeMap& attributes)
{
    // For now, accept the [ XXX(X) ] syntax, but drop all but
    // numthreads, which is used to set the CS local size.
    // TODO: subset to correct set?  Pass on?
    do {
        HlslToken idToken;

        // LEFT_BRACKET?
        if (! acceptTokenClass(EHTokLeftBracket))
            return;

        // attribute
        if (acceptIdentifier(idToken)) {
            // 'idToken.string' is the attribute
        } else if (! peekTokenClass(EHTokRightBracket)) {
            expected("identifier");
            advanceToken();
        }

        TIntermAggregate* expressions = nullptr;

        // (x, ...)
        if (acceptTokenClass(EHTokLeftParen)) {
            expressions = new TIntermAggregate;

            TIntermTyped* node;
            bool expectingExpression = false;

            while (acceptAssignmentExpression(node)) {
                expectingExpression = false;
                expressions->getSequence().push_back(node);
                if (acceptTokenClass(EHTokComma))
                    expectingExpression = true;
            }

            // 'expressions' is an aggregate with the expressions in it
            if (! acceptTokenClass(EHTokRightParen))
                expected(")");

            // Error for partial or missing expression
            if (expectingExpression || expressions->getSequence().empty())
                expected("expression");
        }

        // RIGHT_BRACKET
        if (!acceptTokenClass(EHTokRightBracket)) {
            expected("]");
            return;
        }

        // Add any values we found into the attribute map.  This accepts
        // (and ignores) values not mapping to a known TAttributeType;
        attributes.setAttribute(idToken.string, expressions);
    } while (true);
}

// selection_statement
//      : IF LEFT_PAREN expression RIGHT_PAREN statement
//      : IF LEFT_PAREN expression RIGHT_PAREN statement ELSE statement
//
bool HlslGrammar::acceptSelectionStatement(TIntermNode*& statement)
{
    TSourceLoc loc = token.loc;

    // IF
    if (! acceptTokenClass(EHTokIf))
        return false;

    // so that something declared in the condition is scoped to the lifetimes
    // of the then-else statements
    parseContext.pushScope();

    // LEFT_PAREN expression RIGHT_PAREN
    TIntermTyped* condition;
    if (! acceptParenExpression(condition))
        return false;

    // create the child statements
    TIntermNodePair thenElse = { nullptr, nullptr };

    // then statement
    if (! acceptScopedStatement(thenElse.node1)) {
        expected("then statement");
        return false;
    }

    // ELSE
    if (acceptTokenClass(EHTokElse)) {
        // else statement
        if (! acceptScopedStatement(thenElse.node2)) {
            expected("else statement");
            return false;
        }
    }

    // Put the pieces together
    statement = intermediate.addSelection(condition, thenElse, loc);
    parseContext.popScope();

    return true;
}

// switch_statement
//      : SWITCH LEFT_PAREN expression RIGHT_PAREN compound_statement
//
bool HlslGrammar::acceptSwitchStatement(TIntermNode*& statement)
{
    // SWITCH
    TSourceLoc loc = token.loc;
    if (! acceptTokenClass(EHTokSwitch))
        return false;

    // LEFT_PAREN expression RIGHT_PAREN
    parseContext.pushScope();
    TIntermTyped* switchExpression;
    if (! acceptParenExpression(switchExpression)) {
        parseContext.popScope();
        return false;
    }

    // compound_statement
    parseContext.pushSwitchSequence(new TIntermSequence);
    bool statementOkay = acceptCompoundStatement(statement);
    if (statementOkay)
        statement = parseContext.addSwitch(loc, switchExpression, statement ? statement->getAsAggregate() : nullptr);

    parseContext.popSwitchSequence();
    parseContext.popScope();

    return statementOkay;
}

// iteration_statement
//      : WHILE LEFT_PAREN condition RIGHT_PAREN statement
//      | DO LEFT_BRACE statement RIGHT_BRACE WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON
//      | FOR LEFT_PAREN for_init_statement for_rest_statement RIGHT_PAREN statement
//
// Non-speculative, only call if it needs to be found; WHILE or DO or FOR already seen.
bool HlslGrammar::acceptIterationStatement(TIntermNode*& statement)
{
    TSourceLoc loc = token.loc;
    TIntermTyped* condition = nullptr;

    EHlslTokenClass loop = peek();
    assert(loop == EHTokDo || loop == EHTokFor || loop == EHTokWhile);

    //  WHILE or DO or FOR
    advanceToken();

    switch (loop) {
    case EHTokWhile:
        // so that something declared in the condition is scoped to the lifetime
        // of the while sub-statement
        parseContext.pushScope();
        parseContext.nestLooping();

        // LEFT_PAREN condition RIGHT_PAREN
        if (! acceptParenExpression(condition))
            return false;

        // statement
        if (! acceptScopedStatement(statement)) {
            expected("while sub-statement");
            return false;
        }

        parseContext.unnestLooping();
        parseContext.popScope();

        statement = intermediate.addLoop(statement, condition, nullptr, true, loc);

        return true;

    case EHTokDo:
        parseContext.nestLooping();

        if (! acceptTokenClass(EHTokLeftBrace))
            expected("{");

        // statement
        if (! peekTokenClass(EHTokRightBrace) && ! acceptScopedStatement(statement)) {
            expected("do sub-statement");
            return false;
        }

        if (! acceptTokenClass(EHTokRightBrace))
            expected("}");

        // WHILE
        if (! acceptTokenClass(EHTokWhile)) {
            expected("while");
            return false;
        }

        // LEFT_PAREN condition RIGHT_PAREN
        TIntermTyped* condition;
        if (! acceptParenExpression(condition))
            return false;

        if (! acceptTokenClass(EHTokSemicolon))
            expected(";");

        parseContext.unnestLooping();

        statement = intermediate.addLoop(statement, condition, 0, false, loc);

        return true;

    case EHTokFor:
    {
        // LEFT_PAREN
        if (! acceptTokenClass(EHTokLeftParen))
            expected("(");

        // so that something declared in the condition is scoped to the lifetime
        // of the for sub-statement
        parseContext.pushScope();

        // initializer
        TIntermNode* initNode = nullptr;
        if (! acceptControlDeclaration(initNode)) {
            TIntermTyped* initExpr = nullptr;
            acceptExpression(initExpr);
            initNode = initExpr;
        }
        // SEMI_COLON
        if (! acceptTokenClass(EHTokSemicolon))
            expected(";");

        parseContext.nestLooping();

        // condition SEMI_COLON
        acceptExpression(condition);
        if (! acceptTokenClass(EHTokSemicolon))
            expected(";");

        // iterator SEMI_COLON
        TIntermTyped* iterator = nullptr;
        acceptExpression(iterator);
        if (! acceptTokenClass(EHTokRightParen))
            expected(")");

        // statement
        if (! acceptScopedStatement(statement)) {
            expected("for sub-statement");
            return false;
        }

        statement = intermediate.addForLoop(statement, initNode, condition, iterator, true, loc);

        parseContext.popScope();
        parseContext.unnestLooping();

        return true;
    }

    default:
        return false;
    }
}

// jump_statement
//      : CONTINUE SEMICOLON
//      | BREAK SEMICOLON
//      | DISCARD SEMICOLON
//      | RETURN SEMICOLON
//      | RETURN expression SEMICOLON
//
bool HlslGrammar::acceptJumpStatement(TIntermNode*& statement)
{
    EHlslTokenClass jump = peek();
    switch (jump) {
    case EHTokContinue:
    case EHTokBreak:
    case EHTokDiscard:
    case EHTokReturn:
        advanceToken();
        break;
    default:
        // not something we handle in this function
        return false;
    }

    switch (jump) {
    case EHTokContinue:
        statement = intermediate.addBranch(EOpContinue, token.loc);
        break;
    case EHTokBreak:
        statement = intermediate.addBranch(EOpBreak, token.loc);
        break;
    case EHTokDiscard:
        statement = intermediate.addBranch(EOpKill, token.loc);
        break;

    case EHTokReturn:
    {
        // expression
        TIntermTyped* node;
        if (acceptExpression(node)) {
            // hook it up
            statement = parseContext.handleReturnValue(token.loc, node);
        } else
            statement = intermediate.addBranch(EOpReturn, token.loc);
        break;
    }

    default:
        assert(0);
        return false;
    }

    // SEMICOLON
    if (! acceptTokenClass(EHTokSemicolon))
        expected(";");

    return true;
}

// case_label
//      : CASE expression COLON
//
bool HlslGrammar::acceptCaseLabel(TIntermNode*& statement)
{
    TSourceLoc loc = token.loc;
    if (! acceptTokenClass(EHTokCase))
        return false;

    TIntermTyped* expression;
    if (! acceptExpression(expression)) {
        expected("case expression");
        return false;
    }

    if (! acceptTokenClass(EHTokColon)) {
        expected(":");
        return false;
    }

    statement = parseContext.intermediate.addBranch(EOpCase, expression, loc);

    return true;
}

// default_label
//      : DEFAULT COLON
//
bool HlslGrammar::acceptDefaultLabel(TIntermNode*& statement)
{
    TSourceLoc loc = token.loc;
    if (! acceptTokenClass(EHTokDefault))
        return false;

    if (! acceptTokenClass(EHTokColon)) {
        expected(":");
        return false;
    }

    statement = parseContext.intermediate.addBranch(EOpDefault, loc);

    return true;
}

// array_specifier
//      : LEFT_BRACKET integer_expression RGHT_BRACKET ... // optional
//      : LEFT_BRACKET RGHT_BRACKET // optional
//
void HlslGrammar::acceptArraySpecifier(TArraySizes*& arraySizes)
{
    arraySizes = nullptr;

    // Early-out if there aren't any array dimensions
    if (!peekTokenClass(EHTokLeftBracket))
        return;

    // If we get here, we have at least one array dimension.  This will track the sizes we find.
    arraySizes = new TArraySizes;

    // Collect each array dimension.
    while (acceptTokenClass(EHTokLeftBracket)) {
        TSourceLoc loc = token.loc;
        TIntermTyped* sizeExpr = nullptr;

        // Array sizing expression is optional.  If ommitted, array will be later sized by initializer list.
        const bool hasArraySize = acceptAssignmentExpression(sizeExpr);

        if (! acceptTokenClass(EHTokRightBracket)) {
            expected("]");
            return;
        }

        if (hasArraySize) {
            TArraySize arraySize;
            parseContext.arraySizeCheck(loc, sizeExpr, arraySize);
            arraySizes->addInnerSize(arraySize);
        } else {
            arraySizes->addInnerSize(0);  // sized by initializers.
        }
    }
}

// post_decls
//      : COLON semantic // optional
//        COLON PACKOFFSET LEFT_PAREN c[Subcomponent][.component] RIGHT_PAREN // optional
//        COLON REGISTER LEFT_PAREN [shader_profile,] Type#[subcomp]opt (COMMA SPACEN)opt RIGHT_PAREN // optional
//        COLON LAYOUT layout_qualifier_list
//        annotations // optional
//
void HlslGrammar::acceptPostDecls(TQualifier& qualifier)
{
    do {
        // COLON
        if (acceptTokenClass(EHTokColon)) {
            HlslToken idToken;
            if (peekTokenClass(EHTokLayout))
                acceptLayoutQualifierList(qualifier);
            else if (acceptTokenClass(EHTokPackOffset)) {
                // PACKOFFSET LEFT_PAREN c[Subcomponent][.component] RIGHT_PAREN
                if (! acceptTokenClass(EHTokLeftParen)) {
                    expected("(");
                    return;
                }
                HlslToken locationToken;
                if (! acceptIdentifier(locationToken)) {
                    expected("c[subcomponent][.component]");
                    return;
                }
                HlslToken componentToken;
                if (acceptTokenClass(EHTokDot)) {
                    if (! acceptIdentifier(componentToken)) {
                        expected("component");
                        return;
                    }
                }
                if (! acceptTokenClass(EHTokRightParen)) {
                    expected(")");
                    break;
                }
                parseContext.handlePackOffset(locationToken.loc, qualifier, *locationToken.string, componentToken.string);
            } else if (! acceptIdentifier(idToken)) {
                expected("layout, semantic, packoffset, or register");
                return;
            } else if (*idToken.string == "register") {
                // REGISTER LEFT_PAREN [shader_profile,] Type#[subcomp]opt (COMMA SPACEN)opt RIGHT_PAREN
                // LEFT_PAREN
                if (! acceptTokenClass(EHTokLeftParen)) {
                    expected("(");
                    return;
                }
                HlslToken registerDesc;  // for Type#
                HlslToken profile;
                if (! acceptIdentifier(registerDesc)) {
                    expected("register number description");
                    return;
                }
                if (registerDesc.string->size() > 1 && !isdigit((*registerDesc.string)[1]) &&
                                                       acceptTokenClass(EHTokComma)) {
                    // Then we didn't really see the registerDesc yet, it was
                    // actually the profile.  Adjust...
                    profile = registerDesc;
                    if (! acceptIdentifier(registerDesc)) {
                        expected("register number description");
                        return;
                    }
                }
                int subComponent = 0;
                if (acceptTokenClass(EHTokLeftBracket)) {
                    // LEFT_BRACKET subcomponent RIGHT_BRACKET
                    if (! peekTokenClass(EHTokIntConstant)) {
                        expected("literal integer");
                        return;
                    }
                    subComponent = token.i;
                    advanceToken();
                    if (! acceptTokenClass(EHTokRightBracket)) {
                        expected("]");
                        break;
                    }
                }
                // (COMMA SPACEN)opt
                HlslToken spaceDesc;
                if (acceptTokenClass(EHTokComma)) {
                    if (! acceptIdentifier(spaceDesc)) {
                        expected ("space identifier");
                        return;
                    }
                }
                // RIGHT_PAREN
                if (! acceptTokenClass(EHTokRightParen)) {
                    expected(")");
                    break;
                }
                parseContext.handleRegister(registerDesc.loc, qualifier, profile.string, *registerDesc.string, subComponent, spaceDesc.string);
            } else {
                // semantic, in idToken.string
                parseContext.handleSemantic(idToken.loc, qualifier, *idToken.string);
            }
        } else if (peekTokenClass(EHTokLeftAngle))
            acceptAnnotations(qualifier);
        else
            break;

    } while (true);
}

} // end namespace glslang
