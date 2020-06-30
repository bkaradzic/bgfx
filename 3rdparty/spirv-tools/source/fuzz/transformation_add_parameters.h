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

#ifndef SOURCE_FUZZ_TRANSFORMATION_ADD_PARAMETERS_H_
#define SOURCE_FUZZ_TRANSFORMATION_ADD_PARAMETERS_H_

#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/fuzz/transformation.h"
#include "source/fuzz/transformation_context.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace fuzz {

class TransformationAddParameters : public Transformation {
 public:
  explicit TransformationAddParameters(
      const protobufs::TransformationAddParameters& message);

  TransformationAddParameters(uint32_t function_id, uint32_t new_type_id,
                              const std::vector<uint32_t>& new_parameter_type,
                              const std::vector<uint32_t>& new_parameter_id,
                              const std::vector<uint32_t>& constant_id);

  // - |function_id| must be a valid result id of some non-entry-point function
  //   in the module.
  // - |new_type_id| must be a result id of OpTypeFunction instruction.
  // - New type of the function must have the same return type. New function
  //   parameters must be appended to the old ones.
  // - |new_parameter_type| contains result ids of some OpType* instructions in
  //   the module. It may not contain result ids of OpTypeVoid.
  // - |new_parameter_id| contains fresh ids.
  // - |constant_id| contains result ids used to initialize new parameters. Type
  //   ids of these instructions must be the same as |new_parameter_type| (i.e.
  //   |new_parameter_type[i] == GetDef(constant_id[i])->type_id()|).
  // - |new_parameter_id|, |new_parameter_type| and |constant_id| should all
  //   have the same size and may not be empty.
  bool IsApplicable(
      opt::IRContext* ir_context,
      const TransformationContext& transformation_context) const override;

  // - Creates new OpFunctionParameter instructions for the function with
  //   |function_id|.
  // - Changes type of the function to |new_type_id|.
  // - Adds ids from |constant_id| to every OpFunctionCall instruction that
  //   calls the function.
  void Apply(opt::IRContext* ir_context,
             TransformationContext* transformation_context) const override;

  protobufs::Transformation ToMessage() const override;

 private:
  protobufs::TransformationAddParameters message_;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_TRANSFORMATION_ADD_PARAMETERS_H_
