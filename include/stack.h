#ifndef __STACK_H__
#define __STACK_H__

class Stack {
private:
    uint16_t data[16];
public:
    uint8_t sp;
    uint8_t bs;
    
    Stack();
    ~Stack();

    void push(uint8_t value);
    uint8_t pop(); 
};

#endif
