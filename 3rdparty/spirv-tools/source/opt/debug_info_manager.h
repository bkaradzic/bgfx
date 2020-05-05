// Copyright (c) 2020 Google LLC
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

#ifndef SOURCE_OPT_DEBUG_INFO_MANAGER_H_
#define SOURCE_OPT_DEBUG_INFO_MANAGER_H_

#include <unordered_map>

#include "source/opt/instruction.h"
#include "source/opt/module.h"

namespace spvtools {
namespace opt {
namespace analysis {

// A class for analyzing, managing, and creating OpenCL.DebugInfo.100 extension
// instructions.
class DebugInfoManager {
 public:
  // Constructs a debug information manager from the given |context|.
  DebugInfoManager(IRContext* context);

  DebugInfoManager(const DebugInfoManager&) = delete;
  DebugInfoManager(DebugInfoManager&&) = delete;
  DebugInfoManager& operator=(const DebugInfoManager&) = delete;
  DebugInfoManager& operator=(DebugInfoManager&&) = delete;

  friend bool operator==(const DebugInfoManager&, const DebugInfoManager&);
  friend bool operator!=(const DebugInfoManager& lhs,
                         const DebugInfoManager& rhs) {
    return !(lhs == rhs);
  }

  // Analyzes OpenCL.DebugInfo.100 instruction |dbg_inst|.
  void AnalyzeDebugInst(Instruction* dbg_inst);

  // Creates new DebugInlinedAt and returns its id. Its line operand is the
  // line number of |line| if |line| is not nullptr. Otherwise, its line operand
  // is the line number of lexical scope of |scope|. Its Scope and Inlined
  // operands are Scope and Inlined of |scope|.
  uint32_t CreateDebugInlinedAt(const Instruction* line,
                                const DebugScope& scope);

  // Returns a DebugInfoNone instruction.
  Instruction* GetDebugInfoNone();

  // Returns DebugInlinedAt whose id is |dbg_inlined_at_id|. If it does not
  // exist or it is not a DebugInlinedAt instruction, return nullptr.
  Instruction* GetDebugInlinedAt(uint32_t dbg_inlined_at_id);

  // Returns DebugFunction whose Function operand is |fn_id|. If it does not
  // exist, return nullptr.
  Instruction* GetDebugFunction(uint32_t fn_id) {
    auto dbg_fn_it = fn_id_to_dbg_fn_.find(fn_id);
    return dbg_fn_it == fn_id_to_dbg_fn_.end() ? nullptr : dbg_fn_it->second;
  }

  // Clones DebugInlinedAt whose id is |clone_inlined_at_id|. If
  // |clone_inlined_at_id| is not an id of DebugInlinedAt, returns nullptr.
  // If |insert_before| is given, inserts the new DebugInlinedAt before it.
  // Otherwise, inserts the new DebugInlinedAt into the debug instruction
  // section of the module.
  Instruction* CloneDebugInlinedAt(uint32_t clone_inlined_at_id,
                                   Instruction* insert_before = nullptr);

 private:
  IRContext* context() { return context_; }

  // Analyzes OpenCL.DebugInfo.100 instructions in the given |module| and
  // populates data structures in this class.
  void AnalyzeDebugInsts(Module& module);

  // Returns the debug instruction whose id is |id|. Returns |nullptr| if one
  // does not exists.
  Instruction* GetDbgInst(uint32_t id);

  // Registers the debug instruction |inst| into |id_to_dbg_inst_| using id of
  // |inst| as a key.
  void RegisterDbgInst(Instruction* inst);

  // Register the DebugFunction instruction |inst|. The function referenced
  // in |inst| must not already be registered.
  void RegisterDbgFunction(Instruction* inst);

  IRContext* context_;

  // Mapping from ids of OpenCL.DebugInfo.100 extension instructions
  // to their Instruction instances.
  std::unordered_map<uint32_t, Instruction*> id_to_dbg_inst_;

  // Mapping from function's ids to DebugFunction instructions whose
  // operand is the function.
  std::unordered_map<uint32_t, Instruction*> fn_id_to_dbg_fn_;

  // DebugInfoNone instruction. We need only a single DebugInfoNone.
  // To reuse the existing one, we keep it using this member variable.
  Instruction* debug_info_none_inst_;
};

}  // namespace analysis
}  // namespace opt
}  // namespace spvtools

#endif  // SOURCE_OPT_DEBUG_INFO_MANAGER_H_
