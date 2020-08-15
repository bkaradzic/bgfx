// Copyright (c) 2020 Vasyl Teliman
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

#ifndef SOURCE_FUZZ_TRANSFORMATION_MOVE_INSTRUCTION_DOWN_H_
#define SOURCE_FUZZ_TRANSFORMATION_MOVE_INSTRUCTION_DOWN_H_

#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/fuzz/transformation.h"
#include "source/fuzz/transformation_context.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {

class TransformationMoveInstructionDown : public Transformation {
 public:
  explicit TransformationMoveInstructionDown(
      const protobufs::TransformationMoveInstructionDown& message);

  explicit TransformationMoveInstructionDown(
      const protobufs::InstructionDescriptor& instruction);

  // - |instruction| should be a descriptor of a valid instruction in the module
  // - |instruction|'s opcode should be supported by this transformation
  // - neither |instruction| nor its successor may be the last instruction in
  //   the block
  // - |instruction|'s successor may not be dependent on the |instruction|
  // - it should be possible to insert |instruction|'s opcode after its
  //   successor
  bool IsApplicable(
      opt::IRContext* ir_context,
      const TransformationContext& transformation_context) const override;

  // Swaps |instruction| with its successor.
  void Apply(opt::IRContext* ir_context,
             TransformationContext* transformation_context) const override;

  protobufs::Transformation ToMessage() const override;

 private:
  // Returns true if the |opcode| is supported by this transformation (i.e.
  // we can move an instruction with this opcode).
  static bool IsOpcodeSupported(SpvOp opcode);

  protobufs::TransformationMoveInstructionDown message_;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_TRANSFORMATION_MOVE_INSTRUCTION_DOWN_H_
