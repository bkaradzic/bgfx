// Copyright (c) 2017 Google Inc.
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

#ifndef LIBSPIRV_OPT_SCALAR_REPLACEMENT_PASS_H_
#define LIBSPIRV_OPT_SCALAR_REPLACEMENT_PASS_H_

#include "function.h"
#include "pass.h"
#include "type_manager.h"

#include <queue>

namespace spvtools {
namespace opt {

// Documented in optimizer.hpp
class ScalarReplacementPass : public Pass {
 public:
  ScalarReplacementPass() = default;

  const char* name() const override { return "scalar-replacement"; }

  // Attempts to scalarize all appropriate function scope variables. Returns
  // SuccessWithChange if any change is made.
  Status Process(ir::IRContext* c) override;

  ir::IRContext::Analysis GetPreservedAnalyses() override {
    return ir::IRContext::kAnalysisDefUse |
           ir::IRContext::kAnalysisInstrToBlockMapping |
           ir::IRContext::kAnalysisDecorations |
           ir::IRContext::kAnalysisCombinators | ir::IRContext::kAnalysisCFG |
           ir::IRContext::kAnalysisNameMap;
  }

 private:
  // Small container for tracking statistics about variables.
  //
  // TODO(alanbaker): Develop some useful heuristics to tune this pass.
  struct VariableStats {
    uint32_t num_partial_accesses;
    uint32_t num_full_accesses;
  };

  // Attempts to scalarize all appropriate function scope variables in
  // |function|. Returns SuccessWithChange if any changes are mode.
  Status ProcessFunction(ir::Function* function);

  // Returns true if |varInst| can be scalarized.
  //
  // Examines the use chain of |varInst| to verify all uses are valid for
  // scalarization.
  bool CanReplaceVariable(const ir::Instruction* varInst) const;

  // Returns true if |typeInst| is an acceptable type to scalarize.
  //
  // Allows all aggregate types except runtime arrays. Additionally, checks the
  // that the number of elements that would be scalarized is within bounds.
  bool CheckType(const ir::Instruction* typeInst) const;

  // Returns true if all the decorations for |varInst| are acceptable for
  // scalarization.
  bool CheckAnnotations(const ir::Instruction* varInst) const;

  // Returns true if all the decorations for |typeInst| are acceptable for
  // scalarization.
  bool CheckTypeAnnotations(const ir::Instruction* typeInst) const;

  // Returns true if the uses of |inst| are acceptable for scalarization.
  //
  // Recursively checks all the uses of |inst|. For |inst| specifically, only
  // allows SpvOpAccessChain, SpvOpInBoundsAccessChain, SpvOpLoad and
  // SpvOpStore. Access chains must have the first index be a compile-time
  // constant. Subsequent uses of access chains (including other access chains)
  // are checked in a more relaxed manner.
  bool CheckUses(const ir::Instruction* inst) const;

  // Helper function for the above |CheckUses|.
  //
  // This version tracks some stats about the current OpVariable. These stats
  // are used to drive heuristics about when to scalarize.
  bool CheckUses(const ir::Instruction* inst, VariableStats* stats) const;

  // Relaxed helper function for |CheckUses|.
  bool CheckUsesRelaxed(const ir::Instruction* inst) const;

  // Transfers appropriate decorations from |source| to |replacements|.
  void TransferAnnotations(const ir::Instruction* source,
                           std::vector<ir::Instruction*>* replacements);

  // Scalarizes |inst| and updates its uses.
  //
  // |inst| must be an OpVariable. It is replaced with an OpVariable for each
  // for element of the composite type. Uses of |inst| are updated as
  // appropriate. If the replacement variables are themselves scalarizable, they
  // get added to |worklist| for further processing. If any replacement
  // variable ends up with no uses it is erased. Returns false if any
  // subsequent access chain is out of bounds.
  bool ReplaceVariable(ir::Instruction* inst,
                       std::queue<ir::Instruction*>* worklist);

