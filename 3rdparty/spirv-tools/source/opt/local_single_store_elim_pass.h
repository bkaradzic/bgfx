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

#ifndef LIBSPIRV_OPT_LOCAL_SINGLE_STORE_ELIM_PASS_H_
#define LIBSPIRV_OPT_LOCAL_SINGLE_STORE_ELIM_PASS_H_

#include <algorithm>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "basic_block.h"
#include "def_use_manager.h"
#include "mem_pass.h"
#include "module.h"

namespace spvtools {
namespace opt {

// See optimizer.hpp for documentation.
class LocalSingleStoreElimPass : public MemPass {
  using cbb_ptr = const ir::BasicBlock*;

 public:
  LocalSingleStoreElimPass();
  const char* name() const override { return "eliminate-local-single-store"; }
  Status Process(ir::IRContext* irContext) override;

  ir::IRContext::Analysis GetPreservedAnalyses() override {
    return ir::IRContext::kAnalysisDefUse;
  }

 private:
  // Return true if all refs through |ptrId| are only loads or stores and
  // cache ptrId in supported_ref_ptrs_. TODO(dnovillo): This function is
  // replicated in other passes and it's slightly different in every pass. Is it
  // possible to make one common implementation?
  bool HasOnlySupportedRefs(uint32_t ptrId);

  // Find all function scope variables in |func| that are stored to
  // only once (SSA) and map to their stored value id. Only analyze
  // variables of scalar, vector, matrix types and struct and array
  // types comprising only these types. Currently this analysis is
  // is not done in the presence of function calls. TODO(): Allow
  // analysis in the presence of function calls.
  void SingleStoreAnalyze(ir::Function* func);

  using GetBlocksFunction =
      std::function<const std::vector<ir::BasicBlock*>*(const ir::BasicBlock*)>;

  /// Returns the block successors function for the augmented CFG.
  GetBlocksFunction AugmentedCFGSuccessorsFunction() const;

  /// Returns the block predecessors function for the augmented CFG.
  GetBlocksFunction AugmentedCFGPredecessorsFunction() const;

  // Calculate immediate dominators for |func|'s CFG. Leaves result
  // in idom_. Entries for augmented CFG (pseudo blocks) are not created.
  // TODO(dnovillo): Move to new CFG class.
  void CalculateImmediateDominators(ir::Function* func);

  // Return true if instruction in |blk0| at ordinal position |idx0|
  // dominates instruction in |blk1| at position |idx1|.
  bool Dominates(ir::BasicBlock* blk0, uint32_t idx0, ir::BasicBlock* blk1,
                 uint32_t idx1);

  // For each load of an SSA variable in |func|, replace all uses of
  // the load with the value stored if the store dominates the load.
  // Assumes that SingleStoreAnalyze() has just been run. Return true
  // if any instructions are modified.
  bool SingleStoreProcess(ir::Function* func);

  // Do "single-store" optimization of function variables defined only
  // with a single non-access-chain store in |func|. Replace all their
  // non-access-chain loads with the value that is stored and eliminate
  // any resulting dead code.
  bool LocalSingleStoreElim(ir::Function* func);

  // Initialize extensions whitelist
  void InitExtensions();

  // Return true if all extensions in this module are allowed by this pass.
  bool AllExtensionsSupported() const;

  void Initialize(ir::IRContext* irContext);
  Pass::Status ProcessImpl();

  // Map from block's label id to block
  std::unordered_map<uint32_t, ir::BasicBlock*> label2block_;

  // Map from SSA Variable to its single store
  std::unordered_map<uint32_t, ir::Instruction*> ssa_var2store_;

  // Map from store to its ordinal position in its block.
  std::unordered_map<ir::Instruction*, uint32_t> store2idx_;

  // Map from store to its block.
  std::unordered_map<ir::Instruction*, ir::BasicBlock*> store2blk_;

  // Set of non-SSA Variables
  std::unordered_set<uint32_t> non_ssa_vars_;

  // Variables with only supported references, ie. loads and stores using
  // variable directly or through non-ptr access chains.
  std::unordered_set<uint32_t> supported_ref_ptrs_;

  // CFG Predecessors
  std::unordered_map<const ir::BasicBlock*, std::vector<ir::BasicBlock*>>
      predecessors_map_;

  // CFG Successors
  std::unordered_map<const ir::BasicBlock*, std::vector<ir::BasicBlock*>>
      successors_map_;

  // CFG Augmented Predecessors
  std::unordered_map<const ir::BasicBlock*, std::vector<ir::BasicBlock*>>
      augmented_predecessors_map_;

  // CFG Augmented Successors
  std::unordered_map<const ir::BasicBlock*, std::vector<ir::BasicBlock*>>
      augmented_successors_map_;

  // Immediate Dominator Map
  // If block has no idom it points to itself.
  std::unordered_map<ir::BasicBlock*, ir::BasicBlock*> idom_;

  // Extensions supported by this pass.
  std::unordered_set<std::string> extensions_whitelist_;
};

}  // namespace opt
}  // namespace spvtools

#endif  // LIBSPIRV_OPT_LOCAL_SINGLE_STORE_ELIM_PASS_H_
