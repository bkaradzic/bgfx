// Copyright (c) 2017 The Khronos Group Inc.
// Copyright (c) 2017 Valve Corporation
// Copyright (c) 2017 LunarG Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "insert_extract_elim.h"

#include "composite.h"
#include "ir_context.h"
#include "iterator.h"
#include "latest_version_glsl_std_450_header.h"

#include <vector>

namespace spvtools {
namespace opt {

namespace {

const uint32_t kConstantValueInIdx = 0;
const uint32_t kExtractCompositeIdInIdx = 0;
const uint32_t kInsertObjectIdInIdx = 0;
const uint32_t kInsertCompositeIdInIdx = 1;
const uint32_t kVectorShuffleVec1IdInIdx = 0;
const uint32_t kVectorShuffleVec2IdInIdx = 1;
const uint32_t kVectorShuffleCompsInIdx = 2;
const uint32_t kTypeVectorCompTypeIdInIdx = 0;
const uint32_t kTypeVectorLengthInIdx = 1;
const uint32_t kTypeFloatWidthInIdx = 0;
const uint32_t kExtInstSetIdInIdx = 0;
const uint32_t kExtInstInstructionInIdx = 1;
const uint32_t kFMixXIdInIdx = 2;
const uint32_t kFMixYIdInIdx = 3;
const uint32_t kFMixAIdInIdx = 4;

}  // anonymous namespace

uint32_t InsertExtractElimPass::DoExtract(ir::Instruction* compInst,
                                          std::vector<uint32_t>* pExtIndices,
                                          uint32_t extOffset) {
  ir::Instruction* cinst = compInst;
  uint32_t cid = 0;
  uint32_t replId = 0;
  while (true) {
    if (cinst->opcode() == SpvOpCompositeInsert) {
      if (ExtInsMatch(*pExtIndices, cinst, extOffset)) {
        // Match! Use inserted value as replacement
        replId = cinst->GetSingleWordInOperand(kInsertObjectIdInIdx);
        break;
      } else if (ExtInsConflict(*pExtIndices, cinst, extOffset)) {
        // If extract has fewer indices than the insert, stop searching.
        // Otherwise increment offset of extract indices considered and
        // continue searching through the inserted value
        if (pExtIndices->size() - extOffset < cinst->NumInOperands() - 2) {
          break;
        } else {
          extOffset += cinst->NumInOperands() - 2;
          cid = cinst->GetSingleWordInOperand(kInsertObjectIdInIdx);
        }
      } else {
        // Consider next composite in insert chain
        cid = cinst->GetSingleWordInOperand(kInsertCompositeIdInIdx);
      }
    } else if (cinst->opcode() == SpvOpVectorShuffle) {
      // Get length of vector1
      uint32_t v1_id = cinst->GetSingleWordInOperand(kVectorShuffleVec1IdInIdx);
      ir::Instruction* v1_inst = get_def_use_mgr()->GetDef(v1_id);
      uint32_t v1_type_id = v1_inst->type_id();
      ir::Instruction* v1_type_inst = get_def_use_mgr()->GetDef(v1_type_id);
      uint32_t v1_len =
          v1_type_inst->GetSingleWordInOperand(kTypeVectorLengthInIdx);
      // Get shuffle idx
      uint32_t comp_idx = (*pExtIndices)[extOffset];
      uint32_t shuffle_idx =
          cinst->GetSingleWordInOperand(kVectorShuffleCompsInIdx + comp_idx);
      // If undefined, give up
      // TODO(greg-lunarg): Return OpUndef
      if (shuffle_idx == 0xFFFFFFFF) break;
      if (shuffle_idx < v1_len) {
        cid = v1_id;
        (*pExtIndices)[extOffset] = shuffle_idx;
      } else {
        cid = cinst->GetSingleWordInOperand(kVectorShuffleVec2IdInIdx);
        (*pExtIndices)[extOffset] = shuffle_idx - v1_len;
      }
    } else if (cinst->opcode() == SpvOpExtInst &&
               cinst->GetSingleWordInOperand(kExtInstSetIdInIdx) ==
                   get_feature_mgr()->GetExtInstImportId_GLSLstd450() &&
               cinst->GetSingleWordInOperand(kExtInstInstructionInIdx) ==
                   GLSLstd450FMix) {
      // If mixing value component is 0 or 1 we just match with x or y.
      // Otherwise give up.
      uint32_t comp_idx = (*pExtIndices)[extOffset];
      std::vector<uint32_t> aIndices = {comp_idx};
      uint32_t a_id = cinst->GetSingleWordInOperand(kFMixAIdInIdx);
      ir::Instruction* a_inst = get_def_use_mgr()->GetDef(a_id);
      uint32_t a_comp_id = DoExtract(a_inst, &aIndices, 0);
      if (a_comp_id == 0) break;
      ir::Instruction* a_comp_inst = get_def_use_mgr()->GetDef(a_comp_id);
      if (a_comp_inst->opcode() != SpvOpConstant) break;
      // If a value is not 32-bit, give up
      uint32_t a_comp_type_id = a_comp_inst->type_id();
      ir::Instruction* a_comp_type = get_def_use_mgr()->GetDef(a_comp_type_id);
      if (a_comp_type->GetSingleWordInOperand(kTypeFloatWidthInIdx) != 32)
        break;
      uint32_t u = a_comp_inst->GetSingleWordInOperand(kConstantValueInIdx);
      float* fp = reinterpret_cast<float*>(&u);
      if (*fp == 0.0)
        cid = cinst->GetSingleWordInOperand(kFMixXIdInIdx);
      else if (*fp == 1.0)
        cid = cinst->GetSingleWordInOperand(kFMixYIdInIdx);
      else
        break;
    } else {
      break;
    }
    cinst = get_def_use_mgr()->GetDef(cid);
  }
  // If search ended with CompositeConstruct or ConstantComposite
  // and the extract has one index, return the appropriate component.
  // TODO(greg-lunarg): Handle multiple-indices, ConstantNull, special
  // vector composition, and additional CompositeInsert.
  if (replId == 0 &&
      (cinst->opcode() == SpvOpCompositeConstruct ||
       cinst->opcode() == SpvOpConstantComposite) &&
      (*pExtIndices).size() - extOffset == 1) {
    uint32_t compIdx = (*pExtIndices)[extOffset];
    // If a vector CompositeConstruct we make sure all preceding
    // components are of component type (not vector composition).
    uint32_t ctype_id = cinst->type_id();
    ir::Instruction* ctype_inst = get_def_use_mgr()->GetDef(ctype_id);
    if (ctype_inst->opcode() == SpvOpTypeVector &&
        cinst->opcode() == SpvOpConstantComposite) {
      uint32_t vec_comp_type_id =
          ctype_inst->GetSingleWordInOperand(kTypeVectorCompTypeIdInIdx);
      if (compIdx < cinst->NumInOperands()) {
        uint32_t i = 0;
        for (; i <= compIdx; i++) {
          uint32_t compId = cinst->GetSingleWordInOperand(i);
          ir::Instruction* componentInst = get_def_use_mgr()->GetDef(compId);
          if (componentInst->type_id() != vec_comp_type_id) break;
        }
        if (i > compIdx) replId = cinst->GetSingleWordInOperand(compIdx);
      }
    } else {
      replId = cinst->GetSingleWordInOperand(compIdx);
    }
  }
  return replId;
}

bool InsertExtractElimPass::EliminateInsertExtract(ir::Function* func) {
  bool modified = false;
  for (auto bi = func->begin(); bi != func->end(); ++bi) {
    ir::Instruction* inst = &*bi->begin();
    while (inst) {
      switch (inst->opcode()) {
        case SpvOpCompositeExtract: {
          uint32_t cid = inst->GetSingleWordInOperand(kExtractCompositeIdInIdx);
          ir::Instruction* cinst = get_def_use_mgr()->GetDef(cid);
          // Capture extract indices
          std::vector<uint32_t> extIndices;
          uint32_t icnt = 0;
          inst->ForEachInOperand([&icnt, &extIndices](const uint32_t* idp) {
            if (icnt > 0) extIndices.push_back(*idp);
            ++icnt;
          });
          // Offset of extract indices being compared to insert indices.
          // Offset increases as indices are matched.
          uint32_t replId = DoExtract(cinst, &extIndices, 0);
          if (replId != 0) {
            const uint32_t extId = inst->result_id();
            (void)context()->ReplaceAllUsesWith(extId, replId);
            inst = context()->KillInst(inst);
            modified = true;
          } else {
            inst = inst->NextNode();
          }
        } break;
        default:
          inst = inst->NextNode();
          break;
      }
    }
  }
  return modified;
}

void InsertExtractElimPass::Initialize(ir::IRContext* c) {
  InitializeProcessing(c);
}

Pass::Status InsertExtractElimPass::ProcessImpl() {
  // Process all entry point functions.
  ProcessFunction pfn = [this](ir::Function* fp) {
    return EliminateInsertExtract(fp);
  };
  bool modified = ProcessEntryPointCallTree(pfn, get_module());
  return modified ? Status::SuccessWithChange : Status::SuccessWithoutChange;
}

InsertExtractElimPass::InsertExtractElimPass() {}

Pass::Status InsertExtractElimPass::Process(ir::IRContext* c) {
  Initialize(c);
  return ProcessImpl();
}

}  // namespace opt
}  // namespace spvtools
