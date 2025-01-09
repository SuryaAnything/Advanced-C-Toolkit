#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#ifndef __STR_RT_VERSION__
#define __STR_RT_VERSION__

#ifdef __cplusplus
    #define __BRXC extern "C"
#else
    #define __BRXC
#endif

#define __str_restrict __restrict

#if defined(__GNUC__)
    #define __STR__ATTRIB_PURE  __attribute__((__pure__))
    #define __STR__ATTRIB_CONST __attribute__((__const__))
#else
    #define __STR__ATTRIB_PURE
    #define __STR__ATTRIB_CONST
#endif

#if defined(_MSC_VER)
    #define __STR_FORCE_INLINE __forceinline
    #define __STR_NO_INLINE __declspec(noinline)
#elif defined(__GNUC__)
    #define __STR_FORCE_INLINE inline __attribute__((always_inline))
    #define __STR_NO_INLINE __attribute__((noinline))
#else
    #define __STR_FORCE_INLINE inline
    #define __STR_NO_INLINE
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define STR_DLL_EXPORT __declspec(dllexport)
    #define STR_DLL_IMPORT __declspec(dllimport)
#else
    #define STR_DLL_EXPORT __attribute__((visibility("default")))
    #define STR_DLL_IMPORT
#endif

#if defined(_MSC_VER)
    #define __STR_DEPRECATED(msg) __declspec(deprecated(msg))
#elif defined(__GNUC__) || defined(__clang__)
    #define __STR_DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
    #define __STR_DEPRECATED(msg)
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define __STR_LIKELY(x)   __builtin_expect(!!(x), 1)
    #define __STR_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define __STR_LIKELY(x)   (x)
    #define __STR_UNLIKELY(x) (x)
#endif

#if defined(_MSC_VER)
    #define __STR_INLINE __inline
#else
    #define __STR_INLINE inline
#endif

#endif /* __STR_RT_VERSION__ */

#define STR_STREAM_DEFAULT_CAPACITY 16
#define STR_STREAM_AUTO_CREATE  str_auto_create()

typedef struct __string_stream {
    char* buffer;
    size_t size;
    size_t capacity;
    size_t cursor;
}str_stream;

STR_DLL_EXPORT __BRXC __cdecl void str_init(str_stream* __Stream, size_t __Capacity);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl str_stream* str_create(size_t __Capacity);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl str_stream* str_auto_create();
STR_DLL_EXPORT __BRXC __cdecl void str_free(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl void str_push_back(str_stream* __Stream, char __Ch);
STR_DLL_EXPORT __BRXC __cdecl void str_append(str_stream* __Stream, const char* __Str);
STR_DLL_EXPORT __BRXC __cdecl void str_pop_back(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl void str_clear(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl void str_seek(str_stream* __Stream, size_t __Pos);
STR_DLL_EXPORT __BRXC __cdecl void str_seek_end(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl char* str_c_str(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl char str_at(str_stream* __Stream, size_t __Pos);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl size_t str_size(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl size_t str_capacity(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl size_t str_cursor(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl void str_print(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl void str_println(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl str_stream* str_copy(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl bool str_empty(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl void str_shrink_to_fit(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl char str_back(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl char str_front(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl str_stream* str_substr(str_stream* __Stream, size_t __Pos, size_t __Len);
STR_DLL_EXPORT __BRXC __cdecl void str_insert(str_stream* __Stream, size_t __Pos, char __Ch);
STR_DLL_EXPORT __BRXC __cdecl void str_erase(str_stream* __Stream, size_t __Pos);
STR_DLL_EXPORT __BRXC __cdecl void str_erase_range(str_stream* __Stream, size_t __Pos, size_t __Len);
STR_DLL_EXPORT __BRXC __cdecl void str_replace(str_stream* __Stream, size_t __Pos, char __Ch);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl char* str_data(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl int str_find(str_stream* __Stream, char __Ch);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl int str_rfind(str_stream* __Stream, char __Ch);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl bool str_contains(str_stream* __Stream, char __Ch);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl bool str_starts_with(str_stream* __Stream, const char* __Str);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl bool str_ends_with(str_stream* __Stream, const char* __Str);
STR_DLL_EXPORT __BRXC __cdecl void str_reverse(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl void str_resize(str_stream* __Stream, size_t __NewSize);
STR_DLL_EXPORT __BRXC __cdecl void str_resize_fill(str_stream* __Stream, size_t __NewSize, char __Ch);
STR_DLL_EXPORT __BRXC __cdecl void str_swap(str_stream* __Stream1, str_stream* __Stream2);
STR_DLL_EXPORT __BRXC __cdecl void str_concat(str_stream* __Stream1, str_stream* __Stream2);
STR_DLL_EXPORT __BRXC __cdecl void str_concat_cstr(str_stream* __Stream1, const char* __Str);
STR_DLL_EXPORT __BRXC __cdecl void str_flush(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl bool str_includes(str_stream* __Stream, const char* __Str);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl bool str_equals(str_stream* __Stream1, str_stream* __Stream2);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl bool str_equals_cstr(str_stream* __Stream, const char* __Str);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl bool str_less_than(str_stream* __Stream1, str_stream* __Stream2);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl int str_compare(str_stream* __Stream1, str_stream* __Stream2);
STR_DLL_EXPORT __BRXC __cdecl void str_trim(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl void str_to_lower(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl void str_to_upper(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl str_stream** str_split(str_stream* __Stream, char __Delim, size_t* __Count);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl str_stream** str_split_line(str_stream* __Stream, size_t* __Count);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl str_stream* str_join(str_stream** __Streams, char __Delim, size_t __Size);
STR_DLL_EXPORT __BRXC __cdecl void str_pad(str_stream* __Stream, size_t __Length, char __Ch);
STR_DLL_EXPORT __BRXC __cdecl void str_sort(str_stream* __Stream);
STR_DLL_EXPORT __BRXC __cdecl void str_rsort(str_stream* __Stream);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl int str_lowerbound(str_stream* __Stream, char __Ch);
STR_DLL_EXPORT __STR__ATTRIB_PURE __BRXC __cdecl int str_upperbound(str_stream* __Stream, char __Ch);

