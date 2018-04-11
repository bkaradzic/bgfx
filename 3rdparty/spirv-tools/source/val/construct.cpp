// Copyright (c) 2015-2016 The Khronos Group Inc.
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

#include "val/construct.h"

#include <cassert>
#include <cstddef>

namespace libspirv {

Construct::Construct(ConstructType construct_type, BasicBlock* entry,
                     BasicBlock* exit, std::vector<Construct*> constructs)
    : type_(construct_type),
      corresponding_constructs_(constructs),
      entry_block_(entry),
      exit_block_(exit) {}

ConstructType Construct::type() const { return type_; }

const std::vector<Construct*>& Construct::corresponding_constructs() const {
  return corresponding_constructs_;
}
std::vector<Construct*>& Construct::corresponding_constructs() {
  return corresponding_constructs_;
}

bool ValidateConstructSize(ConstructType type, size_t size) {
  switch (type) {
    case ConstructType::kSelection:
      return size == 0;
    case ConstructType::kContinue:
      return size == 1;
    case ConstructType::kLoop:
      return size == 1;
    case ConstructType::kCase:
      return size >= 1;
    default:
      assert(1 == 0 && "Type not defined");
  }
  return false;
}

void Construct::set_corresponding_constructs(
    std::vector<Construct*> constructs) {
  assert(ValidateConstructSize(type_, constructs.size()));
  corresponding_constructs_ = constructs;
}

const BasicBlock* Construct::entry_block() const { return entry_block_; }
BasicBlock* Construct::entry_block() { return entry_block_; }

const BasicBlock* Construct::exit_block() const { return exit_block_; }
BasicBlock* Construct::exit_block() { return exit_block_; }

void Construct::set_exit(BasicBlock* block) { exit_block_ = block; }
}  // namespace libspirv
