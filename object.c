#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType) \
  (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {
  Obj* object = (Obj*)reallocate(NULL, 0, size);
  object->type = type;

  object->next = vm.objects;
  vm.objects = object;

  return object;
}

static ObjString* allocateString(char* chars, int length) {
  ObjString* string = (ObjString*)allocateObject(sizeof(ObjString) + sizeof(char) * length + 1, OBJ_STRING);
  string->length = length + 1;
  strcpy(string->chars, chars);
  string->chars[string->length] = '\0';

  return string;
}

ObjString* copyString(const char* chars, int length) {
  return allocateString(chars, length);
}

void printObject(Value value) {
  switch(OBJ_TYPE(value)) {
    case OBJ_STRING:
      printf("%s", AS_CSTRING(value));
      break;
  }
}

ObjString* takeString(char* chars, int length) {
  return allocateString(chars, length);
}