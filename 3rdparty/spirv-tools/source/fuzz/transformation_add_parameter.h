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

#ifndef SOURCE_FUZZ_TRANSFORMATION_ADD_PARAMETER_H_
#define SOURCE_FUZZ_TRANSFORMATION_ADD_PARAMETER_H_

#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/fuzz/transformation.h"
#include "source/fuzz/transformation_context.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {

class TransformationAddParameter : public Transformation {
 public:
  explicit TransformationAddParameter(
      const protobufs::TransformationAddParameter& message);

  TransformationAddParameter(uint32_t function_id, uint32_t parameter_fresh_id,
                             uint32_t initializer_id,
                             uint32_t function_type_fresh_id);

  // - |function_id| must be a valid result id of some non-entry-point function
  //   in the module.
  // - |initializer_id| must be a valid result id of some instruction in the
  //   module. Instruction's type must be supported by this transformation
  //   as specified by IsParameterTypeSupported function.
  // - |parameter_fresh_id| and |function_type_fresh_id| are fresh ids and are
  //   not equal.
  bool IsApplicable(
      opt::IRContext* ir_context,
      const TransformationContext& transformation_context) const override;

  // - Creates a new OpFunctionParameter instruction with result id
  //   |parameter_fresh_id| for the function with |function_id|.
  // - Adjusts function's type to include a new parameter.
  // - Adds |initializer_id| as a new operand to every OpFunctionCall
  //   instruction that calls the function.
  void Apply(opt::IRContext* ir_context,
             TransformationContext* transformation_context) const override;

  protobufs::Transformation ToMessage() const override;

  // Returns true if the type of the parameter is supported by this
  // transformation.
  static bool IsParameterTypeSupported(const opt::analysis::Type& type);

 private:
  protobufs::TransformationAddParameter message_;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_TRANSFORMATION_ADD_PARAMETER_H_
