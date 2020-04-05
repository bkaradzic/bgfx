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

#ifndef SOURCE_FUZZ_TRANSFORMATION_CONTEXT_H_
#define SOURCE_FUZZ_TRANSFORMATION_CONTEXT_H_

#include "source/fuzz/fact_manager.h"
#include "spirv-tools/libspirv.hpp"

namespace spvtools {
namespace fuzz {

// Encapsulates all information that is required to inform how to apply a
// transformation to a module.
class TransformationContext {
 public:
  // Constructs a transformation context with a given fact manager and validator
  // options.
  TransformationContext(FactManager* fact_manager,
                        spv_validator_options validator_options);

  ~TransformationContext();

  FactManager* GetFactManager() { return fact_manager_; }

  const FactManager* GetFactManager() const { return fact_manager_; }

  spv_validator_options GetValidatorOptions() const {
    return validator_options_;
  }

 private:
  // Manages facts that inform whether transformations can be applied, and that
  // are produced by applying transformations.
  FactManager* fact_manager_;

  // Options to control validation when deciding whether transformations can be
  // applied.
  spv_validator_options validator_options_;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_TRANSFORMATION_CONTEXT_H_
