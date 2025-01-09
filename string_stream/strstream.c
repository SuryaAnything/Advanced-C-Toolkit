#include "strstream.h"

void str_init(str_stream* __Stream, size_t __Capacity) {
    __Stream->buffer = (char*)malloc(__Capacity);
    __Stream->size = 0;
    __Stream->capacity = __Capacity;
    __Stream->cursor = 0;
}

str_stream* str_create(size_t __Capacity) {
    str_stream* __Stream = (str_stream*)malloc(sizeof(str_stream));
    str_init(__Stream, __Capacity);
    return __Stream;
}

str_stream* str_auto_create() {
    str_stream* __Stream = (str_stream*)malloc(sizeof(str_stream));
    str_init(__Stream, STR_STREAM_DEFAULT_CAPACITY);
    return __Stream;
}

void str_free(str_stream* __Stream) {
    free(__Stream->buffer);
    free(__Stream);
}

void str_push_back(str_stream* __Stream, char __Ch) {
    if (__Stream->size + 1 >= __Stream->capacity) {
        __Stream->capacity *= 2;
        __Stream->buffer = (char*)realloc(__Stream->buffer, __Stream->capacity);
    }
    __Stream->buffer[__Stream->size++] = __Ch;
}

void str_append(str_stream* __Stream, const char* __Str) {
    size_t __Len = strlen(__Str);
    for (size_t i = 0; i < __Len; i++) {
        str_push_back(__Stream, __Str[i]);
    }
}

void str_pop_back(str_stream* __Stream) {
    if (__Stream->size > 0) {
        __Stream->size--;
    }
}

void str_clear(str_stream* __Stream) {
    __Stream->size = 0;
}

void str_seek(str_stream* __Stream, size_t __Pos) {
    __Stream->cursor = __Pos;
}

void str_seek_end(str_stream* __Stream) {
    __Stream->cursor = __Stream->size;
}

char* str_c_str(str_stream* __Stream) {
    char* __Res = (char*)malloc(__Stream->size + 1);
    for (size_t i = 0; i < __Stream->size; i++) {
        __Res[i] = __Stream->buffer[i];
    }
    __Res[__Stream->size] = '\0';
    return __Res;
}

char str_at(str_stream* __Stream, size_t __Pos) {
    return __Stream->buffer[__Pos];
}

size_t str_size(str_stream* __Stream) {
    return __Stream->size;
}

size_t str_capacity(str_stream* __Stream) {
    return __Stream->capacity;
}

size_t str_cursor(str_stream* __Stream) {
    return __Stream->cursor;
}

void str_print(str_stream* __Stream) {
    for (size_t i = 0; i < __Stream->size; i++) {
        printf("%c", __Stream->buffer[i]);
    }
}

void str_println(str_stream* __Stream) {
    str_print(__Stream);
    printf("\n");
}

str_stream* str_copy(str_stream* __Stream) {
    str_stream* __Res = str_auto_create();
    for (size_t i = 0; i < __Stream->size; i++) {
        str_push_back(__Res, __Stream->buffer[i]);
    }
    return __Res;
}

bool str_empty(str_stream* __Stream) {
    return __Stream->size == 0;
}

void str_shrink_to_fit(str_stream* __Stream) {
    __Stream->capacity = __Stream->size;
    __Stream->buffer = (char*)realloc(__Stream->buffer, __Stream->size);
}

char str_back(str_stream* __Stream) {
    return __Stream->buffer[__Stream->size - 1];
}

char str_front(str_stream* __Stream) {
    return __Stream->buffer[0];
}

str_stream* str_substr(str_stream* __Stream, size_t __Pos, size_t __Len) {
    str_stream* __Res = str_auto_create();
    for (size_t i = __Pos; i < __Pos + __Len; i++) {
        str_push_back(__Res, __Stream->buffer[i]);
    }
    return __Res;
}

