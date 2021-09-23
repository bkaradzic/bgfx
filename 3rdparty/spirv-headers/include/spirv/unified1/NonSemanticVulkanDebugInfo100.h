// Copyright (c) 2018 The Khronos Group Inc.
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and/or associated documentation files (the "Materials"),
// to deal in the Materials without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Materials, and to permit persons to whom the
// Materials are furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Materials.
// 
// MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS KHRONOS
// STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS SPECIFICATIONS AND
// HEADER INFORMATION ARE LOCATED AT https://www.khronos.org/registry/ 
// 
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM,OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE USE OR OTHER DEALINGS
// IN THE MATERIALS.

#ifndef SPIRV_UNIFIED1_NonSemanticVulkanDebugInfo100_H_
#define SPIRV_UNIFIED1_NonSemanticVulkanDebugInfo100_H_

#ifdef __cplusplus
extern "C" {
#endif

enum {
    NonSemanticVulkanDebugInfo100Version = 100,
    NonSemanticVulkanDebugInfo100Version_BitWidthPadding = 0x7fffffff
};
enum {
    NonSemanticVulkanDebugInfo100Revision = 6,
    NonSemanticVulkanDebugInfo100Revision_BitWidthPadding = 0x7fffffff
};

enum NonSemanticVulkanDebugInfo100Instructions {
    NonSemanticVulkanDebugInfo100DebugInfoNone = 0,
    NonSemanticVulkanDebugInfo100DebugCompilationUnit = 1,
    NonSemanticVulkanDebugInfo100DebugTypeBasic = 2,
    NonSemanticVulkanDebugInfo100DebugTypePointer = 3,
    NonSemanticVulkanDebugInfo100DebugTypeQualifier = 4,
    NonSemanticVulkanDebugInfo100DebugTypeArray = 5,
    NonSemanticVulkanDebugInfo100DebugTypeVector = 6,
    NonSemanticVulkanDebugInfo100DebugTypedef = 7,
    NonSemanticVulkanDebugInfo100DebugTypeFunction = 8,
    NonSemanticVulkanDebugInfo100DebugTypeEnum = 9,
    NonSemanticVulkanDebugInfo100DebugTypeComposite = 10,
    NonSemanticVulkanDebugInfo100DebugTypeMember = 11,
    NonSemanticVulkanDebugInfo100DebugTypeInheritance = 12,
    NonSemanticVulkanDebugInfo100DebugTypePtrToMember = 13,
    NonSemanticVulkanDebugInfo100DebugTypeTemplate = 14,
    NonSemanticVulkanDebugInfo100DebugTypeTemplateParameter = 15,
    NonSemanticVulkanDebugInfo100DebugTypeTemplateTemplateParameter = 16,
    NonSemanticVulkanDebugInfo100DebugTypeTemplateParameterPack = 17,
    NonSemanticVulkanDebugInfo100DebugGlobalVariable = 18,
    NonSemanticVulkanDebugInfo100DebugFunctionDeclaration = 19,
    NonSemanticVulkanDebugInfo100DebugFunction = 20,
    NonSemanticVulkanDebugInfo100DebugLexicalBlock = 21,
    NonSemanticVulkanDebugInfo100DebugLexicalBlockDiscriminator = 22,
    NonSemanticVulkanDebugInfo100DebugScope = 23,
    NonSemanticVulkanDebugInfo100DebugNoScope = 24,
    NonSemanticVulkanDebugInfo100DebugInlinedAt = 25,
    NonSemanticVulkanDebugInfo100DebugLocalVariable = 26,
    NonSemanticVulkanDebugInfo100DebugInlinedVariable = 27,
    NonSemanticVulkanDebugInfo100DebugDeclare = 28,
    NonSemanticVulkanDebugInfo100DebugValue = 29,
    NonSemanticVulkanDebugInfo100DebugOperation = 30,
    NonSemanticVulkanDebugInfo100DebugExpression = 31,
    NonSemanticVulkanDebugInfo100DebugMacroDef = 32,
    NonSemanticVulkanDebugInfo100DebugMacroUndef = 33,
    NonSemanticVulkanDebugInfo100DebugImportedEntity = 34,
    NonSemanticVulkanDebugInfo100DebugSource = 35,
    NonSemanticVulkanDebugInfo100DebugFunctionDefinition = 101,
    NonSemanticVulkanDebugInfo100DebugSourceContinued = 102,
    NonSemanticVulkanDebugInfo100DebugLine = 103,
    NonSemanticVulkanDebugInfo100DebugNoLine = 104,
    NonSemanticVulkanDebugInfo100DebugBuildIdentifier = 105,
    NonSemanticVulkanDebugInfo100DebugStoragePath = 106,
    NonSemanticVulkanDebugInfo100DebugEntryPoint = 107,
    NonSemanticVulkanDebugInfo100DebugTypeMatrix = 108,
    NonSemanticVulkanDebugInfo100InstructionsMax = 0x7fffffff
};


enum NonSemanticVulkanDebugInfo100DebugInfoFlags {
    NonSemanticVulkanDebugInfo100None = 0x0000,
    NonSemanticVulkanDebugInfo100FlagIsProtected = 0x01,
    NonSemanticVulkanDebugInfo100FlagIsPrivate = 0x02,
    NonSemanticVulkanDebugInfo100FlagIsPublic = 0x03,
    NonSemanticVulkanDebugInfo100FlagIsLocal = 0x04,
    NonSemanticVulkanDebugInfo100FlagIsDefinition = 0x08,
    NonSemanticVulkanDebugInfo100FlagFwdDecl = 0x10,
    NonSemanticVulkanDebugInfo100FlagArtificial = 0x20,
    NonSemanticVulkanDebugInfo100FlagExplicit = 0x40,
    NonSemanticVulkanDebugInfo100FlagPrototyped = 0x80,
    NonSemanticVulkanDebugInfo100FlagObjectPointer = 0x100,
    NonSemanticVulkanDebugInfo100FlagStaticMember = 0x200,
    NonSemanticVulkanDebugInfo100FlagIndirectVariable = 0x400,
    NonSemanticVulkanDebugInfo100FlagLValueReference = 0x800,
    NonSemanticVulkanDebugInfo100FlagRValueReference = 0x1000,
    NonSemanticVulkanDebugInfo100FlagIsOptimized = 0x2000,
    NonSemanticVulkanDebugInfo100FlagIsEnumClass = 0x4000,
    NonSemanticVulkanDebugInfo100FlagTypePassByValue = 0x8000,
    NonSemanticVulkanDebugInfo100FlagTypePassByReference = 0x10000,
    NonSemanticVulkanDebugInfo100FlagUnknownPhysicalLayout = 0x20000,
    NonSemanticVulkanDebugInfo100DebugInfoFlagsMax = 0x7fffffff
};

enum NonSemanticVulkanDebugInfo100BuildIdentifierFlags {
    NonSemanticVulkanDebugInfo100IdentifierPossibleDuplicates = 0x01,
    NonSemanticVulkanDebugInfo100BuildIdentifierFlagsMax = 0x7fffffff
};

enum NonSemanticVulkanDebugInfo100DebugBaseTypeAttributeEncoding {
    NonSemanticVulkanDebugInfo100Unspecified = 0,
    NonSemanticVulkanDebugInfo100Address = 1,
    NonSemanticVulkanDebugInfo100Boolean = 2,
    NonSemanticVulkanDebugInfo100Float = 3,
    NonSemanticVulkanDebugInfo100Signed = 4,
    NonSemanticVulkanDebugInfo100SignedChar = 5,
    NonSemanticVulkanDebugInfo100Unsigned = 6,
    NonSemanticVulkanDebugInfo100UnsignedChar = 7,
    NonSemanticVulkanDebugInfo100DebugBaseTypeAttributeEncodingMax = 0x7fffffff
};

enum NonSemanticVulkanDebugInfo100DebugCompositeType {
    NonSemanticVulkanDebugInfo100Class = 0,
    NonSemanticVulkanDebugInfo100Structure = 1,
    NonSemanticVulkanDebugInfo100Union = 2,
    NonSemanticVulkanDebugInfo100DebugCompositeTypeMax = 0x7fffffff
};

enum NonSemanticVulkanDebugInfo100DebugTypeQualifier {
    NonSemanticVulkanDebugInfo100ConstType = 0,
    NonSemanticVulkanDebugInfo100VolatileType = 1,
    NonSemanticVulkanDebugInfo100RestrictType = 2,
    NonSemanticVulkanDebugInfo100AtomicType = 3,
    NonSemanticVulkanDebugInfo100DebugTypeQualifierMax = 0x7fffffff
};

enum NonSemanticVulkanDebugInfo100DebugOperation {
    NonSemanticVulkanDebugInfo100Deref = 0,
    NonSemanticVulkanDebugInfo100Plus = 1,
    NonSemanticVulkanDebugInfo100Minus = 2,
    NonSemanticVulkanDebugInfo100PlusUconst = 3,
    NonSemanticVulkanDebugInfo100BitPiece = 4,
    NonSemanticVulkanDebugInfo100Swap = 5,
    NonSemanticVulkanDebugInfo100Xderef = 6,
    NonSemanticVulkanDebugInfo100StackValue = 7,
    NonSemanticVulkanDebugInfo100Constu = 8,
    NonSemanticVulkanDebugInfo100Fragment = 9,
    NonSemanticVulkanDebugInfo100DebugOperationMax = 0x7fffffff
};

enum NonSemanticVulkanDebugInfo100DebugImportedEntity {
    NonSemanticVulkanDebugInfo100ImportedModule = 0,
    NonSemanticVulkanDebugInfo100ImportedDeclaration = 1,
    NonSemanticVulkanDebugInfo100DebugImportedEntityMax = 0x7fffffff
};


#ifdef __cplusplus
}
#endif

#endif // SPIRV_UNIFIED1_NonSemanticVulkanDebugInfo100_H_
