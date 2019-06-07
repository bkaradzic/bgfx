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

#include "source/fuzz/fuzzer_context.h"

namespace spvtools {
namespace fuzz {

namespace {
// Default probabilities for applying various transformations.
// All values are percentages.
// Keep them in alphabetical order.

const uint32_t kDefaultChanceOfAddingDeadBreak = 20;
const uint32_t kDefaultChanceOfMovingBlockDown = 25;
const uint32_t kDefaultChanceOfSplittingBlock = 20;

}  // namespace

FuzzerContext::FuzzerContext(RandomGenerator* random_generator,
                             uint32_t min_fresh_id)
    : random_generator_(random_generator),
      next_fresh_id_(min_fresh_id),
      chance_of_adding_dead_break_(kDefaultChanceOfAddingDeadBreak),
      chance_of_moving_block_down_(kDefaultChanceOfMovingBlockDown),
      chance_of_splitting_block_(kDefaultChanceOfSplittingBlock) {}

FuzzerContext::~FuzzerContext() = default;

uint32_t FuzzerContext::GetFreshId() { return next_fresh_id_++; }

RandomGenerator* FuzzerContext::GetRandomGenerator() {
  return random_generator_;
}

}  // namespace fuzz
}  // namespace spvtools
