// Copyright (c) 2018 Google LLC
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

#ifndef LIBSPIRV_OPT_IF_CONVERSION_H_
#define LIBSPIRV_OPT_IF_CONVERSION_H_

#include "basic_block.h"
#include "ir_builder.h"
#include "pass.h"
#include "types.h"

namespace spvtools {
namespace opt {

// See optimizer.hpp for documentation.
class IfConversion : public Pass {
 public:
  const char* name() const override { return "if-conversion"; }
  Status Process(ir::IRContext* context) override;

  ir::IRContext::Analysis GetPreservedAnalyses() override {
    return ir::IRContext::kAnalysisDefUse |
           ir::IRContext::kAnalysisDominatorAnalysis |
           ir::IRContext::kAnalysisInstrToBlockMapping |
           ir::IRContext::kAnalysisCFG | ir::IRContext::kAnalysisNameMap;
  }

 private:
  // Returns true if |id| is a valid type for use with OpSelect. OpSelect only
  // allows scalars, vectors and pointers as valid inputs.
  bool CheckType(uint32_t id);

  // Returns the basic block containing |id|.
  ir::BasicBlock* GetBlock(uint32_t id);

  // Returns the basic block for the |predecessor|'th index predecessor of
  // |phi|.
  ir::BasicBlock* GetIncomingBlock(ir::Instruction* phi, uint32_t predecessor);

  // Returns the instruction defining the |predecessor|'th index of |phi|.
  ir::Instruction* GetIncomingValue(ir::Instruction* phi, uint32_t predecessor);

  // Returns the id of a OpCompositeConstruct boolean vector. The composite has
  // the same number of elements as |vec_data_ty| and each member is |cond|.
  // |where| indicates the location in |block| to insert the composite
  // construct. If necessary, this function will also construct the necessary
  // type instructions for the boolean vector.
  uint32_t SplatCondition(analysis::Vector* vec_data_ty, uint32_t cond,
                          InstructionBuilder* builder);

  // Returns true if none of |phi|'s users are in |block|.
  bool CheckPhiUsers(ir::Instruction* phi, ir::BasicBlock* block);

  // Returns |false| if |block| is not appropriate to transform. Only
  // transforms blocks with two predecessors. Neither incoming block can be
  // dominated by |block|. Both predecessors must share a common dominator that
  // is terminated by a conditional branch.
  bool CheckBlock(ir::BasicBlock* block, DominatorAnalysis* dominators,
                  ir::BasicBlock** common);
};

}  //  namespace opt
}  //  namespace spvtools

#endif  //  LIBSPIRV_OPT_IF_CONVERSION_H_
