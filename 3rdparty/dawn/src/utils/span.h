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

#ifndef SRC_UTILS_SPAN_H_
#define SRC_UTILS_SPAN_H_

#include <concepts>
#include <limits>
#include <memory>
#include <span>

#include "src/utils/numeric.h"
#include "src/utils/underlying_type.h"

namespace dawn {

// A span is a contiguous view of elements that can be accessed like an array. They are preferred
// over pointers and sizes because they enforce safe usage (in addition to requiring less typing).
// Dawn has its own Span class for multiple reasons:
//
// - It needs a version of std::span that can work with TypedInteger to make it impossible to use a
//   span with the wrong kind of index.
// - It needs a version of std::span with a configurable type for the pointer, so that it can be
//   changed to a raw_ptr<T> when the span is stored as a member (this is important to keep the
//   MiraclePtr refcount exact).
// - It ensures that the layout of Span is exactly (size_t mSize, T* mData) to match webgpu.h
//   structures where the count of elements always comes just before the pointer to the elements.
//   This is important because conversions between webgpu.h and dawn_platform.h structures is done
//   by simply casting the pointer (and checking that the layout matches). dawn_platform.h
//   structures use Span so we need to know the exact layout.
//
// The deviations from std::span are marked with DIFF.

namespace detail {
template <typename T, HasUnsignedUnderlyingType Index, typename PtrType>
class SpanBase;
}

// A direct replacement for std::span<T>
template <typename T>
using Span = detail::SpanBase<T, size_t, T*>;

namespace ityp {
// A replacement for std::span<T> but with a different index type (like a TypedInteger).
template <typename Index, typename T>
using span = dawn::detail::SpanBase<T, Index, T*>;
}  // namespace ityp

// The equivalent of std::dynamic_extent for the given index type.
template <typename Index>
inline constexpr Index DynamicExtent = std::numeric_limits<Index>::max();

namespace detail {

template <typename From, typename To>
concept LegalDataConversion = std::is_convertible_v<From (*)[], To (*)[]>;

template <typename T, typename It>
concept CompatibleIter = std::contiguous_iterator<It> &&
                         LegalDataConversion<std::remove_reference_t<std::iter_reference_t<It>>, T>;

template <typename T, typename Index, typename R>
concept CompatibleRange = requires(R r) {
    { r.data() } -> std::convertible_to<T*>;
    { r.size() } -> std::same_as<Index>;
};

// DIFF: only dynamic_extent is supported at the moment because Dawn might not need spans with
// static extents.
// DIFF: size_t in function signatures is replaced by Index to support typed integers as the index
// type. The only exception is size_bytes().
template <typename T, HasUnsignedUnderlyingType Index, typename PtrType>
class SpanBase {
  private:
    using Self = SpanBase<T, Index, PtrType>;

  public:
    // Type aliases and static members.

    // DIFF: size_type / difference_type missing because it's not clear what they should be, Index
    // or size_t?
    // DIFF: const_iterator missing to match LLVM's libc++
    // DIFF: [const_]reverse_iterator missing to avoid including <iterator> until it is needed.
    using element_type = T;
    using value_type = std::remove_cv<T>::type;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using iterator = std::span<T>::iterator;

    static inline constexpr Index extent = DynamicExtent<Index>;

    // Constructors
    // DIFF: The constructor from a C-style array is not present.
    // DIFF: Many constructors are UNSAFE_BUFFER_USAGE.
    // DIFF: The constructor from a range is less strict than the spec requires as it would be
    // challenging to duplicate the exact logic while keeping support for custom index types.

    constexpr SpanBase() noexcept = default;

    // Constructor from a pointer + size. This is UNSAFE_BUFFER_USAGE as other methods should be
    // preferred to create spans directly from ranges. Will DAWN_CHECK() if the size doesn't fit in
    // a size_t.
    template <typename It>
        requires CompatibleIter<element_type, It>
    DAWN_UNSAFE_BUFFER_USAGE constexpr SpanBase(It first, Index count)
        : mSize(checked_cast<size_t>(count)), mData(std::to_address(first)) {
        DAWN_CHECK(count != DynamicExtent<Index>);
    }

    // Constructor from two iterators, this is UNSAFE_BUFFER_USAGE as other method should be
    // preferred to create spans directly from ranges. Will DAWN_CHECK() if the size doesn't fit in
    // a size_t.
    template <typename It, typename End>
        requires(CompatibleIter<element_type, It> && std::sized_sentinel_for<End, It> &&
                 !std::is_convertible_v<End, size_t>)
    DAWN_UNSAFE_BUFFER_USAGE constexpr SpanBase(It first, End last)
        : mSize(last - first), mData(std::to_address(first)) {
        DAWN_CHECK(first <= last);
        if constexpr (sizeof(size_t) > sizeof(Index)) {
            DAWN_CHECK(mSize <= size_t{UnderlyingType<Index>{DynamicExtent<Index>}});
        }
    }

    // Constructor from a "range-like" that provides `T* data()` and `Index size()`. Note that this
    // is quite different from Chromium's base::span constructor from ranges because adapting that
    // constructor to support TypedInteger for Index would be extremely challenging. Will
    // DAWN_CHECK() if the size doesn't fit in a size_t.
    template <typename R>
        requires CompatibleRange<T, Index, R>
    // NOLINTNEXTLINE(runtime/explicit)
    constexpr SpanBase(R&& range)
        : mSize(checked_cast<size_t>(range.size())), mData(range.data()) {}
    template <typename R>
        requires CompatibleRange<T, Index, R> && std::is_const_v<T>
    // NOLINTNEXTLINE(runtime/explicit)
    constexpr SpanBase(const R& range)
        : mSize(checked_cast<size_t>(range.size())), mData(range.data()) {}