  // Returns the underlying storage type for |inst|.
  //
  // |inst| must be an OpVariable. Returns the type that is pointed to by
  // |inst|.
  ir::Instruction* GetStorageType(const ir::Instruction* inst) const;

  // Returns true if the load can be scalarized.
  //
  // |inst| must be an OpLoad. Returns true if |index| is the pointer operand of
  // |inst| and the load is not from volatile memory.
  bool CheckLoad(const ir::Instruction* inst, uint32_t index) const;

  // Returns true if the store can be scalarized.
  //
  // |inst| must be an OpStore. Returns true if |index| is the pointer operand
  // of |inst| and the store is not to volatile memory.
  bool CheckStore(const ir::Instruction* inst, uint32_t index) const;

  // Creates a variable of type |typeId| from the |index|'th element of
  // |varInst|. The new variable is added to |replacements|.
  void CreateVariable(uint32_t typeId, ir::Instruction* varInst, uint32_t index,
                      std::vector<ir::Instruction*>* replacements);

  // Populates |replacements| with a new OpVariable for each element of |inst|.
  //
  // |inst| must be an OpVariable of a composite type. New variables are
  // initialized the same as the corresponding index in |inst|. |replacements|
  // will contain a variable for each element of the composite with matching
  // indexes (i.e. the 0'th element of |inst| is the 0'th entry of
  // |replacements|).
  void CreateReplacementVariables(ir::Instruction* inst,
                                  std::vector<ir::Instruction*>* replacements);

  // Returns the value of an OpConstant of integer type.
  //
  // |constant| must use two or fewer words to generate the value.
  size_t GetConstantInteger(const ir::Instruction* constant) const;

  // Returns the integer literal for |op|.
  size_t GetIntegerLiteral(const ir::Operand& op) const;

  // Returns the array length for |arrayInst|.
  size_t GetArrayLength(const ir::Instruction* arrayInst) const;

  // Returns the number of elements in |type|.
  //
  // |type| must be a vector or matrix type.
  size_t GetNumElements(const ir::Instruction* type) const;

  // Returns an id for a pointer to |id|.
  uint32_t GetOrCreatePointerType(uint32_t id);

  // Creates the initial value for the |index| element of |source| in |newVar|.
  //
  // If there is an initial value for |source| for element |index|, it is
  // appended as an operand on |newVar|. If the initial value is OpUndef, no
  // initial value is added to |newVar|.
  void GetOrCreateInitialValue(ir::Instruction* source, uint32_t index,
                               ir::Instruction* newVar);

  // Replaces the load to the entire composite.
  //
  // Generates a load for each replacement variable and then creates a new
  // composite by combining all of the loads.
  //
  // |load| must be a load.
  void ReplaceWholeLoad(ir::Instruction* load,
                        const std::vector<ir::Instruction*>& replacements);

  // Replaces the store to the entire composite.
  //
  // Generates a composite extract and store for each element in the scalarized
  // variable from the original store data input.
  void ReplaceWholeStore(ir::Instruction* store,
                         const std::vector<ir::Instruction*>& replacements);

  // Replaces an access chain to the composite variable with either a direct use
  // of the appropriate replacement variable or another access chain with the
  // replacement variable as the base and one fewer indexes. Returns false if
  // the chain has an out of bounds access.
  bool ReplaceAccessChain(ir::Instruction* chain,
                          const std::vector<ir::Instruction*>& replacements);

  // Maps storage type to a pointer type enclosing that type.
  std::unordered_map<uint32_t, uint32_t> pointee_to_pointer_;

  // Maps type id to OpConstantNull for that type.
  std::unordered_map<uint32_t, uint32_t> type_to_null_;
};

}  // namespace opt
}  // namespace spvtools

#endif  // LIBSPIRV_OPT_SCALAR_REPLACEMENT_PASS_H_
