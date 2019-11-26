// Copyright (c) 2019 Google LLC
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

#ifndef SOURCE_FUZZ_FUZZER_PASS_H_
#define SOURCE_FUZZ_FUZZER_PASS_H_

#include <functional>
#include <vector>

#include "source/fuzz/fact_manager.h"
#include "source/fuzz/fuzzer_context.h"
#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {

// Interface for applying a pass of transformations to a module.
class FuzzerPass {
 public:
  FuzzerPass(opt::IRContext* ir_context, FactManager* fact_manager,
             FuzzerContext* fuzzer_context,
             protobufs::TransformationSequence* transformations);

  virtual ~FuzzerPass();

  // Applies the pass to the module |ir_context_|, assuming and updating
  // facts from |fact_manager_|, and using |fuzzer_context_| to guide the
  // process.  Appends to |transformations_| all transformations that were
  // applied during the pass.
  virtual void Apply() = 0;

 protected:
  opt::IRContext* GetIRContext() const { return ir_context_; }

  FactManager* GetFactManager() const { return fact_manager_; }

  FuzzerContext* GetFuzzerContext() const { return fuzzer_context_; }

  protobufs::TransformationSequence* GetTransformations() const {
    return transformations_;
  }

  // Returns all instructions that are *available* at |inst_it|, which is
  // required to be inside block |block| of function |function| - that is, all
  // instructions at global scope and all instructions that strictly dominate
  // |inst_it|.
  //
  // Filters said instructions to return only those that satisfy the
  // |instruction_is_relevant| predicate.  This, for instance, could ignore all
  // instructions that have a particular decoration.
  std::vector<opt::Instruction*> FindAvailableInstructions(
      const opt::Function& function, opt::BasicBlock* block,
      opt::BasicBlock::iterator inst_it,
      std::function<bool(opt::IRContext*, opt::Instruction*)>
          instruction_is_relevant);

  // A helper method that iterates through each instruction in each block, at
  // all times tracking an instruction descriptor that allows the latest
  // instruction to be located even if it has no result id.
  //
  // The code to manipulate the instruction descriptor is a bit fiddly, and the
  // point of this method is to avoiding having to duplicate it in multiple
  // transformation passes.
  //
  // The function |maybe_apply_transformation| is invoked for each instruction
  // |inst_it| in block |block| of function |function| that is encountered.  The
  // |instruction_descriptor| parameter to the function object allows |inst_it|
  // to be identified.
  //
  // The job of |maybe_apply_transformation| is to randomly decide whether to
  // try to apply some transformation, and then - if selected - to attempt to
  // apply it.
  void MaybeAddTransformationBeforeEachInstruction(
      std::function<
          void(const opt::Function& function, opt::BasicBlock* block,
               opt::BasicBlock::iterator inst_it,
               const protobufs::InstructionDescriptor& instruction_descriptor)>
          maybe_apply_transformation);

 private:
  opt::IRContext* ir_context_;
  FactManager* fact_manager_;
  FuzzerContext* fuzzer_context_;
  protobufs::TransformationSequence* transformations_;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_FUZZER_PASS_H_
