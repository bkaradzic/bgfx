// Copyright 2026 The Dawn & Tint Authors
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Test the type checks of dawn::Span

#include <array>

#include "src/utils/span.h"
#include "src/utils/typed_integer.h"

namespace dawn {

static constexpr std::array<int, 5> kSpanData = {1, 2, 3, 4, 5};

using Index = TypedInteger<struct IndexT, uint32_t>;
using IndexSizeT = TypedInteger<struct IndexT, size_t>;

struct FakeRange {
    size_t size() const { return kSpanData.size(); }
    const int* data() const { return kSpanData.data(); }
};

struct FakeTypedRange {
    Index size() const {
        return Index{uint32_t{kSpanData.size()}};
    }
    const int* data() const { return kSpanData.data(); }
};

void TestConstPointerToNonConstSpan() {
    DAWN_UNSAFE_BUFFERS(Span<const int>(kSpanData.data(), kSpanData.size())); // Control case.
    DAWN_UNSAFE_BUFFERS(Span<int>(kSpanData.data(), kSpanData.size())); // expected-error {{no matching constructor for initialization}}

    DAWN_UNSAFE_BUFFERS(Span<const int>(kSpanData.begin(), kSpanData.end())); // Control case.
    DAWN_UNSAFE_BUFFERS(Span<int>(kSpanData.begin(), kSpanData.end())); // expected-error {{no matching constructor for initialization of}}

    Span<const int>{FakeRange()}; // Control case.
    Span<int>{FakeRange()}; // expected-error {{no matching constructor for initialization of}}
}

void TestConstructorsThatRequireDawnUnsafeBuffers() {
    DAWN_UNSAFE_BUFFERS(Span<const int>(kSpanData.data(), kSpanData.size())); // Control case.
    // TODO(https://crbug.com/523128530): DAWN_UNSAFE_BUFFERS doesn't seem required in no-compile tests for some reason. Fix that and add an expected error here.
    Span<const int>(kSpanData.data(), kSpanData.size());

    DAWN_UNSAFE_BUFFERS(Span<const int>(kSpanData.begin(), kSpanData.end())); // Control case.
    // TODO(https://crbug.com/523128530): DAWN_UNSAFE_BUFFERS doesn't seem required in no-compile tests for some reason. Fix that and add an expected error here.
    Span<const int>(kSpanData.begin(), kSpanData.end());
}

void TestConstructorWithRangeRequirements() {
    Span<const int>{FakeRange()}; // Control case.

    struct FakeRangeBadSize {
        uint8_t size() const {
            return uint8_t{kSpanData.size()};
        }
        const int* data() const { return kSpanData.data(); }
    };
    Span<const int>{FakeRangeBadSize()}; // expected-error {{no matching constructor for initialization of}}

    struct FakeRangeTypedSize {
         IndexSizeT size() const {
            return IndexSizeT{kSpanData.size()};
        }
        const int* data() const { return kSpanData.data(); }
    };
    Span<const int>{FakeRangeTypedSize()}; // expected-error {{no matching constructor for initialization of}}

    struct FakeRangeBadData {
        size_t size() const {
            return kSpanData.size();
        }
        const int& data() const { return *kSpanData.data(); }
    };
    Span<const int>{FakeRangeBadData()}; // expected-error {{no matching constructor for initialization of}}
}

void TestTypedIntegerArguments() {
    ityp::span<Index, const int> sp{FakeTypedRange()};

    DAWN_UNSAFE_BUFFERS(ityp::span<Index, const int>(kSpanData.data(), kSpanData.size())); // expected-error {{no matching constructor for initialization}}
    (void) sp.at(2); // expected-error {{no viable conversion from}}
    (void) sp[2]; // expected-error {{no viable overloaded operator[]}}
    (void) sp.first(2); // expected-error {{no viable conversion from}}
    (void) sp.last(2); // expected-error {{no viable conversion from}}
    (void) sp.subspan(2); // expected-error {{no matching member function for call to}}
    (void) sp.subspan(2, 2); // expected-error {{no matching member function for call to}}
}

}  // namespace dawn