    // Move / copy constructor / assignment operator.
    constexpr SpanBase(const SpanBase& other) noexcept = default;
    constexpr SpanBase(SpanBase&& other) noexcept = default;
    constexpr SpanBase& operator=(const SpanBase& other) noexcept = default;
    constexpr SpanBase& operator=(SpanBase&& other) noexcept = default;

    // Iterators
    //
    // Note that iterators use the std::span iterators to take advantage of the hardened stdlib.

    // DIFF: cbegin/cend missing to match LLVM's libc++
    // DIFF: r[c]begin/end missing to avoid including <iterator> until it is needed.

    constexpr iterator begin() const noexcept { return as_std_span().begin(); }
    constexpr iterator end() const noexcept { return as_std_span().end(); }

    // Element access

    // Returns a reference to the first element of this. When empty, will DAWN_CHECK().
    constexpr reference front() const noexcept { return at(Index{0u}); }
    // Returns a reference to the last element of this. When empty, will DAWN_CHECK().
    constexpr reference back() const noexcept {
        // Note that an underflow happens in empty spans, which will make the argument to `at` be
        // the maximum value and cause a DAWN_CHECK.
        return at(size() - Index{1u});
    }

    // Returns a reference to the element of this at `index`. Will DAWN_CHECK() if OOB.
    constexpr reference at(Index index) const {
        DAWN_CHECK(index < size());
        // SAFETY: The argument to unchecked_at is already checked in range in the DAWN_CHECK above.
        return DAWN_UNSAFE_BUFFERS(unchecked_at(index));
    }
    // Returns a reference to the element of this at `index`. Will DAWN_CHECK() if OOB.
    constexpr T& operator[](Index index) const noexcept { return at(index); }

    // Returns a pointer at the contents of this.
    constexpr pointer data() const noexcept { return mData; }

    // Observers

    // Returns the number of elements of this.
    constexpr Index size() const noexcept {
        return Index(static_cast<UnderlyingType<Index>>(mSize));
    }

    // Returns the footprint in bytes of the elements of this.
    constexpr size_t size_bytes() const noexcept { return mSize * sizeof(element_type); }

    // Returns true if this contains no elements.
    [[nodiscard]] constexpr bool empty() const noexcept { return mSize == 0; }

    // Subviews
    // DIFF: subviews with template Offset / Count missing.
    // DIFF: dynamic_extent is not supported in the 2-arg version of subspan(), the single argument
    // overload must be used instead.

    // Returns a span of the first `count` elements of this. Will DAWN_CHECK() if OOB.
    constexpr Self first(Index count) const {
        DAWN_CHECK(count <= size());
        // SAFETY: data() points at at least size() elements, so the DAWN_CHECK ensure that the
        // result span is a subset of this
        return DAWN_UNSAFE_BUFFERS(Self(data(), count));
    }

    // Returns a span of the last `count` elements of this. Will DAWN_CHECK() if OOB.
    constexpr Self last(Index count) const {
        DAWN_CHECK(count <= size());
        // SAFETY: data() points at at least size() elements, so the DAWN_CHECK ensure that the
        // result span is a subset of this. The argument to unchecked_at is already checked in range
        // in the DAWN_CHECK above.
        return DAWN_UNSAFE_BUFFERS(Self(&unchecked_at(size() - count), count));
    }

    // Returns a span starting at `offset` and until the end of this. Will DAWN_CHECK() if OOB.
    constexpr Self subspan(Index offset) const {
        DAWN_CHECK(offset <= size());
        Index remainingSize = size() - offset;
        // SAFETY: data() points at at least size() elements, so the DAWN_CHECK ensure that the
        // result span is a subset of this. The argument to unchecked_at is already checked in range
        // in the first DAWN_CHECK above.
        return DAWN_UNSAFE_BUFFERS(Self(&unchecked_at(offset), remainingSize));
    }
    // Returns a span starting at `offset` and of `count` elements inside of this. Will DAWN_CHECK()
    // if OOB.
    constexpr Self subspan(Index offset, Index count) const {
        DAWN_CHECK(offset <= size());
        DAWN_CHECK(count <= size() - offset);
        // SAFETY: data() points at at least size() elements, so the DAWN_CHECKs ensure that the
        // result span is a subset of this. The argument to unchecked_at is already checked in range
        // in the first DAWN_CHECK above.
        return DAWN_UNSAFE_BUFFERS(Self(&unchecked_at(offset), count));
    }

    // Additions not part of std::span.

    // None for now, but consider adding the following like in Chromium's base::span:
    //
    //  - constructor from (&T)[N]
    //  - operator ==, operator <=>
    //  - copy_from, copy_prefix_from
    //  - split_at, take_first, take_first_elem
    //  - get_at
    //  - to_fixed_extent

  private:
    // Helper function used to avoid doing the DAWN_CHECK inside at() redundantly when the
    // precondition is already checked by some other mean.
    DAWN_UNSAFE_BUFFER_USAGE constexpr reference unchecked_at(Index typedIndex) const {
        size_t index = checked_cast<size_t>(typedIndex);
        // SAFETY: The caller must guarantee that the index is in range already.
        return DAWN_UNSAFE_BUFFERS(*(data() + index));
    }

    // Helper function to return the equivalent std::span. This is necessary to be able to use
    // the hardened std::span iterators when the standard library enables them.
    constexpr std::span<T> as_std_span() const {
        // SAFETY: This is the same allocation and size as this.
        return DAWN_UNSAFE_BUFFERS({mData, mSize});
    }

    // Keep members in this order as it matches the layout of webgpu.h, see toplevel comment.
    size_t mSize = 0;
    PtrType mData = {};
};

}  // namespace detail

}  // namespace dawn

#endif  // SRC_UTILS_SPAN_H_
