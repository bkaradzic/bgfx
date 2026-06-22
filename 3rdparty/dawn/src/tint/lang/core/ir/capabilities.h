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

#ifndef SRC_TINT_LANG_CORE_IR_CAPABILITIES_H_
#define SRC_TINT_LANG_CORE_IR_CAPABILITIES_H_

#include "src/tint/utils/containers/enum_set.h"

namespace tint::core::ir {

/// Enumerator of optional IR capabilities.
/// TODO(crbug.com/512904070): Remove this when transition to properties is complete.
enum class Capability : uint8_t {
    /// Allows 16-bit integer types.
    kAllow16BitIntegers,
    /// Allows 64-bit integer types.
    kAllow64BitIntegers,
    /// Allows ShaderIO specific features, like blend_src on non-struct members.
    /// These are not separate capabilities, because they are enabled/disabled in lockstep with each
    /// other.
    /// TODO(448417342): Validate in/out address space usage based on this capability
    kLoosenValidationForShaderIO,
};

/// Capabilities is a set of Capability
using Capabilities = EnumSet<Capability>;

}  // namespace tint::core::ir

#endif  // SRC_TINT_LANG_CORE_IR_CAPABILITIES_H_
