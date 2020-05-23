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

// When an instruction of a callee function is inlined to its caller function,
// we need the line and the scope information of the function call instruction
// to generate DebugInlinedAt. This class keeps the data. For multiple inlining
// of a single instruction, we have to create multiple DebugInlinedAt
// instructions as a chain. This class keeps the information of the generated
// DebugInlinedAt chains to reduce the number of chains.
class DebugInlinedAtContext {
 public:
  explicit DebugInlinedAtContext(Instruction* call_inst)
      : call_inst_line_(call_inst->dbg_line_inst()),
        call_inst_scope_(call_inst->GetDebugScope()) {}

  const Instruction* GetLineOfCallInstruction() { return call_inst_line_; }
  const DebugScope& GetScopeOfCallInstruction() { return call_inst_scope_; }
  // Puts the DebugInlinedAt chain that is generated for the callee instruction
  // whose DebugInlinedAt of DebugScope is |callee_instr_inlined_at| into
  // |callee_inlined_at2chain_|.
  void SetDebugInlinedAtChain(uint32_t callee_instr_inlined_at,
                              uint32_t chain_head_id) {
    callee_inlined_at2chain_[callee_instr_inlined_at] = chain_head_id;
  }
  // Gets the DebugInlinedAt chain from |callee_inlined_at2chain_|.
  uint32_t GetDebugInlinedAtChain(uint32_t callee_instr_inlined_at) {
    auto chain_itr = callee_inlined_at2chain_.find(callee_instr_inlined_at);
    if (chain_itr != callee_inlined_at2chain_.end()) return chain_itr->second;
    return kNoInlinedAt;
  }

 private:
  // The line information of the function call instruction that will be
  // replaced by the callee function.
  const Instruction* call_inst_line_;

  // The scope information of the function call instruction that will be
  // replaced by the callee function.
  const DebugScope call_inst_scope_;

  // Map from DebugInlinedAt ids of callee to head ids of new generated
  // DebugInlinedAt chain.
  std::unordered_map<uint32_t, uint32_t> callee_inlined_at2chain_;
};

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

  // Returns the debug scope corresponding to an inlining instruction in the
  // scope |callee_instr_scope| into |inlined_at_ctx|. Generates all new
  // debug instructions needed to represent the scope.
  DebugScope BuildDebugScope(const DebugScope& callee_instr_scope,
                             DebugInlinedAtContext* inlined_at_ctx);

  // Returns DebugInlinedAt corresponding to inlining an instruction, which
  // was inlined at |callee_inlined_at|, into |inlined_at_ctx|. Generates all
  // new debug instructions needed to represent the DebugInlinedAt.
  uint32_t BuildDebugInlinedAtChain(uint32_t callee_inlined_at,
                                    DebugInlinedAtContext* inlined_at_ctx);

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
