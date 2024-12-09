#include "DynamicArray.h"

template<class K>
K DynamicArray<K>::get(uint32_t index) {
    return list[index];
}

template<class K>
void DynamicArray<K>::remove(uint32_t index) {
    for (uint32_t i = index; i < consumed - 1; ++i) {
        list[i] = list[i + 1];
    }

    consumed--;
}

template<class K>
void DynamicArray<K>::add(K entry) {
    if (capacity < consumed + 1)
        resize_list(2 * capacity);

    list[consumed++] = entry;
}

template<class K>
DynamicArray<K>::DynamicArray(uint32_t capacity): capacity(capacity), consumed(0) {
    list = new K[capacity];
}

template<class K>
void DynamicArray<K>::resize_list(uint32_t resized_capacity) {
    static_assert(resized_capacity > capacity);

    K resized_list[] = new K[resized_capacity];

    for (int i = 0; i < capacity; ++i) {
        resized_list[i] = list[i];
    }

    delete[] list;

    list = resized_list;
    capacity = resized_capacity;
}