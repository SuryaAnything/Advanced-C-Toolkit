#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "darray.h"

void darray_init(darray_t *darray) {
    darray->data = (int *)malloc(sizeof(int) * __DEFAULT_DARRAY_CAPACITY);
    darray->size = 0;
    darray->capacity = __DEFAULT_DARRAY_CAPACITY;
    darray->element_size = 0;
    darray->free_fn = NULL;
}

darray_t *darray_create() {
    darray_t *darray = (darray_t *)malloc(sizeof(darray_t));
    if (darray == NULL) {
        return NULL;
    }
    darray->data = (int *)malloc(sizeof(int) * __DEFAULT_DARRAY_CAPACITY);
    darray->size = 0;
    darray->capacity = 0;
    darray->element_size = 0;
    darray->free_fn = NULL;
    return darray;
}

void darray_flush(darray_t *darray) {
    if (darray == NULL) {
        return;
    }
    if (darray->free_fn != NULL) {
        for (size_t i = 0; i < darray->size; i++) {
            darray->free_fn(&darray->data[i]);
        }
    }
    free(darray->data);
    free(darray);
}

void darray_push(darray_t *darray, int value) {
    if (darray == NULL) {
        return;
    }
    if (darray->size == darray->capacity) {
        darray->capacity = darray->capacity == 0 ? __DEFAULT_DARRAY_CAPACITY : darray->capacity * 2;
        darray->data = (int *)realloc(darray->data, sizeof(int) * darray->capacity);
    }
    darray->data[darray->size++] = value;
}

int darray_pop(darray_t *darray) {
    if (darray == NULL || darray->size == 0) {
        return -1;
    }
    return darray->data[--darray->size];
}

void darray_set_free_fn(darray_t *darray, void (*free_fn)(void *)) {
    if (darray == NULL) {
        return;
    }
    darray->free_fn = free_fn;
}

void darray_print(darray_t *darray) {
    if (darray == NULL) {
        return;
    }
    for (size_t i = 0; i < darray->size; i++) {
        printf("%d ", darray->data[i]);
    }
    printf("\n");
}

int darray_size(darray_t *darray) {
    if (darray == NULL) {
        return -1;
    }
    return darray->size;
}

int darray_capacity(darray_t *darray) {
    if (darray == NULL) {
        return -1;
    }
    return darray->capacity;
}

int darray_element_size(darray_t *darray) {
    if (darray == NULL) {
        return -1;
    }
    return darray->element_size;
}

int darray_get(darray_t *darray, size_t index) {
    if (darray == NULL || index >= darray->size) {
        return -1;
    }
    return darray->data[index];
}

void darray_set(darray_t *darray, size_t index, int value) {
    if (darray == NULL || index >= darray->size) {
        return;
    }
    darray->data[index] = value;
}

int darray_front(darray_t *darray) {
    if (darray == NULL || darray->size == 0) {
        return -1;
    }
    return darray->data[0];
}

int darray_back(darray_t *darray) {
    if (darray == NULL || darray->size == 0) {
        return -1;
    }
    return darray->data[darray->size - 1];
}

int darray_empty(darray_t *darray) {
    if (darray == NULL) {
        return -1;
    }
    return darray->size == 0;
}

void darray_clear(darray_t *darray) {
    if (darray == NULL) {
        return;
    }
    darray->size = 0;
}

void darray_resize(darray_t *darray, size_t new_size) {
    if (darray == NULL) {
        return;
    }
    if (new_size < darray->size) {
        darray->size = new_size;
    } else {
        if (new_size > darray->capacity) {
            darray->capacity = new_size;
            darray->data = (int *)realloc(darray->data, sizeof(int) * darray->capacity);
        }
        for (size_t i = darray->size; i < new_size; i++) {
            darray->data[i] = 0;
        }
        darray->size = new_size;
    }
}

void darray_reserve(darray_t *darray, size_t new_capacity) {
    if (darray == NULL) {
        return;
    }
    if (new_capacity > darray->capacity) {
        darray->capacity = new_capacity;
        darray->data = (int *)realloc(darray->data, sizeof(int) * darray->capacity);
    }
}

void darray_shrink_to_fit(darray_t *darray) {
    if (darray == NULL) {
        return;
    }
    darray->capacity = darray->size;
    darray->data = (int *)realloc(darray->data, sizeof(int) * darray->capacity);
}

