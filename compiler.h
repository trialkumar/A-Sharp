#ifndef asharp_compiler_h
#define asharp_compiler_h

#include "chunk.h"
#include "scanner.h"
#include "vm.h"
#include "object.h"

ObjFunction* compile(const char* source);

#endif