#ifndef clox_table_h
#define clox_table_h

#include "common.h"
#include "value.h"

typedef struct {
  ObjString* key;
  Value value;
} Entry;

typedef struct {
  int count;
  int capacity;
  Entry* entries;
} Table;

void freeTable(Table* table);
void initTable(Table* table);
void tableAddAll(Table* from, Table* to);
bool tableDelete(Table* table, ObjString* key);
ObjString* tableFindString(Table* table, const char* chars, int length, uint32_t hash);
bool tableGet(Table* table, ObjString* key, Value* value);
bool tableSet(Table* table, ObjString* key, Value value);

#endif