void str_insert(str_stream* __Stream, size_t __Pos, char __Ch) {
    if (__Stream->size + 1 >= __Stream->capacity) {
        __Stream->capacity *= 2;
        __Stream->buffer = (char*)realloc(__Stream->buffer, __Stream->capacity);
    }
    for (size_t i = __Stream->size; i > __Pos; i--) {
        __Stream->buffer[i] = __Stream->buffer[i - 1];
    }
    __Stream->buffer[__Pos] = __Ch;
    __Stream->size++;
}

void str_erase(str_stream* __Stream, size_t __Pos) {
    for (size_t i = __Pos; i < __Stream->size - 1; i++) {
        __Stream->buffer[i] = __Stream->buffer[i + 1];
    }
    __Stream->size--;
}

void str_erase_range(str_stream* __Stream, size_t __Pos, size_t __Len) {
    for (size_t i = __Pos; i < __Stream->size - __Len; i++) {
        __Stream->buffer[i] = __Stream->buffer[i + __Len];
    }
    __Stream->size -= __Len;
}

void str_replace(str_stream* __Stream, size_t __Pos, char __Ch) {
    __Stream->buffer[__Pos] = __Ch;
}

char* str_data(str_stream* __Stream) {
    return __Stream->buffer;
}

int str_find(str_stream* __Stream, char __Ch) {
    for (size_t i = 0; i < __Stream->size; i++) {
        if (__Stream->buffer[i] == __Ch) {
            return i;
        }
    }
    return -1;
}

int str_rfind(str_stream* __Stream, char __Ch) {
    for (int i = (int)__Stream->size - 1; i >= 0; --i) {
        if (__Stream->buffer[i] == __Ch) {
            return i;
        }
    }
    return -1;
}

bool str_contains(str_stream* __Stream, char __Ch) {
    for (size_t i = 0; i < __Stream->size; i++) {
        if (__Stream->buffer[i] == __Ch) {
            return true;
        }
    }
    return false;
}

bool str_starts_with(str_stream* __Stream, const char* __Str) {
    size_t __Len = strlen(__Str);
    if (__Stream->size < __Len) {
        return false;
    }
    for (size_t i = 0; i < __Len; i++) {
        if (__Stream->buffer[i] != __Str[i]) {
            return false;
        }
    }
    return true;
}

bool str_ends_with(str_stream* __Stream, const char* __Str) {
    size_t __Len = strlen(__Str);
    if (__Stream->size < __Len) {
        return false;
    }
    for (size_t i = 0; i < __Len; i++) {
        if (__Stream->buffer[__Stream->size - __Len + i] != __Str[i]) {
            return false;
        }
    }
    return true;
}

void str_reverse(str_stream* __Stream) {
    for (size_t i = 0; i < __Stream->size / 2; i++) {
        char __Temp = __Stream->buffer[i];
        __Stream->buffer[i] = __Stream->buffer[__Stream->size - i - 1];
        __Stream->buffer[__Stream->size - i - 1] = __Temp;
    }
}

void str_resize(str_stream* __Stream, size_t __NewSize) {
    if (__NewSize > __Stream->size) {
        for (size_t i = __Stream->size; i < __NewSize; i++) {
            str_push_back(__Stream, '\0');
        }
    }
    else {
        __Stream->size = __NewSize;
    }
}

void str_resize_fill(str_stream* __Stream, size_t __NewSize, char __Ch) {
    if (__NewSize > __Stream->size) {
        for (size_t i = __Stream->size; i < __NewSize; i++) {
            str_push_back(__Stream, __Ch);
        }
    }
    else {
        __Stream->size = __NewSize;
    }
}

void str_swap(str_stream* __Stream1, str_stream* __Stream2) {
    str_stream __Temp = *__Stream1;
    *__Stream1 = *__Stream2;
    *__Stream2 = __Temp;
}

void str_concat(str_stream* __Stream1, str_stream* __Stream2) {
    for (size_t i = 0; i < __Stream2->size; i++) {
        str_push_back(__Stream1, __Stream2->buffer[i]);
    }
}

