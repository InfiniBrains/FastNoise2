#pragma once
#include <cstdint>
#include <cstddef>

#include "FastSIMD_Export.h"

#if defined(__arm__) || defined(__aarch64__)
#define FASTSIMD_x86 false
#define FASTSIMD_ARM true
#else
#define FASTSIMD_x86 true
#define FASTSIMD_ARM false
#endif

#ifndef FASTSIMD_64BIT
#define FASTSIMD_64BIT (INTPTR_MAX == INT64_MAX)
#endif

#ifndef FASTSIMD_COMPILE_SCALAR
#define FASTSIMD_COMPILE_SCALAR (!(FASTSIMD_x86 && FASTSIMD_64BIT)) // Don't compile for x86 64bit since CPU is guaranteed SSE2 support 
#endif

#ifndef FASTSIMD_COMPILE_SSE
#define FASTSIMD_COMPILE_SSE    (FASTSIMD_x86 & false) // Not supported
#endif

#ifndef FASTSIMD_COMPILE_SSE2
#define FASTSIMD_COMPILE_SSE2   (FASTSIMD_x86 & true )
#endif

#ifndef FASTSIMD_COMPILE_SSE3
#define FASTSIMD_COMPILE_SSE3   (FASTSIMD_x86 & true )
#endif

#ifndef FASTSIMD_COMPILE_SSSE3
#define FASTSIMD_COMPILE_SSSE3  (FASTSIMD_x86 & true )
#endif

#ifndef FASTSIMD_COMPILE_SSE41
#define FASTSIMD_COMPILE_SSE41  (FASTSIMD_x86 & true )
#endif

#ifndef FASTSIMD_COMPILE_SSE42
#define FASTSIMD_COMPILE_SSE42  (FASTSIMD_x86 & true )
#endif

#ifndef FASTSIMD_COMPILE_AVX
#define FASTSIMD_COMPILE_AVX    (FASTSIMD_x86 & false) // Not supported
#endif

#ifndef FASTSIMD_COMPILE_AVX2
#define FASTSIMD_COMPILE_AVX2   (FASTSIMD_x86 & true )
#endif

#ifndef FASTSIMD_COMPILE_AVX512
#define FASTSIMD_COMPILE_AVX512 (FASTSIMD_x86 & true )
#endif

#ifndef FASTSIMD_COMPILE_NEON
#define FASTSIMD_COMPILE_NEON   (FASTSIMD_ARM & true )
#endif

#ifndef FASTSIMD_USE_FMA
#define FASTSIMD_USE_FMA                   true
#endif

#ifndef FASTSIMD_CONFIG_GENERATE_CONSTANTS
#define FASTSIMD_CONFIG_GENERATE_CONSTANTS false
#endif
