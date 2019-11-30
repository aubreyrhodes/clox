#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"
#include "table.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);
void displayTable(Table* table);

#endif