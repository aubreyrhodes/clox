#include <stdio.h>

#include "common.h"
#include "vm.h"
#include "memory.h"

#ifdef DEBUG_TRACE_EXECUTION
#include "debug.h"
#endif

VM vm;

static void resetStack() {
    vm.stack = NULL;
    vm.stackCapacity = 0;
    vm.stackTop = 0;
}

void initVM(){
    resetStack();
}

void freeVM(){
    FREE_ARRAY(Value, vm.stack, vm.stackCapacity);
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do { \
        double a = pop(); \
        double b = pop(); \
        push(a op b); \
    } while (false)

    for(;;) {

#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");                                           
    for (int slot = 0; slot < vm.stackTop; slot++) {      
      printf("[ ");                                                 
      printValue(vm.stack[slot]);                                            
      printf(" ]");                                                 
    }                                                               
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction;
        switch(instruction = READ_BYTE()){
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_NEGATE:   push(-pop()); break;
            case OP_ADD:      BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_DIVIDE:   BINARY_OP(/); break;
            case OP_MULTIPY:  BINARY_OP(*); break;
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(Chunk* chunk){
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}

void push(Value value) {
    if(vm.stackTop >= vm.stackCapacity){
        int oldCapacity = vm.stackCapacity;
        vm.stackCapacity = GROW_CAPACITY(oldCapacity);
        vm.stack = GROW_ARRAY(vm.stack, Value, oldCapacity, vm.stackCapacity);
    }

    vm.stack[vm.stackTop] = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return vm.stack[vm.stackTop];
}