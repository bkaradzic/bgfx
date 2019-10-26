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

#include <set>

#include "gtest/gtest.h"
#include "source/fuzz/equivalence_relation.h"

namespace spvtools {
namespace fuzz {
namespace {

struct UInt32Equals {
  bool operator()(const uint32_t* first, const uint32_t* second) const {
    return *first == *second;
  }
};

struct UInt32Hash {
  size_t operator()(const uint32_t* element) const {
    return static_cast<size_t>(*element);
  }
};

std::set<uint32_t> ToUIntSet(
    EquivalenceRelation<uint32_t, UInt32Hash, UInt32Equals>::ValueSet
        pointers) {
  std::set<uint32_t> result;
  for (auto pointer : pointers) {
    result.insert(*pointer);
  }
  return result;
}

TEST(EquivalenceRelationTest, BasicTest) {
  EquivalenceRelation<uint32_t, UInt32Hash, UInt32Equals> relation;
  ASSERT_TRUE(relation.GetAllKnownValues().empty());

  for (uint32_t element = 2; element < 80; element += 2) {
    relation.MakeEquivalent(0, element);
    relation.MakeEquivalent(element - 1, element + 1);
  }

  for (uint32_t element = 82; element < 100; element += 2) {
    relation.MakeEquivalent(80, element);
    relation.MakeEquivalent(element - 1, element + 1);
  }

  relation.MakeEquivalent(78, 80);

  std::set<uint32_t> class1;
  for (uint32_t element = 0; element < 98; element += 2) {
    ASSERT_TRUE(relation.IsEquivalent(0, element));
    ASSERT_TRUE(relation.IsEquivalent(element, element + 2));
    class1.insert(element);
  }
  class1.insert(98);
  ASSERT_TRUE(class1 == ToUIntSet(relation.GetEquivalenceClass(0)));
  ASSERT_TRUE(class1 == ToUIntSet(relation.GetEquivalenceClass(4)));
  ASSERT_TRUE(class1 == ToUIntSet(relation.GetEquivalenceClass(40)));

  std::set<uint32_t> class2;
  for (uint32_t element = 1; element < 79; element += 2) {
    ASSERT_TRUE(relation.IsEquivalent(1, element));
    ASSERT_TRUE(relation.IsEquivalent(element, element + 2));
    class2.insert(element);
  }
  class2.insert(79);
  ASSERT_TRUE(class2 == ToUIntSet(relation.GetEquivalenceClass(1)));
  ASSERT_TRUE(class2 == ToUIntSet(relation.GetEquivalenceClass(11)));
  ASSERT_TRUE(class2 == ToUIntSet(relation.GetEquivalenceClass(31)));

  std::set<uint32_t> class3;
  for (uint32_t element = 81; element < 99; element += 2) {
    ASSERT_TRUE(relation.IsEquivalent(81, element));
    ASSERT_TRUE(relation.IsEquivalent(element, element + 2));
    class3.insert(element);
  }
  class3.insert(99);
  ASSERT_TRUE(class3 == ToUIntSet(relation.GetEquivalenceClass(81)));
  ASSERT_TRUE(class3 == ToUIntSet(relation.GetEquivalenceClass(91)));
  ASSERT_TRUE(class3 == ToUIntSet(relation.GetEquivalenceClass(99)));
}

}  // namespace
}  // namespace fuzz
}  // namespace spvtools
