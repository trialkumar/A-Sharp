#include <stdio.h>
#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

void initVM(){
    vm.stackTop = vm.stack;
}

void freeVM(){

}

void push(Value value){
    *vm.stackTop = value; //put the value in empty slot
    vm.stackTop++; //Move the pointer up
}//Not checking for overflow yet!

Value pop(){
    vm.stackTop--;
    return *vm.stackTop;
}

//The Engine Loop
static InterpretResult run(){
    //macro: Read the byte currently pointed at by ip, then advance ip
    #define READ_BYTE() (*vm.ip++)
    //macro: Read the next, use it as an index and look up the constant
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for(;;){
        #ifndef DEBUG_TRACE_EXECUTION
        printf("        ");
        for(Value* slot = vm.stack; slot < vm.stackTop; slot++){
            printf("[ ");
            printfValue(*slot);
            printf(" ]");
        }
        printf("\n");
        // Disassemble the current instruction so we see what's happening
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction = READ_BYTE();
    switch (instruction) {
      case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        push(constant); // Push the number onto the stack
        break;
      }
      case OP_RETURN: {
        printValue(pop()); // Pop the result and print it
        printf("\n");
        return INTERPRET_OK;
      }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code; // Start IP at the beginning of the chunk
  return run();
}