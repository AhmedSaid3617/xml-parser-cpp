//
// Created by Shams El-Din Abdel-Monem on 09/12/2024.
//

#ifndef XML_PARSER_DYNAMICARRAY_H
#define XML_PARSER_DYNAMICARRAY_H

#include <cstdint>

#include <stdexcept>
#include <algorithm>
#include <string>
#include <sstream>

class ArrayIndexException : public std::exception {
private:
    std::string message;
    size_t index;
    size_t array_size;

public:
    // Constructor with detailed information
    ArrayIndexException(size_t index, size_t array_size)
            : index(index), array_size(array_size) {
        std::ostringstream oss;
        oss << "Index " << index << " is out of range. Array size is " << array_size;
        message = oss.str();
    }

    // Override what() to provide custom error message
    const char* what() const noexcept override {
        return message.c_str();
    }

    // Additional methods to get specific error details
    size_t get_index() const { return index; }
    size_t get_array_size() const { return array_size; }
};

template<class K>
class DynamicArray {
private:
    uint32_t consumed;
    uint32_t capacity;
    K ** list;

    void resize_list(uint32_t resized_capacity);

public:
    explicit DynamicArray(uint32_t capacity = 100);
    uint32_t get_capacity() {
        return capacity;
    }
    uint32_t get_consumed() {
        return consumed;
    }
    K * get(uint32_t index);
    void remove(uint32_t index);
    uint32_t add(K * entry);

};

template<class K>
K * DynamicArray<K>::get(uint32_t index) {
    if (index < consumed)
        return list[index];

    throw ArrayIndexException(index, consumed);
}

template<class K>
void DynamicArray<K>::remove(uint32_t index) {
    for (uint32_t i = index; i < consumed - 1; ++i) {
        list[i] = list[i + 1];
    }

    consumed--;
}

template<class K>
uint32_t DynamicArray<K>::add(K * entry) {
    if (capacity < consumed + 1)
        resize_list(2 * capacity);

    list[consumed++] = entry;
    return consumed - 1;
}

template<class K>
DynamicArray<K>::DynamicArray(uint32_t capacity): capacity(capacity), consumed(0) {
    list = new K*[capacity];
}

template<class K>
void DynamicArray<K>::resize_list(uint32_t resized_capacity) {
    K ** resized_list = new K*[resized_capacity];

    for (int i = 0; i < capacity; ++i) {
        resized_list[i] = list[i];
    }

    delete[] list;

    list = resized_list;
    capacity = resized_capacity;
}

#endif //XML_PARSER_DYNAMICARRAY_H
