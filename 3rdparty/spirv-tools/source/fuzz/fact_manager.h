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

#ifndef SOURCE_FUZZ_FACT_MANAGER_H_
#define SOURCE_FUZZ_FACT_MANAGER_H_

#include <utility>

#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/opt/constants.h"

namespace spvtools {
namespace fuzz {

// Keeps track of facts about the module being transformed on which the fuzzing
// process can depend. Some initial facts can be provided, for example about
// guarantees on the values of inputs to SPIR-V entry points. Transformations
// may then rely on these facts, can add further facts that they establish.
// Facts are intended to be simple properties that either cannot be deduced from
// the module (such as properties that are guaranteed to hold for entry point
// inputs), or that are established by transformations, likely to be useful for
// future transformations, and not completely trivial to deduce straight from
// the module.
class FactManager {
 public:
  FactManager();

  ~FactManager();

  // Adds all the facts from |facts|, checking them for validity with respect to
  // |context|. Returns true if and only if all facts are valid.
  bool AddFacts(const protobufs::FactSequence& facts, opt::IRContext* context);

  // Adds |fact| to the fact manager, checking it for validity with respect to
  // |context|. Returns true if and only if the fact is valid.
  bool AddFact(const protobufs::Fact& fact, opt::IRContext* context);
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // #define SOURCE_FUZZ_FACT_MANAGER_H_
