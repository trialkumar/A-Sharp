#include <stdio.h>
#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"
#include "scanner.h" // <--- Import the scanner

int main(int argc, const char* argv[]) {
  // Feed source code directly to the scanner
  const char* source = "1 + 2 * (3 - 4) * (5/10)";
  initScanner(source);

  // Print every token found until we hit the end
  int line = -1;
  for (;;) {
    Token token = scanToken();
    if (token.line != line) {
      printf("%4d ", token.line);
      line = token.line;
    } else {
      printf("   | ");
    }
    
    // Print the token type and the actual text
    printf("%2d '%.*s'\n", token.type, token.length, token.start); 

    if (token.type == TOKEN_EOF) break;
  }

  return 0;
}