void str_concat_cstr(str_stream* __Stream1, const char* __Str) {
    size_t __Len = strlen(__Str);
    for (size_t i = 0; i < __Len; i++) {
        str_push_back(__Stream1, __Str[i]);
    }
}

void str_flush(str_stream* __Stream) {
    free(__Stream->buffer);
    __Stream->buffer = (char*)malloc(__Stream->capacity);
    __Stream->size = 0;
    __Stream->cursor = 0;
}

bool str_includes(str_stream* __Stream, const char* __Str) {
    size_t __StreamLen = __Stream->size;
    size_t __StrLen = strlen(__Str);
    
    if (__StrLen == 0) return true;

    int* lps = (int*)malloc(__StrLen * sizeof(int));
    size_t length = 0;
    lps[0] = 0;
    size_t i = 1;

    while (i < __StrLen) {
        if (__Str[i] == __Str[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;
    size_t j = 0;

    while (i < __StreamLen) {
        if (__Stream->buffer[i] == __Str[j]) {
            i++;
            j++;
        }

        if (j == __StrLen) {
            free(lps);
            return true;
        } else if (i < __StreamLen && __Stream->buffer[i] != __Str[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    return false;
}

bool str_equals(str_stream* __Stream1, str_stream* __Stream2) {
    if (__Stream1->size != __Stream2->size) {
        return false;
    }
    for (size_t i = 0; i < __Stream1->size; i++) {
        if (__Stream1->buffer[i] != __Stream2->buffer[i]) {
            return false;
        }
    }
    return true;
}

bool str_equals_cstr(str_stream* __Stream, const char* __Str) {
    size_t __Len = strlen(__Str);
    if (__Stream->size != __Len) {
        return false;
    }
    for (size_t i = 0; i < __Len; i++) {
        if (__Stream->buffer[i] != __Str[i]) {
            return false;
        }
    }
    return true;
}

bool str_less_than(str_stream* __Stream1, str_stream* __Stream2) {
    size_t __MinSize = __Stream1->size < __Stream2->size ? __Stream1->size : __Stream2->size;
    for (size_t i = 0; i < __MinSize; i++) {
        if (__Stream1->buffer[i] < __Stream2->buffer[i]) {
            return true;
        }
        else if (__Stream1->buffer[i] > __Stream2->buffer[i]) {
            return false;
        }
    }
    return __Stream1->size < __Stream2->size;
}

int str_compare(str_stream* __Stream1, str_stream* __Stream2) {
    if (str_equals(__Stream1, __Stream2)) {
        return 0;
    }
    else if (str_less_than(__Stream1, __Stream2)) {
        return -1;
    }
    else {
        return 1;
    }
}

void str_trim(str_stream* __Stream) {
    size_t start = 0;
    while (start < __Stream->size && (__Stream->buffer[start] == ' ' || __Stream->buffer[start] == '\n' || __Stream->buffer[start] == '\t')) {
        start++;
    }

    size_t end = __Stream->size;
    while (end > start && (__Stream->buffer[end - 1] == ' ' || __Stream->buffer[end - 1] == '\n' || __Stream->buffer[end - 1] == '\t')) {
        end--;
    }

    str_stream* temp = str_substr(__Stream, start, end - start);
    str_swap(__Stream, temp);
    str_free(temp);
}

void str_to_lower(str_stream* __Stream) {
    for (size_t i = 0; i < __Stream->size; i++) {
        if (__Stream->buffer[i] >= 'A' && __Stream->buffer[i] <= 'Z') {
            __Stream->buffer[i] += 'a' - 'A';
        }
    }
}

void str_to_upper(str_stream* __Stream) {
    for (size_t i = 0; i < __Stream->size; i++) {
        if (__Stream->buffer[i] >= 'a' && __Stream->buffer[i] <= 'z') {
            __Stream->buffer[i] -= 'a' - 'A';
        }
    }
}

str_stream** str_split(str_stream* __Stream, char __Delim, size_t* __Count) {
    size_t __Size = 0;
    for (size_t i = 0; i < __Stream->size; i++) {
        if (__Stream->buffer[i] == __Delim) {
            __Size++;
        }
    }
    __Size++;

    str_stream** __Res = (str_stream**)malloc(__Size * sizeof(str_stream*));
    size_t __Index = 0;
    size_t __Start = 0;
    for (size_t i = 0; i < __Stream->size; i++) {
        if (__Stream->buffer[i] == __Delim) {
            __Res[__Index] = str_substr(__Stream, __Start, i - __Start);
            __Start = i + 1;
            __Index++;
        }
    }
    __Res[__Index] = str_substr(__Stream, __Start, __Stream->size - __Start);
    *__Count = __Size;
    return __Res;
}

str_stream** str_split_line(str_stream* __Stream, size_t* __Count) {
    return str_split(__Stream, '\n', __Count);
}

str_stream* str_join(str_stream** __Streams, char __Delim, size_t __Size) {
    if(__Size <= 0) return NULL;
    str_stream* __Stream = str_auto_create();
    str_append(__Stream, __Streams[0]->buffer);
    for(int i=1; i<__Size; ++i) {
        str_push_back(__Stream, __Delim);
        str_append(__Stream, __Streams[i]->buffer);
    }
    return __Stream;
}

void str_pad(str_stream* __Stream, size_t __Length, char __Ch) {
    while (__Stream->size < __Length) {
        str_push_back(__Stream, __Ch);
    }
}

void __str_swap(char* __Str, size_t __i, size_t __j) {
    char __Temp = __Str[__i];
    __Str[__i] = __Str[__j];
    __Str[__j] = __Temp;
}

size_t __str_partition(char* __Str, size_t __Low, size_t __High) {
    char __Pivot = __Str[__High];
    size_t __i = __Low - 1;

    for (size_t __j = __Low; __j < __High; __j++) {
        if (__Str[__j] <= __Pivot) {
            __i++;
            __str_swap(__Str, __i, __j);
        }
    }
    __str_swap(__Str, __i + 1, __High);
    return __i + 1;
}

void __str_quick_sort(char* __Str, size_t __Low, size_t __High) {
    if (__Low < __High) {
        size_t __Pivot = __str_partition(__Str, __Low, __High);
        __str_quick_sort(__Str, __Low, __Pivot - 1);
        __str_quick_sort(__Str, __Pivot + 1, __High);
    }
}

void str_sort(str_stream* __Stream) {
    __str_quick_sort(__Stream->buffer, 0, __Stream->size - 1);
}

void str_rsort(str_stream* __Stream) {
    str_sort(__Stream);
    str_reverse(__Stream);
}

int str_lowerbound(str_stream* __Stream, char __Ch) {
    size_t __Low = 0, __High = __Stream->size;
    
    while (__Low < __High) {
        size_t __Mid = __Low + ((__High - __Low) >> 1);
        
        if (__Stream->buffer[__Mid] >= __Ch) {
            __High = __Mid;
        } else {
            __Low = __Mid + 1;
        }
    }

    if (__Low < __Stream->size && __Stream->buffer[__Low] >= __Ch) {
        return __Low;
    } else {
        return __Low + 1;
    }
}

int str_upperbound(str_stream* __Stream, char __Ch) {
    size_t __Low = 0, __High = __Stream->size;
    
    while (__Low < __High) {
        size_t __Mid = __Low + ((__High - __Low) >> 1);
        
        if (__Stream->buffer[__Mid] <= __Ch) {
            __Low = __Mid + 1;
        } else {
            __High = __Mid;
        }
    }

    if (__Low > 0 && __Stream->buffer[__Low - 1] <= __Ch) {
        return __Low - 1;
    } else {
        return __Low;
    }
}
