/*
 * Copyright (c) 2023-present, Qihoo, Inc.  All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <folly/Portability.h>

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace folly {
inline void asm_volatile_memory() {
#if defined(__GNUC__) || defined(__clang__)
  asm volatile("" : : : "memory");
#elif defined(_MSC_VER)
  ::_ReadWriteBarrier();
#endif
}

inline void asm_volatile_pause() {
#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
  ::_mm_pause();
#elif defined(__i386__) || FOLLY_X64 ||                                        \
    (defined(__mips_isa_rev) && __mips_isa_rev > 1)
  asm volatile("pause");
#elif FOLLY_AARCH64
  asm volatile("isb");
#elif (defined(__arm__) && !(__ARM_ARCH < 7))
  asm volatile("yield");
#elif FOLLY_PPC64
  asm volatile("or 27,27,27");
#endif
}
} // namespace folly
