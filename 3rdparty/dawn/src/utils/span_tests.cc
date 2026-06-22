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

#include <gtest/gtest.h>

#include <array>

#include "partition_alloc/pointers/raw_ptr.h"
#include "src/utils/span.h"
#include "src/utils/typed_integer.h"

namespace dawn {
namespace {

static constexpr std::array<int, 5> kSpanData = {1, 2, 3, 4, 5};

using Index = TypedInteger<struct IndexT, uint32_t>;
using Index8 = TypedInteger<struct IndexT, uint8_t>;
using Index64 = TypedInteger<struct IndexT, uint64_t>;

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

struct FakeTyped64Range {
    Index64 size() const {
        return Index64{uint64_t{kSpanData.size()}};
    }
    const int* data() const { return kSpanData.data(); }
};

TEST(SpanTest, Constructor_Default) {
    {
        Span<int> sp;
        EXPECT_EQ(sp.size(), 0u);
        EXPECT_EQ(sp.data(), nullptr);
    }
    {
        ityp::span<Index, int> sp;
        EXPECT_EQ(sp.size(), Index{0u});
        EXPECT_EQ(sp.data(), nullptr);
    }
}

TEST(SpanTest, Constructor_PointerAndSize) {
    int data[] = {1, 2, 3};
    int constData[] = {1, 2, 3};
    raw_ptr<int> rptr = data;

    // T* + size for Span<T>
    {
        // SAFETY: Test for the unsafe constructor.
        Span<int> DAWN_UNSAFE_BUFFERS(sp{&data[0], 3});
        EXPECT_EQ(sp.size(), 3u);
        EXPECT_EQ(sp.data(), data);
    }
    // const T* + size for Span<const T>
    {
        // SAFETY: Test for the unsafe constructor.
        Span<const int> DAWN_UNSAFE_BUFFERS(sp{&constData[0], 3});
        EXPECT_EQ(sp.size(), 3u);
        EXPECT_EQ(sp.data(), constData);
    }
    // T* + size for Span<const T>
    {
        // SAFETY: Test for the unsafe constructor.
        Span<const int> DAWN_UNSAFE_BUFFERS(sp{&data[0], 3});
        EXPECT_EQ(sp.size(), 3u);
        EXPECT_EQ(sp.data(), data);
    }

    // T* + size for ityp::span<T, ...>
    {
        // SAFETY: Test for the unsafe constructor.
        ityp::span<Index, int> DAWN_UNSAFE_BUFFERS(sp{&data[0], Index{3u}});
        EXPECT_EQ(sp.size(), Index{3u});
        EXPECT_EQ(sp.data(), data);
    }
    // const T* + size for ityp::span<const T, ...>
    {
        // SAFETY: Test for the unsafe constructor.
        ityp::span<Index, const int> DAWN_UNSAFE_BUFFERS(sp{&constData[0], Index{3u}});
        EXPECT_EQ(sp.size(), Index{3u});
        EXPECT_EQ(sp.data(), constData);
    }
    // T* + size for ityp::span<const T, ...>
    {
        // SAFETY: Test for the unsafe constructor.
        ityp::span<Index, const int> DAWN_UNSAFE_BUFFERS(sp{&data[0], Index{3u}});
        EXPECT_EQ(sp.size(), Index{3u});
        EXPECT_EQ(sp.data(), data);
    }
}

TEST(SpanDeathTest, Constructor_PointerAndSizeOversizedIndex) {
    // These tests are only relevant on 32-bit builds.
    if constexpr (sizeof(size_t) > sizeof(uint32_t)) {
        GTEST_SKIP();
    }

    constexpr Index64 kHugeSize{0x1'0000'0000LLU};
    // SAFETY: Test for the unsafe constructor.
    DAWN_UNSAFE_BUFFERS(EXPECT_DEATH_IF_SUPPORTED(
        (ityp::span<Index64, const int>(kSpanData.data(), kHugeSize)), ""));
}

TEST(SpanTest, Constructor_TwoIterators) {
    std::array<int, 3> data = {1, 2, 3};
    const std::array<int, 3> constData = {1, 2, 3};

    // 2 x iterator for Span<T>
    {
        // SAFETY: Test for the unsafe constructor.
        Span<int> DAWN_UNSAFE_BUFFERS(sp{data.begin(), data.end()});
        EXPECT_EQ(sp.size(), 3u);
        EXPECT_EQ(sp.data(), data.data());
    }
    // 2 x const_iterator for Span<const T>
    {
        // SAFETY: Test for the unsafe constructor.
        Span<const int> DAWN_UNSAFE_BUFFERS(sp{constData.begin(), constData.end()});
        EXPECT_EQ(sp.size(), 3u);
        EXPECT_EQ(sp.data(), constData.data());
    }
    // 2 x iterator for Span<const T>
    {
        // SAFETY: Test for the unsafe constructor.
        Span<const int> DAWN_UNSAFE_BUFFERS(sp{data.begin(), data.end()});
        EXPECT_EQ(sp.size(), 3u);
        EXPECT_EQ(sp.data(), data.data());
    }

    // 2 x iterator for ityp::span<T, ...>
    {
        // SAFETY: Test for the unsafe constructor.
        ityp::span<Index, int> DAWN_UNSAFE_BUFFERS(sp{data.begin(), data.end()});
        EXPECT_EQ(sp.size(), Index{3u});
        EXPECT_EQ(sp.data(), data.data());
    }
    // 2 x const_iterator for ityp::span<const T, ...>
    {
        // SAFETY: Test for the unsafe constructor.
        ityp::span<Index, const int> DAWN_UNSAFE_BUFFERS(sp{constData.begin(), constData.end()});
        EXPECT_EQ(sp.size(), Index{3u});
        EXPECT_EQ(sp.data(), constData.data());
    }
    // 2 x iterator for ityp::span<const T, ...>
    {
        // SAFETY: Test for the unsafe constructor.
        ityp::span<Index, const int> DAWN_UNSAFE_BUFFERS(sp{data.begin(), data.end()});
        EXPECT_EQ(sp.size(), Index{3u});
        EXPECT_EQ(sp.data(), data.data());
    }
}

TEST(SpanDeathTest, Constructor_TwoIteratorsInverted) {
    std::array<int, 3> data = {1, 2, 3};
    // SAFETY: Test for the unsafe constructor.
    DAWN_UNSAFE_BUFFERS(EXPECT_DEATH_IF_SUPPORTED((Span<int>{data.end(), data.begin()}), ""));
}

TEST(SpanDeathTest, Constructor_TwoIteratorsLargerThanIndexType) {
    std::vector<int> data;
    data.resize(256);  // Larger than indices that can be store in a uint8_t.

    // SAFETY: Test for the unsafe constructor.
    DAWN_UNSAFE_BUFFERS(
        EXPECT_DEATH_IF_SUPPORTED((ityp::span<Index8, int>(data.begin(), data.end())), ""));

    // Fits exactly in uint8_t for indexing.
    data.resize(255);

    // SAFETY: Test for the unsafe constructor.
    DAWN_UNSAFE_BUFFERS((ityp::span<Index8, int>(data.begin(), data.end())));
}

std::span<std::byte> GetByteSpan() {
    return {};
}

TEST(SpanTest, ConstructorFromCompatibleRange) {
    {
        std::array<int, 3> data = {1, 2, 3};
        Span<int> sp{data};
        EXPECT_EQ(sp.size(), data.size());
        EXPECT_EQ(sp.data(), data.data());
    }
    {
        const std::array<int, 3> data = {1, 2, 3};
        Span<const int> sp{data};
        EXPECT_EQ(sp.size(), data.size());
        EXPECT_EQ(sp.data(), data.data());
    }
    {
        std::vector<int> data{{1, 2, 3}};
        Span<const int> sp{data};
        EXPECT_EQ(sp.size(), data.size());
        EXPECT_EQ(sp.data(), data.data());
    }
    {
        std::string data = "foo";
        Span<char> sp{data};
        EXPECT_EQ(sp.size(), data.size());
        EXPECT_EQ(sp.data(), data.data());
    }
    {
        std::string_view data = "foo";
        Span<const char> sp{data};
        EXPECT_EQ(sp.size(), data.size());
        EXPECT_EQ(sp.data(), data.data());
    }
    {
        FakeRange data;
        Span<const int> sp{data};
        EXPECT_EQ(sp.size(), data.size());
        EXPECT_EQ(sp.data(), data.data());
    }
    {
        // Fails to compile if the constructor from range take a reference and not an rvalue
        // reference.
        Span<std::byte> sp;
        sp = GetByteSpan();
    }

    {
        FakeTypedRange data;
        ityp::span<Index, const int> sp{data};
        EXPECT_EQ(sp.size(), data.size());
        EXPECT_EQ(sp.data(), data.data());
    }
}

TEST(SpanTest, CopyConstructor) {
    std::array<int, 3> data = {1, 2, 3};
    Span<int> sp{data};

    Span<int> sp2{sp};
    ASSERT_EQ(sp.data(), sp2.data());
    ASSERT_EQ(sp.size(), sp2.size());

    // Actually calls the constructor from a range.
    Span<const int> sp3{sp};
    ASSERT_EQ(sp.data(), sp3.data());
    ASSERT_EQ(sp.size(), sp3.size());
}

TEST(SpanTest, CopyAssignment) {
    std::array<int, 3> data = {1, 2, 3};
    Span<int> sp{data};

    Span<int> sp2;
    sp2 = sp;
    ASSERT_EQ(sp.data(), sp2.data());
    ASSERT_EQ(sp.size(), sp2.size());

    // Actually calls the constructor from a range and then assigns.
    Span<const int> sp3;
    sp3 = sp;
    ASSERT_EQ(sp.data(), sp3.data());
    ASSERT_EQ(sp.size(), sp3.size());
}

TEST(SpanTest, MoveConstructor) {
    std::array<int, 3> data = {1, 2, 3};
    Span<int> sp{data};

    Span<int> sp2{std::move(sp)};
    ASSERT_EQ(data.data(), sp2.data());
    ASSERT_EQ(data.size(), sp2.size());

    // Move actually does a copy so sp stays the same.
    ASSERT_EQ(data.data(), sp.data());
    ASSERT_EQ(data.size(), sp.size());
}

TEST(SpanTest, MoveAssignment) {
    std::array<int, 3> data = {1, 2, 3};
    Span<int> sp{data};

    Span<int> sp2;
    sp2 = std::move(sp);
    ASSERT_EQ(data.data(), sp2.data());
    ASSERT_EQ(data.size(), sp2.size());

    // Move actually does a copy so sp stays the same.
    ASSERT_EQ(data.data(), sp.data());
    ASSERT_EQ(data.size(), sp.size());
}

TEST(SpanTest, BeginEnd) {
    {
        Span<const int> sp(FakeRange{});
        ASSERT_EQ(&*sp.begin(), &*kSpanData.begin());
        ASSERT_EQ(&*sp.end(), &*kSpanData.end());
    }
    {
        ityp::span<Index, const int> sp(FakeTypedRange{});
        ASSERT_EQ(&*sp.begin(), &*kSpanData.begin());
        ASSERT_EQ(&*sp.end(), &*kSpanData.end());
    }
}

TEST(SpanTest, BeginEndForIteration) {
    // Uses begin/end
    {
        Span<const int> sp(FakeRange{});

        int expected = 1;
        for (const int& i : sp) {
            EXPECT_EQ(i, expected);
            expected++;
        }
    }

    // Uses cbegin/cend
    {
        const Span<const int> sp(FakeRange{});

        int expected = 1;
        for (const int& i : sp) {
            EXPECT_EQ(i, expected);
            expected++;
        }
    }

    // ityp, uses begin/end
    {
        ityp::span<Index, const int> sp(FakeTypedRange{});

        int expected = 1;
        for (const int& i : sp) {
            EXPECT_EQ(i, expected);
            expected++;
        }
    }

    // ityp, uses cbegin/cend
    {
        const ityp::span<Index, const int> sp(FakeTypedRange{});

        int expected = 1;
        for (const int& i : sp) {
            EXPECT_EQ(i, expected);
            expected++;
        }
    }
}

TEST(SpanTest, FrontBack) {
    {
        Span<const int> sp(FakeRange{});
        EXPECT_EQ(&sp.front(), &kSpanData.front());
        EXPECT_EQ(&sp.back(), &kSpanData.back());
    }
    {
        ityp::span<Index, const int> sp(FakeTypedRange{});
        EXPECT_EQ(&sp.front(), &kSpanData.front());
        EXPECT_EQ(&sp.back(), &kSpanData.back());
    }
}

TEST(SpanDeathTest, FrontBackOfEmpty) {
    Span<const int> sp;
    EXPECT_DEATH_IF_SUPPORTED(sp.front(), "");
    EXPECT_DEATH_IF_SUPPORTED(sp.back(), "");
}

TEST(SpanTest, Indexing) {
    {
        Span<const int> sp(FakeRange{});
        for (size_t i = 0; i < kSpanData.size(); i++) {
            EXPECT_EQ(&sp.at(i), &kSpanData[i]);
            EXPECT_EQ(&sp[i], &kSpanData[i]);
        }
    }
    {
        ityp::span<Index, const int> sp(FakeTypedRange{});
        for (size_t i = 0; i < kSpanData.size(); i++) {
            Index id{static_cast<uint32_t>(i)};
            EXPECT_EQ(&sp.at(id), &kSpanData[i]);
            EXPECT_EQ(&sp[id], &kSpanData[i]);
        }
    }
}

TEST(SpanDeathTest, IndexingOOB) {
    Span<const int> sp(FakeRange{});
    EXPECT_DEATH_IF_SUPPORTED(sp.at(sp.size()), "");
    EXPECT_DEATH_IF_SUPPORTED(sp[sp.size()], "");

    Span<const int> spEmpty;
    EXPECT_DEATH_IF_SUPPORTED(spEmpty.at(0u), "");
    EXPECT_DEATH_IF_SUPPORTED(spEmpty[0u], "");
}

TEST(SpanDeathTest, IndexingOversizedIndex) {
    // These tests are only relevant on 32-bit builds.
    if constexpr (sizeof(size_t) > sizeof(uint32_t)) {
        GTEST_SKIP();
    }

    auto sp = ityp::span<Index64, const int>(FakeTyped64Range());

    // The narrowing to size_t would give 0 which is in bounds, so this checks that the cast to
    // size_t itself causes a crash.
    constexpr Index64 kHugeIndex{0x1'0000'0000LLU};
    EXPECT_DEATH_IF_SUPPORTED(sp[kHugeIndex], "");
}

// .data() and .size() are tested in every test essentially.

TEST(SpanTest, Empty) {
    ASSERT_FALSE(Span<const int>{FakeRange{}}.empty());
    // SAFETY: Test for the unsafe constructor.
    ASSERT_FALSE(DAWN_UNSAFE_BUFFERS((Span<const int>{static_cast<int*>(nullptr), 1u})).empty());
    ASSERT_TRUE(Span<const int>{}.empty());
    // SAFETY: Test for the unsafe constructor.
    ASSERT_TRUE(DAWN_UNSAFE_BUFFERS((Span<const int>{kSpanData.data(), 0u})).empty());

    ASSERT_FALSE((ityp::span<Index, const int>{FakeTypedRange{}}.empty()));
    ASSERT_FALSE(
        // SAFETY: Test for the unsafe constructor.
        DAWN_UNSAFE_BUFFERS((ityp::span<Index, const int>{static_cast<int*>(nullptr), Index{1u}}))
            .empty());
    ASSERT_TRUE((ityp::span<Index, const int>{}.empty()));
    ASSERT_TRUE(
        // SAFETY: Test for the unsafe constructor.
        DAWN_UNSAFE_BUFFERS((ityp::span<Index, const int>{kSpanData.data(), Index{0u}})).empty());
}

TEST(SpanTest, SizeBytes) {
    ASSERT_EQ(Span<int>{}.size_bytes(), 0u);
    ASSERT_EQ((ityp::span<Index, int>{}.size_bytes()), 0u);

    std::array<int, 3> ints{};
    ASSERT_EQ(Span<int>{ints}.size_bytes(), 3 * sizeof(int));

    std::array<double, 10> doubles{};
    ASSERT_EQ(Span<double>{doubles}.size_bytes(), 10 * sizeof(double));
}

TEST(SpanTest, FirstLast) {
    {
        Span<const int> sp{FakeRange()};
        Span<const int> first0 = sp.first(0);
        Span<const int> first2 = sp.first(2);
        Span<const int> last0 = sp.last(0);
        Span<const int> last2 = sp.last(2);

        EXPECT_EQ(first0.data(), sp.data());
        EXPECT_EQ(first0.size(), 0u);
        EXPECT_EQ(first2.data(), sp.data());
        EXPECT_EQ(first2.size(), 2u);

        EXPECT_EQ(last0.data(), &*sp.end());
        EXPECT_EQ(last0.size(), 0u);
        EXPECT_EQ(last2.data(), &sp.at(sp.size() - 2));
        EXPECT_EQ(last2.size(), 2u);
    }

    {
        ityp::span<Index, const int> sp{FakeTypedRange()};
        ityp::span<Index, const int> first0 = sp.first(Index{0u});
        ityp::span<Index, const int> first2 = sp.first(Index{2u});
        ityp::span<Index, const int> last0 = sp.last(Index{0u});
        ityp::span<Index, const int> last2 = sp.last(Index{2u});

        EXPECT_EQ(first0.data(), sp.data());
        EXPECT_EQ(first0.size(), Index{0u});
        EXPECT_EQ(first2.data(), sp.data());
        EXPECT_EQ(first2.size(), Index{2u});

        EXPECT_EQ(last0.data(), &*sp.end());
        EXPECT_EQ(last0.size(), Index{0u});
        EXPECT_EQ(last2.data(), &sp.at(sp.size() - Index{2u}));
        EXPECT_EQ(last2.size(), Index{2u});
    }
}

TEST(SpanDeathTest, FirstLastOOB) {
    Span<const int> sp{FakeRange()};

    sp.first(sp.size());
    EXPECT_DEATH_IF_SUPPORTED(sp.first(sp.size() + 1), "");

    sp.last(sp.size());
    EXPECT_DEATH_IF_SUPPORTED(sp.last(sp.size() + 1), "");
}

TEST(SpanTest, Subspan1Arg) {
    {
        Span<const int> sp{FakeRange()};
        Span<const int> subspan0 = sp.subspan(0);
        Span<const int> subspan2 = sp.subspan(2);

        EXPECT_EQ(subspan0.data(), sp.data());
        EXPECT_EQ(subspan0.size(), sp.size());
        EXPECT_EQ(subspan2.data(), &sp.at(2));
        EXPECT_EQ(subspan2.size(), sp.size() - 2);
    }
    {
        ityp::span<Index, const int> sp{FakeTypedRange()};
        ityp::span<Index, const int> subspan0 = sp.subspan(Index{0u});
        ityp::span<Index, const int> subspan2 = sp.subspan(Index{2u});

        EXPECT_EQ(subspan0.data(), sp.data());
        EXPECT_EQ(subspan0.size(), sp.size());
        EXPECT_EQ(subspan2.data(), &sp.at(Index{2u}));
        EXPECT_EQ(subspan2.size(), sp.size() - Index{2u});
    }
}

TEST(SpanDeathTest, Subspan1ArgOOB) {
    Span<const int> sp{FakeRange()};

    sp.subspan(sp.size());
    EXPECT_DEATH_IF_SUPPORTED(sp.subspan(sp.size() + 1), "");
}

TEST(SpanTest, Subspan2Args) {
    {
        Span<const int> sp{FakeRange()};
        Span<const int> subspan0_2 = sp.subspan(0, 2);
        Span<const int> subspan3_2 = sp.subspan(3, 2);

        EXPECT_EQ(subspan0_2.data(), sp.data());
        EXPECT_EQ(subspan0_2.size(), 2u);
        EXPECT_EQ(subspan3_2.data(), &sp.at(3));
        EXPECT_EQ(subspan3_2.size(), 2u);
    }
    {
        ityp::span<Index, const int> sp{FakeTypedRange()};
        ityp::span<Index, const int> subspan0_2 = sp.subspan(Index{0u}, Index{2u});
        ityp::span<Index, const int> subspan3_2 = sp.subspan(Index{3u}, Index{2u});

        EXPECT_EQ(subspan0_2.data(), sp.data());
        EXPECT_EQ(subspan0_2.size(), Index{2u});
        EXPECT_EQ(subspan3_2.data(), &sp.at(Index{3u}));
        EXPECT_EQ(subspan3_2.size(), Index{2u});
    }
}

TEST(SpanDeathTest, Subspan2ArgOOB) {
    Span<const int> sp{FakeRange()};

    sp.subspan(2, sp.size() - 2);
    EXPECT_DEATH_IF_SUPPORTED(sp.subspan(2, sp.size() - 1), "");

    // Check that overflows of offset + count is handled.
    EXPECT_DEATH_IF_SUPPORTED(sp.subspan(std::numeric_limits<size_t>::max(), 1), "");
    EXPECT_DEATH_IF_SUPPORTED(sp.subspan(1, std::numeric_limits<size_t>::max()), "");

    // SAFETY: This is the same range as kSpanData, just viewed with a uint8_t index (which fits the
    // size of kSpanData since it is 5).
    auto sp8 = DAWN_UNSAFE_BUFFERS(
        ityp::span<Index8, const int>(kSpanData.data(), Index8{uint8_t{kSpanData.size()}}));

    Index8 kOne = Index8{uint8_t{1}};
    Index8 kTwo = Index8{uint8_t{2}};
    sp8.subspan(kTwo, sp8.size() - kTwo);
    EXPECT_DEATH_IF_SUPPORTED(sp8.subspan(kTwo, sp8.size() - kOne), "");

    // Check that overflows of offset + count is handled.
    EXPECT_DEATH_IF_SUPPORTED(sp8.subspan(std::numeric_limits<Index8>::max(), kOne), "");
    EXPECT_DEATH_IF_SUPPORTED(sp8.subspan(kOne, std::numeric_limits<Index8>::max()), "");
}

}  // anonymous namespace
}  // namespace dawn
