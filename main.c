#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

// NEW: Include the compiler
#include "compiler.h" 

static void repl() {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    // Compile and run the line
    Chunk chunk;
    initChunk(&chunk);
    
    if (compile(line, &chunk)) {
      interpret(&chunk);
    }
    
    freeChunk(&chunk);
  }
}

int main(int argc, const char* argv[]) {
  initVM();

  // Run the Read-Eval-Print Loop (REPL)
  repl();

  freeVM();
  return 0;
}