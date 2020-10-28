#include <cstdint>
#include <iostream>
#include "stack.h"

Stack::Stack() : data{0}, sp(0), bs(0) {
    
}

Stack::~Stack() {

}

void Stack::push(uint8_t value) {
    if(sp >= 15) {
        return;
    }
    data[sp++] = value;
}

uint8_t Stack::pop() {
    if(sp == bs) {
        return 0;
    }
    return data[sp--];
}