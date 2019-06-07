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

#ifndef SOURCE_FUZZ_FUZZER_CONTEXT_H_
#define SOURCE_FUZZ_FUZZER_CONTEXT_H_

#include "source/fuzz/random_generator.h"
#include "source/opt/function.h"

namespace spvtools {
namespace fuzz {

// Encapsulates all parameters that control the fuzzing process, such as the
// source of randomness and the probabilities with which transformations are
// applied.
class FuzzerContext {
 public:
  // Constructs a fuzzer context with a given random generator and the minimum
  // value that can be used for fresh ids.
  FuzzerContext(RandomGenerator* random_generator, uint32_t min_fresh_id);

  ~FuzzerContext();

  // Provides the random generator used to control fuzzing.
  RandomGenerator* GetRandomGenerator();

  // Yields an id that is guaranteed not to be used in the module being fuzzed,
  // or to have been issued before.
  uint32_t GetFreshId();

  // Probabilities associated with applying various transformations.
  // Keep them in alphabetical order.
  uint32_t GetChanceOfAddingDeadBreak() { return chance_of_adding_dead_break_; }
  uint32_t GetChanceOfMovingBlockDown() { return chance_of_moving_block_down_; }
  uint32_t GetChanceOfSplittingBlock() { return chance_of_splitting_block_; }

 private:
  // The source of randomness.
  RandomGenerator* random_generator_;
  // The next fresh id to be issued.
  uint32_t next_fresh_id_;

  // Probabilities associated with applying various transformations.
  // Keep them in alphabetical order.
  uint32_t chance_of_adding_dead_break_;
  uint32_t chance_of_moving_block_down_;
  uint32_t chance_of_splitting_block_;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_FUZZER_CONTEXT_H_
