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

#include "source/fuzz/fact_manager/dead_block_facts.h"

namespace spvtools {
namespace fuzz {
namespace fact_manager {

void DeadBlockFacts::AddFact(const protobufs::FactBlockIsDead& fact) {
  dead_block_ids_.insert(fact.block_id());
}

bool DeadBlockFacts::BlockIsDead(uint32_t block_id) const {
  return dead_block_ids_.count(block_id) != 0;
}

}  // namespace fact_manager
}  // namespace fuzz
}  // namespace spvtools