void darray_insert(darray_t *darray, size_t index, int value) {
    if (darray == NULL || index > darray->size) {
        return;
    }
    if (darray->size == darray->capacity) {
        darray->capacity = darray->capacity == 0 ? __DEFAULT_DARRAY_CAPACITY : darray->capacity * 2;
        darray->data = (int *)realloc(darray->data, sizeof(int) * darray->capacity);
    }
    for (size_t i = darray->size; i > index; i--) {
        darray->data[i] = darray->data[i - 1];
    }
    darray->data[index] = value;
    darray->size++;
}

void darray_erase(darray_t *darray, size_t index) {
    if (darray == NULL || index >= darray->size) {
        return;
    }
    for (size_t i = index; i < darray->size - 1; i++) {
        darray->data[i] = darray->data[i + 1];
    }
    darray->size--;
}

void darray_remove(darray_t *darray, int value) {
    if (darray == NULL) {
        return;
    }
    for (size_t i = 0; i < darray->size; i++) {
        if (darray->data[i] == value) {
            darray_erase(darray, i);
            i--;
        }
    }
}

void darray_push_front(darray_t *darray, int value) {
    if (darray == NULL) {
        return;
    }
    darray_insert(darray, 0, value);
}

void darray_pop_front(darray_t *darray) {
    if (darray == NULL || darray->size == 0) {
        return;
    }
    darray_erase(darray, 0);
}

void darray_erase_range(darray_t *darray, size_t start, size_t end) {
    if (darray == NULL || start >= darray->size || end >= darray->size) {
        return;
    }
    for (size_t i = start; i <= end; i++) {
        darray_erase(darray, start);
    }
}


void darray_push_all(darray_t *darray, int *values, size_t size) {
    if (darray == NULL || values == NULL || size == 0) {
        return;
    }

    if (darray->size + size > darray->capacity) {
        darray_reserve(darray, darray->size + size); 
    }

    memcpy(darray->data + darray->size, values, sizeof(int) * size);
    darray->size += size;
}

void darray_remove_if(darray_t *darray, int (*predicate)(int)) {
    if (darray == NULL) {
        return;
    }
    for (size_t i = 0; i < darray->size; i++) {
        if (predicate(darray->data[i])) {
            darray_erase(darray, i);
            i--;
        }
    }
}

void darray_reverse(darray_t *darray) {
    if (darray == NULL) {
        return;
    }
    for (size_t i = 0; i < darray->size / 2; i++) {
        int temp = darray->data[i];
        darray->data[i] = darray->data[darray->size - i - 1];
        darray->data[darray->size - i - 1] = temp;
    }
}


void darray_map(darray_t *darray, int (*mapper)(int)) {
    if (darray == NULL) {
        return;
    }
    for (size_t i = 0; i < darray->size; i++) {
        darray->data[i] = mapper(darray->data[i]);
    }
}

void darray_filter(darray_t *darray, int (*predicate)(int)) {
    if (darray == NULL) {
        return;
    }
    for (size_t i = 0; i < darray->size; i++) {
        if (!predicate(darray->data[i])) {
            darray_erase(darray, i);
            i--;
        }
    }
}

void darray_reduce(darray_t *darray, int (*reducer)(int, int)) {
    if (darray == NULL) {
        return;
    }
    if (darray->size == 0) {
        return;
    }
    int result = darray->data[0];
    for (size_t i = 1; i < darray->size; i++) {
        result = reducer(result, darray->data[i]);
    }
    darray->size = 1;
    darray->data[0] = result;
}

int darray_sum(darray_t* darray) {
    if (darray == NULL) {
        return -1;
    }
    int sum = 0;
    for (size_t i = 0; i < darray->size; i++) {
        sum += darray->data[i];
    }
    return sum;
}

int darray_max(darray_t* darray) {
    if (darray == NULL) {
        return -1;
    }
    if (darray->size == 0) {
        return -1;
    }
    int max = darray->data[0];
    for (size_t i = 1; i < darray->size; i++) {
        if (darray->data[i] > max) {
            max = darray->data[i];
        }
    }
    return max;
}

int darray_min(darray_t* darray) {
    if (darray == NULL) {
        return -1;
    }
    if (darray->size == 0) {
        return -1;
    }
    int min = darray->data[0];
    for (size_t i = 1; i < darray->size; i++) {
        if (darray->data[i] < min) {
            min = darray->data[i];
        }
    }
    return min;
}

int darray_avg(darray_t* darray) {
    if (darray == NULL) {
        return -1;
    }
    if (darray->size == 0) {
        return -1;
    }
    return darray_sum(darray) / darray->size;
}

