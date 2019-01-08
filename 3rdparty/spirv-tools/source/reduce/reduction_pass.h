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

#ifndef SOURCE_REDUCE_REDUCTION_PASS_H_
#define SOURCE_REDUCE_REDUCTION_PASS_H_

#include "spirv-tools/libspirv.hpp"

#include "reduction_opportunity.h"
#include "source/opt/ir_context.h"

namespace spvtools {
namespace reduce {

// Abstract class representing a reduction pass, which can be repeatedly
// invoked to find and apply particular reduction opportunities to a SPIR-V
// binary.  In the spirit of delta debugging, a pass initially tries to apply
// large chunks of reduction opportunities, iterating through available
// opportunities at a given granularity.  When an iteration over available
// opportunities completes, the granularity is reduced and iteration starts
// again, until the minimum granularity is reached.
class ReductionPass {
 public:
  // Constructs a reduction pass with a given target environment, |target_env|.
  // Initially the pass is uninitialized.
  explicit ReductionPass(const spv_target_env target_env)
      : target_env_(target_env), is_initialized_(false) {}

  virtual ~ReductionPass() = default;

  // Applies the reduction pass to the given binary.
  std::vector<uint32_t> TryApplyReduction(const std::vector<uint32_t>& binary);

  // Sets a consumer to which relevant messages will be directed.
  void SetMessageConsumer(MessageConsumer consumer);

  // Returns true if the granularity with which reduction opportunities are
  // applied has reached a minimum.
  bool ReachedMinimumGranularity() const;

  // Returns the name of the reduction pass (useful for monitoring reduction
  // progress).
  virtual std::string GetName() const = 0;

 protected:
  // Finds and returns the reduction opportunities relevant to this pass that
  // could be applied to the given SPIR-V module.
  virtual std::vector<std::unique_ptr<ReductionOpportunity>>
  GetAvailableOpportunities(opt::IRContext* context) const = 0;

 private:
  const spv_target_env target_env_;
  MessageConsumer consumer_;
  bool is_initialized_;
  uint32_t index_;
  uint32_t granularity_;
};

}  // namespace reduce
}  // namespace spvtools

#endif  // SOURCE_REDUCE_REDUCTION_PASS_H_
