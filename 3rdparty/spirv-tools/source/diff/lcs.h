// Copyright (c) 2022 Google LLC.
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

#ifndef SOURCE_DIFF_LCS_H_
#define SOURCE_DIFF_LCS_H_

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <vector>

namespace spvtools {
namespace diff {

// The result of a diff.
using DiffMatch = std::vector<bool>;

// Helper class to find the longest common subsequence between two function
// bodies.
template <typename Sequence>
class LongestCommonSubsequence {
 public:
  LongestCommonSubsequence(const Sequence& src, const Sequence& dst)
      : src_(src),
        dst_(dst),
        table_(src.size(), std::vector<DiffMatchEntry>(dst.size())) {}

  // Given two sequences, it creates a matching between them.  The elements are
  // simply marked as matched in src and dst, with any unmatched element in src
  // implying a removal and any unmatched element in dst implying an addition.
  //
  // Returns the length of the longest common subsequence.
  template <typename T>
  size_t Get(std::function<bool(T src_elem, T dst_elem)> match,
             DiffMatch* src_match_result, DiffMatch* dst_match_result);

 private:
  template <typename T>
  size_t CalculateLCS(size_t src_start, size_t dst_start,
                      std::function<bool(T src_elem, T dst_elem)> match);
  void RetrieveMatch(DiffMatch* src_match_result, DiffMatch* dst_match_result);
  bool IsInBound(size_t src_index, size_t dst_index) {
    return src_index < src_.size() && dst_index < dst_.size();
  }
  bool IsCalculated(size_t src_index, size_t dst_index) {
    assert(IsInBound(src_index, dst_index));
    return table_[src_index][dst_index].valid;
  }
  size_t GetMemoizedLength(size_t src_index, size_t dst_index) {
    if (!IsInBound(src_index, dst_index)) {
      return 0;
    }
    assert(IsCalculated(src_index, dst_index));
    return table_[src_index][dst_index].best_match_length;
  }
  bool IsMatched(size_t src_index, size_t dst_index) {
    assert(IsCalculated(src_index, dst_index));
    return table_[src_index][dst_index].matched;
  }

  const Sequence& src_;
  const Sequence& dst_;

  struct DiffMatchEntry {
    size_t best_match_length = 0;
    // Whether src[i] and dst[j] matched.  This is an optimization to avoid
    // calling the `match` function again when walking the LCS table.
    bool matched = false;
    // Use for the recursive algorithm to know if the contents of this entry are
    // valid.
    bool valid = false;
  };

  std::vector<std::vector<DiffMatchEntry>> table_;
};

template <typename Sequence>
template <typename T>
size_t LongestCommonSubsequence<Sequence>::Get(
    std::function<bool(T src_elem, T dst_elem)> match,
    DiffMatch* src_match_result, DiffMatch* dst_match_result) {
  size_t best_match_length = CalculateLCS(0, 0, match);
  RetrieveMatch(src_match_result, dst_match_result);
  return best_match_length;
}

template <typename Sequence>
template <typename T>
size_t LongestCommonSubsequence<Sequence>::CalculateLCS(
    size_t src_start, size_t dst_start,
    std::function<bool(T src_elem, T dst_elem)> match) {
  // The LCS algorithm is simple.  Given sequences s and d, with a:b depicting a
  // range in python syntax:
  //
  //     lcs(s[i:], d[j:]) =
  //         lcs(s[i+1:], d[j+1:]) + 1                        if s[i] == d[j]
  //         max(lcs(s[i+1:], d[j:]), lcs(s[i:], d[j+1:]))               o.w.
  //
  // Once the LCS table is filled according to the above, it can be walked and
  // the best match retrieved.
  //
  // This is a recursive function with memoization, which avoids filling table
  // entries where unnecessary.  This makes the best case O(N) instead of
  // O(N^2).

  // To avoid unnecessary recursion on long sequences, process a whole strip of
  // matching elements in one go.
  size_t src_cur = src_start;
  size_t dst_cur = dst_start;
  while (IsInBound(src_cur, dst_cur) && !IsCalculated(src_cur, dst_cur) &&
         match(src_[src_cur], dst_[dst_cur])) {
    ++src_cur;
    ++dst_cur;
  }

  // We've reached a pair of elements that don't match.  Recursively determine
  // which one should be left unmatched.
  size_t best_match_length = 0;
  if (IsInBound(src_cur, dst_cur)) {
    if (IsCalculated(src_cur, dst_cur)) {
      best_match_length = GetMemoizedLength(src_cur, dst_cur);
    } else {
      best_match_length = std::max(CalculateLCS(src_cur + 1, dst_cur, match),
                                   CalculateLCS(src_cur, dst_cur + 1, match));

      // Fill the table with this information
      DiffMatchEntry& entry = table_[src_cur][dst_cur];
      assert(!entry.valid);
      entry.best_match_length = best_match_length;
      entry.valid = true;
    }
  }

  // Go over the matched strip and update the table as well.
  assert(src_cur - src_start == dst_cur - dst_start);
  size_t contiguous_match_len = src_cur - src_start;

  for (size_t i = 0; i < contiguous_match_len; ++i) {
    --src_cur;
    --dst_cur;
    assert(IsInBound(src_cur, dst_cur));

    DiffMatchEntry& entry = table_[src_cur][dst_cur];
    assert(!entry.valid);
    entry.best_match_length = ++best_match_length;
    entry.matched = true;
    entry.valid = true;
  }

  return best_match_length;
}

template <typename Sequence>
void LongestCommonSubsequence<Sequence>::RetrieveMatch(
    DiffMatch* src_match_result, DiffMatch* dst_match_result) {
  src_match_result->clear();
  dst_match_result->clear();

  src_match_result->resize(src_.size(), false);
  dst_match_result->resize(dst_.size(), false);

  size_t src_cur = 0;
  size_t dst_cur = 0;
  while (IsInBound(src_cur, dst_cur)) {
    if (IsMatched(src_cur, dst_cur)) {
      (*src_match_result)[src_cur++] = true;
      (*dst_match_result)[dst_cur++] = true;
      continue;
    }

    if (GetMemoizedLength(src_cur + 1, dst_cur) >=
        GetMemoizedLength(src_cur, dst_cur + 1)) {
      ++src_cur;
    } else {
      ++dst_cur;
    }
  }
}

}  // namespace diff
}  // namespace spvtools

#endif  // SOURCE_DIFF_LCS_H_