int* darray_data(darray_t *darray) {
    if (darray == NULL) {
        return NULL;
    }
    return darray->data;
}

void darray_set_data(darray_t *darray, int *data, size_t size) {
    if (darray == NULL) {
        return;
    }
    darray->data = data;
    darray->size = size;
    darray->capacity = size;
}

void darray_copy(darray_t *darray, darray_t *other) {
    if (darray == NULL || other == NULL) {
        return;
    }
    darray->size = other->size;
    darray->capacity = other->capacity;
    darray->element_size = other->element_size;
    darray->free_fn = other->free_fn;
    darray->data = (int *)malloc(sizeof(int) * darray->capacity);
    for (size_t i = 0; i < darray->size; i++) {
        darray->data[i] = other->data[i];
    }
}

void darray_swap(darray_t *darray, darray_t *other) {
    if (darray == NULL || other == NULL) {
        return;
    }
    darray_t temp;
    temp.data = darray->data;
    temp.size = darray->size;
    temp.capacity = darray->capacity;
    temp.element_size = darray->element_size;
    temp.free_fn = darray->free_fn;
    darray->data = other->data;
    darray->size = other->size;
    darray->capacity = other->capacity;
    darray->element_size = other->element_size;
    darray->free_fn = other->free_fn;
    other->data = temp.data;
    other->size = temp.size;
    other->capacity = temp.capacity;
    other->element_size = temp.element_size;
    other->free_fn = temp.free_fn;
}


void darray_for_each(darray_t *darray, void (*func)(int)) {
    if (darray == NULL || func == NULL) return;
    for (size_t i = 0; i < darray->size; i++) {
        func(darray->data[i]);
    }
}


int darray_binary_search(darray_t *darray, int value) {
    if (darray == NULL || darray->size == 0) return -1;
    size_t left = 0, right = darray->size - 1;
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (darray->data[mid] == value) return mid;
        if (darray->data[mid] < value) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}


size_t darray_memory_usage(darray_t *darray) {
    if (darray == NULL) return 0;
    return sizeof(darray_t) + darray->capacity * darray->element_size;
}


void darray_replace(darray_t *darray, int old_value, int new_value) {
    if (darray == NULL) return;
    for (size_t i = 0; i < darray->size; i++) {
        if (darray->data[i] == old_value) {
            darray->data[i] = new_value;
        }
    }
}


void darray_fill(darray_t *darray, int value) {
    if (darray == NULL) return;
    for (size_t i = 0; i < darray->size; i++) {
        darray->data[i] = value;
    }
}

size_t darray_count(darray_t *darray, int value) {
    if (darray == NULL) return 0;
    size_t count = 0;
    for (size_t i = 0; i < darray->size; i++) {
        if (darray->data[i] == value) count++;
    }
    return count;
}


void __quick_sort(int *arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        int partition_index = i + 1;
        __quick_sort(arr, left, partition_index - 1);
        __quick_sort(arr, partition_index + 1, right);
    }
}

// Quick Sort Helper for custom sorting
void __quick_sort_custom(int *arr, int left, int right, int (*cmp)(int, int)) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (cmp(arr[j], pivot) <= 0) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        int partition_index = i + 1;
        __quick_sort_custom(arr, left, partition_index - 1, cmp);
        __quick_sort_custom(arr, partition_index + 1, right, cmp);
    }
}

void darray_sort(darray_t *darray) {
    if (darray == NULL || darray->size == 0) {
        return;
    }
    __quick_sort(darray->data, 0, darray->size - 1);
}

void darray_sort_custom(darray_t *darray, int (*cmp)(int, int)) {
    if (darray == NULL || darray->size == 0 || cmp == NULL) {
        return;
    }
    __quick_sort_custom(darray->data, 0, darray->size - 1, cmp);
}


size_t darray_index_of(darray_t *darray, int value) {
    if (darray == NULL) return -1;
    for (size_t i = 0; i < darray->size; i++) {
        if (darray->data[i] == value) return i;
    }
    return -1;
}

int darray_median(darray_t* darray) {
    if (darray == NULL) {
        return -1;
    }
    if (darray->size == 0) {
        return -1;
    }
    darray_sort(darray);
    if (darray->size % 2 == 0) {
        return (darray->data[darray->size / 2 - 1] + darray->data[darray->size / 2]) / 2;
    } else {
        return darray->data[darray->size / 2];
    }
}

