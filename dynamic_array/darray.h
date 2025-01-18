#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __DEFAULT_DARRAY_CAPACITY 10
#define DARRAY_AUTO_CREATE()    darray_create()

#ifndef __DARR_RT_VERSION__
#define __DARR_RT_VERSION__

#ifdef __cplusplus
    #define __BRXC extern "C"
#else
    #define __BRXC
#endif

#define __darr_restrict __restrict

#if defined(__GNUC__)
    #define __DARR__ATTRIB_PURE  __attribute__((__pure__))
    #define __DARR__ATTRIB_CONST __attribute__((__const__))
#else
    #define __DARR__ATTRIB_PURE
    #define __DARR__ATTRIB_CONST
#endif

#if defined(_MSC_VER)
    #define __DARR_FORCE_INLINE __forceinline
    #define __DARR_NO_INLINE __declspec(noinline)
#elif defined(__GNUC__)
    #define __DARR_FORCE_INLINE inline __attribute__((always_inline))
    #define __DARR_NO_INLINE __attribute__((noinline))
#else
    #define __DARR_FORCE_INLINE inline
    #define __DARR_NO_INLINE
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define DARR_DLL_EXPORT __declspec(dllexport)
    #define DARR_DLL_IMPORT __declspec(dllimport)
#else
    #define DARR_DLL_EXPORT __attribute__((visibility("default")))
    #define DARR_DLL_IMPORT
#endif

#if defined(_MSC_VER)
    #define __DARR_DEPRECATED(msg) __declspec(deprecated(msg))
#elif defined(__GNUC__) || defined(__clang__)
    #define __DARR_DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
    #define __DARR_DEPRECATED(msg)
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define __DARR_LIKELY(x)   __builtin_expect(!!(x), 1)
    #define __DARR_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define __DARR_LIKELY(x)   (x)
    #define __DARR_UNLIKELY(x) (x)
#endif

#if defined(_MSC_VER)
    #define __DARR_INLINE __inline
#else
    #define __DARR_INLINE inline
#endif

#endif

typedef struct _darray {
    int *data;
    size_t size;
    size_t capacity;
    size_t element_size;
    void (*free_fn)(void *);
} darray_t;

DARR_DLL_EXPORT __BRXC __cdecl void darray_init(darray_t* __darr_restrict darray);
DARR_DLL_EXPORT __BRXC __cdecl darray_t *darray_create();
DARR_DLL_EXPORT __BRXC __cdecl void darray_flush(darray_t* __darr_restrict darray);
DARR_DLL_EXPORT __BRXC __cdecl void darray_push(darray_t *darray, int value);
DARR_DLL_EXPORT __BRXC __cdecl int darray_pop(darray_t *darray);
DARR_DLL_EXPORT __BRXC __cdecl void darray_set_free_fn(darray_t *darray, void (*free_fn)(void *));
DARR_DLL_EXPORT __BRXC __cdecl void darray_print(darray_t *darray);
DARR_DLL_EXPORT __BRXC __cdecl int darray_size(darray_t *darray) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl int darray_capacity(darray_t *darray) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl int darray_element_size(darray_t *darray) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl int darray_get(darray_t *darray, size_t index);
DARR_DLL_EXPORT __BRXC __cdecl void darray_set(darray_t *darray, size_t index, int value);
DARR_DLL_EXPORT __BRXC __cdecl int darray_front(darray_t *darray) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl int darray_back(darray_t *darray) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl int darray_empty(darray_t *darray) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl void darray_clear(darray_t *darray);
DARR_DLL_EXPORT __BRXC __cdecl void darray_resize(darray_t *darray, size_t new_size);
DARR_DLL_EXPORT __BRXC __cdecl void darray_reserve(darray_t *darray, size_t new_capacity);
DARR_DLL_EXPORT __BRXC __cdecl void darray_shrink_to_fit(darray_t *darray);
DARR_DLL_EXPORT __BRXC __cdecl void darray_insert(darray_t *darray, size_t index, int value);
DARR_DLL_EXPORT __BRXC __cdecl void darray_erase(darray_t *darray, size_t index);
DARR_DLL_EXPORT __BRXC __cdecl void darray_remove(darray_t *darray, int value);
DARR_DLL_EXPORT __BRXC __cdecl void darray_push_front(darray_t *darray, int value);
DARR_DLL_EXPORT __BRXC __cdecl void darray_pop_front(darray_t *darray);
DARR_DLL_EXPORT __BRXC __cdecl void darray_erase_range(darray_t *darray, size_t start, size_t end);
DARR_DLL_EXPORT __BRXC __cdecl void darray_push_all(darray_t *darray, int *values, size_t size);
DARR_DLL_EXPORT __BRXC __cdecl void darray_remove_if(darray_t *darray, int (*predicate)(int));
DARR_DLL_EXPORT __BRXC __cdecl void darray_reverse(darray_t *darray);
DARR_DLL_EXPORT __BRXC __cdecl void darray_map(darray_t *darray, int (*mapper)(int));
DARR_DLL_EXPORT __BRXC __cdecl void darray_filter(darray_t *darray, int (*predicate)(int));
DARR_DLL_EXPORT __BRXC __cdecl void darray_reduce(darray_t *darray, int (*reducer)(int, int));
DARR_DLL_EXPORT __BRXC __cdecl int darray_sum(darray_t* darray) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl int darray_max(darray_t* darray) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl int darray_min(darray_t* darray) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl int darray_avg(darray_t* darray) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl int* darray_data(darray_t *darray);
DARR_DLL_EXPORT __BRXC __cdecl void darray_set_data(darray_t *darray, int *data, size_t size);
DARR_DLL_EXPORT __BRXC __cdecl void darray_copy(darray_t *darray, darray_t *other);
DARR_DLL_EXPORT __BRXC __cdecl void darray_swap(darray_t *darray, darray_t *other);
DARR_DLL_EXPORT __BRXC __cdecl void darray_for_each(darray_t *darray, void (*func)(int));
DARR_DLL_EXPORT __BRXC __cdecl int darray_binary_search(darray_t *darray, int value);
DARR_DLL_EXPORT __BRXC __cdecl size_t darray_memory_usage(darray_t *darray);
DARR_DLL_EXPORT __BRXC __cdecl void darray_replace(darray_t *darray, int old_value, int new_value);
DARR_DLL_EXPORT __BRXC __cdecl void darray_fill(darray_t *darray, int value);
DARR_DLL_EXPORT __BRXC __cdecl size_t darray_count(darray_t *darray, int value);
DARR_DLL_EXPORT __BRXC __cdecl void darray_sort(darray_t *darray);
DARR_DLL_EXPORT __BRXC __cdecl void darray_sort_custom(darray_t *darray, int (*cmp)(int, int));
DARR_DLL_EXPORT __BRXC __cdecl size_t darray_index_of(darray_t *darray, int value) __DARR__ATTRIB_PURE;
DARR_DLL_EXPORT __BRXC __cdecl int darray_median(darray_t* darray) __DARR__ATTRIB_PURE;
