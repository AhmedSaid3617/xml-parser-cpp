//
// Created by Shams El-Din Abdel-Monem on 09/12/2024.
//

#ifndef XML_PARSER_DYNAMICARRAY_H
#define XML_PARSER_DYNAMICARRAY_H

#include <cstdint>

template<class K>
class DynamicArray {
private:
    uint32_t consumed;
    uint32_t capacity;
    K list[];

    void resize_list(uint32_t resized_capacity);

public:
    explicit DynamicArray(uint32_t capacity = 100);
    K get(uint32_t index);
    void remove(uint32_t index);
    void add(K entry);

};

#endif //XML_PARSER_DYNAMICARRAY_H
