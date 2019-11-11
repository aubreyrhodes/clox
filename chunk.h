#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_ADD,
  OP_CONSTANT,
  OP_DIVIDE,
  OP_FALSE,
  OP_MULTIPLY,
  OP_NEGATE,
  OP_NIL,
  OP_NOT,
  OP_RETURN,
  OP_SUBTRACT,
  OP_TRUE
} OpCode;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  int* lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);

#endif